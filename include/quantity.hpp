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
#include "krypton.hpp"

BEGIN_KR_NAMESPACE

template<class T>
struct iso_traits {
    using value_type = T;
};

template<class T, class Dim, class Ratio = std::ratio<1>, class Traits = iso_traits<T>>
class quantity {
public:
    using value_type = typename Traits::value_type;
    using dim_type = Dim;
    using ration_type = Ratio;
    using normalized_type = quantity<T, Dim, std::ratio<1>, Traits>;
    using reference = quantity&;
    
public:
    value_type  value;
    
    inline value_type normalized_value() {
        return static_cast<value_type>(value *
               static_cast<double>(ration_type::type::num) /
               static_cast<double>(ration_type::type::den));
    }
    
public:
    quantity() : value(T{}) {}
    explicit quantity(T val) : value(val) {}
    
    template<class Ratio2>
    quantity(const quantity<T, Dim, Ratio2, Traits>& other) {
        T val = other.normalize().value;
        
    }
	
    normalized_type normalize() {
        return normalized_type{normalized_value()};
    };
};



END_KR_NAMESPACE


#endif /* quantity_h */
