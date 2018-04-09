//
//  volume.hpp
//  krypton
//
//  Created by Jack Zou on 2018/4/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef volume_h
#define volume_h

#include "core/common.hpp"
#include "core/quantity.hpp"

BEGIN_KR_NAMESPACE

using cubic_milli = std::ratio<1, 1000* 1000 * 1000>;
using cubic_centi = std::ratio<1, 100 * 100 * 100>;
using cubic_kilo  = std::ratio<1000 * 1000 * 1000, 1>;

template<class T> using cubic_meter = quantity<T, volume>;
template<class T> using cubic_centimeter = quantity<T, volume, cubic_centi>;
template<class T> using cubic_millimeter = quantity<T, volume, cubic_milli>;
template<class T> using cubic_kilometer = quantity<T, volume, cubic_kilo>;

// british system
template<class T> using cubic_mile = quantity<T, volume, std::ratio<5280 * 5280 * 5280>, british_system<volume>>;
template<class T> using cubic_foot = quantity<T, volume, std::ratio<1>, british_system<volume>>;
template<class T> using cubic_inch = quantity<T, volume, std::ratio<1, 12 * 12 * 12>, british_system<volume>>;

END_KR_NAMESPACE

#endif /* volume_h */
