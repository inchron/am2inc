// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/DiscreteValueIntervalImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "DiscreteValueInterval.hpp"
#include <am220/model/ModelPackage.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(DiscreteValueIntervalImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am220::model;

void DiscreteValueInterval::_initialize()
{
    // Supertypes

    // References

    /*PROTECTED REGION ID(DiscreteValueIntervalImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

::ecore::EDoubleObject DiscreteValueInterval::getAverage()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return <%org.eclipse.app4mc.amalthea.model.AmaltheaServices2%>.getAverage(this.getLowerBound(), this.getUpperBound());
#endif
    /*PROTECTED REGION ID(DiscreteValueIntervalImpl_getAverage) ENABLED START*/
    ecore::EDoubleObject avg = getLowerBound() + getUpperBound();
    avg /= 2.;
    return avg;
    /*PROTECTED REGION END*/
}

::ecore::EBoolean DiscreteValueInterval::validateInvariants(
        [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics,
        [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject > _context)
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return <%org.eclipse.app4mc.amalthea.model.AmaltheaValidations%>.validateInvariants(this, diagnostics);
#endif
    /*PROTECTED REGION ID(DiscreteValueIntervalImpl_validateInvariants) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: am220::model::DiscreteValueInterval::validateInvariants";
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject DiscreteValueInterval::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am220::model::ModelPackage::DISCRETEVALUEINTERVAL__LOWERBOUND:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::ELongObject
                > ::toAny(_any, getLowerBound());
    }
        return _any;
    case ::am220::model::ModelPackage::DISCRETEVALUEINTERVAL__UPPERBOUND:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::ELongObject
                > ::toAny(_any, getUpperBound());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void DiscreteValueInterval::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am220::model::ModelPackage::DISCRETEVALUEINTERVAL__LOWERBOUND:
    {
        ::ecore::ELongObject _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::ELongObject
                > ::fromAny(_newValue, _t0);
        setLowerBound(_t0);
    }
        return;
    case ::am220::model::ModelPackage::DISCRETEVALUEINTERVAL__UPPERBOUND:
    {
        ::ecore::ELongObject _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::ELongObject
                > ::fromAny(_newValue, _t0);
        setUpperBound(_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean DiscreteValueInterval::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am220::model::ModelPackage::DISCRETEVALUEINTERVAL__LOWERBOUND:
        return getLowerBound() != 0;
    case ::am220::model::ModelPackage::DISCRETEVALUEINTERVAL__UPPERBOUND:
        return getUpperBound() != 0;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void DiscreteValueInterval::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr DiscreteValueInterval::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am220::model::ModelPackage::_instance()->getDiscreteValueInterval();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void DiscreteValueInterval::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void DiscreteValueInterval::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

