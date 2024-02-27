// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/ModeLabelAssignment.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM320_MODEL_MODELABELASSIGNMENT_HPP
#define AM320_MODEL_MODELABELASSIGNMENT_HPP

#include <am320/model/dllModel.hpp>
#include <am320/model_forward.hpp>

#include <am320/model/ActivityGraphItem.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ModeLabelAssignment_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am320
{
    namespace model
    {

    class EXPORT_AM320_MODEL_DLL ModeLabelAssignment : public virtual ::am320::model::ActivityGraphItem
    {
    public:
        ModeLabelAssignment();

        ~ModeLabelAssignment() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes

        // References
        virtual ::am320::model::ModeLabel_ptr getGlobalLabel () const;
        virtual void setGlobalLabel (::am320::model::ModeLabel_ptr _globalLabel);

        virtual ::am320::model::LocalModeLabel_ptr getLocalLabel () const;
        virtual void setLocalLabel (::am320::model::LocalModeLabel_ptr _localLabel);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MODELABELASSIGNMENT;

        /*PROTECTED REGION ID(ModeLabelAssignment) START*/
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

        /*PROTECTED REGION ID(ModeLabelAssignmentImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ModeLabelAssignment_ptr _this()
        {   return std::dynamic_pointer_cast<ModeLabelAssignment>(shared_from_this());}

        // Attributes

        // References

        std::weak_ptr< ::am320::model::ModeLabel > m_globalLabel;

        std::weak_ptr< ::am320::model::LocalModeLabel > m_localLabel;

    };

}
 // model
}// am320

#endif // AM320_MODEL_MODELABELASSIGNMENT_HPP

