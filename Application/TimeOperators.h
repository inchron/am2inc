/* -*- c++ -*-
 *
 * Converter/TimeOperators.hpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file TimeOperators.cpp
 * A reduced set of operations on Time, which are used in the Amalthea
 * Importer.
 *
 * These are free methods and operators. The first parameter would be the this
 * pointer of a method.
 */
#include <root/model/Time.hpp>

void normalize(root::model::Time&, root::model::TimeUnit = root::model::TimeUnit::fs);

inline
void checkUnits(const root::model::Time& lhs, const root::model::Time& rhs) {
	if (lhs.getUnit() != rhs.getUnit())
		throw std::logic_error("Mismatching TimeUnits");
}

inline
root::model::Time operator - (const root::model::Time& lhs, const root::model::Time& rhs) {
	checkUnits(lhs, rhs);
	root::model::Time t;
	t.setUnit(lhs.getUnit());
	t.setValue(lhs.getValue() - rhs.getValue());
	return t;
}

inline
bool operator > (const root::model::Time& lhs, const root::model::Time& rhs) {
	checkUnits(lhs, rhs);
	return lhs.getValue() > rhs.getValue();
}

inline
root::model::Time operator / (const root::model::Time& lhs, double divisor) {
	root::model::Time t;
	t.setUnit(lhs.getUnit());
	t.setValue(lhs.getValue() / divisor);
	return t;
}
