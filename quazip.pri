#
# qmake configuration for QuaZip
#
# Copyright (c) 2024 INCHRON AG <info@inchron.com>
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# https://www.eclipse.org/legal/epl-2.0/
#
# SPDX-License-Identifier: EPL-2.0
#

# Order of precendence of which path to use for include and lib of quazip
# 1. qmake variable QUAZIP
# 2. environment variable QUAZIP
# 3. default path of compiler and linker

isEmpty(QUAZIP_USE_SYSTEM): QUAZIP_USE_SYSTEM = $$(QUAZIP_USE_SYSTEM)
isEmpty(QUAZIP_USE_SYSTEM) {
    isEmpty(QUAZIP): QUAZIP = $$(QUAZIP)
    isEmpty(QUAZIP): QUAZIP = $${INCHRONLIBS}/quazip
    INCLUDEPATH += $${QUAZIP}/include
    unix: LIBS += -L$${QUAZIP}/lib
    win32: LIBS += -L$${QUAZIP}/bin
}
LIBS += -lquazip
