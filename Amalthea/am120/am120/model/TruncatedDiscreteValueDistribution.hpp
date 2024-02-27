// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/TruncatedDiscreteValueDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM120_MODEL_TRUNCATEDDISCRETEVALUEDISTRIBUTION_HPP
#define AM120_MODEL_TRUNCATEDDISCRETEVALUEDISTRIBUTION_HPP

#include <am120/model/dllModel.hpp>
#include <am120/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am120/model/IDiscreteValueDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TruncatedDiscreteValueDistribution_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am120
{
    namespace model
    {

    class EXPORT_AM120_MODEL_DLL TruncatedDiscreteValueDistribution : public virtual ::am120::model::IDiscreteValueDeviation
    {
    public:
        TruncatedDiscreteValueDistribution();

        ~TruncatedDiscreteValueDistribution() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes
        virtual ::ecore::ELongObject getLowerBound () const;
        virtual void setLowerBound (::ecore::ELongObject _lowerBound);

        virtual ::ecore::ELongObject getUpperBound () const;
        virtual void setUpperBound (::ecore::ELongObject _upperBound);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TRUNCATEDDISCRETEVALUEDISTRIBUTION;

        /*PROTECTED REGION ID(TruncatedDiscreteValueDistribution) ENABLED START*/
        ::ecore::ELongObject getLowerBound () override
        {
            return const_cast<const TruncatedDiscreteValueDistribution*>(this)->getLowerBound();}
        ::ecore::ELongObject getUpperBound () override
        {
            return const_cast<const TruncatedDiscreteValueDistribution*>(this)->getUpperBound();}
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(TruncatedDiscreteValueDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TruncatedDiscreteValueDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<TruncatedDiscreteValueDistribution>(shared_from_this());}

        // Attributes

        ::ecore::ELongObject m_lowerBound
        {};

        ::ecore::ELongObject m_upperBound
        {};

        // References

    };

}
 // model
}// am120

#endif // AM120_MODEL_TRUNCATEDDISCRETEVALUEDISTRIBUTION_HPP

