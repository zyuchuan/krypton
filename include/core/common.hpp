//
//  krypton.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/5.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef krypton_h
#define krypton_h

#include <type_traits>

#define BEGIN_KR_NAMESPACE namespace kr {
#define END_KR_NAMESPACE }

#define NUM_FUNDAMENTAL_DIM     9

//********************************

BEGIN_KR_NAMESPACE


using kr_int_t = int;


// No defination here, leave it
// to specific types
template<class T1, class T2>
struct plus;

template<class T1, class T2>
struct minus;

template<class T1, class T2>
struct multiply;

template<class T1, class T2>
struct divide;

template<class A, class B>
struct equals : public std::false_type {};

template<typename... Args>
constexpr bool all(Args... args) {
	return (... && args);
}

template<typename... Args>
constexpr bool any(Args... args) {
	return (... || args);
}
    

template<typename V, size_t N>
struct accumulate {
	constexpr static int value = V::value + accumulate<V, N - 1>::value;
};

template<typename V>
struct accumulate<V, 1> {
	constexpr static int value = V::value;
};


END_KR_NAMESPACE

#endif /* krypton_h */
