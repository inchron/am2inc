// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am200/model/MinAvgMaxStatistic.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM200_MODEL_MINAVGMAXSTATISTIC_HPP
#define AM200_MODEL_MINAVGMAXSTATISTIC_HPP

#include <am200/model/dllModel.hpp>
#include <am200/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am200/model/NumericStatistic.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(MinAvgMaxStatistic_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am200
{
    namespace model
    {

    class EXPORT_AM200_MODEL_DLL MinAvgMaxStatistic : public virtual ::am200::model::NumericStatistic
    {
    public:
        MinAvgMaxStatistic();

        ~MinAvgMaxStatistic() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes
        virtual ::ecore::EInt getMin () const;
        virtual void setMin (::ecore::EInt _min);

        virtual ::ecore::EFloat getAvg () const;
        virtual void setAvg (::ecore::EFloat _avg);

        virtual ::ecore::EInt getMax () const;
        virtual void setMax (::ecore::EInt _max);

        // References

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MINAVGMAXSTATISTIC;

        /*PROTECTED REGION ID(MinAvgMaxStatistic) START*/
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

        /*PROTECTED REGION ID(MinAvgMaxStatisticImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        MinAvgMaxStatistic_ptr _this()
        {   return std::dynamic_pointer_cast<MinAvgMaxStatistic>(shared_from_this());}

        // Attributes

        ::ecore::EInt m_min
        {   0};

        ::ecore::EFloat m_avg
        {   0.f};

        ::ecore::EInt m_max
        {   0};

        // References

    };

}
 // model
}// am200

#endif // AM200_MODEL_MINAVGMAXSTATISTIC_HPP

