// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/HwConnectionImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "HwConnection.hpp"
#include <am120/model/ModelPackage.hpp>
#include <am120/model/ReferableBaseObject.hpp>
#include <am120/model/HwPathElement.hpp>
#include <am120/model/ITaggable.hpp>
#include <am120/model/CustomProperty.hpp>
#include <am120/model/Tag.hpp>
#include <am120/model/IDiscreteValueDeviation.hpp>
#include <am120/model/DataRate.hpp>
#include <am120/model/HwPort.hpp>
#include <am120/model/INamed.hpp>
#include <am120/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(HwConnectionImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am120::model;

void HwConnection::_initialize()
{
    // Supertypes
    ::am120::model::ReferableBaseObject::_initialize();
    ::am120::model::HwPathElement::_initialize();
    ::am120::model::ITaggable::_initialize();

    // References
    if (m_readLatency)
    {
        m_readLatency->_initialize();
    }
    if (m_writeLatency)
    {
        m_writeLatency->_initialize();
    }
    if (m_dataRate)
    {
        m_dataRate->_initialize();
    }

    /*PROTECTED REGION ID(HwConnectionImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > HwConnection::getNamePrefixSegments()
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
    /*PROTECTED REGION ID(HwConnectionImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _namedContainer = getNamedContainer();
    if (_namedContainer)
        _qualifiedNameSegments = _namedContainer->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

std::vector< ::am120::model::HwPort_ptr > HwConnection::getPorts()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return <%org.eclipse.emf.common.util.ECollections%>.<<%org.eclipse.app4mc.amalthea.model.HwPort%>>unmodifiableEList(<%org.eclipse.emf.common.util.ECollections%>.<<%org.eclipse.app4mc.amalthea.model.HwPort%>>toEList(<%org.eclipse.xtext.xbase.lib.IterableExtensions%>.<<%org.eclipse.app4mc.amalthea.model.HwPort%>>filterNull(<%org.eclipse.xtext.xbase.lib.CollectionLiterals%>.<<%org.eclipse.app4mc.amalthea.model.HwPort%>>newArrayList(this.getPort1(), this.getPort2()))));
#endif
    /*PROTECTED REGION ID(HwConnectionImpl_getPorts) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: am120::model::HwConnection::getPorts";
    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject HwConnection::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::HWCONNECTION__CUSTOMPROPERTIES:
    {
        _any = getCustomProperties().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__TAGS:
    {
        _any = getTags().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__READLATENCY:
    {
        _any = ::ecore::as < ::ecore::EObject > (getReadLatency());
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__WRITELATENCY:
    {
        _any = ::ecore::as < ::ecore::EObject > (getWriteLatency());
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__DATARATE:
    {
        _any = ::ecore::as < ::ecore::EObject > (getDataRate());
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT1:
    {
        _any = ::ecore::as < ::ecore::EObject > (getPort1());
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT2:
    {
        _any = ::ecore::as < ::ecore::EObject > (getPort2());
    }
        return _any;
    case ::am120::model::ModelPackage::HWCONNECTION__INTERNAL:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EBoolean
                > ::toAny(_any, isInternal());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void HwConnection::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::HWCONNECTION__CUSTOMPROPERTIES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getCustomProperties().clear();
        getCustomProperties().insert_all(*_t0);
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__TAGS:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getTags().clear();
        getTags().insert_all(*_t0);
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__READLATENCY:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am120::model::IDiscreteValueDeviation
                > (_t0);
        setReadLatency(_t1);
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__WRITELATENCY:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am120::model::IDiscreteValueDeviation
                > (_t0);
        setWriteLatency(_t1);
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__DATARATE:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am120::model::DataRate > (_t0);
        setDataRate(_t1);
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT1:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am120::model::HwPort > (_t0);
        setPort1(_t1);
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT2:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast < ::ecore::EObject_ptr
                > (_newValue);
        auto _t1 = ::ecore::as < ::am120::model::HwPort > (_t0);
        setPort2(_t1);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean HwConnection::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::HWCONNECTION__CUSTOMPROPERTIES:
        return getCustomProperties().size() > 0;
    case ::am120::model::ModelPackage::HWCONNECTION__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::am120::model::ModelPackage::HWCONNECTION__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::am120::model::ModelPackage::HWCONNECTION__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::am120::model::ModelPackage::HWCONNECTION__TAGS:
        return getTags().size() > 0;
    case ::am120::model::ModelPackage::HWCONNECTION__READLATENCY:
        return getReadLatency().get() != nullptr;
    case ::am120::model::ModelPackage::HWCONNECTION__WRITELATENCY:
        return getWriteLatency().get() != nullptr;
    case ::am120::model::ModelPackage::HWCONNECTION__DATARATE:
        return getDataRate().get() != nullptr;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT1:
        return getPort1().get() != nullptr;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT2:
        return getPort2().get() != nullptr;
    case ::am120::model::ModelPackage::HWCONNECTION__INTERNAL:
        return ::ecorecpp::mapping::set_traits < ::ecore::EBoolean
                > ::is_set(isInternal());

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void HwConnection::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr HwConnection::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am120::model::ModelPackage::_instance()->getHwConnection();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void HwConnection::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::HWCONNECTION__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__TAGS:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__READLATENCY:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__WRITELATENCY:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__DATARATE:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT1:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT2:
    {
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void HwConnection::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::HWCONNECTION__CUSTOMPROPERTIES:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__TAGS:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__READLATENCY:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__WRITELATENCY:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__DATARATE:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT1:
    {
    }
        return;
    case ::am120::model::ModelPackage::HWCONNECTION__PORT2:
    {
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

