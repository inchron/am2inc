// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/MainInterface.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM320_MODEL_MAININTERFACE_HPP
#define AM320_MODEL_MAININTERFACE_HPP

#include <am320/model/dllModel.hpp>
#include <am320/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am320/model/ComponentInterface.hpp>
#include <am320/model/INamespaceMember.hpp>
#include <am320/model/IComponentStructureMember.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(MainInterface_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am320
{
    namespace model
    {

    class EXPORT_AM320_MODEL_DLL MainInterface : public virtual ::am320::model::ComponentInterface, public virtual ::am320::model::INamespaceMember, public virtual ::am320::model::IComponentStructureMember
    {
    public:
        MainInterface();

        ~MainInterface() override;

        void _initialize() override;

        // Operations

        // Attributes
        virtual ::ecore::EString const& getVersion () const;
        virtual void setVersion (::ecore::EString const& _version);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MAININTERFACE;

        /*PROTECTED REGION ID(MainInterface) ENABLED START*/
        using INamespaceMember::getNamespace;
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(MainInterfaceImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        MainInterface_ptr _this()
        {   return std::dynamic_pointer_cast<MainInterface>(shared_from_this());}

        // Attributes

        ::ecore::EString m_version
        {   "1.0"};

        // References

    };

}
 // model
}// am320

#endif // AM320_MODEL_MAININTERFACE_HPP

