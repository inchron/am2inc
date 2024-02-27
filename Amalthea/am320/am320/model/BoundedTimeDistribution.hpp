// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/BoundedTimeDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM320_MODEL_BOUNDEDTIMEDISTRIBUTION_HPP
#define AM320_MODEL_BOUNDEDTIMEDISTRIBUTION_HPP

#include <am320/model/dllModel.hpp>
#include <am320/model_forward.hpp>

#include <am320/model/TimeInterval.hpp>
#include <am320/model/ITimeDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(BoundedTimeDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am320
{
    namespace model
    {

    class EXPORT_AM320_MODEL_DLL BoundedTimeDistribution : public virtual ::am320::model::TimeInterval, public virtual ::am320::model::ITimeDeviation
    {
    public:
        BoundedTimeDistribution();

        ~BoundedTimeDistribution() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::BOUNDEDTIMEDISTRIBUTION;

        /*PROTECTED REGION ID(BoundedTimeDistribution) ENABLED START*/
        /* Reimplement the abstract operations from ITimeDeviation, which are
         * defined non-const. */
        ::am320::model::Time_ptr getLowerBound() override
        {
            return TimeInterval::getLowerBound();
        }
        ::am320::model::Time_ptr getUpperBound() override
        {
            return TimeInterval::getUpperBound();
        }
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(BoundedTimeDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        BoundedTimeDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<BoundedTimeDistribution>(shared_from_this());}

        // Attributes

        // References

    };

}
 // model
}// am320

#endif // AM320_MODEL_BOUNDEDTIMEDISTRIBUTION_HPP

