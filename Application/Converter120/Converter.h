/* -*- c++ -*-
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#pragma once

#include <list>
#include <stack>

#include <am120/model/ModelItemDispatcher.hpp>
#include <root/model/Model.hpp>
#include <root/Root.hpp>

#include "../Converter.h"

namespace am120 {

class Converter : public ::Converter,
				  public am120::model::ModelItemDispatcher<Converter> {
public:
	Converter() : ::Converter() {}

	void convert( const ecore::EObject_ptr& ) override;
	void relax() override;

	Status preOrder( const ecore::EObject_ptr& );
	Status postOrder( const ecore::EObject_ptr& );

	using ModelItemDispatcher::work;

	/* Amalthea HwModel */
	void work( const am120::model::FrequencyDomain_ptr&, am120::model::FrequencyDomain* );

	/* Hardware model elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.1 */
	void work( const am120::model::HwFeatureCategory_ptr&,
			   am120::model::HwFeatureCategory* );
	void work( const am120::model::HwFeature_ptr&, am120::model::HwFeature* );
	void work( const am120::model::HwStructure_ptr&, am120::model::HwStructure* );
	void work( const am120::model::HwConnection_ptr&, am120::model::HwConnection* );
	void work( const am120::model::HwPort_ptr&, am120::model::HwPort* );

	/* Hardware modules and access elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.3 */
	void work( const am120::model::ProcessingUnit_ptr&, am120::model::ProcessingUnit* );
	void work( const am120::model::Memory_ptr&, am120::model::Memory* );
	void work( const am120::model::Cache_ptr&, am120::model::Cache* );
	void work( const am120::model::ConnectionHandler_ptr&,
			   am120::model::ConnectionHandler* );
	void work( const am120::model::HwAccessElement_ptr&, am120::model::HwAccessElement* );
	void work( const am120::model::HwAccessPath_ptr&, am120::model::HwAccessPath* );

	/* Amalthea StimuliModel */
	void work( const am120::model::ArrivalCurveStimulus_ptr&,
			   am120::model::ArrivalCurveStimulus* );
	void work( const am120::model::CustomStimulus_ptr&, am120::model::CustomStimulus* );
	void work( const am120::model::EventStimulus_ptr&, am120::model::EventStimulus* );
	void work( const am120::model::InterProcessStimulus_ptr&,
			   am120::model::InterProcessStimulus* );
	void work( const am120::model::PeriodicBurstStimulus_ptr&,
			   am120::model::PeriodicBurstStimulus* );
	void work( const am120::model::PeriodicStimulus_ptr&,
			   am120::model::PeriodicStimulus* );
	void work( const am120::model::PeriodicSyntheticStimulus_ptr&,
			   am120::model::PeriodicSyntheticStimulus* );
	void work( const am120::model::RelativePeriodicStimulus_ptr&,
			   am120::model::RelativePeriodicStimulus* );
	void work( const am120::model::SingleStimulus_ptr&, am120::model::SingleStimulus* );
	void work( const am120::model::VariableRateStimulus_ptr&,
			   am120::model::VariableRateStimulus* );

	/* Amalthea SwModel */
	void work( const am120::model::ISR_ptr&, am120::model::ISR* );
	void work( const am120::model::Label_ptr&, am120::model::Label* );
	void work( const am120::model::OsEvent_ptr&, am120::model::OsEvent* );
	void work( const am120::model::Runnable_ptr&, am120::model::Runnable* );
	void work( const am120::model::Task_ptr&, am120::model::Task* );
	void work( const am120::model::ModeLabel_ptr&, am120::model::ModeLabel* );
	void work( const am120::model::EnumMode_ptr&, am120::model::EnumMode* );
	void work( const am120::model::NumericMode_ptr&, am120::model::NumericMode* );
	void work( const am120::model::ModeConditionDisjunction_ptr&,
			   am120::model::ModeConditionDisjunction* );

	void addStimulus( const am120::model::Process_ptr&, const root::model::Process_ptr& );
	void addEvents( const root::model::Process_ptr& );
	void addEvents( const root::model::Function_ptr& );

	/* Amalthea ActivityGraph and ActivityGraphItems */
	void work( const am120::model::ActivityGraph_ptr&, am120::model::ActivityGraph* );
	void work( const am120::model::ChannelReceive_ptr&, am120::model::ChannelReceive* );
	void work( const am120::model::ChannelSend_ptr&, am120::model::ChannelSend* );
	void work( const am120::model::ClearEvent_ptr&, am120::model::ClearEvent* );
	void work( const am120::model::CustomEventTrigger_ptr&,
			   am120::model::CustomEventTrigger* );
	void work( const am120::model::EnforcedMigration_ptr&,
			   am120::model::EnforcedMigration* );
	void work( const am120::model::ExecutionNeed_ptr&, am120::model::ExecutionNeed* );
	void work( const am120::model::GetResultServerCall_ptr&,
			   am120::model::GetResultServerCall* );
	void work( const am120::model::Group_ptr&, am120::model::Group* );
	void work( const am120::model::InterProcessTrigger_ptr&,
			   am120::model::InterProcessTrigger* );
	void work( const am120::model::LabelAccess_ptr&, am120::model::LabelAccess* );
	void work( const am120::model::ModeLabelAccess_ptr&, am120::model::ModeLabelAccess* );
	void work( const am120::model::ModeSwitch_ptr&, am120::model::ModeSwitch* );
	void work( const am120::model::ModeSwitchDefault_ptr&,
			   am120::model::ModeSwitchDefault* );
	void work( const am120::model::ModeSwitchEntry_ptr&, am120::model::ModeSwitchEntry* );
	void work( const am120::model::ProbabilitySwitch_ptr&,
			   am120::model::ProbabilitySwitch* );
	void work( const am120::model::ProbabilitySwitchEntry_ptr&,
			   am120::model::ProbabilitySwitchEntry* );
	void work( const am120::model::WhileLoop_ptr&, am120::model::WhileLoop* );
	void work( const am120::model::RunnableCall_ptr&, am120::model::RunnableCall* );
	void work( const am120::model::SchedulePoint_ptr&, am120::model::SchedulePoint* );
	void work( const am120::model::SemaphoreAccess_ptr&, am120::model::SemaphoreAccess* );
	void work( const am120::model::SenderReceiverRead_ptr&,
			   am120::model::SenderReceiverRead* );
	void work( const am120::model::SenderReceiverWrite_ptr&,
			   am120::model::SenderReceiverWrite* );
	void work( const am120::model::SetEvent_ptr&, am120::model::SetEvent* );
	void work( const am120::model::SynchronousServerCall_ptr&,
			   am120::model::SynchronousServerCall* );
	void work( const am120::model::TerminateProcess_ptr&,
			   am120::model::TerminateProcess* );
	void work( const am120::model::Ticks_ptr&, am120::model::Ticks* );
	void work( const am120::model::WaitEvent_ptr&, am120::model::WaitEvent* );

	/* Amalthea osModel */
	void work( const am120::model::OperatingSystem_ptr&, am120::model::OperatingSystem* );
	void work( const am120::model::InterruptController_ptr&,
			   am120::model::InterruptController* );
	void work( const am120::model::TaskScheduler_ptr&, am120::model::TaskScheduler* );
	void work( const am120::model::TaskSchedulingAlgorithm_ptr&,
			   am120::model::TaskSchedulingAlgorithm* );
	void work( const am120::model::SchedulerAssociation_ptr&,
			   am120::model::SchedulerAssociation* );
	void work( const am120::model::Semaphore_ptr&, am120::model::Semaphore* );

	/* Amalthea mappingModel */
	void work( const am120::model::MappingModel_ptr&, am120::model::MappingModel* );
	void work( const am120::model::MemoryMapping_ptr&, am120::model::MemoryMapping* );
	void work( const am120::model::PhysicalSectionMapping_ptr&,
			   am120::model::PhysicalSectionMapping* );
	void work( const am120::model::RunnableAllocation_ptr&,
			   am120::model::RunnableAllocation* );
	void work( const am120::model::SchedulerAllocation_ptr&,
			   am120::model::SchedulerAllocation* );
	void work( const am120::model::ISRAllocation_ptr&, am120::model::ISRAllocation* );
	void work( const am120::model::TaskAllocation_ptr&, am120::model::TaskAllocation* );

	/* Amalthea eventModel */
	void work( const am120::model::EventSet_ptr&, am120::model::EventSet* );
	void work( const am120::model::ComponentEvent_ptr&, am120::model::ComponentEvent* );
	void work( const am120::model::ProcessEvent_ptr&, am120::model::ProcessEvent* );
	void work( const am120::model::ProcessChainEvent_ptr&,
			   am120::model::ProcessChainEvent* );
	void work( const am120::model::SemaphoreEvent_ptr&, am120::model::SemaphoreEvent* );
	void work( const am120::model::StimulusEvent_ptr&, am120::model::StimulusEvent* );
	void work( const am120::model::ChannelEvent_ptr&, am120::model::ChannelEvent* );
	void work( const am120::model::CustomEvent_ptr&, am120::model::CustomEvent* );
	void work( const am120::model::LabelEvent_ptr&, am120::model::LabelEvent* );
	void work( const am120::model::RunnableEvent_ptr&, am120::model::RunnableEvent* );

	/* Amalthea constraintsModel */
	std::list<am120::model::Event_ptr> getAmaltheaEventSequence(
		const am120::model::AbstractEventChain_ptr& am );
	void work( const am120::model::EventChain_ptr&, am120::model::EventChain* );
	void work( const am120::model::TimingConstraint_ptr&,
			   am120::model::TimingConstraint* );
	void work( const am120::model::AffinityConstraint_ptr&,
			   am120::model::AffinityConstraint* );
	void work( const am120::model::RunnableSequencingConstraint_ptr&,
			   am120::model::RunnableSequencingConstraint* );
	void work( const am120::model::DataAgeConstraint_ptr&,
			   am120::model::DataAgeConstraint* );
	void work( const am120::model::Requirement_ptr&, am120::model::Requirement* );
	void work( const am120::model::DataCoherencyGroup_ptr&,
			   am120::model::DataCoherencyGroup* );
	void work( const am120::model::DataStabilityGroup_ptr&,
			   am120::model::DataStabilityGroup* );
	void work( const am120::model::PhysicalSectionConstraint_ptr&,
			   am120::model::PhysicalSectionConstraint* );

	/* All relaxations, split according to structure. */
	void relaxHardware();
	void relaxIsrSchedulers();
	void relaxRunnables();
	void relaxFreeObjects();

	/* Helper functions used by multiple modules. */
	static root::model::ModeGroup_ptr createModeGroup(
		ObjectCache&, const am120::model::ModeLabel_ptr& );
	static root::model::Counter_ptr createCounter( ObjectCache&,
												   const am120::model::ModeLabel_ptr& );
	static root::model::RelationalExpression_ptr createRelationalExpression(
		ObjectCache& oc, const am120::model::ModeCondition_ptr& );
};

}  // namespace am120
