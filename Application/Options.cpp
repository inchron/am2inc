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
#include "Options.h"

#include <iostream>

#include <QSettings>

#include <root/RootPackage.hpp>

#include "../gitversion.h"
#include "Converter.h"


Options::Options() {
	_parser.setApplicationDescription( "AMALTHEA to INCHRON Converter" );
	_parser.addOption( QCommandLineOption( QStringList()
#ifdef Q_OS_WIN
											   << QStringLiteral( "?" )
#endif
											   << QStringLiteral( "h" )
											   << QStringLiteral( "help" ),
										   "Displays help on commandline options." ) );

	_parser.addPositionalArgument(
		"model.amxmi",
		"If given, the AMALTHEA model is read from this file. If multiple files "
		"are specified, all of them are read as unified model." );

	_parser.addOption(
		QCommandLineOption( QStringList() << "o" << "output",
							"Write the new INCHRON project to file FILE. If FILE is '-' "
							"or this option is not specified, write to stdout.",
							"-" ) );
	_parser.addOption( QCommandLineOption(
		QStringList() << "m" << "mapping",
		"When given, a translation map is written to the named FILE.", "mapping.xmi" ) );
	_parser.addOption( QCommandLineOption( QStringList() << "Q" << "no-output",
										   "Do not write any output." ) );
	_parser.addOption( QCommandLineOption( QStringList() << "v" << "verbose",
										   "Increase verbosity level." ) );
	_parser.addOption( QCommandLineOption( QStringList() << "q" << "quiet",
										   "Set verbosity level to 0." ) );
	_parser.addOption( QCommandLineOption( QStringList() << "V" << "version",
										   "Show version information and exit." ) );
	_parser.addOption( QCommandLineOption(
		QStringList() << "pedantic",
		"Adhere strictly to the model constraints. Generates a broken output model, if "
		"the input model is not compliant." ) );
	_parser.addOption( QCommandLineOption(
		QStringList() << "no-memory-accesses",
		"Do not generate memory, interconnects, and hardware connections (ports)." ) );
	_parser.addOption( QCommandLineOption(
		QStringList() << "relax",
		"Accept input models, which do not strictly adhere to the model constraints. A "
		"post processing step tries to repair as much as possible." ) );
	_parser.addOption( QCommandLineOption(
		QStringList() << "i" << "install",
		"Install this model importer to be used with the Tool-Suite 3.x." ) );

	QCommandLineOption stable( QStringList() << "stable",
							   "Generate stable intrinsic ID in the output (default)." );
	stable.setFlags( QCommandLineOption::HiddenFromHelp );
	_parser.addOption( stable );

	_parser.addOption(
		QCommandLineOption( QStringList() << "stable-from-hash",
							"Generate stable intrinsic IDs in the output, which are "
							"derived from a hash of the input file(s)." ) );
	_parser.addOption(
		QCommandLineOption( QStringList() << "stable-from-value",
							"Generate stable intrinsic IDs in the output, which are "
							"derived from the given string.",
							"value" ) );
	_parser.addOption( QCommandLineOption(
		QStringList() << "no-stable",
		"Generate random intrinsic IDs in the output. The default is "
		"to generate stable intrinsic IDs, which are derived from a fixed value." ) );

	// Add more options here.
}


/** The CommandLineParser is configured by delegation to the default
 * constructor. Afterwards the command-line arguments of the QCoreApplication
 * are immediately processed.
 */
