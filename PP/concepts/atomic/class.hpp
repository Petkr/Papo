#pragma once
#include "../../functional/functor.hpp"
#include "../../get_type.hpp"
#include "../../templated_dummy.hpp"

namespace PP
{
	PP_FUNCTOR(is_class, concepts::type auto t)
	{
		return requires
		{
			typename detail::templated_dummy<int PP_GET_TYPE(t)::*>;
		};
	});
}
