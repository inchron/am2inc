// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am120/model/ModeLabelAccess.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM120_MODEL_MODELABELACCESS_HPP
#define AM120_MODEL_MODELABELACCESS_HPP

#include <am120/model/dllModel.hpp>
#include <am120/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am120/model/ActivityGraphItem.hpp>
#include <am120/model/ModeLabelAccessEnum.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ModeLabelAccess_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am120
{
    namespace model
    {

    class EXPORT_AM120_MODEL_DLL ModeLabelAccess : public virtual ::am120::model::ActivityGraphItem
    {
    public:
        ModeLabelAccess();

        virtual ~ModeLabelAccess();

        virtual void _initialize();

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes
        virtual ::am120::model::ModeLabelAccessEnum getAccess () const;
        virtual void setAccess (::am120::model::ModeLabelAccessEnum _access);

        virtual ::ecore::EString const& getValue () const;
        virtual void setValue (::ecore::EString const& _value);

        virtual ::am120::model::PositiveInt getStep () const;
        virtual void setStep (::am120::model::PositiveInt _step);

        // References
        virtual ::am120::model::ModeLabel_ptr getData () const;
        virtual void setData (::am120::model::ModeLabel_ptr _data);

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

        ::am120::model::ModeLabelAccessEnum m_access
        {};

        ::ecore::EString m_value
        {};

        ::am120::model::PositiveInt m_step
        {   1};

        // References

        std::weak_ptr< ::am120::model::ModeLabel > m_data;

    };

}
 // model
}// am120

#endif // AM120_MODEL_MODELABELACCESS_HPP

