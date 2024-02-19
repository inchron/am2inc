// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/Runnable.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM120_MODEL_RUNNABLE_HPP
#define AM120_MODEL_RUNNABLE_HPP

#include <am120/model/dllModel.hpp>
#include <am120/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am120/model/AbstractMemoryElement.hpp>
#include <am120/model/IExecutable.hpp>
#include <am120/model/INamespaceMember.hpp>
#include <am120/model/ASILType.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Runnable_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am120
{
    namespace model
    {

    class EXPORT_AM120_MODEL_DLL Runnable : public virtual ::am120::model::AbstractMemoryElement, public virtual ::am120::model::IExecutable, public virtual ::am120::model::INamespaceMember
    {
    public:
        Runnable();

        virtual ~Runnable();

        virtual void _initialize();

        // Operations

        virtual std::vector< ::am120::model::ActivityGraphItem_ptr > getRunnableItems ();

        virtual ::am120::model::Activation_ptr getFirstActivation ();

        // Attributes
        virtual ::ecore::EBoolean isCallback () const;
        virtual void setCallback (::ecore::EBoolean _callback);

        virtual ::ecore::EBoolean isService () const;
        virtual void setService (::ecore::EBoolean _service);

        virtual ::am120::model::ASILType getAsilLevel () const;
        virtual void setAsilLevel (::am120::model::ASILType _asilLevel);

        // References
        virtual ::am120::model::ModeConditionDisjunction_ptr getExecutionCondition () const;
        virtual void setExecutionCondition (::am120::model::ModeConditionDisjunction_ptr _executionCondition);

        virtual const ::ecorecpp::mapping::EList< ::am120::model::RunnableParameter_ptr >& getParameters () const;
        virtual ::ecorecpp::mapping::EList< ::am120::model::RunnableParameter_ptr >& getParameters ();

        virtual const ::ecorecpp::mapping::EList< ::am120::model::Activation_ptr >& getActivations () const;
        virtual ::ecorecpp::mapping::EList< ::am120::model::Activation_ptr >& getActivations ();

        virtual ::am120::model::Section_ptr getSection () const;
        virtual void setSection (::am120::model::Section_ptr _section);

        virtual const ::ecorecpp::mapping::EList< ::am120::model::RunnableCall_ptr >& getRunnableCalls () const;
        virtual ::ecorecpp::mapping::EList< ::am120::model::RunnableCall_ptr >& getRunnableCalls ();

        virtual const ::ecorecpp::mapping::EList< ::am120::model::Component_ptr >& getReferringComponents () const;
        virtual ::ecorecpp::mapping::EList< ::am120::model::Component_ptr >& getReferringComponents ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::RUNNABLE;

        /*PROTECTED REGION ID(Runnable) ENABLED START*/
        using INamespaceMember::getNamespace;
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

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

        ::am120::model::ASILType m_asilLevel
        {};

        // References

        ::am120::model::ModeConditionDisjunction_ptr m_executionCondition;

        ::ecore::EList_ptr< ::am120::model::RunnableParameter_ptr > m_parameters;

        ::ecore::EList_ptr< ::am120::model::Activation_ptr > m_activations;

        std::weak_ptr< ::am120::model::Section > m_section;

        ::ecore::EList_ptr< ::am120::model::RunnableCall_ptr > m_runnableCalls;

        ::ecore::EList_ptr< ::am120::model::Component_ptr > m_referringComponents;

    };

}
 // model
}// am120

#endif // AM120_MODEL_RUNNABLE_HPP

