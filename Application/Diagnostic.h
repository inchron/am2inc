/* -*- c++ -*-
 *
 * Copyright (c) 2020-2021 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#pragma once

#include <string.h>

/** The classes and methods in this namespace help to emit certain messages to
 * the user. Per default, everything is sent to std::cerr.
 */
namespace Diagnostic {

namespace details {

/** The idiom of converting a type's name into a string was taken from
 * https://blog.molecular-matters.com/2015/12/11/getting-the-type-of-a-template-argument-as-string-without-rtti/
 * It is covered by the following license:
 */
// The MIT License(MIT)
//
// Copyright(c) 2012-2017 Stefan Reinalter
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
template<typename T>
struct GetNameHelper {

#if defined(__GNUC__)
#   define FUNCTION __PRETTY_FUNCTION__
	static constexpr unsigned int front = sizeof("static const char* Diagnostic::details::GetNameHelper<T>::getTypeName() [with T = ") - 1u;
	static constexpr unsigned int back = sizeof("]") - 1u;

#else // if MSVC
#   define FUNCTION __FUNCTION__
	static constexpr unsigned int front = sizeof("Diagnostic::details::GetNameHelper<") - 1u;
	static constexpr unsigned int back = sizeof(">::GetTypeName") - 1u;

#endif

	static const char* getTypeName() {
		static constexpr size_t size = sizeof(FUNCTION) - front - back;
		static char typeName[size] = {};
		if (typeName[0] == 0)
			memcpy(typeName, FUNCTION + front, size - 1u);
		return typeName;
	}
};
/* End of the idiom. */

} // namespace details


/** Emit a message about an unimplemented conversion regarding a certain
 * class.
 *
 * Usage:
 * static Diagnostic::NotImplemented<am::RunnableAllocation> message;
 *
 * The compiler will take care that the constructor of this object is executed
 * only once, hence the message will appear only once.
 */
template<typename T>
struct NotImplemented {
	NotImplemented() {
		std::cerr << "Conversion not implemented: "
				  << details::GetNameHelper<T>::getTypeName()
				  << "\n";
	}
};


struct ObjectRequired {
	template<typename T>
	static bool exists(const ecore::Ptr<T>& t) {
		if (!t) {
			std::cerr << "Missing object of type "
					  << details::GetNameHelper<T>::getTypeName()
					  << "\n";
			return false;
		}
		return true;
	}

	template<typename T>
	static bool notEmpty(const ecorecpp::mapping::EList< ecore::Ptr<T> >& list) {
		if (list.size() == 0) {
			std::cerr << "Missing object(s) of type "
					  << details::GetNameHelper<T>::getTypeName()
					  << "\n";
			return false;
		}
		return true;
	}

};

} // namespace Diagnostic
