// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/SubInterfaceImpl.cpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "SubInterface.hpp"
#include <amalthea/model/ModelPackage.hpp>
#include <amalthea/model/ComponentInterface.hpp>
#include <amalthea/model/CustomProperty.hpp>
#include <amalthea/model/Tag.hpp>
#include <amalthea/model/TypeDefinition.hpp>
#include <amalthea/model/SubInterface.hpp>
#include <amalthea/model/INamed.hpp>
#include <amalthea/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(SubInterfaceImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::amalthea::model;

void SubInterface::_initialize()
{
    // Supertypes
    ::amalthea::model::ComponentInterface::_initialize();

    // References

    /*PROTECTED REGION ID(SubInterfaceImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > SubInterface::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
    <%org.eclipse.app4mc.amalthea.model.ComponentInterface%> _containingInterface = this.getContainingInterface();
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
    if (_containingInterface!=null)
    {
        _qualifiedNameSegments=_containingInterface.getQualifiedNameSegments();
    }
    if (_qualifiedNameSegments != null)
    {
        _elvis = _qualifiedNameSegments;
    }
    else
    {
        <%org.eclipse.emf.common.util.BasicEList%><<%java.lang.String%>> _newBasicEList = <%org.eclipse.emf.ecore.xcore.lib.XcoreCollectionLiterals%>.<<%java.lang.String%>>newBasicEList();
        _elvis = _newBasicEList;
    }
    return _elvis;
#endif
    /*PROTECTED REGION ID(SubInterfaceImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _containingInterface = getContainingInterface(); // ecore::as<ComponentInterface>(eContainer());
    if (_containingInterface)
        _qualifiedNameSegments =
                _containingInterface->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject SubInterface::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CUSTOMPROPERTIES:
    {
        _any = getCustomProperties().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__TAGS:
    {
        _any = getTags().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__DATATYPE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getDatatype());
    }
        return _any;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__SUBINTERFACES:
    {
        _any = getSubInterfaces().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CONTAININGINTERFACE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getContainingInterface());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void SubInterface::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CUSTOMPROPERTIES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getCustomProperties().clear();
        getCustomProperties().insert_all(*_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__TAGS:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getTags().clear();
        getTags().insert_all(*_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__DATATYPE:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::amalthea::model::TypeDefinition > (_t0);
        setDatatype(_t1);
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__SUBINTERFACES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getSubInterfaces().clear();
        getSubInterfaces().insert_all(*_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean SubInterface::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CUSTOMPROPERTIES:
        return getCustomProperties().size() > 0;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::amalthea::model::ModelPackage::SUBINTERFACE__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::amalthea::model::ModelPackage::SUBINTERFACE__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::amalthea::model::ModelPackage::SUBINTERFACE__TAGS:
        return getTags().size() > 0;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__DATATYPE:
        return getDatatype().get() != nullptr;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__SUBINTERFACES:
        return getSubInterfaces().size() > 0;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CONTAININGINTERFACE:
        return getContainingInterface().get() != nullptr;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void SubInterface::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr SubInterface::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::amalthea::model::ModelPackage::_instance()->getSubInterface();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void SubInterface::_inverseAdd(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__TAGS:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__DATATYPE:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__SUBINTERFACES:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::amalthea::model::SubInterface_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::SubInterface > (_t0);

        // add to a list
        auto& container =
                (::ecorecpp::mapping::ReferenceEListImpl<
                        ::amalthea::model::SubInterface_ptr, -1, true, true >&) ::amalthea::model::ComponentInterface::getSubInterfaces();
        container.basicAdd(_t1);
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CONTAININGINTERFACE:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::amalthea::model::ComponentInterface_ptr _t1 =
                std::dynamic_pointer_cast
                        < ::amalthea::model::ComponentInterface > (_t0);

        ::amalthea::model::ComponentInterface_ptr _old_containingInterface =
                getContainingInterface();
        if (_old_containingInterface && _old_containingInterface != _t0)
        {
            ::ecore::EJavaObject _this = ::ecore::EObject::_this();
            _old_containingInterface->::ecore::EObject::_inverseRemove(
                    ::amalthea::model::ModelPackage::_instance()->getComponentInterface__subInterfaces(),
                    _this);
        }

        // set reference
        basicsetContainingInterface(_t1);
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void SubInterface::_inverseRemove(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _oldValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__TAGS:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__DATATYPE:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__SUBINTERFACES:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::amalthea::model::SubInterface_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::SubInterface > (_t0);

        // add to a list
        auto& container =
                (::ecorecpp::mapping::ReferenceEListImpl<
                        ::amalthea::model::SubInterface_ptr, -1, true, true >&) ::amalthea::model::ComponentInterface::getSubInterfaces();
        container.basicRemove(_t1);
    }
        return;
    case ::amalthea::model::ModelPackage::SUBINTERFACE__CONTAININGINTERFACE:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::amalthea::model::ComponentInterface_ptr _t1 =
                std::dynamic_pointer_cast
                        < ::amalthea::model::ComponentInterface > (_t0);

        // set reference
        if (basicgetContainingInterface() == _t1)
            basicsetContainingInterface(nullptr);
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

