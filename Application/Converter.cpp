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
#include "Converter.h"

#include <Mapping/am2inc.hpp>

#include <ecore/EClass.hpp>

#include <am120/model/ModelPackage.hpp>

#include "AttributeCreator.h"
#include "Converter120/Converter.h"

std::unique_ptr<Converter> Converter::create(
	const ecore::EObject_ptr& potentialAmaltheaObject ) {
	const auto eClass = potentialAmaltheaObject->eClass();
	const auto ePkg = eClass->getEPackage();

	if ( ePkg == am120::model::ModelPackage::_instance() )
		return std::make_unique<am120::Converter>();

	return {};
}

/** Clear the internal state.
 *
 * For an unknown reason the ObjectCache blocks the serialization of the
 * contained EObjects.
 */
void Converter::clear() { _oc.clear(); }

void Converter::relax() {}

Converter::Converter() {
	_mappings = am2inc::create<am2inc::Mappings>();

	_root = root::create<root::Root>();
	_model = sm3::create<sm3::Model>();
	_model->setName( "New Project" );
	_root->setModel( _model );

	{
		auto scenario = sm3::stimulation::create<sm3::stimulation::StimulationScenario>();
		scenario->setName( "DefaultScenario" );
		_model->getScenarios().push_back( scenario );
		_model->setDefaultScenario( scenario );
	}

	{
		auto clock = sm3::create<sm3::Clock>();
		clock->setName( "IdealClock" );
		clock->setPeriod( sm3::create<sm3::Time>() );
		clock->getPeriod()->setValue( 1 );
		clock->getPeriod()->setUnit( sm3::TimeUnit::ns );
		clock->setRange( sm3::create<sm3::Time>() );
		clock->getRange()->setValue( 1 );
		clock->getRange()->setUnit( sm3::TimeUnit::s );
		clock->setStartValue( sm3::create<sm3::Time>() );
		clock->setStartTimeMin( sm3::create<sm3::Time>() );
		clock->setStartTimeMax( sm3::create<sm3::Time>() );
		clock->setStartTimeFixed( sm3::create<sm3::Time>() );
		_model->getClocks().push_back( clock );
		_idealClock = clock;
	}
}

/** Set an automatic name for a CallSequenceItem.
 *
 * The name often contains useful information about another object used by the
 * CallSequenceItem.
 */
void Converter::setName( root::model::CallSequenceItem& csi, const std::string& name ) {
	csi.setName( name + "_" + std::to_string( _csiCounter++ ) );
}

/** Set an automatic name for a GraphEntry.
 *
 * The class name of the GraphEntry object is used, if no other name is given.
 */
void Converter::setName( root::model::GraphEntryBase& ge, const std::string& nameIn ) {
	auto name = nameIn.empty() ? ge.eClass()->getName() : nameIn;
	ge.setName( name + "_" + std::to_string( _geCounter++ ) );
}

/** Set an automatic name for a ModeSwitchEntry.
 *
 * The class name of the GraphEntry object is used, if no other name is given.
 */
void Converter::setName( root::model::SwitchEntry& switchEntry,
						 const std::string& nameIn ) {
	auto name = nameIn.empty() ? switchEntry.eClass()->getName() : nameIn;
	switchEntry.setName( name + "_" + std::to_string( _switchEntryCounter.top()++ ) );
}

/** Set an automatic name for a ModeSwitchEntry.
 *
 * The class name of the GraphEntry object is used, if no other name is given.
 */
void Converter::setName( root::model::ProbabilitySwitchEntry& pse,
						 const std::string& nameIn ) {
	auto name = nameIn.empty() ? pse.eClass()->getName() : nameIn;
	pse.setName( name + "_" + std::to_string( _switchEntryCounter.top()++ ) );
}

/** Set an automatic name for a ModelObject.
 *
 * The concrete class name of the ModelObject object is used, if no other name
 * is given.
 */
void Converter::setName( root::model::ModelObject& mo, const std::string& nameIn ) {
	auto name = nameIn.empty() ? mo.eClass()->getName() : nameIn;
	mo.setName( name + "_" + std::to_string( _moCounter++ ) );
}

void Converter::addMapping( const std::vector<ecore::EObject_ptr>& am,
							const std::vector<root::Referable_ptr>& inc ) {
	auto mapping = am2inc::create<am2inc::Mapping>();
	for ( auto&& a : am )
		mapping->getAmalthea().push_back_unsafe( a );
	for ( auto&& i : inc )
		mapping->getInchron().push_back_unsafe( i );
	_mappings->getMappings().push_back_unsafe( mapping );
}
