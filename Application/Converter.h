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

	/* Amalthea SwModel */
	void work(const amalthea::model::Task_ptr&, amalthea::model::Task*);

private:
	enum Mode { PreOrder, PostOrder } _mode{PreOrder};
	Utils::EmfTreeWalker::Status _status{Utils::EmfTreeWalker::Status::Continue};

	ObjectCache _oc;

	ecore::Ptr<am2inc::Mappings> _mappings;
	ecore::Ptr<Projects::Project> _project;
	ecore::Ptr<root::model::Model> _model;
	ecore::Ptr<root::model::Clock> _idealClock;
};
