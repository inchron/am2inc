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


#include <amalthea/model/ModelFactory.hpp>
#include <root/RootFactory.hpp>


#include "ObjectCache.h"




/* Some test code */
ObjectCache oc;

void test() {


	auto amObject = amalthea::model::create<amalthea::model::Amalthea>();

	auto e = oc.make<root::RootFactory, root::Root>(amObject);
}
