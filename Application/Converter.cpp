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
#include "Converter.h"

#include <Mapping/am2inc.hpp>

#include <ecore/EClass.hpp>
#include <ecorecpp/mapping/any.hpp>
#include <ecorecpp/mapping/EList.hpp>
#include <ecorecpp/resource/Resource.hpp>
#include <ecorecpp/resource/ResourceSet.hpp>

#include <am120/model/ModelPackage.hpp>
#include <am200/model/ModelPackage.hpp>
#include <am210/model/ModelPackage.hpp>
#include <am220/model/ModelPackage.hpp>
#include <am320/model/ModelPackage.hpp>

#include "Application.h"
#include "AttributeCreator.h"
#include "Converter120/Converter.h"
#include "Converter200/Converter.h"
#include "Converter210/Converter.h"
#include "Converter220/Converter.h"
#include "Converter320/Converter.h"
#include "Options.h"

namespace em = ecorecpp::mapping;

namespace {

using EList_ptr = em::EList<ecore::EObject_ptr>::ptr_type;

/** Move all containment children from src to dest.
 *
 * @note dest and src need to have the same EClass, or src is a superclass of
 *     dest. Returns true if this is not satisfied.
 */
bool moveContent( const ecore::EObject_ptr& dest, const ecore::EObject_ptr& src ) {
	if ( dest->eClass() != src->eClass()
		 and not src->eClass()->isSuperTypeOf( dest->eClass() ) ) {
		return true;
	}

	/* Recursively traverse references, move all containments. */
	const auto& ereferences = src->eClass()->getEAllReferences();
	for ( const auto& ereference : ereferences ) {
		if ( not ereference->isContainment() or not ereference->isChangeable()
			 or ereference->isDerived() or not src->eIsSet( ereference ) )
			continue;

		auto src_refs = src->eGet( ereference );
		if ( ereference->getUpperBound() != 1 ) {
			const auto& srcs = *em::any::any_cast<EList_ptr>( src_refs );

			auto dest_refs = dest->eGet( ereference );
			auto dests = em::any::any_cast<EList_ptr>( dest_refs );

			for ( const auto& srcObject : srcs ) {
				auto child = em::any::any_cast<ecore::EObject_ptr>( srcObject );
				dests->push_back( child );
			}
		} else if ( auto child = em::any::any_cast<ecore::EObject_ptr>( src_refs ) )
			dest->eSet( ereference, child );
	}

	return false;
}

}  // namespace

/** The Amalthea object of the first EResource is part of this namespace.
 * Check if the Amalthea objects of the other EResources are part of the same
 * namespace and merge their content.
 */
ecore::EObject_ptr Converter::merge(
	const ecore::Ptr<ecorecpp::resource::ResourceSet>& theSet ) {
	ecore::EObject_ptr mainObject;

	auto& allResources = theSet->getResources();
	auto resourceIterator = allResources.begin();
	if ( resourceIterator == allResources.end() )
		return {};

	/* Will be overwritten immediately, but I need it in the outer scope. */
	auto contentIterator = ( *resourceIterator )->getContents()->begin();

	for ( ; resourceIterator != allResources.end(); ++resourceIterator ) {
		auto allContent = ( *resourceIterator )->getContents();
		for ( contentIterator = allContent->begin(); contentIterator != allContent->end();
			  ++contentIterator ) {
			mainObject = *contentIterator;
			if ( mainObject ) {
				++contentIterator;
				break;
			}
		}
		if ( mainObject )
			break;
	}
	if ( not mainObject )
		return {};

	/* Assumption: mainObject is the first content of the first EResource. */

	auto mainClass = mainObject->eClass();

	do {
		/* Continue with the current value of contentIterator. */
		for ( ; contentIterator != ( *resourceIterator )->getContents()->end();
			  ++contentIterator ) {
			if ( moveContent( mainObject, *contentIterator ) )
				throw std::invalid_argument(
					"Split models must use base objects of the same EClass" );
		}

		++resourceIterator;
		if ( resourceIterator != allResources.end() )
			contentIterator = ( *resourceIterator )->getContents()->begin();
	} while ( resourceIterator != allResources.end() );

	return mainObject;
}

