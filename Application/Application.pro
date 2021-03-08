#
# Amalthea/Application/Application.pro
#
# Copyright (c) 2020-2021 INCHRON AG <info@inchron.com>
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# https://www.eclipse.org/legal/epl-2.0/
#
# SPDX-License-Identifier: EPL-2.0
#

include(../config.pri)

TEMPLATE = app
TARGET = am2inc
QMAKE_TARGET_DESCRIPTION = Tool-Suite 3 Amalthea Importer

INCLUDEPATH += ..
INCLUDEPATH += ../Amalthea ../Amalthea/amalthea
INCLUDEPATH += ../Mapping
INCLUDEPATH += ../Root/model
INCLUDEPATH += $${EMF4CPP}/include/emf4cpp

# When an ecore changes, emf4cpp will regenerate the .pri file. Then we need
# to rerun qmake to update the dependencies.
Makefile.target = $(MAKEFILE)
Makefile.depends += \
    $$relative_path($$PWD/../Amalthea/amalthea_model.pri, $$OUT_PWD) \
    $$relative_path($$PWD/../Root/model/root.pri, $$OUT_PWD) \
    $$relative_path($$PWD/../Mapping/am2inc.pri, $$OUT_PWD)
QMAKE_EXTRA_TARGETS += Makefile

DEFINES += VERSION=\\\"$$VERSION\\\"

QMAKE_CXXFLAGS += -Wno-unused-parameter

QT += core
QT -= gui
CONFIG += console

LIBS += -L../Amalthea/$${DESTDIR} -lAmalthea
LIBS += -L../Root/$${DESTDIR} -lRoot
LIBS += -L../Mapping/$${DESTDIR} -lMapping


! isEmpty(EMF4CPP): LIBS += -L$${EMF4CPP}/lib
LIBS += -lemf4cpp-ecore -lemf4cpp-ecorecpp

QMAKE_RPATHDIR += ../lib

# uses definitions above
include(../install.pri)

unix:debian {
	unset(MANGLED_INSTALLS)
	for(x, INSTALLS):MANGLED_INSTALLS += install_$${x}

	deploy.path = $$(OUT_PWD)/bin
	deploy.commands = linuxdeployqt $${PREFIX}/bin/$${TARGET}
	deploy.depends = $${MANGLED_INSTALLS}

	INSTALLS += deploy
}


# Input
HEADERS += \
    Application.h \
    AttributeCreator.h \
    Converter.h \
    CreatorTraits.h \
    Diagnostic.h \
    EcoreModelChecker.h \
    ModelChecker.h \
    ObjectCache.h \
    Options.h \
    TimeOperators.h \

SOURCES += \
    Application.cpp \
    AttributeCreator.cpp \
    Converter.cpp \
    Converter/activityGraph.cpp \
    Converter/hwModel.cpp \
    Converter/mappingModel.cpp \
    Converter/osModel.cpp \
    Converter/relax.cpp \
    Converter/stimuliModel.cpp \
    Converter/swModel.cpp \
    CreatorTraits.cpp \
    EcoreModelChecker.cpp \
    ModelChecker.cpp \
    ObjectCache.cpp \
    Options.cpp \
    TimeOperators.cpp \
    main.cpp \
