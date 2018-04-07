//
//  traits.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/11.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef utility_h
#define utility_h

#include <ratio>
#include "common.hpp"

BEGIN_KR_NAMESPACE

// std::ratio utilities, import from libc++ ratio implementation
// we import these utilites because there are such funcitons in
// MSVC std::ration

// gcd
template<intmax_t X, intmax_t Y>
struct gcd {
	static const constexpr intmax_t value = gcd<Y, X % Y>::value;
};

template<intmax_t X>
struct gcd<X, 0> {
	static const constexpr intmax_t value = X;
};

template<>
struct gcd<0, 0> {
	static const constexpr intmax_t value = 1;
};

// lcm
template<intmax_t X, intmax_t Y>
struct lcm {
	static const constexpr intmax_t value = X / gcd<X, Y>::value * Y;
};

template<class R1, class R2>
struct ratio_gcd {
	using type = std::ratio<gcd<R1::num, R2::num>::value, lcm<R1::den, R2::den>::value>;
};

END_KR_NAMESPACE

#endif
