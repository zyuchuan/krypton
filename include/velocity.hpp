//
//  velocity.hpp
//  krypton
//
//  Created by Jack Zou on 2018/4/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef velocity_h
#define velocity_h

#include "core/common.hpp"
#include "core/quantity.hpp"
#include "core/system.hpp"

BEGIN_KR_NAMESPACE

template<class T> using m_per_s     = quantity<T, velocity>;
template<class T> using km_per_h    = quantity<T, velocity, std::ratio<1000, 3600>>;

template<class T> using f_per_s     = quantity<T, velocity, std::ratio<1>, british_system<velocity>>;

END_KR_NAMESPACE

#endif /* velocity_h */
