//
//  sequence.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/5.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef sequence_h
#define sequence_h

#include "krypton.hpp"

BEGIN_KR_NAMESPACE

// Most fundamental type for type calculation
template<class... T> struct sequence{};

// Type traits
template<class T>
struct is_sequence : public std::false_type {};

template<class... Args>
struct is_sequence<sequence<Args...>> : public std::true_type {};


template<class...Args1, class...Args2>
struct plus<sequence<Args1...>, sequence<Args2...>> {
    using type = sequence<plus<Args1, Args2>...>;
};


END_KR_NAMESPACE


#endif /* sequence_h */
