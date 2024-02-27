// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/TimeWeibullEstimatorsDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM210_MODEL_TIMEWEIBULLESTIMATORSDISTRIBUTION_HPP
#define AM210_MODEL_TIMEWEIBULLESTIMATORSDISTRIBUTION_HPP

#include <am210/model/dllModel.hpp>
#include <am210/model_forward.hpp>

#include <am210/model/BoundedTimeDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TimeWeibullEstimatorsDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am210
{
    namespace model
    {

    class EXPORT_AM210_MODEL_DLL TimeWeibullEstimatorsDistribution : public virtual ::am210::model::BoundedTimeDistribution
    {
    public:
        TimeWeibullEstimatorsDistribution();

        ~TimeWeibullEstimatorsDistribution() override;

        void _initialize() override;

        // Operations

        // Attributes
        virtual ::am210::model::PositiveDouble getPRemainPromille () const;
        virtual void setPRemainPromille (::am210::model::PositiveDouble _pRemainPromille);

        // References
        virtual ::am210::model::Time_ptr getAverage () const;
        virtual void setAverage (::am210::model::Time_ptr _average);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TIMEWEIBULLESTIMATORSDISTRIBUTION;

        /*PROTECTED REGION ID(TimeWeibullEstimatorsDistribution) ENABLED START*/
        ::am210::model::Time_ptr getAverage() override
        {
            return const_cast<const TimeWeibullEstimatorsDistribution*>( this )->getAverage();
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

        /*PROTECTED REGION ID(TimeWeibullEstimatorsDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TimeWeibullEstimatorsDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<TimeWeibullEstimatorsDistribution>(shared_from_this());}

        // Attributes

        ::am210::model::PositiveDouble m_pRemainPromille
        {   1.0};

        // References

        ::am210::model::Time_ptr m_average;

    };

}
 // model
}// am210

#endif // AM210_MODEL_TIMEWEIBULLESTIMATORSDISTRIBUTION_HPP

