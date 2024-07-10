/* -*- c++ -*-
 *
 * Converter/activityGraph.cpp
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 */
/** @file activityGraph.cpp
 * Groups all code related to Amalthea's ActivityGraph and ActivityGraphItems.
 *
 * The conversion concept is as follows:
 *
 * We know the current CallGraph, the current CallSequence and its end is the current
 * CallSequenceItem.
 *
 * All CallSequenceItems are appended to the current CallSequence, except as
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
 * Nested sm3::Switch and and sm3::ProbabilitySwitch instances are tracked
 * in a graphEntries deque.
 *
 */
#include "../AttributeCreator.h"
#include "../Diagnostic.h"
#include "../TimeOperators.h"
#include "Converter.h"
#include "StimulusTraits.h"

namespace am = am210::model;

namespace am210 {

namespace details {

/** Remove the CallSequence from its parent, if it is empty AND has no
 * Amalthea counterpart.
 */
bool isUnused( const sm3::CallSequence_ptr& cs, ObjectCache& oc ) {
	return cs->getCalls().size() == 0 && !oc.reverseFind<ecore::EObject_ptr>( cs );
}

/** Remove the CallSequence from its parent, if it is empty AND has no
 * Amalthea counterpart.
 */
void removeIfUnused( const sm3::CallSequence_ptr& cs, ObjectCache& oc ) {
	if ( isUnused( cs, oc ) ) {
		auto parent = cs->eContainer();
		auto ef = cs->eContainingFeature();

		auto any = parent->eGet( ef );
		ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type list =
			ecorecpp::mapping::any::any_cast<
				ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type>( any );

		list->remove( cs );
	}
}

/** addAsSibling() adds the younger value to the same relation as the older
 * value.
 *
 * It is used only in the context of new elements and may therefor use
 * push_back_unsafe(), which skips the uniqueness test for the new element.
 */
template<class T, class U>
void addAsSibling( const ecore::Ptr<T>& older, const ecore::Ptr<U>& younger ) {
	auto parent = older->eContainer();
	auto ef = older->eContainingFeature();

	auto any = parent->eGet( ef );
	ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type list =
		ecorecpp::mapping::any::any_cast<
			ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type>( any );

	list->push_back_unsafe( younger );
}

}  // namespace details


/** Translate an am::ActivityGraph into a sm3::CallGraph.
 *
 * Amalthea does not necessarily need a CallSequence, but in the INCHRON model
 * every CallSequenceItem must be contained by a CallSequence. Whenever
 * needed, CallSequences are created, and afterwards the helper methods
 * defined above detect and remove unnecessary instances.
 *
 * GraphEntries are tracked in a std::deque. The current CallSequence is
 * always at the end. When a Switch or another GraphEntry is processed, it
 * is added as sibling of the current end, and the newly created CallSequence
 * is appended to the std::deque. The postorder processing of the Switch
 * is responsible to not only cleanup empty CallSequences, but also remove it
 * from the std::deque.
 */
void Converter::work( const am::ActivityGraph_ptr& am, am::ActivityGraph* ) {
	if ( _mode == PreOrder ) {
		auto cg = _oc.make<sm3::ModelFactory, sm3::CallGraph>( am );
		auto parent =
			_oc.find<sm3::ModelObject>( am->eContainer(), ObjectCache::Default );
		if ( auto process = ecore::as<sm3::Process>( parent ) )
			process->setCallGraph( cg );
		else if ( auto runnable = ecore::as<sm3::Function>( parent ) )
			runnable->setCallGraph( cg );

		_csiCounter = 0u;
		_geCounter = 0u;

		auto cs = sm3::create<sm3::CallSequence>();
		setName( *cs );
		cg->getGraphEntries().push_back_unsafe( cs );

		_callGraph = cg;
		_callSequence = cs;
		assert( _graphEntries.empty() );
		_graphEntries.push_back( _callSequence );

	} else {
		details::removeIfUnused( _callSequence, _oc );

		_callGraph = sm3::CallGraph_ptr();
		_callSequence = sm3::CallSequence_ptr();
		_graphEntries.clear();
	}
}

void Converter::work( const am::Group_ptr& am, am::Group* ) {
	if ( _mode == PreOrder ) {
		auto cs = _callSequence;
		if ( details::isUnused( cs, _oc ) ) {
			_oc.add( am, ObjectCache::Default, cs );
			_oc.reverseAdd( am, cs );
		} else {
			cs = _oc.make<sm3::ModelFactory, sm3::CallSequence>( am );
			details::addAsSibling( _callSequence, cs );
			_callSequence = cs;
			_graphEntries.pop_back();
			_graphEntries.push_back( _callSequence );
		}

		cs->setName( am->getName() );
		if ( !am->isOrdered() ) {
			warning(
				QStringLiteral(
					"Unsupported attribute: Group '%1' uses random execution order." )
					.arg( QString::fromStdString( am->getName() ) ) );
		}

		/* A non-interruptible Group is emulated by added a
		 * SuspendAllInterrupts at the beginning and a ResumeAllInterrupts at
		 * the end [AM2INC-74]. Suspend- and ResumeAllInterrupts already
		 * handle nested interrupt locking. */
		if ( !am->isInterruptible() ) {
			auto suspend = sm3::create<sm3::SuspendAllInterrupts>();
			suspend->setName( "ImplicitSuspend_" + am->getName() );
			_callSequence->getCalls().push_back_unsafe( suspend );
		}

	} else {  // PostOrder
		/* A non-interruptible Group executes a ResumeAllInterrupts at the end
		 * [AM2INC-74]. Depending on the nesting of the interrupt locks, this
		 * might lead to immediate preemption. */
		if ( !am->isInterruptible() ) {
			auto resume = sm3::create<sm3::ResumeAllInterrupts>();
			resume->setName( "ImplicitResume_" + am->getName() );
			_callSequence->getCalls().push_back_unsafe( resume );
		}

		auto cs = sm3::create<sm3::CallSequence>();
		setName( *cs );
		details::addAsSibling( _callSequence, cs );
		_callSequence = cs;
		_graphEntries.pop_back();
		_graphEntries.push_back( _callSequence );
	}
}

void Converter::work( const am::LabelAccess_ptr& am, am::LabelAccess* ) {
	if ( _mode == PreOrder ) {
		auto rc = _oc.make<sm3::ModelFactory, sm3::ResourceConsumption>(
			am, ObjectCache::Default );
		_callSequence->getCalls().push_back_unsafe( rc );

		setName( *rc, "LabelAccess_" + am->getData()->getName() );
		auto access = _oc.make<sm3m::MemoryFactory, sm3m::ExplicitDataAccess>(
			am, ObjectCache::Sub1 );
		rc->getDataAccess().push_back_unsafe( access );
		access->setAccessType( am->getAccess() == am::LabelAccessEnum::write
								   ? sm3m::DataAccessType::Write
								   : sm3m::DataAccessType::Read );
		access->setDataObject(
			_oc.make<sm3m::MemoryFactory, sm3m::DataObject>( am->getData() ) );
		access->getBandwidth()->setValue( 0 );
	}
}

void Converter::work( const am::RunnableCall_ptr& am, am::RunnableCall* ) {
	if ( _mode == PreOrder ) {
		auto call = _oc.make<sm3::ModelFactory, sm3::FunctionCall>( am );
		_callSequence->getCalls().push_back_unsafe( call );

		call->setFunction(
			_oc.make<sm3::ModelFactory, sm3::Function>( am->getRunnable() ) );
		setName( *call, "Call_" + am->getRunnable()->getName() );
		if ( auto&& counter = am->getCounter() ) {
			call->setPeriod( counter->getPrescaler() );
			call->setOffset( counter->getOffset() );
		}
	}
}

void Converter::work( const am::InterProcessTrigger_ptr& am, am::InterProcessTrigger* ) {
	if ( _mode == PreOrder ) {
		auto act = _oc.make<sm3::ModelFactory, sm3::ActivationItem>( am );
		_callSequence->getCalls().push_back_unsafe( act );

		setName( *act, "InterProcessTrigger_" + am->getStimulus()->getName() );
		act->setConnection(
			_oc.make<sm3::ModelFactory, sm3::ActivationConnection>( am->getStimulus() ) );
		if ( auto&& counter = am->getCounter() ) {
			act->setPeriod( counter->getPrescaler() );
			act->setOffset( counter->getOffset() );
		}
	}
}

void Converter::work( const am::SetEvent_ptr& am, am::SetEvent* ) {
	if ( _mode == PreOrder ) {
		auto set = _oc.make<sm3::ModelFactory, sm3::SetEvent>( am );
		_callSequence->getCalls().push_back_unsafe( set );

		for ( auto&& amEvent : am->getEventMask()->getEvents() ) {
			auto event = _oc.make<sm3::ModelFactory, sm3::Event>( amEvent );
			set->setEvent( event );
			break;
		}
		if ( auto&& counter = am->getCounter() ) {
			set->setPeriod( counter->getPrescaler() );
			set->setOffset( counter->getOffset() );
		}
	}
}

void Converter::work( const am::WaitEvent_ptr& am, am::WaitEvent* ) {
	if ( _mode == PreOrder ) {
		auto wait = _oc.make<sm3::ModelFactory, sm3::WaitEvent>( am );
		_callSequence->getCalls().push_back_unsafe( wait );

		for ( auto&& amEvent : am->getEventMask()->getEvents() ) {
			auto event = _oc.make<sm3::ModelFactory, sm3::Event>( amEvent );
			wait->setEvent( event );
			break;
		}
		if ( auto&& counter = am->getCounter() ) {
			wait->setPeriod( counter->getPrescaler() );
			wait->setOffset( counter->getOffset() );
		}
	}
}

void Converter::work( const am::ClearEvent_ptr& am, am::ClearEvent* ) {
	if ( _mode == PreOrder ) {
		auto clear = _oc.make<sm3::ModelFactory, sm3::SetEvent>( am );
		clear->setReset( true );
		_callSequence->getCalls().push_back_unsafe( clear );

		for ( auto&& amEvent : am->getEventMask()->getEvents() ) {
			auto event = _oc.make<sm3::ModelFactory, sm3::Event>( amEvent );
			clear->setEvent( event );
			break;
		}
		if ( auto&& counter = am->getCounter() ) {
			clear->setPeriod( counter->getPrescaler() );
			clear->setOffset( counter->getOffset() );
		}
	}
}

/* IDiscreteValueDeviation is an interface class, which is implemented by
 * DiscreteValueConstant, DiscreteValueHistogram,
 *
 * BoundedDiscreteValueDistribution (ie. DiscreteValueBoundaries,
 * DiscreteValueStatistics, DiscreteValueUniformDistribution,
 * DiscreteValueWeibullEstimatorsDistribution, DiscreteValueBetaDistribution),
 *
 * and TruncatedDiscreteValueDistribution (ie. DiscreteValueGaussDistribution)
 */
sm3::TimeDistribution_ptr Converter::createTimeDistribution(
	const am::IDiscreteValueDeviation_ptr& am ) {
	auto td = sm3::create<sm3::TimeDistribution>();

	switch ( am->eClass()->getClassifierID() ) {
	case am::ModelPackage::DISCRETEVALUECONSTANT:
		td->setMin( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getLowerBound(),
																	 sm3::TimeUnit::T ) );
		td->setMax( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getUpperBound(),
																	 sm3::TimeUnit::T ) );
		td->setType( sm3::TimeDistributionType::Min );
		break;

