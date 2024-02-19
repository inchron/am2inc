// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/MainInterface.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM120_MODEL_MAININTERFACE_HPP
#define AM120_MODEL_MAININTERFACE_HPP

#include <am120/model/dllModel.hpp>
#include <am120/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am120/model/ComponentInterface.hpp>
#include <am120/model/INamespaceMember.hpp>
#include <am120/model/IComponentStructureMember.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(MainInterface_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am120
{
    namespace model
    {

    class EXPORT_AM120_MODEL_DLL MainInterface : public virtual ::am120::model::ComponentInterface, public virtual ::am120::model::INamespaceMember, public virtual ::am120::model::IComponentStructureMember
    {
    public:
        MainInterface();

        virtual ~MainInterface();

        virtual void _initialize();

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
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

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
}// am120

#endif // AM120_MODEL_MAININTERFACE_HPP

