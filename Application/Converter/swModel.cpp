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

void Converter::work(const amalthea::model::OsEvent_ptr& am, amalthea::model::OsEvent*) {
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
