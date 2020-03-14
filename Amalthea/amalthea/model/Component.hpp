// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/Component.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_COMPONENT_HPP
#define AMALTHEA_MODEL_COMPONENT_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/ReferableBaseObject.hpp>
#include <amalthea/model/ITaggable.hpp>
#include <amalthea/model/INamespaceMember.hpp>
#include <amalthea/model/IComponentStructureMember.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Component_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL Component : public virtual ::amalthea::model::ReferableBaseObject, public virtual ::amalthea::model::ITaggable, public virtual ::amalthea::model::INamespaceMember, public virtual ::amalthea::model::IComponentStructureMember
    {
    public:
        Component();

        virtual ~Component();

        virtual void _initialize();

        // Operations

        // Attributes

        // References
        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::ComponentPort_ptr >& getPorts () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::ComponentPort_ptr >& getPorts ();

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::AbstractProcess_ptr >& getProcesses () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::AbstractProcess_ptr >& getProcesses ();

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::Runnable_ptr >& getRunnables () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::Runnable_ptr >& getRunnables ();

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::Label_ptr >& getLabels () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::Label_ptr >& getLabels ();

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::Semaphore_ptr >& getSemaphores () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::Semaphore_ptr >& getSemaphores ();

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::OsEvent_ptr >& getOsEvents () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::OsEvent_ptr >& getOsEvents ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::COMPONENT;

        /*PROTECTED REGION ID(Component) ENABLED START*/
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

        /*PROTECTED REGION ID(ComponentImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        Component_ptr _this()
        {   return std::dynamic_pointer_cast<Component>(shared_from_this());}

        // Attributes

        // References

        ::ecore::EList_ptr< ::amalthea::model::ComponentPort_ptr > m_ports;

        ::ecore::EList_ptr< ::amalthea::model::AbstractProcess_ptr > m_processes;

        ::ecore::EList_ptr< ::amalthea::model::Runnable_ptr > m_runnables;

        ::ecore::EList_ptr< ::amalthea::model::Label_ptr > m_labels;

        ::ecore::EList_ptr< ::amalthea::model::Semaphore_ptr > m_semaphores;

        ::ecore::EList_ptr< ::amalthea::model::OsEvent_ptr > m_osEvents;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_COMPONENT_HPP

