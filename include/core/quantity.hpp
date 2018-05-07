//
//  quantity.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef quantity_h
#define quantity_h

#if defined (_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4244) // possible loss of data 
#endif

#include "common.hpp"
#include "traits.hpp"
#include "dimension.hpp"
#include "system.hpp"

BEGIN_KR_NAMESPACE


// quantity cast, one quantity can be converted to another,
// if and only if two quantities have same dimension.

namespace detail {

    template<class From, class To,
             class Ratio = typename std::ratio_divide<typename From::ratio_type, typename To::ratio_type>::type,
             bool DimEqual = kr::equals<typename From::dim_type, typename To::dim_type>::value,
             bool UnitEqual = kr::equals<typename From::unit_type, typename To::unit_type>::value,
             bool = (Ratio::num == 1),
             bool = (Ratio::den == 1)>
    struct quantity_cast_impl;
    
    // Ratio::num == 1, Ratio::den == 1, same unit
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, true, true, true> {
        inline constexpr To operator()(const From& from) const {
            return To(static_cast<typename To::value_type>(from.value));
        }
    };

	// Ratio::num == 1, Ratio::den == 1, different unit
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, false, true, true> {
        inline constexpr To operator()(const From& from) const {
            using converter = unit_converter<typename From::unit_type, typename To::unit_type>;
            return To(static_cast<typename To::value_type>(static_cast<double>(from.value * converter::ratio::num)
                                                           / static_cast<double>(converter::ratio::den)));
        }
    };
	
    // Ratio::num == 1, Ratio::den <> 1, same unit
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, true, true, false> {
        inline constexpr To operator()(const From& from) const {
            using type = typename std::common_type<typename To::value_type, typename From::value_type, intmax_t>::type;
            return To(static_cast<typename To::value_type>(
                      static_cast<type>(from.value) / static_cast<type>(Ratio::den)));
        }
    };

    // Ratio::num == 1, Ratio::den <> 1,  different unit
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, false, true, false> {
        inline constexpr To operator()(const From& from) const {
            
            using converter = unit_converter<typename From::unit_type, typename To::unit_type>;
            return To(static_cast<typename To::value_type>(static_cast<double>(from.value * converter::ratio::num) /
                                                           static_cast<double>(Ratio::den * converter::ratio::den)));
        }
    };

    // Ratio::num <> 1, Ration::den == 1, same unit
    // e.g. convert kilometer to meter
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, true, false, true> {
        inline constexpr To operator()(const From& from) const {
            using type = typename std::common_type<typename To::value_type, typename From::value_type, intmax_t>::type;
            return To(static_cast<typename To::value_type>(static_cast<type>(from.value) * static_cast<type>(Ratio::num)));
        }
    };

    // Ratio::num <> 1, Ration::den == 1, different unit
    // e.g. convert kilometer to feet
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, false, false, true > {
        inline constexpr To operator()(const From& from) const {
            using converter = unit_converter<typename From::unit_type, typename To::unit_type>;
            return To(static_cast<typename To::value_type>(
                                                static_cast<double>(from.value * converter::ratio::num * Ratio::num) /
                                                static_cast<double>(converter::ratio::den)));
        }
    };

    // Ratio::num <> 1, Ration::den <> 1, same unit
    // e.g. convert kilometer to centimeter
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, true, false, false> {
        inline constexpr To operator()(const From& from) const {
            using type = typename std::common_type<typename To::value_type, typename From::value_type, intmax_t>::type;
            return To(static_cast<typename To::value_type>(static_cast<type>(from.value) * static_cast<type>(Ratio::num) /
                                                  static_cast<type>(Ratio::den)));
        }
    };

    // Ratio::num <> 1, Ration::den <> 1, different unit
    // e.g. convert kilometer to inch
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, false, false, false> {
        inline constexpr To operator()(const From& from) const {
            using converter = unit_converter<typename From::unit_type, typename To::unit_type>;
            return To(static_cast<typename To::value_type>(static_cast<double>(from.value * converter::ratio::num * Ratio::num) /
                                                           static_cast<double>(Ratio::den * converter::ratio::den)));
        }
    };
    
