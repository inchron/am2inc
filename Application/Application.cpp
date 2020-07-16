/* -*- c++ -*-
 *
 * Application.cpp
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#include "Application.h"

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <QString>

#include <ecorecpp.hpp>
#include <ecorecpp/resource/XMLResource.hpp>

#include <amalthea/model.hpp>
#include <amalthea/model/ModelPackage.hpp>
#include <root.hpp>
#include <root/RootPackage.hpp>

#include "Converter.h"

namespace am   = amalthea::model;
namespace sm3  = root::model;
namespace sm3m = root::model::memory;


Application::Application(int &argc, char **argv)
	: QCoreApplication(argc, argv),
	  _options(std::make_shared<Options>(*this)),
	  _resourceSet(ecore::make<ecorecpp::resource::ResourceSet>()) {
	_resourceSet->getResourceFactoryRegistry()
		->getProtocolToFactoryMap()[ "file" ].reset(
			new ecorecpp::resource::XMLResourceFactory() );

	/* Disable required minimum number of CpuCores in this application. */
	auto sm3Pkg = sm3::ModelPackage::_instance();
	sm3Pkg->getCpu__cores()->setLowerBound(0);
	sm3Pkg->getCpuCore__connectedSlave()->setLowerBound(0);
	sm3Pkg->getModeCondition__conjunctions()->setLowerBound(0);

	auto memPkg = sm3m::MemoryPackage::_instance();
	memPkg->getMemory__connectedMaster()->setLowerBound(0);
	memPkg->getCacheMemory__connectedSlave()->setLowerBound(0);
	memPkg->getInterconnect__connectedMasters()->setLowerBound(0);
	memPkg->getInterconnect__connectedSlaves()->setLowerBound(0);
}

Application::~Application() = default;

void Application::start() {
	try {
		if (readInput())
			return;
		if (convert())
			return;
		if (_options->getMode() == Options::Relaxed) {
			if (relax())
				return;
		}
		if (writeOutput())
			return;
	} catch (std::exception& e) {
		error(Options::Trouble,
			  QStringLiteral("Aborting due to exception: %1")
			  .arg(QString::fromStdString(e.what())));
		return;
	} catch (const char* msg) {
		error(Options::Trouble,
			  QStringLiteral("Aborting due to exception: %1").arg(msg));
		return;
	} catch (...) {
		error(Options::Trouble,
			  QStringLiteral("Aborting due to unknown exception"));
		return;
	}

	error(Options::Ok, QString::null);
}

void Application::error(Options::Status error, const QString& msg) {
	if (error != Options::Ok) {
		if (!msg.isEmpty())
			info(0, QStringLiteral("Terminating with error %1").arg(msg));
		else
			info(0, QStringLiteral("Terminating with error"));
	} else
		info(0, QStringLiteral("Successful translation."));
	QCoreApplication::exit(error);
}

void Application::warning(const QString& msg) {
	info(1, QStringLiteral("Warning: %1").arg(msg));
}

/** Emit an informational message depending on the verbosity level.
 *
 * A verbosity of 1 is the default. If option -q/--quiet is used, only
 * messages with a verbosity level of 0 will be emitted.
 */
void Application::info(unsigned int verbosity, const QString& msg) {
	if (verbosity <= _options->verbosity())
		std::cerr << QCoreApplication::applicationName().toStdString()
				  << " " << msg.toStdString() << "\n";
}

std::string Application::readStdIn() {
	const int ReadBufferSize = 1024;
	char readBuffer[ReadBufferSize+1];
	std::string xmi;

	while (1) {
		auto bytesRead = read(0, readBuffer, ReadBufferSize);
		if (bytesRead <= 0)
			break;
		readBuffer[bytesRead] = '\0';
		xmi += readBuffer;
	}

	return xmi;
}

bool Application::readInput() {
	QUrl file = QUrl::fromLocalFile(_options->getInputName());

	ecorecpp::resource::Resource_ptr input = ecore::make<ecorecpp::resource::XMLResource>(file);
	input->setResourceSet(_resourceSet.get());
	_resourceSet->getResources().push_back(input);

	try {
		if (!_options->getInputName().isEmpty() && _options->getInputName() != "-")
			input->load();
		else {
			std::string xmi = readStdIn();
			std::istringstream istream(xmi);
			input->load(istream);
		}
	} catch (const std::logic_error& error) {
		std::cerr << "[am2inc] Exiting, parser failed (const std::logic_error&)\n";
		std::cerr << "[am2inc] error: " << error.what() << "\n";
		exit(1);
		return true;

	} catch (const char* error) {
		std::cerr << "[am2inc] Exiting, parser failed (const char*)\n";
		std::cerr << "[am2inc] error: " << error << "\n";
		exit(1);
		return true;
	}

	_amalthea = ecore::as<am::Amalthea>(input->getContents()->get(0));
	if (!_amalthea) {
		error(Options::Trouble, "no Amalthea model");
		return true;
	}

	_amalthea->_initialize();
	return false;
}

bool Application::convert() {
#if 0
	try {
		std::cerr << "amalthea: @" << (void*)_amalthea.get() << "\n";
		auto swModel = ecore::as<am::SWModel>(_amalthea->getSwModel());
		std::cerr << "  swModel: @" << (void*)swModel.get() << "\n";

		for (auto task : swModel->getTasks())
			std::cerr << "    task: @" << (void*)task.get()
					  << " uniqueName " << task->getUniqueName()
					  << "\n";

		for (auto runnable : swModel->getRunnables())
			std::cerr << "    runnable: @" << (void*)runnable.get()
					  << " uniqueName " << runnable->getUniqueName()
					  << "\n";
	} catch (const char* error) {
		std::cerr << "\n\n### Exception: " << error << " ###\n";
		exit(1);
		return true;
	}

#else

	_converter.convert(_amalthea);
	_mappings = _converter.getMappings();
	_root = _converter.getRoot();
#endif
	return false;
}

bool Application::relax() {
	_converter.relax();
	return false;
}

bool Application::writeOutput() {
	_converter.clear();
	if (_options->noOutput()) {
		info(1, QStringLiteral("Writing no output as requested"));
		return false;
	}

	auto projectUrl = QUrl::fromLocalFile(_options->getOutputName());
	info(1, QStringLiteral("Writing output to %1").arg(projectUrl.toLocalFile()));
	auto rootXmi = _resourceSet->createResource(projectUrl);
	rootXmi->getContents()->push_back(_root);

	if (!_options->getOutputName().isEmpty() && _options->getOutputName() != "-") {
		rootXmi->save();
	} else {
		std::ostringstream stream;
		rootXmi->save(stream);
		std::cout << stream.str();
	}

	if (!_options->getMappingName().isEmpty()) {
		auto mappingXmi = _resourceSet->createResource(
			QUrl::fromLocalFile(_options->getMappingName()));
		mappingXmi->getContents()->push_back(_mappings);
		mappingXmi->save();
	}

	return false;
}
