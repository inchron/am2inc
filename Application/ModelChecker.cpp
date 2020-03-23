/** -*- c++ -*-
 *
 * Copyright 2020 INCHRON AG <info@inchron.com>
 */
#include "ModelChecker.h"

#include <root/model.hpp>

namespace sm3 = root::model;


void ModelChecker<root::model::GenericSystem>::work(const ecore::Ptr<sm3::GenericSystem>& o) {
	EcoreModelChecker().work(o);

	sm3::Scheduler_ptr isrScheduler(sm3::create<sm3::Scheduler>());
	isrScheduler->setName("IsrScheduler");
	sm3::Scheduler_ptr defaultScheduler(sm3::create<sm3::Scheduler>());
	defaultScheduler->setName("DefaultScheduler");
	isrScheduler->getSchedulables().push_back(defaultScheduler);
	o->getRtosConfig()->getSchedulables().push_back(isrScheduler);

	EcoreModelChecker().work(isrScheduler);
}