    // quantity multiplication
    
    template<class Q1, class Q2,
             bool SameSystem = system_equals<typename Q1::unit_type, typename Q2::unit_type>::value>
    struct quantity_multiplication_impl;
    
    // quantity multiplication
    // same system
    template<class Q1, class Q2>
    struct quantity_multiplication_impl<Q1, Q2, true> {
        using result_type = typename quantity_arithmetic_traits<Q1, Q2>::multiplication::result_type;
        inline result_type operator()(const Q1& q1, const Q2& q2) {
            return result_type{q1.normalized().value * q2.normalized().value};
        }
    };
    
    // quantity multiplication
    // different system
    template<class Q1, class Q2>
    struct quantity_multiplication_impl<Q1, Q2, false> {
        using dim_type_2 = typename quantity_arithmetic_traits<Q1, Q2>::dim_type_2;
        using ratio_type_2 = typename quantity_arithmetic_traits<Q1, Q2>::ratio_type_2;
        using unit_type_1 = typename quantity_arithmetic_traits<Q1, Q2>::unit_type_1;
        using rebind_type = quantity<double, dim_type_2, ratio_type_2, unit_type_1>;
        using result_type = typename quantity_arithmetic_traits<Q1, Q2>::multiplication::result_type;
        inline result_type operator()(const Q1& q1, const Q2& q2) {
            rebind_type temp{q2};
            return result_type{q1.normalized().value * temp.normalized().value};
        }
    };

	// quantity division
	template<class Q1, class Q2,
		bool SameSystem = system_equals<typename Q1::unit_type, typename Q2::unit_type>::value>
		struct quantity_division_impl;

	// quantity division
	// same system
	template<class Q1, class Q2>
	struct quantity_division_impl<Q1, Q2, true> {
		using result_type = typename quantity_arithmetic_traits<Q1, Q2>::division::result_type;
		inline result_type operator()(const Q1& q1, const Q2& q2) {
			return result_type{ static_cast<double>(q1.normalized().value) / static_cast<double>(q2.normalized().value) };
		}
	};

	// quantity division
	// different system
	template<class Q1, class Q2>
	struct quantity_division_impl<Q1, Q2, false> {
		using dim_type_2 = typename quantity_arithmetic_traits<Q1, Q2>::dim_type_2;
		using ratio_type_2 = typename quantity_arithmetic_traits<Q1, Q2>::ratio_type_2;
		using unit_type_1 = typename quantity_arithmetic_traits<Q1, Q2>::unit_type_1;
		using rebind_type = quantity<double, dim_type_2, ratio_type_2, unit_type_1>;
		using result_type = typename quantity_arithmetic_traits<Q1, Q2>::division::result_type;
		inline result_type operator()(const Q1& q1, const Q2& q2) {
			rebind_type temp{ q2 };
			return result_type{ static_cast<double>(q1.normalized().value) / static_cast<double>(temp.normalized().value)};
		}
	};
}

template<class To, class U, class Dim, class Ratio, class Traits>
inline constexpr typename std::enable_if
<
    is_quantity<To>::value && equals<Dim, typename To::dim_type>::value, To
>::type
quantity_cast(const quantity<U, Dim, Ratio, Traits>& other) {
    return detail::quantity_cast_impl<quantity<U, Dim, Ratio, Traits>, To>()(other);
}

template<class Q1, class Q2>
inline constexpr
typename std::enable_if<is_quantity<Q1>::value && is_quantity<Q2>::value,
                        typename quantity_arithmetic_traits<Q1, Q2>::multiplication::result_type>::type
quantity_multiply(const Q1& q1, const Q2& q2) {
    return detail::quantity_multiplication_impl<Q1, Q2>()(q1, q2);
}

