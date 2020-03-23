/* -*- c++ -*-
 *
 * Converter/hwModel.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file hwModel.cpp
 * Groups all code related to Amalthea's HwModel.
 */
#include "../Converter.h"

#include "../AttributeCreator.h"


void Converter::work(const am::FrequencyDomain_ptr& am, am::FrequencyDomain*) {
	if (_mode == PreOrder) {
		auto clock = _oc.make<sm3::ModelFactory, sm3::Clock>(am);
		clock->setName(am->getName());
		clock->setFrequency(AttributeCreator<sm3::Frequency>()(am->getDefaultValue()));
		_model->getClocks().push_back(clock);
		addMapping({am}, {clock});
	}
}

void Converter::work(const am::Memory_ptr& am, am::Memory*) {
	if (_mode == PreOrder) {
		auto memory = _oc.make<sm3m::MemoryFactory, sm3m::Memory>(am);
		memory->setName(am->getName());
		if (am->getFrequencyDomain()) {
			auto clock = _oc.make<sm3::ModelFactory, sm3::Clock>(am->getFrequencyDomain());
			memory->setClock(clock);
			memory->setPrescaler(1); // ?am->getFrequencyDomain()->getDefaultValue()->getValue()
		}

		// @todo Evaluate am::Definition

		if (auto hwStructure = ecore::as<am::HwStructure>(am->eContainer())) {
			switch (hwStructure->getStructureType()) {
			case am::StructureType::System:
			case am::StructureType::ECU:
			case am::StructureType::SoC:
				_model->getMemories().push_back(memory);
				break;
			case am::StructureType::Microcontroller:
			{
				auto cpu = _oc.make<sm3::ModelFactory, sm3::Cpu>(hwStructure);
				cpu->getMemories().push_back(memory);
			} break;
			default:
				break;
			}
		}
	}
}

void Converter::work(const am::HwStructure_ptr& am, am::HwStructure*) {
	if (_mode == PreOrder) {
		switch (am->getStructureType()) {
		case am::StructureType::System:
			_model->setName(am->getName());
			break;
		case am::StructureType::ECU:
		case am::StructureType::SoC:
		case am::StructureType::Microcontroller:
		{
			auto cpu = _oc.make<sm3::ModelFactory, sm3::Cpu>(am, ObjectCache::Default);
			_model->getCpus().push_back(cpu);
			cpu->setName(am->getName());
			if (am->getModules().size() == 0) {
				cpu->setClock(_idealClock);
			} else {
				auto firstModuleClock = am->getModules().get(0)->getFrequencyDomain();
				auto clock = _oc.make<sm3::ModelFactory, sm3::Clock>(firstModuleClock);
				cpu->setClock(clock);
			}
		} break;
		default:
			break;
		}

	} else { /* PostOrder */
		switch (am->getStructureType()) {
		case am::StructureType::System:
		case am::StructureType::ECU:
		case am::StructureType::SoC:
		{

		} break;

		case am::StructureType::Microcontroller:
		{
			auto cpu = _oc.make<sm3::ModelFactory, sm3::Cpu>(am, ObjectCache::Default);
			const auto numberOfCores = cpu->getCores().size();

			if (numberOfCores > 0) {
				cpu->setCpuModel("generic");
				cpu->setReloadCpuModel(true);

				auto system = _oc.make<sm3::ModelFactory, sm3::GenericSystem>(am, ObjectCache::Sub1);
				system->setName("System_" + am->getName());
				_model->getSystems().push_back(system);
				auto isrScheduler = system->getRtosConfig()->getSchedulables().get(0);
				for (auto&& core : cpu->getCores())
					isrScheduler->getCpuCores().push_back(core);
			}

		} break;
		default:
			break;
		}
	}
}

void Converter::work(const amalthea::model::ProcessingUnit_ptr& am, amalthea::model::ProcessingUnit*) {
	if (_mode == PreOrder) {
		auto cpuCore = _oc.make<sm3::ModelFactory, sm3::CpuCore>(am);
		cpuCore->setName(am->getName());

		auto cpu = _oc.make<sm3::ModelFactory, sm3::Cpu>(am->eContainer());
		cpu->getCores().push_back(cpuCore);

		auto cpuClock = cpu->getClock();
		auto coreClock = _oc.make<sm3::ModelFactory, sm3::Clock>(am->getFrequencyDomain());
		if (cpuClock == coreClock)
			cpuCore->setPrescaler(1.);
		else {
			// @todo derive prescaler from relation of referenced
			// FrequencyDomain and parent Clock.
			cpuCore->setPrescaler(-1.);
		}
	}
}

/** A Cache is an am::HwModule and references a CacheDefinition.
 *
 * As a L1 Cache it is container at am::ProcessingUnit::caches, while as a L2
 * Cache it lives in am::HwStructure::modules (where the am::HwStructure probably
 * has the am::StructureType MicroController.
 *
 * Are L3 caches contained by an am::HwStructure with the am::StructureType ECU?
 */
void Converter::work(const amalthea::model::Cache_ptr& am, amalthea::model::Cache*) {
	if (_mode == PreOrder) {
		auto cache = _oc.make<sm3m::MemoryFactory, sm3m::CacheMemory>(am);
		cache->setName(am->getName());
		if (am->getFrequencyDomain()) {
			cache->setClock(_oc.make<sm3::ModelFactory, sm3::Clock>(am->getFrequencyDomain()));
			cache->setPrescaler(1); // ?am->getFrequencyDomain()->getDefaultValue()->getValue()
		}

		if (auto definition = am->getDefinition()) {
			cache->setSize(AttributeCreator<sm3::DataSize>()(definition->getSize()));
			// connectedSlave
			cache->setLineSize(AttributeCreator<sm3::DataSize>()(definition->getLineSize()));
			// cache->setCacheType();
			// cache->setWritePolicy(defintion->getWriteStrategy());
			cache->setCoherency(definition->isCoherency());
		}

		auto cpuCore = _oc.make<sm3::ModelFactory, sm3::CpuCore>(am->eContainer());
		sm3::Cpu_ptr cpu;
		if (cpuCore)
			cpu = ecore::as<sm3::Cpu>(cpuCore->eContainer());
		else
			cpu = _oc.make<sm3::ModelFactory, sm3::Cpu>(am->eContainer());
		cpu->getMemories().push_back(cache);
	}
}
