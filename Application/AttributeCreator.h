/* -*- c++ -*-
 *
 * AttributeCreator.h
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/* @file AttributeCreator.h
 * Basic helpers, especially for those types, which are pseudo attributes in
 * the INCHRON model.
 */

#include <ecore/EEnum.hpp>
#include <ecore/EEnumLiteral.hpp>

#include <amalthea/model/Amalthea.hpp>
#include <am2inc.hpp>
#include <root.hpp>
#include <root/model/memory/MemoryPackage.hpp>

namespace am   = amalthea::model;
namespace sm3  = root::model;
namespace sm3m = root::model::memory;


template<class I>
struct AttributeCreator {
	template<class A>
	ecore::Ptr<I> operator()(ecore::Ptr<A>);
};

template<>
struct AttributeCreator<sm3::Frequency> {
	template<class A>
	ecore::Ptr<sm3::Frequency> operator()(ecore::Ptr<A> a) {
		auto value = sm3::create<sm3::Frequency>();
		value->setValue(a->getValue());

		auto eenum = am::ModelPackage::_instance()->getFrequencyUnit();
		auto name = eenum->getEEnumLiteral( (int)a->getUnit() )->getName();
		auto newEenum = sm3::ModelPackage::_instance()->getFrequencyUnit();
		auto newUnit = newEenum->getEEnumLiteral(name);
		value->setUnit( (sm3::FrequencyUnit)newUnit->getValue() );

		return value;
	}
};

template<>
struct AttributeCreator<sm3::DataSize> {
	template<class A>
	ecore::Ptr<sm3::DataSize> operator()(ecore::Ptr<A> a) {
		auto value = sm3::create<sm3::DataSize>();
		return value;
	}
};
