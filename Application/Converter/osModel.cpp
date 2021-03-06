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
		_model->getSystems().push_back(system);

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

void Converter::work(const amalthea::model::TaskScheduler_ptr& am,
					 amalthea::model::TaskScheduler*) {
	if (_mode == PreOrder) {
		auto scheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>(am);
		scheduler->setName(am->getName());
		_schedulerHierarchy.back()->getSchedulables().push_back(scheduler);
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
		if (parentScheduler)
			parentScheduler->getSchedulables().push_back(impactedScheduler);
	}
}

void Converter::work(const amalthea::model::Semaphore_ptr& am, amalthea::model::Semaphore*) {
	if (_mode == PreOrder) {
		auto semaphore = _oc.make<sm3::ModelFactory, sm3::Semaphore>(am);
		_model->getSemaphores().push_back(semaphore);

		semaphore->setName(am->getName());
		semaphore->setInitialValue(am->getInitialValue());
		semaphore->setMaxValue(am->getMaxValue());
		// ignored: am->getPriorityCeilingProtocol()
	}
}
