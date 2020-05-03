/* -*- c++ -*-
 *
 * Application.h
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#pragma once

#include <memory>

#include <QCoreApplication>
#include <ecorecpp/resource/ResourceSet.hpp>

#include <Projects/Project.h>

#include <amalthea/model_forward.hpp>
#include <am2inc_forward.hpp>
#include <root_forward.hpp>
#include <root/model_forward.hpp>

#include "Converter.h"
#include "Options.h"

class Application : public QCoreApplication {
	Q_OBJECT
public:
	Application(int& argc, char** argv);
	~Application() override;

public slots:
	void start();

protected slots:
	bool readInput();
	bool convert();
	bool relax();
	bool writeOutput();

protected:
	void error(Options::Status, const char* = nullptr);
	void warning(const char*);
	void info(unsigned int verbosity, const QString& msg);

	std::string readStdIn();

private:
	std::shared_ptr<Options> _options;
	ecore::Ptr<ecorecpp::resource::ResourceSet> _resourceSet;

	amalthea::model::Amalthea_ptr _amalthea;
	am2inc::Mappings_ptr _mappings;
	ecore::Ptr<Projects::Project> _project;
	Converter _converter;
};