	case am::ModelPackage::DISCRETEVALUEHISTOGRAM: {
		// Translate to DiscreteDistribution
		auto histo = ecore::as<am::DiscreteValueHistogram>( am );
		for ( auto&& entry : histo->getEntries() ) {
			// entry := DiscreteValueInterval + #occurrences
			auto dde = sm3::create<sm3::DiscreteDistributionEntry>();
			dde->setCount( entry->getOccurrences() );
			dde->setLower( AttributeCreator<sm3::Time, am::ModelPackage>()(
				entry->getLowerBound(), sm3::TimeUnit::T ) );
			dde->setUpper( AttributeCreator<sm3::Time, am::ModelPackage>()(
				entry->getUpperBound(), sm3::TimeUnit::T ) );
			td->getDiscreteDistribution().push_back_unsafe( dde );
		}
		td->setType( sm3::TimeDistributionType::Discrete );
	} break;

	case am::ModelPackage::DISCRETEVALUEBOUNDARIES: {
		/** This corresponds to the Amalthea Boundaries distribution (see 3.2.6.1 of the
		 * Amalthea documentation) which defines five sampling (sub-)types (scenarios).
		 * All these five scenarios are modeled by a Beta Distribution with scenario specific
		 * distribution parameters (fixed) Alpha and Beta.
		 * The free parameters of a scenario are a lower and an upper bound (see the
		 * am::BoundedTimeDistribution inherits from am::TimeInterval and the
		 * definition of the corresponding discrete value classes is analogous).
		 */
		auto bound = ecore::as<am::DiscreteValueBoundaries>( am );
		td->setMin( AttributeCreator<sm3::Time, am::ModelPackage>()(
			bound->getLowerBound(), sm3::TimeUnit::T ) );
		td->setMax( AttributeCreator<sm3::Time, am::ModelPackage>()(
			bound->getUpperBound(), sm3::TimeUnit::T ) );
		switch ( bound->getSamplingType() ) {
		case am::SamplingType::_default_: {
			/** _default_ implies (Amalthea class) Constant, which does not exist in the
			 * INCHRON model. We set it to type Mean (i.e. not a beta distribution) in order
			 * to clearly differentiate it from the five distinct "scenarios" of am::Boundaries. */
			td->setType( sm3::TimeDistributionType::Mean );
			/** Providing the mean value is mandatory.
			 * \note Rounding error due to integer truncation applies. */
			const auto mean = ( *td->getMax() - *td->getMin() ) / 2;
			td->setMean( AttributeCreator<sm3::Time, am::ModelPackage>()(
				mean.getValue(), sm3::TimeUnit::T ) );
		} break;
		case am::SamplingType::BestCase:
			td->setType( sm3::TimeDistributionType::BestCase );
			break;
		case am::SamplingType::WorstCase:
			td->setType( sm3::TimeDistributionType::WorstCase );
			break;
		case am::SamplingType::AverageCase:
			td->setType( sm3::TimeDistributionType::AverageCase );
			break;
		case am::SamplingType::CornerCase:
			td->setType( sm3::TimeDistributionType::CornerCase );
			break;
		case am::SamplingType::Uniform:
			td->setType( sm3::TimeDistributionType::Uniform );
			break;
		default:
			warning( QStringLiteral(
						 "Unsupported DiscreteValueBoundaries::samplingType '%1'." )
						 .arg( QString::fromStdString(
							 am::ModelPackage::_instance()
								 ->getSamplingType()
								 ->getEEnumLiteral( (int)bound->getSamplingType() )
								 ->getName() ) ) );
		}
	} break;

