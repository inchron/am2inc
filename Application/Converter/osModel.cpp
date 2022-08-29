/* -*- c++ -*-
 *
 * Converter/osModel.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file osModel.cpp
 * Groups all code related to Amalthea's OsModel.
 */
#include "../Converter.h"

#include "../AttributeCreator.h"
#include "../StimulusTraits.h"


void Converter::work(const amalthea::model::OperatingSystem_ptr& am,
					 amalthea::model::OperatingSystem*) {
	if (_mode == PreOrder) {
		auto system = _oc.make<sm3::ModelFactory, sm3::GenericSystem>(am);
		system->setName(am->getName());
		_model->getSystems().push_back_unsafe(system);

		auto isrScheduler = ecore::as<sm3::Scheduler>(
			system->getRtosConfig()->getSchedulables().get(0));
		assert(isrScheduler);
		_schedulerHierarchy.push_back(isrScheduler);
		isrScheduler->getSchedulables().clear();

	} else {
		_schedulerHierarchy.pop_back();
		assert(_schedulerHierarchy.empty());
	}
}

/** All InterruptController instances are to the RtosConfig of the current
 * OperatingSystem. In a later phase the will be unified to a single top level
 * Scheduler.
 */
void Converter::work(const amalthea::model::InterruptController_ptr& am,
					 amalthea::model::InterruptController*) {
	if (_mode == PreOrder) {
		if (auto os = ecore::as<amalthea::model::OperatingSystem>(am->eContainer())) {
			auto isrScheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>(am);
			isrScheduler->setName(am->getName());

			auto system = _oc.find<sm3::GenericSystem>(os, ObjectCache::Default);
			system->getRtosConfig()->getSchedulables().push_back_unsafe(isrScheduler);
		}
	}
}

void Converter::work(const amalthea::model::TaskScheduler_ptr& am,
					 amalthea::model::TaskScheduler*) {
	if ( am->getSchedulingAlgorithm()
		 && am->getSchedulingAlgorithm()->eClass()
				== am::ModelPackage::_instance()->getGrouping() ) {
		skipChildren();
		return;
	}

	if (_mode == PreOrder) {
		auto scheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>(am);
		scheduler->setName(am->getName());
		_schedulerHierarchy.back()->getSchedulables().push_back_unsafe(scheduler);
		_schedulerHierarchy.push_back(scheduler);

	} else {
		_schedulerHierarchy.pop_back();
	}
}

void Converter::work(const amalthea::model::TaskSchedulingAlgorithm_ptr&,
					 amalthea::model::TaskSchedulingAlgorithm*) {
	if (_mode == PreOrder) {
		auto scheduler = _schedulerHierarchy.back();
		auto classifierId = scheduler->eClass()->getClassifierID();
		if (classifierId == am::ModelPackage::FIXEDPRIORITYPREEMPTIVE) {
			scheduler->setType(sm3::SchedulerType::Preemptive);
			scheduler->setStrategy(sm3::SchedulerStrategy::FixedPriority);
		} else {
			/* @todo */
		}
	}
}

void Converter::work(const amalthea::model::SchedulerAssociation_ptr& am,
					 amalthea::model::SchedulerAssociation*) {
	if (_mode == PreOrder) {
		auto impactedScheduler = _schedulerHierarchy.back();
		auto parentScheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>(am->getParent());
		/* We assume there is only 1 SchedulerAssociation per Scheduler. */
		if (parentScheduler)
			parentScheduler->getSchedulables().push_back_unsafe(impactedScheduler);
	}
}

void Converter::work(const amalthea::model::Semaphore_ptr& am, amalthea::model::Semaphore*) {
	if (_mode == PreOrder) {
		auto semaphore = _oc.make<sm3::ModelFactory, sm3::Semaphore>(am);
		_model->getSemaphores().push_back_unsafe(semaphore);

		semaphore->setName(am->getName());
		semaphore->setInitialValue(am->getInitialValue());
		semaphore->setMaxValue(am->getMaxValue());
		// ignored: am->getPriorityCeilingProtocol()
	}
}
