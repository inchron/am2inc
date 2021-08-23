/* -*- c++ -*-
 *
 * Copyright (c) 2020-2021 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#pragma once

#include <stack>

#include <ecorecpp/util/TreeWalker.hpp>

#include <amalthea/model/ModelItemDispatcher.hpp>

#include <am2inc/Mappings.hpp>
#include <root/Root.hpp>
#include <root/model/Model.hpp>

#include "ObjectCache.h"


class Converter : public amalthea::model::ModelItemDispatcher<Converter> {
public:
	Converter();

	void clear();
	void convert(const amalthea::model::Amalthea_ptr&);
	void relax();

	const ecore::Ptr<am2inc::Mappings>& getMappings() const { return _mappings; }
	const ecore::Ptr<root::Root>& getRoot() const { return _root; }

	using Status = ecorecpp::util::TreeWalker::Status;
	Status preOrder(const ecore::EObject_ptr&);
	Status postOrder(const ecore::EObject_ptr&);
	void skipChildren();

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
	void work(const amalthea::model::ModeLabel_ptr&, amalthea::model::ModeLabel*);
	void work(const amalthea::model::EnumMode_ptr&, amalthea::model::EnumMode*);
	void work(const amalthea::model::NumericMode_ptr&, amalthea::model::NumericMode*);
	void work(const amalthea::model::ModeConditionDisjunction_ptr&, amalthea::model::ModeConditionDisjunction*);

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
	void work(const amalthea::model::ModeSwitchDefault_ptr&, amalthea::model::ModeSwitchDefault*);
	void work(const amalthea::model::ModeSwitchEntry_ptr&, amalthea::model::ModeSwitchEntry*);
	void work(const amalthea::model::ProbabilitySwitch_ptr&, amalthea::model::ProbabilitySwitch*);
	void work(const amalthea::model::ProbabilitySwitchEntry_ptr&, amalthea::model::ProbabilitySwitchEntry*);
	void work(const amalthea::model::WhileLoop_ptr&, amalthea::model::WhileLoop*);
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
	void work(const amalthea::model::InterruptController_ptr&, amalthea::model::InterruptController*);
	void work(const amalthea::model::TaskScheduler_ptr&, amalthea::model::TaskScheduler*);
	void work(const amalthea::model::TaskSchedulingAlgorithm_ptr&, amalthea::model::TaskSchedulingAlgorithm*);
	void work(const amalthea::model::SchedulerAssociation_ptr&, amalthea::model::SchedulerAssociation*);
	void work(const amalthea::model::Semaphore_ptr&, amalthea::model::Semaphore*);

	/* Amalthea mappingModel */
	void work(const amalthea::model::MappingModel_ptr&, amalthea::model::MappingModel*);
	void work(const amalthea::model::MemoryMapping_ptr&, amalthea::model::MemoryMapping*);
	void work(const amalthea::model::PhysicalSectionMapping_ptr&, amalthea::model::PhysicalSectionMapping*);
	void work(const amalthea::model::RunnableAllocation_ptr&, amalthea::model::RunnableAllocation*);
	void work(const amalthea::model::SchedulerAllocation_ptr&, amalthea::model::SchedulerAllocation*);
	void work(const amalthea::model::ISRAllocation_ptr&, amalthea::model::ISRAllocation*);
	void work(const amalthea::model::TaskAllocation_ptr&, amalthea::model::TaskAllocation*);


	/* All relaxations, split according to structure. */
	void relaxHardware();
	void relaxIsrSchedulers();
	void relaxRunnables();
	void relaxFreeObjects();

	void setName(root::model::CallSequenceItem&, const std::string&);
	void setName(root::model::GraphEntryBase&, const std::string& = std::string());
	void setName(root::model::ModeSwitchEntry&, const std::string& = std::string());
	void setName(root::model::ProbabilitySwitchEntry&, const std::string& = std::string());
	void setName(root::model::ModelObject&, const std::string& = std::string());

	/* Helper functions used by multiple modules. */
	static root::model::ModeGroup_ptr createModeGroup(ObjectCache&, const amalthea::model::ModeLabel_ptr&);
	static root::model::Counter_ptr createCounter(ObjectCache&, const amalthea::model::ModeLabel_ptr&);
	static root::model::RelationalExpression_ptr createRelationalExpression(ObjectCache& oc, const amalthea::model::ModeCondition_ptr&);

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

	/** See work(const am::ActivityGraph_ptr&, ...) for an explanation of
	 * _graphEntries and _callSequence. */
	std::deque<root::model::GraphEntryBase_ptr> _graphEntries;
	/** See work(const am::ActivityGraph_ptr&, ...) for an explanation of
	 * _graphEntries and _callSequence. */
	ecore::Ptr<root::model::CallSequence> _callSequence;

	/** CallSequenceItems have a name, which is suffixed with this counter. */
	std::uint32_t _csiCounter{0};

	/** CallSequences are GraphEntryBases and have a name, too, but they are
	 * created freehanded and deleted again if unused. Hence they use their
	 * own counter. */
	std::uint32_t _geCounter{0};

	/** ModeSwitchEntrys and ProbablitiySwitchEntrys are named locally to their
	 * surrounding ModeSwitch resp. ProbabilitySwitch. Due to nested
	 * switches this is implemented as a stack. */
	std::stack<std::uint32_t> _mseCounter;

	/** This counter is used for various ModelObjects. */
	std::uint32_t _moCounter{0};

	bool _connectionHandlersDefined{false};
};
