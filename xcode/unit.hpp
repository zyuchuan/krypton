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
#incldue "quantity.hpp"

BEGIN_KR_NAMESPACE

template<class T> using kilogram = quantity<T, mass>;
template<class T> using gram = quantity<T, mass, std::milli>;

template<class T> using millimeter = quantity<T, length, std::milli>;
template<class T> using centimeter = quantity<T, length, std::centi>;
template<class T> using meter = quantity<T, length>;
template<class T> using kilometer = quantity<T, length, std::kilo>;

template<class T> using mile = quantity<T, length, std::ratio<5280>, british_system<length>>;
template<class T> using feet = quantity<T, length, std::ratio<1>, british_system<length>>;
template<class T> using inch = quantity<T, length, std::ratio<1, 12>, british_system<length>>;

template<class T> using second = quantity<T, time>;
template<class T> using hour = quantity<T, time, std::ratio<3600>>;

template<class T> using m_per_s = quantity<T, velocity>;
template<class T> using km_per_h = quantity<T, velocity, std::ratio<1000, 3600>>;

template<class T> using ft_per_s = quantity<T, velocity, std::ratio<1>, british_system<velocity>>;
template<class T> using ml_per_h = quantity<T, velocity, std::ratio<5280, 3600>, british_system<velocity>>;

END_KR_NAMESPACE


#endif /* unit_h */
