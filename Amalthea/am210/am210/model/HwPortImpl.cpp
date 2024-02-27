// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/HwPortImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "HwPort.hpp"
#include <am210/model/ModelPackage.hpp>
#include <am210/model/ReferableBaseObject.hpp>
#include <am210/model/ITaggable.hpp>
#include <am210/model/CustomProperty.hpp>
#include <am210/model/Tag.hpp>
#include <am210/model/HwConnection.hpp>
#include <am210/model/INamed.hpp>
#include <am210/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(HwPortImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am210::model;

void HwPort::_initialize()
{
    // Supertypes
    ::am210::model::ReferableBaseObject::_initialize();
    ::am210::model::ITaggable::_initialize();

    // References

    /*PROTECTED REGION ID(HwPortImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > HwPort::getNamePrefixSegments()
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
    /*PROTECTED REGION ID(HwPortImpl_getNamePrefixSegments) ENABLED START*/
    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _namedContainer = getNamedContainer();
    if (_namedContainer)
        _qualifiedNameSegments = _namedContainer->getQualifiedNameSegments();
    return _qualifiedNameSegments;
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject HwPort::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::HWPORT__CUSTOMPROPERTIES:
    {
        _any = getCustomProperties().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__TAGS:
    {
        _any = getTags().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__BITWIDTH:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EInt
                > ::toAny(_any, getBitWidth());
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__PRIORITY:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EInt
                > ::toAny(_any, getPriority());
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__PORTTYPE:
    {
        ::ecorecpp::mapping::any_traits < ::am210::model::PortType
                > ::toAny(_any, getPortType());
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__PORTINTERFACE:
    {
        ::ecorecpp::mapping::any_traits < ::am210::model::PortInterface
                > ::toAny(_any, getPortInterface());
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__DELEGATED:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EBoolean
                > ::toAny(_any, isDelegated());
    }
        return _any;
    case ::am210::model::ModelPackage::HWPORT__CONNECTIONS:
    {
        _any = getConnections().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void HwPort::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::HWPORT__CUSTOMPROPERTIES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getCustomProperties().clear();
        getCustomProperties().insert_all(*_t0);
    }
        return;
    case ::am210::model::ModelPackage::HWPORT__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::am210::model::ModelPackage::HWPORT__TAGS:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getTags().clear();
        getTags().insert_all(*_t0);
    }
        return;
    case ::am210::model::ModelPackage::HWPORT__BITWIDTH:
    {
        ::ecore::EInt _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EInt
                > ::fromAny(_newValue, _t0);
        setBitWidth(_t0);
    }
        return;
    case ::am210::model::ModelPackage::HWPORT__PRIORITY:
    {
        ::ecore::EInt _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EInt
                > ::fromAny(_newValue, _t0);
        setPriority(_t0);
    }
        return;
    case ::am210::model::ModelPackage::HWPORT__PORTTYPE:
    {
        ::am210::model::PortType _t0;
        ::ecorecpp::mapping::any_traits < ::am210::model::PortType
                > ::fromAny(_newValue, _t0);
        setPortType(_t0);
    }
        return;
    case ::am210::model::ModelPackage::HWPORT__PORTINTERFACE:
    {
        ::am210::model::PortInterface _t0;
        ::ecorecpp::mapping::any_traits < ::am210::model::PortInterface
                > ::fromAny(_newValue, _t0);
        setPortInterface(_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean HwPort::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::HWPORT__CUSTOMPROPERTIES:
        return getCustomProperties().size() > 0;
    case ::am210::model::ModelPackage::HWPORT__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::am210::model::ModelPackage::HWPORT__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::am210::model::ModelPackage::HWPORT__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::am210::model::ModelPackage::HWPORT__TAGS:
        return getTags().size() > 0;
    case ::am210::model::ModelPackage::HWPORT__BITWIDTH:
        return getBitWidth() != 0;
    case ::am210::model::ModelPackage::HWPORT__PRIORITY:
        return getPriority() != 0;
    case ::am210::model::ModelPackage::HWPORT__PORTTYPE:
        return ::ecorecpp::mapping::set_traits < ::am210::model::PortType
                > ::is_set(getPortType());
    case ::am210::model::ModelPackage::HWPORT__PORTINTERFACE:
        return ::ecorecpp::mapping::set_traits < ::am210::model::PortInterface
                > ::is_set(getPortInterface());
    case ::am210::model::ModelPackage::HWPORT__DELEGATED:
        return ::ecorecpp::mapping::set_traits < ::ecore::EBoolean
                > ::is_set(isDelegated());
    case ::am210::model::ModelPackage::HWPORT__CONNECTIONS:
        return getConnections().size() > 0;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void HwPort::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr HwPort::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am210::model::ModelPackage::_instance()->getHwPort();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void HwPort::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::HWPORT__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am210::model::ModelPackage::HWPORT__TAGS:
    {
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void HwPort::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::am210::model::ModelPackage::HWPORT__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am210::model::ModelPackage::HWPORT__TAGS:
    {
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

