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

//********************************

BEGIN_KR_NAMESPACE

using kr_int_t = int;

// No defination here, leave it
// to specific types
template<class... T>
struct plus;
    
END_KR_NAMESPACE

#endif /* krypton_h */
