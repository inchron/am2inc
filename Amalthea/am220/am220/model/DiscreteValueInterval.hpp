// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/DiscreteValueInterval.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM220_MODEL_DISCRETEVALUEINTERVAL_HPP
#define AM220_MODEL_DISCRETEVALUEINTERVAL_HPP

#include <ecore/EObject.hpp>

#include <am220/model/dllModel.hpp>
#include <am220/model_forward.hpp>

#include <ecore_forward.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(DiscreteValueInterval_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am220
{
    namespace model
    {

    class EXPORT_AM220_MODEL_DLL DiscreteValueInterval : public virtual ::ecore::EObject
    {
    public:
        DiscreteValueInterval();

        ~DiscreteValueInterval() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EDoubleObject getAverage ();

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes
        virtual ::ecore::ELongObject getLowerBound () const;
        virtual void setLowerBound (::ecore::ELongObject _lowerBound);

        virtual ::ecore::ELongObject getUpperBound () const;
        virtual void setUpperBound (::ecore::ELongObject _upperBound);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::DISCRETEVALUEINTERVAL;

        /*PROTECTED REGION ID(DiscreteValueInterval) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(DiscreteValueIntervalImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        DiscreteValueInterval_ptr _this()
        {   return std::dynamic_pointer_cast<DiscreteValueInterval>(shared_from_this());}

        // Attributes

        ::ecore::ELongObject m_lowerBound
        {   0};

        ::ecore::ELongObject m_upperBound
        {   0};

        // References

    };

}
 // model
}// am220

#endif // AM220_MODEL_DISCRETEVALUEINTERVAL_HPP

