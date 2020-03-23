/** -*- c++ -*-
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
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
