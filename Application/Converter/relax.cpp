/* -*- c++ -*-
 *
 * Converter.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#include "../Converter.h"

#include "../AttributeCreator.h"

/** @file relax.cpp
 * Groups all code related to fixing a possible incomplete model.
 */

/** Check and repair the model as much as possible, e.g. add Interconnects and
 * connect all CpuCores to them.
 */
void Converter::relax() {
	relaxHardware();
	relaxIsrSchedulers();
	relaxFreeObjects();
}

void Converter::relaxHardware() {
	/* Add Interconnect to Cpus. */
	for (auto&& cpu : _model->getCpus()) {
		const auto numberOfCores = cpu->getCores().size();
		const auto numberOfMemories = cpu->getMemories().size();

		if (numberOfCores > 0 || numberOfMemories > 0) {
			/* Ensure there is a cpu-level interconnect. */
			if (cpu->getInterconnects().size() == 0) {
				auto ic = sm3m::create<sm3m::Interconnect>();

				ic->setName(cpu->getName() + "_Interconnect");
				ic->setClock(cpu->getClock());
				auto bitWidth = sm3::create<sm3::DataSize>();
				*bitWidth = *(cpu->getCores().get(0)->getBitWidth());
				ic->setBitWidth(bitWidth);

				cpu->getInterconnects().push_back(ic);
			}

			auto ic = cpu->getInterconnects().get(0);

			/* Connect all CpuCores. */
			while (ic->getConnectedMasters().size() < numberOfCores) {
				auto port = sm3m::create<sm3m::ResponderPort>();
				ic->getConnectedMasters().push_back(port);
			}
			for (auto i = 0u; i < numberOfCores; ++i) {
				ic->getConnectedMasters().get(i)->setName(
					"to_" + cpu->getCores().get(i)->getName() );
				ic->getConnectedMasters().get(i)->setInitiator(
					cpu->getCores().get(i)->getConnectedSlave() );
			}

			sm3m::CacheMemory* theCache{nullptr};

			for (auto&& memory : cpu->getMemories()) {
				if (!memory->getConnectedMaster()) {
					auto port = sm3m::create<sm3m::ResponderPort>();
					port->setName("to_CpuInterconnect");
					memory->setConnectedMaster(port);
				}
				if (memory->eClass()->getClassifierID() == sm3m::MemoryPackage::CACHEMEMORY) {
					theCache = ecore::as<sm3m::CacheMemory>(memory.get());
					if (!theCache->getConnectedSlave()) {
						auto port = sm3m::create<sm3m::InitiatorPort>();
						port->setName("to_SystemInterconnect");
						theCache->setConnectedSlave(port);
					}
				}
			}

			/* Connect all Memories. */
			const auto neededInitiatorPorts = numberOfMemories + (theCache ? 0 : 1);
			while (ic->getConnectedSlaves().size() < neededInitiatorPorts) {
				auto port = sm3m::create<sm3m::InitiatorPort>();
				ic->getConnectedSlaves().push_back(port);
			}
			for (auto i = 0u; i < numberOfMemories; ++i) {
				ic->getConnectedSlaves().get(i)->setName(
					"to_" + cpu->getMemories().get(i)->getName() );
				ic->getConnectedSlaves().get(i)->setResponder(
					cpu->getMemories().get(i)->getConnectedMaster() );
			}

			/* Set outgoing port to upper level network. */
			sm3m::InitiatorPort_ptr port;
			if (theCache)
				port = theCache->getConnectedSlave();
			else
				port = ic->getConnectedSlaves().get(numberOfMemories);
			auto amStructure = _oc.reverseFind<am::HwStructure>(cpu);
			_oc.add(amStructure, ObjectCache::Sub2, port);

		} // if (numberOfCores > 0 || numberOfMemories > 0)
	}

	/* Add Interconnect at Model level. */
	const auto numberOfSubStructures = _model->getCpus().size();
	const auto numberOfMemories = _model->getMemories().size();
	if (numberOfSubStructures > 0 || numberOfMemories > 0) {
		/* Ensure there is a model-level interconnect. */
		if (_model->getInterconnects().size() == 0) {
			auto ic = sm3m::create<sm3m::Interconnect>();
			ic->setName("Interconnect");
			ic->setClock(_idealClock);
			_model->getInterconnects().push_back(ic);
		}

		auto ic = _model->getInterconnects().get(0);

		/* Connect all substructures */
		while (ic->getConnectedMasters().size() < numberOfSubStructures) {
			auto port = sm3m::create<sm3m::ResponderPort>();
			ic->getConnectedMasters().push_back(port);
		}
		for (auto i = 0u; i < numberOfSubStructures; ++i) {
			auto cpu = _model->getCpus().get(i);
			ic->getConnectedMasters().get(i)->setName(
				"to_" + cpu->getName() );
			auto amStructure = _oc.reverseFind<am::HwStructure>(cpu);
			auto port = _oc.find<sm3m::InitiatorPort>(amStructure, ObjectCache::Sub2);
			ic->getConnectedMasters().get(i)->setInitiator(port);
		}

		/* Connect all Memories. */
		while (ic->getConnectedSlaves().size() < numberOfMemories) {
			auto port = sm3m::create<sm3m::InitiatorPort>();
			ic->getConnectedSlaves().push_back(port);
		}
		for (auto i = 0u; i < numberOfMemories; ++i) {
			auto memory = _model->getMemories().get(i);
			ic->getConnectedSlaves().get(i)->setName(
				"to_" + memory->getName() );
			auto port = memory->getConnectedMaster();
			ic->getConnectedSlaves().get(i)->setResponder(port);
		}
	} // if (numberOfSubStructures > 0 || numberOfMemories > 0)
}


