// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/BoundedTimeDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_BOUNDEDTIMEDISTRIBUTION_HPP
#define AMALTHEA_MODEL_BOUNDEDTIMEDISTRIBUTION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <amalthea/model/TimeInterval.hpp>
#include <amalthea/model/ITimeDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(BoundedTimeDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL BoundedTimeDistribution : public virtual ::amalthea::model::TimeInterval, public virtual ::amalthea::model::ITimeDeviation
    {
    public:
        BoundedTimeDistribution();

        virtual ~BoundedTimeDistribution();

        virtual void _initialize();

        // Operations

        // Attributes

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::BOUNDEDTIMEDISTRIBUTION;

        /*PROTECTED REGION ID(BoundedTimeDistribution) ENABLED START*/
        /* Reimplement the abstract operations from ITimeDeviation, which are
         * defined non-const. */
        ::amalthea::model::Time_ptr getLowerBound () override
        {   return TimeInterval::getLowerBound();}
        ::amalthea::model::Time_ptr getUpperBound () override
        {   return TimeInterval::getUpperBound();}
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

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
}// amalthea

#endif // AMALTHEA_MODEL_BOUNDEDTIMEDISTRIBUTION_HPP

