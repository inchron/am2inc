// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/TimeBoundaries.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_TIMEBOUNDARIES_HPP
#define AMALTHEA_MODEL_TIMEBOUNDARIES_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <amalthea/model/BoundedTimeDistribution.hpp>
#include <amalthea/model/SamplingType.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(TimeBoundaries_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL TimeBoundaries : public virtual ::amalthea::model::BoundedTimeDistribution
    {
    public:
        TimeBoundaries();

        virtual ~TimeBoundaries();

        virtual void _initialize();

        // Operations

        // Attributes
        virtual ::amalthea::model::SamplingType getSamplingType () const;
        virtual void setSamplingType (::amalthea::model::SamplingType _samplingType);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::TIMEBOUNDARIES;

        /*PROTECTED REGION ID(TimeBoundaries) ENABLED START*/
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

        /*PROTECTED REGION ID(TimeBoundariesImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        TimeBoundaries_ptr _this()
        {   return std::dynamic_pointer_cast<TimeBoundaries>(shared_from_this());}

        // Attributes

        ::amalthea::model::SamplingType m_samplingType
        {};

        // References

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_TIMEBOUNDARIES_HPP

