#pragma once
#include "conditional.hpp"

template <typename T>
struct _make_signed_integral
{
	using type = conditional<sizeof(T) == 1, signed char,
				 conditional<sizeof(T) == 2, signed short,
				 conditional<sizeof(T) == 4, signed int,
											 signed long long>>>;
};
template <typename T>
struct _make_signed_integral<const T>
{
	using type = conditional<sizeof(T) == 1, const signed char,
				 conditional<sizeof(T) == 2, const signed short,
				 conditional<sizeof(T) == 4, const signed int,
											 const signed long long>>>;
};
template <typename T>
struct _make_signed_integral<volatile T>
{
	using type = conditional<sizeof(T) == 1, volatile signed char,
				 conditional<sizeof(T) == 2, volatile signed short,
				 conditional<sizeof(T) == 4, volatile signed int,
											 volatile signed long long>>>;
};
template <typename T>
struct _make_signed_integral<const volatile T>
{
	using type = conditional<sizeof(T) == 1, const volatile signed char,
				 conditional<sizeof(T) == 2, const volatile signed short,
				 conditional<sizeof(T) == 4, const volatile signed int,
											 const volatile signed long long>>>;
};
template <typename T>
using make_signed_integral = typename _make_signed_integral<T>::type;