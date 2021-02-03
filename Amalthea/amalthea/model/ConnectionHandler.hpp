// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/ConnectionHandler.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_CONNECTIONHANDLER_HPP
#define AMALTHEA_MODEL_CONNECTIONHANDLER_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/HwModule.hpp>
#include <amalthea/model/HwPathElement.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ConnectionHandler_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL ConnectionHandler : public virtual ::amalthea::model::HwModule, public virtual ::amalthea::model::HwPathElement
    {
    public:
        ConnectionHandler();

        virtual ~ConnectionHandler();

        virtual void _initialize();

        // Operations

        // Attributes

        // References
        virtual ::amalthea::model::ConnectionHandlerDefinition_ptr getDefinition () const;
        virtual void setDefinition (::amalthea::model::ConnectionHandlerDefinition_ptr _definition);

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::HwConnection_ptr >& getInternalConnections () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::HwConnection_ptr >& getInternalConnections ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::CONNECTIONHANDLER;

        /*PROTECTED REGION ID(ConnectionHandler) ENABLED START*/
        using HwModule::getPorts;
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

        /*PROTECTED REGION ID(ConnectionHandlerImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ConnectionHandler_ptr _this()
        {   return std::dynamic_pointer_cast<ConnectionHandler>(shared_from_this());}

        // Attributes

        // References

        std::weak_ptr< ::amalthea::model::ConnectionHandlerDefinition > m_definition;

        ::ecore::EList_ptr< ::amalthea::model::HwConnection_ptr > m_internalConnections;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_CONNECTIONHANDLER_HPP

