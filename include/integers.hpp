//
//  integers.hpp
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef integers_h
#define integers_h

#include "krypton.hpp"

BEGIN_KR_NAMESPACE
    
// integral constant
using __8 = std::integral_constant<kr_int_t, -8>;
using __7 = std::integral_constant<kr_int_t, -7>;
using __6 = std::integral_constant<kr_int_t, -6>;
using __5 = std::integral_constant<kr_int_t, -5>;
using __4 = std::integral_constant<kr_int_t, -4>;
using __3 = std::integral_constant<kr_int_t, -3>;
using __2 = std::integral_constant<kr_int_t, -2>;
using __1 = std::integral_constant<kr_int_t, -1>;
using  _0 = std::integral_constant<kr_int_t, 0>;
using  _1 = std::integral_constant<kr_int_t, 1>;
using  _2 = std::integral_constant<kr_int_t, 2>;
using  _3 = std::integral_constant<kr_int_t, 3>;
using  _4 = std::integral_constant<kr_int_t, 4>;
using  _5 = std::integral_constant<kr_int_t, 5>;
using  _6 = std::integral_constant<kr_int_t, 6>;
using  _7 = std::integral_constant<kr_int_t, 7>;
using  _8 = std::integral_constant<kr_int_t, 8>;

// Type traits
template<class T>
struct is_integral_constant : public std::false_type {};

template<class T, T v>
struct is_integral_constant<std::integral_constant<T, v>> : public std::true_type {};
    
// Specialization for std::integral_constant
template<class T, T v1, T v2>
struct plus<std::integral_constant<T, v1>,
            std::integral_constant<T, v2>> : std::integral_constant<T, v1 + v2>{};

    
END_KR_NAMESPACE


#endif /* integers_h */
