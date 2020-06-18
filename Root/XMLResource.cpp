/* -*- c++ -*-
 *
 * File: XMLResource.h
 *
 * Copyright 2018 INCHRON GmbH <info@inchron.com>
 */
#include "XMLResource.h"

#include <cctype>
#include <cstdlib>

#include <ecore/EClass.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <root/model/ModelObject.hpp>

namespace root {

XMLResource::XMLResource(const ProtectedTag&, const QUrl& url)
	: ecorecpp::resource::XMLResource(url) {
}

XMLResource::~XMLResource() = default;

void XMLResource::load(std::istream& is, const Resource::OptionMap& options) {
	::ecorecpp::resource::XMLResource::load(is, options);
}

void XMLResource::save(std::ostream& os, const Resource::OptionMap& options) {
	::ecorecpp::resource::XMLResource::save(os, options);
}

/** By default the uriFragment is first interpreted as our XPath-name
 * format. If that fails, the base class is called.
 */
::ecore::EObject_ptr XMLResource::getEObject(const std::string& uriFragment) {
	/* First parse the special format. */
	if (uriFragment.empty())
		return ::ecore::EObject_ptr();

	if (uriFragment[0] == '/') {
		auto eObject = _getEObject( uriFragment );
		if (eObject)
			return eObject;
	}

	/* If it fails, ask the base class. */
	return ::ecorecpp::resource::XMLResource::getEObject( uriFragment );
}

::ecore::EObject_ptr XMLResource::_getEObject(const std::string& uriFragment) {
	std::istringstream input(uriFragment.substr(1));
	std::string segment;

	::ecore::EObject_ptr current = nullptr;
	if ( getContents()->size() > 1 ) {
		std::getline(input, segment, '/');
		current = getEObjectForURIFragmentRootSegment(segment);
		if ( !current )
			return nullptr;
	} else {
		current = getContents()->get(0);
	}

	while (std::getline(input, segment, '/') ) {
		if (segment.empty())
			continue;

		if ( segment[0] == '@' )
			segment.erase(segment.begin());

		std::string name;
		bool isCollection = false;
		size_t dotPosition = segment.find('.');
		if ( dotPosition != std::string::npos ) {
			name = QUrl::fromPercentEncoding(
					QByteArray::fromStdString(
						segment.substr(dotPosition + 1) ) ).toStdString();
			segment.erase(dotPosition);
			isCollection = true;
		}

		auto cl = current->eClass();
		auto sf = cl->getEStructuralFeature(segment);
		::ecorecpp::mapping::any any = current->eGet(sf);
		if (isCollection) {
			bool found = false;
			auto collection = ecorecpp::mapping::any::any_cast<
				::ecorecpp::mapping::EList<::ecore::EObject_ptr>::ptr_type>(any);

			/* Depending on the context (unknown here), names may start with
			 * digits. Hence first an object with a matching name is searched
			 * [SUITE3-1112]. */
			for (auto&& entry : *collection) {
				auto modelObject = ecore::as<root::model::ModelObject>(entry);
				if (modelObject && modelObject->getName() == name) {
					current = modelObject;
					found = true;
					break;
				}
			}

			if (!found && std::isdigit(name[0])) {
				/* For non-ModelObjects the name is a number and denotes the
				 * position in the container [SUITE3-1112]. */
				unsigned int pos = std::atoi(name.c_str());
				if (pos < collection->size()) {
					current = collection->get(pos);
					found = true;
				}
			}

			/* If there is no ModelObject with a matching name, the search
			 * will stop here. */
			if (!found)
				return nullptr;

		} else {
			current = ::ecorecpp::mapping::any::any_cast<::ecore::EObject_ptr>(any);
		}
	}

	return current;
}

/** getURIFragment() always returns our XPath-name format. All options are
 * ignored.
 */
std::string XMLResource::getURIFragment(::ecore::EObject_ptr eObject) {
	if ( !eObject)
		return "";

	/* Always return the special encoding. */
	return _getURIFragment(eObject);
}

std::string XMLResource::_getURIFragment(::ecore::EObject_ptr eObject) {
	if ( !eObject)
		return "";

	auto current = eObject;
	std::string id;
	while ( auto container = current->eContainer() ) {
		if ( container->eResource().get() != this )
			break;

		auto feature = current->eContainingFeature();
		if ( feature->getUpperBound() == 1 )
			id.insert(0, std::string("/@") + feature->getName());
		else {
			auto modelObject = ecore::as<root::model::ModelObject>(current);
			if ( modelObject ) {
				auto encodedModelName = QUrl::toPercentEncoding(
						QString::fromStdString( modelObject->getName() ) );
				id.insert(0, std::string("/@") + feature->getName()
						  + "." + encodedModelName.toStdString());
			} else {
				ecorecpp::mapping::any _any = container->eGet(feature);
				auto ef = ecorecpp::mapping::any::any_cast<
					ecorecpp::mapping::EList<::ecore::EObject_ptr>::ptr_type >(_any);
				for (size_t index = 0; index < ef->size(); ++index) {
					if ( ef->get(index) == current ) {
						id.insert( 0, std::string("/@")
								   + feature->getName()
								   + "." + std::to_string(index) );
						break;
					}
				}
			}
		}
		current = container;
	}

	if ( getContents()->size() > 1 )
		id.insert(0, getURIFragmentRootSegment(current));

	id.insert(0, std::string("/"));
	return id;
}

} // namespace root
