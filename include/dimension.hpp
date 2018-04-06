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
 * Angle                | r      | radian        | R
 */

/******************************************************************
* Base dimension
* https://en.wikipedia.org/wiki/List_of_physical_quantities
*
* Our world is built upon seven basic units, theoretically seven
* flags is enough to define all these seven units.
* However, things are little complicated when we try to simulate
* real word by programming:
*
*	1. we add one more flag to address angle and radian
*	2. Some compound dimensions share common dimension formula
		with others, like work and moment, both have same
		dimension ML^2T^2, we need one more flag to distinguish
		them.
*
* Hence in krypton, each dimension is defined by nine flags.
*****************************************************************/

using scalar        = sequence<_0, _0, _0, _0, _0, _0, _0, _0, _0>;
using length        = sequence<_1, _0, _0, _0, _0, _0, _0, _0, _0>;
using mass          = sequence<_0, _1, _0, _0, _0, _0, _0, _0, _0>;
using time          = sequence<_0, _0, _1, _0, _0, _0, _0, _0, _0>;
using current       = sequence<_0, _0, _0, _1, _0, _0, _0, _0, _0>;
using temperature   = sequence<_0, _0, _0, _0, _1, _0, _0, _0, _0>;
using substance     = sequence<_0, _0, _0, _0, _0, _1, _0, _0, _0>;
using intensity     = sequence<_0, _0, _0, _0, _0, _0, _1, _0, _0>;
using angle         = sequence<_0, _0, _0, _0, _0, _0, _0, _1, _0>;

using L = length;
using T = time;
using M = mass;

// Compound dimensions
//using velocity                  = sequence<_1, _0, __1, _0, _0, _0, _0, _0>;   // LT^-1
//using acceleration              = sequence<_1, _0, __2, _0, _0, _0, _0, _0>;   // LT^-2
//using force                     = sequence<_1, _1, __2, _0, _0, _0, _0, _0>;   // MLT^-2
//using momentum                  = sequence<_1, _1, __1, _0, _0, _0, _0, _0>;   // MLT^-1
//using work                      = sequence<_2, _1, __2, _0, _0, _0, _0, _1>;   // ML^2T^-2
//using moment                    = sequence<_2, _1, __2, _0, _0, _0, _0, _0>;   // ML^2T^-2
//using angular_velocity          = sequence<_0, _0, __1, _0, _0, _0, _1, _0>;   // T^-1
//using angular_acceleration      = sequence<_0, _0, __2, _0, _0, _0, _1, _0>;   // T^-2
//using moment_of_inertia         = sequence<_2, _1,  _0, _0, _0, _0, _0, _0>;   // ML^2
//using density                   = sequence<__1,_1,  _0, _0, _0, _0, _0, _0>;   // ML^-1

using velocity = divide<L, T>::type;
using acceleration = multiply<L, pow<T, -2>::type>::type;
using force = multiply<multiply<M, L>::type, pow<T, -2>::type>::type;

END_KR_NAMESPACE
#endif /* dimension_h */
