#
# Amalthea/Application/Application.pro
#

include(../../config.pri)

TEMPLATE = app
TARGET = am2inc
QMAKE_TARGET_DESCRIPTION = Tool-Suite 3 Amalthea Importer

INCLUDEPATH += ../..
INCLUDEPATH += ../Amalthea ../Amalthea/amalthea
INCLUDEPATH += ../Mapping
INCLUDEPATH += ../../Root/model
INCLUDEPATH += ../../Projects/model
INCLUDEPATH += $${EMF4CPP}/include/emf4cpp

QMAKE_CXXFLAGS += -Wno-unused-parameter

QT += core
QT -= gui
CONFIG += console

LIBS += -L../../Projects/$${DESTDIR} -lProjects
LIBS += -L../../Utils/$${DESTDIR} -lUtils
LIBS += -L../../Basics/$${DESTDIR} -lBasics
LIBS += -L../../emf-command-qt5/$${DESTDIR} -lemf-command-qt5
LIBS += -L../../Model/$${DESTDIR} -lModelv20
LIBS += -L../../ReleaseInfo/$${DESTDIR} -lReleaseInfo

LIBS += -L../Amalthea/$${DESTDIR} -lAmalthea
LIBS += -L../Mapping/$${DESTDIR} -lMapping
LIBS += -L../../Root/$${DESTDIR} -lRoot


! isEmpty(EMF4CPP): LIBS += -L$${EMF4CPP}/lib
LIBS += -lemf4cpp-ecore -lemf4cpp-ecorecpp

QMAKE_RPATHDIR += ../lib

# uses definitions above
include(../../install.pri)



# Input
HEADERS += \
    Application.h \
    AttributeCreator.h \
    Converter.h \
    CreatorTraits.h \
    EcoreModelChecker.h \
    ModelChecker.h \
    ObjectCache.h \
    Options.h \

SOURCES += \
    Application.cpp \
    AttributeCreator.cpp \
    Converter.cpp \
    Converter/hwModel.cpp \
    Converter/relax.cpp \
    CreatorTraits.cpp \
    EcoreModelChecker.cpp \
    ModelChecker.cpp \
    ObjectCache.cpp \
    Options.cpp \
    main.cpp \
