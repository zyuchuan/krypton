//
//  dimensions.hpp
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef dimensions_h
#define dimensions_h

#include "sequence.hpp"
#include "integers.hpp"
#include "quantity.hpp"

BEGIN_KR_NAMESPACE
    
// Basic dimensions
using mass = sequence<_1, _0, _0, _0, _0, _0, _0>;
using length = sequence<_0, _1, _0, _0, _0, _0, _0>;
using time = sequence<_0, _0, _1, _0, _0, _0, _0>;
//    using sequence<_0, _0, _0, _1, _0, _0, _0> charge;
//    using sequence<_0, _0, _0, _0, _1, _0, _0> temperature;
//    using sequence<_0, _0, _0, _0, _0, _1, _0> intensity;

// Compound dimensions
using velocity = sequence<_0, _1, __1, _0, _0, _0, _0>;       // l/t
using acceleration = sequence<_0, _1, __2, _0, _0, _0, _0>;   // l/t^2
using force = sequence<_1, _1, __2, _0, _0, _0, _0>;          // ml/t^2


template<class T> using meter = quantity<T, length>;
template<class T> using kilometer = quantity<T, length, std::kilo>;

END_KR_NAMESPACE
#endif /* dimensions_h */
