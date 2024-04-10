/* -*- c++ -*-
 *
 * Converter/eventModel.cpp
 *
 * Copyright (c) 2022-2024 INCHRON AG <info@inchron.com>
 */
/** @file eventModel.cpp
 * Groups all code related to Amalthea's EventModel.
 */
#include "../AttributeCreator.h"
#include "../Diagnostic.h"
#include "Converter.h"

namespace am = am220::model;
namespace sm3 = root::model;

namespace am220 {
void Converter::work( const am::EventSet_ptr&, am::EventSet* ) {
	static Diagnostic::NotImplemented<am::EventSet> message;
}

void Converter::work( const am::ComponentEvent_ptr&, am::ComponentEvent* ) {
	static Diagnostic::NotImplemented<am::ComponentEvent> message;
}

void Converter::work( const am::ProcessEvent_ptr& am, am::ProcessEvent* ) {
	if ( _mode == PreOrder ) {
		auto amTask = am->getEntity();
		if ( not amTask ) {
			return;
		}

		auto process = _oc.find<sm3::Process>( amTask, ObjectCache::Default );
		if ( not process ) {
			return;
		}

		static const std::map<am::ProcessEventType, sm3::TraceEventType> processEventMap{
			{ am::ProcessEventType::activate, sm3::TraceEventType::Activate },
			{ am::ProcessEventType::start, sm3::TraceEventType::Start },
			{ am::ProcessEventType::resume, sm3::TraceEventType::Restart },
			{ am::ProcessEventType::wait, sm3::TraceEventType::Block },
			{ am::ProcessEventType::release, sm3::TraceEventType::Release },
			{ am::ProcessEventType::terminate, sm3::TraceEventType::Terminate } };

		auto it = processEventMap.find( am->getEventType() );
		if ( it != processEventMap.end() ) {
			for ( const auto& event : process->getTraceEvents() ) {
				if ( event->getType() == it->second ) {
					_oc.add( am, ObjectCache::SubKey::Default, event );
					return;
				}
			}
		}
	}
}

void Converter::work( const am::ProcessChainEvent_ptr&, am::ProcessChainEvent* ) {
	static Diagnostic::NotImplemented<am::ProcessChainEvent> message;
}

void Converter::work( const am::SemaphoreEvent_ptr&, am::SemaphoreEvent* ) {
	static Diagnostic::NotImplemented<am::SemaphoreEvent> message;
}

void Converter::work( const am::StimulusEvent_ptr&, am::StimulusEvent* ) {
	static Diagnostic::NotImplemented<am::StimulusEvent> message;
}

void Converter::work( const am::ChannelEvent_ptr&, am::ChannelEvent* ) {
	static Diagnostic::NotImplemented<am::ChannelEvent> message;
}

void Converter::work( const am::CustomEvent_ptr&, am::CustomEvent* ) {
	static Diagnostic::NotImplemented<am::CustomEvent> message;
}

void Converter::work( const am::LabelEvent_ptr&, am::LabelEvent* ) {
	static Diagnostic::NotImplemented<am::LabelEvent> message;
}

void Converter::work( const am::RunnableEvent_ptr& am, am::RunnableEvent* ) {
	if ( _mode == PreOrder ) {
		auto amRunnable = am->getEntity();
		if ( not amRunnable ) {
			return;
		}

		auto function = _oc.find<sm3::Function>( amRunnable, ObjectCache::Default );
		if ( not function ) {
			return;
		}

		static const std::map<am::RunnableEventType, sm3::TraceEventType>
			runnableEventMap{
				{ am::RunnableEventType::start, sm3::TraceEventType::Entry },
				{ am::RunnableEventType::terminate, sm3::TraceEventType::Exit } };

		auto it = runnableEventMap.find( am->getEventType() );
		if ( it != runnableEventMap.end() ) {
			for ( const auto& event : function->getTraceEvents() ) {
				if ( event->getType() == it->second ) {
					_oc.add( am, ObjectCache::SubKey::Default, event );
					return;
				}
			}
		}
	}
}

}  // namespace am220
