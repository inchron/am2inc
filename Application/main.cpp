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
#include <memory>

#include <QCoreApplication>
#include <QThread>
#include <QTimer>

#include <ecorecpp/MetaModelRepository.hpp>

#include <am120/model/ModelPackage.hpp>
#include <am200/model/ModelPackage.hpp>
#include <am2inc/Am2incPackage.hpp>
#include <root/RootPackage.hpp>

#include "Application.h"
#include "EcoreModelChecker.h"

void loadPackages( ::ecorecpp::MetaModelRepository_ptr mmr,
				   ::ecore::EPackage_ptr package ) {
	mmr->load( package );
	for ( auto subPackage : package->getESubpackages() )
		loadPackages( mmr, subPackage );
}


int main( int argc, char* argv[] ) {
	QCoreApplication::setOrganizationName( "INCHRON" );
	QCoreApplication::setOrganizationDomain( "inchron.com" );
	QCoreApplication::setApplicationName( "am2inc" );
	QCoreApplication::setApplicationVersion( VERSION );

	QThread::currentThread()->setObjectName(
		QString( "%1/main" ).arg( QCoreApplication::applicationName() ) );
	qSetMessagePattern( "%{file}:%{line} %{function}: %{message}" );  // SUITE3-314

	auto mmr = ecorecpp::MetaModelRepository::_instance();
	loadPackages( mmr, am120::model::ModelPackage::_instance() );
	loadPackages( mmr, am200::model::ModelPackage::_instance() );
	loadPackages( mmr, am2inc::Am2incPackage::_instance() );
	loadPackages( mmr, root::RootPackage::_instance() );
	EcoreModelChecker::setToplevelPackage( root::RootPackage::_instance() );

	/* Read commandline options after initializing all ecore packages, so that
	 * Options::showVersion() can use them. */
	Application a( argc, argv );

	QTimer::singleShot( 0, &a, SLOT( start() ) );

	return a.exec();
}
