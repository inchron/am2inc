// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/ContinuousValueWeibullEstimatorsDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_CONTINUOUSVALUEWEIBULLESTIMATORSDISTRIBUTION_HPP
#define AMALTHEA_MODEL_CONTINUOUSVALUEWEIBULLESTIMATORSDISTRIBUTION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/BoundedContinuousValueDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ContinuousValueWeibullEstimatorsDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL ContinuousValueWeibullEstimatorsDistribution : public virtual ::amalthea::model::BoundedContinuousValueDistribution
    {
    public:
        ContinuousValueWeibullEstimatorsDistribution();

        virtual ~ContinuousValueWeibullEstimatorsDistribution();

        virtual void _initialize();

        // Operations

        // Attributes
        virtual ::ecore::EDoubleObject getAverage () const;
        virtual void setAverage (::ecore::EDoubleObject _average);

        virtual ::amalthea::model::PositiveDouble getPRemainPromille () const;
        virtual void setPRemainPromille (::amalthea::model::PositiveDouble _pRemainPromille);

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
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

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

        ::amalthea::model::PositiveDouble m_pRemainPromille
        {   1.0};

        // References

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_CONTINUOUSVALUEWEIBULLESTIMATORSDISTRIBUTION_HPP

