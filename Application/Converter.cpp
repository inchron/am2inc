/* -*- c++ -*-
 *
 * Converter.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#include "Converter.h"

#include "AttributeCreator.h"

/** Clear the internal state.
 *
 * For an unknown reason the ObjectCache blocks the serialization of the
 * contained EObjects.
 */
void Converter::clear() {
	_oc.clear();
}

/** Main entry to the Converter, part of the fixed framework.
 */
void Converter::convert(const am::Amalthea_ptr& am) {
	auto pre  = std::bind(&Converter::preOrder,  this, std::placeholders::_1);
	auto post = std::bind(&Converter::postOrder, this, std::placeholders::_1);

	_mappings = am2inc::create<am2inc::Mappings>();
	_project = Projects::Project::create();
	_model = ecore::as<sm3::Model>(_project->getRoot()->getModel());

	{
		auto clock = sm3::create<sm3::Clock>();
		clock->setName("IdealClock");
		clock->setPeriod(sm3::create<sm3::Time>());
		clock->getPeriod()->setValue(1);
		clock->getPeriod()->setUnit(sm3::TimeUnit::ns);
		clock->setRange(sm3::create<sm3::Time>());
		clock->getRange()->setValue(1);
		clock->getRange()->setUnit(sm3::TimeUnit::s);
		clock->setStartValue(sm3::create<sm3::Time>());
		clock->setStartTimeMin(sm3::create<sm3::Time>());
		clock->setStartTimeMax(sm3::create<sm3::Time>());
		clock->setStartTimeFixed(sm3::create<sm3::Time>());
		_model->getClocks().push_back(clock);
		_idealClock = clock;
	}

	Utils::EmfTreeWalker walker(pre, post);
	walker.traverse(am);
}

Utils::EmfTreeWalker::Status Converter::preOrder(const ecore::EObject_ptr& obj) {
	_status = Utils::EmfTreeWalker::Status::Continue;
	_mode = PreOrder;
	enter(obj);
	return _status;
}

Utils::EmfTreeWalker::Status Converter::postOrder(const ecore::EObject_ptr& obj) {
	_status = Utils::EmfTreeWalker::Status::Continue;
	_mode = PostOrder;
	enter(obj);
	return _status;
}


void Converter::addMapping(const std::vector<am::ReferableBaseObject_ptr>& am,
						   const std::vector<root::Referable_ptr>& inc) {
	auto mapping = am2inc::create<am2inc::Mapping>();
	for (auto&& a : am)
		mapping->getAmalthea().push_back(a);
	for (auto&& i : inc)
		mapping->getInchron().push_back(i);
	_mappings->getMappings().push_back(mapping);
}


/*
 * @see Converter/hwModel.cpp for the conversion of Amalthea's HwModel.
 */



void Converter::work(const am::Task_ptr& task, am::Task*) {
	if (_mode == PreOrder) {
		auto process = _oc.make<sm3::ModelFactory, sm3::Process>(task);
		process->setName(task->getName());
		addMapping({task}, {process});
	}
}