Options::Options( QCoreApplication& app ) : Options() {
	_parser.process( app );

	if ( _parser.isSet( "version" ) ) {
		showVersion();
	}

	if ( _parser.isSet( "help" ) )
		showHelp( Ok );

	if ( _parser.isSet( "install" ) )
		installImporter();

	auto allGivenOptions = _parser.optionNames();
	for ( const auto& optionName : allGivenOptions ) {
		if ( optionName == "v" )
			_verbosity++;
		else if ( optionName == "q" )
			_verbosity = 0;
		else if ( optionName == "pedantic" )
			_mode = Pedantic;
		else if ( optionName == "relax" )
			_mode = Relaxed;
	}

	if ( _parser.positionalArguments().count() > 0 )
		_inputNames = _parser.positionalArguments();
	else
		showHelp( CommandLine );

	if ( _parser.isSet( "no-output" ) ) {
		_noOutput = true;
	}

	if ( _parser.isSet( "no-memory-accesses" ) )
		_withMemory = false;

	if ( _parser.isSet( "output" ) ) {
		_outputName = _parser.value( "output" );
	}
	/* Verbose messages go to stderr, hence no need to switch them off if the
	 * output file is '-'. */

	if ( _parser.isSet( "mapping" ) ) {
		if ( _outputName == "-" ) {
			std::cerr << "A mapping file can only be created, if the output goes to a "
						 "file, too.\n";
			exit( CommandLine );
		}
		_mappingName = _parser.value( "mapping" );
	}

	if ( _parser.isSet( "no-stable" ) ) {
		_stable = false;

	} else if ( _parser.isSet( "stable-from-hash" ) ) {
		_stable = true;
		_stableFromHash = true;

	} else if ( _parser.isSet( "stable-from-value" ) ) {
		_stable = true;
		_stableFromValue = true;
		const auto& value = _parser.value( "stable-from-value" );
		_stableValue = value.toUtf8();
	}

	// Process more options

	/* Backward slashes need to be converted to forward slashes. */
	QStringList converted;
	for ( auto fileName : _inputNames )
		converted << fileName.replace( '\\', '/' );
	_inputNames = converted;
}

void Options::showVersion() {
	/* VERSION refers to the RELEASE number of am2inc, and usually reflects
	 * the version of the latest Amalthea model, which is supported. Minor
	 * increments may indicate features and bugfixes. */
	std::cout << "Version " << VERSION << " Build " __DATE__ " (" << GIT_VERSION << ")\n";

	std::cout << "AMALTHEA : ";
	const auto& nsURIs = Converter::getNsURIs();
	auto it = nsURIs.begin();
	std::cout << *it++;
	for ( ; it != nsURIs.end(); ++it )
		std::cout << "\n           " << *it;

	std::cout << "\nINCHRON  : " << root::RootPackage::_instance()->getNsURI() << "\n";

	/* The capabilities can be parsed by a UI tool, e.g. to control a
	 * multi-selection dialog. 'version' refers to the root.ecore version of
	 * the generated model. */
	std::cout << "\nversion: " << getRootEcoreVersion().toStdString()
			  << "\ncapabilities: +multi\n";

	::exit( Ok );
}

QString Options::getRootEcoreVersion() {
	QString nsUri = QString::fromStdString( root::RootPackage::_instance()->getNsURI() );
	int lastSlash = nsUri.lastIndexOf( '/' );
	return nsUri.mid( lastSlash + 1 );
}

void Options::showHelp( int exitCode ) {
	std::cout << _parser.helpText().toStdString();

	/* Additional multi-line text should go here as a raw string literal. See
	 * https://en.cppreference.com/w/cpp/language/string_literal */
	// 	std::cout << R"foo(
	// )foo";

	std::cout << "\nExit status:\n"
			  << "  0      if OK,\n"
			  << "  1      if errors on the command-line,\n"
			  << "  2      if serious errors, e.g. file access or translations issues.\n";

	::exit( exitCode );
}

/** Create entries in QSettings according to [SUITE3-2575].
 */
void Options::installImporter() {
	{
		/* The local scope is required because ::exit() below does not return
		 * and destructors are not executed.
		 *
		 * For history reasons the windows and the linux version registry keys
		 * resp. files for the external trace and model importers. */
#if defined( __WIN32__ ) || defined( _WIN32 )
		QSettings settings( "INCHRON", "chronsim" );
#else
		QSettings settings( "INCHRON", "ModelImporter" );
#endif
		settings.beginGroup( "ModelImporter" );
		settings.beginGroup( "AmaltheaImporter" );
		settings.setValue( "commandline", QCoreApplication::applicationFilePath() );
		settings.setValue( "arguments", "-o %t %f %F" );
		settings.setValue( "filter", "AMALTHEA Model (*.amxmi)" );
		settings.setValue( "CurrentVersion", VERSION "000" );
		settings.endGroup();
		settings.endGroup();
	}

	std::cout << "am2inc has been registered as model importer.\n";
	::exit( Ok );
}
