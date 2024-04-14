/* -*- c++ -*-
 *
 * File: XMLResourceFactory.h
 *
 * Copyright 2018 INCHRON GmbH <info@inchron.com>
 */
#include "XMLResourceFactory.h"

#include "XMLResource.h"

namespace root {

XMLResourceFactory::XMLResourceFactory() = default;

XMLResourceFactory::~XMLResourceFactory() = default;

ecorecpp::resource::Resource_ptr XMLResourceFactory::createResource( const QUrl& uri ) {
	auto retValue = XMLResource::create( uri );
	return retValue;
}

}  // namespace root
