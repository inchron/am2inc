/* -*- c++ -*-
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#include "Application.h"

#include <iostream>
#include <memory>
#include <unistd.h>

#include <QFile>
#include <QString>

#include <ecorecpp.hpp>
#include <ecorecpp/resource/URIConverter.hpp>
#include <ecorecpp/resource/XMLResource.hpp>

#include <Amalthea/XMLResource.h>

#include "Converter.h"
#include "StableIntrinsicIds.h"

namespace sm3 = root::model;
namespace sm3m = root::model::memory;


Application::Application( int& argc, char** argv )
	: QCoreApplication( argc, argv ), _options( std::make_shared<Options>( *this ) ),
	  _resourceSet( ecore::make<ecorecpp::resource::ResourceSet>() ),
	  _hash( QCryptographicHash::Sha3_512 ) {
	auto& map = _resourceSet->getResourceFactoryRegistry()->getProtocolToFactoryMap();
	map["file"] = std::make_unique<ecorecpp::resource::XMLResourceFactory>();
	map["inchron"] = std::make_unique<ecorecpp::resource::XMLResourceFactory>();

	/* Disable required minimum number of CpuCores in this application. */
	auto sm3Pkg = sm3::ModelPackage::_instance();
	sm3Pkg->getCpu__cores()->setLowerBound( 0 );
	sm3Pkg->getCpuCore__initiator()->setLowerBound( 0 );
	sm3Pkg->getCondition__conjunctions()->setLowerBound( 0 );

	auto memPkg = sm3m::MemoryPackage::_instance();
	memPkg->getMemory__responder()->setLowerBound( 0 );
	memPkg->getCacheMemory__initiator()->setLowerBound( 0 );
	memPkg->getInterconnect__responders()->setLowerBound( 0 );
	memPkg->getInterconnect__initiators()->setLowerBound( 0 );
}

Application::~Application() = default;

void Application::start() {
	try {
		if ( readInput() )
			return;
		if ( convert() )
			return;
		if ( _options->getMode() == Options::Relaxed ) {
			if ( relax() )
				return;
		}
		if ( writeOutput() )
			return;
	} catch ( std::exception& e ) {
		error( Options::Trouble, QStringLiteral( "Aborting due to exception: %1" )
									 .arg( QString::fromStdString( e.what() ) ) );
		return;
	} catch ( const char* msg ) {
		error( Options::Trouble,
			   QStringLiteral( "Aborting due to exception: %1" ).arg( msg ) );
		return;
	} catch ( ... ) {
		error( Options::Trouble, QStringLiteral( "Aborting due to unknown exception" ) );
		return;
	}

	error( Options::Ok, QString() );
}

void Application::error( Options::Status error, const QString& msg ) {
	if ( error != Options::Ok ) {
		if ( !msg.isEmpty() )
			info( 0, QStringLiteral( "Terminating with error %1" ).arg( msg ) );
		else
			info( 0, QStringLiteral( "Terminating with error" ) );
	} else
		info( 0, QStringLiteral( "Successful translation." ) );
	QCoreApplication::exit( error );
}

void Application::warning( const QString& msg ) {
	info( 1, QStringLiteral( "Warning: %1" ).arg( msg ) );
}

/** Emit an informational message depending on the verbosity level.
 *
 * A verbosity of 1 is the default. If option -q/--quiet is used, only
 * messages with a verbosity level of 0 will be emitted.
 */
void Application::info( unsigned int verbosity, const QString& msg ) {
	if ( verbosity <= _options->verbosity() )
		std::cerr << QCoreApplication::applicationName().toStdString() << " "
				  << msg.toStdString() << "\n";
}

std::string Application::readStdIn() {
	const int ReadBufferSize = 1024;
	char readBuffer[ReadBufferSize + 1];
	std::string xmi;

	while ( 1 ) {
		auto bytesRead = read( 0, readBuffer, ReadBufferSize );
		if ( bytesRead <= 0 )
			break;
		readBuffer[bytesRead] = '\0';
		xmi += readBuffer;
	}

	return xmi;
}

bool Application::readInput() {
	amalthea::XMLResource::URIList _allUris;
	for ( auto&& fileName : _options->getInputNames() )
		_allUris.push_back( QUrl::fromLocalFile( fileName ) );

	auto input = amalthea::XMLResource::create( _allUris );
	input->setResourceSet( _resourceSet.get() );
	_resourceSet->getResources().push_back( input );

	try {
		input->load();

	} catch ( const std::logic_error& error ) {
		std::cerr << "[am2inc] Exiting, parser failed (const std::logic_error&)\n";
		std::cerr << "[am2inc] error: " << error.what() << "\n";
		exit( 1 );
		return true;

	} catch ( const char* error ) {
		std::cerr << "[am2inc] Exiting, parser failed (const char*)\n";
		std::cerr << "[am2inc] error: " << error << "\n";
		exit( 1 );
		return true;
	}

	/* When all files have been read without an error, they are added to a
	 * hash sum, from which stable intrinsic IDs can be derived. */
	if ( _options->isStableIntrinsicIdFromHash() )
		for ( auto&& fileName : _options->getInputNames() ) {
			QFile file( fileName );
			if ( file.open( QIODevice::ReadOnly ) )
				_hash.addData( &file );
		}

	return false;
}

bool Application::convert() {
	/* Actually there is only one Resource. */
	for ( auto&& resource : _resourceSet->getResources() )
		for ( auto&& content : *resource->getContents() ) {
			if ( not _converter )
				_converter = Converter::create( content );
			_converter->convert( content );
		}

	_mappings = _converter->getMappings();
	_root = _converter->getRoot();

	return false;
}

bool Application::relax() {
	_converter->relax();
	return false;
}

bool Application::writeOutput() {
	_converter->clear();
	if ( _options->noOutput() ) {
		info( 1, QStringLiteral( "Writing no output as requested" ) );
		return false;
	}

	if ( _options->isStableIntrinsicId() ) {
		StableIntrinsicIds stabilizer;
		if ( _options->isStableIntrinsicIdFromHash() ) {
			stabilizer.resetBase( _hash.result() );
		} else if ( _options->isStableIntrinsicIdFromValue() ) {
			stabilizer.resetBase( _options->getStableIntrinsicIdValue() );
		}

		stabilizer.stabilize( _root->getModel() );
	}

	const std::string toplevelUri = "inchron://root";

	auto projectUrl = QUrl::fromLocalFile( _options->getOutputName() );
	info( 1, QStringLiteral( "Writing output to %1" ).arg( projectUrl.toLocalFile() ) );
	_resourceSet->getURIConverter()->getURIMap()[toplevelUri] =
		projectUrl.adjusted( QUrl::RemoveQuery | QUrl::RemoveFragment )
			.toString()
			.toStdString();
	auto rootXmi =
		_resourceSet->createResource( QUrl( QString::fromStdString( toplevelUri ) ) );
	rootXmi->getContents()->push_back( _root );

	if ( !_options->getOutputName().isEmpty() && _options->getOutputName() != "-" ) {
		rootXmi->save();
	} else {
		std::ostringstream stream;
		rootXmi->save( stream );
		std::cout << stream.str();
	}

	if ( !_options->getMappingName().isEmpty() ) {
		auto mappingXmi = _resourceSet->createResource(
			QUrl::fromLocalFile( _options->getMappingName() ) );
		mappingXmi->getContents()->push_back( _mappings );
		mappingXmi->save();
	}

	return false;
}
