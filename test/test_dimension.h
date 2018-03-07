//
//  test_dimension.cpp
//  krypton
//
//  Created by Jack Zou on 2018/3/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include "dimensions.hpp"
#include <iostream>

void test_dimension() {
    kr::meter<double> m(5.0);
    kr::meter<int> m1;
    
    std::cout << m.value << ", " << m1.value << std::endl;
}
