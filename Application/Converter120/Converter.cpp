/* -*- c++ -*-
 *
 * Copyright (c) 2020-2021 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#include "Converter.h"

#include "../AttributeCreator.h"

namespace am = am120::model;

namespace am120 {

/** Main entry to the Converter, part of the fixed framework.
 */
void Converter::convert( const ecore::EObject_ptr& topLevelAmalthea ) {
	ecorecpp::util::TreeWalker walker(
		[this]( const auto& eObject ) { return preOrder( eObject ); },
		[this]( const auto& eObject ) { return postOrder( eObject ); } );
	walker.traverse( topLevelAmalthea );
}

ecorecpp::util::TreeWalker::Status Converter::preOrder( const ecore::EObject_ptr& obj ) {
	_status = ecorecpp::util::TreeWalker::Status::Continue;
	_mode = PreOrder;
	enter( obj );
	return _status;
}

ecorecpp::util::TreeWalker::Status Converter::postOrder( const ecore::EObject_ptr& obj ) {
	_status = ecorecpp::util::TreeWalker::Status::Continue;
	_mode = PostOrder;
	enter( obj );
	return _status;
}

void Converter::addMapping( const std::vector<am::ReferableBaseObject_ptr>& am,
							const std::vector<root::Referable_ptr>& inc ) {
	/*
	auto mapping = am2inc::create<am2inc::Mapping>();
	for ( auto&& a : am )
		mapping->getAmalthea().push_back_unsafe( a );
	for ( auto&& i : inc )
		mapping->getInchron().push_back_unsafe( i );
	_mappings->getMappings().push_back_unsafe( mapping );
*/
}

/*
 * @see Converter/hwModel.cpp for the conversion of Amalthea's HwModel.
 *
 * @see Converter/swModel.cpp for the conversion of Amalthea's SwModel.
 */

}  // namespace am120
