//
//  traits_static_check.h
//  krypton
//
//  Created by Jack Zou on 2018/3/12.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef traits_static_check_h
#define traits_static_check_h

#include "traits.hpp"

void traits_static_check() {
    static_assert(!kr::equals<kr::eng_traits_base, kr::iso_traits_base>::value, "tratis are different");
    static_assert(kr::equals<kr::iso_traits_base, kr::iso_traits_base>::value, "tratis are same");
    static_assert(!kr::equals<kr::iso_traits<kr::length>, kr::iso_traits<kr::mass>>::value, "tratis are diffenent");
    static_assert(!kr::equals<kr::eng_traits<kr::length>, kr::eng_traits<kr::mass>>::value, "tratis are diffenent");
    static_assert(!kr::equals<kr::iso_traits<kr::length>, kr::eng_traits<kr::length>>::value, "tratis are different");
}


#endif /* traits_static_check_h */
