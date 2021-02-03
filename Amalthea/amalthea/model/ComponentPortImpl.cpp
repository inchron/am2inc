// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/ComponentPortImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "ComponentPort.hpp"
#include <amalthea/model/ModelPackage.hpp>
#include <amalthea/model/ReferableBaseObject.hpp>
#include <amalthea/model/ITaggable.hpp>
#include <amalthea/model/CustomProperty.hpp>
#include <amalthea/model/Tag.hpp>
#include <amalthea/model/Component.hpp>
#include <amalthea/model/ComponentInterface.hpp>
#include <amalthea/model/INamed.hpp>
#include <amalthea/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(ComponentPortImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::amalthea::model;

void ComponentPort::_initialize()
{
    // Supertypes
    ::amalthea::model::ReferableBaseObject::_initialize();
    ::amalthea::model::ITaggable::_initialize();

    // References

    /*PROTECTED REGION ID(ComponentPortImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > ComponentPort::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
<%org.eclipse.app4mc.amalthea.model.Component%> _containingComponent = this.getContainingComponent();
<%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
if (_containingComponent!=null)
{
	_qualifiedNameSegments=_containingComponent.getQualifiedNameSegments();
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
    /*PROTECTED REGION ID(ComponentPortImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _containingComponent = getContainingComponent();
    if (_containingComponent)
        _qualifiedNameSegments =
                _containingComponent->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject ComponentPort::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CUSTOMPROPERTIES:
    {
        _any = getCustomProperties().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__TAGS:
    {
        _any = getTags().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CONTAININGCOMPONENT:
    {
        _any = ::ecore::as < ::ecore::EObject > (getContainingComponent());
    }
        return _any;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__KIND:
    {
        ::ecorecpp::mapping::any_traits < ::amalthea::model::InterfaceKind
                > ::toAny(_any, getKind());
    }
        return _any;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__INTERFACE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getInterface());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void ComponentPort::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CUSTOMPROPERTIES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getCustomProperties().clear();
        getCustomProperties().insert_all(*_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__TAGS:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getTags().clear();
        getTags().insert_all(*_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__KIND:
    {
        ::amalthea::model::InterfaceKind _t0;
        ::ecorecpp::mapping::any_traits < ::amalthea::model::InterfaceKind
                > ::fromAny(_newValue, _t0);
        setKind(_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__INTERFACE:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::amalthea::model::ComponentInterface > (_t0);
        setInterface(_t1);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean ComponentPort::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CUSTOMPROPERTIES:
        return getCustomProperties().size() > 0;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::amalthea::model::ModelPackage::COMPONENTPORT__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::amalthea::model::ModelPackage::COMPONENTPORT__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::amalthea::model::ModelPackage::COMPONENTPORT__TAGS:
        return getTags().size() > 0;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CONTAININGCOMPONENT:
        return getContainingComponent().get() != nullptr;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__KIND:
        return ::ecorecpp::mapping::set_traits
                < ::amalthea::model::InterfaceKind > ::is_set(getKind());
    case ::amalthea::model::ModelPackage::COMPONENTPORT__INTERFACE:
        return getInterface().get() != nullptr;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void ComponentPort::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr ComponentPort::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::amalthea::model::ModelPackage::_instance()->getComponentPort();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void ComponentPort::_inverseAdd(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__TAGS:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CONTAININGCOMPONENT:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::amalthea::model::Component_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::Component > (_t0);

        ::amalthea::model::Component_ptr _old_containingComponent =
                getContainingComponent();
        if (_old_containingComponent && _old_containingComponent != _t0)
        {
            ::ecore::EJavaObject _this = ::ecore::EObject::_this();
            _old_containingComponent->::ecore::EObject::_inverseRemove(
                    ::amalthea::model::ModelPackage::_instance()->getComponent__ports(),
                    _this);
        }

        // set reference
        basicsetContainingComponent(_t1);
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__INTERFACE:
    {
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void ComponentPort::_inverseRemove(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__TAGS:
    {
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__CONTAININGCOMPONENT:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::amalthea::model::Component_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::Component > (_t0);

        // set reference
        if (basicgetContainingComponent() == _t1)
            basicsetContainingComponent(nullptr);
    }
        return;
    case ::amalthea::model::ModelPackage::COMPONENTPORT__INTERFACE:
    {
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

