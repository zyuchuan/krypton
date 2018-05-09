//
//  quantity_static_check.h
//  krypton
//
//  Created by Jack Zou on 2018/5/9.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef quantity_static_check_h
#define quantity_static_check_h

#include "core/quantity.hpp"
#include "length.hpp"
#include "time.hpp"

void quantity_static_check() {
    
    // this should no compile, initializing a quantity<int> with a
    // floating point number is not allowed
    //kr::quantity<int, kr::length> q1(1.0);
    
    // these should compile
    kr::quantity<float, kr::length> q2(2);
    kr::quantity<float, kr::length> q3(3.0);
    
    using Q1 = kr::quantity<int, kr::length, std::ratio<100, 1>>;
    using Q2 = kr::quantity<double, kr::length, std::ratio<1000, 1>>;
    using common_type = kr::common_type<Q1, Q2>::type;
    static_assert(kr::is_quantity<common_type>::value, "Common type of two quantity types must be a quantity type");
    using ratio_type = common_type::ratio_type;
    static_assert(ratio_type::num == 100, "there are errors in kr::common_type implementation");
    static_assert(ratio_type::den == 1, "there are errors in kr::common_type implementation");
    
    using Q3 = kr::quantity<int, kr::length, std::ratio<100, 33>>;
    using Q4 = kr::quantity<double, kr::length, std::ratio<100, 99>>;
    using common_type_2 = kr::common_type<Q3, Q4>::type;
    static_assert(kr::is_quantity<common_type_2>::value, "Common type of two quantity types must be a quantity type");
    using ratio_type_2 = common_type_2::ratio_type;
    static_assert(ratio_type_2::num == 100, "there are errors in kr::common_type implementation");
    static_assert(ratio_type_2::den == 99, "there are errors in kr::common_type implementation");
    
    using Q5 = kr::quantity<int, kr::length, std::ratio<100, 66>>;
    using Q6 = kr::quantity<double, kr::length, std::ratio<100, 99>>;
    using common_type_3 = kr::common_type<Q5, Q6>::type;
    static_assert(kr::is_quantity<common_type_3>::value, "Common type of two quantity types must be a quantity type");
    using ratio_type_3 = common_type_3::ratio_type;
    static_assert(ratio_type_3::num == 50, "there are errors in kr::common_type implementation");
    static_assert(ratio_type_3::den == 99, "there are errors in kr::common_type implementation");
    
    using Q7 = kr::quantity<int, kr::length, std::ratio<100, 66>, kr::metric_system<kr::length>>;
    using Q8 = kr::quantity<int, kr::length, std::ratio<100, 99>, kr::british_system<kr::length>>;
    using common_type_4 = kr::common_type<Q7, Q8>::type;
}

void quantity_static_check2() {
    using m1 = kr::meter<double>;
    using m2 = kr::meter<int>;
    using s1 = kr::second<int>;
    using s2 = kr::hour<double>;
    
    static_assert(kr::detail::dimension_equal<m1, m2>::value, "They are equal in dimension");
    static_assert(!kr::detail::dimension_equal<m1, s1>::value, "They are not equal in dimension");
    static_assert(kr::detail::dimension_equal<s1, s2>::value, "They are equal in dimension");
    static_assert(!kr::detail::dimension_equal<s2, m2>::value, "They are not equal in dimension");
}


#endif /* quantity_static_check_h */
