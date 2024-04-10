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
#include "AliasedMetaModelRepository.h"

void AliasedMetaModelRepository::loadPackage( ecore::EPackage_ptr package ) {
	load( package );
	for ( const auto& subPackage : package->getESubpackages() )
		loadPackage( subPackage );
}

void AliasedMetaModelRepository::loadPackage(
	ecore::EPackage_ptr package, std::initializer_list<std::string> nsUriAliases ) {
	auto topLevelNsUri = package->getNsURI();
	loadPackage( package, topLevelNsUri, topLevelNsUri.length(), nsUriAliases );
}

void AliasedMetaModelRepository::loadPackage(
	ecore::EPackage_ptr package, const std::string& baseNsUri, const unsigned int length,
	const std::initializer_list<std::string>& nsUriAliases ) {
	load( package );
	auto suffix = package->getNsURI();
	auto index = suffix.find( baseNsUri );
	if ( index != std::string::npos ) {
		suffix.erase( index, length );
		for ( const auto& alias : nsUriAliases ) {
			auto newNsURI = alias + suffix;
			m_by_nsURI[newNsURI] = package;
		}
	}

	for ( const auto& subPackage : package->getESubpackages() )
		loadPackage( subPackage, baseNsUri, length, nsUriAliases );
}
