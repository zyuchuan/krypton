//
//  traits.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/24.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef traits_h
#define traits_h

#include <ratio>
#include "common.hpp"
#include "utility.hpp"
#include "system.hpp"

BEGIN_KR_NAMESPACE

// forward declare
template<class T, class Dim, class Ratio = std::ratio<1>, class Unit = metric_system<Dim>>
class quantity;

template<class T>
struct is_quantity : public std::false_type {};

template<class T, class Dim, class Ratio, class Unit>
struct is_quantity<quantity<T, Dim, Ratio, Unit>> : public std::true_type{};

template<class T, class Dim, class Ratio, class Unit>
struct is_quantity<const quantity<T, Dim, Ratio, Unit>> : public std::true_type{};

template<class T, class Dim, class Ratio, class Unit>
struct is_quantity<volatile quantity<T, Dim, Ratio, Unit>> : public std::true_type{};

template<class T, class Dim, class Ratio, class Unit>
struct is_quantity<const volatile quantity<T, Dim, Ratio, Unit>> : public std::true_type{};

template<class T1, class T2>
struct common_type : public std::false_type {};


template<class T1, class Dim, class Ratio1, class T2, class Ratio2, class Unit>
struct common_type<quantity<T1, Dim, Ratio1, Unit>, quantity<T2, Dim, Ratio2, Unit>> {
    using type = quantity<typename std::common_type<T1, T2>::type,
    Dim,
    typename ratio_gcd<Ratio1, Ratio2>::type,
    Unit>;
};

template<class Q>
struct quantity_traits {
    using value_type        = typename Q::value_type;
    using dim_type          = typename Q::dim_type;
    using ratio_type        = typename Q::ratio_type;
    using unit_type         = typename Q::unit_type;
};

template<class Q1,
		class Q2,
		bool q1_is_quantity = kr::is_quantity<Q1>::value,
		bool q2_is_quantity = kr::is_quantity<Q2>::value,
		bool q1_is_arithmetic = std::is_arithmetic_v<Q1>,
		bool q2_is_arithmetic = std::is_arithmetic_v<Q2>>
struct quantity_arithmetic_traits;

// Q1 is quantity
// Q2 is quantity
template<class Q1, class Q2>
struct quantity_arithmetic_traits<Q1, Q2, true, true, false, false> {
    using value_type_1      = typename Q1::value_type;
    using value_type_2      = typename Q2::value_type;
    using dim_type_1        = typename Q1::dim_type;
    using dim_type_2        = typename Q2::dim_type;
    using ratio_type_1      = typename Q1::ratio_type;
    using ratio_type_2      = typename Q2::ratio_type;
    using unit_type_1       = typename Q1::unit_type;
    using unit_type_2       = typename Q2::unit_type;
    using normalized_type_1 = typename Q1::normalized_type;
    using normalized_type_2 = typename Q2::normalized_type;

    struct multiplication {
		using value_type = typename std::common_type_t<value_type_1, value_type_2>;
        using dim_type = typename plus<dim_type_1, dim_type_2>::type;
        using ratio_type = std::ratio<1>;
        using unit_type = typename unit_type_1::template rebind<dim_type>::other;
        using result_type = quantity<value_type, dim_type, ratio_type, unit_type>;
    };

	struct division {
		using value_type = typename std::common_type_t<value_type_1, value_type_2>;
		using dim_type = typename minus<dim_type_1, dim_type_2>::type;
		using ratio_type = std::ratio<1>;
		using unit_type = typename unit_type_1::template rebind<dim_type>::other;
		using result_type = quantity<value_type, dim_type, ratio_type, unit_type>;
	};
};

// Q1 is arithmetic: integer of floating point number
// Q2 is quantity
template<class Q1, class Q2>
struct quantity_arithmetic_traits<Q1, Q2, false, true, true, false> {
	using value_type_1 = Q1;
	using value_type_2 = typename Q2::value_type;
	using dim_type = typename Q2::dim_type;
	using ratio_type = typename Q2::ratio_type;
	using unit_type = typename Q2::unit_type;
	using normalized_type = typename Q2::normalized_type;

	struct multiplication {	
		using value_type = typename std::common_type_t<value_type_1, value_type_2>;
		using result_type = quantity<double, dim_type, ratio_type, unit_type>;
	};

	struct division {
		using value_type = typename std::common_type_t<value_type_1, value_type_2>;
		using result_type = quantity<value_type, dim_type, ratio_type, unit_type>;
	};
};

// Q1 is quantity
// Q2 is arimetic: integer of floating point number
template<class Q1, class Q2>
struct quantity_arithmetic_traits<Q1, Q2, true, false, false, true> {
	using value_type_1 = typename Q1::value_type;
	using value_type_2 = Q2;
	using dim_type = typename Q1::dim_type;
	using ratio_type = typename Q1::ratio_type;
	using unit_type = typename Q1::unit_type;
	using normalized_type = typename Q1::normalized_type;

	struct multiplication {
		using value_type = typename std::common_type_t<value_type_1, value_type_2>;
		using result_type = quantity<value_type, dim_type, ratio_type, unit_type>;
	};

	struct division {
		using value_type = typename std::common_type_t<value_type_1, value_type_2>;
		using result_type = quantity<value_type, dim_type, ratio_type, unit_type>;
	};
};

END_KR_NAMESPACE

#endif /* traits_h */
