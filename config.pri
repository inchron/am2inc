#
# Toplevel configuration for Amalthea-to-INCHRON
#

# SUITE3-546: qmake's config option 'testcase' does not work with
# debug_and_release, but this is the default on Windows.
CONFIG -= debug_and_release

# As a developer the first step to do is to override this
# with a file local.pri containing the line CONFIG += debug
CONFIG += release
CONFIG += ccache

# Suppress output of compiler command lines.
CONFIG += silent

#
# $PWD (or .) must NOT be added to the list of INCLUDES, because then
# any sytem header time.h will resolve to our Time.h - which is not
# what you want. The keyword no_include_pwd disables automatic add of
# -I. by qmake.
#
CONFIG += no_include_pwd

# Some source files are distributed over subdirectories.
CONFIG += object_parallel_to_source

# Explicitly make the Makefile depend on RELEASE so that it must be remade when
# RELEASE becomes newer than the Makefile
Makefile.target = $(MAKEFILE)
Makefile.depends = $$relative_path($$PWD/RELEASE, $$OUT_PWD)
QMAKE_EXTRA_TARGETS += Makefile

# VERSION will trigger the creation of a windows .rc file
VERSION = $$cat(RELEASE)
QMAKE_TARGET_COMPANY = INCHRON AG
QMAKE_TARGET_COPYRIGHT = 2024
# derived from TARGET: QMAKE_TARGET_PRODUCT
# QMAKE_TARGET_DESCRIPTION and RC_ICONS must be filled in subprojects

DEFINES += BUILD_NUMBER=$(BUILD_NUMBER)

CONFIG += c++17

CROSSBUILDARCH = $$(WINCROSSBUILDARCH)
!isEmpty(CROSSBUILDARCH): CONFIG += $${CROSSBUILDARCH}

i686: DEFINES += TARGETBITS=32
else: DEFINES += TARGETBITS=64

QMAKE_CXXFLAGS += -Wno-error=cpp -Wall -Wextra

CROSSBUILD = $$(WINCROSSBUILD)
! isEmpty(CROSSBUILD): CONFIG += crossbuild

TOOLCHAIN = $$(TOOLCHAIN)
! isEmpty(TOOLCHAIN): {
    contains(TOOLCHAIN, llvm-mingw) {
        CONFIG += llvm_mingw
    }
}

DEBIAN = $$(DEBIAN)
! isEmpty(DEBIAN): {
#  message(building debian package)
  CONFIG += debian
  INSTALLLIBS=$$IN_PWD/buildtools/install-libs
}

# Build and install(!) only those things, which shall go into a .msi or .deb
# installer package [SUITE3-864].
MSIONLY = $$(MSIONLY)
! isEmpty(MSIONLY) {
  CONFIG += msionly
}

unix: LIB_DIR=lib
win32: LIB_DIR=bin

# Do not use the major version number as suffix for the library name
CONFIG += skip_target_version_ext

INCHRONLIBS = /opt/inchron
win32: !crossbuild: INCHRONLIBS = D:/Development/

_INCHRONLIBS = $$(INCHRONLIBS)
! isEmpty( _INCHRONLIBS ) {	# environment variable override?
  INCHRONLIBS = $${_INCHRONLIBS}
}

# Variables for external libraries. Use default path unless the
# environmental variable with a custom path is set. Do not use any path
# if the environmental variable is set to use the system library.

EMF4CPP = $$(EMF4CPP)
isEmpty(EMF4CPP): EMF4CPP = $${INCHRONLIBS}/emf4cpp
EMF4CPP_USE_SYSTEM = $$(EMF4CPP_USE_SYSTEM)
! isEmpty(EMF4CPP_USE_SYSTEM): EMF4CPP =
unset(EMF4CPP_USE_SYSTEM)

! isEmpty(EMF4CPP): INCLUDEPATH += $${EMF4CPP}/include/emf4cpp

BOOST = $$(BOOST)
! isEmpty(BOOST): INCLUDEPATH += $${BOOST}/include

GCC_MAJOR_VERSION = $$system( $${QMAKE_CXX} -dumpversion | cut -d . -f 1 )
greaterThan(GCC_MAJOR_VERSION, 5): QMAKE_LFLAGS += -no-pie
greaterThan(GCC_MAJOR_VERSION, 7): QMAKE_CXXFLAGS += -Wno-cast-function-type

# NOTE Do not modify qmake variables after the following include, see SUITE3-1247.
exists(local.pri): include(local.pri)

unix:CONFIG(debug, debug|release) {
    # Summon the power of the address sanitizer. This can only be done in
    # debug mode, as in release mode the compilation of
    # Root/model/root/model/ModelPackageImpl.cpp will eat up all your
    # RAM.
    CONFIG += sanitizer sanitize_address sanitize_undefined
    # Further sanitizers known by Qt: sanitize_memory, sanitize_thread
}

# We assume no parallel builds of windows and linux
CONFIG(debug, debug|release):DESTDIR = debug
else:DESTDIR = release

unset(DESTDIR_SUFFIX)
crossbuild {
    i686: DESTDIR_SUFFIX = -win32
    else: DESTDIR_SUFFIX = -win64
    llvm_mingw {
        INCLUDEPATH += $${INCHRONLIBS}/zlib/include
        QMAKE_CXXFLAGS += -Wno-error=overloaded-virtual -Wno-error=inconsistent-missing-override
    }
}

OBJECTS_DIR = $$DESTDIR/.obj$${DESTDIR_SUFFIX}
MOC_DIR = $$DESTDIR/.moc$${DESTDIR_SUFFIX}
UI_DIR = $$DESTDIR/.uic$${DESTDIR_SUFFIX}
unset(DESTDIR_SUFFIX)
