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

#include "../AttributeCreator.h"
#include "../Diagnostic.h"
#include "../StimulusTraits.h"
#include "../TimeOperators.h"

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


/** Translate an am::ActivityGraph into a sm3::CallGraph.
 *
 * Amalthea does not necessarily need a CallSequence, but in the INCHRON model
 * every CallSequenceItem must be contained by a CallSequence. Whenever
 * needed, CallSequences are created, and afterwards the helper methods
 * defined above detect and remove unnecessary instances.
 *
 * GraphEntries are tracked in a std::deque. The current CallSequence is
 * always at the end. When a ModeSwitch or another GraphEntry is processed, it
 * is added as sibling of the current end, and the newly created CallSequence
 * is appended to the std::deque. The postorder processing of the ModeSwitch
 * is responsible to not only cleanup empty CallSequences, but also remove it
 * from the std::deque.
 */
void Converter::work(const am::ActivityGraph_ptr& am, am::ActivityGraph*) {
	if (_mode == PreOrder) {
		auto cg = _oc.make<sm3::ModelFactory, sm3::CallGraph>(am);
		auto parent = _oc.find<sm3::ModelObject>(am->eContainer(), ObjectCache::Default);
		if (auto process = ecore::as<sm3::Process>(parent))
			process->setCallGraph(cg);
		else if (auto runnable = ecore::as<sm3::Function>(parent))
			runnable->setCallGraph(cg);

		auto cs = sm3::create<sm3::CallSequence>();
		setName(*cs);
		cg->getGraphEntries().push_back(cs);

		_callGraph = cg;
		_callSequence = cs;
		assert(_graphEntries.empty());
		_graphEntries.push_back(_callSequence);

		_csiCounter = 0u;
		_geCounter = 0u;

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
			_graphEntries.pop_back();
			_graphEntries.push_back(_callSequence);
		}

		cs->setName(am->getName());
		if (!am->isOrdered()) {
			std::cerr << "Unsupported attribute: Group '" << am->getName()
					  << "' uses random execution order\n";
		}

	} else { // PostOrder
		auto cs = sm3::create<sm3::CallSequence>();
		setName(*cs);
		details::addAsSibling(_callSequence, cs);
		_callSequence = cs;
		_graphEntries.pop_back();
		_graphEntries.push_back(_callSequence);
	}
}

void Converter::work(const am::LabelAccess_ptr& am, am::LabelAccess*) {
	if (_mode == PreOrder) {
		auto rc = _oc.make<sm3::ModelFactory, sm3::ResourceConsumption>(am, ObjectCache::Default);
		_callSequence->getCalls().push_back(rc);

		setName(*rc, "LabelAccess_" + am->getData()->getName());

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
		setName(*call, "Call_" + am->getRunnable()->getName());
	} else {
	}
}

