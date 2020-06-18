// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/DiscreteValueConstantImpl.cpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "DiscreteValueConstant.hpp"
#include <amalthea/model/ModelPackage.hpp>
#include <amalthea/model/IDiscreteValueDeviation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(DiscreteValueConstantImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::amalthea::model;

void DiscreteValueConstant::_initialize()
{
    // Supertypes
    ::amalthea::model::IDiscreteValueDeviation::_initialize();

    // References

    /*PROTECTED REGION ID(DiscreteValueConstantImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

::ecore::ELongObject DiscreteValueConstant::getLowerBound()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return <%java.lang.Long%>.valueOf(this.getValue());
#endif
    /*PROTECTED REGION ID(DiscreteValueConstantImpl_getLowerBound) ENABLED START*/
    return getValue();
    /*PROTECTED REGION END*/
}

::ecore::ELongObject DiscreteValueConstant::getUpperBound()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return <%java.lang.Long%>.valueOf(this.getValue());
#endif
    /*PROTECTED REGION ID(DiscreteValueConstantImpl_getUpperBound) ENABLED START*/
    return getValue();
    /*PROTECTED REGION END*/
}

::ecore::EDoubleObject DiscreteValueConstant::getAverage()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return <%java.lang.Double%>.valueOf(<%java.lang.Long%>.valueOf(this.getValue()).doubleValue());
#endif
    /*PROTECTED REGION ID(DiscreteValueConstantImpl_getAverage) ENABLED START*/
    return getValue();
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject DiscreteValueConstant::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::DISCRETEVALUECONSTANT__VALUE:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::ELong
                > ::toAny(_any, getValue());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void DiscreteValueConstant::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::DISCRETEVALUECONSTANT__VALUE:
    {
        ::ecore::ELong _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::ELong
                > ::fromAny(_newValue, _t0);
        setValue(_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean DiscreteValueConstant::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::DISCRETEVALUECONSTANT__VALUE:
        return getValue() != 0;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void DiscreteValueConstant::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr DiscreteValueConstant::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::amalthea::model::ModelPackage::_instance()->getDiscreteValueConstant();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void DiscreteValueConstant::_inverseAdd(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void DiscreteValueConstant::_inverseRemove(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

