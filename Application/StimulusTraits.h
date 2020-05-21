/** -*- c++ -*-
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#pragma once

#include <ecore_forward.hpp>

#include <amalthea/model.hpp>
#include <root/model/stimulation.hpp>

namespace sm3s = root::model::stimulation;


/** A type trait, which maps Amalthea Stimulus types to INCHRON
 * StimuliGenerator types.
 */
template<class A>
struct StimulusTrait { };

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
	// using type = sm3s::;
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