template<class Q1, class Q2>
inline constexpr
typename std::enable_if<is_quantity<Q1>::value && is_quantity<Q2>::value,
	typename quantity_arithmetic_traits<Q1, Q2>::division::result_type>::type
	quantity_divide(const Q1& q1, const Q2& q2) {
	return detail::quantity_division_impl<Q1, Q2>()(q1, q2);
}

template<class R1, class R2>
struct no_overflow {
private:
#if defined(__clang__)
    static const constexpr intmax_t gcd_n1_n2 = std::__static_gcd<R1::num, R2::num>::value;
    static const constexpr intmax_t gcd_d1_d2 = std::__static_gcd<R1::den, R2::den>::value;
#elif defined(_MSC_VER)
    static const constexpr intmax_t gcd_n1_n2 = std::_Gcd<R1::num, R2::num>::value;
    static const constexpr intmax_t gcd_d1_d2 = std::_Gcd<R1::den, R2::den>::value;
#endif // defined(__clang__)
    
    static const constexpr intmax_t n1 = R1::num / gcd_d1_d2;
    static const constexpr intmax_t d1 = R1::den / gcd_d1_d2;
    static const constexpr intmax_t n2 = R2::num / gcd_d1_d2;
    static const constexpr intmax_t d2 = R2::den / gcd_d1_d2;
    static const constexpr intmax_t max = -((intmax_t(1) << (sizeof(intmax_t) * 8 - 1)) + 1);
    
    template<intmax_t X, intmax_t Y, bool overflow>
    struct mul {
        static const constexpr intmax_t value = X * Y;
    };
    
    template<intmax_t X, intmax_t Y>
    struct mul<X, Y, true> {
        static const constexpr intmax_t value = 1;
    };
    
public:
    static const constexpr bool value = (n1 <= max / d2) && (n2 <= max / d1);
    using type = std::ratio<mul<n1, d2, !value>::value, mul<n2, d1, !value>::value>;
};

template<class T, class Dim, class Ratio, class Unit>
class quantity {
	static_assert(std::is_arithmetic_v<T>, "Template parameter T must be integer or floating point type");
	static_assert(is_dimension<Dim>::value, "Template parameter Dim must be a kr::dimension");

#if defined(__clang__)
	static_assert(std::__is_ratio<Ratio>::value, "Third template parameter of quantity must be a std::ratio");
#elif defined(_MSC_VER)
	static_assert(std::_Is_ratio_v<Ratio>, "Third template parameter of quantity must be a std::ratio");
#endif // defined(__clang__)

	/*
		static_assert(Ratio::num > 0, "Quantity ratio must be positive");

		template<class R1, class R2>
		struct no_overflow {
		private:
	#if defined(__clang__)
			static const constexpr intmax_t gcd_n1_n2 = std::__static_gcd<R1::num, R2::num>::value;
			static const constexpr intmax_t gcd_d1_d2 = std::__static_gcd<R1::den, R2::den>::value;
	#elif defined(_MSC_VER)
			static const constexpr intmax_t gcd_n1_n2 = std::_Gcd<R1::num, R2::num>::value;
			static const constexpr intmax_t gcd_d1_d2 = std::_Gcd<R1::den, R2::den>::value;
	#endif // defined(__clang__)

			static const constexpr intmax_t n1 = R1::num / gcd_n1_n2;
			static const constexpr intmax_t d1 = R1::den / gcd_d1_d2;
			static const constexpr intmax_t n2 = R2::num / gcd_n1_n2;
			static const constexpr intmax_t d2 = R2::den / gcd_d1_d2;
			static const constexpr intmax_t max = -((intmax_t(1) << (sizeof(intmax_t) * 8 - 1)) + 1);

			template<intmax_t X, intmax_t Y, bool overflow>
			struct mul {
				static const constexpr intmax_t value = X * Y;
			};

			template<intmax_t X, intmax_t Y>
			struct mul<X, Y, true> {
				static const constexpr intmax_t value = 1;
			};

		public:
			static const constexpr bool value = (n1 <= max / d2) && (n2 <= max / d1);
			using type = std::ratio<mul<n1, d2, !value>::value, mul<n2, d1, !value>::value>;
		};
	*/

public:
	using value_type = T;
	using dim_type = Dim;
	using ratio_type = Ratio;
	using unit_type = Unit;
	using this_type = quantity;
	using normalized_type = quantity<T, Dim, std::ratio<1>, Unit>;

