/* -*- c++ -*-
 *
 * Converter/swModel.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file swModel.cpp
 * Groups all code related to Amalthea's SwModel.
 */
#include "../Converter.h"

#include "../AttributeCreator.h"
#include "../Diagnostic.h"
#include "../StimulusTraits.h"


/** Add an sm3::ActivateProcess to the CallGraph of all am::Stimulus, which
 * are referenced by the am::Process.
 *
 * Amalthea defines a derived feature Stimulus::affectedProcesses, which is
 * not (yet) implemented in C++. Hence, the logic goes from the Process to the
 * Stimulus.
 */
void Converter::addStimulus(const am::Process_ptr& am, const sm3::Process_ptr& process) {
	for (auto&& stimulus : am->getStimuli()) {
		auto gen = _oc.find<sm3s::StimuliGenerator>(stimulus, ObjectCache::Default);
		auto conn = _oc.find<sm3::Connection>(stimulus, ObjectCache::Default);

		if (!gen && !conn) {
			const auto id = stimulus->eClass()->getClassifierID();
			switch (id) {
			case am::ModelPackage::ARRIVALCURVESTIMULUS:
			case am::ModelPackage::CUSTOMSTIMULUS:
			case am::ModelPackage::EVENTSTIMULUS:
			case am::ModelPackage::VARIABLERATESTIMULUS:
				/* unsupported */
				return;

			case am::ModelPackage::INTERPROCESSSTIMULUS:
				conn = _oc.make<sm3::ModelFactory, sm3::ActivationConnection>(stimulus);
				break;

			case am::ModelPackage::PERIODICBURSTSTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::PeriodicBurstStimulus>::type >(stimulus);
				break;
			case am::ModelPackage::PERIODICSTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::PeriodicStimulus>::type >(stimulus);
				break;
			case am::ModelPackage::PERIODICSYNTHETICSTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::PeriodicSyntheticStimulus>::type >(stimulus);
				break;
			case am::ModelPackage::RELATIVEPERIODICSTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::RelativePeriodicStimulus>::type >(stimulus);
				break;
			case am::ModelPackage::SINGLESTIMULUS:
				gen = _oc.make<sm3s::StimulationFactory,
							   StimulusTrait<am::SingleStimulus>::type >(stimulus);
				break;
			}
		}

		auto activationAction = sm3::create<sm3::ActivateProcess>();
		activationAction->setName(std::string("Activate") + process->getName());
		activationAction->setTarget(process);

		if (gen) {
			auto callGraph = gen->getTargets();
			if (!callGraph) {
				callGraph = sm3::create<sm3::CallGraph>();
				gen->setTargets(callGraph);
			}

			if (callGraph->getGraphEntries().size() == 0)
				callGraph->getGraphEntries().push_back(sm3::create<sm3::CallSequence>());
			auto callSequence = ecore::as<sm3::CallSequence>(callGraph->getGraphEntries().get(0));

			callSequence->getCalls().push_back(activationAction);

		} else {
			auto cg = conn->getCallGraph();
			if (!cg) {
				cg = sm3::create<sm3::CallGraph>();
				conn->setCallGraph(cg);
			}
			if (cg->getGraphEntries().size() == 0)
				cg->getGraphEntries().push_back(sm3::create<sm3::CallSequence>());
			auto cs = ecore::as<sm3::CallSequence>(cg->getGraphEntries().get(0));

			cs->getCalls().push_back(activationAction);
			auto ips = ecore::as<am::InterProcessStimulus>(stimulus);
			if (auto counter = ips->getCounter()) {
				activationAction->setPeriod(counter->getPrescaler());
				activationAction->setOffset(counter->getOffset());
			}
		}
	}
}

/** Add TraceEvents to a Process.
 */
