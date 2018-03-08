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
class quantity {
public:
    using value_type = typename Traits::value_type;
    using dim_type = Dim;
    using ration_type = Ratio;
    
private:
    value_type  value;
    
public:
    quantity() : value(T{}) {}
    explicit quantity(T val) : value(val) {}

	// nominal() returns the value that defines this quantity
	inline value_type nominal() { return value; }

	// actual() returns the actual value that considers both nominal value and ratio
	inline value_type actual() {
		return static_cast<value_type>(nominal() * static_cast<double>(ration_type::type::num) / static_cast<double>(ration_type::type::den));
	}
};



END_KR_NAMESPACE


#endif /* quantity_h */
