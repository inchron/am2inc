// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/TruncatedContinuousValueDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_TRUNCATEDCONTINUOUSVALUEDISTRIBUTION_HPP
#define AMALTHEA_MODEL_TRUNCATEDCONTINUOUSVALUEDISTRIBUTION_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/IContinuousValueDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TruncatedContinuousValueDistribution_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL TruncatedContinuousValueDistribution : public virtual ::amalthea::model::IContinuousValueDeviation
    {
    public:
        TruncatedContinuousValueDistribution();

        virtual ~TruncatedContinuousValueDistribution();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes
        virtual ::ecore::EDoubleObject getLowerBound () const;
        virtual void setLowerBound (::ecore::EDoubleObject _lowerBound);

        virtual ::ecore::EDoubleObject getUpperBound () const;
        virtual void setUpperBound (::ecore::EDoubleObject _upperBound);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TRUNCATEDCONTINUOUSVALUEDISTRIBUTION;

        /*PROTECTED REGION ID(TruncatedContinuousValueDistribution) START*/
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

        /*PROTECTED REGION ID(TruncatedContinuousValueDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TruncatedContinuousValueDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<TruncatedContinuousValueDistribution>(shared_from_this());}

        // Attributes

        ::ecore::EDoubleObject m_lowerBound
        {};

        ::ecore::EDoubleObject m_upperBound
        {};

        // References

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_TRUNCATEDCONTINUOUSVALUEDISTRIBUTION_HPP

