// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/TruncatedTimeDistribution.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM120_MODEL_TRUNCATEDTIMEDISTRIBUTION_HPP
#define AM120_MODEL_TRUNCATEDTIMEDISTRIBUTION_HPP

#include <am120/model/dllModel.hpp>
#include <am120/model_forward.hpp>

#include <am120/model/ITimeDeviation.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TruncatedTimeDistribution_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am120
{
    namespace model
    {

    class EXPORT_AM120_MODEL_DLL TruncatedTimeDistribution : public virtual ::am120::model::ITimeDeviation
    {
    public:
        TruncatedTimeDistribution();

        ~TruncatedTimeDistribution() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes

        // References
        virtual ::am120::model::Time_ptr getLowerBound () const;
        virtual void setLowerBound (::am120::model::Time_ptr _lowerBound);

        virtual ::am120::model::Time_ptr getUpperBound () const;
        virtual void setUpperBound (::am120::model::Time_ptr _upperBound);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TRUNCATEDTIMEDISTRIBUTION;

        /*PROTECTED REGION ID(TruncatedTimeDistribution) ENABLED START*/
        /* Reimplement the abstract operations from ITimeDeviation, which are
         * defined non-const. */
        ::am120::model::Time_ptr getLowerBound() override
        {
            return const_cast<const TruncatedTimeDistribution*>( this )->getLowerBound();
        }
        ::am120::model::Time_ptr getUpperBound() override
        {
            return const_cast<const TruncatedTimeDistribution*>( this )->getUpperBound();
        }
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(TruncatedTimeDistributionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TruncatedTimeDistribution_ptr _this()
        {   return std::dynamic_pointer_cast<TruncatedTimeDistribution>(shared_from_this());}

        // Attributes

        // References

        ::am120::model::Time_ptr m_lowerBound;

        ::am120::model::Time_ptr m_upperBound;

    };

}
 // model
}// am120

#endif // AM120_MODEL_TRUNCATEDTIMEDISTRIBUTION_HPP

