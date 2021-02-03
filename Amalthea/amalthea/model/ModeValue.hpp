// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/ModeValue.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_MODEVALUE_HPP
#define AMALTHEA_MODEL_MODEVALUE_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/BaseObject.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ModeValue_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL ModeValue : public virtual ::amalthea::model::BaseObject
    {
    public:
        ModeValue();

        virtual ~ModeValue();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( ::ecore::EDiagnosticChain _diagnostics, std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        virtual ::amalthea::model::ModeLiteral_ptr getLiteral ();

        virtual ::ecore::EIntegerObject getInteger ();

        // Attributes
        virtual ::ecore::EString const& getValue () const;
        virtual void setValue (::ecore::EString const& _value);

        // References
        virtual ::amalthea::model::ModeLabel_ptr getLabel () const;
        virtual void setLabel (::amalthea::model::ModeLabel_ptr _label);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MODEVALUE;

        /*PROTECTED REGION ID(ModeValue) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

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

        std::weak_ptr< ::amalthea::model::ModeLabel > m_label;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_MODEVALUE_HPP

