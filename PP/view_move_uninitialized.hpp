#pragma once
#include "functional/apply_partially.hpp"
#include "functional/applier.hpp"
#include "functional/operators.hpp"
#include "utility/move.hpp"
#include "view_for_each.hpp"
#include "zip_view.hpp"

namespace PP
{
	constexpr inline auto view_move_uninitialized = view_for_each * *functor([]
		(auto&& to, auto&& from)
		{
			construct_at_pack(&to, move(from));
		}) | zip_view_pack;
}
