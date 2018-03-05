//
//  test_dimensions.cpp
//  krypton
//
//  Created by Jack Zou on 2018/3/5.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include <iostream>
#include "sequence.hpp"
#include "integers.hpp"
#include <brigand/sequences/at.hpp>
#include <iostream>

void test_sequence() {
    using seq0 = kr::sequence<int, int, int>;
    
    static_assert(kr::is_sequence<seq0>::value,"seq0 is a sequence");
    //static_assert(kr::is_sequence<int>::value, "int is not a sequence");
    
    // arthimetic operations
    using seq1 = kr::sequence<kr::_1, kr::_1, kr::_1>;
    using seq2 = kr::sequence<kr::_2, kr::_2, kr::_2>;
    using seq3 = kr::sequence<kr::_3, kr::_3, kr::_3>;
    
    static_assert(std::is_same<seq1, kr::sequence<kr::_1, kr::_1, kr::_1>>::value, "is same type");
    //static_assert(std::is_same<seq2, seq1>::value, "is not same type");
    
    //static_assert(std::is_same<kr::plus<seq1, seq2>::type, seq3>::value, "is same type");
    
    using seq = kr::plus<seq1, seq2>::type;
    std::cout << brigand::at<seq, kr::_0>::value << std::endl;
    std::cout << brigand::at<seq, kr::_1>::value << std::endl;
    std::cout << brigand::at<seq, kr::_2>::value << std::endl;
    //std::cout << brigand::at<seq, kr::_3>::value << std::endl;
    
    std::cout << brigand::at<seq3, kr::_0>::value << std::endl;
    std::cout << brigand::at<seq3, kr::_1>::value << std::endl;
    std::cout << brigand::at<seq3, kr::_2>::value << std::endl;
}
