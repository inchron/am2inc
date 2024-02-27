// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/LocalModeValue.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM220_MODEL_LOCALMODEVALUE_HPP
#define AM220_MODEL_LOCALMODEVALUE_HPP

#include <ecore/EObject.hpp>

#include <am220/model/dllModel.hpp>
#include <am220/model_forward.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(LocalModeValue_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am220
{
    namespace model
    {

    class EXPORT_AM220_MODEL_DLL LocalModeValue : public virtual ::ecore::EObject
    {
    public:
        LocalModeValue();

        ~LocalModeValue() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes

        // References
        virtual ::am220::model::LocalModeLabel_ptr getLabel () const;
        virtual void setLabel (::am220::model::LocalModeLabel_ptr _label);

        virtual ::am220::model::ILocalModeValueSource_ptr getValueSource () const;
        virtual void setValueSource (::am220::model::ILocalModeValueSource_ptr _valueSource);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::LOCALMODEVALUE;

        /*PROTECTED REGION ID(LocalModeValue) START*/
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

        /*PROTECTED REGION ID(LocalModeValueImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        LocalModeValue_ptr _this()
        {   return std::dynamic_pointer_cast<LocalModeValue>(shared_from_this());}

        // Attributes

        // References

        std::weak_ptr< ::am220::model::LocalModeLabel > m_label;

        ::am220::model::ILocalModeValueSource_ptr m_valueSource;

    };

}
 // model
}// am220

#endif // AM220_MODEL_LOCALMODEVALUE_HPP

