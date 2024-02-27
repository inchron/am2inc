// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/BoundedDiscreteValueDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM220_MODEL_BOUNDEDDISCRETEVALUEDISTRIBUTION_HPP
#define AM220_MODEL_BOUNDEDDISCRETEVALUEDISTRIBUTION_HPP

#include <am220/model/dllModel.hpp>
#include <am220/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am220/model/DiscreteValueInterval.hpp>
#include <am220/model/IDiscreteValueDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(BoundedDiscreteValueDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am220
{
    namespace model
    {

    class EXPORT_AM220_MODEL_DLL BoundedDiscreteValueDistribution : public virtual ::am220::model::DiscreteValueInterval, public virtual ::am220::model::IDiscreteValueDeviation
    {
    public:
        BoundedDiscreteValueDistribution();

        ~BoundedDiscreteValueDistribution() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::BOUNDEDDISCRETEVALUEDISTRIBUTION;

        /*PROTECTED REGION ID(BoundedDiscreteValueDistribution) ENABLED START*/
        /* The methods defined by the interface class IDiscreteValueDeviation
         * must be reimplemented. In this case the functionality is
         * implemented by another base class. */
        ::ecore::ELongObject getLowerBound () override
        {
            return DiscreteValueInterval::getLowerBound();}
        ::ecore::ELongObject getUpperBound () override
        {
            return DiscreteValueInterval::getUpperBound();}
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(BoundedDiscreteValueDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        BoundedDiscreteValueDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<BoundedDiscreteValueDistribution>(shared_from_this());}

        // Attributes

        // References

    };

}
 // model
}// am220

#endif // AM220_MODEL_BOUNDEDDISCRETEVALUEDISTRIBUTION_HPP

