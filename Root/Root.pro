#
# qmake configuration for libroot.so / root.dll
#

include(../config.pri)

TEMPLATE = lib
TARGET = Root
QT += core

CONFIG += dll
DEFINES += MAKE_ROOT_DLL

QMAKE_CXXFLAGS += -Wno-unused-parameter

INCLUDEPATH += ..

!isEmpty(EMF4CPP): LIBS += -L$${EMF4CPP}/lib
LIBS += -lemf4cpp-ecore -lemf4cpp-ecorecpp

QMAKE_RPATHDIR = .

#
# All files are located in a subdirectory, which needs to be added to VPATH and INCLUDES
#
SRCGEN = model
VPATH = $${SRCGEN}
INCLUDEPATH += $${SRCGEN}


ROOT_ECORE = $${PWD}/../EcoreModels/root.ecore

#
# root.pri has the list of source files created by emf4cpp for the model
#
root.pri.target = $$relative_path($${PWD}/model/root.pri, $${OUT_PWD})
root.pri.depends = $$relative_path($${ROOT_ECORE}, $${OUT_PWD})
root.pri.commands =  \
    @echo generating model && \
    $${EMF4CPP}/bin/emf4cpp.generator.sh -c -o $${PWD}/model $${ROOT_ECORE} && \
    touch $@

QMAKE_EXTRA_TARGETS += root.pri

exists(model/root.pri): include(model/root.pri)
!exists(model/root.pri): Makefile.depends += $$root.pri.target


include(../install.pri)

unix {
    ! isEmpty(EMF4CPP) {
        libemf4cpp.extra = cp --preserve --no-dereference \
                $${EMF4CPP}/lib/libemf4cpp-ecore*.so* $(INSTALL_ROOT)$${PREFIX}/lib
        libemf4cpp.path = $${PREFIX}/lib
        INSTALLS += libemf4cpp
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
    XMLResource.h \
    XMLResourceFactory.h \

SOURCES += \
    XMLResource.cpp \
    XMLResourceFactory.cpp \

RESOURCES += \
