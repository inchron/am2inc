// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/DiscreteValueStatistics.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM210_MODEL_DISCRETEVALUESTATISTICS_HPP
#define AM210_MODEL_DISCRETEVALUESTATISTICS_HPP

#include <am210/model/dllModel.hpp>
#include <am210/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am210/model/BoundedDiscreteValueDistribution.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(DiscreteValueStatistics_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am210
{
    namespace model
    {

    class EXPORT_AM210_MODEL_DLL DiscreteValueStatistics : public virtual ::am210::model::BoundedDiscreteValueDistribution
    {
    public:
        DiscreteValueStatistics();

        ~DiscreteValueStatistics() override;

        void _initialize() override;

        // Operations

        // Attributes
        virtual ::ecore::EDoubleObject getAverage () const;
        virtual void setAverage (::ecore::EDoubleObject _average);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::DISCRETEVALUESTATISTICS;

        /*PROTECTED REGION ID(DiscreteValueStatistics) ENABLED START*/
        ::ecore::EDoubleObject getAverage () override
        {
            return const_cast<const DiscreteValueStatistics*>(this)->getAverage();}
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(DiscreteValueStatisticsImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        DiscreteValueStatistics_ptr _this()
        {   return std::dynamic_pointer_cast<DiscreteValueStatistics>(shared_from_this());}

        // Attributes

        ::ecore::EDoubleObject m_average
        {   0.0};

        // References

    };

}
 // model
}// am210

#endif // AM210_MODEL_DISCRETEVALUESTATISTICS_HPP

