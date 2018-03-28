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
struct is_dimension<sequence<Args...>> : public std::integral_constant<bool, sizeof...(Args)==9>{};

/*
 * Base quantity        | Symbol | SI base unit  | Dimension
 * ----------------------------------------------------------
 * Length               | l      | meter (m)     | L
 * Mass                 | m      | kilogram (kg) | M
 * Time                 | t      | second (s)    | T
 * Electric current     | I      | ampere (A)    | I
 * Temperature          | T      | kelvin (K)    | Θ
 * Amount of substance  | n      | mole (mol)    | N
 * Luminous intensity   | L      | candela (cd)  | J
 * ----------------------------------------------------------
 * Angle                | d      | degree (deg)  | A
 * Radian               | R      | radian (rad)  | R
 */

// Base dimension
// https://en.wikipedia.org/wiki/List_of_physical_quantities
// Out world is built upon these seven basic unit
// we add two more here to address Angle and Radian
using scalar        = sequence<_0, _0, _0, _0, _0, _0, _0, _0, _0>;
using length        = sequence<_1, _0, _0, _0, _0, _0, _0, _0, _0>;
using mass          = sequence<_0, _1, _0, _0, _0, _0, _0, _0, _0>;
using time          = sequence<_0, _0, _1, _0, _0, _0, _0, _0, _0>;
using current       = sequence<_0, _0, _0, _1, _0, _0, _0, _0, _0>;
using temperature   = sequence<_0, _0, _0, _0, _1, _0, _0, _0, _0>;
using substance     = sequence<_0, _0, _0, _0, _0, _1, _0, _0, _0>;
using intensity     = sequence<_0, _0, _0, _0, _0, _0, _1, _0, _0>;
using angle         = sequence<_0, _0, _0, _0, _0, _0, _0, _1, _0>;
using radian        = sequence<_0, _0, _0, _0, _0, _0, _0, _0, _1>;

// Compound dimensions
using velocity      = sequence<_1, _0, __1, _0, _0, _0, _0, _0, _0>;   // l/t
using acceleration  = sequence<_1, _0, __2, _0, _0, _0, _0, _0, _0>;   // l/t^2
using force         = sequence<_1, _1, __2, _0, _0, _0, _0, _0, _0>;   // m * l/t^2

END_KR_NAMESPACE
#endif /* dimension_h */