	case am::ModelPackage::DISCRETEVALUESTATISTICS: {
		auto stat = ecore::as<am::DiscreteValueStatistics>( am );
		auto avg = AttributeCreator<sm3::Time, am::ModelPackage>()( stat->getAverage(),
																	sm3::TimeUnit::T );
		auto min = AttributeCreator<sm3::Time, am::ModelPackage>()( stat->getLowerBound(),
																	sm3::TimeUnit::T );
		auto max = AttributeCreator<sm3::Time, am::ModelPackage>()( stat->getUpperBound(),
																	sm3::TimeUnit::T );

		/* In general it is not safe to handle EMF objects, which are not
		 * created on the heap and are not managed by a std::shared_ptr<>. */
		auto dl = root::model::create<root::model::Time>();
		auto du = root::model::create<root::model::Time>();
		auto sigma = root::model::create<root::model::Time>();

		*dl = *avg - *min;
		*du = *max - *avg;
		if ( *dl > *du )
			*sigma = *dl / 3;
		else
			*sigma = *du / 3;

		td->setMin( min );
		td->setMax( max );
		td->setMean( avg );
		td->setSigma( sigma );
		td->setType( sm3::TimeDistributionType::Normal );
	} break;

	case am::ModelPackage::DISCRETEVALUEUNIFORMDISTRIBUTION: {
		td->setMin( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getLowerBound(),
																	 sm3::TimeUnit::T ) );
		td->setMax( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getUpperBound(),
																	 sm3::TimeUnit::T ) );
		td->setType( sm3::TimeDistributionType::Uniform );
	} break;

	case am::ModelPackage::DISCRETEVALUEGAUSSDISTRIBUTION: {
		td->setMin( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getLowerBound(),
																	 sm3::TimeUnit::T ) );
		td->setMax( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getUpperBound(),
																	 sm3::TimeUnit::T ) );
		auto gauss = ecore::as<am::DiscreteValueGaussDistribution>( am );
		td->setMean( AttributeCreator<sm3::Time, am::ModelPackage>()(
			gauss->getMean(), sm3::TimeUnit::T ) );
		td->setSigma( AttributeCreator<sm3::Time, am::ModelPackage>()(
			gauss->getSd(), sm3::TimeUnit::T ) );
		td->setType( sm3::TimeDistributionType::Normal );
	} break;

	case am::ModelPackage::DISCRETEVALUEWEIBULLESTIMATORSDISTRIBUTION: {
		td->setMin( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getLowerBound(),
																	 sm3::TimeUnit::T ) );
		td->setMax( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getUpperBound(),
																	 sm3::TimeUnit::T ) );
		auto stat = ecore::as<am::DiscreteValueWeibullEstimatorsDistribution>( am );
		td->setMean( AttributeCreator<sm3::Time, am::ModelPackage>()(
			stat->getAverage(), sm3::TimeUnit::T ) );
		/* OutlierProbability has to be in the range ]0..1]. */
		double outlier = stat->getPRemainPromille() / 1000.;
		if ( outlier <= 0. )
			outlier = .001;
		td->setOutlierProbability( outlier );
		td->setType( sm3::TimeDistributionType::WeibullEstimator );

	} break;

	case am::ModelPackage::DISCRETEVALUEBETADISTRIBUTION: {
		td->setMin( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getLowerBound(),
																	 sm3::TimeUnit::T ) );
		td->setMax( AttributeCreator<sm3::Time, am::ModelPackage>()( am->getUpperBound(),
																	 sm3::TimeUnit::T ) );
		const auto stat = ecore::as<am::DiscreteValueBetaDistribution>( am );
		td->setAlpha( stat->getAlpha() );
		td->setBeta( stat->getBeta() );
	} break;
	}

	ModelChecker<sm3::TimeDistribution>().work( td );
	return td;
}

