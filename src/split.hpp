#pragma once
#include "block.hpp"
#include "u_copy.hpp"
#include "next.hpp"
#include "output.hpp"
#include "val_operators.hpp"

template <typename R, typename P>
requires AND<range_type<R>, callable_r<P, bool, range_base<R>>>::v
auto split(R r, P p)
{
	using T = range_base<R>;

	size_t x = 1;

	for (auto i = +r; i != -r; ++i)
	{
		if (p(*i))
			++x;
	}

	block<block<T>> arrays(x);
	range s(arrays);

	x = 0;
	
	range t(+r, +r);

	for (; t.end != r.end; ++t.end)
	{
		if (!p(&t))
			++x;
		else
		{
			construct(+s, x);
			u_copy(t, range(*s));
			t.begin = next(-t);
			x = 0;
			++s;
		}
	}

	construct(+s, x);
	u_copy(t, range(*s));

	return arrays;
}