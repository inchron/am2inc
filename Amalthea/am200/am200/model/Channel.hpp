// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am200/model/Channel.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef AM200_MODEL_CHANNEL_HPP
#define AM200_MODEL_CHANNEL_HPP

#include <am200/model/dllModel.hpp>
#include <am200/model_forward.hpp>

#include <ecore_forward.hpp>
#include <am200/model/AbstractMemoryElement.hpp>
#include <am200/model/IDisplayName.hpp>
#include <am200/model/INamespaceMember.hpp>

#include "ModelPackage.hpp"

/*PROTECTED REGION ID(Channel_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace am200
{
    namespace model
    {

    class EXPORT_AM200_MODEL_DLL Channel : public virtual ::am200::model::AbstractMemoryElement, public virtual ::am200::model::IDisplayName, public virtual ::am200::model::INamespaceMember
    {
    public:
        Channel();

        ~Channel() override;

        void _initialize() override;

        // Operations

        // Attributes
        virtual ::ecore::EInt getDefaultElements () const;
        virtual void setDefaultElements (::ecore::EInt _defaultElements);

        virtual ::ecore::EInt getMaxElements () const;
        virtual void setMaxElements (::ecore::EInt _maxElements);

        // References
        virtual ::am200::model::DataType_ptr getElementType () const;
        virtual void setElementType (::am200::model::DataType_ptr _elementType);

        virtual const ::ecorecpp::mapping::EList< ::am200::model::ChannelAccess_ptr >& getChannelAccesses () const;
        virtual ::ecorecpp::mapping::EList< ::am200::model::ChannelAccess_ptr >& getChannelAccesses ();

        /* This is the same value as getClassifierId() returns, but as a static
         * value it can be used in template expansions. */
        static const int classifierId = ModelPackage::CHANNEL;

        /*PROTECTED REGION ID(Channel) ENABLED START*/
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

        ::am200::model::DataType_ptr m_elementType;

        ::ecore::EList_ptr< ::am200::model::ChannelAccess_ptr > m_channelAccesses;

    };

}
 // model
}// am200

#endif // AM200_MODEL_CHANNEL_HPP

