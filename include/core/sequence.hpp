//
//  sequence.hpp
//  krypton
//
//  Created by Jack Zou on 2018/3/5.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#ifndef sequence_h
#define sequence_h

#include "common.hpp"

BEGIN_KR_NAMESPACE

// Most fundamental type for type calculation
template<class... T> struct sequence{};

// Type traits
template<class T>
struct is_sequence : public std::false_type {};

template<class... Args>
struct is_sequence<sequence<Args...>> : public std::true_type {};

template<typename... Args1, typename... Args2>
struct equals<sequence<Args1...>, sequence<Args2...>> {
	static constexpr int value = ((sizeof...(Args1) == sizeof...(Args2)) && all(equals<Args1, Args2>::value...));
};

template<class...Args1, class...Args2>
struct plus<sequence<Args1...>, sequence<Args2...>> {
    using type = sequence<typename plus<Args1, Args2>::type ...>;
};

template<class...Args1, class...Args2>
struct minus<sequence<Args1...>, sequence<Args2...>> {
    using type = sequence<typename minus<Args1, Args2>::type ...>;
};

namespace detail {
    template<class Seq1, class Seq2, int N, bool Overflow = false>
    struct positive_pow_impl {
        using init_type = typename plus<Seq1, Seq2>::type;
        using type = typename positive_pow_impl<init_type, Seq2, N-1, ((N-1)<0)>::type;
    };

    template<class Seq1, class Seq2>
    struct positive_pow_impl<Seq1, Seq2, 0, false> {
        using type = Seq1;
    };
    
    template<class Seq1, class Seq2, int N>
    struct positive_pow_impl<Seq1, Seq2, N, true> {
        using type = Seq1;
    };
    
    template<class Seq1, class Seq2, int N, bool Overflow = false>
    struct negative_pow_impl {
        using init_type = typename minus<Seq1, Seq2>::type;
        using type = typename negative_pow_impl<init_type, Seq2, N + 1, ((N+1)>0)>::type;
    };

	template<class Seq1, class Seq2>
	struct negative_pow_impl<Seq1, Seq2, 0, false> {
		using type = Seq1;
	};
    
    template<class Seq1, class Seq2, int N>
    struct negative_pow_impl<Seq1, Seq2, N, true> {
        using type = Seq1;
    };

	template<class Seq, int N>
	struct positive_pow {
		using init_type = Seq;
		using Seq2 = init_type;
		using type = typename detail::positive_pow_impl<init_type, Seq2, N - 1>::type;
	};

	template<class Seq, int N>
	struct negative_pow {
		using Seq2 = Seq;
		using init_type = typename minus<Seq2, Seq2>::type;
        using type = typename detail::negative_pow_impl<init_type, Seq2, N, (N>0)>::type;
	};
}

template<class T, int N>
struct pow;

template<class... Args, int N>
struct pow<sequence<Args...>, N> {
	using type = std::conditional_t<(N>=0), typename detail::positive_pow<sequence<Args...>, N>::type,
										   typename detail::negative_pow<sequence<Args...>, N>::type>;
};

// This does not compile in XCode 9.2
//template<class... Args, int N>
//using pow_t = typename pow<Args..., N>::type;

template<class... Args1, class... Args2>
struct multiply<sequence<Args1...>, sequence<Args2...>> {
    using type = typename plus<sequence<Args1...>, sequence<Args2...>>::type;
};

//template<class... Args1, class... Args2>
//using multiply_t = typename multiply<Args1..., Args2...>::type;

template<class... Args1, class... Args2>
struct divide<sequence<Args1...>, sequence<Args2...>> {
    using type = typename minus<sequence<Args1...>, sequence<Args2...>>::type;
};

//template<class... Args1, class... Args2>
//using divide_t = typename divide<Args1..., Args2...>::type;

END_KR_NAMESPACE


#endif /* sequence_h */
