/* -*- c++ -*-
 *
 * Root/XMLResource.h
 *
 * Copyright (c) 2024 INCHRON AG <info@inchron.com>
 */
#pragma once

#include <ecorecpp/resource/XMLResource.hpp>

#include "model/root/dllRoot.hpp"

namespace root {

class XMLResource : public ecorecpp::resource::XMLResource {
protected:
	/** This empty struct is used to limit the callability (!= visibility) of
	 * the constructor to methods of this and derived classes. This is needed
	 * to enforce std::shared_ptr<>-managed instances [SUITE3-1135].
	 */
	struct ProtectedTag {};

public:
	/** This is the official way to create an instance of this class. */
	static ::ecore::Ptr<XMLResource> create( const QUrl& url ) {
		return std::make_shared<XMLResource>( ProtectedTag(), url );
	}

	explicit XMLResource( const ProtectedTag&, const QUrl& );

protected:
	Buffer doCompress( const Buffer& ) override;
	Buffer doUncompress( const Buffer& ) override;
};

}  // namespace root
