/* -*- c++ -*-
 *
 * Converter/mappingModel.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file mappingModel.cpp
 * Groups all code related to Amalthea's HwModel.
 */
#include "../Converter.h"

#include "../AttributeCreator.h"
#include "../StimulusTraits.h"


void Converter::work(const amalthea::model::SchedulerAllocation_ptr& am,
					 amalthea::model::SchedulerAllocation*) {
	if (_mode == PreOrder) {
		auto scheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>(am->getScheduler());
		/* @todo only used for the process of the UserDefinedScheduler.
		 * auto executingCore = _oc.find<sm3::Scheduler>(am->getExecutingPU()); */

		for (auto&& amCore : am->getResponsibility()) {
			auto core = _oc.find<sm3::CpuCore>(amCore, ObjectCache::Default);
			scheduler->getCpuCores().push_back(core);
		}
	}
}

/** RunnableAllocations are ignored because they are not supported by the
 * INCHRON model. During the validation it should be checked, if the existing
 * RunnableAllocations and the TaskAllocations of the Tasks, which call those
 * Runnables, are in sync. Otherwise there will be undefined behaviour.
 */
void Converter::work(const amalthea::model::RunnableAllocation_ptr&,
					 amalthea::model::RunnableAllocation*) {
}

void Converter::work(const amalthea::model::TaskAllocation_ptr& am,
					 amalthea::model::TaskAllocation*) {
	if (_mode == PreOrder) {
		auto task = _oc.find<sm3::Process>(am->getTask(), ObjectCache::Default);
		auto scheduler = _oc.make<sm3::ModelFactory, sm3::Scheduler>(am->getScheduler());
		scheduler->getSchedulables().push_back(task);

		for (auto&& amCore : am->getAffinity()) {
			auto core = _oc.make<sm3::ModelFactory, sm3::CpuCore>(amCore);
			task->getCpuCores().push_back(core);
		}

		if (auto parameters = am->getSchedulingParameters()) {
			int priority = parameters->getPriority();
			task->setPriority(priority);
			/* Other attributes of SchedulingParameters are ignored. */
		}

		/* ParameterExtensions are ignored. */
	}
}
