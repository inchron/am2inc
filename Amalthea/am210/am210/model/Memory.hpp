// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/Memory.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM210_MODEL_MEMORY_HPP
#define AM210_MODEL_MEMORY_HPP

#include <am210/model/dllModel.hpp>
#include <am210/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am210/model/HwModule.hpp>
#include <am210/model/HwDestination.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Memory_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am210
{
    namespace model
    {

    class EXPORT_AM210_MODEL_DLL Memory : public virtual ::am210::model::HwModule, public virtual ::am210::model::HwDestination
    {
    public:
        Memory();

        ~Memory() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References
        virtual ::am210::model::MemoryDefinition_ptr getDefinition () const;
        virtual void setDefinition (::am210::model::MemoryDefinition_ptr _definition);

        virtual const ::ecorecpp::mapping::EList< ::am210::model::MemoryMapping_ptr >& getMappings () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::MemoryMapping_ptr >& getMappings ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MEMORY;

        /*PROTECTED REGION ID(Memory) ENABLED START*/
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

        /*PROTECTED REGION ID(MemoryImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        Memory_ptr _this()
        {   return std::dynamic_pointer_cast<Memory>(shared_from_this());}

        // Attributes

        // References

        std::weak_ptr< ::am210::model::MemoryDefinition > m_definition;

        ::ecore::EList_ptr< ::am210::model::MemoryMapping_ptr > m_mappings;

    };

}
 // model
}// am210

#endif // AM210_MODEL_MEMORY_HPP

