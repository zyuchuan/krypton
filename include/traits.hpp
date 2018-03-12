//
//  traits.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/11.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef traits_h
#define traits_h

#include <ratio>
#include "krypton.hpp"
#include "dimension.hpp"

BEGIN_KR_NAMESPACE

enum class metrics : int {
  ISO = 1,
  ENG = 2,
};

template<int N>
struct traits_base {
    static const constexpr metrics metric{static_cast<metrics>(N)};
};
    
using iso_traits_base = traits_base<static_cast<int>(metrics::ISO)>;
using eng_traits_base = traits_base<static_cast<int>(metrics::ENG)>;
    
template<class T>
struct iso_traits;

template<class T>
struct eng_traits;

template<>
struct iso_traits<length> : public iso_traits_base {
    using convert_factor = std::ratio<32808399, 10000000>;
};

template<>
struct eng_traits<length> : public eng_traits_base {
    using convert_factor = std::ratio<10000000, 32808399>;
};
    
template<>
struct iso_traits<mass> : public iso_traits_base {
};

template<>
struct eng_traits<mass> : public eng_traits_base {
};
    
template<int N, int M>
struct equals<traits_base<N>, traits_base<M>> : public std::integral_constant<bool, N==M>{};
    
template<class Dim1, class Dim2>
struct equals<iso_traits<Dim1>, iso_traits<Dim2>> : public std::integral_constant<bool, equals<Dim1, Dim2>::value>{};

template<class Dim1, class Dim2>
struct equals<eng_traits<Dim1>, eng_traits<Dim2>> : public std::integral_constant<bool, equals<Dim1, Dim2>::value>{};

END_KR_NAMESPACE

#endif /* traits_h */
