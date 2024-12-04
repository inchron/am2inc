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
#include <am220/model/ModelPackage.hpp>
#include <am220/model/Value.hpp>

#include "../AttributeCreator.h"

namespace am220::ResolveValue {

/* A small helper to access the embedded value of a polymorphic Value object.
 *
 * See https://eclipse.dev/app4mc/help/latest/index.html#section3.2.1 for reference.
 */
template<typename T>
T resolve( const am220::model::Value_ptr& );
template<>
ecore::EString resolve<ecore::EString>( const am220::model::Value_ptr& );
template<>
ecore::EBoolean resolve<ecore::EBoolean>( const am220::model::Value_ptr& );
template<>
ecore::EInt resolve<int>( const am220::model::Value_ptr& );
template<>
ecore::ELong resolve<ecore::ELong>( const am220::model::Value_ptr& );
template<>
ecore::EFloat resolve<ecore::EFloat>( const am220::model::Value_ptr& );
template<>
ecore::EDouble resolve<ecore::EDouble>( const am220::model::Value_ptr& );
template<>
sm3::Time_ptr resolve<sm3::Time_ptr>( const am220::model::Value_ptr& );

}  // namespace am220::ResolveValue
