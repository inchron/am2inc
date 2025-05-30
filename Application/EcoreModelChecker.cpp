/* -*- c++ -*-
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#include "EcoreModelChecker.h"

#include <QObject>

#include <ecore.hpp>
#include <ecorecpp.hpp>
#include <ecorecpp/mapping.hpp>
#include <ecorecpp/resource/Resource.hpp>

// #include <Model/DataRate.h>
// #include <Model/DataSize.h>
// #include <Model/Frequency.h>
// #include <Model/Time.h>


ecore::EPackage_ptr EcoreModelChecker::s_toplevelPackage;


/** Test the package hierarchy if the intended type of the EReference points
 * to an EClass, from which no other EClasses are derived, and create a new
 * instance if this is the case.
 */
ecore::EObject_ptr EcoreModelChecker::createChildIfUnique(
	const ecore::EReference_ptr& erp ) {
	auto eClass = ecore::as<ecore::EClass>( erp->getEType() );
	auto subClasses =
		ecorecpp::util::EcoreUtil::getSubClasses( s_toplevelPackage, eClass );
	if ( subClasses.size() > 1 ) {
		return ecore::EObject_ptr();
	}

	ecore::EFactory_ptr const efac = eClass->getEPackage()->getEFactoryInstance();
	assert( efac );

	return efac->create( eClass );
}

void EcoreModelChecker::work( const ecore::EObject_ptr& eobj ) {
	if ( !eobj )
		return;

	auto eClass = eobj->eClass();
	for ( const auto& reference : eClass->getEAllReferences() ) {
		if ( not reference->isChangeable() or reference->isDerived() )
			continue;

		auto any = eobj->eGet( reference );
		if ( reference->getUpperBound() != 1 ) {  //Multiplicity many reference
			auto eList = ::ecorecpp::mapping::any::any_cast<
				::ecorecpp::mapping::EList<ecore::EObject_ptr>::ptr_type>( any );

			if ( reference->isContainment() ) {
				if ( int64_t( eList->size() ) < reference->getLowerBound() ) {
					for ( int idx = eList->size(); idx < reference->getLowerBound();
						  ++idx ) {
						auto child = createChildIfUnique( reference );
						if ( child )
							eList->push_back_unsafe( child );
					}
				}

				for ( size_t ind = 0; ind < eList->size(); ++ind ) {
					work( eList->get( ind ) );
				}
			}

		} else {  //Multiplicity one reference
			if ( any.empty() || !any.store_->eObject() ) {
				if ( reference->getLowerBound() == 0 )
					continue;

				if ( reference->isContainment() ) {
					auto child = createChildIfUnique( reference );
					if ( child ) {
						::ecorecpp::mapping::any_traits<ecore::EObject_ptr>::toAny(
							any, child );
						eobj->eSet( reference, any );
						work( child );
					}
				}

			} else if ( reference->isContainment() ) {
				auto child = any.store_->eObject();
				work( child );
			}
		}
	}

	// Unique name part.
	ecore::EStructuralFeature_ptr nameFeature;
	for ( auto&& ef : eClass->getEAllStructuralFeatures() ) {
		if ( ef->getName() == "name" ) {
			nameFeature = ef;
			ecorecpp::mapping::any any = eobj->eGet( nameFeature );
			ecore::EString originalName;
			ecorecpp::mapping::any_traits<ecore::EString>::fromAny( any, originalName );

			if ( originalName.empty() ) {
				ecore::EString uniqueName = getUniqueName( eobj, nameFeature );
				ecorecpp::mapping::any_traits<ecore::EString>::toAny( any, uniqueName );
				eobj->eSet( nameFeature, any );
			}
			break;
		}
	}
}

ecore::EString EcoreModelChecker::getUniqueName( const ecore::EObject_ptr& eobj,
												 const ecore::EStructuralFeature_ptr& ) {
	return eobj->eClass()->getName();
}
