#
# Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# https://www.eclipse.org/legal/epl-2.0/
#
# SPDX-License-Identifier: EPL-2.0
#

include(../../config.pri)

TEMPLATE = lib
TARGET = am220
CONFIG -= qt

CONFIG += dll
win32: CONFIG += plugin # skip installation of libXX.a next to libXX.dll
CONFIG -= debug
CONFIG += release

# Amalthea does not distribute the classes over subpackages. As a result the
# generated PackageImpl.cpp is too big to compile with debug and the
# sanitizer.
CONFIG -= sanitizer

TARGET_UPPER = $$upper($${TARGET})

dll {
    DEFINES += MAKE_$${TARGET_UPPER}_MODEL_DLL
} else {
    DEFINES += MAKE_STATIC MAKE_$${TARGET_UPPER}_MODEL_STATIC
}

QMAKE_CXXFLAGS += -Wno-unused-parameter

INCLUDEPATH += ../..


!isEmpty(EMF4CPP): LIBS += -L$${EMF4CPP}/lib
LIBS += -lemf4cpp-ecore -lemf4cpp-ecorecpp

QMAKE_RPATHDIR = .

#
# All files are located in a subdirectory, which needs to be added to VPATH and INCLUDES
#
SRCGEN = .
VPATH = $${SRCGEN}
INCLUDEPATH += $${SRCGEN}

#
# list of source files created by emf4cpp
#
AMALTHEA_ECORE = $${PWD}/../../EcoreModels/amalthea-2.2.0.ecore

PRI=$${TARGET}_model.pri
$${PRI}.target = $$relative_path($${PWD}/$${PRI}, $${OUT_PWD})
$${PRI}.depends = $$relative_path($${AMALTHEA_ECORE}, $${OUT_PWD})
$${PRI}.commands =  \
    @echo generating model && \
    ../adaptC++.sh $${AMALTHEA_ECORE} && \
    $${EMF4CPP}/bin/emf4cpp.generator.sh -c -java \
        --target-version=$${TARGET} $${AMALTHEA_ECORE} && \
    touch $@

QMAKE_EXTRA_TARGETS += $${PRI}

exists($${PRI}): include($${PRI})
!exists($${PRI}): Makefile.depends += $$am220_model.pri.target

Makefile.depends += ../adaptC++.sh

include(../../install.pri)
