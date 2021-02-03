// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * am2inc_forward.hpp
 * This file was created by EMF4CPP 3.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef _AM2INC_FORWARD_HPP
#define _AM2INC_FORWARD_HPP

#include <ecore_forward.hpp> // for EDataTypes

/*PROTECTED REGION ID(am2inc_forward) ENABLED START*/
namespace amalthea
{
    namespace model
    {
    }
}

namespace model = amalthea::model;
/*PROTECTED REGION END*/

// EPackage

namespace am2inc
{

// EDataType

// EClass

// Mappings
    class Mappings;
    using Mappings_ptr = ::ecore::Ptr<Mappings>;

// Mapping
    class Mapping;
    using Mapping_ptr = ::ecore::Ptr<Mapping>;

// EEnum

// Package & Factory
    class Am2incFactory;
    using Am2incFactory_ptr = ::ecore::Ptr<Am2incFactory>;
    class Am2incPackage;
    using Am2incPackage_ptr = ::ecore::Ptr<Am2incPackage>;

} // am2inc

#endif // _AM2INC_FORWARD_HPP