void Converter::work( const am::Ticks_ptr& am, am::Ticks* ) {
	if ( _mode == PreOrder ) {
		auto consumption = _oc.make<sm3::ModelFactory, sm3::ResourceConsumption>( am );
		setName( *consumption, "Tick" );
		_callSequence->getCalls().push_back_unsafe( consumption );

		auto value = am->getDefault();
		if ( !value ) {
			if ( Diagnostic::ObjectRequired::notEmpty( this, am->getExtended() ) )
				value = am->getExtended().get( 0 )->getValue();
		}

		if ( Diagnostic::ObjectRequired::exists( this, value ) )
			consumption->setTimeDistribution( createTimeDistribution( value ) );
	}
}

void Converter::work( const am::ChannelReceive_ptr&, am::ChannelReceive* ) {
	static Diagnostic::NotImplemented<am::ChannelReceive> message( this );
}

void Converter::work( const am::ChannelSend_ptr&, am::ChannelSend* ) {
	static Diagnostic::NotImplemented<am::ChannelSend> message( this );
}

void Converter::work( const am::CustomEventTrigger_ptr&, am::CustomEventTrigger* ) {
	static Diagnostic::NotImplemented<am::CustomEventTrigger> message( this );
}

void Converter::work( const am::EnforcedMigration_ptr&, am::EnforcedMigration* ) {
	static Diagnostic::NotImplemented<am::EnforcedMigration> message( this );
}

