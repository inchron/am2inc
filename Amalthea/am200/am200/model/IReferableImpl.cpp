// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am200/model/IReferableImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "IReferable.hpp"
#include <am200/model/ModelPackage.hpp>
#include <am200/model/INamed.hpp>
#include <am200/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(IReferableImpl.cpp) ENABLED START*/
#include <algorithm>
/*PROTECTED REGION END*/

using namespace ::am200::model;

void IReferable::_initialize()
{
    // Supertypes
    ::am200::model::INamed::_initialize();

    // References

    /*PROTECTED REGION ID(IReferableImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

::ecore::EString IReferable::getEncodedQualifiedName()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return <%org.eclipse.app4mc.amalthea.model.AmaltheaExtensions%>.toEncodedString(this.getQualifiedNameSegments());
#endif
    /*PROTECTED REGION ID(IReferableImpl_getEncodedQualifiedName) ENABLED START*/

    /* toEncodedString: URLEncode each part and concatenate by "/". */
    auto segments = getQualifiedNameSegments();
    if (segments.empty())
        return ecore::EString("");

    ecore::EString result(segments.front());

    for (auto i = 1u; i < segments.size(); ++i)
    {
        result.append("/");
        result.append(segments[i]);
    }

    std::replace(result.begin(), result.end(), ' ', '+'); // replace all ' ' to '+'
    return result;
    /*PROTECTED REGION END*/
}

::ecore::EBoolean IReferable::validateInvariants(
        [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics,
        [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject > _context)
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return <%org.eclipse.app4mc.amalthea.model.AmaltheaValidations%>.validateInvariants(this, diagnostics);
#endif
    /*PROTECTED REGION ID(IReferableImpl_validateInvariants) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: am200::model::IReferable::validateInvariants";
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject IReferable::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am200::model::ModelPackage::IREFERABLE__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::am200::model::ModelPackage::IREFERABLE__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::am200::model::ModelPackage::IREFERABLE__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void IReferable::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am200::model::ModelPackage::IREFERABLE__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean IReferable::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am200::model::ModelPackage::IREFERABLE__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::am200::model::ModelPackage::IREFERABLE__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::am200::model::ModelPackage::IREFERABLE__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void IReferable::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr IReferable::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am200::model::ModelPackage::_instance()->getIReferable();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void IReferable::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void IReferable::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

