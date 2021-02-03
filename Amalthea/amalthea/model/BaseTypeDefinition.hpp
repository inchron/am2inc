// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/BaseTypeDefinition.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_BASETYPEDEFINITION_HPP
#define AMALTHEA_MODEL_BASETYPEDEFINITION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/TypeDefinition.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(BaseTypeDefinition_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL BaseTypeDefinition : public virtual ::amalthea::model::TypeDefinition
    {
    public:
        BaseTypeDefinition();

        virtual ~BaseTypeDefinition();

        virtual void _initialize();

        // Operations

        // Attributes

        // References
        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::Alias_ptr >& getAliases () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::Alias_ptr >& getAliases ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::BASETYPEDEFINITION;

        /*PROTECTED REGION ID(BaseTypeDefinition) ENABLED START*/
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

        /*PROTECTED REGION ID(BaseTypeDefinitionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        BaseTypeDefinition_ptr _this()
        {   return std::dynamic_pointer_cast<BaseTypeDefinition>(shared_from_this());}

        // Attributes

        // References

        ::ecore::EList_ptr< ::amalthea::model::Alias_ptr > m_aliases;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_BASETYPEDEFINITION_HPP

