#
# Amalthea/Amalthea.pro
#
# Copyright (c) 2020-2021 INCHRON AG <info@inchron.com>
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# https://www.eclipse.org/legal/epl-2.0/
#
# SPDX-License-Identifier: EPL-2.0
#

TEMPLATE = subdirs

SUBDIRS += \
    Amalthea \
    Application \
    Mapping \
    Root \
    gitversion \

gitversion.file = gitversion.pri

Amalthea.depends += gitversion
Mapping.depends += gitversion Amalthea Root
Application.depends += Amalthea Mapping Root