void Converter::work( const am::ExecutionNeed_ptr&, am::ExecutionNeed* ) {
	static Diagnostic::NotImplemented<am::ExecutionNeed> message( this );
}

void Converter::work( const am::GetResultServerCall_ptr&, am::GetResultServerCall* ) {
	static Diagnostic::NotImplemented<am::GetResultServerCall> message( this );
}

void Converter::work( const am::ModeLabelAccess_ptr& am, am::ModeLabelAccess* ) {
	if ( _mode == PreOrder ) {
		if ( auto&& enumMode = ecore::as<am::EnumMode>( am->getData()->getMode() ) ) {
			/* A ModeLabelAccess for an EnumMode is translated to a ModeSwitchPoint. */
			if ( am->getAccess() == am::ModeLabelAccessEnum::set ) {
				auto modeGroup = createModeGroup( am->getData() );
				for ( auto&& literal : enumMode->getLiterals() ) {
					if ( am->getValue() == literal->getName() ) {
						for ( const auto&& mode : modeGroup->getModes() ) {
							if ( literal->getName() == mode->getName() ) {
								auto modeSwitchPoint =
									_oc.make<sm3::ModelFactory, sm3::ModeSwitchPoint>(
										am );
								setName( *modeSwitchPoint, "EnumModeLabelAccess" );
								modeSwitchPoint->setMode( mode );
								_callSequence->getCalls().push_back_unsafe(
									modeSwitchPoint );
								break;
							}
						}
						break;
					}
				}
			}

		} else if ( auto&& numericMode =
						ecore::as<am::NumericMode>( am->getData()->getMode() ) ) {
			/* A ModeLabelAccess for a NumericMode is translated to a CounterModification. */
			if ( am->getAccess() == am::ModeLabelAccessEnum::increment
				 or am->getAccess() == am::ModeLabelAccessEnum::decrement
				 or am->getAccess() == am::ModeLabelAccessEnum::set ) {
				auto counter = createCounter( am->getData() );
				auto counterModification =
					_oc.make<sm3::ModelFactory, sm3::CounterModification>( am );
				setName( *counterModification, "NumericModeLabelAccess" );
				counterModification->setCounter( counter );
				if ( am->getAccess() == am::ModeLabelAccessEnum::increment )
					counterModification->setType(
						sm3::CounterModificationType::Increment );
				else if ( am->getAccess() == am::ModeLabelAccessEnum::decrement )
					counterModification->setType(
						sm3::CounterModificationType::Decrement );
				else if ( am->getAccess() == am::ModeLabelAccessEnum::set )
					counterModification->setType( sm3::CounterModificationType::Set );
				counterModification->setValue( am->getStep() );
				_callSequence->getCalls().push_back_unsafe( counterModification );
			}
		}

	} else {
	}

	/* FIXME? We could also create a an additional conventional
	 * DataAccess for the memory subsystem. */
}

