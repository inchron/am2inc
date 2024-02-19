// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/DiscreteValueInterval.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM120_MODEL_DISCRETEVALUEINTERVAL_HPP
#define AM120_MODEL_DISCRETEVALUEINTERVAL_HPP

#include <ecore/EObject.hpp>

#include <am120/model/dllModel.hpp>
#include <am120/model_forward.hpp>

#include <ecore_forward.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(DiscreteValueInterval_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am120
{
    namespace model
    {

    class EXPORT_AM120_MODEL_DLL DiscreteValueInterval : public virtual ::ecore::EObject
    {
    public:
        DiscreteValueInterval();

        virtual ~DiscreteValueInterval();

        virtual void _initialize();

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
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

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
}// am120

#endif // AM120_MODEL_DISCRETEVALUEINTERVAL_HPP

