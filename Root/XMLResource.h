/* -*- c++ -*-
*
 * File: XMLResource.h
 *
 * Copyright 2018 INCHRON GmbH <info@inchron.com>
 */
#ifndef Root_XMLResource_H
#define Root_XMLResource_H

#include <ecorecpp/resource/XMLResource.hpp>
#include "model/root/dllRoot.hpp"

namespace root {

/** The specialization of an ecorecpp::resource::XMLResource which uses
 * xpath-like references with ModelObject::getName() instead of the container
 * index.
 *
 * Xpath references use the container name and an index position within
 * this container. Named uids use the name of the object instead of the
 * index. This results in a uid like this one:
 * "//@root/@model/@cpus.NewCpu/@cores.CpuCore"
 *
 * The name of the objects is used from
 * root::model::ModelObject::getName(). If the eObject is not a
 * ModelObject, the multiplicity of the container must be 0..1 and no name
 * is used (or needed). Otherwise an exception is thrown.
 *
 * Usage:
 \code{.cpp}
ecore::Ptr<Resource> input = ResourceSet::getInstance().createResource(file);
Resource::OptionMap options;
options.insert(std::make_pair(XMLResource::OPTION_USE_NAMED_UIDS, "true"));

input->load(istream, options);
	 \endcode
 *
 */
class EXPORT_ROOT_DLL XMLResource : public ecorecpp::resource::XMLResource {
protected:
	/** This empty struct is used to limit the callability (!= visibility) of
	 * the constructor to methods of this and derived classes. This is needed
	 * to enforce std::shared_ptr<>-managed instances [SUITE3-1135].
	 */
	struct ProtectedTag { };

public:
	/** This is the official way to create an instance of this class. */
	static ::ecore::Ptr<XMLResource> create(const QUrl& url) {
		return std::make_shared<XMLResource>(ProtectedTag(), url);
	}

	explicit XMLResource(const ProtectedTag&, const QUrl&);
	~XMLResource() override;

	using ::ecorecpp::resource::Resource::load;
	void load(std::istream&,
			const Resource::OptionMap& = Resource::OptionMap()) override;
	using ::ecorecpp::resource::Resource::save;
	void save(std::ostream&,
			const Resource::OptionMap& = Resource::OptionMap()) override;

	::ecore::EObject_ptr getEObject(const std::string& uriFragment) override;
	std::string getURIFragment(::ecore::EObject_ptr) override;

private:
	::ecore::EObject_ptr _getEObject(const std::string& uriFragment);
	std::string _getURIFragment(::ecore::EObject_ptr);
};

} // namespace root

#endif // ifndef Root_XMLResource_H