template<class C>
void Converter::workSwitch( const ecore::Ptr<C>& am ) {
	if ( _mode == PreOrder ) {
		auto modeSwitch = _oc.make<sm3::ModelFactory, sm3::Switch>( am );
		setName( *modeSwitch );
		modeSwitch->setEvaluateConditionsOnEntry( true );
		details::addAsSibling( _callSequence, modeSwitch );
		details::removeIfUnused( _callSequence, _oc );

		/* The end of this am::ModeSwitch, any am::ModeSwitchEntry and an
		 * am::ModeSwitchDefault will lead to the creation of a new
		 * CallSequence. */
		_callSequence = sm3::CallSequence_ptr();

		_switchEntryCounter.push( 0u );

	} else {
		/* A new CallSequence starts after the ModeSwitch. It replaces the
		 * previous one. */
		_callSequence = sm3::create<sm3::CallSequence>();
		setName( *_callSequence );
		auto thisModeSwitch = _oc.make<sm3::ModelFactory, sm3::Switch>( am );
		details::addAsSibling( thisModeSwitch, _callSequence );
		_graphEntries.pop_back();
		_graphEntries.push_back( _callSequence );

		_switchEntryCounter.pop();
	}
}

void Converter::work( const am::ModeSwitch_ptr& am, am::ModeSwitch* ) {
	workSwitch( am );
}

