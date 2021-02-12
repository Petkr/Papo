#pragma once
#include "compressed_pair.hpp"
#include "placeholder.hpp"
#include "utility/move.hpp"

namespace PP
{
	template <typename T, typename Destructor>
	class scoped
	{
		template <typename U, typename D>
		friend class scoped;

		compressed_pair<T, Destructor> pair;

	public:
		constexpr scoped() = default;

		template <typename U, typename D>
		constexpr scoped(const scoped<U, D>& other)
			: pair(other.pair.first, other.pair.second)
		{}
		template <typename U, typename D>
		constexpr scoped(scoped<U, D>&& other)
			: pair(move(other).pair.first, move(other).pair.second)
		{}

		constexpr scoped(auto&& value, auto&& destructor)
			: pair(PP_FORWARD(value), PP_FORWARD(destructor))
		{}

		constexpr T& inner()
		{
			return pair.first;
		}
		constexpr const T& inner() const
		{
			return pair.first;
		}
		constexpr Destructor& get_destructor()
		{
			return pair.second;
		}
		constexpr const Destructor& get_destructor() const
		{
			return pair.second;
		}
	private:
		constexpr void destroy()
		{
			get_destructor()(inner());
		}
	public:
		constexpr scoped& operator=(scoped&& other)
		{
			destroy();
			pair = move(other).pair;
			return *this;
		}

		constexpr ~scoped()
		{
			destroy();
		}
	};
	scoped(auto&& v, auto&& d) -> scoped<PP_GET_TYPE(~PP_DECLTYPE(v)), PP_GET_TYPE(~PP_DECLTYPE(d))>;
}
