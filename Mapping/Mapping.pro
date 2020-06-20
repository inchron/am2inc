#
# qmake configuration for libAmalthea.so / Amalthea.dll
#

include(../config.pri)

TEMPLATE = lib
TARGET = Mapping
QT += core

CONFIG += dll

# Amalthea does not distribute the classes over subpackages. As a result the
# generated PackageImpl.cpp is too big to compile with debug and the
# sanitizer.
CONFIG -= sanitizer

DEFINES += MAKE_AM2INC_DLL

QMAKE_CXXFLAGS += -Wno-unused-parameter

INCLUDEPATH += ..

win32 {
    LIBS += -L../Amalthea/$${DESTDIR} -lAmalthea
    LIBS += -L../Root/$${DESTDIR} -lRoot
}


!isEmpty(EMF4CPP): LIBS += -L$${EMF4CPP}/lib
LIBS += -lemf4cpp-ecore -lemf4cpp-ecorecpp

QMAKE_RPATHDIR = .

#
# All files are located in a subdirectory, which needs to be added to VPATH and INCLUDES
#
SRCGEN = .
VPATH = $${SRCGEN}
INCLUDEPATH += $${SRCGEN}
INCLUDEPATH += ../Root/model
INCLUDEPATH += ../Amalthea/amalthea ../Amalthea

#
# list of source files created by emf4cpp
#
ECORE_PATH    = $${PWD}/../EcoreModels
MAPPING_ECORE = $${ECORE_PATH}/Am2IncMapping.ecore

am2inc.pri.target = $$relative_path($${PWD}/am2inc.pri, $${OUT_PWD})
am2inc.pri.depends = $$relative_path($${MAPPING_ECORE}, $${OUT_PWD})
am2inc.pri.commands =  \
    echo generating model && \
    ( cd $${ECORE_PATH} && \
    $${EMF4CPP}/bin/emf4cpp.generator.sh -c -o $${PWD} \
        $${MAPPING_ECORE} ) && \
    touch $@

QMAKE_EXTRA_TARGETS += am2inc.pri

exists(am2inc.pri): include(am2inc.pri)
!exists(am2inc.pri): Makefile.depends += $$am2inc.pri.target


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
      deploy.commands = windeployqt.exe --verbose 0 \
              $(INSTALL_ROOT:@msyshack@%=%)$${deploy.path}/libemf4cpp-ecore.dll \
              $(INSTALL_ROOT:@msyshack@%=%)$${deploy.path}/libemf4cpp-ecorecpp.dll
      deploy.depends = $${MANGLED_INSTALLS}

      INSTALLS += deploy
}


HEADERS += \

SOURCES += \
    version.cpp \

RESOURCES += \
