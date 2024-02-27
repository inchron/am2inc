// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/ModeLabelAccess.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM220_MODEL_MODELABELACCESS_HPP
#define AM220_MODEL_MODELABELACCESS_HPP

#include <am220/model/dllModel.hpp>
#include <am220/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am220/model/ActivityGraphItem.hpp>
#include <am220/model/ModeLabelAccessEnum.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ModeLabelAccess_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am220
{
    namespace model
    {

    class EXPORT_AM220_MODEL_DLL ModeLabelAccess : public virtual ::am220::model::ActivityGraphItem
    {
    public:
        ModeLabelAccess();

        ~ModeLabelAccess() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes
        virtual ::am220::model::ModeLabelAccessEnum getAccess () const;
        virtual void setAccess (::am220::model::ModeLabelAccessEnum _access);

        virtual ::ecore::EString const& getValue () const;
        virtual void setValue (::ecore::EString const& _value);

        virtual ::am220::model::PositiveInt getStep () const;
        virtual void setStep (::am220::model::PositiveInt _step);

        // References
        virtual ::am220::model::ModeLabel_ptr getData () const;
        virtual void setData (::am220::model::ModeLabel_ptr _data);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MODELABELACCESS;

        /*PROTECTED REGION ID(ModeLabelAccess) START*/
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

        /*PROTECTED REGION ID(ModeLabelAccessImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ModeLabelAccess_ptr _this()
        {   return std::dynamic_pointer_cast<ModeLabelAccess>(shared_from_this());}

        // Attributes

        ::am220::model::ModeLabelAccessEnum m_access
        {};

        ::ecore::EString m_value
        {};

        ::am220::model::PositiveInt m_step
        {   1};

        // References

        std::weak_ptr< ::am220::model::ModeLabel > m_data;

    };

}
 // model
}// am220

#endif // AM220_MODEL_MODELABELACCESS_HPP

