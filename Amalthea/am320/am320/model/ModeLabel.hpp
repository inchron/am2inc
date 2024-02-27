// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/ModeLabel.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM320_MODEL_MODELABEL_HPP
#define AM320_MODEL_MODELABEL_HPP

#include <am320/model/dllModel.hpp>
#include <am320/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am320/model/AbstractMemoryElement.hpp>
#include <am320/model/IDisplayName.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ModeLabel_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am320
{
    namespace model
    {

    class EXPORT_AM320_MODEL_DLL ModeLabel : public virtual ::am320::model::AbstractMemoryElement, public virtual ::am320::model::IDisplayName
    {
    public:
        ModeLabel();

        ~ModeLabel() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        virtual ::ecore::EBoolean isEnum ();

        virtual ::ecore::EBoolean isNumeric ();

        // Attributes
        virtual ::ecore::EString const& getInitialValue () const;
        virtual void setInitialValue (::ecore::EString const& _initialValue);

        // References
        virtual ::am320::model::Mode_ptr getMode () const;
        virtual void setMode (::am320::model::Mode_ptr _mode);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MODELABEL;

        /*PROTECTED REGION ID(ModeLabel) START*/
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

        /*PROTECTED REGION ID(ModeLabelImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ModeLabel_ptr _this()
        {   return std::dynamic_pointer_cast<ModeLabel>(shared_from_this());}

        // Attributes

        ::ecore::EString m_initialValue
        {};

        // References

        std::weak_ptr< ::am320::model::Mode > m_mode;

    };

}
 // model
}// am320

#endif // AM320_MODEL_MODELABEL_HPP

