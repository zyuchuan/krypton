//
//  unit_static_check.h
//  krypton
//
//  Created by Jack Zou on 2018/3/12.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef unit_static_check_h
#define unit_static_check_h

#include "unit.hpp"

void traits_static_check() {
    // equals
    static_assert(!kr::equals<kr::metric_system<kr::length>, kr::metric_system<kr::mass>>::value, "Units are diffenent");
    static_assert(!kr::equals<kr::british_system<kr::length>, kr::british_system<kr::mass>>::value, "Units are diffenent");
    static_assert(!kr::equals<kr::metric_system<kr::length>, kr::british_system<kr::length>>::value, "Units are different");
    
    // metric_equals
    static_assert(kr::system_equals<kr::metric_system<kr::length>, kr::metric_system<kr::mass>>::value, "Both belong to metric system");
    static_assert(kr::system_equals<kr::british_system<kr::length>, kr::british_system<kr::mass>>::value, "Both belong to british system");
    static_assert(!kr::equals<kr::metric_system<kr::length>, kr::british_system<kr::length>>::value, "They are different system");
}


#endif /* unit_static_check_h */
