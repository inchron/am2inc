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

#include <ecore_forward.hpp>

#include <root/RootFactory.hpp>
#include <root/model/ModelFactory.hpp>
#include <root/model/autosar/AutosarFactory.hpp>
#include <root/model/memory/MemoryFactory.hpp>
#include <root/model/metric/MetricFactory.hpp>
#include <root/model/peripheral/PeripheralFactory.hpp>
#include <root/model/requirement/RequirementFactory.hpp>
#include <root/model/stimulation/StimulationFactory.hpp>


/** A type trait to allow a templated creation of concrete objects.
 *
 * Its main intention is to allow
 * ObjectCache::make<root::RootFactory, root::Root>()
 */
template<class F, class T>
struct Creator {
	static ecore::Ptr< T > create();
};

template<class T>
struct Creator<root::RootFactory, T> {
	static ecore::Ptr< T > create() { return root::create<T>(); }
};

template<class T>
struct Creator<root::model::ModelFactory, T> {
	static ecore::Ptr< T > create() { return root::model::create<T>(); }
};

template<class T>
struct Creator<root::model::autosar::AutosarFactory, T> {
	static ecore::Ptr< T > create() { return root::model::autosar::create<T>(); }
};

template<class T>
struct Creator<root::model::memory::MemoryFactory, T> {
	static ecore::Ptr< T > create() { return root::model::memory::create<T>(); }
};

template<class T>
struct Creator<root::model::peripheral::PeripheralFactory, T> {
	static ecore::Ptr< T > create() { return root::model::peripheral::create<T>(); }
};

template<class T>
struct Creator<root::model::requirement::RequirementFactory, T> {
	static ecore::Ptr< T > create() { return root::model::requirement::create<T>(); }
};

template<class T>
struct Creator<root::model::stimulation::StimulationFactory, T> {
	static ecore::Ptr< T > create() { return root::model::stimulation::create<T>(); }
};

/* These packages are probably not needed:
 *
#include <root/model/fmi/FmiFactory.hpp>
#include <root/model/fmi/type/TypeFactory.hpp>
#include <root/model/fmi/unit/UnitFactory.hpp>
#include <root/model/fmi/variable/VariableFactory.hpp>
#include <root/model/metric/MetricFactory.hpp>
#include <root/results/ResultsFactory.hpp>
 *
 * root::model::fmi::FmiFactory
 * root::model::fmi::type::TypeFactory
 * root::model::fmi::unit::UnitFactory
 * root::model::fmi::variable::VariableFactory
 * root::model::metric::MetricFactory
 */

