#pragma once
#include "range.hpp"
#include "callable.hpp"
template <range_t R, callable<typename R::base_t> F>
void for_each(R r, F f)
{
	for (; r.begin != r.end; ++r.begin)
		f(*r.begin);
}