/*
 * FILE: Options.cpp
 *
 * URL: $HeadURL$
 *
 */
#include "Options.h"

#include <iostream>

#include <amalthea/model/ModelPackage.hpp>
#include <root/RootPackage.hpp>

#include "../gitversion.h"


Options::Options() {
    _parser.setApplicationDescription("Amalthea to INCHRON Converter");
    _parser.addOption(
		QCommandLineOption(
			QStringList()
#ifdef Q_OS_WIN
			<< QStringLiteral("?")
#endif
			<< QStringLiteral("h")
			<< QStringLiteral("help"),
			"Displays help on commandline options."));

	_parser.addPositionalArgument("model.amxmi", "If given, the Amalthea model is read from this file, otherwise it is read from stdin.");

	_parser.addOption(
		QCommandLineOption(
			QStringList() << "o" << "output",
			"Write the new INCHRON project to file FILE. If FILE is '-' or this option is not specified, write to stdout.",
			"-"
			) );
	_parser.addOption(
		QCommandLineOption(
			QStringList() << "m" << "mapping",
			"When given, a translation map is written to the named FILE.",
			"mapping.xmi"
			) );
	_parser.addOption(
		QCommandLineOption(
			QStringList() << "Q" << "no-output",
			"Do not write any output."
			) );
	_parser.addOption(
		QCommandLineOption(
			QStringList() << "v" << "verbose",
			"Increase verbosity level."
			) );
	_parser.addOption(
		QCommandLineOption(
			QStringList() << "V" << "version",
			"Show version information and exit."
			) );
	_parser.addOption(
		QCommandLineOption(
			QStringList() << "pedantic",
			"Adhere strictly to the model constraints. Generates a broken output model, if the input model is not compliant."
			) );
	_parser.addOption(
		QCommandLineOption(
			QStringList() << "relax",
			"Accept input models, which do not strictly adhere to the model constraints. A post processing step tries to repair as much as possible."
			) );

	// Add more options here.
}


/** The CommandLineParser is configured by delegation to the default
 * constructor. Afterwards the command-line arguments of the QCoreApplication
 * are immediately processed.
 */
Options::Options(QCoreApplication& app) : Options() {
    _parser.process(app);

	if ( _parser.isSet("version") ) {
		showVersion();
	}

	if ( _parser.isSet("help") )
		showHelp(Ok);

	auto allGivenOptions = _parser.optionNames();
	for ( const auto optionName : allGivenOptions ) {
		if ( optionName == "v" )
			_verbosity++;
		else if ( optionName == "pedantic" )
			_mode = Pedantic;
		else if ( optionName == "relax" )
			_mode = Relaxed;
	}

	if ( _parser.positionalArguments().count() > 0 ) {
		_inputName = _parser.positionalArguments().at(0);
	}

	if ( _parser.isSet("no-output") ) {
		_noOutput = true;
	}

	if ( _parser.isSet("output") ) {
		_outputName = _parser.value("output");
	}
	/* Verbose messages go to stderr, hence no need to switch if off if the
	 * output file is '-'. */

	if ( _parser.isSet("mapping") ) {
		if (_outputName == "-") {
			std::cerr << "A mapping file can only be created, if the output goes to a file, too.\n";
			exit(CommandLine);
		}
		_mappingName = _parser.value("mapping");
	}

	// Process more options
}

void Options::showVersion() {
	std::cout << "Version " << VERSION << " Build " __DATE__ " ("
			  << GIT_VERSION << ")\n";

	std::cout <<   "Amalthea : " << amalthea::model::ModelPackage::_instance()->getNsURI()
			  << "\nINCHRON  : " << root::RootPackage::_instance()->getNsURI()
			  << "\n";
	::exit(Ok);
}

void Options::showHelp(int exitCode) {
	std::cout << _parser.helpText().toStdString();

	/* Additional multi-line text should go here as a raw string literal. See
	 * https://en.cppreference.com/w/cpp/language/string_literal */
// 	std::cout << R"foo(
// )foo";

	std::cout << "\nExit status:\n"
			  <<   "  0      if OK,\n"
			  <<   "  1      if errors on the command-line,\n"
			  <<   "  2      if serious errors, e.g. file access or translations issues.\n";

	::exit(exitCode);
}
