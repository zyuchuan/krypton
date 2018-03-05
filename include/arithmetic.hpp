//
//  arithmetic.hpp
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef arithmetic_h
#define arithmetic_h

#include <type_traits>
#include "integers.hpp"
#include "dimensions.hpp"

namespace kr {
    //template<class A, class B>
    //struct plus;
    
    template<class A,
             class B,
             class = typename std::enable_if<
                kr::is_integral_constant<A>::value &&
                kr::is_integral_constant<B>::value>::type>
    struct plus : std::integral_constant<kr_int_t, A::value + B::value>{};
    
    template<class A,
            class B,
            class = typename std::enable_if<
            kr::is_integral_constant<A>::value &&
            kr::is_integral_constant<B>::value>::type>
            struct minus : std::integral_constant<kr_int_t, A::value - B::value>{};
    
    
}

#endif /* arithmetic_h */
