// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/TruncatedTimeDistribution.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_TRUNCATEDTIMEDISTRIBUTION_HPP
#define AMALTHEA_MODEL_TRUNCATEDTIMEDISTRIBUTION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <amalthea/model/ITimeDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TruncatedTimeDistribution_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL TruncatedTimeDistribution : public virtual ::amalthea::model::ITimeDeviation
    {
    public:
        TruncatedTimeDistribution();

        virtual ~TruncatedTimeDistribution();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( ::ecore::EDiagnosticChain _diagnostics, std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes

        // References
        virtual ::amalthea::model::Time_ptr getLowerBound () const;
        virtual void setLowerBound (::amalthea::model::Time_ptr _lowerBound);

        virtual ::amalthea::model::Time_ptr getUpperBound () const;
        virtual void setUpperBound (::amalthea::model::Time_ptr _upperBound);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TRUNCATEDTIMEDISTRIBUTION;

        /*PROTECTED REGION ID(TruncatedTimeDistribution) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

        /*PROTECTED REGION ID(TruncatedTimeDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TruncatedTimeDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<TruncatedTimeDistribution>(shared_from_this());}

        // Attributes

        // References

        ::amalthea::model::Time_ptr m_lowerBound;

        ::amalthea::model::Time_ptr m_upperBound;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_TRUNCATEDTIMEDISTRIBUTION_HPP

