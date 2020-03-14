// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/TypeDefinition.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_TYPEDEFINITION_HPP
#define AMALTHEA_MODEL_TYPEDEFINITION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/ReferableBaseObject.hpp>
#include <amalthea/model/INamespaceMember.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TypeDefinition_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL TypeDefinition : public virtual ::amalthea::model::ReferableBaseObject, public virtual ::amalthea::model::INamespaceMember
    {
    public:
        TypeDefinition();

        virtual ~TypeDefinition();

        virtual void _initialize();

        // Operations

        // Attributes

        // References
        virtual ::amalthea::model::DataSize_ptr getSize () const;
        virtual void setSize (::amalthea::model::DataSize_ptr _size);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TYPEDEFINITION;

        /*PROTECTED REGION ID(TypeDefinition) ENABLED START*/
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

        /*PROTECTED REGION ID(TypeDefinitionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TypeDefinition_ptr _this()
        {   return std::dynamic_pointer_cast<TypeDefinition>(shared_from_this());}

        // Attributes

        // References

        ::amalthea::model::DataSize_ptr m_size;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_TYPEDEFINITION_HPP

