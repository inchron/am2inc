/* -*- c++ -*-
 *
 * Converter/activityGraph.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file activityGraph.cpp
 * Groups all code related to Amalthea's ActivitGraph and ActivityGraphItems.
 *
 * The conversion concept is as follows:
 *
 * We know the current CallGraph and the current CallSequenceItem.
 *
 * All CallSequenceItems are added to the current CallSequenceItem, except as
 * given below.
 *
 * An am::Group creates a new CallSequenceItem as sibling of the current
 * CallSequenceItem unless it is empty, in which case it is reused.
 *
 * am::ModeSwitch and am::ProbabilitySwitch are am::ActivityGraphItems, but
 * are not translated to CallSequenceItems. Instead they end the current
 * CallSequence and are added as its sibling. When the am::ModeSwitch or the
 * am::ProbabilitySwitch ends, a new CallSequenceItem is created and set as
 * the current one.
 *
 * Nested sm3::ModeSwitch and and sm3::ProbabilitySwitch instances are tracked
 * in a graphEntries deque.
 *
 */
#include "../Converter.h"

#include <Model/Time.h>

#include "../AttributeCreator.h"
#include "../Diagnostic.h"
#include "../StimulusTraits.h"


namespace details {

/** Remove the CallSequence from its parent, if it is empty AND has no
 * Amalthea counterpart.
 */
bool isUnused(const sm3::CallSequence_ptr& cs, ObjectCache& oc) {
	return cs->getCalls().size() == 0
		&& !oc.reverseFind<ecore::EObject_ptr>(cs);
}

/** Remove the CallSequence from its parent, if it is empty AND has no
 * Amalthea counterpart.
 */
void removeIfUnused(const sm3::CallSequence_ptr& cs, ObjectCache& oc) {
	if (isUnused(cs, oc)) {
		auto parent = cs->eContainer();
		auto ef = cs->eContainingFeature();

		auto any = parent->eGet(ef);
		ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type list =
			ecorecpp::mapping::any::any_cast<
				ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type>(any);

		list->remove(cs);
	}
}

template<class T, class U>
void addAsSibling(const ecore::Ptr<T>& older, const ecore::Ptr<U>& younger) {
	auto parent = older->eContainer();
	auto ef = older->eContainingFeature();

	auto any = parent->eGet(ef);
	ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type list =
		ecorecpp::mapping::any::any_cast<
			ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type>(any);

	list->push_back(younger);
}

} // namespace details


void Converter::work(const am::ActivityGraph_ptr& am, am::ActivityGraph*) {
	if (_mode == PreOrder) {
		auto cg = _oc.make<sm3::ModelFactory, sm3::CallGraph>(am);
		auto parent = _oc.find<sm3::ModelObject>(am->eContainer(), ObjectCache::Default);
		if (auto process = ecore::as<sm3::Process>(parent))
			process->setCallGraph(cg);
		else if (auto runnable = ecore::as<sm3::Function>(parent))
			runnable->setCallGraph(cg);

		auto cs = sm3::create<sm3::CallSequence>();
		cg->getGraphEntries().push_back(cs);

		_callGraph = cg;
		_callSequence = cs;
		assert(_graphEntries.empty());

	} else {
		details::removeIfUnused(_callSequence, _oc);

		_callGraph = sm3::CallGraph_ptr();
		_callSequence = sm3::CallSequence_ptr();
		_graphEntries.clear();
	}
}

void Converter::work(const am::Group_ptr& am, am::Group*) {
	if (_mode == PreOrder) {
		auto cs = _callSequence;
		if (details::isUnused(cs, _oc)) {
			_oc.add(am, ObjectCache::Default, cs);
			_oc.reverseAdd(am, cs);
		} else {
			cs = _oc.make<sm3::ModelFactory, sm3::CallSequence>(am);
			details::addAsSibling(_callSequence, cs);
			_callSequence = cs;
		}

		cs->setName(am->getName());

	} else { // PostOrder
		auto cs = sm3::create<sm3::CallSequence>();
		details::addAsSibling(_callSequence, cs);
		_callSequence = cs;
	}
}

