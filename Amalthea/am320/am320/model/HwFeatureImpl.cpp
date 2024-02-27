// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/HwFeatureImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "HwFeature.hpp"
#include <am320/model/ModelPackage.hpp>
#include <am320/model/ReferableBaseObject.hpp>
#include <am320/model/CustomProperty.hpp>
#include <am320/model/HwFeatureCategory.hpp>
#include <am320/model/INamed.hpp>
#include <am320/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(HwFeatureImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am320::model;

void HwFeature::_initialize()
{
    // Supertypes
    ::am320::model::ReferableBaseObject::_initialize();

    // References

    /*PROTECTED REGION ID(HwFeatureImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > HwFeature::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
<%org.eclipse.app4mc.amalthea.model.HwFeatureCategory%> _containingCategory = this.getContainingCategory();
<%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
if (_containingCategory!=null)
{
	_qualifiedNameSegments=_containingCategory.getQualifiedNameSegments();
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
    /*PROTECTED REGION ID(HwFeatureImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _containingCategory = getContainingCategory();
    if (_containingCategory)
        _qualifiedNameSegments =
                _containingCategory->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

::ecore::EString HwFeature::toString()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.app4mc.amalthea.model.HwFeatureCategory%> _containingCategory = this.getContainingCategory();
<%java.lang.String%> _name = null;
if (_containingCategory!=null)
{
	_name=_containingCategory.getName();
}
final <%java.lang.String%> featureName = _name;
<%java.lang.String%> _xifexpression = null;
boolean _isNullOrEmpty = <%org.eclipse.xtext.xbase.lib.StringExtensions%>.isNullOrEmpty(featureName);
if (_isNullOrEmpty)
{
	_xifexpression = "<category>";
}
else
{
	_xifexpression = featureName;
}
<%java.lang.String%> _plus = (_xifexpression + "::");
<%java.lang.String%> _xifexpression_1 = null;
boolean _isNullOrEmpty_1 = <%org.eclipse.xtext.xbase.lib.StringExtensions%>.isNullOrEmpty(this.getName());
if (_isNullOrEmpty_1)
{
	_xifexpression_1 = "<feature>";
}
else
{
	_xifexpression_1 = this.getName();
}
return (_plus + _xifexpression_1);
#endif
    /*PROTECTED REGION ID(HwFeatureImpl_toString) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: am320::model::HwFeature::toString";
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject HwFeature::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am320::model::ModelPackage::HWFEATURE__CUSTOMPROPERTIES:
    {
        _any = getCustomProperties().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am320::model::ModelPackage::HWFEATURE__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::am320::model::ModelPackage::HWFEATURE__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::am320::model::ModelPackage::HWFEATURE__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::am320::model::ModelPackage::HWFEATURE__CONTAININGCATEGORY:
    {
        _any = ::ecore::as < ::ecore::EObject > (getContainingCategory());
    }
        return _any;
    case ::am320::model::ModelPackage::HWFEATURE__VALUE:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EDouble
                > ::toAny(_any, getValue());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void HwFeature::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am320::model::ModelPackage::HWFEATURE__CUSTOMPROPERTIES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getCustomProperties().clear();
        getCustomProperties().insert_all(*_t0);
    }
        return;
    case ::am320::model::ModelPackage::HWFEATURE__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::am320::model::ModelPackage::HWFEATURE__VALUE:
    {
        ::ecore::EDouble _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EDouble
                > ::fromAny(_newValue, _t0);
        setValue(_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean HwFeature::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am320::model::ModelPackage::HWFEATURE__CUSTOMPROPERTIES:
        return getCustomProperties().size() > 0;
    case ::am320::model::ModelPackage::HWFEATURE__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::am320::model::ModelPackage::HWFEATURE__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::am320::model::ModelPackage::HWFEATURE__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::am320::model::ModelPackage::HWFEATURE__CONTAININGCATEGORY:
        return getContainingCategory().get() != nullptr;
    case ::am320::model::ModelPackage::HWFEATURE__VALUE:
        return getValue() != 0.0;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void HwFeature::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr HwFeature::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am320::model::ModelPackage::_instance()->getHwFeature();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void HwFeature::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am320::model::ModelPackage::HWFEATURE__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am320::model::ModelPackage::HWFEATURE__CONTAININGCATEGORY:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::am320::model::HwFeatureCategory_ptr _t1 = std::dynamic_pointer_cast
                < ::am320::model::HwFeatureCategory > (_t0);

        ::am320::model::HwFeatureCategory_ptr _old_containingCategory =
                getContainingCategory();
        if (_old_containingCategory && _old_containingCategory != _t0)
        {
            ::ecore::EJavaObject _this = ::ecore::EObject::_this();
            _old_containingCategory->::ecore::EObject::_inverseRemove(
                    ::am320::model::ModelPackage::_instance()->getHwFeatureCategory__features(),
                    _this);
        }

        // set reference
        basicsetContainingCategory(_t1);
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void HwFeature::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::am320::model::ModelPackage::HWFEATURE__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am320::model::ModelPackage::HWFEATURE__CONTAININGCATEGORY:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::am320::model::HwFeatureCategory_ptr _t1 = std::dynamic_pointer_cast
                < ::am320::model::HwFeatureCategory > (_t0);

        // set reference
        if (basicgetContainingCategory() == _t1)
            basicsetContainingCategory(nullptr);
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

