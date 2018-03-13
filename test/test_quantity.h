//
//  test_quantity.h
//  krypton
//
//  Created by Jack Zou on 2018/3/8.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef test_quantity_h
#define test_quantity_h

#include <gtest/gtest.h>
#include "dimension.hpp"
#include "quantity.hpp"

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
    
    using Q7 = kr::quantity<int, kr::length, std::ratio<100, 66>, kr::iso_traits<kr::length>>;
    using Q8 = kr::quantity<int, kr::length, std::ratio<100, 99>, kr::eng_traits<kr::length>>;
    using common_type_4 = kr::common_type<Q7, Q8>::type;
}

TEST(test_quantity, test_quantity_cast) {
    using from_type = kr::quantity<int, kr::length, std::ratio<1>>;
    using to_type = kr::quantity<double, kr::length, std::ratio<1>>;
    
    //static_assert(kr::is_quantity<to_type>::value, "type is not quantity");
    //static_assert(kr::equals<from_type::dim_type, to_type::dim_type>::value, "dimension not equal");
    
    from_type from{1};
    to_type to = kr::quantity_cast<to_type>(from);
    EXPECT_EQ(to.value, 1.0);
}


//TEST(test_quantity, test_normalize) {
    //kr::quantity<double, kr::length, std::ratio<1000, 3600>> km_per_h{3.6};
    //EXPECT_EQ(km_per_h.normalize().value, 1.0);
//}

//TEST(test_quantity, test_construct) {
    //kr::quantity<int, kr::length> q1(3);
    //EXPECT_EQ(q1.value, 3);
    
    // this should not compile
    //kr::quantity<int, kr::mass> q2(3.0);
    //EXPECT_EQ(q1.value, 3.0);
    
    //kr::quantity<double, kr::length> q3(3);
    //EXPECT_EQ(q3.value, 3.0);
//}


#endif /* test_quantity_h */
