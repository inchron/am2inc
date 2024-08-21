/* -*- c++ -*-
 *
 * Amalthea/AmaltheaXMLResource.cpp
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 */
#include "XMLResource.h"

#include <ecorecpp/parser/simple_xml_parser.hpp>
#include <ecorecpp/resource/Compression.hpp>
#include <ecorecpp/resource/URIConverter.hpp>

namespace amalthea {

namespace {

const std::streamsize s_minimumAmxmlLength = []() {
	return (signed)strlen( "<am:Amalthea xmi:version=\"2.0\"" );
}();

}  // namespace

/** The URI of the baseclass is initialized with the base URI of all split
 * files, which is "amlt:/".
 */
XMLResource::XMLResource( const ProtectedTag&, const URIList& uriList )
	: ecorecpp::resource::XMLResource( QUrl( "amlt:/" ) ), _uriList( uriList ) {}

XMLResource::~XMLResource() = default;


void XMLResource::load( const Resource::OptionMap& options ) { doLoad( options ); }

void XMLResource::doLoad( const Resource::OptionMap& options ) {
	std::vector<std::unique_ptr<ecorecpp::parser::XMLHandler>> _allHandlers;

	for ( auto&& uri : _uriList ) {
		auto is = getURIConverter()->createInputStream( uri );
		if ( !is )
			throw std::logic_error( "Input stream not readable" );

		// get length of file:
		is->seekg( 0, is->end );
		std::streamsize length = is->tellg();
		if ( length <= s_minimumAmxmlLength )
			throw std::logic_error( "Input stream does not contain useful amxmi" );

		// allocate memory:
		std::vector<::ecorecpp::mapping::type_definitions::char_t> buffer( length );

		// read data as a block:
		is->seekg( 0, is->beg );
		is->read( buffer.data(), length );

		// The file is read in text mode. If it contains \r\n line
		// endings, the number of bytes read can be smaller than the
		// file size calculated by seekg().
		length = is->gcount();
		buffer.resize( length );

		/* Decompression is done automatically by checking magic numbers.
		 * https://en.wikipedia.org/wiki/List_of_file_signatures -> "50 4B" */
		if ( buffer[0] == 0x50 and buffer[1] == 0x4b ) {
			/* There are two more variants, but we only support non-empty, contiguous archives. */
			if ( buffer[2] == 0x03 and buffer[3] == 0x04 ) {
				buffer = doUncompress( buffer );
			}
		}

		auto handler = new ecorecpp::parser::XMLHandler;
		_allHandlers.push_back(
			std::unique_ptr<ecorecpp::parser::XMLHandler>( handler ) );
		doLoad( handler, buffer, options );
	}

	/* Now the model knows its resource and we can try to resolve
	 * the (cross-document) references, too.
	 */
	for ( auto&& handler : _allHandlers )
		handler->resolveReferences();

	for ( auto&& handler : _allHandlers )
		handler->resolveCrossDocumentReferences();

	/* The XMLHandlers are no longer needed and will be deleted. */
}

void XMLResource::doLoad(
	ecorecpp::parser::XMLHandler* handler,
	const std::vector<::ecorecpp::mapping::type_definitions::char_t>& buffer,
	const Resource::OptionMap& options ) {
	bool extendedMetaData = false;
	if ( options.count( OPTION_EXTENDED_META_DATA ) ) {
		std::string emdStr = options.at( OPTION_EXTENDED_META_DATA );
		std::transform( emdStr.begin(), emdStr.end(), emdStr.begin(),
						[]( unsigned char c ) { return std::tolower( c ); } );
		extendedMetaData = ( emdStr != "false" );
	}
	handler->setExtendedMetaData( extendedMetaData );

	using namespace ecorecpp;
	xml_parser::SemanticState<XMLHandler> ss( *handler );

	State<xml_parser::SemanticState<XMLHandler>> st( ss, buffer.data(), buffer.size() );

	/*
	 * Get the starting time and kick off the parse of the indicated
	 * file. Catch any exceptions that might propogate out of it.
	 */
	xml_parser::grammar::the_xml::match( st );

	/* This only resolves non-containment references that are not
	 * cross-document.
	 */
	for ( const auto& root : handler->getRootElements() ) {
		root->_initialize();
		getContents()->push_back( root );
	}

	/* Insert all (id, eobject) mappings into the translation maps of this
	 * XMLResource. */
	const auto& xmiIds = handler->getXmiIds();
	for ( auto&& entry : xmiIds )
		setID( entry.second, entry.first );
}

ecorecpp::resource::XMLResource::Buffer XMLResource::doCompress( const Buffer& input ) {
	return ecorecpp::resource::Compression::doCompress( input );
}

ecorecpp::resource::XMLResource::Buffer XMLResource::doUncompress( const Buffer& input ) {
	return ecorecpp::resource::Compression::doUncompress( input );
}

}  // namespace amalthea
