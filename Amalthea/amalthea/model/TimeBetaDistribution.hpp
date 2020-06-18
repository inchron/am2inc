// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/TimeBetaDistribution.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_TIMEBETADISTRIBUTION_HPP
#define AMALTHEA_MODEL_TIMEBETADISTRIBUTION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <amalthea/model/BoundedTimeDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TimeBetaDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL TimeBetaDistribution : public virtual ::amalthea::model::BoundedTimeDistribution
    {
    public:
        TimeBetaDistribution();

        virtual ~TimeBetaDistribution();

        virtual void _initialize();

        // Operations

        virtual ::amalthea::model::Time_ptr getAverage ();

        // Attributes
        virtual ::amalthea::model::PositiveDouble getAlpha () const;
        virtual void setAlpha (::amalthea::model::PositiveDouble _alpha);

        virtual ::amalthea::model::PositiveDouble getBeta () const;
        virtual void setBeta (::amalthea::model::PositiveDouble _beta);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TIMEBETADISTRIBUTION;

        /*PROTECTED REGION ID(TimeBetaDistribution) ENABLED START*/
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

        /*PROTECTED REGION ID(TimeBetaDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TimeBetaDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<TimeBetaDistribution>(shared_from_this());}

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

#endif // AMALTHEA_MODEL_TIMEBETADISTRIBUTION_HPP

