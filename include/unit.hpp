//
//  unit.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/11.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef unit_h
#define unit_h

#include <ratio>
#include "krypton.hpp"
#include "dimension.hpp"

BEGIN_KR_NAMESPACE

//enum class metrology : int {
//    metric = 1,
//    british = 2,
//    us = 3,
//};

//template<int N>
//struct metrology_base {
//    static constexpr metrology metric{static_cast<metrology>(N)};
//};

//using metric_system_base = metrology_base<static_cast<int>(metrology::metric)>;
//using british_system_base = metrology_base<static_cast<int>(metrology::british)>;

template<class T>
struct metric_system;

template<class T>
struct british_system;

struct metric_system_base {
    //using convert_factor = std::ratio<1>;
    
    // rebind metric_system<T> to metric_system<U>
    template<class U>
    struct rebind {
        using other = metric_system<U>;
    };
};

struct british_system_base {
    template<class U>
    struct rebind {
        using other = british_system<U>;
    };
};

template<class T>
struct british_system : public british_system_base {
    //using dim_type = T;
    using convert_factor = std::ratio<1>;
};

template<>
struct metric_system<length> : public metric_system_base {
    using convert_factor = std::ratio<32808399, 10000000>;
};

template<>
struct british_system<length> : public british_system_base {
    using convert_factor = std::ratio<10000000, 32808399>;
};
    
template<>
struct metric_system<mass> : public metric_system_base {
    using convert_factor = std::ratio<1>;
};

template<>
struct british_system<mass> : public british_system_base {
    using convert_factor = std::ratio<1>;
};
    
template<>
struct metric_system<velocity> : public metric_system_base  {
    using convert_factor = std::ratio<32808399, 10000000>;
};
    
template<>
struct british_system<velocity> : public british_system_base {
    using convert_factor = std::ratio<10000000, 32808399>;
};

// equals test if two metric as same

template<>
struct equals<metric_system_base, metric_system_base> : public std::true_type{};

template<>
struct equals<british_system_base, british_system_base> : public std::true_type{};
    
template<class Dim1, class Dim2>
struct equals<metric_system<Dim1>, metric_system<Dim2>> : public std::integral_constant<bool, equals<Dim1, Dim2>::value>{};

template<class Dim1, class Dim2>
struct equals<british_system<Dim1>, british_system<Dim2>> : public std::integral_constant<bool, equals<Dim1, Dim2>::value>{};

// equal_metric tests if two metrics belong to same system
template<class M1, class M2>
struct metric_equals : public std::false_type {};
    
template<>
struct metric_equals<metric_system_base, metric_system_base> : public std::true_type {};

template<class Dim1, class Dim2>
struct metric_equals<metric_system<Dim1>, metric_system<Dim2>> : public std::true_type {};

template<>
struct metric_equals<british_system_base, british_system_base> : public std::true_type {};

template<class Dim1, class Dim2>
struct metric_equals<british_system<Dim1>, british_system<Dim2>> : public std::true_type {};
    
//template<class T>
//struct is_metric_system : public std::false_type{};
//
//template<class T>
//struct is_metric_system<metric_system<T>> : public std::true_type{};
//    
//template<>
//struct is_metric_system<metric_system_base> : public std::true_type{};
//
//template<class T>
//struct is_british_system : public std::false_type {};
//    
//template<class T>
//struct is_british_system<british_system<T>> : public std::true_type{};
//
//template<>
//struct is_british_system<british_system_base> : public std::true_type{};

END_KR_NAMESPACE

#endif /* unit_h */