void Converter::work( const am::Switch_ptr& am, am::Switch* ) { workSwitch( am ); }

template<class C>
void Converter::workSwitchDefault( const ecore::Ptr<C>& am ) {
	if ( _mode == PreOrder ) {
		auto msd = _oc.make<sm3::ModelFactory, sm3::SwitchDefault>( am );
		auto modeSwitch = _oc.make<sm3::ModelFactory, sm3::Switch>( am->eContainer() );
		modeSwitch->setDefaultEntry( msd );

		auto cs = sm3::create<sm3::CallSequence>();
		setName( *cs );
		msd->getGraphEntries().push_back_unsafe( cs );
		_graphEntries.push_back( cs );
		_callSequence = cs;

	} else {
		details::removeIfUnused( _callSequence, _oc );
		_callSequence = sm3::CallSequence_ptr();
		_graphEntries.pop_back();
	}
}

void Converter::work( const am::ModeSwitchDefault_ptr& am, am::ModeSwitchDefault* ) {
	workSwitchDefault( am );
}

void Converter::work( const am::SwitchDefault_ptr& am, am::SwitchDefault* ) {
	workSwitchDefault( am );
}

template<class C>
void Converter::workSwitchEntry( const ecore::Ptr<C>& am ) {
	if ( _mode == PreOrder ) {
		auto mse = _oc.make<sm3::ModelFactory, sm3::SwitchEntry>( am );
		setName( *mse );
		auto modeSwitch = _oc.make<sm3::ModelFactory, sm3::Switch>( am->eContainer() );
		assert( modeSwitch );
		modeSwitch->getEntries().push_back_unsafe( mse );

		auto condition =
			_oc.make<sm3::ModelFactory, sm3::Condition>( am->getCondition() );
		mse->setCondition( condition );

		auto cs = sm3::create<sm3::CallSequence>();
		setName( *cs );
		mse->getGraphEntries().push_back_unsafe( cs );
		_graphEntries.push_back( cs );
		_callSequence = cs;

	} else {
		details::removeIfUnused( _callSequence, _oc );
		_callSequence = sm3::CallSequence_ptr();
		_graphEntries.pop_back();
	}
}

void Converter::work( const am::ModeSwitchEntry_ptr& am, am::ModeSwitchEntry* ) {
	workSwitchEntry( am );
}

void Converter::work( const am::SwitchEntry_ptr& am, am::SwitchEntry* ) {
	workSwitchEntry( am );
}

void Converter::work( const am::ProbabilitySwitch_ptr& am, am::ProbabilitySwitch* ) {
	if ( _mode == PreOrder ) {
		auto probSwitch = _oc.make<sm3::ModelFactory, sm3::ProbabilitySwitch>( am );
		setName( *probSwitch );
		details::addAsSibling( _callSequence, probSwitch );
		details::removeIfUnused( _callSequence, _oc );

		/* The end of this am::ProbabilitySwitch, and any
		 * am::ProbabilitySwitchEntry will lead to the creation of a new
		 * CallSequence. */
		_callSequence = sm3::CallSequence_ptr();

		_switchEntryCounter.push( 0u );

	} else {
		/* A new CallSequence starts after the ProbalitySwitch. It replaces
		 * the previous one. */
		_callSequence = sm3::create<sm3::CallSequence>();
		setName( *_callSequence );
		auto thisProbSwitch = _oc.make<sm3::ModelFactory, sm3::ProbabilitySwitch>( am );
		details::addAsSibling( thisProbSwitch, _callSequence );
		_graphEntries.pop_back();
		_graphEntries.push_back( _callSequence );

		_switchEntryCounter.pop();
	}
}

