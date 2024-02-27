// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am320/model/Label.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM320_MODEL_LABEL_HPP
#define AM320_MODEL_LABEL_HPP

#include <am320/model/dllModel.hpp>
#include <am320/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am320/model/AbstractMemoryElement.hpp>
#include <am320/model/IDisplayName.hpp>
#include <am320/model/INamespaceMember.hpp>
#include <am320/model/LabelDataStability.hpp>
#include <am320/model/DataStabilityLevel.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Label_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am320
{
    namespace model
    {

    class EXPORT_AM320_MODEL_DLL Label : public virtual ::am320::model::AbstractMemoryElement, public virtual ::am320::model::IDisplayName, public virtual ::am320::model::INamespaceMember
    {
    public:
        Label();

        ~Label() override;

        void _initialize() override;

        // Operations

        // Attributes
        virtual ::ecore::EBoolean isConstant () const;
        virtual void setConstant (::ecore::EBoolean _constant);

        virtual ::ecore::EBoolean isBVolatile () const;
        virtual void setBVolatile (::ecore::EBoolean _bVolatile);

        virtual ::am320::model::LabelDataStability getDataStability () const;
        virtual void setDataStability (::am320::model::LabelDataStability _dataStability);

        virtual ::am320::model::DataStabilityLevel getStabilityLevel () const;
        virtual void setStabilityLevel (::am320::model::DataStabilityLevel _stabilityLevel);

        // References
        virtual ::am320::model::TypeDefinition_ptr getDataType () const;
        virtual void setDataType (::am320::model::TypeDefinition_ptr _dataType);

        virtual ::am320::model::Section_ptr getSection () const;
        virtual void setSection (::am320::model::Section_ptr _section);

        virtual const ::ecorecpp::mapping::EList< ::am320::model::LabelAccess_ptr >& getLabelAccesses () const;
        virtual ::ecorecpp::mapping::EList< ::am320::model::LabelAccess_ptr >& getLabelAccesses ();

        virtual const ::ecorecpp::mapping::EList< ::am320::model::Component_ptr >& getReferringComponents () const;
        virtual ::ecorecpp::mapping::EList< ::am320::model::Component_ptr >& getReferringComponents ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::LABEL;

        /*PROTECTED REGION ID(Label) ENABLED START*/
        using INamespaceMember::getNamespace;
        /*PROTECTED REGION END*/

        // EObjectImpl
        ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve) override;
        void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID) override;
        void eUnset ( ::ecore::EInt _featureID) override;
        ::ecore::EClass_ptr _eClass () override;
        void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue) override;
        void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue) override;

        /*PROTECTED REGION ID(LabelImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        Label_ptr _this()
        {   return std::dynamic_pointer_cast<Label>(shared_from_this());}

        // Attributes

        ::ecore::EBoolean m_constant
        {   false};

        ::ecore::EBoolean m_bVolatile
        {   false};

        ::am320::model::LabelDataStability m_dataStability
        {};

        ::am320::model::DataStabilityLevel m_stabilityLevel
        {};

        // References

        std::weak_ptr< ::am320::model::TypeDefinition > m_dataType;

        std::weak_ptr< ::am320::model::Section > m_section;

        ::ecore::EList_ptr< ::am320::model::LabelAccess_ptr > m_labelAccesses;

        ::ecore::EList_ptr< ::am320::model::Component_ptr > m_referringComponents;

    };

}
 // model
}// am320

#endif // AM320_MODEL_LABEL_HPP