	//    using normalized_type = quantity<T, Dim, std::ratio<1>, Traits>;
	//    using reference = quantity&;

	const value_type  value;

	inline normalized_type normalized() const {
		return normalized_type{ *this };
	}

	//explicit quantity(T t) : value(t){}

	// construct with a scalar value
	template<class U>
	explicit quantity(U&& u,
		typename std::enable_if
		<
		std::is_convertible<U, T>::value &&
		(std::is_floating_point<T>::value || !std::is_floating_point<U>::value)>::type* = 0)
		: value(std::forward<U>(u)) {}

	// you can construct a quantity from another quantity, as long as
	// two quantities share common dimension
	template<class U, class Ratio2, class Unit2>
	quantity(const quantity<U, Dim, Ratio2, Unit2>& other) :
		value(quantity_cast<quantity>(other).value) {
	}

	template<class U, class Ratio2, class Unit2>
	inline constexpr quantity add(const quantity<U, Dim, Ratio2, Unit2>& other) const {
		quantity temp{ other };
		return quantity(this->value + temp.value);
	}

	template<class U, class Ratio2, class Unit2>
	inline constexpr quantity substract(const quantity<U, Dim, Ratio2, Unit2>& other) const {
		quantity temp{ other };
		return quantity(this->value - temp.value);
	}

	template<class Q>
	inline constexpr
		std::enable_if_t<is_quantity<Q>::value, typename quantity_arithmetic_traits<quantity, Q>::multiplication::result_type>
		multiply(const Q& other) const {
		return quantity_multiply(*this, other);
	}

	template<class S>
	inline constexpr
		std::enable_if_t<std::is_arithmetic_v<S>, typename quantity_arithmetic_traits<quantity, S>::multiplication::result_type>
		multiply(S s) const {
		using value_type = typename quantity_arithmetic_traits<quantity, S>::multiplication::value_type;
		using result_type = typename quantity_arithmetic_traits<quantity, S>::multiplication::result_type;
		return result_type{ static_cast<value_type>(value) * static_cast<value_type>(s) };
	}

	template<class Q>
	typename std::enable_if<is_quantity<Q>::value,
		typename quantity_arithmetic_traits<quantity, Q>::division::result_type>::type
		divide(const Q& other) const {
		return quantity_divide(*this, other);
	}

	template<class S>
	inline constexpr
		std::enable_if_t<std::is_arithmetic_v<S>, typename quantity_arithmetic_traits<quantity, S>::division::result_type>
		divide(S s) const {
		using value_type = typename quantity_arithmetic_traits<quantity, S>::division::value_type;
		using result_type = typename quantity_arithmetic_traits<quantity, S>::division::result_type;
		return result_type{ static_cast<value_type>(value) / static_cast<value_type>(s) };
	}

	// we want quantity to work with STL containers

	template<class T2 class Dim2, class Ratio2, class Unit2, bool dim_equal = equals<Dim, Dim2>::value>
	struct static_equal;

	template<>
	struct static_equal<quantity<T2, Dim2, Ratio2, Unit2>, false> : std::false_type {};

	template<>
	struct static_equal<quantity<T2, Dim2, Ratio2, Unit2>, true> : std::true_type {};

	template<class Q>
	bool equals_impl(const Q& other, std::false_type not_static_equal) const {
		return false;
	}

	template<class Q>
	bool equals_impl(const Q& other, std::true_type static_equal) const {
		quantity temp{ other };
		return (value == temp.value);
	}

