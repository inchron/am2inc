// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * root/Referable.cpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#include "Referable.hpp"
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "root/RootPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

/*PROTECTED REGION ID(Referable.cpp) ENABLED START*/
#include <QString>
#include <QUuid>
/*PROTECTED REGION END*/

using namespace ::root;

// Default constructor
Referable::Referable()
{
    /*PROTECTED REGION ID(ReferableImpl__ReferableImpl) ENABLED START*/

    /* http://download.eclipse.org/modeling/emf/emf/javadoc/2.5.0/org/eclipse/emf/ecore/util/EcoreUtil.html#generateUUID()
     * contradicts itself: On one side it references
     * http://www.ietf.org/rfc/rfc2045.txt as "base 64", but on the other side
     * the result must be a valid "NCName" according to
     * http://www.w3.org/TR/1999/REC-xml-names-19990114/#NT-NCName - which it
     * can't be as base 64 contains a '+' and a '/', which a NCName must not
     * contain. */
    QString uuid(
            QUuid::createUuid().toRfc4122().toBase64(
                    QByteArray::Base64Encoding
                            | QByteArray::OmitTrailingEquals));
    m_intrinsicId = uuid.prepend("_").toStdString();

    /*PROTECTED REGION END*/

#ifdef ECORECPP_NOTIFICATION_API
    m_eDeliver = false;
#endif
}

Referable::~Referable()
{
}

// Attributes

::ecore::EString const& Referable::getIntrinsicId() const
{
    return m_intrinsicId;
}

void Referable::setIntrinsicId(::ecore::EString const &_intrinsicId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_intrinsicId = m_intrinsicId;
#endif
    m_intrinsicId = _intrinsicId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                _this(),
                ::root::RootPackage::_instance()->getReferable__intrinsicId(),
                _old_intrinsicId,
                m_intrinsicId
            );
        eNotify(&notification);
    }
#endif
}

// References

