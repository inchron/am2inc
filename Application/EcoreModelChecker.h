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
#pragma once

#include <ecore_forward.hpp>

/** EcoreModelChecker is the base class for all package dependent model checkers.
 *
 * A model checker takes a pointer to an object of its enclosing class
 * Validator. In its work methods it checks or repairs model elements
 * according to the selected mode of the validator.
 *
 * The default implementation of work(const EObject_ptr&, EObject*)
 * checks all containment references of the object.
 * If the lower bound of the reference is larger than the actual
 * number of child nodes a message is sent to the logger that the
 * object of type xy misses child nodes of type z.
 * In 'Repair' mode the missing child nodes are created if
 * possible (if child type is a 'leaf' class).
 * Afterwards the work method calls Validator::checkOrRepair() for all
 * child nodes.
 *
 * \note Model checkers need to be nested classes of the Validator.
 */
class EcoreModelChecker {
public:
	EcoreModelChecker() = default;
	~EcoreModelChecker() = default;

	void work(const ecore::EObject_ptr&);

	static void setToplevelPackage(const ecore::EPackage_ptr& p) { s_toplevelPackage = p; }

protected:
	virtual ecore::EObject_ptr createChildIfUnique(const ecore::EReference_ptr&);
	virtual ecore::EString getUniqueName(const ecore::EObject_ptr&,
										 const ecore::EStructuralFeature_ptr&);

	static ecore::EPackage_ptr s_toplevelPackage;
};
