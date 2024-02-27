// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/Component.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM210_MODEL_COMPONENT_HPP
#define AM210_MODEL_COMPONENT_HPP

#include <am210/model/dllModel.hpp>
#include <am210/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am210/model/ReferableBaseObject.hpp>
#include <am210/model/ITaggable.hpp>
#include <am210/model/INamespaceMember.hpp>
#include <am210/model/IComponentStructureMember.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Component_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am210
{
    namespace model
    {

    class EXPORT_AM210_MODEL_DLL Component : public virtual ::am210::model::ReferableBaseObject, public virtual ::am210::model::ITaggable, public virtual ::am210::model::INamespaceMember, public virtual ::am210::model::IComponentStructureMember
    {
    public:
        Component();

        ~Component() override;

        void _initialize() override;

        // Operations

        // Attributes

        // References
        virtual const ::ecorecpp::mapping::EList< ::am210::model::ComponentPort_ptr >& getPorts () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::ComponentPort_ptr >& getPorts ();

        virtual const ::ecorecpp::mapping::EList< ::am210::model::AbstractProcess_ptr >& getProcesses () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::AbstractProcess_ptr >& getProcesses ();

        virtual const ::ecorecpp::mapping::EList< ::am210::model::Runnable_ptr >& getRunnables () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::Runnable_ptr >& getRunnables ();

        virtual const ::ecorecpp::mapping::EList< ::am210::model::Label_ptr >& getLabels () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::Label_ptr >& getLabels ();

        virtual const ::ecorecpp::mapping::EList< ::am210::model::Semaphore_ptr >& getSemaphores () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::Semaphore_ptr >& getSemaphores ();

        virtual const ::ecorecpp::mapping::EList< ::am210::model::OsEvent_ptr >& getOsEvents () const;
        virtual ::ecorecpp::mapping::EList< ::am210::model::OsEvent_ptr >& getOsEvents ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::COMPONENT;

        /*PROTECTED REGION ID(Component) ENABLED START*/
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

        /*PROTECTED REGION ID(ComponentImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        Component_ptr _this()
        {   return std::dynamic_pointer_cast<Component>(shared_from_this());}

        // Attributes

        // References

        ::ecore::EList_ptr< ::am210::model::ComponentPort_ptr > m_ports;

        ::ecore::EList_ptr< ::am210::model::AbstractProcess_ptr > m_processes;

        ::ecore::EList_ptr< ::am210::model::Runnable_ptr > m_runnables;

        ::ecore::EList_ptr< ::am210::model::Label_ptr > m_labels;

        ::ecore::EList_ptr< ::am210::model::Semaphore_ptr > m_semaphores;

        ::ecore::EList_ptr< ::am210::model::OsEvent_ptr > m_osEvents;

    };

}
 // model
}// am210

#endif // AM210_MODEL_COMPONENT_HPP

