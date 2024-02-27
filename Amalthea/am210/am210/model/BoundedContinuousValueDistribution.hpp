// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/BoundedContinuousValueDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM210_MODEL_BOUNDEDCONTINUOUSVALUEDISTRIBUTION_HPP
#define AM210_MODEL_BOUNDEDCONTINUOUSVALUEDISTRIBUTION_HPP

#include <am210/model/dllModel.hpp>
#include <am210/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am210/model/ContinuousValueInterval.hpp>
#include <am210/model/IContinuousValueDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(BoundedContinuousValueDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am210
{
    namespace model
    {

    class EXPORT_AM210_MODEL_DLL BoundedContinuousValueDistribution : public virtual ::am210::model::ContinuousValueInterval, public virtual ::am210::model::IContinuousValueDeviation
    {
    public:
        BoundedContinuousValueDistribution();

        ~BoundedContinuousValueDistribution() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::BOUNDEDCONTINUOUSVALUEDISTRIBUTION;

        /*PROTECTED REGION ID(BoundedContinuousValueDistribution) ENABLED START*/
        ::ecore::EDoubleObject getLowerBound () override
        {
            return ContinuousValueInterval::getLowerBound();}
        ::ecore::EDoubleObject getUpperBound () override
        {
            return ContinuousValueInterval::getUpperBound();}
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(BoundedContinuousValueDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        BoundedContinuousValueDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<BoundedContinuousValueDistribution>(shared_from_this());}

        // Attributes

        // References

    };

}
 // model
}// am210

#endif // AM210_MODEL_BOUNDEDCONTINUOUSVALUEDISTRIBUTION_HPP