void Converter::work(const am::InterProcessTrigger_ptr& am, am::InterProcessTrigger*) {
	if (_mode == PreOrder) {
		auto act = _oc.make<sm3::ModelFactory, sm3::ActivationItem>(am);
		_callSequence->getCalls().push_back(act);
		setName(*act, "InterProcessTrigger_" + am->getStimulus()->getName());
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
		clear->setReset(true);
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
		auto avg = AttributeCreator<sm3::Time>()(stat->getAverage(), sm3::TimeUnit::T);
		auto min = AttributeCreator<sm3::Time>()(stat->getLowerBound(), sm3::TimeUnit::T);
		auto max = AttributeCreator<sm3::Time>()(stat->getUpperBound(), sm3::TimeUnit::T);

		/* In general it is not safe to handle EMF objects, which are not
		 * created on the heap and are not managed by a std::shared_ptr<>. */
		auto dl = root::model::create<root::model::Time>();
		auto du  = root::model::create<root::model::Time>();
		auto sigma = root::model::create<root::model::Time>();

		*dl = *avg - *min;
		*du = *max - *avg;
		if (*dl > *du)
			*sigma = *dl / 3;
		else
			*sigma = *du / 3;

		td->setMin(min);
		td->setMax(max);
		td->setMean(avg);
		td->setSigma(sigma);
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
		td->setMin(AttributeCreator<sm3::Time>()(am->getLowerBound(), sm3::TimeUnit::T));
		td->setMax(AttributeCreator<sm3::Time>()(am->getUpperBound(), sm3::TimeUnit::T));
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
		setName(*consumption, "Tick");
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

void Converter::work(const am::ModeSwitch_ptr& am, am::ModeSwitch*) {
	if (_mode == PreOrder) {
		auto modeSwitch = _oc.make<sm3::ModelFactory, sm3::ModeSwitch>(am);
		setName(*modeSwitch);
		details::addAsSibling(_callSequence, modeSwitch);
		details::removeIfUnused(_callSequence, _oc);

		/* The end of this am::ModeSwitch, any am::ModeSwitchEntry and an
		 * am::ModeSwitchDefault will lead to the creation of a new
		 * CallSequence. */
		_callSequence = sm3::CallSequence_ptr();

		_mseCounter.push(0u);

	} else {
		/* A new CallSequence starts after the ModeSwitch. It replaces the
		 * previous one. */
		_callSequence = sm3::create<sm3::CallSequence>();
		setName(*_callSequence);
		auto thisModeSwitch = _oc.make<sm3::ModelFactory, sm3::ModeSwitch>(am);
		details::addAsSibling( thisModeSwitch, _callSequence);
		_graphEntries.pop_back();
		_graphEntries.push_back(_callSequence);

		_mseCounter.pop();
	}
}

void Converter::work(const am::ModeSwitchDefault_ptr& am, am::ModeSwitchDefault*) {
	if (_mode == PreOrder) {
		auto msd = _oc.make<sm3::ModelFactory, sm3::ModeSwitchDefault>(am);
		auto modeSwitch = _oc.make<sm3::ModelFactory, sm3::ModeSwitch>(am->eContainer());
		modeSwitch->setDefaultEntry(msd);

		auto cs = sm3::create<sm3::CallSequence>();
		setName(*cs);
		msd->getGraphEntries().push_back(cs);
		_graphEntries.push_back(cs);
		_callSequence = cs;

	} else {
		details::removeIfUnused(_callSequence, _oc);
		_callSequence = sm3::CallSequence_ptr();
		_graphEntries.pop_back();
	}
}

void Converter::work(const am::ModeSwitchEntry_ptr& am, am::ModeSwitchEntry*) {
	if (_mode == PreOrder) {
		auto mse = _oc.make<sm3::ModelFactory, sm3::ModeSwitchEntry>(am);
		setName(*mse);
		auto modeSwitch = _oc.make<sm3::ModelFactory, sm3::ModeSwitch>(am->eContainer());
		assert(modeSwitch);
		modeSwitch->getEntries().push_back(mse);

		auto condition = _oc.make<sm3::ModelFactory, sm3::ModeCondition>(am->getCondition());
		mse->setCondition(condition);

		auto cs = sm3::create<sm3::CallSequence>();
		setName(*cs);
		mse->getGraphEntries().push_back(cs);
		_graphEntries.push_back(cs);
		_callSequence = cs;

	} else {
		details::removeIfUnused(_callSequence, _oc);
		_callSequence = sm3::CallSequence_ptr();
		_graphEntries.pop_back();
	}
}

void Converter::work(const am::ProbabilitySwitch_ptr& am, am::ProbabilitySwitch*) {
	if (_mode == PreOrder) {
		auto probSwitch = _oc.make<sm3::ModelFactory, sm3::ProbabilitySwitch>(am);
		setName(*probSwitch);
		details::addAsSibling(_callSequence, probSwitch);
		details::removeIfUnused(_callSequence, _oc);

		/* The end of this am::ProbabilitySwitch, and any
		 * am::ProbabilitySwitchEntry will lead to the creation of a new
		 * CallSequence. */
		_callSequence = sm3::CallSequence_ptr();

		_mseCounter.push(0u);

	} else {
		/* A new CallSequence starts after the ProbalitySwitch. It replaces
		 * the previous one. */
		_callSequence = sm3::create<sm3::CallSequence>();
		setName(*_callSequence);
		auto thisProbSwitch = _oc.make<sm3::ModelFactory, sm3::ProbabilitySwitch>(am);
		details::addAsSibling( thisProbSwitch, _callSequence);
		_graphEntries.pop_back();
		_graphEntries.push_back(_callSequence);

		_mseCounter.pop();
	}
}

void Converter::work(const am::ProbabilitySwitchEntry_ptr& am, am::ProbabilitySwitchEntry*) {
	if (_mode == PreOrder) {
		auto pse = _oc.make<sm3::ModelFactory, sm3::ProbabilitySwitchEntry>(am);
		setName(*pse);
		auto probSwitch = _oc.make<sm3::ModelFactory, sm3::ProbabilitySwitch>(am->eContainer());
		assert(probSwitch);
		probSwitch->getEntries().push_back(pse);

		auto probability = am->getProbability();
		pse->setProbability(probability);

		auto cs = sm3::create<sm3::CallSequence>();
		setName(*cs);
		pse->getGraphEntries().push_back(cs);
		_graphEntries.push_back(cs);
		_callSequence = cs;

	} else {
		details::removeIfUnused(_callSequence, _oc);
		_callSequence = sm3::CallSequence_ptr();
		_graphEntries.pop_back();
	}
}

void Converter::work(const am::SchedulePoint_ptr&, am::SchedulePoint*) {
	static Diagnostic::NotImplemented<am::SchedulePoint> message;
}

void Converter::work(const am::SemaphoreAccess_ptr& am, am::SemaphoreAccess*) {
	if (_mode == PreOrder) {
		auto access = _oc.make<sm3::ModelFactory, sm3::SemaphoreAccess>(am);
		_callSequence->getCalls().push_back(access);

		auto theSemaphore = am->getSemaphore();
		if (theSemaphore) {
			setName(*access, "SemaphoreAccess_" + theSemaphore->getName());
			auto semaphore = _oc.make<sm3::ModelFactory, sm3::Semaphore>(theSemaphore);
			access->setSemaphore(semaphore);
		}

		auto type = am->getAccess();
		switch (type) {
		case am::SemaphoreAccessEnum::request:
			access->setType(sm3::SemaphoreAccessType::Request);
			break;
		case am::SemaphoreAccessEnum::exclusive:
			access->setType(sm3::SemaphoreAccessType::Exclusive);
			break;
		case am::SemaphoreAccessEnum::release:
			access->setType(sm3::SemaphoreAccessType::Release);
			break;
		default:
			break;
		}

		/* ignored: auto behavior = am->getWaitingBehaviour(); */
	}
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
