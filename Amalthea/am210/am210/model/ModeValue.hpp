// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am210/model/ModeValue.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM210_MODEL_MODEVALUE_HPP
#define AM210_MODEL_MODEVALUE_HPP

#include <am210/model/dllModel.hpp>
#include <am210/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am210/model/BaseObject.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ModeValue_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am210
{
    namespace model
    {

    class EXPORT_AM210_MODEL_DLL ModeValue : public virtual ::am210::model::BaseObject
    {
    public:
        ModeValue();

        ~ModeValue() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        virtual ::am210::model::ModeLiteral_ptr getLiteral ();

        virtual ::ecore::EIntegerObject getInteger ();

        // Attributes
        virtual ::ecore::EString const& getValue () const;
        virtual void setValue (::ecore::EString const& _value);

        // References
        virtual ::am210::model::ModeLabel_ptr getLabel () const;
        virtual void setLabel (::am210::model::ModeLabel_ptr _label);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MODEVALUE;

        /*PROTECTED REGION ID(ModeValue) START*/
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

        /*PROTECTED REGION ID(ModeValueImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ModeValue_ptr _this()
        {   return std::dynamic_pointer_cast<ModeValue>(shared_from_this());}

        // Attributes

        ::ecore::EString m_value
        {};

        // References

        std::weak_ptr< ::am210::model::ModeLabel > m_label;

    };

}
 // model
}// am210

#endif // AM210_MODEL_MODEVALUE_HPP