void Converter::addEvents(const root::model::Process_ptr& process) {
	static const std::vector<
		std::pair<sm3::TraceEventType, std::string> > s_events = {
		{ sm3::TraceEventType::Activate, "Activate" },
		{ sm3::TraceEventType::Start, "Start" },
		{ sm3::TraceEventType::Terminate, "Terminate" },
		{ sm3::TraceEventType::Block, "Block" },
		{ sm3::TraceEventType::Release, "Release" },
		{ sm3::TraceEventType::Restart, "Restart" },
	};

	const auto count = process->isIsr() ? 3u : 6u;
	for (auto i = 0u; i < count; ++i) {
		auto event = sm3::create<sm3::TraceEvent>();
		event->setType(s_events[i].first);
		event->setName(s_events[i].second);
		process->getTraceEvents().push_back(event);
	}
}

/** Add TraceEvents to a Function.
 */
void Converter::addEvents(const root::model::Function_ptr& function) {
	static const std::vector<
		std::pair<sm3::TraceEventType, std::string> > s_events = {
		{ sm3::TraceEventType::Entry, "Entry" },
		{ sm3::TraceEventType::Exit, "Exit" },
	};

	const auto count = 2;
	for (auto i = 0u; i < count; ++i) {
		auto event = sm3::create<sm3::TraceEvent>();
		event->setType(s_events[i].first);
		event->setName(s_events[i].second);
		function->getTraceEvents().push_back(event);
	}
}


void Converter::work(const am::ISR_ptr& am, am::ISR*) {
	if (_mode == PreOrder) {
		auto process = _oc.make<sm3::ModelFactory, sm3::Process>(am);
		process->setIsr(true);
		process->setName(am->getName());
		addEvents(process);
		addStimulus(am, process);
	}
}

void Converter::work(const am::OsEvent_ptr& am, am::OsEvent*) {
	if (_mode == PreOrder) {
		auto event = _oc.make<sm3::ModelFactory, sm3::Event>(am);
		event->setName(am->getName());
	}
}

void Converter::work(const am::Label_ptr& am, am::Label*) {
	if (_mode == PreOrder) {
		auto dataObject = _oc.make<sm3m::MemoryFactory, sm3m::DataObject>(am);
		dataObject->setName(am->getName());
		dataObject->setSize(AttributeCreator<sm3::DataSize>()(am->getSize()));
	}
}

void Converter::work(const am::Runnable_ptr& am, am::Runnable*) {
	if (_mode == PreOrder) {
		auto run = _oc.make<sm3::ModelFactory, sm3::Function>(am);
		run->setName(am->getName());
		addEvents(run);
	}
}

namespace details {

bool isPreemptable(const am::Task_ptr& am) {
	switch (am->getPreemption()) {
	default:
	case am::Preemption::_undefined_:
	case am::Preemption::preemptive:
		return true;
	case am::Preemption::cooperative:
	case am::Preemption::non_preemptive:
		return false;
	}
}

} // namespace details

void Converter::work(const am::Task_ptr& am, am::Task*) {
	if (_mode == PreOrder) {
		auto process = _oc.make<sm3::ModelFactory, sm3::Process>(am);
		process->setName(am->getName());
		process->setPreemptable(details::isPreemptable(am));
		process->setActivationLimit(std::max(1, am->getMultipleTaskActivationLimit()));
		addEvents(process);
		addStimulus(am, process);
	}
}

