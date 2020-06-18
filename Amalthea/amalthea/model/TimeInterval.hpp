// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/TimeInterval.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_TIMEINTERVAL_HPP
#define AMALTHEA_MODEL_TIMEINTERVAL_HPP

#include <ecore/EObject.hpp>

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TimeInterval_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL TimeInterval : public virtual ::ecore::EObject
    {
    public:
        TimeInterval();

        virtual ~TimeInterval();

        virtual void _initialize();

        // Operations

        virtual ::amalthea::model::Time_ptr getAverage ();

        virtual ::ecore::EBoolean validateInvariants ( ::ecore::EDiagnosticChain _diagnostics, std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes

        // References
        virtual ::amalthea::model::Time_ptr getLowerBound () const;
        virtual void setLowerBound (::amalthea::model::Time_ptr _lowerBound);

        virtual ::amalthea::model::Time_ptr getUpperBound () const;
        virtual void setUpperBound (::amalthea::model::Time_ptr _upperBound);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TIMEINTERVAL;

        /*PROTECTED REGION ID(TimeInterval) START*/
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

        /*PROTECTED REGION ID(TimeIntervalImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TimeInterval_ptr _this()
        {   return std::dynamic_pointer_cast<TimeInterval>(shared_from_this());}

        // Attributes

        // References

        ::amalthea::model::Time_ptr m_lowerBound;

        ::amalthea::model::Time_ptr m_upperBound;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_TIMEINTERVAL_HPP

