//
//  main.cpp
//  krypton
//
//  Created by Jack Zou on 2018/3/3.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include <iostream>
#include <boost/hana/integral_constant.hpp>

namespace hana = boost::hana;

int main() {
    
    hana::integral_constant<int, 0>{};
    
    std::cout << "hello world!" << std::endl;
}
