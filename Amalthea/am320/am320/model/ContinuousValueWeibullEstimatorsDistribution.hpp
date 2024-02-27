// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/ContinuousValueWeibullEstimatorsDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM320_MODEL_CONTINUOUSVALUEWEIBULLESTIMATORSDISTRIBUTION_HPP
#define AM320_MODEL_CONTINUOUSVALUEWEIBULLESTIMATORSDISTRIBUTION_HPP

#include <am320/model/dllModel.hpp>
#include <am320/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am320/model/BoundedContinuousValueDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ContinuousValueWeibullEstimatorsDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am320
{
    namespace model
    {

    class EXPORT_AM320_MODEL_DLL ContinuousValueWeibullEstimatorsDistribution : public virtual ::am320::model::BoundedContinuousValueDistribution
    {
    public:
        ContinuousValueWeibullEstimatorsDistribution();

        ~ContinuousValueWeibullEstimatorsDistribution() override;

        void _initialize() override;

        // Operations

        // Attributes
        virtual ::ecore::EDoubleObject getAverage () const;
        virtual void setAverage (::ecore::EDoubleObject _average);

        virtual ::am320::model::PositiveDouble getPRemainPromille () const;
        virtual void setPRemainPromille (::am320::model::PositiveDouble _pRemainPromille);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::CONTINUOUSVALUEWEIBULLESTIMATORSDISTRIBUTION;

        /*PROTECTED REGION ID(ContinuousValueWeibullEstimatorsDistribution) ENABLED START*/
        ::ecore::EDoubleObject getAverage () override
        {
            return const_cast<const ContinuousValueWeibullEstimatorsDistribution*>(this)->getAverage();}
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(ContinuousValueWeibullEstimatorsDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ContinuousValueWeibullEstimatorsDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<ContinuousValueWeibullEstimatorsDistribution>(shared_from_this());}

        // Attributes

        ::ecore::EDoubleObject m_average
        {   0.0};

        ::am320::model::PositiveDouble m_pRemainPromille
        {   1.0};

        // References

    };

}
 // model
}// am320

#endif // AM320_MODEL_CONTINUOUSVALUEWEIBULLESTIMATORSDISTRIBUTION_HPP

