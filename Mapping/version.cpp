/* -*- c++ -*-
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file version.cpp
 * This file introduces a dependency to Qt so that deployqt.exe can be called
 * on the resulting binary.
 */
#include <QString>

#include <ReleaseInfo/gitversion.h>
#include "am2inc/dllAm2inc.hpp"

namespace am2inc {

QString EXPORT_AM2INC_DLL getGitVersion() {
	return QString(GIT_VERSION);
}

} // namespace am2inc
