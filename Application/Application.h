/* -*- c++ -*-
 *
 * Copyright (c) 2020-2021 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#pragma once

#include <memory>

#include <QCoreApplication>

#include <ecorecpp/resource/ResourceSet.hpp>

#include <am120/model_forward.hpp>
#include <root/model_forward.hpp>

#include "Converter.h"
#include "Options.h"

class Application : public QCoreApplication {
	Q_OBJECT

public:
	Application( int& argc, char** argv );
	~Application() override;

public slots:
	void start();

protected slots:
	bool readInput();
	bool convert();
	bool relax();
	bool writeOutput();

protected:
	void error( Options::Status, const QString& );
	void warning( const QString& );
	void info( unsigned int verbosity, const QString& msg );

	std::string readStdIn();

private:
	std::shared_ptr<Options> _options;
	ecore::Ptr<ecorecpp::resource::ResourceSet> _resourceSet;

	am2inc::Mappings_ptr _mappings;
	ecore::Ptr<root::Root> _root;
	std::unique_ptr<Converter> _converter;
};
