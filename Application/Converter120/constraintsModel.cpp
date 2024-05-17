/* -*- c++ -*-
 *
 * Converter/constraintsModel.cpp
 *
 * Copyright (c) 2022-2024 INCHRON AG <info@inchron.com>
 */
/** @file constraintsModel.cpp
 * Groups all code related to Amalthea's ConstraintsModel.
 */
#include <exception>

#include "../AttributeCreator.h"
#include "../Diagnostic.h"
#include "Converter.h"

namespace am = am120::model;
namespace sm3 = root::model;
namespace sm3r = root::model::requirement;

namespace am120 {
/** Retrieve the sequence of am::Events from an am::EventChain definition.
 *
 * This method tries to extract a sequence of events from an amalthea EventChain
 * which then can be translated to a sm3::EventGraph.
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

	if ( am->getResponse() and am->getResponse() != result.back() )
		result.push_back( am->getResponse() );

	return result;
}

void Converter::work( const am::EventChain_ptr& am, am::EventChain* ) {
	if ( _mode == PreOrder ) {
		try {
			auto amaltheaEvents = getAmaltheaEventSequence( am );
			std::list<sm3::EventGraphTraceEvent_ptr> egteList;
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
					/* For RunnableEvents an additional restriction to a Process
					 * may be given. */
					if ( auto process = _oc.find<sm3::Process>( runnEvent->getProcess(),
																ObjectCache::Default ) )
						cte->setProcess( process );
				}
				auto egte = sm3::create<sm3::EventGraphTraceEvent>();
				egte->setName( amEvent->getName() );
				egte->setFirst( cte );
				if ( not egteList.empty() )
					egteList.back()->getSuccessors().push_back( egte );
				egteList.push_back( egte );
			}

			auto eventGraph = _oc.make<sm3::ModelFactory, sm3::EventGraph>( am );
			eventGraph->setName( am->getName() );
			for ( const auto& cte : egteList )
				eventGraph->getNodes().push_back_unsafe( cte );
			if ( not egteList.empty() ) {
				eventGraph->setInitialNode( egteList.front() );
				eventGraph->getTerminalNodes().push_back_unsafe( egteList.back() );
			}
			_model->getEventChains().push_back_unsafe( eventGraph );

		} catch ( const std::invalid_argument& err ) {
			warning( QStringLiteral( "Ignoring EventChain '%1': %2" )
						 .arg( QString::fromStdString( am->getName() ),
							   QString::fromStdString( err.what() ) ) );
		}
	}

	skipChildren();
}

void Converter::work( const am::EventChainLatencyConstraint_ptr& am,
					  am::EventChainLatencyConstraint* ) {
	/* Since the EventChainLatencyConstrains are on the same hierarchy level as the
	 * EventChains we can not be sure, if we have seen (and translated) the EventChain
	 * already. Therefore, we just memorize the LatencyConstraint here and translate
	 * it in a separate step. */

	if ( _mode == PreOrder )
		_latencyConstraints.emplace_back( am );

	skipChildren();
}

void Converter::convertEventChainLatencyConstraints() {
	for ( const auto& am : _latencyConstraints ) {
		if ( not am->getScope() ) {
			warning( QStringLiteral( "Ignoring EventChainLatencyConstraint '%1' "
									 "without EventChain reference. " )
						 .arg( QString::fromStdString( am->getName() ) ) );
			continue;
		}

		auto amEventChain = am->getScope();
		auto eventChain = _oc.find<sm3::EventGraph>( amEventChain, ObjectCache::Default );
		if ( not eventChain ) {
			warning( QStringLiteral( "Ignoring EventChainLatencyConstraint '%1' without "
									 "mapped EventChain '%2'." )
						 .arg( QString::fromStdString( am->getName() ),
							   QString::fromStdString( amEventChain->getName() ) ) );
			continue;
		}

		auto startStep =
			::ecore::as<sm3::EventGraphTraceEvent>( eventChain->getInitialNode() )
				->getFirst();
		auto& terminalNodes = eventChain->getTerminalNodes();
		auto endStep =
			terminalNodes.empty()
				? sm3::ConditionalTraceEvent_ptr()
				: ::ecore::as<sm3::EventGraphTraceEvent>( terminalNodes[0] )->getFirst();

		auto lowerBound =
			AttributeCreator<sm3::Time, am::ModelPackage>()( am->getMinimum() );

		auto upperBound =
			AttributeCreator<sm3::Time, am::ModelPackage>()( am->getMaximum() );

		auto ectRequirement =
			_oc.make<sm3r::RequirementFactory, sm3r::EventChainTimingRequirement>( am );
		ectRequirement->setName( am->getName() );
		ectRequirement->setEventChain( eventChain );
		if ( startStep )
			ectRequirement->getStart().push_back_unsafe( startStep );
		if ( endStep )
			ectRequirement->getEnd().push_back_unsafe( endStep );
		ectRequirement->setInterval( sm3::create<sm3::TimeInterval>() );
		ectRequirement->getInterval()->setLowerLimit( lowerBound );
		ectRequirement->getInterval()->setUpperLimit( upperBound );

		_model->getRequirements().push_back_unsafe( ectRequirement );
	}
}

void Converter::work( const am::TimingConstraint_ptr&, am::TimingConstraint* ) {
	static Diagnostic::NotImplemented<am::TimingConstraint> message( this );
}

void Converter::work( const am::AffinityConstraint_ptr&, am::AffinityConstraint* ) {
	static Diagnostic::NotImplemented<am::AffinityConstraint> message( this );
}

void Converter::work( const am::RunnableSequencingConstraint_ptr&,
					  am::RunnableSequencingConstraint* ) {
	static Diagnostic::NotImplemented<am::RunnableSequencingConstraint> message( this );
}

void Converter::work( const am::DataAgeConstraint_ptr&, am::DataAgeConstraint* ) {
	static Diagnostic::NotImplemented<am::DataAgeConstraint> message( this );
}

void Converter::work( const am::Requirement_ptr&, am::Requirement* ) {
	static Diagnostic::NotImplemented<am::Requirement> message( this );
}

void Converter::work( const am::DataCoherencyGroup_ptr&, am::DataCoherencyGroup* ) {
	static Diagnostic::NotImplemented<am::DataCoherencyGroup> message( this );
}

void Converter::work( const am::DataStabilityGroup_ptr&, am::DataStabilityGroup* ) {
	static Diagnostic::NotImplemented<am::DataStabilityGroup> message( this );
}

void Converter::work( const am::PhysicalSectionConstraint_ptr&,
					  am::PhysicalSectionConstraint* ) {
	static Diagnostic::NotImplemented<am::PhysicalSectionConstraint> message( this );
}

}  // namespace am120
