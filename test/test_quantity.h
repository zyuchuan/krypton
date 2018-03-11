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
#include "dimensions.hpp"
#include "quantity.hpp"

void quantity_static_check() {
    using Q1 = kr::quantity<int, kr::length, std::ratio<100, 1>>;
    using Q2 = kr::quantity<double, kr::length, std::ratio<1000, 1>>;
    
    using common_type = kr::common_type<Q1, Q2>::type;
    static_assert(kr::is_quantity<common_type>::value, "Common type of two quantity types must be a quantity type");
    //using ratio_type = common_type::ratio_type;
}


TEST(test_quantity, test_normalize) {
    //kr::quantity<double, kr::length, std::ratio<1000, 3600>> km_per_h{3.6};
    //EXPECT_EQ(km_per_h.normalize().value, 1.0);
}

TEST(test_quantity, test_construct) {
    //kr::quantity<int, kr::length> q1(3);
    //EXPECT_EQ(q1.value, 3);
    
    // this should not compile
    //kr::quantity<int, kr::mass> q2(3.0);
    //EXPECT_EQ(q1.value, 3.0);
    
    //kr::quantity<double, kr::length> q3(3);
    //EXPECT_EQ(q3.value, 3.0);
}


#endif /* test_quantity_h */
