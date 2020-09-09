#pragma once
#include <type_traits>
#include "ref_qualifier.hpp"
#include "get_type.hpp"

namespace PP
{
	namespace detail
	{
		template <ref_qualifier cv, typename T>
		constexpr auto add_ref_helper() noexcept
		{
			if constexpr (std::is_void_v<T> || cv == ref_qualifier::none)
				return type_t<T>{};
			else if constexpr (cv == ref_qualifier::lvalue)
				return type_t<T&>{};
			else
				return type_t<T&&>{};
		}
	}

	template <ref_qualifier ref, typename T>
	using add_ref = get_type<decltype(detail::add_ref_helper<ref, T>())>;
}
