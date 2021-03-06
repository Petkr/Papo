#pragma once
#include "remove_const.hpp"
#include "same.hpp"

namespace PP
{
	PP_FUNCTOR(is_const, concepts::type auto t)
	{
		return remove_const(t) != t;
	});
}
