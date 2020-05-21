/* -*- c++ -*-
 *
 * Converter.h
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#pragma once

#include <Utils/EmfTreeWalker.h>

#include <amalthea/model/ModelItemDispatcher.hpp>

#include <Projects/Project.h>
#include <am2inc/Mappings.hpp>
#include <root/model/Model.hpp>

#include "ObjectCache.h"


class Converter : public amalthea::model::ModelItemDispatcher<Converter> {
public:

	void clear();
	void convert(const amalthea::model::Amalthea_ptr&);
	void relax();

	const ecore::Ptr<am2inc::Mappings>& getMappings() const { return _mappings; }
	const ecore::Ptr<Projects::Project>& getProject() const { return _project; }

	Utils::EmfTreeWalker::Status preOrder(const ecore::EObject_ptr&);
	Utils::EmfTreeWalker::Status postOrder(const ecore::EObject_ptr&);

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
	void work(const amalthea::model::Task_ptr&, amalthea::model::Task*);
	void work(const amalthea::model::ISR_ptr&, amalthea::model::ISR*);
	void addStimulus(const amalthea::model::Process_ptr&, const root::model::Process_ptr&);
	void addEvents(const root::model::Process_ptr&);

	/* Amalthea osModel */
	void work(const amalthea::model::OperatingSystem_ptr&, amalthea::model::OperatingSystem*);
	void work(const amalthea::model::TaskScheduler_ptr&, amalthea::model::TaskScheduler*);
	void work(const amalthea::model::TaskSchedulingAlgorithm_ptr&, amalthea::model::TaskSchedulingAlgorithm*);
	void work(const amalthea::model::SchedulerAssociation_ptr&, amalthea::model::SchedulerAssociation*);

	/* Amalthea mappingModel */
	void work(const amalthea::model::SchedulerAllocation_ptr&, amalthea::model::SchedulerAllocation*);
	void work(const amalthea::model::RunnableAllocation_ptr&, amalthea::model::RunnableAllocation*);
	void work(const amalthea::model::TaskAllocation_ptr&, amalthea::model::TaskAllocation*);


private:
	enum Mode { PreOrder, PostOrder } _mode{PreOrder};
	Utils::EmfTreeWalker::Status _status{Utils::EmfTreeWalker::Status::Continue};

	ObjectCache _oc;

	ecore::Ptr<am2inc::Mappings> _mappings;
	ecore::Ptr<Projects::Project> _project;
	ecore::Ptr<root::model::Model> _model;
	ecore::Ptr<root::model::Clock> _idealClock;
	std::deque<root::model::Scheduler_ptr> _schedulerHierarchy;
};
