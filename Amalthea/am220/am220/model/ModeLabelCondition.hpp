// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am220/model/ModeLabelCondition.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM220_MODEL_MODELABELCONDITION_HPP
#define AM220_MODEL_MODELABELCONDITION_HPP

#include <am220/model/dllModel.hpp>
#include <am220/model_forward.hpp>

#include <am220/model/BaseObject.hpp>
#include <am220/model/ModeCondition.hpp>
#include <am220/model/RelationalOperator.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(ModeLabelCondition_pre) ENABLED START*/
#include <map>
/*PROTECTED REGION END*/

namespace am220
{
    namespace model
    {

    class EXPORT_AM220_MODEL_DLL ModeLabelCondition : public virtual ::am220::model::BaseObject, public virtual ::am220::model::ModeCondition
    {
    public:
        ModeLabelCondition();

        ~ModeLabelCondition() override;

        void _initialize() override;

        // Operations

        virtual ::ecore::EBoolean isSatisfiedBy ( [[maybe_unused]]std::vector< ::am220::model::ModeValueMapEntry_ptr > _context);

        virtual ::ecore::EBoolean validateInvariants ( [[maybe_unused]]::ecore::EDiagnosticChain _diagnostics, [[maybe_unused]]std::map< ::ecore::EJavaObject, ::ecore::EJavaObject> _context);

        // Attributes

        // References
        virtual ::am220::model::ModeLabel_ptr getLabel1 () const;
        virtual void setLabel1 (::am220::model::ModeLabel_ptr _label1);

        virtual ::am220::model::ModeLabel_ptr getLabel2 () const;
        virtual void setLabel2 (::am220::model::ModeLabel_ptr _label2);

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::MODELABELCONDITION;

        /*PROTECTED REGION ID(ModeLabelCondition) START*/
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

        /*PROTECTED REGION ID(ModeLabelConditionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        ModeLabelCondition_ptr _this()
        {   return std::dynamic_pointer_cast<ModeLabelCondition>(shared_from_this());}

        // Attributes

        // References

        std::weak_ptr< ::am220::model::ModeLabel > m_label1;

        std::weak_ptr< ::am220::model::ModeLabel > m_label2;

    };

}
 // model
}// am220

#endif // AM220_MODEL_MODELABELCONDITION_HPP

