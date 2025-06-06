/* -*- c++ -*-
 *
 * Converter/swModel.cpp
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 */
/** @file swModel.cpp
 * Groups all code related to Amalthea's SwModel.
 */
#include "../AttributeCreator.h"
#include "../Diagnostic.h"
#include "Converter.h"
#include "StimulusTraits.h"

namespace am = am220::model;

namespace am220 {

/** Add an sm3::ActivateProcess to the CallGraph of all am::Stimulus, which
 * are referenced by the am::Process.
 *
 * Amalthea defines a derived feature Stimulus::affectedProcesses, which is
 * not (yet) implemented in C++. Hence, the logic goes from the Process to the
 * Stimulus.
 */
void Converter::addStimulus( const am::Process_ptr& am,
							 const sm3::Process_ptr& process ) {
	for ( auto&& stimulus : am->getStimuli() ) {
		auto gen = _oc.find<sm3s::StimuliGenerator>( stimulus, ObjectCache::Default );
		auto conn = _oc.find<sm3::Connection>( stimulus, ObjectCache::Default );

		if ( !gen && !conn ) {
			const auto id = stimulus->eClass()->getClassifierID();
			switch ( id ) {
			case am::ModelPackage::ARRIVALCURVESTIMULUS:
			case am::ModelPackage::CUSTOMSTIMULUS:
			case am::ModelPackage::EVENTSTIMULUS:
			case am::ModelPackage::VARIABLERATESTIMULUS:
				/* unsupported */
				return;

			case am::ModelPackage::INTERPROCESSSTIMULUS:
				conn = _oc.make<sm3::ModelFactory, sm3::ActivationConnection>( stimulus );
				break;

			case am::ModelPackage::PERIODICBURSTSTIMULUS:
				gen =
					_oc.make<sm3s::StimulationFactory,
							 StimulusTrait<am::PeriodicBurstStimulus>::type>( stimulus );
				break;
			case am::ModelPackage::PERIODICSTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::PeriodicStimulus>::type>( stimulus );
				break;
			case am::ModelPackage::PERIODICSYNTHETICSTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::PeriodicSyntheticStimulus>::type>(
					stimulus );
				break;
			case am::ModelPackage::RELATIVEPERIODICSTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::RelativePeriodicStimulus>::type>(
					stimulus );
				break;
			case am::ModelPackage::SINGLESTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::SingleStimulus>::type>( stimulus );
				break;
			}
		}

		auto activationAction = sm3::create<sm3::ActivateProcess>();
		activationAction->setName( std::string( "Activate" ) + process->getName() );
		activationAction->setTarget( process );

		sm3::CallGraph_ptr callGraph;
		if ( gen ) {
			callGraph = gen->getTargets();
			if ( !callGraph ) {
				callGraph = sm3::create<sm3::CallGraph>();
				gen->setTargets( callGraph );
			}
		} else {
			callGraph = conn->getCallGraph();
			if ( !callGraph ) {
				callGraph = sm3::create<sm3::CallGraph>();
				conn->setCallGraph( callGraph );
			}
		}

		sm3::CallSequence_ptr callSequence;
		if ( callGraph->getGraphEntries().size() == 0 ) {
			if ( auto&& cond = stimulus->getExecutionCondition() ) {
				auto modeSwitch = sm3::create<sm3::Switch>();
				callGraph->getGraphEntries().push_back_unsafe( modeSwitch );
				setName( *modeSwitch );
				modeSwitch->setEvaluateConditionsOnEntry( true );

				_switchEntryCounter.push( 0u );
				auto modeSwitchEntry = sm3::create<sm3::SwitchEntry>();
				modeSwitch->getEntries().push_back_unsafe( modeSwitchEntry );
				setName( *modeSwitchEntry );
				_switchEntryCounter.pop();
				modeSwitchEntry->setCondition(
					_oc.make<sm3::ModelFactory, sm3::Condition>( cond ) );

				callSequence = sm3::create<sm3::CallSequence>();
				modeSwitchEntry->getGraphEntries().push_back_unsafe( callSequence );
				setName( *callSequence );

			} else {
				callSequence = sm3::create<sm3::CallSequence>();
				callGraph->getGraphEntries().push_back_unsafe( callSequence );
				setName( *callSequence );
			}
		} else {
			if ( auto&& cond = stimulus->getExecutionCondition() ) {
				auto modeSwitch =
					ecore::as<sm3::Switch>( callGraph->getGraphEntries().get( 0 ) );
				auto modeSwitchEntry =
					ecore::as<sm3::SwitchEntry>( modeSwitch->getEntries().get( 0 ) );
				callSequence = ecore::as<sm3::CallSequence>(
					modeSwitchEntry->getGraphEntries().get( 0 ) );

			} else {
				callSequence =
					ecore::as<sm3::CallSequence>( callGraph->getGraphEntries().get( 0 ) );
			}
		}

		callSequence->getCalls().push_back_unsafe( activationAction );

		if ( auto ips = ecore::as<am::InterProcessStimulus>( stimulus ) ) {
			if ( auto&& counter = ips->getCounter() ) {
				activationAction->setPeriod( counter->getPrescaler() );
				activationAction->setOffset( counter->getOffset() );
			}
		}
	}
}

void Converter::work( const am::ISR_ptr& am, am::ISR* ) {
	if ( _mode == PreOrder ) {
		auto process = _oc.make<sm3::ModelFactory, sm3::Process>( am );
		process->setIsr( true );
		process->setName( am->getName() );
		addEvents( process );
		addStimulus( am, process );
	}
}

void Converter::work( const am::OsEvent_ptr& am, am::OsEvent* ) {
	if ( _mode == PreOrder ) {
		auto event = _oc.make<sm3::ModelFactory, sm3::Event>( am );
		event->setName( am->getName() );
	}
}

void Converter::work( const am::Label_ptr& am, am::Label* ) {
	if ( _mode == PreOrder ) {
		auto dataObject = _oc.make<sm3m::MemoryFactory, sm3m::DataObject>( am );
		dataObject->setName( am->getName() );
		dataObject->setSize(
			AttributeCreator<sm3::DataSize, am::ModelPackage>()( am->getSize() ) );
		addEvents( dataObject );
	}
}

void Converter::work( const am::Runnable_ptr& am, am::Runnable* ) {
	if ( _mode == PreOrder ) {
		auto run = _oc.make<sm3::ModelFactory, sm3::Function>( am );
		run->setName( am->getName() );
		addEvents( run );
	}
}

namespace details {

bool isPreemptable( const am::Task_ptr& am ) {
	switch ( am->getPreemption() ) {
	default:
	case am::Preemption::_undefined_:
	case am::Preemption::preemptive:
		return true;
	case am::Preemption::cooperative:
	case am::Preemption::non_preemptive:
		return false;
	}
}

}  // namespace details

void Converter::work( const am::Task_ptr& am, am::Task* ) {
	if ( _mode == PreOrder ) {
		auto process = _oc.make<sm3::ModelFactory, sm3::Process>( am );
		process->setName( am->getName() );
		process->setPreemptable( details::isPreemptable( am ) );
		process->setActivationLimit(
			std::max( 1, am->getMultipleTaskActivationLimit() ) );
		addEvents( process );
		addStimulus( am, process );

	} else {
		auto process = _oc.find<sm3::Process>( am, ObjectCache::Default );
		if ( not process->getCallGraph() ) {
			/* Process.callGraph is a [0..1] relation, however chronSUITE's
			 * semantic check thinks it is an error. */
			auto callGraph = sm3::create<sm3::CallGraph>();
			process->setCallGraph( callGraph );
			ModelChecker<sm3::CallGraph>().work( callGraph );
		}
	}
}

/** Create and initialize a sm3::ModeGroup from an am::ModeLabel with a
 * modeDefinition of type am::EnumMode.
 *
 * The EnumMode literals are copied from the am::EnumMode (which can be
 * referenced by many am::ModeLabels) to the sm3::ModeGroup (which represents
 * the current value AND the literals).
 *
 * This method is called from both the methods work(const am::ModeLabel_ptr&)
 * and details::createRelationalExpression(). The new ModeGroup is only
 * created and initialized if it does not exist, hence the order does not
 * matter.
 */
sm3::ModeGroup_ptr Converter::createModeGroup( const am::ModeLabel_ptr& label ) {
	if ( auto ptr = _oc.find<sm3::ModeGroup>( label, ObjectCache::Default ) )
		return ptr;

	auto modeDefinition = label->getMode();
	auto enumMode = ecore::as<am::EnumMode>( modeDefinition );

	auto modeGroup = _oc.make<sm3::ModelFactory, sm3::ModeGroup>( label );
	modeGroup->setName( label->getName() );

	sm3::Mode_ptr initialMode;
	for ( auto&& literal : enumMode->getLiterals() ) {
		auto mode = sm3::create<sm3::Mode>();
		mode->setName( literal->getName() );
		modeGroup->getModes().push_back_unsafe( mode );
		if ( literal->getName() == label->getInitialValue() )
			initialMode = mode;
	}

	modeGroup->setInitialMode( initialMode );

	return modeGroup;
}

/** Create and initialize a sm3::Counter from an an::ModeLabel with a
 * modeDefinition of type am::NumericMode.
 *
 * This method is called from both the methods work(const am::ModeLabel_ptr&)
 * and details::createRelationalExpression(). The new Counter is only created
 * and initialized if it does not exist, hence the order does not matter.
 */
sm3::Counter_ptr Converter::createCounter( const am::ModeLabel_ptr& label ) {
	if ( auto ptr = _oc.find<sm3::Counter>( label, ObjectCache::Default ) )
		return ptr;

	auto modeDefinition = label->getMode();
	auto numericMode = ecore::as<am::NumericMode>( modeDefinition );

	auto counter = _oc.make<sm3::ModelFactory, sm3::Counter>( label );
	counter->setName( label->getName() );

	auto initialValue = 0;
	if ( !label->getInitialValue().empty() ) {
		try {
			initialValue = std::stoi( label->getInitialValue() );
		} catch ( ... ) {
			warning( QStringLiteral( "Cannot convert initial value of NumericMode-Label "
									 "'%1' to an integer value." )
						 .arg( QString::fromStdString( label->getName() ) ) );
		}
	}
	counter->setInitialValue( initialValue );

	return counter;
}

/** Each am::ModeLabel translates either to a sm3::ModeGroup or to a
 * sm3::Counter, depending on the type of the reference Mode.
 *
 * Note that the objects are added to the Model (on a global level). In
 * Amalthea they are first-level children of the SwModel. However, Runnables
 * are first-level children of the SwModel, too, but in the INCHRON model they
 * are required to contained in a Component, hence relax() creates a helper
 * Component if needed.
 */
void Converter::work( const am::ModeLabel_ptr& label, am::ModeLabel* ) {
	if ( _mode == PreOrder ) {
		auto modeDefinition = label->getMode();
		if ( !modeDefinition ) {
			warning(
				QStringLiteral( "Ignoring ModeLabel '%1' without reference to a Mode." )
					.arg( QString::fromStdString( label->getName() ) ) );
			return;
		}

		if ( auto enumMode = ecore::as<am::EnumMode>( modeDefinition ) ) {
			auto modeGroup = createModeGroup( label );
			_model->getGlobalModeGroups().push_back_unsafe( modeGroup );

		} else if ( modeDefinition->eClass()
					== am::ModelPackage::_instance()->getNumericMode() ) {
			/* The am::NumericMode does not have any additional parameters, so
			 * the default values of a sm3::Counter are used. */
			auto counter = createCounter( label );
			_model->getGlobalCounters().push_back_unsafe( counter );
		}
	}
}

/** An am::EnumMode is translated into a new sm3::ModeGroup for each
 * am::ModeLabel, which refers to it.
 *
 * \sa work(const am::ModeLabel_ptr&, ...)
 */
void Converter::work( const am::EnumMode_ptr& am, am::EnumMode* ) { skipChildren(); }

/** An am::EnumMode is translated into a new sm3::Counter for each
 * am::ModeLabel, which refers to it.
 *
 * \sa work(const am::ModeLabel_ptr&, ...)
 */
void Converter::work( const am::NumericMode_ptr&, am::NumericMode* ) { skipChildren(); }

template<class C>
root::model::RelationalExpression_ptr Converter::createRelationalExpression(
	const ecore::Ptr<C>& am ) {
	sm3::RelationalExpression_ptr expression;

	if ( auto mvc = ecore::as<am::ModeValueCondition>( am ) ) {
		/* Compare one am::ModeLabel -> sm::ModeGroup | sm3::Counter against a
		 * (string) value. */
		auto label = mvc->getLabel();
		if ( ecore::as<am::EnumMode>( label->getMode() ) ) {
			/* EnumMode */
			auto sm3 = sm3::create<sm3::ModeGroupExpression>();
			auto modeGroup = createModeGroup( label );
			sm3->setModeGroup( modeGroup );

			std::string value = mvc->getValue();
			for ( const auto&& mode : modeGroup->getModes() )
				if ( mode->getName() == value )
					sm3->setValue( mode );

			expression = sm3;

		} else {
			/* NumericMode */
			auto sm3 = sm3::create<sm3::ValueExpression>();
			auto counter = createCounter( label );
			sm3->setValue( counter );

			auto value = 0;
			try {
				value = std::stoi( mvc->getValue() );
			} catch ( ... ) {
				warning(
					QStringLiteral( "Cannot convert value of ModeValueCondition with a "
									"NumericMode-Label '%1' to an integer value." )
						.arg( QString::fromStdString( label->getName() ) ) );
			}
			sm3->setConstant( value );

			expression = sm3;
		}

	} else if ( auto mlc = ecore::as<am::ModeLabelCondition>( am ) ) {
		/* Compare two am::ModeLabel -> sm::ModeGroup | sm3::Counter against
		 * each other. */
		auto label1 = mlc->getLabel1();
		if ( ecore::as<am::EnumMode>( label1->getMode() ) ) {
			/* EnumMode */
			auto sm3 = sm3::create<sm3::ModeGroupComparison>();
			auto modeGroup1 = createModeGroup( label1 );
			sm3->setModeGroup1( modeGroup1 );

			auto label2 = mlc->getLabel2();
			if ( ecore::as<am::EnumMode>( label2->getMode() ) ) {
				auto modeGroup2 = createModeGroup( label2 );
				sm3->setModeGroup2( modeGroup2 );
			} else {
				warning( QStringLiteral( "Cannot compare ModeGroup and Counter: Ignoring "
										 "'%1' used as label2." )
							 .arg( QString::fromStdString( label2->getName() ) ) );
			}

			expression = sm3;

		} else {
			/* NumericMode */
			auto sm3 = sm3::create<sm3::ValueComparison>();
			auto counter1 = createCounter( label1 );
			sm3->setValue1( counter1 );

			auto label2 = mlc->getLabel2();
			if ( ecore::as<am::NumericMode>( label2->getMode() ) ) {
				auto counter2 = createCounter( label2 );
				sm3->setValue2( counter2 );
			} else {
				warning( QStringLiteral( "Cannot compare ModeGroup and Counter: Ignoring "
										 "'%1' used as label2." )
							 .arg( QString::fromStdString( label2->getName() ) ) );
			}

			expression = sm3;
		}

	} else if ( auto mc = ecore::as<am::ModeCondition>( am ) ) {
		auto relation = mc->getRelation();
		switch ( relation ) {
		default:
		case am::RelationalOperator::EQUAL:
			expression->setRelationalOperator( sm3::RelationalOperator::eq );
			break;
		case am::RelationalOperator::NOT_EQUAL:
			expression->setRelationalOperator( sm3::RelationalOperator::ne );
			break;
		case am::RelationalOperator::LESS_THAN:
			expression->setRelationalOperator( sm3::RelationalOperator::lt );
			break;
		case am::RelationalOperator::GREATER_THAN:
			expression->setRelationalOperator( sm3::RelationalOperator::gt );
			break;
		}
	}

	// auto expression = sm3::create<sm3::CounterExpression>();
	// auto expression = sm3::create<sm3::ModeGroupExpression>();

	return expression;
}

/** An am::ModeConditionDisjunction is aggregated by an am::ModeSwitchEntry::condition,
 * an am::Stimulus::executionCondition, am::Runnable::executionCondition or an
 * am::WhileLoop::condition. In general, it is translated into a sm3::ModeCondition,
 * which is aggregated by the Model.
 */
template<class C>
void Converter::workConditionDisjunction( const ecore::Ptr<C>& am ) {
	if ( _mode == PreOrder ) {
		auto condition = _oc.make<sm3::ModelFactory, sm3::Condition>( am );
		setName( *condition );
		_model->getGlobalConditions().push_back_unsafe( condition );

		/* 1..* ModeConditionDisjunctionEntry interface -> ModeCondition interface ->
		 * ModeValueCondition
		 * ModeLabelCondition */
		for ( auto&& entry : am->getEntries() ) {
			if ( auto amModeCondition = ecore::as<am::ModeCondition>( entry ) ) {
				/* Wrap the am::ModeCondition into a sm3::RelationalExpression
				 * and a sm3::ModeConjunction, then add it to the
				 * sm3::ModeCondition. */
				auto conjunction = sm3::create<sm3::Conjunction>();
				auto expression = createRelationalExpression( amModeCondition );
				conjunction->getExpressions().push_back_unsafe( expression );
				condition->getConjunctions().push_back_unsafe( conjunction );

			} else if ( auto amMcConjunction =
							ecore::as<am::ModeConditionConjunction>( entry ) ) {
				/* Create a sm3::ModeConjunction and add all the
				 * am::ModeConditions as sm3::RelationalExpressions to it. */
				auto conjunction = sm3::create<sm3::Conjunction>();
				for ( auto&& amModeCondition : amMcConjunction->getEntries() ) {
					auto expression = createRelationalExpression( amModeCondition );
					conjunction->getExpressions().push_back_unsafe( expression );
				}
				condition->getConjunctions().push_back_unsafe( conjunction );
			}
		}

	} else {
	}

	skipChildren();
}

void Converter::work( const am::ModeConditionDisjunction_ptr& am,
					  am::ModeConditionDisjunction* ) {
	workConditionDisjunction( am );
}

void Converter::work( const am::ConditionDisjunction_ptr& am,
					  am::ConditionDisjunction* ) {
	workConditionDisjunction( am );
}

void Converter::work( const am::LocalModeLabel_ptr&, am::LocalModeLabel* ) {
	static Diagnostic::NotImplemented<am::LocalModeLabel> message( this );
}

void Converter::work( const am::ProcessPrototype_ptr&, am::ProcessPrototype* ) {
	skipChildren();
}

}  // namespace am220
