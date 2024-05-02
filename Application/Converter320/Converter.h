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

#include <am320/model/ModelItemDispatcher.hpp>
#include <root/model/Model.hpp>
#include <root/Root.hpp>

#include "../Converter.h"

namespace am320 {

class Converter : public ::Converter,
				  public am320::model::ModelItemDispatcher<Converter> {
public:
	Converter( Application& application ) : ::Converter( application ) {}

	void convert( const ecore::EObject_ptr& ) override;
	void relax() override;

	Status preOrder( const ecore::EObject_ptr& );
	Status postOrder( const ecore::EObject_ptr& );

	using ModelItemDispatcher::work;

	/* Amalthea HwModel */
	void work( const am320::model::FrequencyDomain_ptr&, am320::model::FrequencyDomain* );

	/* Hardware model elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.1 */
	void work( const am320::model::HwFeatureCategory_ptr&,
			   am320::model::HwFeatureCategory* );
	void work( const am320::model::HwFeature_ptr&, am320::model::HwFeature* );
	void work( const am320::model::HwStructure_ptr&, am320::model::HwStructure* );
	void work( const am320::model::HwConnection_ptr&, am320::model::HwConnection* );
	void work( const am320::model::HwPort_ptr&, am320::model::HwPort* );

	/* Hardware modules and access elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.3 */
	void work( const am320::model::ProcessingUnit_ptr&, am320::model::ProcessingUnit* );
	void work( const am320::model::Memory_ptr&, am320::model::Memory* );
	void work( const am320::model::Cache_ptr&, am320::model::Cache* );
	void work( const am320::model::ConnectionHandler_ptr&,
			   am320::model::ConnectionHandler* );
	void work( const am320::model::HwAccessElement_ptr&, am320::model::HwAccessElement* );
	void work( const am320::model::HwAccessPath_ptr&, am320::model::HwAccessPath* );

	/* Amalthea StimuliModel */
	void work( const am320::model::ArrivalCurveStimulus_ptr&,
			   am320::model::ArrivalCurveStimulus* );
	void work( const am320::model::CustomStimulus_ptr&, am320::model::CustomStimulus* );
	void work( const am320::model::EventStimulus_ptr&, am320::model::EventStimulus* );
	void work( const am320::model::InterProcessStimulus_ptr&,
			   am320::model::InterProcessStimulus* );
	void work( const am320::model::PeriodicBurstStimulus_ptr&,
			   am320::model::PeriodicBurstStimulus* );
	void work( const am320::model::PeriodicStimulus_ptr&,
			   am320::model::PeriodicStimulus* );
	void work( const am320::model::PeriodicSyntheticStimulus_ptr&,
			   am320::model::PeriodicSyntheticStimulus* );
	void work( const am320::model::RelativePeriodicStimulus_ptr&,
			   am320::model::RelativePeriodicStimulus* );
	void work( const am320::model::SingleStimulus_ptr&, am320::model::SingleStimulus* );
	void work( const am320::model::VariableRateStimulus_ptr&,
			   am320::model::VariableRateStimulus* );

	/* Amalthea SwModel */
	void work( const am320::model::ISR_ptr&, am320::model::ISR* );
	void work( const am320::model::Label_ptr&, am320::model::Label* );
	void work( const am320::model::OsEvent_ptr&, am320::model::OsEvent* );
	void work( const am320::model::Runnable_ptr&, am320::model::Runnable* );
	void work( const am320::model::Task_ptr&, am320::model::Task* );
	void work( const am320::model::ModeLabel_ptr&, am320::model::ModeLabel* );
	void work( const am320::model::EnumMode_ptr&, am320::model::EnumMode* );
	void work( const am320::model::NumericMode_ptr&, am320::model::NumericMode* );
	void work( const am320::model::ConditionDisjunction_ptr&,
			   am320::model::ConditionDisjunction* );
	void work( const am320::model::LocalModeLabel_ptr&, am320::model::LocalModeLabel* );

	void addStimulus( const am320::model::Process_ptr&, const root::model::Process_ptr& );
	void addEvents( const root::model::Process_ptr& );
	void addEvents( const root::model::Function_ptr& );

	/* Amalthea ActivityGraph and ActivityGraphItems */
	void work( const am320::model::ActivityGraph_ptr&, am320::model::ActivityGraph* );
	void work( const am320::model::AsynchronousServerCall_ptr&,
			   am320::model::AsynchronousServerCall* );
	void work( const am320::model::ChannelReceive_ptr&, am320::model::ChannelReceive* );
	void work( const am320::model::ChannelSend_ptr&, am320::model::ChannelSend* );
	void work( const am320::model::ClearEvent_ptr&, am320::model::ClearEvent* );
	void work( const am320::model::CustomEventTrigger_ptr&,
			   am320::model::CustomEventTrigger* );
	void work( const am320::model::EnforcedMigration_ptr&,
			   am320::model::EnforcedMigration* );
	void work( const am320::model::ExecutionNeed_ptr&, am320::model::ExecutionNeed* );
	void work( const am320::model::GetResultServerCall_ptr&,
			   am320::model::GetResultServerCall* );
	void work( const am320::model::Group_ptr&, am320::model::Group* );
	void work( const am320::model::InterProcessTrigger_ptr&,
			   am320::model::InterProcessTrigger* );
	void work( const am320::model::LabelAccess_ptr&, am320::model::LabelAccess* );
	void work( const am320::model::ModeLabelAccess_ptr&, am320::model::ModeLabelAccess* );
	void work( const am320::model::Switch_ptr&, am320::model::Switch* );
	void work( const am320::model::SwitchDefault_ptr&, am320::model::SwitchDefault* );
	void work( const am320::model::SwitchEntry_ptr&, am320::model::SwitchEntry* );
	void work( const am320::model::ProbabilitySwitch_ptr&,
			   am320::model::ProbabilitySwitch* );
	void work( const am320::model::ProbabilitySwitchEntry_ptr&,
			   am320::model::ProbabilitySwitchEntry* );
	void work( const am320::model::WhileLoop_ptr&, am320::model::WhileLoop* );
	void work( const am320::model::RunnableCall_ptr&, am320::model::RunnableCall* );
	void work( const am320::model::SchedulePoint_ptr&, am320::model::SchedulePoint* );
	void work( const am320::model::SemaphoreAccess_ptr&, am320::model::SemaphoreAccess* );
	void work( const am320::model::SenderReceiverRead_ptr&,
			   am320::model::SenderReceiverRead* );
	void work( const am320::model::SenderReceiverWrite_ptr&,
			   am320::model::SenderReceiverWrite* );
	void work( const am320::model::SetEvent_ptr&, am320::model::SetEvent* );
	void work( const am320::model::SynchronousServerCall_ptr&,
			   am320::model::SynchronousServerCall* );
	void work( const am320::model::TerminateProcess_ptr&,
			   am320::model::TerminateProcess* );
	void work( const am320::model::Ticks_ptr&, am320::model::Ticks* );
	void work( const am320::model::WaitEvent_ptr&, am320::model::WaitEvent* );

	/* Amalthea osModel */
	void work( const am320::model::OperatingSystem_ptr&, am320::model::OperatingSystem* );
	void work( const am320::model::InterruptController_ptr&,
			   am320::model::InterruptController* );
	void work( const am320::model::TaskScheduler_ptr&, am320::model::TaskScheduler* );
	//	void work( const am320::model::TaskSchedulingAlgorithm_ptr&,
	//			   am320::model::TaskSchedulingAlgorithm* );
	void work( const am320::model::SchedulerAssociation_ptr&,
			   am320::model::SchedulerAssociation* );
	void work( const am320::model::Semaphore_ptr&, am320::model::Semaphore* );

	/* Amalthea mappingModel */
	void work( const am320::model::MappingModel_ptr&, am320::model::MappingModel* );
	void work( const am320::model::MemoryMapping_ptr&, am320::model::MemoryMapping* );
	void work( const am320::model::PhysicalSectionMapping_ptr&,
			   am320::model::PhysicalSectionMapping* );
	void work( const am320::model::RunnableAllocation_ptr&,
			   am320::model::RunnableAllocation* );
	void work( const am320::model::SchedulerAllocation_ptr&,
			   am320::model::SchedulerAllocation* );
	void work( const am320::model::ISRAllocation_ptr&, am320::model::ISRAllocation* );
	void work( const am320::model::TaskAllocation_ptr&, am320::model::TaskAllocation* );

	/* Amalthea eventModel */
	void work( const am320::model::EventSet_ptr&, am320::model::EventSet* );
	void work( const am320::model::ComponentEvent_ptr&, am320::model::ComponentEvent* );
	void work( const am320::model::ProcessEvent_ptr&, am320::model::ProcessEvent* );
	void work( const am320::model::ProcessChainEvent_ptr&,
			   am320::model::ProcessChainEvent* );
	void work( const am320::model::SemaphoreEvent_ptr&, am320::model::SemaphoreEvent* );
	void work( const am320::model::StimulusEvent_ptr&, am320::model::StimulusEvent* );
	void work( const am320::model::ChannelEvent_ptr&, am320::model::ChannelEvent* );
	void work( const am320::model::CustomEvent_ptr&, am320::model::CustomEvent* );
	void work( const am320::model::LabelEvent_ptr&, am320::model::LabelEvent* );
	void work( const am320::model::RunnableEvent_ptr&, am320::model::RunnableEvent* );

	/* Amalthea constraintsModel */
	std::list<am320::model::Event_ptr> getAmaltheaEventSequence(
		const am320::model::AbstractEventChain_ptr& am );
	void work( const am320::model::EventChain_ptr&, am320::model::EventChain* );
	void work( const am320::model::TimingConstraint_ptr&,
			   am320::model::TimingConstraint* );
	void work( const am320::model::AffinityConstraint_ptr&,
			   am320::model::AffinityConstraint* );
	void work( const am320::model::RunnableSequencingConstraint_ptr&,
			   am320::model::RunnableSequencingConstraint* );
	void work( const am320::model::DataAgeConstraint_ptr&,
			   am320::model::DataAgeConstraint* );
	void work( const am320::model::Requirement_ptr&, am320::model::Requirement* );
	void work( const am320::model::DataCoherencyGroup_ptr&,
			   am320::model::DataCoherencyGroup* );
	void work( const am320::model::DataStabilityGroup_ptr&,
			   am320::model::DataStabilityGroup* );
	void work( const am320::model::PhysicalSectionConstraint_ptr&,
			   am320::model::PhysicalSectionConstraint* );

	/* All relaxations, split according to structure. */
	void relaxHardware();
	void relaxIsrSchedulers();
	void relaxRunnables();
	void relaxFreeObjects();

	/* Helper functions used by multiple modules. */
	root::model::ModeGroup_ptr createModeGroup( const am320::model::ModeLabel_ptr& );
	root::model::Counter_ptr createCounter( const am320::model::ModeLabel_ptr& );

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
		const am320::model::IDiscreteValueDeviation_ptr& );
};

}  // namespace am320
