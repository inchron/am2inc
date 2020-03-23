/** -*- c++ -*-
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#pragma once

#include <root/model/GenericSystem.hpp>

#include "EcoreModelChecker.h"

/** In general, a ModelChecker is a template wrapper around the generic,
 * ecore-based model checker, but template specializations may add behavior.
 */
template<class C>
struct ModelChecker {
	void work(const ecore::Ptr<C>& o) { EcoreModelChecker().work(o); }
};


/** This ModelChecker adds the scheduler hierarchy to the GenericSystem.
 */
template<>
struct ModelChecker<root::model::GenericSystem> {
	void work(const ecore::Ptr<root::model::GenericSystem>& o);
};
