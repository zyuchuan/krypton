//
//  area.hpp
//  krypton
//
//  Created by Jack Zou on 2018/4/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef area_h
#define area_h

#include "core/common.hpp"
#include "core/quantity.hpp"

BEGIN_KR_NAMESPACE

using square_milli = std::ratio<1, 1000 * 1000>;
using square_centi = std::ratio<1, 100 * 100>;
using square_kilo  = std::ratio<1000 * 1000, 1>;

template<class T> using square_meter = quantity<T, area>;
template<class T> using square_centimeter = quantity<T, area, square_centi>;
template<class T> using square_millimeter = quantity<T, area, square_milli>;
template<class T> using square_kilometer = quantity<T, area, square_kilo>;

// british system
template<class T> using square_mile = quantity<T, area, std::ratio<5280 * 5280>, british_system<area>>;
template<class T> using square_foot = quantity<T, area, std::ratio<1>, british_system<area>>;
template<class T> using square_inch = quantity<T, area, std::ratio<1, 12 * 12>, british_system<area>>;

END_KR_NAMESPACE

#endif /* area_h */
