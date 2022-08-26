/* -*- c++ -*-
 *
 * Converter/constraintsModel.cpp
 *
 * Copyright 2022 INCHRON AG <info@inchron.com>
 */
/** @file constraintsModel.cpp
 * Groups all code related to Amalthea's ConstraintsModel.
 */
#include "../Converter.h"

#include <exception>

#include "../AttributeCreator.h"
#include "../Diagnostic.h"

namespace sm3 = root::model;

/** Retrive the sequence of am::Events from an am::EventChain definition.
 *
 * This method tries to extract a sequence of events from an amalthea EventChain
 * which then can be translated to a sm3::EventSequence.
 * If this is not possible e.g. if the am::EventChain forks, a corresponding
 * std::invalid_argument exception is thrown.
 */
std::list<am::Event_ptr> Converter::getAmaltheaEventSequence(
	const am::AbstractEventChain_ptr& am ) {
	if ( am->getItems().size() == 0 ) {
		auto stimulus = am->getStimulus();
		if ( not stimulus ) {
			const std::string msg =
				std::string( "The stimulus is missing in the (Sub-)EventChain '" )
					.append( am->getName() )
					.append( "'." );

			throw std::invalid_argument( msg );
		}

		auto response = am->getResponse();
		if ( not response ) {
			const std::string msg =
				std::string( "The response is missing in the (Sub-)EventChain '" )
					.append( am->getName() )
					.append( "'." );

			throw std::invalid_argument( msg );
		}

		return { stimulus, response };
	}

	if ( am->getItemType() == am::EventChainItemType::parallel
		 && am->getItems().size() > 1 ) {
		const std::string msg = std::string( "Steps of the (Sub-)EventChain '" )
									.append( am->getName() )
									.append( "' are not sequential." );
		throw std::invalid_argument( msg );
	}

	std::list<am::Event_ptr> result{ am->getStimulus() };
	for ( const auto& item : am->getItems() ) {
		am::AbstractEventChain_ptr ec;
		if ( auto container = ecore::as<am::EventChainContainer>( item ) )
			ec = container->getEventChain();
		else if ( auto reference = ecore::as<am::EventChainReference>( item ) )
			ec = reference->getEventChain();

		if ( not ec )
			continue;

		for ( const auto& event : getAmaltheaEventSequence( ec ) ) {
			if ( event == result.back() )
				continue;
			result.push_back( event );
		}
	}

	return result;
}

void Converter::work( const am::EventChain_ptr& am, am::EventChain* ) {
	if ( _mode == PreOrder ) {
		try {
			auto amaltheaEvents = getAmaltheaEventSequence( am );
			std::list<sm3::ConditionalTraceEvent_ptr> cteList;
			for ( const auto& amEvent : amaltheaEvents ) {
				auto traceEvent =
					_oc.find<sm3::TraceEvent>( amEvent, ObjectCache::Default );
				if ( not traceEvent ) {
					const std::string msg = std::string( "Event '" )
												.append( amEvent->getName() )
												.append( "' can not be mapped." );
					throw std::invalid_argument( msg );
				}

				auto cte = sm3::create<sm3::ConditionalTraceEvent>();
				cte->setTraceEvent( traceEvent );
				if ( auto runnEvent = ::ecore::as<am::RunnableEvent>( amEvent ) ) {
					/* For RunnableEvents an additional restiction to a Process
					 * may be given. */
					if ( auto process = _oc.find<sm3::Process>( runnEvent->getProcess(),
																ObjectCache::Default ) )
						cte->setProcess( process );
				}
				cteList.push_back( cte );
			}

			auto eventSequence = _oc.make<sm3::ModelFactory, sm3::EventSequence>( am );
			eventSequence->setName( am->getName() );
			for ( const auto& cte : cteList )
				eventSequence->getEvents().push_back_unsafe( cte );
			_model->getEventChains().push_back_unsafe( eventSequence );

		} catch ( const std::invalid_argument& err ) {
			std::cerr << "Ignoring EventChain '" << am->getName() << "': " << err.what()
					  << "\n";
		}
	}

	skipChildren();
}

void Converter::work( const am::TimingConstraint_ptr&, am::TimingConstraint* ) {
	static Diagnostic::NotImplemented<am::TimingConstraint> message;
}

void Converter::work( const am::AffinityConstraint_ptr&, am::AffinityConstraint* ) {
	static Diagnostic::NotImplemented<am::AffinityConstraint> message;
}

void Converter::work( const am::RunnableSequencingConstraint_ptr&,
					  am::RunnableSequencingConstraint* ) {
	static Diagnostic::NotImplemented<am::RunnableSequencingConstraint> message;
}

void Converter::work( const am::DataAgeConstraint_ptr&, am::DataAgeConstraint* ) {
	static Diagnostic::NotImplemented<am::DataAgeConstraint> message;
}

void Converter::work( const am::Requirement_ptr&, am::Requirement* ) {
	static Diagnostic::NotImplemented<am::Requirement> message;
}

void Converter::work( const am::DataCoherencyGroup_ptr&, am::DataCoherencyGroup* ) {
	static Diagnostic::NotImplemented<am::DataCoherencyGroup> message;
}

void Converter::work( const am::DataStabilityGroup_ptr&, am::DataStabilityGroup* ) {
	static Diagnostic::NotImplemented<am::DataStabilityGroup> message;
}

void Converter::work( const am::PhysicalSectionConstraint_ptr&,
					  am::PhysicalSectionConstraint* ) {
	static Diagnostic::NotImplemented<am::PhysicalSectionConstraint> message;
}
