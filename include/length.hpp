//
//  unit.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/26.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef unit_h
#define unit_h

#include "common.hpp"
#include "quantity.hpp"

BEGIN_KR_NAMESPACE

//template<class T> using kilogram = quantity<T, mass>;
//template<class T> using gram = quantity<T, mass, std::milli>;
//
//template<class T> using millimeter = quantity<T, length, std::milli>;
//template<class T> using centimeter = quantity<T, length, std::centi>;
//template<class T> using meter = quantity<T, length>;
//template<class T> using kilometer = quantity<T, length, std::kilo>;
//
//template<class T> using mile = quantity<T, length, std::ratio<5280>, british_system<length>>;
//template<class T> using feet = quantity<T, length, std::ratio<1>, british_system<length>>;
//template<class T> using inch = quantity<T, length, std::ratio<1, 12>, british_system<length>>;
//
//template<class T> using second = quantity<T, time>;
//template<class T> using hour = quantity<T, time, std::ratio<3600>>;
//
//template<class T> using m_per_s = quantity<T, velocity>;
//template<class T> using km_per_h = quantity<T, velocity, std::ratio<1000, 3600>>;
//
//template<class T> using ft_per_s = quantity<T, velocity, std::ratio<1>, british_system<velocity>>;
//template<class T> using ml_per_h = quantity<T, velocity, std::ratio<5280, 3600>, british_system<velocity>>;

// https://en.wikipedia.org/wiki/List_of_physical_quantities

/******************************************************
 *
 *  yocto    std::ratio<1, 1000000000000000000000000>
 *  zepto    std::ratio<1, 1000000000000000000000>
 *  atto     std::ratio<1, 1000000000000000000>
 *  femto    std::ratio<1, 1000000000000000>
 *  pico     std::ratio<1, 1000000000000>
 *  nano     std::ratio<1, 1000000000>
 *  micro    std::ratio<1, 1000000>
 *  milli    std::ratio<1, 1000>
 *  centi    std::ratio<1, 100>
 *  deci     std::ratio<1, 10>
 *  deca     std::ratio<10, 1>
 *  hecto    std::ratio<100, 1>
 *  kilo     std::ratio<1000, 1>
 *  mega     std::ratio<1000000, 1>
 *  giga     std::ratio<1000000000, 1>
 *  tera     std::ratio<1000000000000, 1>
 *  peta     std::ratio<1000000000000000, 1>
 *  exa      std::ratio<1000000000000000000, 1>
 *  zetta    std::ratio<1000000000000000000000, 1>
 *  yotta    std::ratio<1000000000000000000000000, 1>
 *
 *****************************************************/

// metric system, we define meter as ratio 1
template<class T> using yoctometer = quantity<T, length, std::yocto>;
template<class T> using zeptometer = quantity<T, length, std::zepto>;
template<class T> using attometer = quantity<T, length, std::atto>;
template<class T> using femtometer = quantity<T, length, std::femto>;
template<class T> using picometer = quantity<T, length, std::pico>;
template<class T> using nanometer = quantity<T, length, std::nano>;
template<class T> using nm = nanometer<T>;
template<class T> using micormeter = quantity<T, length, std::micro>;
template<class T> using millimeter = quantity<T, length, std::milli>;
template<class T> using mm = millimeter<T>;
template<class T> using centimeter = quantity<T, length, std::centi>;
template<class T> using cm = centimeter<T>;
template<class T> using decimeter = quantity<T, length, std::deci>;

// we define meter as ratio 1
template<class T> using meter = quantity<T, length, std::ratio<1>>;

template<class T> using m = meter<T>;
template<class T> using decameter = quantity<T, length, std::deca>;
template<class T> using hectometer = quantity<T, length, std::hecto>;
template<class T> using kilometer = quantity<T, length, std::kilo>;
template<class T> using km = kilometer<T>;

// british system
template<class T> using mile = quantity<T, length, std::ratio<5280>, british_system<length>>;
// we define foot as ratio 1
template<class T> using foot = quantity<T, length, std::ratio<1>, british_system<length>>;

template<class T> using inch = quantity<T, length, std::ratio<1, 12>, british_system<length>>;
template<class T> using yard = quantity<T, length, std::ratio<3, 1>, british_system<length>>;

template<class T> using nautical_mile = quantity<T, length, std::ratio<60761155, 10000000>, british_system<length>>;

END_KR_NAMESPACE


#endif /* unit_h */
