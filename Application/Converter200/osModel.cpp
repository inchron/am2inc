/* -*- c++ -*-
 *
 * Converter/osModel.cpp
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 */
/** @file osModel.cpp
 * Groups all code related to Amalthea's OsModel.
 */
#include "../AttributeCreator.h"
#include "Converter.h"
#include "StimulusTraits.h"

namespace am200 {

void Converter::work( const am200::model::OperatingSystem_ptr& am,
					  am200::model::OperatingSystem* ) {
	if ( _mode == PreOrder ) {
		auto system = _oc.make<sm3::ModelFactory, sm3::GenericSystem>( am );
		system->setName( am->getName() );
		_model->getSystems().push_back_unsafe( system );

		auto isrScheduler = ecore::as<sm3::Scheduler>(
			system->getRtosConfig()->getSchedulables().get( 0 ) );
		assert( isrScheduler );
		_schedulerHierarchy.push_back( isrScheduler );
		isrScheduler->getSchedulables().clear();

	} else {
		_schedulerHierarchy.pop_back();
		assert( _schedulerHierarchy.empty() );
	}
}

/** All InterruptController instances are to the RtosConfig of the current
 * OperatingSystem. In a later phase the will be unified to a single top level
 * Scheduler.
 */
void Converter::work( const am200::model::InterruptController_ptr& am,
					  am200::model::InterruptController* ) {
	if ( _mode == PreOrder ) {
		if ( auto os = ecore::as<am200::model::OperatingSystem>( am->eContainer() ) ) {
			auto isrScheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>( am );
			isrScheduler->setName( am->getName() );

			auto system = _oc.find<sm3::GenericSystem>( os, ObjectCache::Default );
			system->getRtosConfig()->getSchedulables().push_back_unsafe( isrScheduler );
		}
	}
}

void Converter::work( const am200::model::TaskScheduler_ptr& am,
					  am200::model::TaskScheduler* ) {
	if ( _mode == PreOrder ) {
		auto scheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>( am );
		scheduler->setName( am->getName() );
		_schedulerHierarchy.back()->getSchedulables().push_back_unsafe( scheduler );
		_schedulerHierarchy.push_back( scheduler );

	} else {
		_schedulerHierarchy.pop_back();
	}
}

//void Converter::work( const am200::model::TaskSchedulingAlgorithm_ptr&,
//					  am200::model::TaskSchedulingAlgorithm* ) {
//	if ( _mode == PreOrder ) {
//		auto scheduler = _schedulerHierarchy.back();
//		auto classifierId = scheduler->eClass()->getClassifierID();
//		if ( classifierId == am::ModelPackage::FIXEDPRIORITYPREEMPTIVE ) {
//			scheduler->setType( sm3::SchedulerType::Preemptive );
//			scheduler->setStrategy( sm3::SchedulerStrategy::FixedPriority );
//		} else {
//			/* @todo */
//		}
//	}
//}

void Converter::work( const am200::model::SchedulerAssociation_ptr& am,
					  am200::model::SchedulerAssociation* ) {
	if ( _mode == PreOrder ) {
		auto impactedScheduler = _schedulerHierarchy.back();
		auto newParentScheduler =
			_oc.make<sm3::ModelFactory, sm3::Scheduler>( am->getParent() );
		const auto& oldParentScheduler =
			ecore::as<sm3::Scheduler>( impactedScheduler->eContainer() );

		/* We assume there is only 1 SchedulerAssociation per Scheduler. */
		if ( newParentScheduler ) {
			oldParentScheduler->getSchedulables().remove( impactedScheduler );
			newParentScheduler->getSchedulables().push_back( impactedScheduler );
		}
	}
}

void Converter::work( const am200::model::Semaphore_ptr& am, am200::model::Semaphore* ) {
	if ( _mode == PreOrder ) {
		auto semaphore = _oc.make<sm3::ModelFactory, sm3::Semaphore>( am );
		_model->getSemaphores().push_back_unsafe( semaphore );

		semaphore->setName( am->getName() );
		semaphore->setInitialValue( am->getInitialValue() );
		semaphore->setMaxValue( am->getMaxValue() );
		// ignored: am->getPriorityCeilingProtocol()
	}
}

}  // namespace am200
