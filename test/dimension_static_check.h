//
//  dimension_static_check.h
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef dimension_static_check_h
#define dimension_static_check_h

#include "core/sequence.hpp"
#include "core/dimension.hpp"

void dimension_static_check() {
	static_assert(kr::equals<kr::velocity, kr::sequence<kr::_1, kr::_0, kr::__1, kr::_0, kr::_0, kr::_0, kr::_0, kr::_0, kr::_0>>::value, "they are equal");
	static_assert(kr::equals<kr::acceleration, kr::sequence<kr::_1, kr::_0, kr::__2, kr::_0, kr::_0, kr::_0, kr::_0, kr::_0, kr::_0>>::value, "they are equal");
	static_assert(kr::equals<kr::force, kr::sequence<kr::_1, kr::_1, kr::__2, kr::_0, kr::_0, kr::_0, kr::_0, kr::_0, kr::_0>>::value, "they are equal");
}

#endif // dimension_static_check_h