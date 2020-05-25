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
namespace sm3s = root::model::stimulation;


template<class I>
struct AttributeCreator {
	template<class A>
	ecore::Ptr<I> operator()(ecore::Ptr<A>);
};

template<>
struct AttributeCreator<sm3::Time> {
	template<class A>
	ecore::Ptr<sm3::Time> operator()(ecore::Ptr<A> a) {
		auto value = sm3::create<sm3::Time>();
		if (!a)
			return value;

		value->setValue(a->getValue());

		auto eenum = am::ModelPackage::_instance()->getTimeUnit();
		auto name = eenum->getEEnumLiteral( (int)a->getUnit() )->getName();
		auto newEenum = sm3::ModelPackage::_instance()->getTimeUnit();
		auto newUnit = newEenum->getEEnumLiteral(name);
		value->setUnit( (sm3::TimeUnit)newUnit->getValue() );

		return value;
	}

	template<typename Integer>
	ecore::Ptr<sm3::Time> operator()(Integer v, sm3::TimeUnit u) {
		auto value = sm3::create<sm3::Time>();
		value->setValue(v);
		value->setUnit(u);
		return value;
	}
};

template<>
struct AttributeCreator<sm3::Frequency> {
	template<class A>
	ecore::Ptr<sm3::Frequency> operator()(ecore::Ptr<A> a) {
		auto value = sm3::create<sm3::Frequency>();
		if (!a)
			return value;

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
		if (!a)
			return value;

		value->setValue(a->getValue());

		auto eenum = am::ModelPackage::_instance()->getDataSizeUnit();
		auto name = eenum->getEEnumLiteral( (int)a->getUnit() )->getName();
		if (name == "Kibit")
			name = "kibit";
		else if (name == "KiB")
			name = "kiB";
		auto newEenum = sm3::ModelPackage::_instance()->getDataSizeUnit();
		auto newUnit = newEenum->getEEnumLiteral(name);
		value->setUnit( (sm3::DataSizeUnit)newUnit->getValue() );

		return value;
	}

	ecore::Ptr<sm3::DataSize> operator()(ecore::ELong v, sm3::DataSizeUnit u) {
		auto value = sm3::create<sm3::DataSize>();
		value->setValue(v);
		value->setUnit(u);
		return value;
	}
};

template<>
struct AttributeCreator<sm3::DataRate> {
	template<class A>
	ecore::Ptr<sm3::DataRate> operator()(ecore::Ptr<A> a) {
		auto value = sm3::create<sm3::DataRate>();
		if (!a)
			return value;

		value->setValue(a->getValue());

		auto eenum = am::ModelPackage::_instance()->getDataRateUnit();
		auto name = eenum->getEEnumLiteral( (int)a->getUnit() )->getName();
		if (name == "KibitPerSecond")
			name = "kibitPerSecond";
		else if (name == "KiBPerSecond")
			name = "kiBPerSecond";
		auto newEenum = sm3::ModelPackage::_instance()->getDataRateUnit();
		auto newUnit = newEenum->getEEnumLiteral(name);
		value->setUnit( (sm3::DataRateUnit)newUnit->getValue() );

		return value;
	}
};
