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

#include <am220/model/ModelItemDispatcher.hpp>
#include <root/model/Model.hpp>
#include <root/Root.hpp>

#include "../Converter.h"

namespace am220 {

class Converter : public ::Converter,
				  public am220::model::ModelItemDispatcher<Converter> {
public:
	Converter( Application& application ) : ::Converter( application ) {}

	void convert( const ecore::EObject_ptr& ) override;
	void relax() override;

	Status preOrder( const ecore::EObject_ptr& );
	Status postOrder( const ecore::EObject_ptr& );

	using ModelItemDispatcher::work;

	/* Amalthea HwModel */
	void work( const am220::model::FrequencyDomain_ptr&, am220::model::FrequencyDomain* );

	/* Hardware model elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.1 */
	void work( const am220::model::HwFeatureCategory_ptr&,
			   am220::model::HwFeatureCategory* );
	void work( const am220::model::HwFeature_ptr&, am220::model::HwFeature* );
	void work( const am220::model::HwStructure_ptr&, am220::model::HwStructure* );
	void work( const am220::model::HwConnection_ptr&, am220::model::HwConnection* );
	void work( const am220::model::HwPort_ptr&, am220::model::HwPort* );

	/* Hardware modules and access elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.3 */
	void work( const am220::model::ProcessingUnit_ptr&, am220::model::ProcessingUnit* );
	void work( const am220::model::Memory_ptr&, am220::model::Memory* );
	void work( const am220::model::Cache_ptr&, am220::model::Cache* );
	void work( const am220::model::ConnectionHandler_ptr&,
			   am220::model::ConnectionHandler* );
	void work( const am220::model::HwAccessElement_ptr&, am220::model::HwAccessElement* );
	void work( const am220::model::HwAccessPath_ptr&, am220::model::HwAccessPath* );

	/* Amalthea StimuliModel */
	void work( const am220::model::ArrivalCurveStimulus_ptr&,
			   am220::model::ArrivalCurveStimulus* );
	void work( const am220::model::CustomStimulus_ptr&, am220::model::CustomStimulus* );
	void work( const am220::model::EventStimulus_ptr&, am220::model::EventStimulus* );
	void work( const am220::model::InterProcessStimulus_ptr&,
			   am220::model::InterProcessStimulus* );
	void work( const am220::model::PeriodicBurstStimulus_ptr&,
			   am220::model::PeriodicBurstStimulus* );
	void work( const am220::model::PeriodicStimulus_ptr&,
			   am220::model::PeriodicStimulus* );
	void work( const am220::model::PeriodicSyntheticStimulus_ptr&,
			   am220::model::PeriodicSyntheticStimulus* );
	void work( const am220::model::RelativePeriodicStimulus_ptr&,
			   am220::model::RelativePeriodicStimulus* );
	void work( const am220::model::SingleStimulus_ptr&, am220::model::SingleStimulus* );
	void work( const am220::model::VariableRateStimulus_ptr&,
			   am220::model::VariableRateStimulus* );

	/* Amalthea SwModel */
	void work( const am220::model::ISR_ptr&, am220::model::ISR* );
	void work( const am220::model::Label_ptr&, am220::model::Label* );
	void work( const am220::model::OsEvent_ptr&, am220::model::OsEvent* );
	void work( const am220::model::Runnable_ptr&, am220::model::Runnable* );
	void work( const am220::model::Task_ptr&, am220::model::Task* );
	void work( const am220::model::ModeLabel_ptr&, am220::model::ModeLabel* );
	void work( const am220::model::EnumMode_ptr&, am220::model::EnumMode* );
	void work( const am220::model::NumericMode_ptr&, am220::model::NumericMode* );
	void work( const am220::model::ModeConditionDisjunction_ptr&,
			   am220::model::ModeConditionDisjunction* );
	void work( const am220::model::ConditionDisjunction_ptr&,
			   am220::model::ConditionDisjunction* );
	void work( const am220::model::LocalModeLabel_ptr&, am220::model::LocalModeLabel* );

	void addStimulus( const am220::model::Process_ptr&, const root::model::Process_ptr& );
	void addEvents( const root::model::Process_ptr& );
	void addEvents( const root::model::Function_ptr& );

	/* Amalthea ActivityGraph and ActivityGraphItems */
	void work( const am220::model::ActivityGraph_ptr&, am220::model::ActivityGraph* );
	void work( const am220::model::ChannelReceive_ptr&, am220::model::ChannelReceive* );
	void work( const am220::model::ChannelSend_ptr&, am220::model::ChannelSend* );
	void work( const am220::model::ClearEvent_ptr&, am220::model::ClearEvent* );
	void work( const am220::model::CustomEventTrigger_ptr&,
			   am220::model::CustomEventTrigger* );
	void work( const am220::model::EnforcedMigration_ptr&,
			   am220::model::EnforcedMigration* );
	void work( const am220::model::ExecutionNeed_ptr&, am220::model::ExecutionNeed* );
	void work( const am220::model::GetResultServerCall_ptr&,
			   am220::model::GetResultServerCall* );
	void work( const am220::model::Group_ptr&, am220::model::Group* );
	void work( const am220::model::InterProcessTrigger_ptr&,
			   am220::model::InterProcessTrigger* );
	void work( const am220::model::LabelAccess_ptr&, am220::model::LabelAccess* );
	void work( const am220::model::ModeLabelAccess_ptr&, am220::model::ModeLabelAccess* );
	void work( const am220::model::Switch_ptr&, am220::model::Switch* );
	void work( const am220::model::SwitchDefault_ptr&, am220::model::SwitchDefault* );
	void work( const am220::model::SwitchEntry_ptr&, am220::model::SwitchEntry* );
	void work( const am220::model::ModeSwitch_ptr&, am220::model::ModeSwitch* );
	void work( const am220::model::ModeSwitchDefault_ptr&,
			   am220::model::ModeSwitchDefault* );
	void work( const am220::model::ModeSwitchEntry_ptr&, am220::model::ModeSwitchEntry* );
	void work( const am220::model::ProbabilitySwitch_ptr&,
			   am220::model::ProbabilitySwitch* );
	void work( const am220::model::ProbabilitySwitchEntry_ptr&,
			   am220::model::ProbabilitySwitchEntry* );
	void work( const am220::model::WhileLoop_ptr&, am220::model::WhileLoop* );
	void work( const am220::model::RunnableCall_ptr&, am220::model::RunnableCall* );
	void work( const am220::model::SchedulePoint_ptr&, am220::model::SchedulePoint* );
	void work( const am220::model::SemaphoreAccess_ptr&, am220::model::SemaphoreAccess* );
	void work( const am220::model::SenderReceiverRead_ptr&,
			   am220::model::SenderReceiverRead* );
	void work( const am220::model::SenderReceiverWrite_ptr&,
			   am220::model::SenderReceiverWrite* );
	void work( const am220::model::SetEvent_ptr&, am220::model::SetEvent* );
	void work( const am220::model::SynchronousServerCall_ptr&,
			   am220::model::SynchronousServerCall* );
	void work( const am220::model::TerminateProcess_ptr&,
			   am220::model::TerminateProcess* );
	void work( const am220::model::Ticks_ptr&, am220::model::Ticks* );
	void work( const am220::model::WaitEvent_ptr&, am220::model::WaitEvent* );

	/* Amalthea osModel */
	void work( const am220::model::OperatingSystem_ptr&, am220::model::OperatingSystem* );
	void work( const am220::model::InterruptController_ptr&,
			   am220::model::InterruptController* );
	void work( const am220::model::TaskScheduler_ptr&, am220::model::TaskScheduler* );
	//	void work( const am220::model::TaskSchedulingAlgorithm_ptr&,
	//			   am220::model::TaskSchedulingAlgorithm* );
	void work( const am220::model::SchedulerAssociation_ptr&,
			   am220::model::SchedulerAssociation* );
	void work( const am220::model::Semaphore_ptr&, am220::model::Semaphore* );

	/* Amalthea mappingModel */
	void work( const am220::model::MappingModel_ptr&, am220::model::MappingModel* );
	void work( const am220::model::MemoryMapping_ptr&, am220::model::MemoryMapping* );
	void work( const am220::model::PhysicalSectionMapping_ptr&,
			   am220::model::PhysicalSectionMapping* );
	void work( const am220::model::RunnableAllocation_ptr&,
			   am220::model::RunnableAllocation* );
	void work( const am220::model::SchedulerAllocation_ptr&,
			   am220::model::SchedulerAllocation* );
	void work( const am220::model::ISRAllocation_ptr&, am220::model::ISRAllocation* );
	void work( const am220::model::TaskAllocation_ptr&, am220::model::TaskAllocation* );

	/* Amalthea eventModel */
	void work( const am220::model::EventSet_ptr&, am220::model::EventSet* );
	void work( const am220::model::ComponentEvent_ptr&, am220::model::ComponentEvent* );
	void work( const am220::model::ProcessEvent_ptr&, am220::model::ProcessEvent* );
	void work( const am220::model::ProcessChainEvent_ptr&,
			   am220::model::ProcessChainEvent* );
	void work( const am220::model::SemaphoreEvent_ptr&, am220::model::SemaphoreEvent* );
	void work( const am220::model::StimulusEvent_ptr&, am220::model::StimulusEvent* );
	void work( const am220::model::ChannelEvent_ptr&, am220::model::ChannelEvent* );
	void work( const am220::model::CustomEvent_ptr&, am220::model::CustomEvent* );
	void work( const am220::model::LabelEvent_ptr&, am220::model::LabelEvent* );
	void work( const am220::model::RunnableEvent_ptr&, am220::model::RunnableEvent* );

	/* Amalthea constraintsModel */
	std::list<am220::model::Event_ptr> getAmaltheaEventSequence(
		const am220::model::AbstractEventChain_ptr& am );
	void work( const am220::model::EventChain_ptr&, am220::model::EventChain* );
	void work( const am220::model::TimingConstraint_ptr&,
			   am220::model::TimingConstraint* );
	void work( const am220::model::AffinityConstraint_ptr&,
			   am220::model::AffinityConstraint* );
	void work( const am220::model::RunnableSequencingConstraint_ptr&,
			   am220::model::RunnableSequencingConstraint* );
	void work( const am220::model::DataAgeConstraint_ptr&,
			   am220::model::DataAgeConstraint* );
	void work( const am220::model::Requirement_ptr&, am220::model::Requirement* );
	void work( const am220::model::DataCoherencyGroup_ptr&,
			   am220::model::DataCoherencyGroup* );
	void work( const am220::model::DataStabilityGroup_ptr&,
			   am220::model::DataStabilityGroup* );
	void work( const am220::model::PhysicalSectionConstraint_ptr&,
			   am220::model::PhysicalSectionConstraint* );

	/* All relaxations, split according to structure. */
	void relaxHardware();
	void relaxIsrSchedulers();
	void relaxRunnables();
	void relaxFreeObjects();

	/* Helper functions used by multiple modules. */
	root::model::ModeGroup_ptr createModeGroup( const am220::model::ModeLabel_ptr& );
	root::model::Counter_ptr createCounter( const am220::model::ModeLabel_ptr& );

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
	root::model::RelationalExpression_ptr createRelationalExpression(
		const ecore::Ptr<C>& );
	root::model::TimeDistribution_ptr createTimeDistribution(
		const am220::model::IDiscreteValueDeviation_ptr& );
};

}  // namespace am220
