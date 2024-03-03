/* -*- c++ -*-
 *
 * Copyright (c) 2024 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#include "StableIntrinsicIds.h"

#include <QByteArray>

#include <ecore/EStructuralFeature.hpp>

#include <root/model/ModelObject.hpp>


StableIntrinsicIds::StableIntrinsicIds()
	: _uuidNamespace(
		  QUuid::createUuidV5( QUuid{}, QByteArrayLiteral( "com.inchron.am2inc" ) ) ) {}

void StableIntrinsicIds::resetBase( const QByteArray& base ) {
	_uuidNamespace = QUuid::createUuidV5( _uuidNamespace, base );
}

void StableIntrinsicIds::stabilize( const ecore::EObject_ptr& toplevel ) {
	const auto baseId =
		_uuidNamespace.toRfc4122()
			.toBase64( QByteArray::Base64Encoding | QByteArray::OmitTrailingEquals )
			.prepend( "_" )
			.toStdString();

	if ( const auto& modelObject = ecore::as<root::model::ModelObject>( toplevel ) )
		setStableIntrinsicId( baseId, modelObject );
	else if ( const auto& referable = ecore::as<root::Referable>( toplevel ) )
		setStableIntrinsicId( baseId, referable );
	else
		throw std::invalid_argument( "Cannot set intrinsicId of non-Referable" );

	/* Fun fact: EObject::eAllContents() includes itself in "all content". */
	auto it = toplevel->eAllContents();
	++it;
	for ( ; *it; it++ ) {
		if ( const auto& modelObject = ecore::as<root::model::ModelObject>( *it ) )
			setStableIntrinsicId( modelObject );
		else if ( const auto& referable = ecore::as<root::Referable>( *it ) )
			setStableIntrinsicId( referable );
	}
}

namespace {

template<class ECLASS>
ECLASS* findParent( const ecore::EObject_ptr& child ) {
	if ( !child )
		return {};

	auto parent = child->eContainer();
	while ( parent ) {
		if ( auto obj = ::ecore::as<ECLASS>( parent.get() ) )
			return obj;
		parent = parent->eContainer();
	}

	return {};
}

}  // namespace

void StableIntrinsicIds::setStableIntrinsicId( const root::Referable_ptr& referable ) {
	auto parent = findParent<root::Referable>( referable );
	setStableIntrinsicId( parent->getIntrinsicId(), referable );
}

void StableIntrinsicIds::setStableIntrinsicId(
	const root::model::ModelObject_ptr& model ) {
	auto parent = findParent<root::Referable>( model );
	setStableIntrinsicId( parent->getIntrinsicId(), model );
}

void StableIntrinsicIds::setStableIntrinsicId( const std::string& parentId,
											   const root::Referable_ptr& referable ) {
	const auto& esf = referable->eContainingFeature();
	auto namePart = parentId + "/@" + esf->getName();
	if ( esf->getUpperBound() != 1 ) {
		ecorecpp::mapping::any _any = referable->eContainer()->eGet( esf );
		auto ef = ecorecpp::mapping::any::any_cast<
			ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type>( _any );
		for ( size_t index = 0; index < ef->size(); ++index ) {
			if ( ef->get( index ) == referable ) {
				namePart += "." + std::to_string( index );
				break;
			}
		}
	}

	auto stableUuid =
		QUuid::createUuidV5( _uuidNamespace, QByteArray::fromStdString( namePart ) );
	setIntrinsicId( referable, stableUuid );
}

void StableIntrinsicIds::setStableIntrinsicId(
	const std::string& parentId, const root::model::ModelObject_ptr& model ) {
	auto namePart =
		parentId + "/@" + model->eContainingFeature()->getName() + "." + model->getName();
	auto stableUuid =
		QUuid::createUuidV5( _uuidNamespace, QByteArray::fromStdString( namePart ) );
	setIntrinsicId( model, stableUuid );
}


void StableIntrinsicIds::setIntrinsicId( const ::root::Referable_ptr& r,
										 const QUuid& uuid ) {
	r->setIntrinsicId(
		uuid.toRfc4122()
			.toBase64( QByteArray::Base64Encoding | QByteArray::OmitTrailingEquals )
			.prepend( "_" )
			.toStdString() );
}
