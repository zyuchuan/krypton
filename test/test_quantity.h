//
//  test_integers.cpp
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include "quantity.hpp"
#include "dimensions.hpp"
#include <iostream>

void test_quantity(){
	kr::quantity<double, kr::velocity> m_per_s(5.0);
	
	kr::quantity<double, kr::velocity, std::ratio<1000, 3600>> km_per_h(3.6);
	std::cout << km_per_h.nominal() << ", " << km_per_h.actual() << std::endl;
}
