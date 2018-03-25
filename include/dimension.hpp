//
//  dimensions.hpp
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef dimension_h
#define dimension_h

#include "integer.hpp"
#include "sequence.hpp"

BEGIN_KR_NAMESPACE

template<class T>
struct is_dimension : public std::false_type{};

template<class... Args>
struct is_dimension<sequence<Args...>> : public std::integral_constant<bool, sizeof...(Args)==7>{};
    
// Basic dimensions
using mass          = sequence<_1, _0, _0, _0, _0, _0, _0>;
using length        = sequence<_0, _1, _0, _0, _0, _0, _0>;
using time          = sequence<_0, _0, _1, _0, _0, _0, _0>;
using charge        = sequence<_0, _0, _0, _1, _0, _0, _0>;
using temperature   = sequence<_0, _0, _0, _0, _1, _0, _0>;
using intensity     = sequence<_0, _0, _0, _0, _0, _1, _0>;


// Compound dimensions
using velocity      = sequence<_0, _1, __1, _0, _0, _0, _0>;       // l/t
using acceleration  = sequence<_0, _1, __2, _0, _0, _0, _0>;   // l/t^2
using force         = sequence<_1, _1, __2, _0, _0, _0, _0>;          // ml/t^2


END_KR_NAMESPACE
#endif /* dimension_h */
