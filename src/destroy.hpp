#pragma once
#include "destroy_at.hpp"
#include "range.hpp"

template <typename R>
requires range_type<R>::v
void destroy(R r)
{
	for (; r; ++r)
		destroy_at(+r);
}