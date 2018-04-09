//
//  time.hpp
//  krypton
//
//  Created by Jack Zou on 2018/4/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef time_h
#define time_h

#include <ratio>
#include "core/common.hpp"
#include "core/quantity.hpp"

BEGIN_KR_NAMESPACE

template<class T> using nanosecond  = quantity<T, time, std::nano>;
template<class T> using microsecond = quantity<T, time, std::micro>;
template<class T> using millisecond = quantity<T, time, std::milli>;
template<class T> using second      = quantity<T, time>;
template<class T> using minute      = quantity<T, time, std::ratio<60>>;
template<class T> using hour        = quantity<T, time, std::ratio<3600>>;
template<class T> using day         = quantity<T, time, std::ratio<24 * 3600>>;

END_KR_NAMESPACE


#endif /* time_h */
