/*
 * Copyright (c) 2024 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
*/

#include "ResolveValues.h"

#include <am200/model/BooleanObject.hpp>
#include <am200/model/DoubleObject.hpp>
#include <am200/model/FloatObject.hpp>
#include <am200/model/IntegerObject.hpp>
#include <am200/model/LongObject.hpp>
#include <am200/model/ModelPackage.hpp>
#include <am200/model/StringObject.hpp>
#include <am200/model/Time.hpp>
#include <am200/model/Value.hpp>

namespace am200::ResolveValue {

/* A small helper to access the embedded value of a polymorphic Value object.
 *
 * See https://eclipse.dev/app4mc/help/latest/index.html#section3.2.1 for reference.
 */
template<typename T>
T resolve( const am200::model::Value_ptr& ) {
	return {};
}

template<>
ecore::EString resolve<ecore::EString>( const am200::model::Value_ptr& abstract ) {
	auto concrete = ecore::as<am200::model::StringObject>( abstract );
	return concrete->getValue();
}

template<>
ecore::EBoolean resolve<ecore::EBoolean>( const am200::model::Value_ptr& abstract ) {
	auto concrete = ecore::as<am200::model::BooleanObject>( abstract );
	return concrete->isValue();
}

template<>
ecore::EInt resolve<ecore::EInt>( const am200::model::Value_ptr& abstract ) {
	auto concrete = ecore::as<am200::model::IntegerObject>( abstract );
	return concrete->getValue();
}

/**
 * \note Since EBigInteger and ELong are mapped to the same C++ type,
 * this variant will cover both.
 */
template<>
ecore::ELong resolve<ecore::ELong>( const am200::model::Value_ptr& abstract ) {
	auto concrete = ecore::as<am200::model::LongObject>( abstract );
	return concrete->getValue();
}

template<>
ecore::EFloat resolve<ecore::EFloat>( const am200::model::Value_ptr& abstract ) {
	auto concrete = ecore::as<am200::model::FloatObject>( abstract );
	return concrete->getValue();
}

template<>
ecore::EDouble resolve<ecore::EDouble>( const am200::model::Value_ptr& abstract ) {
	auto concrete = ecore::as<am200::model::DoubleObject>( abstract );
	return concrete->getValue();
}

template<>
sm3::Time_ptr resolve<sm3::Time_ptr>( const am200::model::Value_ptr& abstract ) {
	auto concrete = ecore::as<am200::model::Time>( abstract );
	return AttributeCreator<sm3::Time, am200::model::ModelPackage>()( concrete );
}

}  // namespace am200::ResolveValue
