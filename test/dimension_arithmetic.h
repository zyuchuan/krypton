//
//  dimension_arithmetic.cpp
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include <type_traits>
//#include <tuple>
//#include <brigand/sequences/at.hpp>

namespace kr1 {
    
    using __2 = std::integral_constant<int, -2>;
    using __1 = std::integral_constant<int, -1>;
    using  _0 = std::integral_constant<int, 0>;
    using  _1 = std::integral_constant<int, 1>;
    using  _2 = std::integral_constant<int, 2>;
    
    template<class ...T> struct vector{};
    
    using mass      = vector<_1, _0, _0, _0, _0, _0, _0>;
    using length    = vector<_0, _1, _0, _0, _0, _0, _0>;
    using time      = vector<_0, _0, _1, _0, _0, _0, _0>;
    
    using velocity  = vector<_1, _1, _0, _0, _0, _0, _0>;
    
    template<class... T>
    struct plus_impl {};
    
    template<class T, T v1, T v2>
    struct plus_impl<std::integral_constant<T, v1>, std::integral_constant<T, v2>> : std::integral_constant<T, v1 + v2>{};
    
    template<class... T>
    struct vector_add_impl{};
    
    template<template<typename...> class Seq1, template<typename...> class Seq2, typename... Args1, typename... Args2>
    struct vector_add_impl<Seq1<Args1...>, Seq2<Args2...>> {
        using type = vector<plus_impl<Args1, Args2>...>;
    };
    
    template<class T1, class T2>
    using vector_add = typename vector_add_impl<T1, T2>::type;
    
    template<class T1, class T2>
    struct minus : std::integral_constant<typename T1::value_type, T1::value - T2::value>{};
}

//int main() {
//    static_assert(kr::plus_impl<kr::_1, kr::_1>::value == 2, "");
//
//    using t = kr::vector_add<kr::mass, kr::length>;
//
//    static_assert(std::is_same<t, kr::velocity>::value == 0, "");
//
//    static_assert(brigand::at<t, std::integral_constant<int, 2>>::value == 0, "");
//}

