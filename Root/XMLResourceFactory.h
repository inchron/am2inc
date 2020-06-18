/* -*- c++ -*-
 *
 * File: XMLResourceFactory.h
 *
 * Copyright 2018 INCHRON GmbH <info@inchron.com>
 */
#ifndef Root_XMLResourceFactory_H
#define Root_XMLResourceFactory_H

#include <ecorecpp/resource/XMLResource.hpp>
#include "model/root/dllRoot.hpp"


namespace root {

class EXPORT_ROOT_DLL XMLResourceFactory : public ecorecpp::resource::Resource::Factory {
public:
	XMLResourceFactory();
	~XMLResourceFactory() override;

	ecorecpp::resource::Resource_ptr createResource(const QUrl&) override;
};

} // namespace root

#endif // ifndef Root_XMLResourceFactory_H
