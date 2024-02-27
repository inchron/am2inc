// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/ProcessingUnit.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM320_MODEL_PROCESSINGUNIT_HPP
#define AM320_MODEL_PROCESSINGUNIT_HPP

#include <am320/model/dllModel.hpp>
#include <am320/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am320/model/HwModule.hpp>
#include <am320/model/HwDestination.hpp>
#include <am320/model/HwPathElement.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ProcessingUnit_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am320
{
    namespace model
    {

    class EXPORT_AM320_MODEL_DLL ProcessingUnit : public virtual ::am320::model::HwModule, public virtual ::am320::model::HwDestination, public virtual ::am320::model::HwPathElement
    {
    public:
        ProcessingUnit();

        ~ProcessingUnit() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References
        virtual ::am320::model::ProcessingUnitDefinition_ptr getDefinition () const;
        virtual void setDefinition (::am320::model::ProcessingUnitDefinition_ptr _definition);

        virtual const ::ecorecpp::mapping::EList< ::am320::model::HwAccessElement_ptr >& getAccessElements () const;
        virtual ::ecorecpp::mapping::EList< ::am320::model::HwAccessElement_ptr >& getAccessElements ();

        virtual const ::ecorecpp::mapping::EList< ::am320::model::Cache_ptr >& getCaches () const;
        virtual ::ecorecpp::mapping::EList< ::am320::model::Cache_ptr >& getCaches ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::PROCESSINGUNIT;

        /*PROTECTED REGION ID(ProcessingUnit) ENABLED START*/
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

        /*PROTECTED REGION ID(ProcessingUnitImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ProcessingUnit_ptr _this()
        {   return std::dynamic_pointer_cast<ProcessingUnit>(shared_from_this());}

        // Attributes

        // References

        std::weak_ptr< ::am320::model::ProcessingUnitDefinition > m_definition;

        ::ecore::EList_ptr< ::am320::model::HwAccessElement_ptr > m_accessElements;

        ::ecore::EList_ptr< ::am320::model::Cache_ptr > m_caches;

    };

}
 // model
}// am320

#endif // AM320_MODEL_PROCESSINGUNIT_HPP

