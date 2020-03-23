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
	void work(const amalthea::model::Memory_ptr&, amalthea::model::Memory*);
	void work(const amalthea::model::HwStructure_ptr&, amalthea::model::HwStructure*);
	void work(const amalthea::model::ProcessingUnit_ptr&, amalthea::model::ProcessingUnit*);
	void work(const amalthea::model::Cache_ptr&, amalthea::model::Cache*);

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