void Converter::work( const am::ProbabilitySwitchEntry_ptr& am,
					  am::ProbabilitySwitchEntry* ) {
	if ( _mode == PreOrder ) {
		auto pse = _oc.make<sm3::ModelFactory, sm3::ProbabilitySwitchEntry>( am );
		setName( *pse );
		auto probSwitch =
			_oc.make<sm3::ModelFactory, sm3::ProbabilitySwitch>( am->eContainer() );
		assert( probSwitch );
		probSwitch->getEntries().push_back_unsafe( pse );

		auto probability = am->getProbability();
		pse->setProbability( probability );

		auto cs = sm3::create<sm3::CallSequence>();
		setName( *cs );
		pse->getGraphEntries().push_back_unsafe( cs );
		_graphEntries.push_back( cs );
		_callSequence = cs;

	} else {
		details::removeIfUnused( _callSequence, _oc );
		_callSequence = sm3::CallSequence_ptr();
		_graphEntries.pop_back();
	}
}

void Converter::work( const am::WhileLoop_ptr& am, am::WhileLoop* ) {
	if ( _mode == PreOrder ) {
		auto wloop = _oc.make<sm3::ModelFactory, sm3::WhileLoop>( am );
		details::addAsSibling( _callSequence, wloop );
		details::removeIfUnused( _callSequence, _oc );

		auto condition =
			_oc.make<sm3::ModelFactory, sm3::Condition>( am->getCondition() );
		wloop->setCondition( condition );

		auto cs = sm3::create<sm3::CallSequence>();
		wloop->getGraphEntries().push_back_unsafe( cs );
		_callSequence = cs;

	} else {  // PostOrder
		details::removeIfUnused( _callSequence, _oc );

		/* A new CallSequence starts after the WhileLoop. It replaces
		 * the previous one. */
		_callSequence = sm3::create<sm3::CallSequence>();
		setName( *_callSequence );
		auto thisWhileLoop = _oc.make<sm3::ModelFactory, sm3::WhileLoop>( am );
		details::addAsSibling( thisWhileLoop, _callSequence );
		_graphEntries.pop_back();
		_graphEntries.push_back( _callSequence );
	}
}

void Converter::work( const am::SchedulePoint_ptr& am, am::SchedulePoint* ) {
	if ( _mode == PreOrder ) {
		auto sp = _oc.make<sm3::ModelFactory, sm3::SchedulePoint>( am );
		setName( *sp );
		_callSequence->getCalls().push_back_unsafe( sp );
	}
}

void Converter::work( const am::SemaphoreAccess_ptr& am, am::SemaphoreAccess* ) {
	if ( _mode == PreOrder ) {
		auto access = _oc.make<sm3::ModelFactory, sm3::SemaphoreAccess>( am );
		_callSequence->getCalls().push_back_unsafe( access );

		auto theSemaphore = am->getSemaphore();
		if ( theSemaphore ) {
			setName( *access, "SemaphoreAccess_" + theSemaphore->getName() );
			auto semaphore = _oc.make<sm3::ModelFactory, sm3::Semaphore>( theSemaphore );
			access->setSemaphore( semaphore );
		}

		auto type = am->getAccess();
		switch ( type ) {
		case am::SemaphoreAccessEnum::request:
			access->setType( sm3::SemaphoreAccessType::Request );
			break;
		case am::SemaphoreAccessEnum::exclusive:
			access->setType( sm3::SemaphoreAccessType::Exclusive );
			break;
		case am::SemaphoreAccessEnum::release:
			access->setType( sm3::SemaphoreAccessType::Release );
			break;
		default:
			break;
		}

		/* ignored: auto behavior = am->getWaitingBehaviour(); */
	}
}

void Converter::work( const am::SenderReceiverRead_ptr&, am::SenderReceiverRead* ) {
	static Diagnostic::NotImplemented<am::SenderReceiverRead> message( this );
}

void Converter::work( const am::SenderReceiverWrite_ptr&, am::SenderReceiverWrite* ) {
	static Diagnostic::NotImplemented<am::SenderReceiverWrite> message( this );
}

void Converter::work( const am::SynchronousServerCall_ptr&, am::SynchronousServerCall* ) {
	static Diagnostic::NotImplemented<am::SynchronousServerCall> message( this );
}

void Converter::work( const am::TerminateProcess_ptr&, am::TerminateProcess* ) {
	static Diagnostic::NotImplemented<am::TerminateProcess> message( this );
}

}  // namespace am210
