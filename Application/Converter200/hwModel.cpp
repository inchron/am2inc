/* -*- c++ -*-
 *
 * Converter/hwModel.cpp
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 */
/** @file hwModel.cpp
 * Groups all code related to Amalthea's HwModel.
 */
#include "../AttributeCreator.h"
#include "Converter.h"

namespace am = am200::model;

namespace am200 {

/**
 * \note Setting clock references is on behalf of the work() methods for
 * the respective hardware elements, e.g. work(HwStructure) for CPUs,
 * and work(ProcessingUnit) for cores will calculate a prescaler based
 * on the associated FrequencyDomain.
 */
void Converter::work( const am::FrequencyDomain_ptr& am, am::FrequencyDomain* ) {
	if ( _mode == PreOrder ) {
		auto clock = _oc.make<sm3::ModelFactory, sm3::Clock>( am );
		clock->setName( am->getName() );
		clock->setFrequency( AttributeCreator<sm3::Frequency, am::ModelPackage>()(
			am->getDefaultValue() ) );
		_model->getClocks().push_back_unsafe( clock );
		addMapping( { am }, { clock } );
	}
}

/*****************************************************************************
 * Hardware model elements
 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.1
 *****************************************************************************/

/** am::HwFeatureCategory is currently unsupported.
 */
void Converter::work( const am::HwFeatureCategory_ptr&, am::HwFeatureCategory* ) {}

/** am::HwFeature is currently unsupported.
 */
void Converter::work( const am::HwFeature_ptr&, am::HwFeature* ) {}

void Converter::work( const am::HwStructure_ptr& am, am::HwStructure* ) {
	if ( _mode == PreOrder ) {
		if ( am->getStructureType() == am::StructureType::System ) {
			_model->setName( am->getName() );
		}

		/* If there are CpuCores, this will be a Cpu. */
		auto numberOfProcessingUnits =
			std::count_if( am->getModules().begin(), am->getModules().end(),
						   []( am::HwModule_ptr child ) {
							   return !!ecore::as<am::ProcessingUnit>( child );
						   } );
		if ( numberOfProcessingUnits ) {
			auto cpu = _oc.make<sm3::ModelFactory, sm3::Cpu>( am, ObjectCache::Default );
			_model->getCpus().push_back_unsafe( cpu );
			cpu->setName( am->getName() );
			cpu->setCpuModel( "generic" );
			cpu->setReloadCpuModel( true );

			/** Use the frequency domain with the highest frequency
			 * of all HW modules of the HwStructure. */
			am::FrequencyDomain_ptr frequencyDomain{};
			const auto& amPkg = am::ModelPackage::_instance();
			for ( const auto& module : am->getModules() ) {
				if ( module->eClass() != amPkg->getProcessingUnit() )
					continue;
				if ( auto freqDomain = module->getFrequencyDomain() ) {
					if ( not frequencyDomain
						 or amFreq2Double( freqDomain->getDefaultValue() )
								> amFreq2Double( frequencyDomain->getDefaultValue() ) )
						frequencyDomain = freqDomain;
				}
			}

			auto clock = _oc.make<sm3::ModelFactory, sm3::Clock>( frequencyDomain );
			clock->setFrequency( AttributeCreator<sm3::Frequency, am::ModelPackage>()(
				frequencyDomain->getDefaultValue() ) );
			cpu->setClock( clock );
		}

	} else { /* PostOrder */
	}
}

/** Connect two HwPorts. If there is a mismatch of the PortTypes, the connection will be dropped.
 */
void Converter::work( const am::HwConnection_ptr& am, am::HwConnection* ) {
	if ( not withMemory() )
		return;

	if ( _mode == PreOrder ) {
		/* It does not matter if the used HwPorts have already been converted
		 * to INCHRON InitiatorPorts respective ResponderPorts or not. Just
		 * create them on the fly and they will be initialized lateron. */
		auto port1 = am->getPort1();
		auto port2 = am->getPort2();
		if ( !port1 || !port2 )
			return;
		if ( port1->getPortType() == am::PortType::_undefined_
			 || port2->getPortType() == am::PortType::_undefined_
			 || port1->getPortType() == port2->getPortType() )
			return;

		if ( port1->getPortType() == am::PortType::initiator ) {
			auto initiator = _oc.make<sm3m::MemoryFactory, sm3m::InitiatorPort>( port1 );
			auto responder = _oc.make<sm3m::MemoryFactory, sm3m::ResponderPort>( port2 );
			initiator->setResponder( responder );
		} else {
			auto responder = _oc.make<sm3m::MemoryFactory, sm3m::ResponderPort>( port1 );
			auto initiator = _oc.make<sm3m::MemoryFactory, sm3m::InitiatorPort>( port2 );
			initiator->setResponder( responder );
		}
	}
}

void Converter::work( const am::HwPort_ptr& am, am::HwPort* ) {
	if ( not withMemory() )
		return;

	if ( _mode == PreOrder ) {
		auto hwModule = ecore::as<am::HwModule>( am->eContainer() );
		if ( !hwModule )
			return;

		auto inchron = _oc.find<ecore::EObject>( hwModule, ObjectCache::Default );
		if ( !inchron )
			return;

		if ( am->getPortType() == am::PortType::initiator ) {
			auto port = _oc.make<sm3m::MemoryFactory, sm3m::InitiatorPort>( am );
			port->setName( am->getName() );
			port->setPriority( am->getPriority() );

			if ( auto p = ecore::as<sm3m::Interconnect>( inchron ) ) {
				p->getInitiators().push_back_unsafe( port );
			} else if ( auto p = ecore::as<sm3::CpuCore>( inchron ) ) {
				p->setInitiator( port );
				p->setBitWidth( AttributeCreator<sm3::DataSize, am::ModelPackage>()(
					am->getBitWidth(), sm3::DataSizeUnit::B ) );
				// } else if (auto p = ecore::as<sm3m::Memory>(inchron)) {
			} else if ( auto p = ecore::as<sm3m::CacheMemory>( inchron ) ) {
				p->setInitiator( port );
				p->setBitWidth( AttributeCreator<sm3::DataSize, am::ModelPackage>()(
					am->getBitWidth(), sm3::DataSizeUnit::B ) );
			}

		} else if ( am->getPortType() == am::PortType::responder ) {
			auto port = _oc.make<sm3m::MemoryFactory, sm3m::ResponderPort>( am );
			port->setName( am->getName() );

			if ( auto p = ecore::as<sm3m::Interconnect>( inchron ) ) {
				p->getResponders().push_back_unsafe( port );
				// } else if (auto p = ecore::as<sm3::CpuCore>(inchron)) {
			} else if ( auto p = ecore::as<sm3m::Memory>( inchron ) ) {
				p->setResponder( port );
				p->setBitWidth( AttributeCreator<sm3::DataSize, am::ModelPackage>()(
					am->getBitWidth(), sm3::DataSizeUnit::B ) );
			} else if ( auto p = ecore::as<sm3m::CacheMemory>( inchron ) ) {
				p->setResponder( port );
				p->setBitWidth( AttributeCreator<sm3::DataSize, am::ModelPackage>()(
					am->getBitWidth(), sm3::DataSizeUnit::B ) );
			}
		}
	}
}


/*****************************************************************************
 * Hardware modules and access elements
 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.3
 *****************************************************************************/

void Converter::work( const am::ProcessingUnit_ptr& am, am::ProcessingUnit* ) {
	if ( _mode != PreOrder )
		return;
	if ( auto hwStructure = ecore::as<am::HwStructure>( am->eContainer() ) ) {
		auto cpuCore = _oc.make<sm3::ModelFactory, sm3::CpuCore>( am );
		cpuCore->setName( am->getName() );
		cpuCore->setBitWidth( AttributeCreator<sm3::DataSize, am::ModelPackage>()(
			64, sm3::DataSizeUnit::bit ) );
		cpuCore->setInitiator( sm3m::create<sm3m::InitiatorPort>() );
		cpuCore->getInitiator()->setName( "from_" + am->getName() );

		sm3::Cpu_ptr cpu = _oc.find<sm3::Cpu>( hwStructure, ObjectCache::Default );
		cpu->getCores().push_back_unsafe( cpuCore );

		double prescaler{ 1. };
		if ( auto cpuClock = cpu->getClock() )
			if ( auto cpuFrequency = cpuClock->getFrequency() ) {
				if ( auto coreFrequency =
						 AttributeCreator<sm3::Frequency, am::ModelPackage>()(
							 am->getFrequencyDomain()->getDefaultValue() ) ) {
					const double cpuFreq = incFreq2Double( cpuFrequency );
					const double coreFreq = incFreq2Double( coreFrequency );
					if ( coreFreq != cpuFreq )
						prescaler = cpuFreq / coreFreq;
				}
			}
		cpuCore->setPrescaler( prescaler );
	}
}

void Converter::work( const am::Memory_ptr& am, am::Memory* ) {
	if ( not withMemory() )
		return;

	if ( _mode == PreOrder ) {
		auto memory = _oc.make<sm3m::MemoryFactory, sm3m::Memory>( am );
		memory->setName( am->getName() );
		memory->setBitWidth( AttributeCreator<sm3::DataSize, am::ModelPackage>()(
			64, sm3::DataSizeUnit::bit ) );
		memory->setResponder( sm3m::create<sm3m::ResponderPort>() );
		memory->getResponder()->setName( "ResponderPort" );

		if ( am->getFrequencyDomain() ) {
			auto clock =
				_oc.make<sm3::ModelFactory, sm3::Clock>( am->getFrequencyDomain() );
			memory->setClock( clock );
			memory->setPrescaler(
				1 );  // ?am->getFrequencyDomain()->getDefaultValue()->getValue()
		}

		if ( auto def = am->getDefinition() ) {
			memory->setSize(
				AttributeCreator<sm3::DataSize, am::ModelPackage>()( def->getSize() ) );
			// def->getDataRate() - ignored
			// def->getClassifiers() - ignored
		}

		// am->getMappings() - ignored

		if ( auto hwStructure = ecore::as<am::HwStructure>( am->eContainer() ) ) {
			sm3m::Interconnect_ptr interconnect;

			sm3::Cpu_ptr cpu = _oc.find<sm3::Cpu>( hwStructure, ObjectCache::Default );
			if ( !cpu ) {
				_model->getMemories().push_back_unsafe( memory );
			} else {
				cpu->getMemories().push_back_unsafe( memory );
			}
		}
	}
}

namespace details {

sm3m::CacheType convert( am::CacheType t ) {
	switch ( t ) {
	case am::CacheType::instruction:
		return sm3m::CacheType::Instruction;
	case am::CacheType::data:
		return sm3m::CacheType::Data;
	case am::CacheType::unified:
	default:
		return sm3m::CacheType::Unified;
	}
}

sm3m::CacheWritePolicy convert( am::WriteStrategy s ) {
	switch ( s ) {
	case am::WriteStrategy::writeback:
		return sm3m::CacheWritePolicy::WriteBack;
	case am::WriteStrategy::writethrough:
	case am::WriteStrategy::none:
	default:
		return sm3m::CacheWritePolicy::WriteThrough;
	}
}

}  // namespace details

/** A Cache is an am::HwModule and references a CacheDefinition.
 *
 * As a L1 Cache it is container at am::ProcessingUnit::caches, while as a L2
 * Cache it lives in am::HwStructure::modules (where the am::HwStructure probably
 * has the am::StructureType Microcontroller.
 *
 * Are L3 caches contained by an am::HwStructure with the am::StructureType ECU?
 */
void Converter::work( const am::Cache_ptr& am, am::Cache* ) {
	if ( not withMemory() )
		return;

	if ( _mode == PreOrder ) {
		auto cache = _oc.make<sm3m::MemoryFactory, sm3m::CacheMemory>( am );
		cache->setName( am->getName() );
		if ( am->getFrequencyDomain() ) {
			cache->setClock(
				_oc.make<sm3::ModelFactory, sm3::Clock>( am->getFrequencyDomain() ) );
			cache->setPrescaler(
				1 );  // ?am->getFrequencyDomain()->getDefaultValue()->getValue()
		}

		if ( auto definition = am->getDefinition() ) {
			cache->setSize( AttributeCreator<sm3::DataSize, am::ModelPackage>()(
				definition->getSize() ) );
			cache->setLineSize( AttributeCreator<sm3::DataSize, am::ModelPackage>()(
				definition->getLineSize() ) );
			cache->setCacheType( details::convert( definition->getCacheType() ) );
			cache->setWritePolicy( details::convert( definition->getWriteStrategy() ) );
			cache->setCoherency( definition->isCoherency() );
		}

		auto cpuCore = _oc.make<sm3::ModelFactory, sm3::CpuCore>( am->eContainer() );
		sm3::Cpu_ptr cpu;
		if ( cpuCore )
			cpu = ecore::as<sm3::Cpu>( cpuCore->eContainer() );
		else
			cpu = _oc.make<sm3::ModelFactory, sm3::Cpu>( am->eContainer() );
		cpu->getMemories().push_back_unsafe( cache );
	}
}

/** An am::ConnectionHandler can be any bus system. We take a look at the type
 * of its ports and synthesize sm3m::Interconnects if it matches.
 */
void Converter::work( const am::ConnectionHandler_ptr& am, am::ConnectionHandler* ) {
	if ( not withMemory() )
		return;

	if ( _mode == PreOrder ) {
		if ( am->getPorts().size() == 0 )
			return;
		auto type = am->getPorts().get( 0 )->getPortInterface();
		switch ( type ) {
		case am::PortInterface::AXI:
		case am::PortInterface::AHB:
		case am::PortInterface::APB:
		case am::PortInterface::custom:
			break;
		default:
			return; /* unsupported type */
		}

		_connectionHandlersDefined = true;

		auto ic = _oc.make<sm3m::MemoryFactory, sm3m::Interconnect>( am );
		ic->setName( am->getName() );
		// am->getDefinition() - ignored
		// am->getInternalConnections() - ignored

		int maxPortWidth = 0;
		for ( auto&& port : am->getPorts() )
			if ( maxPortWidth < port->getBitWidth() )
				maxPortWidth = port->getBitWidth();
		ic->getBitWidth()->setValue( maxPortWidth );
		ic->getBitWidth()->setUnit( sm3::DataSizeUnit::bit );

		if ( am->getFrequencyDomain() ) {
			ic->setClock(
				_oc.make<sm3::ModelFactory, sm3::Clock>( am->getFrequencyDomain() ) );
			ic->setPrescaler( 1. );
		}

		if ( auto hwStructure = ecore::as<am::HwStructure>( am->eContainer() ) ) {
			if ( auto cpu = _oc.find<sm3::Cpu>( hwStructure, ObjectCache::Default ) )
				cpu->getInterconnects().push_back_unsafe( ic );
			else
				_model->getInterconnects().push_back_unsafe( ic );
		}
	}
}

/** am::HwAccessElement is currently unsupported.
 */
void Converter::work( const am::HwAccessElement_ptr&, am::HwAccessElement* ) {}

/** am::HwAccessPath is currently unsupported.
 */
void Converter::work( const am::HwAccessPath_ptr&, am::HwAccessPath* ) {}

}  // namespace am200
