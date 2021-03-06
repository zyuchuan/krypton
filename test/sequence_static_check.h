//
//  sequence_static_check.h
//  krypton
//
//  Created by Jack Zou on 2018/3/5.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef sequence_static_check_h
#define sequence_static_check_h

#include "core/integer.hpp"
#include "core/sequence.hpp"
#include "core/common.hpp"

void sequence_static_check() {
    using seq0 = kr::sequence<int, int, int>;
    
    static_assert(kr::is_sequence<seq0>::value,"seq0 is a sequence");
    //static_assert(kr::is_sequence<int>::value, "int is not a sequence");
    
    // arthimetic operations
    using seq1 = kr::sequence<kr::_1, kr::_1, kr::_1>;
    using seq2 = kr::sequence<kr::_2, kr::_2, kr::_2>;
    using seq3 = kr::sequence<kr::_3, kr::_3, kr::_3>;
    using seqm1 = kr::sequence<kr::__1, kr::__1, kr::__1>;
    using seqm2 = kr::sequence<kr::__2, kr::__2, kr::__2>;
    using seqm3 = kr::sequence<kr::__3, kr::__3, kr::__3>;
    
    static_assert(std::is_same<seq1, kr::sequence<kr::_1, kr::_1, kr::_1>>::value, "is same type");
    //static_assert(std::is_same<seq2, seq1>::value, "is not same type");
    
    static_assert(std::is_same<kr::plus<seq1, seq2>::type, seq3>::value, "is same type");
    
    // static_assert(kr::equals<seq1, seq2>::value, "they are not equal");
    
    using seq = kr::plus<seq1, seq2>::type;
    static_assert(kr::equals<seq, seq3>::value, "should be equal");

    using seqp2 = kr::pow<seq1, 2>::type;
    static_assert(kr::equals<seq2, seqp2>::value, "should be equal");

    using seqp3 = kr::pow<seq1, 3>::type;
    static_assert(kr::equals<seqp3, seq3>::value, "should be equal");
    
    using seqm2m = kr::pow<seq1, -2>::type;
    static_assert(kr::equals<seqm2, seqm2m>::value, "should be equal");
    
    using seqm3m = kr::pow<seq1, -3>::type;
    static_assert(kr::equals<seqm3m, seqm3>::value, "should be equal");
}


#endif // sequence_static_check_h
