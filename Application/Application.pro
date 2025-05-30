#
# Amalthea/Application/Application.pro
#
# Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
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
INCLUDEPATH += ../Amalthea ../Amalthea/am120 \
               ../Amalthea/am200 ../Amalthea/am210 ../Amalthea/am220 \
               ../Amalthea/am320
INCLUDEPATH += ../Mapping
INCLUDEPATH += ../Root/model
INCLUDEPATH += $${EMF4CPP}/include/emf4cpp

# When an ecore changes, emf4cpp will regenerate the .pri file. Then we need
# to rerun qmake to update the dependencies.
Makefile.target = $(MAKEFILE)
Makefile.depends += \
    $$relative_path($$PWD/../Amalthea/am120/am120_model.pri, $$OUT_PWD) \
    $$relative_path($$PWD/../Amalthea/am200/am200_model.pri, $$OUT_PWD) \
    $$relative_path($$PWD/../Amalthea/am210/am210_model.pri, $$OUT_PWD) \
    $$relative_path($$PWD/../Amalthea/am220/am220_model.pri, $$OUT_PWD) \
    $$relative_path($$PWD/../Amalthea/am320/am320_model.pri, $$OUT_PWD) \
    $$relative_path($$PWD/../Root/model/root.pri, $$OUT_PWD)
QMAKE_EXTRA_TARGETS += Makefile

DEFINES += VERSION=\\\"$$VERSION\\\"

QMAKE_CXXFLAGS += -Wno-unused-parameter

QT += core
QT -= gui
CONFIG += console

LIBS += -L../Amalthea/$${DESTDIR} -lAmalthea
LIBS += -L../Amalthea/am120/$${DESTDIR} -lam120
LIBS += -L../Amalthea/am200/$${DESTDIR} -lam200
LIBS += -L../Amalthea/am210/$${DESTDIR} -lam210
LIBS += -L../Amalthea/am220/$${DESTDIR} -lam220
LIBS += -L../Amalthea/am320/$${DESTDIR} -lam320
LIBS += -L../Root/$${DESTDIR} -lRoot
LIBS += -L../Mapping/$${DESTDIR} -lMapping

include(../quazip.pri)

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
    AliasedMetaModelRepository.h \
    Application.h \
    AttributeCreator.h \
    Converter.h \
    CreatorTraits.h \
    Diagnostic.h \
    EcoreModelChecker.h \
    ModelChecker.h \
    ObjectCache.h \
    Options.h \
    StableIntrinsicIds.h \
    StimulusTraits.h \
    TimeOperators.h \
    \
    Converter120/Converter.h \
    Converter120/StimulusTraits.h \
    \
    Converter200/Converter.h \
    Converter200/ResolveValues.h \
    Converter200/StimulusTraits.h \
    \
    Converter210/Converter.h \
    Converter210/ResolveValues.h \
    Converter210/StimulusTraits.h \
    \
    Converter220/Converter.h \
    Converter220/ResolveValues.h \
    Converter220/StimulusTraits.h \
    \
    Converter320/Converter.h \
    Converter320/ResolveValues.h \
    Converter320/StimulusTraits.h \

SOURCES += \
    AliasedMetaModelRepository.cpp \
    Application.cpp \
    AttributeCreator.cpp \
    Converter.cpp \
    CreatorTraits.cpp \
    EcoreModelChecker.cpp \
    ModelChecker.cpp \
    ObjectCache.cpp \
    Options.cpp \
    StableIntrinsicIds.cpp \
    TimeOperators.cpp \
    main.cpp \
    \
    Converter120/Converter.cpp \
    Converter120/activityGraph.cpp \
    Converter120/constraintsModel.cpp \
    Converter120/eventModel.cpp \
    Converter120/hwModel.cpp \
    Converter120/mappingModel.cpp \
    Converter120/osModel.cpp \
    Converter120/relax.cpp \
    Converter120/stimuliModel.cpp \
    Converter120/swModel.cpp \
    \
    Converter200/Converter.cpp \
    Converter200/ResolveValues.cpp \
    Converter200/activityGraph.cpp \
    Converter200/constraintsModel.cpp \
    Converter200/eventModel.cpp \
    Converter200/hwModel.cpp \
    Converter200/mappingModel.cpp \
    Converter200/osModel.cpp \
    Converter200/relax.cpp \
    Converter200/stimuliModel.cpp \
    Converter200/swModel.cpp \
    \
    Converter210/Converter.cpp \
    Converter210/ResolveValues.cpp \
    Converter210/activityGraph.cpp \
    Converter210/constraintsModel.cpp \
    Converter210/eventModel.cpp \
    Converter210/hwModel.cpp \
    Converter210/mappingModel.cpp \
    Converter210/osModel.cpp \
    Converter210/relax.cpp \
    Converter210/stimuliModel.cpp \
    Converter210/swModel.cpp \
    \
    Converter220/Converter.cpp \
    Converter220/ResolveValues.cpp \
    Converter220/activityGraph.cpp \
    Converter220/constraintsModel.cpp \
    Converter220/eventModel.cpp \
    Converter220/hwModel.cpp \
    Converter220/mappingModel.cpp \
    Converter220/osModel.cpp \
    Converter220/relax.cpp \
    Converter220/stimuliModel.cpp \
    Converter220/swModel.cpp \
    \
    Converter320/Converter.cpp \
    Converter320/ResolveValues.cpp \
    Converter320/activityGraph.cpp \
    Converter320/constraintsModel.cpp \
    Converter320/eventModel.cpp \
    Converter320/hwModel.cpp \
    Converter320/mappingModel.cpp \
    Converter320/osModel.cpp \
    Converter320/relax.cpp \
    Converter320/stimuliModel.cpp \
    Converter320/swModel.cpp \
