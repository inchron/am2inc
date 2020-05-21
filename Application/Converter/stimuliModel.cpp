/* -*- c++ -*-
 *
 * Converter/stimuliModel.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file stimuliModel.cpp
 * Groups all code related to Amalthea's StimuliModel.
 */
#include "../Converter.h"

#include "../AttributeCreator.h"
#include "../StimulusTraits.h"

namespace sm3s = root::model::stimulation;


void Converter::work(const am::ArrivalCurveStimulus_ptr&, am::ArrivalCurveStimulus*) {
}

void Converter::work(const am::CustomStimulus_ptr&, am::CustomStimulus*) {
}

void Converter::work(const am::EventStimulus_ptr&, am::EventStimulus*) {
}

void Converter::work(const am::InterProcessStimulus_ptr&, am::InterProcessStimulus*) {
}

void Converter::work(const am::PeriodicBurstStimulus_ptr& am, am::PeriodicBurstStimulus*) {
	if (_mode == PreOrder) {
		auto gen = _oc.make<sm3s::StimulationFactory, StimulusTrait<am::PeriodicBurstStimulus>::type >(am);
		gen->setName(am->getName());
		gen->setClock(_idealClock);

		{ /* Inherited from am::FixedPeriodic */
			gen->setPeriod(AttributeCreator<sm3::Time>()(am->getRecurrence()));
			auto startOffset = sm3s::create<sm3s::StartOffsetVariation>();
			startOffset->setType(sm3s::StartOffsetVariationType::Min);
			startOffset->setMin(AttributeCreator<sm3::Time>()(am->getOffset()));
			startOffset->setMax(sm3::create<sm3::Time>());
			gen->setStartOffsetVariation(startOffset);
		}

		auto burst = sm3s::create<sm3s::BurstPattern>();
		burst->setMaximumOccurrences(am->getOccurrenceCount());
		burst->setMinimumInterArrivalTime(AttributeCreator<sm3::Time>()(am->getOccurrenceMinDistance()));
		burst->setPatternLength(AttributeCreator<sm3::Time>()(am->getBurstLength()));
		gen->setBurstPatternSettings(burst);

		ecore::as<sm3s::StimulationScenario>(_model->getDefaultScenario())
			->getGenerators().push_back(gen);
	}
}

/** Transform an am::PeriodicStimulus into a sm3::RandomStimuliGenerator.
 *
 * The PeriodicStimulus has a period and a jitter, which is added on top. For
 * a gauss distribution the mean value is assumed to be zero, only the sigma
 * is used.
 */
void Converter::work(const am::PeriodicStimulus_ptr& am, am::PeriodicStimulus*) {
	if (_mode == PreOrder) {
		auto gen = _oc.make<sm3s::StimulationFactory, StimulusTrait<am::PeriodicStimulus>::type >(am);
		gen->setName(am->getName());
		gen->setClock(_idealClock);

		{ /* Inherited from am::FixedPeriodic */
			gen->setPeriod(AttributeCreator<sm3::Time>()(am->getRecurrence()));
			auto startOffset = sm3s::create<sm3s::StartOffsetVariation>();
			startOffset->setType(sm3s::StartOffsetVariationType::Min);
			startOffset->setMin(AttributeCreator<sm3::Time>()(am->getOffset()));
			startOffset->setMax(sm3::create<sm3::Time>());
			gen->setStartOffsetVariation(startOffset);
		}

		gen->setMinimumInterArrivalTime(AttributeCreator<sm3::Time>()(am->getMinDistance()));

		/* Jitter, minDistance */
		if (am::ITimeDeviation_ptr jitter = am->getJitter() ) {
			auto variation = sm3::create<sm3::PeriodVariation>();
			gen->setVariation(variation);

			variation->setMin(AttributeCreator<sm3::Time>()(jitter->getLowerBound()));
			variation->setMax(AttributeCreator<sm3::Time>()(jitter->getUpperBound()));
			auto amPkg = am::ModelPackage::_instance();

			if (jitter->eClass() == amPkg->getTimeGaussDistribution()) {
				variation->setType(sm3::PeriodVariationType::Normal);
				variation->setSigma(
					AttributeCreator<sm3::Time>()(
						ecore::as<am::TimeGaussDistribution>(jitter)->getSd()));

			} else if (jitter->eClass() == amPkg->getTimeUniformDistribution()) {
				variation->setType(sm3::PeriodVariationType::Uniform);

			} else {
				std::cerr << "Unsupported ITimeDeviation " << jitter->eClass()->getName() << "\n";
				throw "Unsupported ITimeDeviation";
			}
		}

		ecore::as<sm3s::StimulationScenario>(_model->getDefaultScenario())
			->getGenerators().push_back(gen);
	}
}

void Converter::work(const am::PeriodicSyntheticStimulus_ptr& am, am::PeriodicSyntheticStimulus*) {
	if (_mode == PreOrder) {
		auto periodic = _oc.make<sm3s::StimulationFactory, sm3s::RandomStimuliGenerator>(
			am, ObjectCache::Sub1);
		periodic->setName(am->getName() + "PeriodicDriver");
		periodic->setClock(_idealClock);
		{ /* Inherited from am::FixedPeriodic */
			periodic->setPeriod(AttributeCreator<sm3::Time>()(am->getRecurrence()));
			auto startOffset = sm3s::create<sm3s::StartOffsetVariation>();
			startOffset->setType(sm3s::StartOffsetVariationType::Min);
			startOffset->setMin(AttributeCreator<sm3::Time>()(am->getOffset()));
			startOffset->setMax(sm3::create<sm3::Time>());
			periodic->setStartOffsetVariation(startOffset);
		}
		ecore::as<sm3s::StimulationScenario>(_model->getDefaultScenario())
			->getGenerators().push_back(periodic);

		auto gen = _oc.make<sm3s::StimulationFactory, StimulusTrait<am::PeriodicSyntheticStimulus>::type >(am);
		gen->setName(am->getName());
		gen->setClock(_idealClock);

		gen->setSourceGenerator(periodic);

		for (auto&& occurrence : am->getOccurrenceTimes())
			gen->getEntries().push_back(
				AttributeCreator<sm3::Time>()(occurrence));

		ecore::as<sm3s::StimulationScenario>(_model->getDefaultScenario())
			->getGenerators().push_back(gen);
	}
}

