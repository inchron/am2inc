/* -*- c++ -*-
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 */
/** @file version.cpp
 * This file introduces a dependency to Qt so that deployqt.exe can be called
 * on the resulting binary.
 */
#include <QString>

#include <am2inc/dllAm2inc.hpp>

#include "../gitversion.h"

namespace am2inc {

QString EXPORT_AM2INC_DLL getGitVersion();

QString getGitVersion() { return QString( GIT_VERSION ); }

}  // namespace am2inc
