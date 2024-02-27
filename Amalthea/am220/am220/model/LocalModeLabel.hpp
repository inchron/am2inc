// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/LocalModeLabel.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM220_MODEL_LOCALMODELABEL_HPP
#define AM220_MODEL_LOCALMODELABEL_HPP

#include <am220/model/dllModel.hpp>
#include <am220/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am220/model/ReferableBaseObject.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(LocalModeLabel_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am220
{
    namespace model
    {

    class EXPORT_AM220_MODEL_DLL LocalModeLabel : public virtual ::am220::model::ReferableBaseObject
    {
    public:
        LocalModeLabel();

        ~LocalModeLabel() override;

        void _initialize() override;

        // Operations

        virtual std::vector< ::ecore::EString > getNamePrefixSegments ();

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        virtual ::ecore::EBoolean isEnum ();

        virtual ::ecore::EBoolean isNumeric ();

        // Attributes
        virtual ::ecore::EString const& getDefaultValue () const;
        virtual void setDefaultValue (::ecore::EString const& _defaultValue);

        // References
        virtual ::am220::model::IExecutable_ptr getContainingExecutable () const;
        virtual void setContainingExecutable (::am220::model::IExecutable_ptr _containingExecutable);
        virtual ::am220::model::IExecutable_ptr basicgetContainingExecutable ();
        virtual void basicsetContainingExecutable (::am220::model::IExecutable_ptr _containingExecutable);

        virtual ::am220::model::Mode_ptr getMode () const;
        virtual void setMode (::am220::model::Mode_ptr _mode);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::LOCALMODELABEL;

        /*PROTECTED REGION ID(LocalModeLabel) START*/
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

        /*PROTECTED REGION ID(LocalModeLabelImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        LocalModeLabel_ptr _this()
        {   return std::dynamic_pointer_cast<LocalModeLabel>(shared_from_this());}

        // Attributes

        ::ecore::EString m_defaultValue
        {};

        // References

        std::weak_ptr< ::am220::model::IExecutable > m_containingExecutable;

        std::weak_ptr< ::am220::model::Mode > m_mode;

    };

}
 // model
}// am220

#endif // AM220_MODEL_LOCALMODELABEL_HPP