namespace /* anonymous */ {


std::underlying_type<sm3::TimeUnit>::type operator +(sm3::TimeUnit val) {
	return static_cast< typename std::underlying_type<sm3::TimeUnit>::type >(val);
}

sm3::TimeUnit operator ++(sm3::TimeUnit& val) {
	return val = static_cast<sm3::TimeUnit>( + val + 1 );
}

sm3::Time& operator-=(sm3::Time& lhs, const sm3::Time& rhs) {
	if (lhs.getUnit() == rhs.getUnit()) {
		lhs.setValue(lhs.getValue() - rhs.getValue());

	} else if (lhs.getUnit() >= sm3::TimeUnit::T || rhs.getUnit() >= sm3::TimeUnit::T) {
		throw std::logic_error("Cannot subtract Time values with different units");

	} else if (lhs.getUnit() > rhs.getUnit()) {
		auto r = rhs.getValue();
		auto u = rhs.getUnit();
		while (lhs.getUnit() > u) {
			r *= 1000;
			++u;
		}

		lhs.setValue(lhs.getValue() - r);

	} else if (lhs.getUnit() < rhs.getUnit()) {
		auto l = lhs.getValue();
		auto u = lhs.getUnit();
		while (u < rhs.getUnit()) {
			l *= 1000;
			++u;
		}

		lhs.setValue(l - rhs.getValue());
	}

	return lhs;
}

} // namespace anonymous

/** Transform an am::RelativePeriodicStimulus into a sm3::RandomStimuliGenerator.
 *
 * The RelativePeriodicStimulus does not have a period, only a jitter. In case
 * of a gauss distribution, the mean value is used as period. For a uniform
 * distribution, the lower bound is used as period, and the length of the
 * interval [lower, upper[ is used for the distribution.
 */
void Converter::work(const am::RelativePeriodicStimulus_ptr& am, am::RelativePeriodicStimulus*) {
	if (_mode == PreOrder) {
		auto gen = _oc.make<sm3s::StimulationFactory, StimulusTrait<am::RelativePeriodicStimulus>::type >(am);
		gen->setName(am->getName());
		gen->setClock(_idealClock);
		gen->setRelative(true);

		{
			auto startOffset = sm3s::create<sm3s::StartOffsetVariation>();
			startOffset->setType(sm3s::StartOffsetVariationType::Min);
			startOffset->setMin(AttributeCreator<sm3::Time>()(am->getOffset()));
			startOffset->setMax(sm3::create<sm3::Time>());
			gen->setStartOffsetVariation(startOffset);
		}

		/* Jitter, minDistance */
		if (am::ITimeDeviation_ptr jitter = am->getNextOccurrence() ) {
			auto variation = sm3::create<sm3::PeriodVariation>();
			gen->setVariation(variation);

			auto lower = AttributeCreator<sm3::Time>()(jitter->getLowerBound());
			auto upper = AttributeCreator<sm3::Time>()(jitter->getUpperBound());
			auto amPkg = am::ModelPackage::_instance();

			if (jitter->eClass() == amPkg->getTimeGaussDistribution()) {
				auto tgd = ecore::as<am::TimeGaussDistribution>(jitter);
				gen->setPeriod(AttributeCreator<sm3::Time>()(tgd->getMean()));
				variation->setMin(lower);
				variation->setMax(upper);
				variation->setType(sm3::PeriodVariationType::Normal);
				variation->setSigma(
					AttributeCreator<sm3::Time>()(tgd->getSd()));

			} else if (jitter->eClass() == amPkg->getTimeUniformDistribution()) {
				gen->setPeriod(lower);
				variation->setMin(sm3::create<sm3::Time>());
				*upper -= *lower;
				variation->setMax(upper);
				variation->setType(sm3::PeriodVariationType::Uniform);

			} else {
				std::cerr << "Unsupported ITimeDeviation " << jitter->eClass()->getName() << "\n";
				throw "Unsupported ITimeDeviation";
			}
		}

		ecore::as<sm3s::StimulationScenario>(_model->getDefaultScenario())
			->getGenerators().push_back(gen);
	}
}

void Converter::work(const am::SingleStimulus_ptr& am, am::SingleStimulus*) {
	if (_mode == PreOrder) {
		auto gen = _oc.make<sm3s::StimulationFactory, StimulusTrait<am::SingleStimulus>::type >(am);
		gen->setName(am->getName());
		gen->setClock(_idealClock);

		gen->getEntries().push_back(
			AttributeCreator<sm3::Time>()(am->getOccurrence()));
		ecore::as<sm3s::StimulationScenario>(_model->getDefaultScenario())
			->getGenerators().push_back(gen);
	}
}

void Converter::work(const am::VariableRateStimulus_ptr&, am::VariableRateStimulus*) {
}

