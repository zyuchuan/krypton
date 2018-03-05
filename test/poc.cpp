//
//  poc.cpp
//  krypto
//
//  Created by Jack Zou on 2018/3/4.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include <brigand/types/integer.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/algorithms.hpp>
#include <brigand/functions.hpp>
#include <brigand/types/operators.hpp>
#include <iostream>

namespace kr {
    using __2 = brigand::int32_t<-2>;
    using __1 = brigand::int32_t<-1>;
    using  _0 = brigand::int32_t<0>;
    using  _1 = brigand::int32_t<1>;
    using  _2 = brigand::int32_t<2>;

    using mass      = brigand::list<_1, _0, _0, _0, _0, _0, _0>;
    using length    = brigand::list<_0, _1, _0, _0, _0, _0, _0>;
    using time      = brigand::list<_0, _0, _1, _0, _0, _0, _0>;
    
    
    using velocity = brigand::list<_1, _1, _0, _0, _0, _0, _0>;
    
    template<class... T>
    struct list_add_impl {
        
    };
    
    template<template<typename...> class L1, template<typename...> class L2, typename... T1s, typename... T2s>
    struct list_add_impl<L1<T1s...>, L2<T2s...>> {
        using type = brigand::list<brigand::plus<T1s, T2s>...>;
//        using e0L1 = brigand::at<L1<T1s...>, std::integral_constant<int, 0>>;
//        using e0L2 = brigand::at<L2<T2s...>, std::integral_constant<int, 0>>;
//        using e1L1 = brigand::at<L1<T1s...>, std::integral_constant<int, 1>>;
//        using e1L2 = brigand::at<L2<T2s...>, std::integral_constant<int, 1>>;
//        using e2L1 = brigand::at<L1<T1s...>, std::integral_constant<int, 2>>;
//        using e2L2 = brigand::at<L2<T2s...>, std::integral_constant<int, 2>>;
//
//        using type = brigand::list<brigand::plus<e0L1, e0L2>, brigand::plus<e1L1, e2L1>, brigand::plus<e2L1, e2L2>>;
    };
    
    template<class T1, class T2>
    using list_add = typename list_add_impl<T1, T2>::type;
    
    template<class T, class Dimensions>
    struct quantity {
        T value;
        
        explicit quantity(T x) : value(x) {}
    };
    
    template<class T, class D>
    quantity<T, D> operator+(quantity<T, D> x, quantity<T, D> y) {
        return quantity<T, D>(x.value + y.value);
    }
    
    template<class T, class D>
    quantity<T, D> operator-(quantity<T, D> x, quantity<T, D> y) {
        return quantity<T, D>(x.value - y.value);
    }
    
    struct plus_f {
        template<class T1, class T2>
        struct apply {
            typedef typename brigand::plus<T1, T2> type;
        };
    };
    
    struct minus_f {
        template<class T1, class T2>
        struct apply {
            typedef typename brigand::minus<T1, T2> type;
        };
    };
    
//    template<class T, class D1, class D2>
//    quantity<T, typename brigand::transform<D1, D2, plus_f>>
//    operator*(quantity<T, D1> x, quantity<T, D2> y) {
//        using dim = brigand::transform<D1, D2, brigand::plus<D1, D2>>;
//        //return quantity<T, dim>(x.value * y.value);
//    }
    
    template<class T, class D1, class D2>
    quantity<T, list_add<D1, D2>>
    operator*(quantity<T, D1> x, quantity<T, D2> y) {
        using dim = list_add<D1, D2>;
        return quantity<T, dim>(x.value * y.value);
    }
}

//int main() {
//    using namespace kr;
//
//    quantity<float, mass> m{5.0};
//    quantity<float, length> l{5.0};
//
//    //velocity vel{};
//
//    using vel2 = list_add<mass, length>;
//    //std::cout << typeid(vel2).name() << std::endl;
//
//    using e1 = brigand::at<vel2, std::integral_constant<int,2>>;
//    std::cout << e1::value << std::endl;
//
//    using t = brigand::plus<std::integral_constant<int, 1>, std::integral_constant<int, 1>>;
//    std::cout << t::value << std::endl;
//}

