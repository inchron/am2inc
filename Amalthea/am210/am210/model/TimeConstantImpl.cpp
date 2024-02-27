// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/TimeConstantImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "TimeConstant.hpp"
#include <am210/model/ModelPackage.hpp>
#include <am210/model/ITimeDeviation.hpp>
#include <am210/model/Time.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(TimeConstantImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am210::model;

void TimeConstant::_initialize()
{
    // Supertypes
    ::am210::model::ITimeDeviation::_initialize();

    // References
    if (m_value)
    {
        m_value->_initialize();
    }

    /*PROTECTED REGION ID(TimeConstantImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

::am210::model::Time_ptr TimeConstant::getLowerBound()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return this.getValue();
#endif
    /*PROTECTED REGION ID(TimeConstantImpl_getLowerBound) ENABLED START*/
    return getValue();
    /*PROTECTED REGION END*/
}

::am210::model::Time_ptr TimeConstant::getUpperBound()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return this.getValue();
#endif
    /*PROTECTED REGION ID(TimeConstantImpl_getUpperBound) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    return getValue();
    /*PROTECTED REGION END*/
}

::am210::model::Time_ptr TimeConstant::getAverage()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return this.getValue();
#endif
    /*PROTECTED REGION ID(TimeConstantImpl_getAverage) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    return getValue();
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject TimeConstant::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::TIMECONSTANT__VALUE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getValue());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void TimeConstant::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::TIMECONSTANT__VALUE:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am210::model::Time > (_t0);
        setValue(_t1);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean TimeConstant::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::TIMECONSTANT__VALUE:
        return getValue().get() != nullptr;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void TimeConstant::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr TimeConstant::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am210::model::ModelPackage::_instance()->getTimeConstant();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void TimeConstant::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::TIMECONSTANT__VALUE:
    {
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void TimeConstant::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::TIMECONSTANT__VALUE:
    {
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

