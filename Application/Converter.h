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

#include <memory>

#include <ecore_forward.hpp>
#include <ecorecpp/util/TreeWalker.hpp>

#include <am2inc/Mappings.hpp>
#include <root_forward.hpp>

#include "ObjectCache.h"

/** This is the base class of all Converters.
 */
class Converter {
protected:
	Converter();

public:
	static std::unique_ptr<Converter> create( const ecore::EObject_ptr& );
	static const std::vector<std::string>& getNsURIs();

	virtual ~Converter() = default;

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
};
