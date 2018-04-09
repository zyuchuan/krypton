//
//  mass.hpp
//  krypton
//
//  Created by Jack Zou on 2018/4/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef mass_h
#define mass_h

#include "core/common.hpp"
#include "core/quantity.hpp"

BEGIN_KR_NAMESPACE

template<class T> using microgram	= quantity<T, mass, std::micro>;
template<class T> using gram		= quantity<T, mass>;
template<class T> using kilogram	= quantity<T, mass, std::kilo>;
template<class T> using ton			= quantity<T, mass, std::mega>;

END_KR_NAMESPACE

#endif /* mass_h */
