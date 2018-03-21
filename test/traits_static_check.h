//
//  traits_static_check.h
//  krypton
//
//  Created by Jack Zou on 2018/3/12.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef traits_static_check_h
#define traits_static_check_h

#include "unit.hpp"

void traits_static_check() {
    static_assert(!kr::equals<kr::metric_system_base, kr::british_system_base>::value, "tratis are different");
    static_assert(kr::equals<kr::metric_system_base, kr::metric_system_base>::value, "tratis are same");
    static_assert(!kr::equals<kr::metric_system<kr::length>, kr::metric_system<kr::mass>>::value, "tratis are diffenent");
    static_assert(!kr::equals<kr::british_system<kr::length>, kr::british_system<kr::mass>>::value, "tratis are diffenent");
    static_assert(!kr::equals<kr::metric_system<kr::length>, kr::british_system<kr::length>>::value, "tratis are different");
}


#endif /* traits_static_check_h */
