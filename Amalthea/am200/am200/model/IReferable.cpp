// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am200/model/IReferable.cpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "IReferable.hpp"
#include <am200/model/INamed.hpp>
#include <am200/model/Namespace.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "am200/model/ModelPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

/*PROTECTED REGION ID(IReferable.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

using namespace ::am200::model;

// Default constructor
IReferable::IReferable()
{
    /*PROTECTED REGION ID(IReferableImpl__IReferableImpl) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/

#ifdef ECORECPP_NOTIFICATION_API
    m_eDeliver = false;
#endif
}

IReferable::~IReferable()
{
}

// Attributes

::ecore::EString IReferable::getUniqueName()
{
#if 0
    // This is the original body of the EOperation as specified in
    // the ecore. If you want to replace it by C++ code, enable
    // the following protected region and implement it there.
    <%java.lang.String%> _encodedQualifiedName = this.getEncodedQualifiedName();
<%java.lang.String%> _plus = (_encodedQualifiedName + "?type=");
<%java.lang.String%> _name = this.eClass().getName();
return (_plus + _name);
#endif
    /*PROTECTED REGION ID(IReferableImpl_Getter_uniqueName) ENABLED START*/

    ecore::EString result(this->getEncodedQualifiedName());
    result.append("?type=");
    result.append(eClass()->getName());

    return result;
    /*PROTECTED REGION END*/
}

// References

