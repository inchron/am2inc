/* -*- c++ -*-
 *
 * Converter/TimeOperators.hpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#include "TimeOperators.h"

template<typename T>
constexpr
typename std::underlying_type<T>::type
operator +(T val) {
	return static_cast< typename std::underlying_type<T>::type >(val);
}

template<typename T>
T&
operator ++(T& val) {
	return val = static_cast<T>( + val + 1 );
}


void normalize(root::model::Time& t, root::model::TimeUnit u) {
	if ( t.getUnit() >= root::model::TimeUnit::T
		 || u >= root::model::TimeUnit::T )
		throw std::logic_error("Cannot normalize from/to TimeUnit T");

	auto value = t.getValue();
	for (auto unit = t.getUnit(); unit < u; ++unit)
		value *= 1000;
	t.setValue(value);
	t.setUnit(u);
}