void Converter::work(const am::LabelAccess_ptr& am, am::LabelAccess*) {
	if (_mode == PreOrder) {
		auto rc = _oc.make<sm3::ModelFactory, sm3::ResourceConsumption>(am, ObjectCache::Default);
		_callSequence->getCalls().push_back(rc);
		rc->getStackUsage()->setValue(0);

		static int instanceCounter = 0;
		rc->setName("LabelAccess_" + am->getData()->getName()
					+ "_" + std::to_string(instanceCounter++));

		auto access = _oc.make<sm3m::MemoryFactory, sm3m::ExplicitDataAccess>(am, ObjectCache::Sub1);
		rc->getDataAccess().push_back(access);
		access->setAccessType(am->getAccess() == am::LabelAccessEnum::write ?
							  sm3m::DataAccessType::Write : sm3m::DataAccessType::Read);
		access->setDataObject(_oc.make<sm3m::MemoryFactory, sm3m::DataObject>(am->getData()));
		access->getBandwidth()->setValue(0);
	}
}

void Converter::work(const am::RunnableCall_ptr& am, am::RunnableCall*) {
	if (_mode == PreOrder) {
		auto call = _oc.make<sm3::ModelFactory, sm3::FunctionCall>(am);
		_callSequence->getCalls().push_back(call);
		call->setFunction(_oc.make<sm3::ModelFactory, sm3::Function>(am->getRunnable()));
		call->setName("Call_" + am->getRunnable()->getName());
	} else {
	}
}

void Converter::work(const am::InterProcessTrigger_ptr& am, am::InterProcessTrigger*) {
	if (_mode == PreOrder) {
		auto act = _oc.make<sm3::ModelFactory, sm3::ActivationItem>(am);
		_callSequence->getCalls().push_back(act);
		act->setName("InterProcessTrigger_" + am->getStimulus()->getName());
		act->setConnection(_oc.make<sm3::ModelFactory, sm3::ActivationConnection>(am->getStimulus()));
		if (auto counter = am->getStimulus()->getCounter()) {
			act->setPeriod(counter->getPrescaler());
			act->setOffset(counter->getOffset());
		}
	}
}

void Converter::work(const am::SetEvent_ptr& am, am::SetEvent*) {
	if (_mode == PreOrder) {
		auto set = _oc.make<sm3::ModelFactory, sm3::SetEvent>(am);
		_callSequence->getCalls().push_back(set);

		for (auto&& amEvent : am->getEventMask()->getEvents()) {
			auto event = _oc.make<sm3::ModelFactory, sm3::Event>(amEvent);
			set->setEvent(event);
			break;
		}
	}
}

void Converter::work(const am::WaitEvent_ptr& am, am::WaitEvent*) {
	if (_mode == PreOrder) {
		auto wait = _oc.make<sm3::ModelFactory, sm3::WaitEvent>(am);
		_callSequence->getCalls().push_back(wait);

		for (auto&& amEvent : am->getEventMask()->getEvents()) {
			auto event = _oc.make<sm3::ModelFactory, sm3::Event>(amEvent);
			wait->setEvent(event);
			break;
		}
	}
}

void Converter::work(const am::ClearEvent_ptr& am, am::ClearEvent*) {
	if (_mode == PreOrder) {
		auto clear = _oc.make<sm3::ModelFactory, sm3::SetEvent>(am);
		clear->setIsReset(true);
		_callSequence->getCalls().push_back(clear);

		for (auto&& amEvent : am->getEventMask()->getEvents()) {
			auto event = _oc.make<sm3::ModelFactory, sm3::Event>(amEvent);
			clear->setEvent(event);
			break;
		}
	}
}

