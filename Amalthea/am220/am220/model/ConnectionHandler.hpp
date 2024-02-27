// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/ConnectionHandler.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM220_MODEL_CONNECTIONHANDLER_HPP
#define AM220_MODEL_CONNECTIONHANDLER_HPP

#include <am220/model/dllModel.hpp>
#include <am220/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am220/model/HwModule.hpp>
#include <am220/model/HwPathElement.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ConnectionHandler_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am220
{
    namespace model
    {

    class EXPORT_AM220_MODEL_DLL ConnectionHandler : public virtual ::am220::model::HwModule, public virtual ::am220::model::HwPathElement
    {
    public:
        ConnectionHandler();

        ~ConnectionHandler() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References
        virtual ::am220::model::ConnectionHandlerDefinition_ptr getDefinition () const;
        virtual void setDefinition (::am220::model::ConnectionHandlerDefinition_ptr _definition);

        virtual const ::ecorecpp::mapping::EList< ::am220::model::HwConnection_ptr >& getInternalConnections () const;
        virtual ::ecorecpp::mapping::EList< ::am220::model::HwConnection_ptr >& getInternalConnections ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::CONNECTIONHANDLER;

        /*PROTECTED REGION ID(ConnectionHandler) ENABLED START*/
        using HwModule::getPorts;
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(ConnectionHandlerImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ConnectionHandler_ptr _this()
        {   return std::dynamic_pointer_cast<ConnectionHandler>(shared_from_this());}

        // Attributes

        // References

        std::weak_ptr< ::am220::model::ConnectionHandlerDefinition > m_definition;

        ::ecore::EList_ptr< ::am220::model::HwConnection_ptr > m_internalConnections;

    };

}
 // model
}// am220

#endif // AM220_MODEL_CONNECTIONHANDLER_HPP

