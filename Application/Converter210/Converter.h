/* -*- c++ -*-
 *
 * Copyright (c) 2024 INCHRON AG <info@inchron.com>
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

#include <am210/model/ModelItemDispatcher.hpp>
#include <root/model/Model.hpp>
#include <root/Root.hpp>

#include "../Converter.h"

namespace am210 {

class Converter : public ::Converter,
				  public am210::model::ModelItemDispatcher<Converter> {
public:
	Converter() : ::Converter() {}

	void convert( const ecore::EObject_ptr& ) override;
	void relax() override;

	Status preOrder( const ecore::EObject_ptr& );
	Status postOrder( const ecore::EObject_ptr& );

	using ModelItemDispatcher::work;

	/* Amalthea HwModel */
	void work( const am210::model::FrequencyDomain_ptr&, am210::model::FrequencyDomain* );

	/* Hardware model elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.1 */
	void work( const am210::model::HwFeatureCategory_ptr&,
			   am210::model::HwFeatureCategory* );
	void work( const am210::model::HwFeature_ptr&, am210::model::HwFeature* );
	void work( const am210::model::HwStructure_ptr&, am210::model::HwStructure* );
	void work( const am210::model::HwConnection_ptr&, am210::model::HwConnection* );
	void work( const am210::model::HwPort_ptr&, am210::model::HwPort* );

	/* Hardware modules and access elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.3 */
	void work( const am210::model::ProcessingUnit_ptr&, am210::model::ProcessingUnit* );
	void work( const am210::model::Memory_ptr&, am210::model::Memory* );
	void work( const am210::model::Cache_ptr&, am210::model::Cache* );
	void work( const am210::model::ConnectionHandler_ptr&,
			   am210::model::ConnectionHandler* );
	void work( const am210::model::HwAccessElement_ptr&, am210::model::HwAccessElement* );
	void work( const am210::model::HwAccessPath_ptr&, am210::model::HwAccessPath* );

	/* Amalthea StimuliModel */
	void work( const am210::model::ArrivalCurveStimulus_ptr&,
			   am210::model::ArrivalCurveStimulus* );
	void work( const am210::model::CustomStimulus_ptr&, am210::model::CustomStimulus* );
	void work( const am210::model::EventStimulus_ptr&, am210::model::EventStimulus* );
	void work( const am210::model::InterProcessStimulus_ptr&,
			   am210::model::InterProcessStimulus* );
	void work( const am210::model::PeriodicBurstStimulus_ptr&,
			   am210::model::PeriodicBurstStimulus* );
	void work( const am210::model::PeriodicStimulus_ptr&,
			   am210::model::PeriodicStimulus* );
	void work( const am210::model::PeriodicSyntheticStimulus_ptr&,
			   am210::model::PeriodicSyntheticStimulus* );
	void work( const am210::model::RelativePeriodicStimulus_ptr&,
			   am210::model::RelativePeriodicStimulus* );
	void work( const am210::model::SingleStimulus_ptr&, am210::model::SingleStimulus* );
	void work( const am210::model::VariableRateStimulus_ptr&,
			   am210::model::VariableRateStimulus* );

	/* Amalthea SwModel */
	void work( const am210::model::ISR_ptr&, am210::model::ISR* );
	void work( const am210::model::Label_ptr&, am210::model::Label* );
	void work( const am210::model::OsEvent_ptr&, am210::model::OsEvent* );
	void work( const am210::model::Runnable_ptr&, am210::model::Runnable* );
	void work( const am210::model::Task_ptr&, am210::model::Task* );
	void work( const am210::model::ModeLabel_ptr&, am210::model::ModeLabel* );
	void work( const am210::model::EnumMode_ptr&, am210::model::EnumMode* );
	void work( const am210::model::NumericMode_ptr&, am210::model::NumericMode* );
	void work( const am210::model::ModeConditionDisjunction_ptr&,
			   am210::model::ModeConditionDisjunction* );
	void work( const am210::model::LocalModeLabel_ptr&, am210::model::LocalModeLabel* );

	void addStimulus( const am210::model::Process_ptr&, const root::model::Process_ptr& );
	void addEvents( const root::model::Process_ptr& );
	void addEvents( const root::model::Function_ptr& );

	/* Amalthea ActivityGraph and ActivityGraphItems */
	void work( const am210::model::ActivityGraph_ptr&, am210::model::ActivityGraph* );
	void work( const am210::model::ChannelReceive_ptr&, am210::model::ChannelReceive* );
	void work( const am210::model::ChannelSend_ptr&, am210::model::ChannelSend* );
	void work( const am210::model::ClearEvent_ptr&, am210::model::ClearEvent* );
	void work( const am210::model::CustomEventTrigger_ptr&,
			   am210::model::CustomEventTrigger* );
	void work( const am210::model::EnforcedMigration_ptr&,
			   am210::model::EnforcedMigration* );
	void work( const am210::model::ExecutionNeed_ptr&, am210::model::ExecutionNeed* );
	void work( const am210::model::GetResultServerCall_ptr&,
			   am210::model::GetResultServerCall* );
	void work( const am210::model::Group_ptr&, am210::model::Group* );
	void work( const am210::model::InterProcessTrigger_ptr&,
			   am210::model::InterProcessTrigger* );
	void work( const am210::model::LabelAccess_ptr&, am210::model::LabelAccess* );
	void work( const am210::model::ModeLabelAccess_ptr&, am210::model::ModeLabelAccess* );
	void work( const am210::model::ModeSwitch_ptr&, am210::model::ModeSwitch* );
	void work( const am210::model::ModeSwitchDefault_ptr&,
			   am210::model::ModeSwitchDefault* );
	void work( const am210::model::ModeSwitchEntry_ptr&, am210::model::ModeSwitchEntry* );
	void work( const am210::model::ProbabilitySwitch_ptr&,
			   am210::model::ProbabilitySwitch* );
	void work( const am210::model::ProbabilitySwitchEntry_ptr&,
			   am210::model::ProbabilitySwitchEntry* );
	void work( const am210::model::WhileLoop_ptr&, am210::model::WhileLoop* );
	void work( const am210::model::RunnableCall_ptr&, am210::model::RunnableCall* );
	void work( const am210::model::SchedulePoint_ptr&, am210::model::SchedulePoint* );
	void work( const am210::model::SemaphoreAccess_ptr&, am210::model::SemaphoreAccess* );
	void work( const am210::model::SenderReceiverRead_ptr&,
			   am210::model::SenderReceiverRead* );
	void work( const am210::model::SenderReceiverWrite_ptr&,
			   am210::model::SenderReceiverWrite* );
	void work( const am210::model::SetEvent_ptr&, am210::model::SetEvent* );
	void work( const am210::model::SynchronousServerCall_ptr&,
			   am210::model::SynchronousServerCall* );
	void work( const am210::model::TerminateProcess_ptr&,
			   am210::model::TerminateProcess* );
	void work( const am210::model::Ticks_ptr&, am210::model::Ticks* );
	void work( const am210::model::WaitEvent_ptr&, am210::model::WaitEvent* );

	/* Amalthea osModel */
	void work( const am210::model::OperatingSystem_ptr&, am210::model::OperatingSystem* );
	void work( const am210::model::InterruptController_ptr&,
			   am210::model::InterruptController* );
	void work( const am210::model::TaskScheduler_ptr&, am210::model::TaskScheduler* );
	//	void work( const am210::model::TaskSchedulingAlgorithm_ptr&,
	//			   am210::model::TaskSchedulingAlgorithm* );
	void work( const am210::model::SchedulerAssociation_ptr&,
			   am210::model::SchedulerAssociation* );
	void work( const am210::model::Semaphore_ptr&, am210::model::Semaphore* );

	/* Amalthea mappingModel */
	void work( const am210::model::MappingModel_ptr&, am210::model::MappingModel* );
	void work( const am210::model::MemoryMapping_ptr&, am210::model::MemoryMapping* );
	void work( const am210::model::PhysicalSectionMapping_ptr&,
			   am210::model::PhysicalSectionMapping* );
	void work( const am210::model::RunnableAllocation_ptr&,
			   am210::model::RunnableAllocation* );
	void work( const am210::model::SchedulerAllocation_ptr&,
			   am210::model::SchedulerAllocation* );
	void work( const am210::model::ISRAllocation_ptr&, am210::model::ISRAllocation* );
	void work( const am210::model::TaskAllocation_ptr&, am210::model::TaskAllocation* );

	/* Amalthea eventModel */
	void work( const am210::model::EventSet_ptr&, am210::model::EventSet* );
	void work( const am210::model::ComponentEvent_ptr&, am210::model::ComponentEvent* );
	void work( const am210::model::ProcessEvent_ptr&, am210::model::ProcessEvent* );
	void work( const am210::model::ProcessChainEvent_ptr&,
			   am210::model::ProcessChainEvent* );
	void work( const am210::model::SemaphoreEvent_ptr&, am210::model::SemaphoreEvent* );
	void work( const am210::model::StimulusEvent_ptr&, am210::model::StimulusEvent* );
	void work( const am210::model::ChannelEvent_ptr&, am210::model::ChannelEvent* );
	void work( const am210::model::CustomEvent_ptr&, am210::model::CustomEvent* );
	void work( const am210::model::LabelEvent_ptr&, am210::model::LabelEvent* );
	void work( const am210::model::RunnableEvent_ptr&, am210::model::RunnableEvent* );

	/* Amalthea constraintsModel */
	std::list<am210::model::Event_ptr> getAmaltheaEventSequence(
		const am210::model::AbstractEventChain_ptr& am );
	void work( const am210::model::EventChain_ptr&, am210::model::EventChain* );
	void work( const am210::model::TimingConstraint_ptr&,
			   am210::model::TimingConstraint* );
	void work( const am210::model::AffinityConstraint_ptr&,
			   am210::model::AffinityConstraint* );
	void work( const am210::model::RunnableSequencingConstraint_ptr&,
			   am210::model::RunnableSequencingConstraint* );
	void work( const am210::model::DataAgeConstraint_ptr&,
			   am210::model::DataAgeConstraint* );
	void work( const am210::model::Requirement_ptr&, am210::model::Requirement* );
	void work( const am210::model::DataCoherencyGroup_ptr&,
			   am210::model::DataCoherencyGroup* );
	void work( const am210::model::DataStabilityGroup_ptr&,
			   am210::model::DataStabilityGroup* );
	void work( const am210::model::PhysicalSectionConstraint_ptr&,
			   am210::model::PhysicalSectionConstraint* );

	/* All relaxations, split according to structure. */
	void relaxHardware();
	void relaxIsrSchedulers();
	void relaxRunnables();
	void relaxFreeObjects();

	/* Helper functions used by multiple modules. */
	static root::model::ModeGroup_ptr createModeGroup(
		ObjectCache&, const am210::model::ModeLabel_ptr& );
	static root::model::Counter_ptr createCounter( ObjectCache&,
												   const am210::model::ModeLabel_ptr& );
	static root::model::RelationalExpression_ptr createRelationalExpression(
		ObjectCache& oc, const am210::model::ModeCondition_ptr& );
};

}  // namespace am210
