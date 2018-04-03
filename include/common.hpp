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

#define NUM_FUNDAMENTAL_DIM     8

//********************************

BEGIN_KR_NAMESPACE


using kr_int_t = int;


// No defination here, leave it
// to specific types
template<class... T>
struct plus;

template<class... T>
struct minus;

template<class A, class B>
struct equals : public std::false_type {};
    
END_KR_NAMESPACE

#endif /* krypton_h */
