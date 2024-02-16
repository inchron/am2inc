// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * root/model/TimeImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "Time.hpp"
#include <root/model/ModelPackage.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(TimeImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::root::model;

void Time::_initialize()
{
    // Supertypes

    // References

    /*PROTECTED REGION ID(TimeImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

void Time::denormalize()
{
    /*PROTECTED REGION ID(TimeImpl_denormalize) ENABLED START*/
    if (m_unit <= TimeUnit::fs)
    {
        while (m_unit > TimeUnit::s)
        {
            ::ecore::ELong newValue = m_value / 1000;
            ::ecore::ELong oldValue = newValue * 1000;
            if (oldValue == m_value)
            {
                m_unit = TimeUnit((int) m_unit - 1);
                m_value = newValue;
            }
            else
                break;
        }
    }
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject Time::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::root::model::ModelPackage::TIME__VALUE:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::ELong
                > ::toAny(_any, getValue());
    }
        return _any;
    case ::root::model::ModelPackage::TIME__UNIT:
    {
        ::ecorecpp::mapping::any_traits < ::root::model::TimeUnit
                > ::toAny(_any, getUnit());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void Time::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::root::model::ModelPackage::TIME__VALUE:
    {
        ::ecore::ELong _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::ELong
                > ::fromAny(_newValue, _t0);
        setValue(_t0);
    }
        return;
    case ::root::model::ModelPackage::TIME__UNIT:
    {
        ::root::model::TimeUnit _t0;
        ::ecorecpp::mapping::any_traits < ::root::model::TimeUnit
                > ::fromAny(_newValue, _t0);
        setUnit(_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean Time::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::root::model::ModelPackage::TIME__VALUE:
        return getValue() != 0;
    case ::root::model::ModelPackage::TIME__UNIT:
        return getUnit() != ::root::model::TimeUnit::ps;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void Time::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr Time::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::root::model::ModelPackage::_instance()->getTime();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void Time::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void Time::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

