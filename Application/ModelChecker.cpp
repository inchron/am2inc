/* -*- c++ -*-
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 */
#include "ModelChecker.h"

#include <root/model.hpp>

namespace sm3 = root::model;


void ModelChecker<root::model::GenericSystem>::work(
	const ecore::Ptr<sm3::GenericSystem>& o ) {
	EcoreModelChecker().work( o );

	sm3::Scheduler_ptr isrScheduler( sm3::create<sm3::Scheduler>() );
	isrScheduler->setName( "IsrScheduler" );
	sm3::Scheduler_ptr defaultScheduler( sm3::create<sm3::Scheduler>() );
	defaultScheduler->setName( "DefaultScheduler" );
	isrScheduler->getSchedulables().push_back_unsafe( defaultScheduler );
	o->getRtosConfig()->getSchedulables().push_back_unsafe( isrScheduler );

	EcoreModelChecker().work( isrScheduler );
}
