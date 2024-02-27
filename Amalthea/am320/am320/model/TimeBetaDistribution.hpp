// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/TimeBetaDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM320_MODEL_TIMEBETADISTRIBUTION_HPP
#define AM320_MODEL_TIMEBETADISTRIBUTION_HPP

#include <am320/model/dllModel.hpp>
#include <am320/model_forward.hpp>

#include <am320/model/BoundedTimeDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TimeBetaDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am320
{
    namespace model
    {

    class EXPORT_AM320_MODEL_DLL TimeBetaDistribution : public virtual ::am320::model::BoundedTimeDistribution
    {
    public:
        TimeBetaDistribution();

        ~TimeBetaDistribution() override;

        void _initialize() override;

        // Operations

        virtual ::am320::model::Time_ptr getAverage ();

        // Attributes
        virtual ::am320::model::PositiveDouble getAlpha () const;
        virtual void setAlpha (::am320::model::PositiveDouble _alpha);

        virtual ::am320::model::PositiveDouble getBeta () const;
        virtual void setBeta (::am320::model::PositiveDouble _beta);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TIMEBETADISTRIBUTION;

        /*PROTECTED REGION ID(TimeBetaDistribution) ENABLED START*/
        using TimeInterval::getUpperBound;
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(TimeBetaDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TimeBetaDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<TimeBetaDistribution>(shared_from_this());}

        // Attributes

        ::am320::model::PositiveDouble m_alpha
        {   1.0};

        ::am320::model::PositiveDouble m_beta
        {   1.0};

        // References

    };

}
 // model
}// am320

#endif // AM320_MODEL_TIMEBETADISTRIBUTION_HPP

