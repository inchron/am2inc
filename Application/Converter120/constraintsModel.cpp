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

namespace {

std::vector<sm3::EventGraphNode_ptr> getTraceEvents( const am::Event_ptr& amEvent,
													 ObjectCache& oc ) {
	auto createEGTE = [&oc]( const auto& entityEvent ) {
		auto traceEvent = oc.find<sm3::TraceEvent>( entityEvent, ObjectCache::Default );
		if ( not traceEvent ) {
			const std::string msg = std::string( "Event '" )
										.append( entityEvent->getName() )
										.append( "' can not be mapped." );
			throw std::invalid_argument( msg );
		}
		auto cte = sm3::create<sm3::ConditionalTraceEvent>();
		cte->setTraceEvent( traceEvent );
		if ( auto runnEvent = ::ecore::as<am::RunnableEvent>( entityEvent ) ) {
			/* For RunnableEvents an additional restriction to a Process
				   * may be given. */
			if ( auto amProcess = runnEvent->getProcess() ) {
				auto process = oc.make<sm3::ModelFactory, sm3::Process>( amProcess );
				cte->setProcess( process );
			}
		}
		auto egte = sm3::create<sm3::EventGraphTraceEvent>();
		egte->setName( entityEvent->getName() );
		egte->setFirst( cte );
		return egte;
	};

	std::vector<sm3::EventGraphNode_ptr> nodes;
	if ( auto eventSet = ::ecore::as<am::EventSet>( amEvent ) ) {
		for ( const auto& entityEvent : eventSet->getEvents() )
			nodes.emplace_back( createEGTE( entityEvent ) );
	} else {
		nodes.emplace_back( createEGTE( amEvent ) );
	}

	return nodes;
}

}  // namespace

/** A function for recursively filling an EventGraph from an Amalthea EventChain.
 *
 *  This function adds all events of the given am::AbstractEventChain to the EventGraph
 *  except for the Stimulus and Response itself. It returns the list of stimuli successor
 *  EventGraphNodes and the response predecessor EventGraphNode. These then are used
 *  to set the predecessor-/successor- relations on higher levels of the calling hierarchy.
 */
std::tuple<std::vector<sm3::EventGraphNode_ptr> /*stimuliSuccessors*/,
		   sm3::EventGraphNode_ptr /*responsePredecessor*/>
	Converter::fillEventGraph( const am::AbstractEventChain_ptr& am,
							   const sm3::EventGraph_ptr& eg ) {
	/* First case: no sub-chains. */
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

		if ( auto eventSet = ::ecore::as<am::EventSet>( am->getStimulus() );
			 eventSet and eventSet->getEvents().size() > 1 ) {
			auto syncBarrier = sm3::create<sm3::EventGraphSynchronizationBarrier>();
			syncBarrier->setMinItems( 0 );
			syncBarrier->setName( eventSet->getName() + std::string( "_sync" ) );
			eg->getNodes().push_back_unsafe( syncBarrier );
			return { { syncBarrier }, syncBarrier };
		}
		return {};
	}

	/* Second case: parallel sub-chains. */
	const auto numberOfItems = am->getItems().size();
	if ( am->getItemType() == am::EventChainItemType::parallel && numberOfItems > 1 ) {
		auto syncBarrier = sm3::create<sm3::EventGraphSynchronizationBarrier>();
		syncBarrier->setMinItems( am->getMinItemsCompleted() );
		syncBarrier->setName( am->getName() + "_sync" );

		std::vector<sm3::EventGraphNode_ptr> stimuliSuccessors;
		for ( const auto& item : am->getItems() ) {
			am::AbstractEventChain_ptr ec;
			if ( auto container = ecore::as<am::EventChainContainer>( item ) )
				ec = container->getEventChain();
			else if ( auto reference = ecore::as<am::EventChainReference>( item ) )
				ec = reference->getEventChain();

			if ( not ec )
				continue;

			if ( ec->getStimulus() != am->getStimulus() ) {
				const std::string msg =
					std::string( "The stimulus of sub-EventChain '" )
						.append( ec->getName() )
						.append(
							"' is not equal to the stimulus of the parent EventChain '" )
						.append( am->getName() )
						.append( "'." );

				throw std::invalid_argument( msg );
			}

			if ( ec->getResponse() != am->getResponse() ) {
				const std::string msg =
					std::string( "The response of sub-EventChain '" )
						.append( ec->getName() )
						.append(
							"' is not equal to the response of the parent EventChain '" )
						.append( am->getName() )
						.append( "'." );

				throw std::invalid_argument( msg );
			}

			auto [stimuliSuccessor, responsePredecessor] = fillEventGraph( ec, eg );
			stimuliSuccessors.insert( stimuliSuccessors.end(), stimuliSuccessor.begin(),
									  stimuliSuccessor.end() );
			syncBarrier->getPredecessors().push_back( responsePredecessor );
		}
		eg->getNodes().push_back_unsafe( syncBarrier );
		return { stimuliSuccessors, syncBarrier };
	}

	/* Third case: sequential sub-chains. */
	std::vector<sm3::EventGraphNode_ptr> firstStimuliSuccessors;
	sm3::EventGraphNode_ptr lastResponsePredecessor;

	bool firstItem{ true };
	for ( const auto& item : am->getItems() ) {
		am::AbstractEventChain_ptr ec;
		if ( auto container = ecore::as<am::EventChainContainer>( item ) )
			ec = container->getEventChain();
		else if ( auto reference = ecore::as<am::EventChainReference>( item ) )
			ec = reference->getEventChain();

		if ( not ec )
			continue;

		const auto& [stimulusSuccessors, responsePredecessor] = fillEventGraph( ec, eg );

		if ( numberOfItems == 1 )
			return { stimulusSuccessors, responsePredecessor };


		if ( firstItem ) {
			firstItem = false;
			if ( not stimulusSuccessors.empty() ) {
				firstStimuliSuccessors = stimulusSuccessors;
				lastResponsePredecessor = responsePredecessor;
			}

		} else {
			auto stimuli = getTraceEvents( ec->getStimulus(), _oc );
			if ( firstStimuliSuccessors.empty() )
				firstStimuliSuccessors = stimuli;

			for ( const auto& stimulus : stimuli ) {
				eg->getNodes().push_back_unsafe( stimulus );

				for ( const auto& succ : stimulusSuccessors )
					stimulus->getSuccessors().push_back( succ );

				if ( lastResponsePredecessor )
					stimulus->getPredecessors().push_back( lastResponsePredecessor );
			}

			if ( responsePredecessor ) {
				lastResponsePredecessor = responsePredecessor;
			} else {
				assert( stimuli.size() == 1 );
				lastResponsePredecessor = *stimuli.begin();
			}
		}
	}

	return { firstStimuliSuccessors, lastResponsePredecessor };
}

