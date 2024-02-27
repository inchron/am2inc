// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/Runnable.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM210_MODEL_RUNNABLE_HPP
#define AM210_MODEL_RUNNABLE_HPP

#include <am210/model/dllModel.hpp>
#include <am210/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am210/model/AbstractMemoryElement.hpp>
#include <am210/model/IExecutable.hpp>
#include <am210/model/INamespaceMember.hpp>
#include <am210/model/ASILType.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Runnable_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am210
{
    namespace model
    {

    class EXPORT_AM210_MODEL_DLL Runnable : public virtual ::am210::model::AbstractMemoryElement, public virtual ::am210::model::IExecutable, public virtual ::am210::model::INamespaceMember
    {
    public:
        Runnable();

        ~Runnable() override;

        void _initialize() override;

        // Operations

        virtual std::vector< ::am210::model::ActivityGraphItem_ptr > getRunnableItems ();

        virtual ::am210::model::Activation_ptr getFirstActivation ();

        // Attributes
        virtual ::ecore::EBoolean isCallback () const;
        virtual void setCallback (::ecore::EBoolean _callback);

        virtual ::ecore::EBoolean isService () const;
        virtual void setService (::ecore::EBoolean _service);

        virtual ::am210::model::ASILType getAsilLevel () const;
        virtual void setAsilLevel (::am210::model::ASILType _asilLevel);

        // References
        virtual ::am210::model::ConditionDisjunction_ptr getExecutionCondition () const;
        virtual void setExecutionCondition (::am210::model::ConditionDisjunction_ptr _executionCondition);

        virtual const ::ecorecpp::mapping::EList< ::am210::model::RunnableParameter_ptr >& getParameters () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::RunnableParameter_ptr >& getParameters ();

        virtual const ::ecorecpp::mapping::EList< ::am210::model::Activation_ptr >& getActivations () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::Activation_ptr >& getActivations ();

        virtual ::am210::model::Section_ptr getSection () const;
        virtual void setSection (::am210::model::Section_ptr _section);

        virtual const ::ecorecpp::mapping::EList< ::am210::model::RunnableCall_ptr >& getRunnableCalls () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::RunnableCall_ptr >& getRunnableCalls ();

        virtual const ::ecorecpp::mapping::EList< ::am210::model::Component_ptr >& getReferringComponents () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::Component_ptr >& getReferringComponents ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::RUNNABLE;

        /*PROTECTED REGION ID(Runnable) ENABLED START*/
        using INamespaceMember::getNamespace;
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(RunnableImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        Runnable_ptr _this()
        {   return std::dynamic_pointer_cast<Runnable>(shared_from_this());}

        // Attributes

        ::ecore::EBoolean m_callback
        {   false};

        ::ecore::EBoolean m_service
        {   false};

        ::am210::model::ASILType m_asilLevel
        {};

        // References

        ::am210::model::ConditionDisjunction_ptr m_executionCondition;

        ::ecore::EList_ptr< ::am210::model::RunnableParameter_ptr > m_parameters;

        ::ecore::EList_ptr< ::am210::model::Activation_ptr > m_activations;

        std::weak_ptr< ::am210::model::Section > m_section;

        ::ecore::EList_ptr< ::am210::model::RunnableCall_ptr > m_runnableCalls;

        ::ecore::EList_ptr< ::am210::model::Component_ptr > m_referringComponents;

    };

}
 // model
}// am210

#endif // AM210_MODEL_RUNNABLE_HPP

