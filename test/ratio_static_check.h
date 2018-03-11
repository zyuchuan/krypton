//
//  ratio_static_check.h
//  krypton
//
//  Created by Jack Zou on 2018/3/11.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef ratio_static_check_h
#define ratio_static_check_h

#include <ratio>

void ratio_static_check() {
    using R1 = std::ratio<100, 1>;
    using R2 = std::ratio<1000, 1>;

    static_assert(std::ratio_divide<R1, R2>::num == 1, "assertion failed");
    static_assert(std::ratio_divide<R1, R2>::den == 10, "assertion failed");
    static_assert(std::ratio_divide<R2, R1>::num == 10, "assertion failed");
    static_assert(std::ratio_divide<R2, R1>::den == 1, "assertion failed");
}

#endif /* ratio_static_check_h */
