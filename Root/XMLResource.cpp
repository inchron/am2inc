/* -*- c++ -*-
 *
 * Root/XMLResource.h
 *
 * Copyright (c) 2024 INCHRON AG <info@inchron.com>
 */
#include "XMLResource.h"

#include <ecorecpp/resource/Compression.hpp>

namespace root {

XMLResource::XMLResource( const ProtectedTag&, const QUrl& url )
	: ecorecpp::resource::XMLResource( url ) {}

ecorecpp::resource::XMLResource::Buffer XMLResource::doCompress( const Buffer& input ) {
	return ecorecpp::resource::Compression::doCompress( input );
}

ecorecpp::resource::XMLResource::Buffer XMLResource::doUncompress( const Buffer& input ) {
	return ecorecpp::resource::Compression::doUncompress( input );
}

}  // namespace root
