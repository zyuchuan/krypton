//
//  quantity.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef quantity_h
#define quantity_h

#include <ratio>

BEGIN_KR_NAMESPACE

template<class T>
struct iso_traits {
    using value_type = T;
};

template<class T, class Dim, class Ratio = std::ratio<1>, class Traits = iso_traits<T>>
struct quantity {
    using value_type = typename Traits::value_type;
    using dim_type = Dim;
    using ration_type = Ratio;
    
    value_type  value;
    
    quantity() : value(T{}) {}
    explicit quantity(T val) : value(val) {}
    
};



END_KR_NAMESPACE


#endif /* quantity_h */