void Converter::relaxIsrSchedulers() {
	/* Set CpuCore affinity of IsrSchedulers if missing. */
	for (auto&& system : _model->getSystems()) {
		if (auto genericSystem = ecore::as<sm3::GenericSystem>(system)) {
			auto isrScheduler = ecore::as<sm3::Scheduler>(
				genericSystem->getRtosConfig()->getSchedulables().get(0));
			if (isrScheduler->getCpuCores().size() > 0)
				continue;
			if (isrScheduler->getSchedulables().size() == 0)
				continue;

			auto defaultScheduler = ecore::as<sm3::Scheduler>(
				isrScheduler->getSchedulables().get(0));
			/* Allow multiple Systems to be mapped to different CpuCores of
			 * the same Cpu. */
			for (auto&& core : defaultScheduler->getCpuCores())
				isrScheduler->getCpuCores().push_back(core);
		}
	}
}

namespace /* anonymous */ {

std::underlying_type<ObjectCache::SubKey>::type operator +(ObjectCache::SubKey val) {
	return static_cast< typename std::underlying_type<ObjectCache::SubKey>::type >(val);
}

ObjectCache::SubKey operator ++(ObjectCache::SubKey& val) {
	return val = static_cast<ObjectCache::SubKey>( + val + 1 );
}

} // anonymous namespace

void Converter::relaxFreeObjects() {
	auto globalComponent = sm3::create<sm3::Component>();
	globalComponent->setName("__GLOBAL__");
	ModelChecker<sm3::Component>().work(globalComponent);

	auto globalSystem = sm3::create<sm3::GenericSystem>();
	ModelChecker<sm3::GenericSystem>().work(globalSystem);
	globalSystem->setName("__GLOBAL__");

	auto globalRtos = globalSystem->getRtosConfig();
	auto globalIsrScheduler = ecore::as<sm3::Scheduler>(globalRtos->getSchedulables().get(0));
	auto globalProcessScheduler = ecore::as<sm3::Scheduler>(
		globalIsrScheduler->getSchedulables().get(0));

	for (auto&& e : _oc.getContent()) {
		auto&& values = e.second;
		for (auto key = ObjectCache::Default; key < ObjectCache::MaxSubKey; ++key) {
			const auto& object = values[key];
			if (!object || object->eContainer())
				continue;

			/* The object is valid and is not located in a container. */
			if (auto function = ecore::as<sm3::Function>(object)) {
				globalComponent->getFunctions().push_back(function);
			} else if (auto dataObject = ecore::as<sm3m::DataObject>(object)) {
				globalComponent->getVariables().push_back(dataObject);
			} else if (auto event = ecore::as<sm3::Event>(object)) {
				globalRtos->getEvents().push_back(event);
			} else if (auto process = ecore::as<sm3::Process>(object)) {
				if (process->isIsr())
					globalIsrScheduler->getSchedulables().push_back(process);
				else
					globalProcessScheduler->getSchedulables().push_back(process);

			} else {
				std::cerr << "Ignoring object w/o container of type "
						  << object->eClass()->getName() << "\n";
			}
		}
	}

	bool keepSystem = false;

	if ( globalComponent->getFunctions().size()
		 || globalComponent->getVariables().size()) {
		globalSystem->getComponents().push_back(globalComponent);
		keepSystem = true;
	}

	if ( keepSystem
		 || globalRtos->getEvents().size() ) {
		_model->getSystems().push_back(globalSystem);
	}
}
