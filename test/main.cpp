//
//  main.cpp
//  krypton
//
//  Created by Jack Zou on 2018/3/5.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include "test_sequence.h"
#include "test_integers.h"
#include "test_dimension.h"
#include "test_ratio.h"

int main() {
    //test_sequence();
    //test_integers();
    
    //test_dimension();
    
    using m_per_s = std::ratio<1,1>;
    using km_per_h = std::ratio<1000, 3600>;
    
    using t = std::ratio_divide<m_per_s, km_per_h>::type;
    std::cout << t::num << ", " << t::den << std::endl;
}
