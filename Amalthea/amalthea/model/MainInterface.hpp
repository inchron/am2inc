// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/MainInterface.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_MAININTERFACE_HPP
#define AMALTHEA_MODEL_MAININTERFACE_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/ComponentInterface.hpp>
#include <amalthea/model/INamespaceMember.hpp>
#include <amalthea/model/IComponentStructureMember.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(MainInterface_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL MainInterface : public virtual ::amalthea::model::ComponentInterface, public virtual ::amalthea::model::INamespaceMember, public virtual ::amalthea::model::IComponentStructureMember
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
}// amalthea

#endif // AMALTHEA_MODEL_MAININTERFACE_HPP

