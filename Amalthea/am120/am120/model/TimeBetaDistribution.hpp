// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/TimeBetaDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM120_MODEL_TIMEBETADISTRIBUTION_HPP
#define AM120_MODEL_TIMEBETADISTRIBUTION_HPP

#include <am120/model/dllModel.hpp>
#include <am120/model_forward.hpp>

#include <am120/model/BoundedTimeDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TimeBetaDistribution_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am120
{
    namespace model
    {

    class EXPORT_AM120_MODEL_DLL TimeBetaDistribution : public virtual ::am120::model::BoundedTimeDistribution
    {
    public:
        TimeBetaDistribution();

        virtual ~TimeBetaDistribution();

        virtual void _initialize();

        // Operations

        virtual ::am120::model::Time_ptr getAverage ();

        // Attributes
        virtual ::am120::model::PositiveDouble getAlpha () const;
        virtual void setAlpha (::am120::model::PositiveDouble _alpha);

        virtual ::am120::model::PositiveDouble getBeta () const;
        virtual void setBeta (::am120::model::PositiveDouble _beta);

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

        ::am120::model::PositiveDouble m_alpha
        {   1.0};

        ::am120::model::PositiveDouble m_beta
        {   1.0};

        // References

    };

}
 // model
}// am120

#endif // AM120_MODEL_TIMEBETADISTRIBUTION_HPP

