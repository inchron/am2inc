// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am200/model/ComponentInstanceImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "ComponentInstance.hpp"
#include <am200/model/ModelPackage.hpp>
#include <am200/model/ReferableBaseObject.hpp>
#include <am200/model/ITaggable.hpp>
#include <am200/model/CustomProperty.hpp>
#include <am200/model/Tag.hpp>
#include <am200/model/ISystem.hpp>
#include <am200/model/Component.hpp>
#include <am200/model/INamed.hpp>
#include <am200/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(ComponentInstanceImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am200::model;

void ComponentInstance::_initialize()
{
    // Supertypes
    ::am200::model::ReferableBaseObject::_initialize();
    ::am200::model::ITaggable::_initialize();

    // References

    /*PROTECTED REGION ID(ComponentInstanceImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > ComponentInstance::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
<%org.eclipse.app4mc.amalthea.model.INamed%> _namedContainer = this.getNamedContainer();
<%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
if (_namedContainer!=null)
{
	_qualifiedNameSegments=_namedContainer.getQualifiedNameSegments();
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
    /*PROTECTED REGION ID(ComponentInstanceImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _namedContainer = getNamedContainer();
    if (_namedContainer)
        _qualifiedNameSegments = _namedContainer->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject ComponentInstance::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CUSTOMPROPERTIES:
    {
        _any = getCustomProperties().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TAGS:
    {
        _any = getTags().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CONTAININGSYSTEM:
    {
        _any = ::ecore::as < ::ecore::EObject > (getContainingSystem());
    }
        return _any;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TYPE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getType());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void ComponentInstance::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CUSTOMPROPERTIES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getCustomProperties().clear();
        getCustomProperties().insert_all(*_t0);
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TAGS:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getTags().clear();
        getTags().insert_all(*_t0);
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CONTAININGSYSTEM:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am200::model::ISystem > (_t0);
        setContainingSystem(_t1);
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TYPE:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am200::model::Component > (_t0);
        setType(_t1);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean ComponentInstance::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CUSTOMPROPERTIES:
        return getCustomProperties().size() > 0;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TAGS:
        return getTags().size() > 0;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CONTAININGSYSTEM:
        return getContainingSystem().get() != nullptr;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TYPE:
        return getType().get() != nullptr;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void ComponentInstance::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr ComponentInstance::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am200::model::ModelPackage::_instance()->getComponentInstance();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void ComponentInstance::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TAGS:
    {
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CONTAININGSYSTEM:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::am200::model::ISystem_ptr _t1 = std::dynamic_pointer_cast
                < ::am200::model::ISystem > (_t0);

        ::am200::model::ISystem_ptr _old_containingSystem =
                getContainingSystem();
        if (_old_containingSystem && _old_containingSystem != _t0)
        {
            ::ecore::EJavaObject _this = ::ecore::EObject::_this();
            _old_containingSystem->::ecore::EObject::_inverseRemove(
                    ::am200::model::ModelPackage::_instance()->getISystem__componentInstances(),
                    _this);
        }

        // set reference
        basicsetContainingSystem(_t1);
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TYPE:
    {
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void ComponentInstance::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TAGS:
    {
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__CONTAININGSYSTEM:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::am200::model::ISystem_ptr _t1 = std::dynamic_pointer_cast
                < ::am200::model::ISystem > (_t0);

        // set reference
        if (basicgetContainingSystem() == _t1)
            basicsetContainingSystem(nullptr);
    }
        return;
    case ::am200::model::ModelPackage::COMPONENTINSTANCE__TYPE:
    {
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

