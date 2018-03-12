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

enum class metrics : unsigned int {
  iso = 1,
  eng = 2,
};

template<class T>
struct iso_traits;

template<class T>
struct eng_traits;

template<>
struct iso_traits<length> {
    static const constexpr metrics metric = metrics::iso;
    
    using factor_type = std::ratio<1, 1>;
};

template<>
struct eng_traits<length> {
    static const constexpr metrics metric = metrics::eng;
    
    using factor_type = std::ratio<120, 19>;
};

END_KR_NAMESPACE

#endif /* traits_h */
