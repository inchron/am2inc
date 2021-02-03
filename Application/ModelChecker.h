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
