//
//  quantity.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/7.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef quantity_h
#define quantity_h

#include <ratio>
#include "krypton.hpp"
#include "dimension.hpp"
#include "traits.hpp"

BEGIN_KR_NAMESPACE

// forward declare
template<class T, class Dim, class Ratio = std::ratio<1>, class Traits = iso_traits<Dim>>
class quantity;

template<class T>
struct is_quantity : public std::false_type {};

template<class T, class Dim, class Ratio, class Traits>
struct is_quantity<quantity<T, Dim, Ratio, Traits>> : public std::true_type{};

template<class T, class Dim, class Ratio, class Traits>
struct is_quantity<const quantity<T, Dim, Ratio, Traits>> : public std::true_type{};

template<class T, class Dim, class Ratio, class Traits>
struct is_quantity<volatile quantity<T, Dim, Ratio, Traits>> : public std::true_type{};

template<class T, class Dim, class Ratio, class Traits>
struct is_quantity<const volatile quantity<T, Dim, Ratio, Traits>> : public std::true_type{};

template<class T1, class T2>
struct common_type : public std::false_type {};

#if defined(__clang__)
template<class T1, class Dim, class Ratio1, class T2, class Ratio2, class Traits>
struct common_type<quantity<T1, Dim, Ratio1, Traits>, quantity<T2, Dim, Ratio2, Traits>> {
    using type = quantity<typename std::common_type<T1, T2>::type,
                          Dim,
                          typename std::__ratio_gcd<Ratio1, Ratio2>::type,
                          Traits>;
};
#elif defined(_MSC_VER)
template<class T1, class Dim, class Ratio1, class T2, class Ratio2, Traits>
struct common_type<quantity<T1, Dim, Ratio1, Traits>, quantity<T2, Dim, Ratio2, Traits>> {
	using type = quantity<typename std::common_type<T1, T2>::type,
                          Dim,
                          typename std::_Gcd<Ratio1, Ratio2>::type,
                          Traits>;
};
#endif


namespace detail {
    template<class From, class To,
             class Ratio = typename std::ratio_divide<typename From::Ratio, typename To::Ratio>::type,
             bool TraitsEqual = kr::equals<typename From::Traits, typename To::Traits>::value,
             bool = Ratio::num == 1,
             bool = Ratio::den == 1>
    struct quantity_cast_impl;
    
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, true, true> {
        inline constexpr To operator()(const From& from) const {
            return To(static_cast<typename To::T>(from.value));
        }
    };
    
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, true, false> {
        inline constexpr To operator()(const From& from) const {
            using type = typename std::common_type<typename To::T, typename From::T, intmax_t>::type;
            return To(static_cast<typename To::Ratio>(
                      static_cast<type>(from.value) / static_cast<type>(Ratio::den)));
        }
    };
    
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, false, true> {
        inline constexpr To operator()(const From& from) const {
            using type = typename std::common_type<typename To::T, typename From::T, intmax_t>::type;
            return To(static_cast<typename To::T>(static_cast<type>(from.value) * static_cast<type>(Ratio::num)));
        }
    };
    
    template<class From, class To, class Ratio>
    struct quantity_cast_impl<From, To, Ratio, true, false, false> {
        inline constexpr To operator()(const From& from) const {
            using type = typename std::common_type<typename To::T, typename From::T, intmax_t>::type;
            return To(static_cast<typename To::T>(static_cast<type>(from.value) * static_cast<type>(Ratio::num) /
                                                  static_cast<type>(Ratio::den)));
        }
    };
}

template<class To, class U, class Ratio>
inline constexpr typename std::enable_if<is_quantity<To>::value, To>::type
quantity_cast(const quantity<U, Ratio>& other) {
    return detail::quantity_cast_impl<quantity<U, Ratio>, To>()(other);
}

template<class T, class Dim, class Ratio, class Traits>
class quantity {
    static_assert(!is_quantity<T>::value, "A quantity can not be value type of another quantity");
    static_assert(is_dimension<Dim>::value, "Second template parameter of quantity must be a kr::dimension");

#if defined(__clang__)
	static_assert(std::__is_ratio<Ratio>::value, "Third template parameter of quantity must be a std::ratio");
#elif defined(_MSC_VER)
	static_assert(std::_Is_ratio_v<Ratio>, "Third template parameter of quantity must be a std::ratio");
#endif // defined(__clang__)

    
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

        static const constexpr intmax_t n1 = R1::num / gcd_d1_d2;
        static const constexpr intmax_t d1 = R1::den / gcd_d1_d2;
        static const constexpr intmax_t n2 = R2::num / gcd_d1_d2;
        static const constexpr intmax_t d2 = R2::den / gcd_d1_d2;
        static const intmax_t max = -((intmax_t(1) << (sizeof(intmax_t) * __CHAR_BIT__ - 1)) + 1);

        template<intmax_t X, intmax_t Y, bool overflow>
        struct mul {
            static const constexpr intmax_t value = X * Y;
        };

        template<intmax_t X, intmax_t Y>
        struct mul<X, Y, true> {
            static const constexpr intmax_t value = 1;
        };

    public:
        static const constexpr bool value = (n1 <= max / d2) && (n2 << max / d1);
        using type = std::ratio<mul<n1, d2, !value>::value, mul<n2, d1, !value>::value>;
    };

public:
    using value_type = T;
    using dim_type = Dim;
    using ratio_type = Ratio;
    using traits_type = Traits;
    
    using normalized_type = quantity<T, Dim, std::ratio<1>, Traits>;
    using reference = quantity&;

    const value_type  value;

public:

    //value_type value() {return _value;}

    inline value_type normalized_value() {
        return static_cast<value_type>(value *
               static_cast<double>(ratio_type::type::num) /
               static_cast<double>(ratio_type::type::den));
    }

public:
    template<class U>
    explicit quantity(const U& u,
                      typename std::enable_if
                      <
                        std::is_convertible<U, T>::value &&
                       (std::is_floating_point<T>::value || !std::is_floating_point<U>::value)>::type* = 0) : value(u){}

    template<class U, class Ratio2>
    quantity(const quantity<U, Ratio2>& other,
             typename std::enable_if
            <
                no_overflow<Ratio2, Ratio>::value &&
                (std::is_floating_point<T>::value ||
                (no_overflow<Ratio2, Ratio>::type::den == 1 && !std::is_floating_point<U>::value))
             >::type* = 0) {

    }

    normalized_type normalize() {
        return normalized_type{normalized_value()};
    };
};

template<class T> using meter = quantity<T, length>;
template<class T> using kilometer = quantity<T, length, std::kilo>;

template<class T> using feet = quantity<T, length, std::ratio<1>, eng_traits<length>>;
template<class T> using inch = quantity<T, length, std::ratio<1, 12>, eng_traits<length>>;

//template<class T> using second = quantity<T, time>;
//template<class T> using hour = quantity<T, time, std::ratio<3600>>;


END_KR_NAMESPACE


#endif /* quantity_h */
