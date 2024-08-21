/* -*- c++ -*-
 *
 * Amalthea/XMLResource.h
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 */
#pragma once

#include <ecorecpp/parser/XMLHandler.hpp>
#include <ecorecpp/resource/XMLResource.hpp>

#include "dllAmalthea.h"

namespace amalthea {

/** Load a model which is split over multiple files.
 *
 * Amalthea models can be distributed over multiple files. Contrary to
 * cross-document containments they use separate trees, which form a
 * forest. Each tree starts with an Amalthea object as top-level node.
 *
 * Such structures can be expressed as multiple ecore::Resources within an
 * ecore::ResourceSet. Unfortunately all cross-document references in the
 * split files use all the same URI to reference objects in other files
 * ("amlt:/#"). This makes it difficult, if not impossible for the ResourceSet
 * to refer to the right Resource.
 *
 * Hence a split model is managed by a specialized XMLResource, which
 * maintains a list of XML documents (identified by URIs). The content these
 * documents is loaded into the getContents() list, where each entry
 * correlates to an entry in the document list.
 */
class EXPORT_AMALTHEA_DLL XMLResource : public ecorecpp::resource::XMLResource {
protected:
	/** This empty struct is used to limit the callability (!= visibility) of
	 * the constructor to methods of this and derived classes. This is needed
	 * to enforce std::shared_ptr<>-managed instances [SUITE3-1135].
	 */
	struct ProtectedTag {};

public:
	using URIList = std::vector<QUrl>;

	/** This is the official way to create an instance of this class. */
	static ::ecore::Ptr<XMLResource> create( const URIList& uris ) {
		return std::make_shared<XMLResource>( ProtectedTag(), uris );
	}

	explicit XMLResource( const ProtectedTag&, const URIList& );
	~XMLResource() override;

	const URIList& getURIList() const { return _uriList; }

	using ecorecpp::resource::XMLResource::load;
	void load( const Resource::OptionMap& ) override;

protected:
	void doLoad( const Resource::OptionMap& );
	void doLoad( ecorecpp::parser::XMLHandler*,
				 const std::vector<::ecorecpp::mapping::type_definitions::char_t>&,
				 const Resource::OptionMap& );

	Buffer doCompress( const Buffer& ) override;
	Buffer doUncompress( const Buffer& ) override;

	URIList _uriList;
};

}  // namespace amalthea