std::unique_ptr<Converter> Converter::create(
	Application& application, const ecore::EObject_ptr& potentialAmaltheaObject ) {
	const auto eClass = potentialAmaltheaObject->eClass();
	const auto ePkg = eClass->getEPackage();

	if ( ePkg == am120::model::ModelPackage::_instance() )
		return std::make_unique<am120::Converter>( application );
	if ( ePkg == am200::model::ModelPackage::_instance() )
		return std::make_unique<am200::Converter>( application );
	if ( ePkg == am210::model::ModelPackage::_instance() )
		return std::make_unique<am210::Converter>( application );
	if ( ePkg == am220::model::ModelPackage::_instance() )
		return std::make_unique<am220::Converter>( application );
	if ( ePkg == am320::model::ModelPackage::_instance() )
		return std::make_unique<am320::Converter>( application );

	throw std::invalid_argument( "This AMALTHEA version is not supported" );
	return {};
}

const std::vector<std::string>& Converter::getNsURIs() {
	static std::vector<std::string> s_nsURIs{
		am120::model::ModelPackage::_instance()->getNsURI(),
		am200::model::ModelPackage::_instance()->getNsURI(),
		am210::model::ModelPackage::_instance()->getNsURI(),
		am220::model::ModelPackage::_instance()->getNsURI(),
		/* These models are aliased to am320. */
		"http://app4mc.eclipse.org/amalthea/3.0.0",
		"http://app4mc.eclipse.org/amalthea/3.1.0",
		am320::model::ModelPackage::_instance()->getNsURI(),
		"http://app4mc.eclipse.org/amalthea/3.3.0",
	};

	return s_nsURIs;
}

void Converter::setOptions( const Options& options ) {
	_withMemory = options.withMemory();
	_withDataFlowConnections = options.withDataFlowConnections();
}

void Converter::warning( const QString& msg ) {
	if ( _resultStatus < Warning )
		_resultStatus = Warning;
	_application.info( 1, QStringLiteral( "Warning: " ) + msg );
}

void Converter::error( const QString& msg ) {
	if ( _resultStatus < Error )
		_resultStatus = Error;
	_application.info( 0, QStringLiteral( "Error: " ) + msg );
}

void Converter::abort( const QString& msg ) {
	/* Abort tree traversal. */
	_status = Status::Stop;

	if ( _resultStatus < Error )
		_resultStatus = Error;
	_application.info( 0, msg );
}


/** Clear the internal state.
 *
 * For an unknown reason the ObjectCache blocks the serialization of the
 * contained EObjects.
 */
void Converter::clear() { _oc.clear(); }

void Converter::relax() {}

Converter::Converter( Application& application ) : _application( application ) {
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

/** Add TraceEvents to a Process.
 */
void Converter::addEvents( const root::model::Process_ptr& process ) {
	static const std::vector<std::pair<sm3::TraceEventType, std::string>> s_events = {
		{ sm3::TraceEventType::Activate, "Activate" },
		{ sm3::TraceEventType::Start, "Start" },
		{ sm3::TraceEventType::Terminate, "Terminate" },
		{ sm3::TraceEventType::Block, "Block" },
		{ sm3::TraceEventType::Release, "Release" },
		{ sm3::TraceEventType::Restart, "Restart" },
	};

	const auto count = process->isIsr() ? 3u : 6u;
	for ( auto i = 0u; i < count; ++i ) {
		auto event = sm3::create<sm3::TraceEvent>();
		event->setType( s_events[i].first );
		event->setName( s_events[i].second );
		process->getTraceEvents().push_back_unsafe( event );
	}
}

/** Add TraceEvents to a Function.
 */
void Converter::addEvents( const root::model::Function_ptr& function ) {
	static const std::vector<std::pair<sm3::TraceEventType, std::string>> s_events = {
		{ sm3::TraceEventType::Activate, "Activate" },
		{ sm3::TraceEventType::Entry, "Entry" },
		{ sm3::TraceEventType::Exit, "Exit" },
	};

	/* Runnables now have an Activate event [SUITE3-4813]. */
	for ( const auto& entry : s_events ) {
		auto event = sm3::create<sm3::TraceEvent>();
		event->setType( entry.first );
		event->setName( entry.second );
		function->getTraceEvents().push_back_unsafe( event );
	}
}

/** Add TraceEvents to a DataObject.
 */
void Converter::addEvents( const root::model::memory::DataObject_ptr& dataObject ) {
	static const std::vector<std::pair<sm3::TraceEventType, std::string>> s_events = {
		{ sm3::TraceEventType::Read, "read" },
		{ sm3::TraceEventType::Write, "write" },
	};

	for ( const auto& entry : s_events ) {
		auto event = sm3::create<sm3::TraceEvent>();
		event->setType( entry.first );
		event->setName( entry.second );
		dataObject->getTraceEvents().push_back_unsafe( event );
	}
}
