// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/TimeWeibullEstimatorsDistribution.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_TIMEWEIBULLESTIMATORSDISTRIBUTION_HPP
#define AMALTHEA_MODEL_TIMEWEIBULLESTIMATORSDISTRIBUTION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <amalthea/model/BoundedTimeDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TimeWeibullEstimatorsDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL TimeWeibullEstimatorsDistribution : public virtual ::amalthea::model::BoundedTimeDistribution
    {
    public:
        TimeWeibullEstimatorsDistribution();

        virtual ~TimeWeibullEstimatorsDistribution();

        virtual void _initialize();

        // Operations

        // Attributes
        virtual ::amalthea::model::PositiveDouble getPRemainPromille () const;
        virtual void setPRemainPromille (::amalthea::model::PositiveDouble _pRemainPromille);

        // References
        virtual ::amalthea::model::Time_ptr getAverage () const;
        virtual void setAverage (::amalthea::model::Time_ptr _average);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TIMEWEIBULLESTIMATORSDISTRIBUTION;

        /*PROTECTED REGION ID(TimeWeibullEstimatorsDistribution) ENABLED START*/
        using TimeInterval::getUpperBound;
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

        /*PROTECTED REGION ID(TimeWeibullEstimatorsDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TimeWeibullEstimatorsDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<TimeWeibullEstimatorsDistribution>(shared_from_this());}

        // Attributes

        ::amalthea::model::PositiveDouble m_pRemainPromille
        {   1.0};

        // References

        ::amalthea::model::Time_ptr m_average;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_TIMEWEIBULLESTIMATORSDISTRIBUTION_HPP

