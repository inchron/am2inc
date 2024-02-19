/* * c++ *
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
/** @file version.cpp
 * This file introduces a dependency to Qt so that deployqt.exe can be called
 * on the resulting binary.
 */
#include <QString>

#include "../gitversion.h"
#include "dllAmalthea.h"

namespace amalthea {

QString EXPORT_AMALTHEA_DLL getGitVersion();

QString getGitVersion() {
	return QString(GIT_VERSION);
}

}  // namespace amalthea
