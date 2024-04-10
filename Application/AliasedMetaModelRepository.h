/* -*- c++ -*-
 *
 * Copyright (c) 2024 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#pragma once

#include <ecorecpp/MetaModelRepository.hpp>

/** This version of a MetaModelRepository supports the registration of an
 * EPackage not only for the native namespace URI, but also for a list of
 * aliased namespace URIs.
 */
class AliasedMetaModelRepository : public ecorecpp::MetaModelRepository {
public:
	void loadPackage( ecore::EPackage_ptr package );
	void loadPackage( ecore::EPackage_ptr package,
					  std::initializer_list<std::string> nsUriAliases );

private:
	void loadPackage( ecore::EPackage_ptr package, const std::string& baseNsUri,
					  unsigned int length,
					  const std::initializer_list<std::string>& nsUriAliases );
};
