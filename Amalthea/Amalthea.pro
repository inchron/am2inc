#
# qmake configuration for libAmalthea.so / Amalthea.dll
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

TEMPLATE = lib
TARGET = Amalthea
QT += core

CONFIG += dll
CONFIG -= debug
CONFIG += release

# Amalthea does not distribute the classes over subpackages. As a result the
# generated PackageImpl.cpp is too big to compile with debug and the
# sanitizer.
CONFIG -= sanitizer

DEFINES += MAKE_AMALTHEA_MODEL_DLL

QMAKE_CXXFLAGS += -Wno-unused-parameter

INCLUDEPATH += .. ../Amalthea


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
AMALTHEA_ECORE = $${PWD}/../EcoreModels/amalthea.ecore

amalthea_model.pri.target = $$relative_path($${PWD}/amalthea_model.pri, $${OUT_PWD})
amalthea_model.pri.depends = $$relative_path($${AMALTHEA_ECORE}, $${OUT_PWD})
amalthea_model.pri.commands =  \
    @echo generating model && \
    ./adaptC++.sh $${AMALTHEA_ECORE} && \
    $${EMF4CPP}/bin/emf4cpp.generator.sh -c -java \
        --target-version=amalthea $${AMALTHEA_ECORE} && \
    touch $@

QMAKE_EXTRA_TARGETS += amalthea_model.pri

exists(amalthea_model.pri): include(amalthea_model.pri)
!exists(amalthea_model.pri): Makefile.depends += $$amalthea_model.pri.target

Makefile.depends += Amalthea.pro adaptC++.sh

include(../install.pri)

unix {
    ! isEmpty(EMF4CPP) {
        libemf4cpp.extra = cp --preserve --no-dereference \
                $${EMF4CPP}/lib/libemf4cpp-ecore*.so* $(INSTALL_ROOT)$${PREFIX}/lib
        libemf4cpp.path = $${PREFIX}/lib
#        INSTALLS += libemf4cpp
    }
}

win32 {
      # On Windows DLLs are searched either in the current directory,
      # in %PATH%, or in the system directories. If you do not want to
      # clobber the latter two, it's best to copy the required DLLs to
      # the same location as the target.
      target_libs.files = \
              $${EMF4CPP}/lib/libemf4cpp-ecore.dll \
              $${EMF4CPP}/lib/libemf4cpp-ecorecpp.dll
      target_libs.path  = $${PREFIX}/bin

      INSTALLS += target_libs

      unset(MANGLED_INSTALLS)
      for(x, INSTALLS):MANGLED_INSTALLS += install_$${x}
      deploy.path = $${target_libs.path}
      deploy.commands = windeployqt --verbose 0 \
              $(INSTALL_ROOT:@msyshack@%=%)$${deploy.path}/libemf4cpp-ecore.dll \
              $(INSTALL_ROOT:@msyshack@%=%)$${deploy.path}/libemf4cpp-ecorecpp.dll
      deploy.depends = $${MANGLED_INSTALLS}

      INSTALLS += deploy
}

QMAKE_EXTRA_TARGETS += version.cpp
version.cpp.depends += amalthea_model.pri

HEADERS += \
    XMLResource.h \

SOURCES += \
    XMLResource.cpp \
    version.cpp

RESOURCES += \
