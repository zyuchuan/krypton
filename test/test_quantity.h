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


TEST(test_quantity, test_normalize) {
    kr::quantity<double, kr::length, std::ratio<1000, 3600>> km_per_h{3.6};
    EXPECT_EQ(km_per_h.normalize().value, 1.0);
}


#endif /* test_quantity_h */
