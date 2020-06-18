/* -*- c++ -*-
 *
 * Converter.h
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#pragma once

#include <ecorecpp/util/TreeWalker.hpp>

#include <amalthea/model/ModelItemDispatcher.hpp>

#include <am2inc/Mappings.hpp>
#include <root/Root.hpp>
#include <root/model/Model.hpp>

#include "ObjectCache.h"


class Converter : public amalthea::model::ModelItemDispatcher<Converter> {
public:

	void clear();
	void convert(const amalthea::model::Amalthea_ptr&);
	void relax();

	const ecore::Ptr<am2inc::Mappings>& getMappings() const { return _mappings; }
	const ecore::Ptr<root::Root>& getRoot() const { return _root; }

	ecorecpp::util::TreeWalker::Status preOrder(const ecore::EObject_ptr&);
	ecorecpp::util::TreeWalker::Status postOrder(const ecore::EObject_ptr&);

	void addMapping(const std::vector<amalthea::model::ReferableBaseObject_ptr>&,
					const std::vector<root::Referable_ptr>&);

	using ModelItemDispatcher::work;

	/* Amalthea HwModel */
	void work(const amalthea::model::FrequencyDomain_ptr&, amalthea::model::FrequencyDomain*);

	/* Hardware model elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.1 */
	void work(const amalthea::model::HwFeatureCategory_ptr&, amalthea::model::HwFeatureCategory*);
	void work(const amalthea::model::HwFeature_ptr&, amalthea::model::HwFeature*);
	void work(const amalthea::model::HwStructure_ptr&, amalthea::model::HwStructure*);
	void work(const amalthea::model::HwConnection_ptr&, amalthea::model::HwConnection*);
	void work(const amalthea::model::HwPort_ptr&, amalthea::model::HwPort*);

	/* Hardware modules and access elements
	 * https://www.eclipse.org/app4mc/help/app4mc-0.9.8/index.html#section3.8.1.3 */
	void work(const amalthea::model::ProcessingUnit_ptr&, amalthea::model::ProcessingUnit*);
	void work(const amalthea::model::Memory_ptr&, amalthea::model::Memory*);
	void work(const amalthea::model::Cache_ptr&, amalthea::model::Cache*);
	void work(const amalthea::model::ConnectionHandler_ptr&, amalthea::model::ConnectionHandler*);
	void work(const amalthea::model::HwAccessElement_ptr&, amalthea::model::HwAccessElement*);
	void work(const amalthea::model::HwAccessPath_ptr&, amalthea::model::HwAccessPath*);

	/* Amalthea StimuliModel */
	void work(const amalthea::model::ArrivalCurveStimulus_ptr&, amalthea::model::ArrivalCurveStimulus*);
	void work(const amalthea::model::CustomStimulus_ptr&, amalthea::model::CustomStimulus*);
	void work(const amalthea::model::EventStimulus_ptr&, amalthea::model::EventStimulus*);
	void work(const amalthea::model::InterProcessStimulus_ptr&, amalthea::model::InterProcessStimulus*);
	void work(const amalthea::model::PeriodicBurstStimulus_ptr&, amalthea::model::PeriodicBurstStimulus*);
	void work(const amalthea::model::PeriodicStimulus_ptr&, amalthea::model::PeriodicStimulus*);
	void work(const amalthea::model::PeriodicSyntheticStimulus_ptr&, amalthea::model::PeriodicSyntheticStimulus*);
	void work(const amalthea::model::RelativePeriodicStimulus_ptr&, amalthea::model::RelativePeriodicStimulus*);
	void work(const amalthea::model::SingleStimulus_ptr&, amalthea::model::SingleStimulus*);
	void work(const amalthea::model::VariableRateStimulus_ptr&, amalthea::model::VariableRateStimulus*);

	/* Amalthea SwModel */
	void work(const amalthea::model::ISR_ptr&, amalthea::model::ISR*);
	void work(const amalthea::model::Label_ptr&, amalthea::model::Label*);
	void work(const amalthea::model::OsEvent_ptr&, amalthea::model::OsEvent*);
	void work(const amalthea::model::Runnable_ptr&, amalthea::model::Runnable*);
	void work(const amalthea::model::Task_ptr&, amalthea::model::Task*);

	void addStimulus(const amalthea::model::Process_ptr&, const root::model::Process_ptr&);
	void addEvents(const root::model::Process_ptr&);
	void addEvents(const root::model::Function_ptr&);

	/* Amalthea ActivityGraph and ActivityGraphItems */
	void work(const amalthea::model::ActivityGraph_ptr&, amalthea::model::ActivityGraph*);
	void work(const amalthea::model::ChannelReceive_ptr&, amalthea::model::ChannelReceive*);
	void work(const amalthea::model::ChannelSend_ptr&, amalthea::model::ChannelSend*);
	void work(const amalthea::model::ClearEvent_ptr&, amalthea::model::ClearEvent*);
	void work(const amalthea::model::CustomEventTrigger_ptr&, amalthea::model::CustomEventTrigger*);
	void work(const amalthea::model::EnforcedMigration_ptr&, amalthea::model::EnforcedMigration*);
	void work(const amalthea::model::ExecutionNeed_ptr&, amalthea::model::ExecutionNeed*);
	void work(const amalthea::model::GetResultServerCall_ptr&, amalthea::model::GetResultServerCall*);
	void work(const amalthea::model::Group_ptr&, amalthea::model::Group*);
	void work(const amalthea::model::InterProcessTrigger_ptr&, amalthea::model::InterProcessTrigger*);
	void work(const amalthea::model::LabelAccess_ptr&, amalthea::model::LabelAccess*);
	void work(const amalthea::model::ModeLabelAccess_ptr&, amalthea::model::ModeLabelAccess*);
	void work(const amalthea::model::ModeSwitch_ptr&, amalthea::model::ModeSwitch*);
	void work(const amalthea::model::ProbabilitySwitch_ptr&, amalthea::model::ProbabilitySwitch*);
	void work(const amalthea::model::RunnableCall_ptr&, amalthea::model::RunnableCall*);
	void work(const amalthea::model::SchedulePoint_ptr&, amalthea::model::SchedulePoint*);
	void work(const amalthea::model::SemaphoreAccess_ptr&, amalthea::model::SemaphoreAccess*);
	void work(const amalthea::model::SenderReceiverRead_ptr&, amalthea::model::SenderReceiverRead*);
	void work(const amalthea::model::SenderReceiverWrite_ptr&, amalthea::model::SenderReceiverWrite*);
	void work(const amalthea::model::SetEvent_ptr&, amalthea::model::SetEvent*);
	void work(const amalthea::model::SynchronousServerCall_ptr&, amalthea::model::SynchronousServerCall*);
	void work(const amalthea::model::TerminateProcess_ptr&, amalthea::model::TerminateProcess*);
	void work(const amalthea::model::Ticks_ptr&, amalthea::model::Ticks*);
	void work(const amalthea::model::WaitEvent_ptr&, amalthea::model::WaitEvent*);

	/* Amalthea osModel */
	void work(const amalthea::model::OperatingSystem_ptr&, amalthea::model::OperatingSystem*);
	void work(const amalthea::model::TaskScheduler_ptr&, amalthea::model::TaskScheduler*);
	void work(const amalthea::model::TaskSchedulingAlgorithm_ptr&, amalthea::model::TaskSchedulingAlgorithm*);
	void work(const amalthea::model::SchedulerAssociation_ptr&, amalthea::model::SchedulerAssociation*);

	/* Amalthea mappingModel */
	void work(const amalthea::model::MemoryMapping_ptr&, amalthea::model::MemoryMapping*);
	void work(const amalthea::model::PhysicalSectionMapping_ptr&, amalthea::model::PhysicalSectionMapping*);
	void work(const amalthea::model::RunnableAllocation_ptr&, amalthea::model::RunnableAllocation*);
	void work(const amalthea::model::SchedulerAllocation_ptr&, amalthea::model::SchedulerAllocation*);
	void work(const amalthea::model::TaskAllocation_ptr&, amalthea::model::TaskAllocation*);


	/* All relaxations, split according to structure. */
	void relaxHardware();
	void relaxIsrSchedulers();
	void relaxFreeObjects();

private:
	enum Mode { PreOrder, PostOrder } _mode{PreOrder};
	ecorecpp::util::TreeWalker::Status _status{ecorecpp::util::TreeWalker::Status::Continue};

	ObjectCache _oc;

	ecore::Ptr<am2inc::Mappings> _mappings;
	ecore::Ptr<root::Root> _root;
	ecore::Ptr<root::model::Model> _model;
	ecore::Ptr<root::model::Clock> _idealClock;
	std::deque<root::model::Scheduler_ptr> _schedulerHierarchy;

	/* Keep track of the current CallGraph elements. */
	ecore::Ptr<root::model::CallGraph> _callGraph;
	std::deque<root::model::GraphEntryBase_ptr> _graphEntries;
	ecore::Ptr<root::model::CallSequence> _callSequence;
};
