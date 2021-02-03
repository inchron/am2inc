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

#include <map>

#include <ecore/EObject.hpp>

#include "ModelChecker.h"
#include "CreatorTraits.h"


/** The ObjectCache manages a relation between 1 Amalthea object and up to 4
 * INCHRON objects.
 *
 * The idea is to pass an Amalthea object in and always get the same INCHRON
 * object back. For convenience, the ObjectCache creates the object if it does
 * not yet exist.
 *
 * Note that the ObjectCache uses owning pointers. So before serializing the
 * INCHRON model you should clear the ObjectCache, which will make it easier
 * to detect referenced-only objects, i.e. which are in no containment
 * relation to the rest of the model.
 *
 * Usage:
 \code{cxx}
ObjectCache oc;
auto p = oc.make<root::model::ModelFactory, root::model::Model>();
 \endcode
 */
class ObjectCache {
public:
	enum SubKey { Default = 0, Sub1, Sub2, Sub3,
				  MaxSubKey };
	using Ptr = ecore::Ptr<ecore::EObject>;
	using Key = Ptr;
	using Value = std::array< Ptr, MaxSubKey >;
	using Map = std::map< Key, Value >;

	/** Returns an existing object for the default SubKey or creates one. */
	template<class F, class T>
	ecore::Ptr<T> make(const Ptr& p) { return make<F, T>(p, Default); }

	/** Returns an existing object for the given SubKey or creates one. */
	template<class F, class T>
	ecore::Ptr<T> make(const Ptr& p, SubKey k) {
		auto it = _content.find(p);
		if (it == _content.end())
			std::tie(it, std::ignore) = _content.emplace( std::make_pair(p, Value()) );
		if (!it->second[k]) {
			auto t = Creator<F, T>::create();
			ModelChecker<T>().work(t);
			it->second[k] = t;
			reverseAdd(p, t);
			return t;
		}
		return ecore::as<T>(it->second[k]);
	}

	template<class T>
	ecore::Ptr<T> find(const Ptr& p, SubKey k) {
		auto it = _content.find(p);
		if (it == _content.end())
			return ecore::Ptr<T>();
		return ecore::as<T>(it->second[k]);
	}

	/** Overwrite existing content for the given SubKey with a new value. */
	template<class T>
	void add(const Ptr& p, SubKey k, const ecore::Ptr<T>& v) {
		auto it = _content.find(p);
		if (it == _content.end())
			std::tie(it, std::ignore) = _content.emplace( std::make_pair(p, Value()) );
		it->second[k] = v;
	}

	void reverseAdd(const Ptr& am, const Ptr& inc) {
		_reverseContent.insert(std::make_pair(inc, am));
	}

	template<class T>
	ecore::Ptr<T> reverseFind(const Ptr& inc) {
		auto it = _reverseContent.find(inc);
		if (it == _reverseContent.end())
			return ecore::Ptr<T>();
		return ecore::as<T>(it->second);
	}

	void clear() { _content.clear(); _reverseContent.clear(); }

	const Map& getContent() const { return _content; }

private:
	Map _content;
	std::map< Ptr, Ptr > _reverseContent;
};
