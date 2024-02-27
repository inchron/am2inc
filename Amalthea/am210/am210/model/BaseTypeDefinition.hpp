// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/BaseTypeDefinition.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM210_MODEL_BASETYPEDEFINITION_HPP
#define AM210_MODEL_BASETYPEDEFINITION_HPP

#include <am210/model/dllModel.hpp>
#include <am210/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am210/model/TypeDefinition.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(BaseTypeDefinition_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am210
{
    namespace model
    {

    class EXPORT_AM210_MODEL_DLL BaseTypeDefinition : public virtual ::am210::model::TypeDefinition
    {
    public:
        BaseTypeDefinition();

        ~BaseTypeDefinition() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References
        virtual const ::ecorecpp::mapping::EList< ::am210::model::Alias_ptr >& getAliases () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::Alias_ptr >& getAliases ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::BASETYPEDEFINITION;

        /*PROTECTED REGION ID(BaseTypeDefinition) ENABLED START*/
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

        /*PROTECTED REGION ID(BaseTypeDefinitionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        BaseTypeDefinition_ptr _this()
        {   return std::dynamic_pointer_cast<BaseTypeDefinition>(shared_from_this());}

        // Attributes

        // References

        ::ecore::EList_ptr< ::am210::model::Alias_ptr > m_aliases;

    };

}
 // model
}// am210

#endif // AM210_MODEL_BASETYPEDEFINITION_HPP

