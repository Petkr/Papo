#pragma once
#include "range.hpp"
#include "assignable.hpp"

template <typename it, assignable_to<base_t<it>> T = base_t<it>>
void fill(range<it> r, const T& value = T())
{
	for (; r.begin != r.end; ++r.begin)
		*r.begin = value;
}