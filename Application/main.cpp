/* -*- c++ -*-
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#include <memory>

#include <QCoreApplication>
#include <QThread>
#include <QTimer>

#include <Basics/Crash.h>
#include <Projects/Project.h>
#include <ReleaseInfo/ReleaseInfo.h>
#include <Utils/EmfPackageLoader.h>

#include <am2inc/Am2incPackage.hpp>
#include <amalthea/model/ModelPackage.hpp>
#include <root/RootPackage.hpp>

#include "Application.h"
#include "EcoreModelChecker.h"
#include "Options.h"


int main(int argc, char* argv[]) {
	QCoreApplication::setOrganizationName("INCHRON");
    QCoreApplication::setOrganizationDomain("inchron.com");
    QCoreApplication::setApplicationName("am2inc");
	QCoreApplication::setApplicationVersion(ReleaseInfo::ReleaseInfo().getVersionString());

    Crash::setHandler();
    Crash::setName(argv[0]);
    Crash::setPath(argv[0]);
    Crash::setType( Crash::Tty );

	QThread::currentThread()->setObjectName(
		QString("%1/main").arg(QCoreApplication::applicationName()) );
	qSetMessagePattern("%{file}:%{line} %{function}: %{message}");	// SUITE3-314

	Utils::EmfPackageLoader().load( amalthea::model::ModelPackage::_instance() );
	Utils::EmfPackageLoader().load( am2inc::Am2incPackage::_instance() );
	Utils::EmfPackageLoader().load( root::RootPackage::_instance() );
	EcoreModelChecker::setToplevelPackage( root::RootPackage::_instance() );
	Projects::init();

	/* Read commandline options after initializing all ecore packages, so that
	 * Options::showVersion() can use them. */
	Application a(argc, argv);

	QTimer::singleShot(0, &a, SLOT(start()));

	return a.exec();
}
