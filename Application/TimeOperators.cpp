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
#include "TimeOperators.h"

template<typename T>
constexpr typename std::underlying_type<T>::type operator+( T val ) {
	return static_cast<typename std::underlying_type<T>::type>( val );
}

template<typename T>
T& operator++( T& val ) {
	return val = static_cast<T>( +val + 1 );
}


void normalize( root::model::Time& t, root::model::TimeUnit u ) {
	if ( t.getUnit() >= root::model::TimeUnit::T || u >= root::model::TimeUnit::T )
		return;

	auto value = t.getValue();
	for ( auto unit = t.getUnit(); unit < u; ++unit )
		value *= 1000;
	t.setValue( value );
	t.setUnit( u );
}