namespace details {

/* IDiscreteValueDeviation is an interface class, which is implemented by
 * DiscreteValueConstant, DiscreteValueHistogram,
 *
 * BoundedDiscreteValueDistribution (ie. DiscreteValueBoundaries,
 * DiscreteValueStatistics, DiscreteValueUniformDistribution,
 * DiscreteValueWeibullEstimatorsDistribution, DiscreteValueBetaDistribution),
 *
 * and TruncatedDiscreteValueDistribution (ie. DiscreteValueGaussDistribution)
 */
sm3::TimeDistribution_ptr createTimeDistribution(am::IDiscreteValueDeviation_ptr am) {
	auto td = sm3::create<sm3::TimeDistribution>();

	auto classifier = am->eClass()->getClassifierID();
	switch (classifier) {
	case am::ModelPackage::DISCRETEVALUECONSTANT:
		td->setMin(AttributeCreator<sm3::Time>()(am->getLowerBound(), sm3::TimeUnit::T));
		td->setMax(AttributeCreator<sm3::Time>()(am->getUpperBound(), sm3::TimeUnit::T));
		td->setType(sm3::TimeDistributionType::Min);
		break;

	case am::ModelPackage::DISCRETEVALUEHISTOGRAM: {
		// Translate to DiscreteDistribution
		auto histo = ecore::as<am::DiscreteValueHistogram>(am);
		for (auto&& entry : histo->getEntries()) {
			// entry := DiscreteValueInterval + #occurrences
			auto dde = sm3::create<sm3::DiscreteDistributionEntry>();
			dde->setCount(entry->getOccurrences());
			dde->setLower(AttributeCreator<sm3::Time>()(entry->getLowerBound(), sm3::TimeUnit::T));
			dde->setUpper(AttributeCreator<sm3::Time>()(entry->getUpperBound(), sm3::TimeUnit::T));
			td->getDiscreteDistribution().push_back(dde);
		}
		td->setType(sm3::TimeDistributionType::Discrete);
	} break;

	case am::ModelPackage::DISCRETEVALUEBOUNDARIES: {
		auto bound = ecore::as<am::DiscreteValueBoundaries>(am);
		td->setMin(AttributeCreator<sm3::Time>()(bound->getLowerBound(), sm3::TimeUnit::T));
		td->setMax(AttributeCreator<sm3::Time>()(bound->getUpperBound(), sm3::TimeUnit::T));
		switch (bound->getSamplingType()) {
		case am::SamplingType::BestCase:
			td->setType(sm3::TimeDistributionType::Min);
			break;
		case am::SamplingType::WorstCase:
			td->setType(sm3::TimeDistributionType::Max);
			break;
		case am::SamplingType::Uniform:
			td->setType(sm3::TimeDistributionType::Uniform);
			break;
		default:
			std::cerr << "Unsupported DiscreteValueBoundaries::samplingType "
					  << am::ModelPackage::_instance()->getSamplingType()
				->getEEnumLiteral((int)bound->getSamplingType())->getName()
					  << "\n";
		}
	} break;

	case am::ModelPackage::DISCRETEVALUESTATISTICS: {
		auto stat = ecore::as<am::DiscreteValueStatistics>(am);
		auto avg = ::Time(*AttributeCreator<sm3::Time>()(stat->getAverage(), sm3::TimeUnit::T));
		auto min = ::Time(*AttributeCreator<sm3::Time>()(stat->getLowerBound(), sm3::TimeUnit::T));
		auto max = ::Time(*AttributeCreator<sm3::Time>()(stat->getUpperBound(), sm3::TimeUnit::T));

		auto dl = avg - min;
		auto du = max - avg;
		::Time sigma;
		if (dl > du)
			sigma = dl / 3;
		else
			sigma = du / 3;

		td->setMin(min.toModelTime());
		td->setMax(max.toModelTime());
		td->setMean(avg.toModelTime());
		td->setSigma(sigma.toModelTime());
		td->setType(sm3::TimeDistributionType::Normal);
	} break;

	case am::ModelPackage::DISCRETEVALUEUNIFORMDISTRIBUTION: {
		td->setMin(AttributeCreator<sm3::Time>()(am->getLowerBound(), sm3::TimeUnit::T));
		td->setMax(AttributeCreator<sm3::Time>()(am->getUpperBound(), sm3::TimeUnit::T));
		td->setType(sm3::TimeDistributionType::Uniform);
	} break;

	case am::ModelPackage::DISCRETEVALUEWEIBULLESTIMATORSDISTRIBUTION: {
		/* amalthea.ecore says: "The parameter of a Weibull distribution
		 * (kappa, lambda...) are calculated from the estimators minimum,
		 * maximum and average.".
		 * The class provides an additional "pRemainPromille".
		 */
		static Diagnostic::NotImplemented<am::DiscreteValueWeibullEstimatorsDistribution> message;
	} break;

	case am::ModelPackage::DISCRETEVALUEBETADISTRIBUTION: {
		/* Beta distribution is not supported. */
		static Diagnostic::NotImplemented<am::DiscreteValueBetaDistribution> message;
	} break;

	case am::ModelPackage::DISCRETEVALUEGAUSSDISTRIBUTION: {
		auto gauss = ecore::as<am::DiscreteValueGaussDistribution>(am);
		td->setMean(AttributeCreator<sm3::Time>()(gauss->getMean(), sm3::TimeUnit::T));
		td->setSigma(AttributeCreator<sm3::Time>()(gauss->getSd(), sm3::TimeUnit::T));
		td->setType(sm3::TimeDistributionType::Normal);
	} break;

	}

	ModelChecker<sm3::TimeDistribution>().work(td);
	return td;
}

} // namespace details

