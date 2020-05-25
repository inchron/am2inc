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
#include "../Diagnostic.h"
#include "../StimulusTraits.h"


void Converter::work(const am::MemoryMapping_ptr& am, am::MemoryMapping*) {
	if (_mode == PreOrder) {
		/* There are 8 concrete types of AbstractMemoryElements. A
		 * MemoryElementTrait would be helpful. */
		if ( am->getAbstractElement()->eClass()->getClassifierID()
			 != am::ModelPackage::LABEL )
			return;

		auto label = _oc.make<sm3m::MemoryFactory, sm3m::DataObject>(am->getAbstractElement());
		auto memory = _oc.make<sm3m::MemoryFactory, sm3m::Memory>(am->getMemory());
		/* ignored: am->getMemoryPositionAddress() */
		label->setMemory(memory);
	}
}

void Converter::work(const am::PhysicalSectionMapping_ptr&, am::PhysicalSectionMapping*) {
	static Diagnostic::NotImplemented<am::PhysicalSectionMapping> message;
}

void Converter::work(const am::SchedulerAllocation_ptr& am, am::SchedulerAllocation*) {
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
void Converter::work(const am::RunnableAllocation_ptr&, am::RunnableAllocation*) {
	static Diagnostic::NotImplemented<am::RunnableAllocation> message;
}

void Converter::work(const am::TaskAllocation_ptr& am, am::TaskAllocation*) {
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
