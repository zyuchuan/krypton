//
//  system.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/11.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef system_h
#define system_h

#include <ratio>
#include "common.hpp"

BEGIN_KR_NAMESPACE

// forward declaration
template<class T>
struct metric_system;

template<class T>
struct british_system;

template<class T>
struct metric_system {
    // rebind metric_system<T> to metric_system<U>
    template<class U>
    struct rebind {
        using other = metric_system<U>;
    };
};

template<class T>
struct british_system {
    template<class U>
    struct rebind {
        using other = british_system<U>;
    };
};

template<class From, class To>
struct unit_converter {
    using ratio = std::ratio<1>;
};

template<>
struct unit_converter<metric_system<length>, british_system<length>> {
    using ratio = std::ratio<32808399, 10000000>;
};

template<>
struct unit_converter<british_system<length>, metric_system<length>> {
    using ratio = std::ratio<10000000, 32808399>;
};

template<>
struct unit_converter<metric_system<velocity>, british_system<velocity>> {
    using ratio = std::ratio<32808399, 10000000>;
};

template<>
struct unit_converter<british_system<velocity>, metric_system<velocity>> {
    using ratio = std::ratio<10000000, 32808399>;
};


// equals test if two metric as same

template<class Dim1, class Dim2>
struct equals<metric_system<Dim1>, metric_system<Dim2>> : public std::integral_constant<bool, equals<Dim1, Dim2>::value>{};

template<class Dim1, class Dim2>
struct equals<british_system<Dim1>, british_system<Dim2>> : public std::integral_constant<bool, equals<Dim1, Dim2>::value>{};

// equal_metric tests if two metrics belong to same system
template<class M1, class M2>
struct system_equals : public std::false_type {};

template<class Dim1, class Dim2>
struct system_equals<metric_system<Dim1>, metric_system<Dim2>> : public std::true_type {};

template<class Dim1, class Dim2>
struct system_equals<british_system<Dim1>, british_system<Dim2>> : public std::true_type {};


END_KR_NAMESPACE

#endif /* system_h */