void Converter::work( const am::EventChain_ptr& am, am::EventChain* ) {
	if ( _mode == PreOrder ) {
		try {
			auto eventGraph = _oc.make<sm3::ModelFactory, sm3::EventGraph>( am );
			eventGraph->setName( am->getName() );

			const auto& [stimulusSuccessors, responsePredecessor] =
				fillEventGraph( am, eventGraph );

			auto stimulus = getTraceEvents( am->getStimulus(), _oc );
			if ( stimulus.size() > 1 ) {
				const std::string msg =
					std::string( "The EventChain '" ) + am->getName()
					+ std::string(
						"' has more than one initial EntityEvent (EventSet). This is "
						"currently not supported and the EventChain will be "
						"skipped." );

				throw std::invalid_argument( msg );
			}

			for ( const auto& stim : stimulus ) {
				eventGraph->getNodes().push_back_unsafe( stim );
				if ( auto initialNode = ::ecore::as<sm3::EventGraphInitialNode>( stim ) )
					eventGraph->setInitialNode( initialNode );

				for ( const auto& stimulusSuccessor : stimulusSuccessors )
					stim->getSuccessors().push_back( stimulusSuccessor );
			}

			auto response = getTraceEvents( am->getResponse(), _oc );
			if ( response.size() > 1 ) {
				const std::string msg =
					std::string( "The EventChain '" ) + am->getName()
					+ std::string(
						"' has more than one terminal EntityEvent "
						"(EventSet). This is currently not "
						"supported and the EventChain will be skipped." );

				throw std::invalid_argument( msg );
			}

			for ( const auto& resp : response ) {
				eventGraph->getNodes().push_back_unsafe( resp );
				if ( auto terminalNode =
						 ::ecore::as<sm3::EventGraphTerminalNode>( resp ) )
					eventGraph->getTerminalNodes().push_back( terminalNode );

				if ( responsePredecessor ) {
					resp->getPredecessors().push_back( responsePredecessor );

				} else if ( not stimulus.empty() ) {
					resp->getPredecessors().push_back( stimulus.front() );
				}
			}

			_model->getEventChains().push_back_unsafe( eventGraph );

		} catch ( const std::invalid_argument& err ) {
			_oc.remove( am );
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
		std::vector<sm3::ConditionalTraceEvent_ptr> endSteps;
		for ( const auto& terminalNode : eventChain->getTerminalNodes() ) {
			if ( auto egTraceEvent =
					 ecore::as<sm3::EventGraphTraceEvent>( terminalNode ) )
				endSteps.emplace_back( egTraceEvent->getFirst() );
		}

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
		for ( const auto& endStep : endSteps )
			ectRequirement->getEnd().push_back_unsafe( endStep );

		ectRequirement->setInterval( sm3::create<sm3::TimeInterval>() );
		ectRequirement->getInterval()->setLowerLimit( lowerBound );
		ectRequirement->getInterval()->setUpperLimit( upperBound );

		ectRequirement->setStrategy( am->getType() == am::LatencyType::Age
										 ? sm3::EventChainStrategy::FirstLast
										 : sm3::EventChainStrategy::FirstFirst );

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
