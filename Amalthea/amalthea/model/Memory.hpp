// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/Memory.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_MEMORY_HPP
#define AMALTHEA_MODEL_MEMORY_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/HwModule.hpp>
#include <amalthea/model/HwDestination.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Memory_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL Memory : public virtual ::amalthea::model::HwModule, public virtual ::amalthea::model::HwDestination
    {
    public:
        Memory();

        virtual ~Memory();

        virtual void _initialize();

        // Operations

        // Attributes

        // References
        virtual ::amalthea::model::MemoryDefinition_ptr getDefinition () const;
        virtual void setDefinition (::amalthea::model::MemoryDefinition_ptr _definition);

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::MemoryMapping_ptr >& getMappings () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::MemoryMapping_ptr >& getMappings ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MEMORY;

        /*PROTECTED REGION ID(Memory) ENABLED START*/
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

        /*PROTECTED REGION ID(MemoryImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        Memory_ptr _this()
        {   return std::dynamic_pointer_cast<Memory>(shared_from_this());}

        // Attributes

        // References

        std::weak_ptr< ::amalthea::model::MemoryDefinition > m_definition;

        ::ecore::EList_ptr< ::amalthea::model::MemoryMapping_ptr > m_mappings;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_MEMORY_HPP

