// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/RunnableParameterImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "RunnableParameter.hpp"
#include <am120/model/ModelPackage.hpp>
#include <am120/model/ReferableBaseObject.hpp>
#include <am120/model/IDependsOn.hpp>
#include <am120/model/CustomProperty.hpp>
#include <am120/model/DataDependency.hpp>
#include <am120/model/Runnable.hpp>
#include <am120/model/TypeDefinition.hpp>
#include <am120/model/INamed.hpp>
#include <am120/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(RunnableParameterImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am120::model;

void RunnableParameter::_initialize()
{
    // Supertypes
    ::am120::model::ReferableBaseObject::_initialize();
    ::am120::model::IDependsOn::_initialize();

    // References

    /*PROTECTED REGION ID(RunnableParameterImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > RunnableParameter::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
<%org.eclipse.app4mc.amalthea.model.Runnable%> _containingRunnable = this.getContainingRunnable();
<%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
if (_containingRunnable!=null)
{
	_qualifiedNameSegments=_containingRunnable.getQualifiedNameSegments();
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
    /*PROTECTED REGION ID(RunnableParameterImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _containingRunnable = getContainingRunnable();
    if (_containingRunnable)
        _qualifiedNameSegments =
                _containingRunnable->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

::ecore::EString RunnableParameter::toString()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.app4mc.amalthea.model.Runnable%> _containingRunnable = this.getContainingRunnable();
<%java.lang.String%> _name = null;
if (_containingRunnable!=null)
{
	_name=_containingRunnable.getName();
}
final <%java.lang.String%> runName = _name;
<%java.lang.String%> _xifexpression = null;
boolean _isNullOrEmpty = <%org.eclipse.xtext.xbase.lib.StringExtensions%>.isNullOrEmpty(runName);
if (_isNullOrEmpty)
{
	_xifexpression = "<runnable>";
}
else
{
	_xifexpression = runName;
}
<%java.lang.String%> _plus = (_xifexpression + "::");
<%java.lang.String%> _xifexpression_1 = null;
boolean _isNullOrEmpty_1 = <%org.eclipse.xtext.xbase.lib.StringExtensions%>.isNullOrEmpty(this.getName());
if (_isNullOrEmpty_1)
{
	_xifexpression_1 = "<parameter>";
}
else
{
	_xifexpression_1 = this.getName();
}
return (_plus + _xifexpression_1);
#endif
    /*PROTECTED REGION ID(RunnableParameterImpl_toString) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: am120::model::RunnableParameter::toString";
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject RunnableParameter::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CUSTOMPROPERTIES:
    {
        _any = getCustomProperties().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DEPENDSON:
    {
        _any = ::ecore::as < ::ecore::EObject > (getDependsOn());
    }
        return _any;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CONTAININGRUNNABLE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getContainingRunnable());
    }
        return _any;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DIRECTION:
    {
        ::ecorecpp::mapping::any_traits < ::am120::model::DirectionType
                > ::toAny(_any, getDirection());
    }
        return _any;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DATATYPE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getDataType());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void RunnableParameter::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CUSTOMPROPERTIES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getCustomProperties().clear();
        getCustomProperties().insert_all(*_t0);
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DEPENDSON:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am120::model::DataDependency > (_t0);
        setDependsOn(_t1);
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DIRECTION:
    {
        ::am120::model::DirectionType _t0;
        ::ecorecpp::mapping::any_traits < ::am120::model::DirectionType
                > ::fromAny(_newValue, _t0);
        setDirection(_t0);
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DATATYPE:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am120::model::TypeDefinition > (_t0);
        setDataType(_t1);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean RunnableParameter::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CUSTOMPROPERTIES:
        return getCustomProperties().size() > 0;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DEPENDSON:
        return getDependsOn().get() != nullptr;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CONTAININGRUNNABLE:
        return getContainingRunnable().get() != nullptr;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DIRECTION:
        return ::ecorecpp::mapping::set_traits < ::am120::model::DirectionType
                > ::is_set(getDirection());
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DATATYPE:
        return getDataType().get() != nullptr;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void RunnableParameter::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr RunnableParameter::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am120::model::ModelPackage::_instance()->getRunnableParameter();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void RunnableParameter::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DEPENDSON:
    {
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CONTAININGRUNNABLE:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::am120::model::Runnable_ptr _t1 = std::dynamic_pointer_cast
                < ::am120::model::Runnable > (_t0);

        ::am120::model::Runnable_ptr _old_containingRunnable =
                getContainingRunnable();
        if (_old_containingRunnable && _old_containingRunnable != _t0)
        {
            ::ecore::EJavaObject _this = ::ecore::EObject::_this();
            _old_containingRunnable->::ecore::EObject::_inverseRemove(
                    ::am120::model::ModelPackage::_instance()->getRunnable__parameters(),
                    _this);
        }

        // set reference
        basicsetContainingRunnable(_t1);
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DATATYPE:
    {
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void RunnableParameter::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DEPENDSON:
    {
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__CONTAININGRUNNABLE:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::am120::model::Runnable_ptr _t1 = std::dynamic_pointer_cast
                < ::am120::model::Runnable > (_t0);

        // set reference
        if (basicgetContainingRunnable() == _t1)
            basicsetContainingRunnable(nullptr);
    }
        return;
    case ::am120::model::ModelPackage::RUNNABLEPARAMETER__DATATYPE:
    {
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

