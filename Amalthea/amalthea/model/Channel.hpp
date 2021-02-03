// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model/Channel.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AMALTHEA_MODEL_CHANNEL_HPP
#define AMALTHEA_MODEL_CHANNEL_HPP

#include <amalthea/model/dllModel.hpp>
#include <amalthea/model_forward.hpp>

#include <ecore_forward.hpp>
#include <amalthea/model/AbstractMemoryElement.hpp>
#include <amalthea/model/IDisplayName.hpp>
#include <amalthea/model/INamespaceMember.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Channel_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace amalthea
{
    namespace model
    {

    class EXPORT_AMALTHEA_MODEL_DLL Channel : public virtual ::amalthea::model::AbstractMemoryElement, public virtual ::amalthea::model::IDisplayName, public virtual ::amalthea::model::INamespaceMember
    {
    public:
        Channel();

        virtual ~Channel();

        virtual void _initialize();

        // Operations

        // Attributes
        virtual ::ecore::EInt getDefaultElements () const;
        virtual void setDefaultElements (::ecore::EInt _defaultElements);

        virtual ::ecore::EInt getMaxElements () const;
        virtual void setMaxElements (::ecore::EInt _maxElements);

        // References
        virtual ::amalthea::model::DataType_ptr getElementType () const;
        virtual void setElementType (::amalthea::model::DataType_ptr _elementType);

        virtual const ::ecorecpp::mapping::EList< ::amalthea::model::ChannelAccess_ptr >& getChannelAccesses () const;
        virtual ::ecorecpp::mapping::EList< ::amalthea::model::ChannelAccess_ptr >& getChannelAccesses ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::CHANNEL;

        /*PROTECTED REGION ID(Channel) ENABLED START*/
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

        /*PROTECTED REGION ID(ChannelImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        Channel_ptr _this()
        {   return std::dynamic_pointer_cast<Channel>(shared_from_this());}

        // Attributes

        ::ecore::EInt m_defaultElements
        {   0};

        ::ecore::EInt m_maxElements
        {   0};

        // References

        ::amalthea::model::DataType_ptr m_elementType;

        ::ecore::EList_ptr< ::amalthea::model::ChannelAccess_ptr > m_channelAccesses;

    };

}
 // model
}// amalthea

#endif // AMALTHEA_MODEL_CHANNEL_HPP

