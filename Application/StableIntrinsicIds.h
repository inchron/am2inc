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
#pragma once

#include <QUuid>

#include <root/model_forward.hpp>
#include <root_forward.hpp>

class QByteArray;

/** Refreshes the intrinsic ID in a containment tree of root::model::Referables.
 *
 * The new intrinsic ID of a Referable object is calculated from the intrinsic
 * ID of its (next) container Referable, and its name or, if it does not have
 * a name, the name of its containing feature and its position therein.
 *
 * The toplevel object passed to stabilize() does not need a container
 * Referable. Instead, its intrinsic ID is derived from the fixed namespace
 * "com.inchron.am2inc". This namespace can be modified (not replaced) by a
 * byte array, e.g. a hash sum of the input files or a constant given on the
 * commandline.
 */
class StableIntrinsicIds {
public:
	StableIntrinsicIds();

	/** Change the base used for the toplevel object.
	 */
	void resetBase( const QByteArray& base );

	/* Overwrite the intrinsic IDs of the given toplevel object and all its
	 * containment children.
	 *
	 * The given object must be an instance of a class derived from Referable.
	 */
	void stabilize( const ecore::EObject_ptr& toplevel );

private:
	QUuid _uuidNamespace;

	void setStableIntrinsicId( const root::Referable_ptr& );
	void setStableIntrinsicId( const root::model::ModelObject_ptr& );

	void setStableIntrinsicId( const std::string& parentId, const root::Referable_ptr& );
	void setStableIntrinsicId( const std::string& parentId,
							   const root::model::ModelObject_ptr& );

	static void setIntrinsicId( const ::root::Referable_ptr&, const QUuid& );
};
