// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/NamespaceImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "Namespace.hpp"
#include <amalthea/model/ModelPackage.hpp>
#include <amalthea/model/ReferableObject.hpp>
#include <amalthea/model/Namespace.hpp>
#include <amalthea/model/INamespaceMember.hpp>
#include <amalthea/model/INamed.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(NamespaceImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::amalthea::model;

void Namespace::_initialize()
{
    // Supertypes
    ::amalthea::model::ReferableObject::_initialize();

    // References
    for (const auto &ref : getNextSegments())
    {
        ref->_initialize();
    }

    /*PROTECTED REGION ID(NamespaceImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

std::vector< ::ecore::EString > Namespace::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
<%org.eclipse.app4mc.amalthea.model.Namespace%> _previousSegment = this.getPreviousSegment();
<%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
if (_previousSegment!=null)
{
	_qualifiedNameSegments=_previousSegment.getQualifiedNameSegments();
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
    /*PROTECTED REGION ID(NamespaceImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _previousSegment = getPreviousSegment();
    if (_previousSegment)
        _qualifiedNameSegments = _previousSegment->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject Namespace::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::NAMESPACE__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::NAMESPACE__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::NAMESPACE__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::NAMESPACE__NEXTSEGMENTS:
    {
        _any = getNextSegments().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::amalthea::model::ModelPackage::NAMESPACE__PREVIOUSSEGMENT:
    {
        _any = ::ecore::as < ::ecore::EObject > (getPreviousSegment());
    }
        return _any;
    case ::amalthea::model::ModelPackage::NAMESPACE__MEMBEROBJECTS:
    {
        _any = getMemberObjects().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void Namespace::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::NAMESPACE__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::amalthea::model::ModelPackage::NAMESPACE__NEXTSEGMENTS:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getNextSegments().clear();
        getNextSegments().insert_all(*_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean Namespace::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::NAMESPACE__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::amalthea::model::ModelPackage::NAMESPACE__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::amalthea::model::ModelPackage::NAMESPACE__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::amalthea::model::ModelPackage::NAMESPACE__NEXTSEGMENTS:
        return getNextSegments().size() > 0;
    case ::amalthea::model::ModelPackage::NAMESPACE__PREVIOUSSEGMENT:
        return getPreviousSegment().get() != nullptr;
    case ::amalthea::model::ModelPackage::NAMESPACE__MEMBEROBJECTS:
        return getMemberObjects().size() > 0;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void Namespace::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr Namespace::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::amalthea::model::ModelPackage::_instance()->getNamespace();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void Namespace::_inverseAdd(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::NAMESPACE__NEXTSEGMENTS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::amalthea::model::Namespace_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::Namespace > (_t0);

        // add to a list
        auto &container =
                (::ecorecpp::mapping::ReferenceEListImpl<
                        ::amalthea::model::Namespace_ptr, -1, true, true >&) ::amalthea::model::Namespace::getNextSegments();
        container.basicAdd(_t1);
    }
        return;
    case ::amalthea::model::ModelPackage::NAMESPACE__PREVIOUSSEGMENT:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_newValue);
        ::amalthea::model::Namespace_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::Namespace > (_t0);

        ::amalthea::model::Namespace_ptr _old_previousSegment =
                getPreviousSegment();
        if (_old_previousSegment && _old_previousSegment != _t0)
        {
            ::ecore::EJavaObject _this = ::ecore::EObject::_this();
            _old_previousSegment->::ecore::EObject::_inverseRemove(
                    ::amalthea::model::ModelPackage::_instance()->getNamespace__nextSegments(),
                    _this);
        }

        // set reference
        basicsetPreviousSegment(_t1);
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void Namespace::_inverseRemove(::ecore::EInt _featureID,
        ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::NAMESPACE__NEXTSEGMENTS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::amalthea::model::Namespace_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::Namespace > (_t0);

        // add to a list
        auto &container =
                (::ecorecpp::mapping::ReferenceEListImpl<
                        ::amalthea::model::Namespace_ptr, -1, true, true >&) ::amalthea::model::Namespace::getNextSegments();
        container.basicRemove(_t1);
    }
        return;
    case ::amalthea::model::ModelPackage::NAMESPACE__PREVIOUSSEGMENT:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EObject_ptr > (_oldValue);
        ::amalthea::model::Namespace_ptr _t1 = std::dynamic_pointer_cast
                < ::amalthea::model::Namespace > (_t0);

        // set reference
        if (basicgetPreviousSegment() == _t1)
            basicsetPreviousSegment(nullptr);
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

