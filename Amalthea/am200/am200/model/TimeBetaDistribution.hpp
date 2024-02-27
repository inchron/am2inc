// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am200/model/TimeBetaDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM200_MODEL_TIMEBETADISTRIBUTION_HPP
#define AM200_MODEL_TIMEBETADISTRIBUTION_HPP

#include <am200/model/dllModel.hpp>
#include <am200/model_forward.hpp>

#include <am200/model/BoundedTimeDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TimeBetaDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am200
{
    namespace model
    {

    class EXPORT_AM200_MODEL_DLL TimeBetaDistribution : public virtual ::am200::model::BoundedTimeDistribution
    {
    public:
        TimeBetaDistribution();

        ~TimeBetaDistribution() override;

        void _initialize() override;

        // Operations

        virtual ::am200::model::Time_ptr getAverage ();

        // Attributes
        virtual ::am200::model::PositiveDouble getAlpha () const;
        virtual void setAlpha (::am200::model::PositiveDouble _alpha);

        virtual ::am200::model::PositiveDouble getBeta () const;
        virtual void setBeta (::am200::model::PositiveDouble _beta);

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

        ::am200::model::PositiveDouble m_alpha
        {   1.0};

        ::am200::model::PositiveDouble m_beta
        {   1.0};

        // References

    };

}
 // model
}// am200

#endif // AM200_MODEL_TIMEBETADISTRIBUTION_HPP

