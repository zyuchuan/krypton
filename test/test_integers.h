//
//  test_integers.cpp
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include <iostream>
#include "integers.hpp"

void test_integers() {
    static_assert(kr::__8::value == -8, "kr::__8 must represent value -8");
    static_assert(kr::__6::value == -6, "kr::__6 must represent value -6");
    static_assert(kr::__4::value == -4, "kr::__4 must represent value -4");
    static_assert(kr::__2::value == -2, "kr::__2 must represent value -2");
    static_assert(kr::_0::value == 0, "kr::_0 must represent value 0");
    static_assert(kr::_1::value == 1, "kr::_1 must represent value 1");
    static_assert(kr::_3::value == 3, "kr::_3 must represent value 3");
    static_assert(kr::_5::value == 5, "kr::_5 must represent value 5");
    static_assert(kr::_7::value == 7, "kr::_7 must represent value 7");
    
    static_assert(kr::is_integral_constant<int>::value == 0, "int is not std::integral_constatn");
    static_assert(kr::is_integral_constant<kr::_1>::value, "kr::_1 is std::integral_constant");
    
    static_assert(kr::plus<kr::__1, kr::_1>::value == 0, "-1 + 1 must equal to zero");
    static_assert(kr::plus<kr::_1, kr::_7>::value == 8, "1 + 7 must equal to eight");
    
    //static_assert(kr::plus<int, int>::value, "kr::plus<int, int> should not compile");
    //static_assert(kr::plus<kr::_1, int>::value, "kr::plus<kr::_1, int> should not compile");
    //static_assert(kr::plus<int, kr::_1>::value, "kr::plus<kr::_1, int> should not compile");
    
    static_assert(kr::equals<kr::_1, std::integral_constant<int, 1>>::value, "they are equal");
    //static_assert(kr::equals<kr::_1, kr::__1>::value, "they are not equal");
}
