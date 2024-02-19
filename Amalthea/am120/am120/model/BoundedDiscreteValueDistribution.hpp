// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/BoundedDiscreteValueDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM120_MODEL_BOUNDEDDISCRETEVALUEDISTRIBUTION_HPP
#define AM120_MODEL_BOUNDEDDISCRETEVALUEDISTRIBUTION_HPP

#include <am120/model/dllModel.hpp>
#include <am120/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am120/model/DiscreteValueInterval.hpp>
#include <am120/model/IDiscreteValueDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(BoundedDiscreteValueDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am120
{
    namespace model
    {

    class EXPORT_AM120_MODEL_DLL BoundedDiscreteValueDistribution : public virtual ::am120::model::DiscreteValueInterval, public virtual ::am120::model::IDiscreteValueDeviation
    {
    public:
        BoundedDiscreteValueDistribution();

        virtual ~BoundedDiscreteValueDistribution();

        virtual void _initialize();

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
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

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
}// am120

#endif // AM120_MODEL_BOUNDEDDISCRETEVALUEDISTRIBUTION_HPP

