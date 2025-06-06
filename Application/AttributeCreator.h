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
/** @file AttributeCreator.h
 * Basic helpers, especially for those types, which are pseudo attributes in
 * the INCHRON model.
 */
#pragma once

#include <ecore/EEnum.hpp>
#include <ecore/EEnumLiteral.hpp>

#include <root.hpp>
#include <root/model/memory/MemoryPackage.hpp>

namespace sm3 = root::model;
namespace sm3m = root::model::memory;
namespace sm3s = root::model::stimulation;


template<class I, class PKG>
struct AttributeCreator {
	template<class A>
	ecore::Ptr<I> operator()( ecore::Ptr<A> );
};

template<class PKG>
struct AttributeCreator<sm3::Time, PKG> {
	template<class A>
	ecore::Ptr<sm3::Time> operator()( ecore::Ptr<A> a ) {
		auto value = sm3::create<sm3::Time>();
		if ( !a )
			return value;

		/* If there is a mismatch regarding the unit mapping, emf4cpp will
		 * throw an exception. In that case we return the empty object, which
		 * was already created. */
		try {
			auto eenum = PKG::_instance()->getTimeUnit();
			auto name = eenum->getEEnumLiteral( (int)a->getUnit() )->getName();
			auto newEenum = sm3::ModelPackage::_instance()->getTimeUnit();
			auto newUnit = newEenum->getEEnumLiteral( name );
			value->setUnit( (sm3::TimeUnit)newUnit->getValue() );
		} catch ( ... ) {
			return value;
		}

		value->setValue( a->getValue() );

		return value;
	}

	template<typename Integer>
	ecore::Ptr<sm3::Time> operator()( Integer v, sm3::TimeUnit u ) {
		auto value = sm3::create<sm3::Time>();
		value->setValue( v );
		value->setUnit( u );
		return value;
	}
};

template<class PKG>
struct AttributeCreator<sm3::Frequency, PKG> {
	template<class A>
	ecore::Ptr<sm3::Frequency> operator()( ecore::Ptr<A> a ) {
		auto value = sm3::create<sm3::Frequency>();
		if ( !a )
			return value;

		/* If there is a mismatch regarding the unit mapping, emf4cpp will
		 * throw an exception. In that case we return the empty object, which
		 * was already created. */
		try {
			auto eenum = PKG::_instance()->getFrequencyUnit();
			auto name = eenum->getEEnumLiteral( (int)a->getUnit() )->getName();
			auto newEenum = sm3::ModelPackage::_instance()->getFrequencyUnit();
			auto newUnit = newEenum->getEEnumLiteral( name );
			value->setUnit( (sm3::FrequencyUnit)newUnit->getValue() );
		} catch ( ... ) {
			return value;
		}

		value->setValue( a->getValue() );

		return value;
	}
};

template<class PKG>
struct AttributeCreator<sm3::DataSize, PKG> {
	template<class A>
	ecore::Ptr<sm3::DataSize> operator()( ecore::Ptr<A> a ) {
		auto value = sm3::create<sm3::DataSize>();
		if ( !a )
			return value;

		/* If there is a mismatch regarding the unit mapping, emf4cpp will
		 * throw an exception. In that case we return the empty object, which
		 * was already created. */
		try {
			auto eenum = PKG::_instance()->getDataSizeUnit();
			auto name = eenum->getEEnumLiteral( (int)a->getUnit() )->getName();
			if ( name == "Kibit" )
				name = "kibit";
			else if ( name == "KiB" )
				name = "kiB";
			auto newEenum = sm3::ModelPackage::_instance()->getDataSizeUnit();
			auto newUnit = newEenum->getEEnumLiteral( name );
			value->setUnit( (sm3::DataSizeUnit)newUnit->getValue() );
		} catch ( ... ) {
			return value;
		}

		value->setValue( a->getValue() );

		return value;
	}

	ecore::Ptr<sm3::DataSize> operator()( ecore::ELong v, sm3::DataSizeUnit u ) {
		auto value = sm3::create<sm3::DataSize>();
		value->setValue( v );
		value->setUnit( u );
		return value;
	}
};

template<class PKG>
struct AttributeCreator<sm3::DataRate, PKG> {
	template<class A>
	ecore::Ptr<sm3::DataRate> operator()( ecore::Ptr<A> a ) {
		auto value = sm3::create<sm3::DataRate>();
		if ( !a )
			return value;

		/* If there is a mismatch regarding the unit mapping, emf4cpp will
		 * throw an exception. In that case we return the empty object, which
		 * was already created. */
		try {
			auto eenum = PKG::_instance()->getDataRateUnit();
			auto name = eenum->getEEnumLiteral( (int)a->getUnit() )->getName();
			if ( name == "KibitPerSecond" )
				name = "kibitPerSecond";
			else if ( name == "KiBPerSecond" )
				name = "kiBPerSecond";
			auto newEenum = sm3::ModelPackage::_instance()->getDataRateUnit();
			auto newUnit = newEenum->getEEnumLiteral( name );
			value->setUnit( (sm3::DataRateUnit)newUnit->getValue() );
		} catch ( ... ) {
			return value;
		}

		value->setValue( a->getValue() );

		return value;
	}
};
