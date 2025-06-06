#
# qmake configuration for libAmalthea.so / Amalthea.dll
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

TEMPLATE = lib
TARGET = Amalthea
QT += core

CONFIG += dll
win32: CONFIG += plugin # skip installation of libXX.a next to libXX.dll
CONFIG -= debug
CONFIG += release

# Amalthea does not distribute the classes over subpackages. As a result the
# generated PackageImpl.cpp is too big to compile with debug and the
# sanitizer.
CONFIG -= sanitizer

DEFINES += MAKE_AMALTHEA_DLL

QMAKE_CXXFLAGS += -Wno-unused-parameter

INCLUDEPATH += .. ../Amalthea

include(../quazip.pri)

!isEmpty(EMF4CPP): LIBS += -L$${EMF4CPP}/lib
LIBS += -lemf4cpp-ecore -lemf4cpp-ecorecpp

QMAKE_RPATHDIR = .

#
# All files are located in a subdirectory, which needs to be added to VPATH and INCLUDES
#
SRCGEN = .
VPATH = $${SRCGEN}
INCLUDEPATH += $${SRCGEN}

include(../install.pri)

unix {
    ! isEmpty(EMF4CPP) {
        libemf4cpp.extra = cp --preserve --no-dereference \
                $${EMF4CPP}/lib/libemf4cpp-ecore*.so* $(INSTALL_ROOT)$${PREFIX}/lib
        libemf4cpp.path = $${PREFIX}/lib
        INSTALLS += libemf4cpp
    }

    ! isEmpty(QUAZIP) {
        libquazip.extra = cp --preserve --no-dereference \
                $${QUAZIP}/lib/libquazip.so* $(INSTALL_ROOT)$${PREFIX}/lib
        libquazip.path = $${PREFIX}/lib
        INSTALLS += libquazip
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

      libquazip.path = $${PREFIX}/bin
      libquazip.files = $${QUAZIP}/bin/quazip.dll

      crossbuild {
          i686 {
              libquazip.files += /usr/i686-w64-mingw32/lib/zlib1.dll
              libquazip.files += /usr/i686-w64-mingw32/lib/libwinpthread-1.dll
          } else {
              llvm_mingw {
                  libquazip.files += $${INCHRONLIBS}/zlib/bin/zlib1.dll
                  libquazip.files += /usr/local/bin/libz.dll
              } else {
                  libquazip.files += /usr/x86_64-w64-mingw32/lib/zlib1.dll
                  libquazip.files += /usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll
              }
          }
      } else {
          libquazip.files += \
              c:/TDM-GCC-64/x86_64-w64-mingw32/lib/zlib1.dll
      }

      INSTALLS += libquazip
}

QMAKE_EXTRA_TARGETS += version.cpp

HEADERS += \
    XMLResource.h \
    dllAmalthea.h

SOURCES += \
    XMLResource.cpp \
    version.cpp

RESOURCES += \
