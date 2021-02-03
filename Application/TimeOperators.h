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
double operator / (const root::model::Time& numerator, const root::model::Time& denominator) {
	checkUnits(numerator, denominator);
	return (double)numerator.getValue() / denominator.getValue();
}

inline
root::model::Time operator / (const root::model::Time& numerator, double denominator) {
	root::model::Time t;
	t.setUnit(numerator.getUnit());
	t.setValue(numerator.getValue());
	/* The smaller the unit, the larger the value, which leads to smaller loss
	 * of precision. */
	normalize(t, root::model::TimeUnit::fs);
	t.setValue(t.getValue() / denominator);
	return t;
}
