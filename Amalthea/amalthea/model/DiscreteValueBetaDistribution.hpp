// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/DiscreteValueBetaDistribution.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_DISCRETEVALUEBETADISTRIBUTION_HPP
#define AMALTHEA_MODEL_DISCRETEVALUEBETADISTRIBUTION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/BoundedDiscreteValueDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(DiscreteValueBetaDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL DiscreteValueBetaDistribution : public virtual ::amalthea::model::BoundedDiscreteValueDistribution
    {
    public:
        DiscreteValueBetaDistribution();

        virtual ~DiscreteValueBetaDistribution();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EDoubleObject getAverage ();

        // Attributes
        virtual ::amalthea::model::PositiveDouble getAlpha () const;
        virtual void setAlpha (::amalthea::model::PositiveDouble _alpha);

        virtual ::amalthea::model::PositiveDouble getBeta () const;
        virtual void setBeta (::amalthea::model::PositiveDouble _beta);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::DISCRETEVALUEBETADISTRIBUTION;

        /*PROTECTED REGION ID(DiscreteValueBetaDistribution) ENABLED START*/
        using DiscreteValueInterval::getLowerBound;
        using DiscreteValueInterval::getUpperBound;
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

        /*PROTECTED REGION ID(DiscreteValueBetaDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        DiscreteValueBetaDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<DiscreteValueBetaDistribution>(shared_from_this());}

        // Attributes

        ::amalthea::model::PositiveDouble m_alpha
        {   1.0};

        ::amalthea::model::PositiveDouble m_beta
        {   1.0};

        // References

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_DISCRETEVALUEBETADISTRIBUTION_HPP

