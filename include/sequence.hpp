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

template<class E1, class... Args1, class E2, class... Args2>
struct equals<sequence<E1, Args1...>, sequence<E2, Args2...>> {
    static constexpr int value = equals<E1, E2>::value && equals<sequence<Args1...>, sequence<Args2...>>::value;
};

template<class Arg1, class Arg2>
struct equals<sequence<Arg1>, sequence<Arg2>> {
    static constexpr int value = equals<Arg1, Arg2>::value;
};

template<class...Args1, class...Args2>
struct plus<sequence<Args1...>, sequence<Args2...>> {
    using type = sequence<typename plus<Args1, Args2>::type ...>;
};

template<class...Args1, class...Args2>
struct minus<sequence<Args1...>, sequence<Args2...>> {
    using type = sequence<typename minus<Args1, Args2>::type ...>;
};


END_KR_NAMESPACE


#endif /* sequence_h */
