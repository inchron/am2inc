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

#include <cmath>  // pow()
#include <memory>
#include <set>

#include <ecore_forward.hpp>
#include <ecorecpp/util/TreeWalker.hpp>

#include <am2inc/Mappings.hpp>
#include <root_forward.hpp>

#include "ObjectCache.h"

/* Requires Application::info(). */
class Application;
class Options;
class QString;

namespace {

/**
 * This is a helper to convert an INCHRON Frequency to a double.
 */
template<class T>
double incFreq2Double( T frequency ) {
	return frequency->getValue() * pow( 10, int( frequency->getUnit() ) * 3 );
};

template<class T>
double amFreq2Double( T f ) {
	/** The off by one of the unit enums results in a factor of 1000. */
	return incFreq2Double( f ) * 1e-3;
};

}  // anonymous namespace

/** This is the base class of all Converters.
 */
class Converter {
protected:
	Converter( Application& );

public:
	/** Amalthea split-models contain one Amalthea object per EResource.
	 * Their content must be merged into a single Amalthea object, which then
	 * can be traversed independent of the given order of the EResources. */
	static ecore::EObject_ptr merge( const ecore::Ptr<ecorecpp::resource::ResourceSet>& );

	static std::unique_ptr<Converter> create( Application&, const ecore::EObject_ptr& );
	static const std::vector<std::string>& getNsURIs();

	virtual ~Converter() = default;
	/* The relevant CLI options are cached so not every derived class needs to
	 * know about the Options class.
	 */
	virtual void setOptions( const Options& );

	enum ResultStatus { Ok, Warning, Error };
	[[nodiscard]] ResultStatus getResultStatus() const { return _resultStatus; }

	/* Emit a warning message and increase the status to Warning.
	 * @note This does only call Application::info(). */
	void warning( const QString& );
	/* Emit an error message and increase the status to Error.
	 * @note This does only call Application::info(). */
	void error( const QString& );
	/* Like error(), but additionally terminate the tree traversal as soon as possible.
	 * @note This does only call Application::info(). */
	void abort( const QString& );

	virtual void clear();
	virtual void convert( const ecore::EObject_ptr& ) = 0;
	virtual void relax();

	[[nodiscard]] const ecore::Ptr<am2inc::Mappings>& getMappings() const {
		return _mappings;
	}
	[[nodiscard]] const root::Root_ptr& getRoot() const { return _root; }

protected:
	using Status = ecorecpp::util::TreeWalker::Status;
	void skipChildren() { _status = Status::SkipChildren; }

	void setName( root::model::CallSequenceItem&, const std::string& );
	void setName( root::model::GraphEntryBase&, const std::string& = std::string() );
	void setName( root::model::SwitchEntry&, const std::string& = std::string() );
	void setName( root::model::ProbabilitySwitchEntry&,
				  const std::string& = std::string() );
	void setName( root::model::ModelObject&, const std::string& = std::string() );

	void addMapping( const std::vector<ecore::EObject_ptr>&,
					 const std::vector<root::Referable_ptr>& );

	void addEvents( const root::model::Process_ptr& );
	void addEvents( const root::model::Function_ptr& );
	void addEvents( const root::model::memory::DataObject_ptr& );

	static bool ucharEquals( char a, char b ) {
		return std::tolower( static_cast<unsigned char>( a ) )
			== std::tolower( static_cast<unsigned char>( b ) );
	}

	static bool equals( const std::string& lhs, const std::string& rhs ) {
		return std::equal( lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), ucharEquals );
	}

	/* Ensure unique names for objects in a container. */
	template<class Container>
	static void uniqueNames( const Container& cont ) {
		std::set<std::string> seenNames;
		for ( const auto& namedObject : cont ) {
			const auto oldName = namedObject->getName();
			auto uniqueName = oldName;
			for ( int count = 0; seenNames.count( uniqueName ) != 0; ++count ) {
				uniqueName = oldName + '_' + std::to_string( count );
			}
			seenNames.insert( uniqueName );
			if ( uniqueName != oldName ) {
				namedObject->setName( uniqueName );
			}
		}
	}

	Application& _application;
	ResultStatus _resultStatus{ ResultStatus::Ok };
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
	std::uint32_t _csiCounter{ 0 };

	/** CallSequences are GraphEntryBases and have a name, too, but they are
	 * created freehanded and deleted again if unused. Hence they use their
	 * own counter. */
	std::uint32_t _geCounter{ 0 };

	/** SwitchEntrys are named locally to their surrounding Switch. Due to
	 * nested switches this is implemented as a stack. */
	std::stack<std::uint32_t> _switchEntryCounter;

	/** This counter is used for various ModelObjects. */
	std::uint32_t _moCounter{ 0 };

	bool _connectionHandlersDefined{ false };

	enum Mode { PreOrder, PostOrder } _mode{ PreOrder };
	Status _status{ Status::Continue };

	bool withMemory() const { return _withMemory; }
	bool withDataFlowConnections() const { return _withDataFlowConnections; }

private:
	bool _withMemory{ true };
	bool _withDataFlowConnections{ false };
};
