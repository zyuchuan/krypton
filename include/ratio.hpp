//
//  ratio.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef ratio_h
#define ratio_h

#include <ratio>

namespace std {
    template<class From, class To>
    struct ratio_cast {
        using type = std::ratio_divide<From, To>::type;
    }
}


#endif /* ratio_h */
