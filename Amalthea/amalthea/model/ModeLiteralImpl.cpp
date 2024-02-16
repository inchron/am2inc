// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/ModeLiteralImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "ModeLiteral.hpp"
#include <amalthea/model/ModelPackage.hpp>
#include <amalthea/model/ReferableBaseObject.hpp>
#include <amalthea/model/CustomProperty.hpp>
#include <amalthea/model/EnumMode.hpp>
#include <amalthea/model/INamed.hpp>
#include <amalthea/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(ModeLiteralImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::amalthea::model;

void ModeLiteral::_initialize()
{
    // Supertypes
    ::amalthea::model::ReferableBaseObject::_initialize();

    // References

    /*PROTECTED REGION ID(ModeLiteralImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > ModeLiteral::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
<%org.eclipse.app4mc.amalthea.model.EnumMode%> _containingMode = this.getContainingMode();
<%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
if (_containingMode!=null)
{
	_qualifiedNameSegments=_containingMode.getQualifiedNameSegments();
}
if (_qualifiedNameSegments != null)
{
	_elvis = _qualifiedNameSegments;
} else
{
	<%org.eclipse.emf.common.util.BasicEList%><<%java.lang.String%>> _newBasicEList = <%org.eclipse.emf.ecore.xcore.lib.XcoreCollectionLiterals%>.<<%java.lang.String%>>newBasicEList();
	_elvis = _newBasicEList;
}
return _elvis;
#endif
    /*PROTECTED REGION ID(ModeLiteralImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _containingMode = getContainingMode();
    if (_containingMode)
        _qualifiedNameSegments = _containingMode->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

::ecore::EString ModeLiteral::toString()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%java.lang.String%> _xifexpression = null;
boolean _isNullOrEmpty = <%org.eclipse.xtext.xbase.lib.StringExtensions%>.isNullOrEmpty(this.getName());
if (_isNullOrEmpty)
{
	_xifexpression = "<literal>";
}
else
{
	_xifexpression = this.getName();
}
return _xifexpression;
#endif
    /*PROTECTED REGION ID(ModeLiteralImpl_toString) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: amalthea::model::ModeLiteral::toString";
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject ModeLiteral::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::MODELITERAL__CUSTOMPROPERTIES:
    {
        _any = getCustomProperties().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::amalthea::model::ModelPackage::MODELITERAL__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::MODELITERAL__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::MODELITERAL__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::MODELITERAL__CONTAININGMODE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getContainingMode());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void ModeLiteral::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::MODELITERAL__CUSTOMPROPERTIES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getCustomProperties().clear();
        getCustomProperties().insert_all(*_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::MODELITERAL__NAME:
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

::ecore::EBoolean ModeLiteral::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::MODELITERAL__CUSTOMPROPERTIES:
        return getCustomProperties().size() > 0;
    case ::amalthea::model::ModelPackage::MODELITERAL__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::amalthea::model::ModelPackage::MODELITERAL__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::amalthea::model::ModelPackage::MODELITERAL__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::amalthea::model::ModelPackage::MODELITERAL__CONTAININGMODE:
        return getContainingMode().get() != nullptr;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void ModeLiteral::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr ModeLiteral::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::amalthea::model::ModelPackage::_instance()->getModeLiteral();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void ModeLiteral::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::MODELITERAL__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::MODELITERAL__CONTAININGMODE:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::amalthea::model::EnumMode_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::EnumMode > (_t0);

        ::amalthea::model::EnumMode_ptr _old_containingMode =
                getContainingMode();
        if (_old_containingMode && _old_containingMode != _t0)
        {
            ::ecore::EJavaObject _this = ::ecore::EObject::_this();
            _old_containingMode->::ecore::EObject::_inverseRemove(
                    ::amalthea::model::ModelPackage::_instance()->getEnumMode__literals(),
                    _this);
        }

        // set reference
        basicsetContainingMode(_t1);
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void ModeLiteral::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::MODELITERAL__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::MODELITERAL__CONTAININGMODE:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::amalthea::model::EnumMode_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::EnumMode > (_t0);

        // set reference
        if (basicgetContainingMode() == _t1)
            basicsetContainingMode(nullptr);
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

