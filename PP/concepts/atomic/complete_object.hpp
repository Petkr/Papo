#pragma once
#include "../../functional/functor.hpp"
#include "../../get_type.hpp"
#include "../../templated_dummy.hpp"

namespace PP
{
	PP_FUNCTOR(is_complete_object, concepts::type auto t)
	{
		return requires
		{
			typename detail::templated_dummy<PP_GET_TYPE(t)[]>;
		};
	});
}