void Converter::work(const am::Ticks_ptr& am, am::Ticks*) {
	if (_mode == PreOrder) {
		auto consumption = _oc.make<sm3::ModelFactory, sm3::ResourceConsumption>(am);
		consumption->getStackUsage()->setValue(0);
		_callSequence->getCalls().push_back(consumption);

		auto value = am->getDefault();
		if (!value) {
			if (Diagnostic::ObjectRequired::notEmpty(am->getExtended()))
				value = am->getExtended().get(0)->getValue();
		}

		if (Diagnostic::ObjectRequired::exists(value))
			consumption->setTimeDistribution(details::createTimeDistribution(value));
	}
}

void Converter::work(const am::ChannelReceive_ptr&, am::ChannelReceive*) {
	static Diagnostic::NotImplemented<am::ChannelReceive> message;
}

void Converter::work(const am::ChannelSend_ptr&, am::ChannelSend*) {
	static Diagnostic::NotImplemented<am::ChannelSend> message;
}

void Converter::work(const am::CustomEventTrigger_ptr&, am::CustomEventTrigger*) {
	static Diagnostic::NotImplemented<am::CustomEventTrigger> message;
}

void Converter::work(const am::EnforcedMigration_ptr&, am::EnforcedMigration*) {
	static Diagnostic::NotImplemented<am::EnforcedMigration> message;
}

void Converter::work(const am::ExecutionNeed_ptr&, am::ExecutionNeed*) {
	static Diagnostic::NotImplemented<am::ExecutionNeed> message;
}

void Converter::work(const am::GetResultServerCall_ptr&, am::GetResultServerCall*) {
	static Diagnostic::NotImplemented<am::GetResultServerCall> message;
}

void Converter::work(const am::ModeLabelAccess_ptr&, am::ModeLabelAccess*) {
	static Diagnostic::NotImplemented<am::ModeLabelAccess> message;
}

void Converter::work(const am::ModeSwitch_ptr&, am::ModeSwitch*) {
	static Diagnostic::NotImplemented<am::ModeSwitch> message;
}

void Converter::work(const am::ProbabilitySwitch_ptr&, am::ProbabilitySwitch*) {
	static Diagnostic::NotImplemented<am::ProbabilitySwitch> message;
}

void Converter::work(const am::SchedulePoint_ptr&, am::SchedulePoint*) {
	static Diagnostic::NotImplemented<am::SchedulePoint> message;
}

void Converter::work(const am::SemaphoreAccess_ptr&, am::SemaphoreAccess*) {
	static Diagnostic::NotImplemented<am::SemaphoreAccess> message;
}

void Converter::work(const am::SenderReceiverRead_ptr&, am::SenderReceiverRead*) {
	static Diagnostic::NotImplemented<am::SenderReceiverRead> message;
}

void Converter::work(const am::SenderReceiverWrite_ptr&, am::SenderReceiverWrite*) {
	static Diagnostic::NotImplemented<am::SenderReceiverWrite> message;
}

void Converter::work(const am::SynchronousServerCall_ptr&, am::SynchronousServerCall*) {
	static Diagnostic::NotImplemented<am::SynchronousServerCall> message;
}

void Converter::work(const am::TerminateProcess_ptr&, am::TerminateProcess*) {
	static Diagnostic::NotImplemented<am::TerminateProcess> message;
}