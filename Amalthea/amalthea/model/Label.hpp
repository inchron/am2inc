// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/Label.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_LABEL_HPP
#define AMALTHEA_MODEL_LABEL_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/AbstractMemoryElement.hpp>
#include <amalthea/model/IDisplayName.hpp>
#include <amalthea/model/INamespaceMember.hpp>
#include <amalthea/model/LabelDataStability.hpp>
#include <amalthea/model/DataStabilityLevel.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Label_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL Label : public virtual ::amalthea::model::AbstractMemoryElement, public virtual ::amalthea::model::IDisplayName, public virtual ::amalthea::model::INamespaceMember
    {
    public:
        Label();

        virtual ~Label();

        virtual void _initialize();

        // Operations

        // Attributes
        virtual ::ecore::EBoolean isConstant () const;
        virtual void setConstant (::ecore::EBoolean _constant);

        virtual ::ecore::EBoolean isBVolatile () const;
        virtual void setBVolatile (::ecore::EBoolean _bVolatile);

        virtual ::amalthea::model::LabelDataStability getDataStability () const;
        virtual void setDataStability (::amalthea::model::LabelDataStability _dataStability);

        virtual ::amalthea::model::DataStabilityLevel getStabilityLevel () const;
        virtual void setStabilityLevel (::amalthea::model::DataStabilityLevel _stabilityLevel);

        // References
        virtual ::amalthea::model::DataType_ptr getDataType () const;
        virtual void setDataType (::amalthea::model::DataType_ptr _dataType);

        virtual ::amalthea::model::Section_ptr getSection () const;
        virtual void setSection (::amalthea::model::Section_ptr _section);

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::LabelAccess_ptr >& getLabelAccesses () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::LabelAccess_ptr >& getLabelAccesses ();

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::Component_ptr >& getReferringComponents () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::Component_ptr >& getReferringComponents ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::LABEL;

        /*PROTECTED REGION ID(Label) ENABLED START*/
        using INamespaceMember::getNamespace;
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet ( ::ecore::EInt _featureID, ::ecore::EBoolean _resolve);
        virtual void eSet ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet ( ::ecore::EInt _featureID);
        virtual void eUnset ( ::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass ();
        virtual void _inverseAdd ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _newValue);
        virtual void _inverseRemove ( ::ecore::EInt _featureID, ::ecore::EJavaObject const& _oldValue);

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

        ::amalthea::model::LabelDataStability m_dataStability
        {};

        ::amalthea::model::DataStabilityLevel m_stabilityLevel
        {};

        // References

        ::amalthea::model::DataType_ptr m_dataType;

        std::weak_ptr< ::amalthea::model::Section > m_section;

        ::ecore::EList_ptr< ::amalthea::model::LabelAccess_ptr > m_labelAccesses;

        ::ecore::EList_ptr< ::amalthea::model::Component_ptr > m_referringComponents;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_LABEL_HPP

