/* -*- c++ -*-
 *
 * Converter/mappingModel.cpp
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 */
/** @file mappingModel.cpp
 * Groups all code related to Amalthea's HwModel.
 */
#include "../AttributeCreator.h"
#include "../Diagnostic.h"
#include "Converter.h"
#include "ResolveValues.h"
#include "StimulusTraits.h"

namespace am = am210::model;

namespace am210 {

void Converter::work( const am210::model::MappingModel_ptr&,
					  am210::model::MappingModel* ) {
	if ( _mode == PreOrder ) {
		/* Nothing to do. */

	} else {
		/* Amalthea allows multiple InterruptControllers, while the INCHRON
		 * model only allows a scheduler hierarchy with a single root
		 * Scheduler. Hence, all InterruptControllers are now aggregated into
		 * a single Scheduler, Isrs are moved and inherit the CpuCore affinity
		 * [AM2INC-45].
		 *
		 * A note regarding tree traversal: The SchedulerAllocation and the
		 * IsrAllocation are both contained by the MappingModel, hence they
		 * have been processed. Both child types create a Scheduler. The
		 * InterruptController contained by the OperatingSystem only adds the
		 * name, which is not used at all, hence it does not matter if it has
		 * been processed or will be processed. */
		for ( auto&& system : _model->getSystems() ) {
			auto genericSystem = ecore::as<sm3::GenericSystem>( system );
			if ( !genericSystem )
				continue;

			auto& allSchedulers = genericSystem->getRtosConfig()->getSchedulables();
			if ( allSchedulers.size() == 0 )
				continue;
			auto rootScheduler = ecore::as<sm3::Scheduler>( allSchedulers.get( 0 ) );

			while ( allSchedulers.size() > 1 ) {
				auto scheduler = ecore::as<sm3::Scheduler>( allSchedulers.get( 1 ) );
				auto& current = scheduler->getSchedulables();
				while ( current.size() > 0 ) {
					auto schedulable = current.get( 0 );
					/* Move to new containment. */
					current.remove( schedulable );
					rootScheduler->getSchedulables().push_back_unsafe( schedulable );

					/* Copy CpuCore affinity from old scheduler to schedulable
					 * and add to new scheduler. */
					for ( auto&& cpuCore : scheduler->getCpuCores() ) {
						schedulable->getCpuCores().push_back( cpuCore );
						rootScheduler->getCpuCores().push_back( cpuCore );
					}
				}

				allSchedulers.remove( scheduler );
				_oc.reverseRemove( scheduler );
			}
		}
	}
}


void Converter::work( const am::MemoryMapping_ptr& am, am::MemoryMapping* ) {
	if ( _mode == PreOrder ) {
		/* There are 8 concrete types of AbstractMemoryElements. A
		 * MemoryElementTrait would be helpful. */
		if ( am->getAbstractElement()->eClass()->getClassifierID()
			 != am::ModelPackage::LABEL )
			return;

		auto label =
			_oc.make<sm3m::MemoryFactory, sm3m::DataObject>( am->getAbstractElement() );
		auto memory = _oc.make<sm3m::MemoryFactory, sm3m::Memory>( am->getMemory() );
		/* ignored: am->getMemoryPositionAddress() */
		label->setMemory( memory );
	}
}

void Converter::work( const am::PhysicalSectionMapping_ptr&,
					  am::PhysicalSectionMapping* ) {
	static Diagnostic::NotImplemented<am::PhysicalSectionMapping> message( this );
}

/** A SchedulerAllocation maps InterruptControllers and TaskSchedulers to ProcessingUnits.
 */
void Converter::work( const am::SchedulerAllocation_ptr& am, am::SchedulerAllocation* ) {
	if ( _mode == PreOrder ) {
		auto scheduler =
			_oc.make<sm3::ModelFactory, sm3::Scheduler>( am->getScheduler() );
		/* @todo only used for the process of the UserDefinedScheduler.
		 * auto executingCore = _oc.find<sm3::Scheduler>(am->getExecutingPU()); */

		for ( auto&& amCore : am->getResponsibility() ) {
			auto core = _oc.find<sm3::CpuCore>( amCore, ObjectCache::Default );
			scheduler->getCpuCores().push_back( core );
		}
	}
}

/** RunnableAllocations are ignored because they are not supported by the
 * INCHRON model. During the validation it should be checked, if the existing
 * RunnableAllocations and the TaskAllocations of the Tasks, which call those
 * Runnables, are in sync. Otherwise there will be undefined behaviour.
 */
void Converter::work( const am::RunnableAllocation_ptr&, am::RunnableAllocation* ) {
	static Diagnostic::NotImplemented<am::RunnableAllocation> message( this );
}

/** An IsrAllocation maps an Isr to an InterruptController.
 *
 * InterruptControllers are translated into Schedulers, which are direct
 * children of the RtosConfig. The scheduling hierarchy only supports a single
 * root, so all Isrs are later moved to a single Scheduler and the remaining
 * empty InterruptControllers will be deleted again.
 */
void Converter::work( const am210::model::ISRAllocation_ptr& am,
					  am210::model::ISRAllocation* ) {
	if ( _mode == PreOrder ) {
		auto isr = _oc.find<sm3::Process>( am->getIsr(), ObjectCache::Default );
		auto isrScheduler =
			_oc.find<sm3::Scheduler>( am->getController(), ObjectCache::Default );
		if ( isr && isrScheduler ) {
			/* We assume there is only 1 ISRAllocation per ISR. */
			isrScheduler->getSchedulables().push_back_unsafe( isr );
			isr->setPriority( am->getPriority() );
		}
	}
}

namespace details {
am::TaskScheduler_ptr getAmaltheaScheduler( const am::TaskScheduler_ptr& ts ) {
	return ts;
}
}  // end namespace details

void Converter::work( const am::TaskAllocation_ptr& am, am::TaskAllocation* ) {
	if ( _mode == PreOrder ) {
		auto task = _oc.find<sm3::Process>( am->getTask(), ObjectCache::Default );
		auto scheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>(
			details::getAmaltheaScheduler( am->getScheduler() ) );
		/* We assume there is only 1 TaskAllocation per Task. */
		scheduler->getSchedulables().push_back_unsafe( task );

		for ( auto&& amCore : am->getAffinity() ) {
			auto core = _oc.make<sm3::ModelFactory, sm3::CpuCore>( amCore );
			task->getCpuCores().push_back( core );
		}

		for ( const auto& parameter : am->getSchedulingParameters() ) {
			if ( parameter->getKey() ) {
				const auto& name = parameter->getKey()->getName();
				if ( name == "priority" ) {
					int priority = ResolveValue::resolve<int>( parameter->getValue() );
					task->setPriority( priority );
				} else if ( name == "deadline" ) {
					auto deadline =
						ResolveValue::resolve<sm3::Time_ptr>( parameter->getValue() );
					task->setDeadline( deadline );
				}
			}

			/* Other attributes of SchedulingParameters are ignored. */
		}

		/* ParameterExtensions are ignored. */
	}
}

}  // namespace am210