namespace details {

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
sm3::ModeGroup_ptr createModeGroup(ObjectCache& oc, const am::ModeLabel_ptr& label) {
	if (auto ptr = oc.find<sm3::ModeGroup>(label, ObjectCache::Default))
		return ptr;

	auto modeDefinition = label->getMode();
	auto enumMode = ecore::as<am::EnumMode>(modeDefinition);

	auto modeGroup = oc.make<sm3::ModelFactory, sm3::ModeGroup>(label);
	modeGroup->setName(label->getName());

	sm3::Mode_ptr initialMode;
	for (auto&& literal : enumMode->getLiterals()) {
		auto mode = sm3::create<sm3::Mode>();
		mode->setName(literal->getName());
		modeGroup->getModes().push_back(mode);
		if (literal->getName() == label->getInitialValue())
			initialMode = mode;
	}

	modeGroup->setInitialMode(initialMode);

	return modeGroup;
}

/** Create and initialize a sm3::Counter from an an::ModeLabel with a
 * modeDefinition of type am::NumericMode.
 *
 * This method is called from both the methods work(const am::ModeLabel_ptr&)
 * and details::createRelationalExpression(). The new Counter is only created
 * and initialized if it does not exist, hence the order does not matter.
 */
sm3::Counter_ptr createCounter(ObjectCache& oc, const am::ModeLabel_ptr& label) {
	if (auto ptr = oc.find<sm3::Counter>(label, ObjectCache::Default))
		return ptr;

	auto modeDefinition = label->getMode();
	auto numericMode = ecore::as<am::NumericMode>(modeDefinition);

	auto counter = oc.make<sm3::ModelFactory, sm3::Counter>(label);
	counter->setName(label->getName());

	auto initialValue = 0;
	if (!label->getInitialValue().empty()) {
		try {
			initialValue = std::stoi(label->getInitialValue());
		} catch (...) {
			std::cerr << "Warning: Cannot convert initial value of NumericMode-Label '"
					  << label->getName() << "' to an integer value.\n";
		}
	}
	counter->setInitialValue(initialValue);

	return counter;
}

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
void Converter::work(const am::ModeLabel_ptr& label, am::ModeLabel*) {
	if (_mode == PreOrder) {
		auto modeDefinition = label->getMode();
		if (!modeDefinition) {
			std::cerr << "Ignoring ModeLabel '" << label->getName()
					  << "' without reference to a Mode\n";
			return;
		}

		if (auto enumMode = ecore::as<am::EnumMode>(modeDefinition)) {
			auto modeGroup = details::createModeGroup(_oc, label);
			_model->getGlobalModeGroups().push_back(modeGroup);

		} else if (modeDefinition->eClass() == am::ModelPackage::_instance()->getNumericMode()) {
			/* The am::NumericMode does not have any additional parameters, so
			 * the default values of a sm3::Counter are used. */
			auto counter = details::createCounter(_oc, label);
			_model->getGlobalCounters().push_back(counter);
		}
	}
}

/** An am::EnumMode is translated into a new sm3::ModeGroup for each
 * am::ModeLabel, which refers to it.
 *
 * \sa work(const am::ModeLabel_ptr&, ...)
 */
void Converter::work(const am::EnumMode_ptr& am, am::EnumMode*) {
	skipChildren();
}

/** An am::EnumMode is translated into a new sm3::Counter for each
 * am::ModeLabel, which refers to it.
 *
 * \sa work(const am::ModeLabel_ptr&, ...)
 */
void Converter::work(const am::NumericMode_ptr&, am::NumericMode*) {
	skipChildren();
}

namespace details {

sm3::RelationalExpression_ptr createRelationalExpression(ObjectCache& oc,
														 const am::ModeCondition_ptr& am) {
	sm3::RelationalExpression_ptr expression;

	if (auto mvc = ecore::as<am::ModeValueCondition>(am)) {
		/* Compare one am::ModeLabel -> sm::ModeGroup | sm3::Counter against a
		 * (string) value. */
		auto label = mvc->getLabel();
		if ( ecore::as<am::EnumMode>(label->getMode()) ) {
			/* EnumMode */
			auto sm3 = sm3::create<sm3::ModeGroupExpression>();
			auto modeGroup = createModeGroup(oc, label);
			sm3->setModeGroup(modeGroup);

			std::string value = mvc->getValue();
			for (const auto&& mode : modeGroup->getModes())
				if (mode->getName() == value)
					sm3->setValue(mode);

			expression = sm3;

		} else {
			/* NumericMode */
			auto sm3 = sm3::create<sm3::CounterExpression>();
			auto counter = createCounter(oc, label);
			sm3->setCounter(counter);

			auto value = 0;
			try {
				value = std::stoi(mvc->getValue());
			} catch (...) {
				std::cerr << "Warning: Cannot convert value of ModeValueCondition with a NumericMode-Label '"
						  << label->getName() << "' to an integer value.\n";
			}
			sm3->setValue(value);

			expression = sm3;
		}

	} else if (auto mlc = ecore::as<am::ModeLabelCondition>(am)) {
		/* Compare two am::ModeLabel -> sm::ModeGroup | sm3::Counter against
		 * each other. */
		auto label1 = mlc->getLabel1();
		if ( ecore::as<am::EnumMode>(label1->getMode()) ) {
			/* EnumMode */
			auto sm3 = sm3::create<sm3::ModeGroupComparison>();
			auto modeGroup1 = createModeGroup(oc, label1);
			sm3->setModeGroup1(modeGroup1);

			auto label2 = mlc->getLabel2();
			if ( ecore::as<am::EnumMode>(label2->getMode()) ) {
				auto modeGroup2 = createModeGroup(oc, label2);
				sm3->setModeGroup2(modeGroup2);
			} else {
				std::cerr << "Cannot compare ModeGroup and Counter: Ignoring '"
						  << label2->getName() << "' used as label2.\n";
			}

			expression = sm3;

		} else {
			/* NumericMode */
			auto sm3 = sm3::create<sm3::CounterComparison>();
			auto counter1 = createCounter(oc, label1);
			sm3->setCounter1(counter1);

			auto label2 = mlc->getLabel2();
			if ( ecore::as<am::NumericMode>(label2->getMode()) ) {
				auto counter2 = createCounter(oc, label2);
				sm3->setCounter2(counter2);
			} else {
				std::cerr << "Cannot compare ModeGroup and Counter: Ignoring '"
						  << label2->getName() << "' used as label2.\n";
			}

			expression = sm3;
		}
	}

	auto relation = am->getRelation();
	switch (relation) {
	default:
	case am::RelationalOperator::EQUAL:
		expression->setRelationalOperator(sm3::RelationalOperator::eq);
		break;
	case am::RelationalOperator::NOT_EQUAL:
		expression->setRelationalOperator(sm3::RelationalOperator::ne);
		break;
	case am::RelationalOperator::LESS_THAN:
		expression->setRelationalOperator(sm3::RelationalOperator::lt);
		break;
	case am::RelationalOperator::GREATER_THAN:
		expression->setRelationalOperator(sm3::RelationalOperator::gt);
		break;
	}

	// auto expression = sm3::create<sm3::CounterExpression>();
	// auto expression = sm3::create<sm3::ModeGroupExpression>();

	return expression;
}

}

/** An am::ModeConditionDisjunction is aggregated by an
 * am::ModeSwitchEntry::condition, an am::Stimulus::executionCondition, or an
 * am::Runnable::executionCondition. In general, it is translated into a
 * sm3::ModeCondition, which is aggregated by the Model.
 */
void Converter::work(const am::ModeConditionDisjunction_ptr& am, am::ModeConditionDisjunction*) {
	if (_mode == PreOrder) {
		auto condition = _oc.make<sm3::ModelFactory, sm3::ModeCondition>(am);
		_model->getGlobalModeConditions().push_back(condition);

		/* 1..* ModeConditionDisjunctionEntry interface -> ModeCondition interface ->
		 * ModeValueCondition
		 * ModeLabelCondition */
		for (auto&& entry : am->getEntries()) {
			if (auto amModeCondition = ecore::as<am::ModeCondition>(entry)) {
				/* Wrap the am::ModeCondition into a sm3::RelationalExpression
				 * and a sm3::ModeConjunction, then add it to the
				 * sm3::ModeCondition. */
				auto conjunction = sm3::create<sm3::ModeConjunction>();
				auto expression = details::createRelationalExpression(_oc, amModeCondition);
				conjunction->getExpressions().push_back(expression);
				condition->getConjunctions().push_back(conjunction);

			} else if (auto amMcConjunction = ecore::as<am::ModeConditionConjunction>(entry)) {
				/* Create a sm3::ModeConjunction and add all the
				 * am::ModeConditions as sm3::RelationalExpressions to it. */
				auto conjunction = sm3::create<sm3::ModeConjunction>();
				for (auto&& amModeCondition : amMcConjunction->getEntries()) {
					auto expression = details::createRelationalExpression(_oc, amModeCondition);
					conjunction->getExpressions().push_back(expression);
				}
				condition->getConjunctions().push_back(conjunction);
			}
		}

	} else {
	}

	skipChildren();
}
