// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/ComponentStructureImpl.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "ComponentStructure.hpp"
#include <am120/model/ModelPackage.hpp>
#include <am120/model/ReferableObject.hpp>
#include <am120/model/ComponentStructure.hpp>
#include <am120/model/IComponentStructureMember.hpp>
#include <am120/model/INamed.hpp>
#include <am120/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

/*PROTECTED REGION ID(ComponentStructureImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am120::model;

void ComponentStructure::_initialize()
{
    // Supertypes
    ::am120::model::ReferableObject::_initialize();

    // References
    for (const auto &ref : getSubStructures())
    {
        ref->_initialize();
    }

    /*PROTECTED REGION ID(ComponentStructureImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations

::am120::model::ComponentStructure_ptr ComponentStructure::getContainingStructure()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.app4mc.amalthea.model.ComponentStructure%> _xifexpression = null;
<%org.eclipse.emf.ecore.EObject%> _eContainer = this.eContainer();
if ((_eContainer instanceof <%org.eclipse.app4mc.amalthea.model.ComponentStructure%>))
{
	<%org.eclipse.emf.ecore.EObject%> _eContainer_1 = this.eContainer();
	_xifexpression = ((<%org.eclipse.app4mc.amalthea.model.ComponentStructure%>) _eContainer_1);
}
else
{
	_xifexpression = null;
}
return _xifexpression;
#endif
    /*PROTECTED REGION ID(ComponentStructureImpl_getContainingStructure) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: am120::model::ComponentStructure::getContainingStructure";
    /*PROTECTED REGION END*/
}

::ecore::EString ComponentStructure::getDefaultNameSeparator()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    return "::";
#endif
    /*PROTECTED REGION ID(ComponentStructureImpl_getDefaultNameSeparator) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    throw "UnsupportedOperationException: am120::model::ComponentStructure::getDefaultNameSeparator";
    /*PROTECTED REGION END*/
}

std::vector< ::ecore::EString > ComponentStructure::getNamePrefixSegments()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _elvis = null;
<%org.eclipse.app4mc.amalthea.model.ComponentStructure%> _containingStructure = this.getContainingStructure();
<%org.eclipse.emf.common.util.EList%><<%java.lang.String%>> _qualifiedNameSegments = null;
if (_containingStructure!=null)
{
	_qualifiedNameSegments=_containingStructure.getQualifiedNameSegments();
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
    /*PROTECTED REGION ID(ComponentStructureImpl_getNamePrefixSegments) ENABLED START*/

    std::vector < ::ecore::EString > _qualifiedNameSegments;
    auto _containingStructure = getContainingStructure();
    if (_containingStructure)
        _qualifiedNameSegments =
                _containingStructure->getQualifiedNameSegments();
    return _qualifiedNameSegments;

    /*PROTECTED REGION END*/
}

// EObject
::ecore::EJavaObject ComponentStructure::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean /*_resolve*/)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__NAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getName());
    }
        return _any;
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__QUALIFIEDNAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getQualifiedName());
    }
        return _any;
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__UNIQUENAME:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getUniqueName());
    }
        return _any;
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__STRUCTURETYPE:
    {
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::toAny(_any, getStructureType());
    }
        return _any;
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__SUBSTRUCTURES:
    {
        _any = getSubStructures().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__MEMBEROBJECTS:
    {
        _any = getMemberObjects().asEListOf< ::ecore::EObject_ptr >();
    }
        return _any;

    }
    throw "Error: eGet() does not handle this featureID";
}

void ComponentStructure::eSet(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__NAME:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setName(_t0);
    }
        return;
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__STRUCTURETYPE:
    {
        ::ecore::EString _t0;
        ::ecorecpp::mapping::any_traits < ::ecore::EString
                > ::fromAny(_newValue, _t0);
        setStructureType(_t0);
    }
        return;
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__SUBSTRUCTURES:
    {
        auto _t0 = ::ecorecpp::mapping::any::any_cast
                < ::ecore::EList_ptr< ::ecore::EObject_ptr > > (_newValue);
        getSubStructures().clear();
        getSubStructures().insert_all(*_t0);
    }
        return;

    }
    throw "Error: eSet() does not handle this featureID";
}

::ecore::EBoolean ComponentStructure::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__NAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getName());
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__QUALIFIEDNAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getQualifiedName());
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__UNIQUENAME:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getUniqueName());
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__STRUCTURETYPE:
        return ::ecorecpp::mapping::set_traits < ::ecore::EString
                > ::is_set(getStructureType());
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__SUBSTRUCTURES:
        return getSubStructures().size() > 0;
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__MEMBEROBJECTS:
        return getMemberObjects().size() > 0;

    }
    throw "Error: eIsSet() does not handle this featureID";
}

void ComponentStructure::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error: eUnset() does not handle this featureID";
}

::ecore::EClass_ptr ComponentStructure::_eClass()
{
    static ::ecore::EClass_ptr _eclass =
            ::am120::model::ModelPackage::_instance()->getComponentStructure();
    return _eclass;
}

/** Set the local end of a reference with an EOpposite property.
 */
void ComponentStructure::_inverseAdd(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_newValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__SUBSTRUCTURES:
    {
    }
        return;

    }
    throw "Error: _inverseAdd() does not handle this featureID";
}

/** Unset the local end of a reference with an EOpposite property.
 */
void ComponentStructure::_inverseRemove(::ecore::EInt _featureID,
        [[maybe_unused]] ::ecore::EJavaObject const &_oldValue)
{
    switch (_featureID)
    {
    case ::am120::model::ModelPackage::COMPONENTSTRUCTURE__SUBSTRUCTURES:
    {
    }
        return;

    }
    throw "Error: _inverseRemove() does not handle this featureID";
}

