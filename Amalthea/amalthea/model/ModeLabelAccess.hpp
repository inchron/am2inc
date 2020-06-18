// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/ModeLabelAccess.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_MODELABELACCESS_HPP
#define AMALTHEA_MODEL_MODELABELACCESS_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/ActivityGraphItem.hpp>
#include <amalthea/model/ModeLabelAccessEnum.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ModeLabelAccess_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL ModeLabelAccess : public virtual ::amalthea::model::ActivityGraphItem
    {
    public:
        ModeLabelAccess();

        virtual ~ModeLabelAccess();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( ::ecore::EDiagnosticChain _diagnostics, std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes
        virtual ::amalthea::model::ModeLabelAccessEnum getAccess () const;
        virtual void setAccess (::amalthea::model::ModeLabelAccessEnum _access);

        virtual ::ecore::EString const& getValue () const;
        virtual void setValue (::ecore::EString const& _value);

        virtual ::amalthea::model::PositiveInt getStep () const;
        virtual void setStep (::amalthea::model::PositiveInt _step);

        // References
        virtual ::amalthea::model::ModeLabel_ptr getData () const;
        virtual void setData (::amalthea::model::ModeLabel_ptr _data);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MODELABELACCESS;

        /*PROTECTED REGION ID(ModeLabelAccess) START*/
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

        /*PROTECTED REGION ID(ModeLabelAccessImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ModeLabelAccess_ptr _this()
        {   return std::dynamic_pointer_cast<ModeLabelAccess>(shared_from_this());}

        // Attributes

        ::amalthea::model::ModeLabelAccessEnum m_access
        {};

        ::ecore::EString m_value
        {};

        ::amalthea::model::PositiveInt m_step
        {   1};

        // References

        std::weak_ptr< ::amalthea::model::ModeLabel > m_data;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_MODELABELACCESS_HPP