	template<class Q>
	inline constexpr
	std::enable_if_t<is_quantity<Q>::value && equals<dim_type, typename Q::dim_type>::value, bool>
	equals(const Q& other) const {
		return equals_impl(other, static_equal<Q>::value);
	}


	//template<class Q>
	//inline constexpr
	//std::enable_if_t<is_quantity<Q>::value && equals<dim_type, typename Q::dim_type>::value, bool>
	//less(const Q& other) const {
	//	quantity temp{ other };
	//	return (value < temp.value);
	//}
};

END_KR_NAMESPACE

template<class T1, class T2, class Dim, class Ratio1, class Ratio2, class Unit1, class Unit2>
inline constexpr kr::quantity<std::common_type_t<T1, T2>, Dim, Ratio1, Unit1>
operator+(const kr::quantity<T1, Dim, Ratio1, Unit1>& lhs, const kr::quantity<T2, Dim, Ratio2, Unit2>& rhs) {
	using value_type = std::common_type_t<T1, T2>;
	using result_type = kr::quantity<value_type, Dim, Ratio1, Unit1>;
	result_type temp{lhs};
    return temp.add(rhs);
}

template<class T1, class T2, class Dim, class Ratio1, class Ratio2, class Unit1, class Unit2>
inline constexpr kr::quantity<std::common_type_t<T1, T2>, Dim, Ratio1, Unit1>
operator-(const kr::quantity<T1, Dim, Ratio1, Unit1>& lhs, const kr::quantity<T2, Dim, Ratio2, Unit2>& rhs) {
    using value_type = std::common_type_t<T1, T2>;
    using result_type = kr::quantity<value_type, Dim, Ratio1, Unit1>;
    result_type temp{lhs};
    return temp.substract(rhs);
}

template<class Q1, class Q2>
inline constexpr
typename std::enable_if_t<kr::is_quantity<Q1>::value && kr::is_quantity<Q2>::value,
typename kr::quantity_arithmetic_traits<Q1, Q2>::multiplication::result_type>
operator *(const Q1& lhs, const Q2& rhs) {
    return lhs.multiply(rhs);
}

template<class T, class Q>
inline constexpr
std::enable_if_t<std::is_arithmetic_v<T> && kr::is_quantity<Q>::value,
    typename kr::quantity_arithmetic_traits<T, Q>::multiplication::result_type>
operator *(T t, const Q& rhs) {
	return rhs.multiply(t);
}

template<class Q, class T>
inline constexpr
std::enable_if_t<std::is_arithmetic_v<T> && kr::is_quantity<Q>::value,
    typename kr::quantity_arithmetic_traits<Q, T>::multiplication::result_type>
operator *(const Q& lhs, T t) {
    return lhs.multiply(t);
}

template<class Q1, class Q2>
inline constexpr
typename std::enable_if_t<kr::is_quantity<Q1>::value && kr::is_quantity<Q2>::value,
typename kr::quantity_arithmetic_traits<Q1, Q2>::division::result_type>
operator /(const Q1& lhs, const Q2& rhs) {
    return lhs.divide(rhs);
}

template<class Q, class T>
inline constexpr
std::enable_if_t<kr::is_quantity<Q>::value && std::is_arithmetic_v<T>,
	typename kr::quantity_arithmetic_traits<Q, T>::division::result_type>
operator /(const Q& lhs, T t) {
	return lhs.divide(t);
}

template<class Q1, class Q2>
inline constexpr
std::enable_if_t<kr::is_quantity<Q1>::value && kr::is_quantity<Q2>::value>, bool>
operator == (cosnt Q1& lhs, const Q2& rhs) {
	return lhs.equals(rhs);
}

//template<class Q1, class Q2>
//inline constexpr
//std::enable_if_t<kr::is_quantity<Q1>::value && kr::is_quantity<Q2>::value, bool>
//operator !=(const Q1& lhs, const rhs) {
//	return !(lhs == rhs);
//}

#if defined (_MSC_VER)
#pragma warning(pop)
#endif

#endif /* quantity_h */
