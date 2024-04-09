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

#include <am200/model/ModelItemDispatcher.hpp>
#include <root/model/Model.hpp>
#include <root/Root.hpp>

#include "../Converter.h"

namespace am200 {

class Converter : public ::Converter,
				  public am200::model::ModelItemDispatcher<Converter> {
public:
	Converter() : ::Converter() {}

	void convert( const ecore::EObject_ptr& ) override;
	void relax() override;

	Status preOrder( const ecore::EObject_ptr& );
	Status postOrder( const ecore::EObject_ptr& );

	using ModelItemDispatcher::work;

	/* Amalthea HwModel */
	void work( const am200::model::FrequencyDomain_ptr&, am200::model::FrequencyDomain* );

	/* Hardware model elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.1 */
	void work( const am200::model::HwFeatureCategory_ptr&,
			   am200::model::HwFeatureCategory* );
	void work( const am200::model::HwFeature_ptr&, am200::model::HwFeature* );
	void work( const am200::model::HwStructure_ptr&, am200::model::HwStructure* );
	void work( const am200::model::HwConnection_ptr&, am200::model::HwConnection* );
	void work( const am200::model::HwPort_ptr&, am200::model::HwPort* );

	/* Hardware modules and access elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.3 */
	void work( const am200::model::ProcessingUnit_ptr&, am200::model::ProcessingUnit* );
	void work( const am200::model::Memory_ptr&, am200::model::Memory* );
	void work( const am200::model::Cache_ptr&, am200::model::Cache* );
	void work( const am200::model::ConnectionHandler_ptr&,
			   am200::model::ConnectionHandler* );
	void work( const am200::model::HwAccessElement_ptr&, am200::model::HwAccessElement* );
	void work( const am200::model::HwAccessPath_ptr&, am200::model::HwAccessPath* );

	/* Amalthea StimuliModel */
	void work( const am200::model::ArrivalCurveStimulus_ptr&,
			   am200::model::ArrivalCurveStimulus* );
	void work( const am200::model::CustomStimulus_ptr&, am200::model::CustomStimulus* );
	void work( const am200::model::EventStimulus_ptr&, am200::model::EventStimulus* );
	void work( const am200::model::InterProcessStimulus_ptr&,
			   am200::model::InterProcessStimulus* );
	void work( const am200::model::PeriodicBurstStimulus_ptr&,
			   am200::model::PeriodicBurstStimulus* );
	void work( const am200::model::PeriodicStimulus_ptr&,
			   am200::model::PeriodicStimulus* );
	void work( const am200::model::PeriodicSyntheticStimulus_ptr&,
			   am200::model::PeriodicSyntheticStimulus* );
	void work( const am200::model::RelativePeriodicStimulus_ptr&,
			   am200::model::RelativePeriodicStimulus* );
	void work( const am200::model::SingleStimulus_ptr&, am200::model::SingleStimulus* );
	void work( const am200::model::VariableRateStimulus_ptr&,
			   am200::model::VariableRateStimulus* );

	/* Amalthea SwModel */
	void work( const am200::model::ISR_ptr&, am200::model::ISR* );
	void work( const am200::model::Label_ptr&, am200::model::Label* );
	void work( const am200::model::OsEvent_ptr&, am200::model::OsEvent* );
	void work( const am200::model::Runnable_ptr&, am200::model::Runnable* );
	void work( const am200::model::Task_ptr&, am200::model::Task* );
	void work( const am200::model::ModeLabel_ptr&, am200::model::ModeLabel* );
	void work( const am200::model::EnumMode_ptr&, am200::model::EnumMode* );
	void work( const am200::model::NumericMode_ptr&, am200::model::NumericMode* );
	void work( const am200::model::ModeConditionDisjunction_ptr&,
			   am200::model::ModeConditionDisjunction* );
	void work( const am200::model::ConditionDisjunction_ptr&,
			   am200::model::ConditionDisjunction* );

	void addStimulus( const am200::model::Process_ptr&, const root::model::Process_ptr& );
	void addEvents( const root::model::Process_ptr& );
	void addEvents( const root::model::Function_ptr& );

	/* Amalthea ActivityGraph and ActivityGraphItems */
	void work( const am200::model::ActivityGraph_ptr&, am200::model::ActivityGraph* );
	void work( const am200::model::ChannelReceive_ptr&, am200::model::ChannelReceive* );
	void work( const am200::model::ChannelSend_ptr&, am200::model::ChannelSend* );
	void work( const am200::model::ClearEvent_ptr&, am200::model::ClearEvent* );
	void work( const am200::model::CustomEventTrigger_ptr&,
			   am200::model::CustomEventTrigger* );
	void work( const am200::model::EnforcedMigration_ptr&,
			   am200::model::EnforcedMigration* );
	void work( const am200::model::ExecutionNeed_ptr&, am200::model::ExecutionNeed* );
	void work( const am200::model::GetResultServerCall_ptr&,
			   am200::model::GetResultServerCall* );
	void work( const am200::model::Group_ptr&, am200::model::Group* );
	void work( const am200::model::InterProcessTrigger_ptr&,
			   am200::model::InterProcessTrigger* );
	void work( const am200::model::LabelAccess_ptr&, am200::model::LabelAccess* );
	void work( const am200::model::ModeLabelAccess_ptr&, am200::model::ModeLabelAccess* );
	void work( const am200::model::Switch_ptr&, am200::model::Switch* );
	void work( const am200::model::SwitchDefault_ptr&, am200::model::SwitchDefault* );
	void work( const am200::model::SwitchEntry_ptr&, am200::model::SwitchEntry* );
	void work( const am200::model::ModeSwitch_ptr&, am200::model::ModeSwitch* );
	void work( const am200::model::ModeSwitchDefault_ptr&,
			   am200::model::ModeSwitchDefault* );
	void work( const am200::model::ModeSwitchEntry_ptr&, am200::model::ModeSwitchEntry* );
	void work( const am200::model::ProbabilitySwitch_ptr&,
			   am200::model::ProbabilitySwitch* );
	void work( const am200::model::ProbabilitySwitchEntry_ptr&,
			   am200::model::ProbabilitySwitchEntry* );
	void work( const am200::model::WhileLoop_ptr&, am200::model::WhileLoop* );
	void work( const am200::model::RunnableCall_ptr&, am200::model::RunnableCall* );
	void work( const am200::model::SchedulePoint_ptr&, am200::model::SchedulePoint* );
	void work( const am200::model::SemaphoreAccess_ptr&, am200::model::SemaphoreAccess* );
	void work( const am200::model::SenderReceiverRead_ptr&,
			   am200::model::SenderReceiverRead* );
	void work( const am200::model::SenderReceiverWrite_ptr&,
			   am200::model::SenderReceiverWrite* );
	void work( const am200::model::SetEvent_ptr&, am200::model::SetEvent* );
	void work( const am200::model::SynchronousServerCall_ptr&,
			   am200::model::SynchronousServerCall* );
	void work( const am200::model::TerminateProcess_ptr&,
			   am200::model::TerminateProcess* );
	void work( const am200::model::Ticks_ptr&, am200::model::Ticks* );
	void work( const am200::model::WaitEvent_ptr&, am200::model::WaitEvent* );

	/* Amalthea osModel */
	void work( const am200::model::OperatingSystem_ptr&, am200::model::OperatingSystem* );
	void work( const am200::model::InterruptController_ptr&,
			   am200::model::InterruptController* );
	void work( const am200::model::TaskScheduler_ptr&, am200::model::TaskScheduler* );
	//	void work( const am200::model::TaskSchedulingAlgorithm_ptr&,
	//			   am200::model::TaskSchedulingAlgorithm* );
	void work( const am200::model::SchedulerAssociation_ptr&,
			   am200::model::SchedulerAssociation* );
	void work( const am200::model::Semaphore_ptr&, am200::model::Semaphore* );

	/* Amalthea mappingModel */
	void work( const am200::model::MappingModel_ptr&, am200::model::MappingModel* );
	void work( const am200::model::MemoryMapping_ptr&, am200::model::MemoryMapping* );
	void work( const am200::model::PhysicalSectionMapping_ptr&,
			   am200::model::PhysicalSectionMapping* );
	void work( const am200::model::RunnableAllocation_ptr&,
			   am200::model::RunnableAllocation* );
	void work( const am200::model::SchedulerAllocation_ptr&,
			   am200::model::SchedulerAllocation* );
	void work( const am200::model::ISRAllocation_ptr&, am200::model::ISRAllocation* );
	void work( const am200::model::TaskAllocation_ptr&, am200::model::TaskAllocation* );

	/* Amalthea eventModel */
	void work( const am200::model::EventSet_ptr&, am200::model::EventSet* );
	void work( const am200::model::ComponentEvent_ptr&, am200::model::ComponentEvent* );
	void work( const am200::model::ProcessEvent_ptr&, am200::model::ProcessEvent* );
	void work( const am200::model::ProcessChainEvent_ptr&,
			   am200::model::ProcessChainEvent* );
	void work( const am200::model::SemaphoreEvent_ptr&, am200::model::SemaphoreEvent* );
	void work( const am200::model::StimulusEvent_ptr&, am200::model::StimulusEvent* );
	void work( const am200::model::ChannelEvent_ptr&, am200::model::ChannelEvent* );
	void work( const am200::model::CustomEvent_ptr&, am200::model::CustomEvent* );
	void work( const am200::model::LabelEvent_ptr&, am200::model::LabelEvent* );
	void work( const am200::model::RunnableEvent_ptr&, am200::model::RunnableEvent* );

	/* Amalthea constraintsModel */
	std::list<am200::model::Event_ptr> getAmaltheaEventSequence(
		const am200::model::AbstractEventChain_ptr& am );
	void work( const am200::model::EventChain_ptr&, am200::model::EventChain* );
	void work( const am200::model::TimingConstraint_ptr&,
			   am200::model::TimingConstraint* );
	void work( const am200::model::AffinityConstraint_ptr&,
			   am200::model::AffinityConstraint* );
	void work( const am200::model::RunnableSequencingConstraint_ptr&,
			   am200::model::RunnableSequencingConstraint* );
	void work( const am200::model::DataAgeConstraint_ptr&,
			   am200::model::DataAgeConstraint* );
	void work( const am200::model::Requirement_ptr&, am200::model::Requirement* );
	void work( const am200::model::DataCoherencyGroup_ptr&,
			   am200::model::DataCoherencyGroup* );
	void work( const am200::model::DataStabilityGroup_ptr&,
			   am200::model::DataStabilityGroup* );
	void work( const am200::model::PhysicalSectionConstraint_ptr&,
			   am200::model::PhysicalSectionConstraint* );

	/* All relaxations, split according to structure. */
	void relaxHardware();
	void relaxIsrSchedulers();
	void relaxRunnables();
	void relaxFreeObjects();

	/* Helper functions used by multiple modules. */
	static root::model::ModeGroup_ptr createModeGroup(
		ObjectCache&, const am200::model::ModeLabel_ptr& );
	static root::model::Counter_ptr createCounter( ObjectCache&,
												   const am200::model::ModeLabel_ptr& );

private:
	template<class C>
	void workSwitch( const ecore::Ptr<C>& );
	template<class C>
	void workSwitchDefault( const ecore::Ptr<C>& );
	template<class C>
	void workSwitchEntry( const ecore::Ptr<C>& );
	template<class C>
	void workConditionDisjunction( const ecore::Ptr<C>& );

	template<class C>
	static root::model::RelationalExpression_ptr createRelationalExpression(
		ObjectCache& oc, const ecore::Ptr<C>& );
};

}  // namespace am200
