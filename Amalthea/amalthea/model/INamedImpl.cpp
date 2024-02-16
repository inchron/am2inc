// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/INamedImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "INamed.hpp"
#include <amalthea/model/ModelPackage.hpp>
#include <amalthea/model/INamed.hpp>
#include <amalthea/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(INamedImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::amalthea::model;

void INamed::_initialize()
{
    // Supertypes

    // References

    /*PROTECTED REGION ID(INamedImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

::amalthea::model::INamed_ptr INamed::getNamedContainer()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.app4mc.amalthea.model.INamed%> _xifexpression = null;
<%org.eclipse.emf.ecore.EObject%> _eContainer = this.eContainer();
if ((_eContainer instanceof <%org.eclipse.app4mc.amalthea.model.INamed%>))
{
	<%org.eclipse.emf.ecore.EObject%> _eContainer_1 = this.eContainer();
	_xifexpression = ((<%org.eclipse.app4mc.amalthea.model.INamed%>) _eContainer_1);
}
else
{
	_xifexpression = null;
}
return _xifexpression;
#endif
    /*PROTECTED REGION ID(INamedImpl_getNamedContainer) ENABLED START*/
    auto _eContainer = eContainer();
    return ecore::as < INamed > (_eContainer);
    /*PROTECTED REGION END*/
}

::ecore::EString INamed::getNamePrefix()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%java.lang.String%> _xifexpression = null;
<%org.eclipse.app4mc.amalthea.model.Namespace%> _namespace = this.getNamespace();
boolean _tripleEquals = (_namespace == null);
if (_tripleEquals)
{
	return "";
}
else
{
	_xifexpression = <%org.eclipse.app4mc.amalthea.model.AmaltheaExtensions%>.toPlainString(this.getNamePrefixSegments(), this.getDefaultNameSeparator());
}
return _xifexpression;
#endif
    /*PROTECTED REGION ID(INamedImpl_getNamePrefix) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: amalthea::model::INamed::getNamePrefix";
    /*PROTECTED REGION END*/
}

std::vector< ::ecore::EString > INamed::getQualifiedNameSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    final <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> segments = this.getNamePrefixSegments();
<%java.lang.String%> _name = this.getName();
boolean _tripleNotEquals = (_name != null);
if (_tripleNotEquals)
{
	segments.add(this.getName());
}
return segments;
#endif
    /*PROTECTED REGION ID(INamedImpl_getQualifiedNameSegments) ENABLED START*/

    /* Create a vector of names of all namespaces. */
    auto segments = getNamePrefixSegments();
    if (!getName().empty())
        segments.push_back(getName());
    return segments;

    /*PROTECTED REGION END*/
}

::ecore::EString INamed::getDefaultNameSeparator()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return ".";
#endif
    /*PROTECTED REGION ID(INamedImpl_getDefaultNameSeparator) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: amalthea::model::INamed::getDefaultNameSeparator";
    /*PROTECTED REGION END*/
}

::amalthea::model::Namespace_ptr INamed::getNamespace()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return null;
#endif
    /*PROTECTED REGION ID(INamedImpl_getNamespace) ENABLED START*/
    return Namespace_ptr();
    /*PROTECTED REGION END*/
}

std::vector< ::ecore::EString > INamed::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
<%org.eclipse.app4mc.amalthea.model.Namespace%> _namespace = this.getNamespace();
<%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
if (_namespace!=null)
{
	_qualifiedNameSegments=_namespace.getQualifiedNameSegments();
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
    /*PROTECTED REGION ID(INamedImpl_getNamePrefixSegments) ENABLED START*/

    if (!getNamespace())
        return std::vector< ecore::EString >();
    return getNamespace()->getQualifiedNameSegments();

    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject INamed::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::INAMED__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::amalthea::model::ModelPackage::INAMED__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void INamed::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::INAMED__NAME:
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

::ecore::EBoolean INamed::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::amalthea::model::ModelPackage::INAMED__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::amalthea::model::ModelPackage::INAMED__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void INamed::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr INamed::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::amalthea::model::ModelPackage::_instance()->getINamed();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void INamed::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void INamed::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

