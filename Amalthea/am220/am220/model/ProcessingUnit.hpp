// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/ProcessingUnit.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM220_MODEL_PROCESSINGUNIT_HPP
#define AM220_MODEL_PROCESSINGUNIT_HPP

#include <am220/model/dllModel.hpp>
#include <am220/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am220/model/HwModule.hpp>
#include <am220/model/HwDestination.hpp>
#include <am220/model/HwPathElement.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ProcessingUnit_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am220
{
    namespace model
    {

    class EXPORT_AM220_MODEL_DLL ProcessingUnit : public virtual ::am220::model::HwModule, public virtual ::am220::model::HwDestination, public virtual ::am220::model::HwPathElement
    {
    public:
        ProcessingUnit();

        ~ProcessingUnit() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References
        virtual ::am220::model::ProcessingUnitDefinition_ptr getDefinition () const;
        virtual void setDefinition (::am220::model::ProcessingUnitDefinition_ptr _definition);

        virtual const ::ecorecpp::mapping::EList< ::am220::model::HwAccessElement_ptr >& getAccessElements () const;
        virtual ::ecorecpp::mapping::EList< ::am220::model::HwAccessElement_ptr >& getAccessElements ();

        virtual const ::ecorecpp::mapping::EList< ::am220::model::Cache_ptr >& getCaches () const;
        virtual ::ecorecpp::mapping::EList< ::am220::model::Cache_ptr >& getCaches ();

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

        std::weak_ptr< ::am220::model::ProcessingUnitDefinition > m_definition;

        ::ecore::EList_ptr< ::am220::model::HwAccessElement_ptr > m_accessElements;

        ::ecore::EList_ptr< ::am220::model::Cache_ptr > m_caches;

    };

}
 // model
}// am220

#endif // AM220_MODEL_PROCESSINGUNIT_HPP

