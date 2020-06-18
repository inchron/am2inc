/*
 * FILE: Options.cpp
 *
 * URL: $HeadURL$
 *
 */
#include "Options.h"

#include <iostream>
#include <QCommandLineParser>
#include "../gitversion.h"

#include <amalthea/model/ModelPackage.hpp>
#include <root/RootPackage.hpp>


Options::Options(QCoreApplication& app) {
    QCommandLineParser parser;
    parser.setApplicationDescription("Amalthea to INCHRON Converter");
    parser.addHelpOption();
    parser.addPositionalArgument("project", "Amalthea file to convert.");

	parser.addOption(
		QCommandLineOption(
			QStringList() << "o" << "output",
			"Write the output to file FILE. If FILE is '-' or this option "
			"is not specified, write to stdout.",
			"-"
			) );
	parser.addOption(
		QCommandLineOption(
			QStringList() << "Q" << "no-output",
			"Do not write any output."
			) );
	parser.addOption(
		QCommandLineOption(
			QStringList() << "S" << "seed",
			"Set the seed of the model.",
			"seed") );
	parser.addOption(
		QCommandLineOption(
			QStringList() << "N" << "no-seed",
			"Create a model without seed."
			) );
	parser.addOption(
		QCommandLineOption(
			QStringList() << "v" << "verbose",
			"Increase verbosity level."
			) );
	parser.addOption(
		QCommandLineOption(
			QStringList() << "V" << "version",
			"Show version information and exit."
			) );
	parser.addOption(
		QCommandLineOption(
			QStringList() << "u" << "uri",
			"Use URI fragment path instead of UUIDs for serialization."
			) );
	parser.addOption(
		QCommandLineOption(
			QStringList() << "pedantic",
			"Adhere strictly to the model constraints. Generates a broken output model, if the input model is not compliant."
			) );
	parser.addOption(
		QCommandLineOption(
			QStringList() << "relax",
			"Accept input models, which do not strictly adhere to the model constraints. A post processing step tries to repair as much as possible."
			) );
	// Add more options here.

	// Process the actual command line arguments given by the user
    parser.process(app);

	if ( parser.isSet("version") ) {
		showVersion();
		exit(0);
	}

	auto allGivenOptions = parser.optionNames();
	for ( const auto optionName : allGivenOptions ) {
		if ( optionName == "v" )
			_verbosity++;
		else if ( optionName == "pedantic" )
			_mode = Pedantic;
		else if ( optionName == "relax" )
			_mode = Relaxed;
	}

	if ( parser.positionalArguments().count() > 0 ) {
		_inputName = parser.positionalArguments().at(0);
	}

	if ( parser.positionalArguments().count() > 1 ) {
		_outputName = parser.positionalArguments().at(1);
	}

	if ( parser.isSet("no-output") ) {
		_noOutput = true;
	}

	if ( parser.isSet("output") ) {
		_outputName = parser.value("output");
	}

	if ( parser.isSet("seed") ) {
		if (parser.value("seed") == "<unknown>") {
			_seedMode = NotSeeded;
		} else {
			bool ok = false;
			RandomSeedType s = parser.value("seed").toULongLong(&ok, 0);
			if (!ok) {
				parser.showHelp(1);
			} else {
				_seedMode = Seeded;
				_seed = s;
			}
		}
	}

	if ( parser.isSet("no-seed") ) {
		_seedMode = NotSeeded;
	}

	if ( parser.isSet("uri") ) {
		_useURI = true;
	}

	// Store more options
}


bool Options::noOutput() const {
	return _noOutput;
}

bool Options::useURI() const {
	return _useURI;
}

QString Options::getInputName() const {
	return _inputName;
}

QString Options::getOutputName() const {
	return _outputName;
}




void Options::showVersion() {
	std::cout << "Version " << VERSION << " Build " __DATE__ " ("
			  << GIT_VERSION << ")\n";

	std::cout <<   "Amalthea : " << amalthea::model::ModelPackage::_instance()->getNsURI()
			  << "\nINCHRON  : " << root::RootPackage::_instance()->getNsURI()
			  << "\n";
}
