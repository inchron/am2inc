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

#include <am200/model.hpp>
#include <root/model/stimulation.hpp>

#include "../StimulusTraits.h"

namespace am = am200::model;
namespace sm3s = root::model::stimulation;


/** StimulusTrait is a type trait, which maps Amalthea Stimulus types to
 * INCHRON StimuliGenerator types.
 */
template<>
struct StimulusTrait<am::ArrivalCurveStimulus> {
	// using type = sm3s::;
};

template<>
struct StimulusTrait<am::CustomStimulus> {
	// using type = sm3s::;
};

template<>
struct StimulusTrait<am::EventStimulus> {
	// using type = sm3s::;
};

template<>
struct StimulusTrait<am::InterProcessStimulus> {
	using type = sm3::ActivationConnection;
};

template<>
struct StimulusTrait<am::PeriodicBurstStimulus> {
	using type = sm3s::RandomStimuliGenerator;
};

template<>
struct StimulusTrait<am::PeriodicStimulus> {
	using type = sm3s::RandomStimuliGenerator;
};

template<>
struct StimulusTrait<am::PeriodicSyntheticStimulus> {
	using type = sm3s::InducedListBasedGenerator;
};

template<>
struct StimulusTrait<am::RelativePeriodicStimulus> {
	using type = sm3s::RandomStimuliGenerator;
};

template<>
struct StimulusTrait<am::SingleStimulus> {
	using type = sm3s::ListBasedGenerator;
};

template<>
struct StimulusTrait<am::VariableRateStimulus> {
	// using type = sm3s::;
};
