#
# Toplevel configuration for Amalthea-to-INCHRON
#

# make install copies the files to these directories
TAG = qt5
INSTALLS += target

isEmpty(PREFIX): PREFIX=$$(PREFIX)

unix {
    isEmpty(PREFIX): PREFIX = /tmp/kde-$$system(whoami)/inchron-$${TAG}

    dll:target.path = $${PREFIX}/lib
    else {
         static:target.path = $${PREFIX}/lib
         else:target.path = $${PREFIX}/bin
    }
}

win32 {
    isEmpty(PREFIX) {
        CONFIG(release, debug|release) {
            PREFIX = d:/Builds/ToolSuite3.$${DESTDIR}
        } else {
            PREFIX = d:/Builds/ToolSuite3
        }
    }

    dll:target.path = $${PREFIX}/bin
    else {
        static:target.path = $${PREFIX}/lib
        else:target.path = $${PREFIX}/bin
    }
    msvc:QMAKE_CXXFLAGS += /MP

    contains(TEMPLATE, ".*app")|contains(TEMPLATE, ".*lib"): !static: !staticlib: qt {
        unset(MANGLED_INSTALLS)
        for(x, INSTALLS):MANGLED_INSTALLS += install_$${x}

        deployqt.path = $${target.path}
        deployqt.commands = windeployqt --verbose 0 $(INSTALL_ROOT:@msyshack@%=%)$${deployqt.path}/$(TARGET)
        deployqt.depends = $${MANGLED_INSTALLS}
        INSTALLS += deployqt

        # [SUITE3-2063] windeployqt on linux does not copy qwindowsd.dll in
        #   debug mode
        crossbuild:CONFIG(debug, debug|release) {
            qwindowsd.path = $${PREFIX}/bin/platforms
            qwindowsd.files += \
                $$(Qt5Core_DIR)/../../../plugins/platforms/qwindowsd.dll
            INSTALLS += qwindowsd
        }
    }
}
