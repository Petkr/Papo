#pragma once
#include "apply_template.hpp"
#include "apply_transform.hpp"
#include "concepts/reference.hpp"
#include "copy_cvref.hpp"
#include "decompose_template.hpp"
#include "empty.hpp"
#include "empty_iterator.hpp"
#include "get_value.hpp"
#include "remove_cvref.hpp"
#include "remove_pointer.hpp"
#include "size_t.hpp"
#include "transform_view.hpp"
#include "tuple.hpp"
#include "value_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		struct array_wrap
		{
			T obj;
		};
		
		template <typename T, typename C>
		struct array_impl
		{
			array_wrap<T> buffer[-type<C>];
		};

		template <typename T, typename C>
		struct array : public PP_GET_TYPE([]
			(concepts::type auto t, concepts::type auto type_count)
			{
				if constexpr (-PP_COPY_TYPE(type_count) == 0)
					return type<empty>;
				else
					return Template<array_impl>(t, type_count);
			}(type<T>, type<C>))
		{
			using type = T;
			static constexpr auto value = -PP::type<C>;

			constexpr auto element(concepts::value auto) const noexcept
			{
				return PP::type<T>;
			}
			constexpr auto tuple_count() const noexcept
			{
				return PP::value<value>;
			}
			constexpr auto&& operator[](size_t i) &;
			constexpr auto&& operator[](size_t i) const&;
			constexpr auto&& operator[](size_t i) &&;
			constexpr auto&& operator[](size_t i) const&&;
			constexpr auto&& operator[](concepts::value auto i) &
			{
				return (*this)[*i];
			}
			constexpr auto&& operator[](concepts::value auto i) const&
			{
				return (*this)[*i];
			}
			constexpr auto&& operator[](concepts::value auto i) &&
			{
				return move(*this)[*i];
			}
			constexpr auto&& operator[](concepts::value auto i) const&&
			{
				return move(*this)[*i];
			}

			constexpr auto data()
			requires (!concepts::reference<T>)
			{
				return &this->buffer->obj;
			}
			constexpr auto data() const
			requires (!concepts::reference<T>)
			{
				return (const T*)&this->buffer->obj;
			}
		};
		array() -> array<char, value_t<0>>;
		template <typename T, typename... U>
		array(T, U...) -> array<T, value_t<sizeof...(U) + 1>>;

		template <typename T>
		concept PParray = type<T>->Template == Template<array>;

		constexpr auto begin(PParray auto&& a) noexcept
		{
			constexpr auto array_type = PP_DECLTYPE(a);
			constexpr auto array_type_no_cvref = ~array_type;
			constexpr auto result_type = copy_cvref(array_type, get_type(array_type_no_cvref));

			if constexpr (-array_type_no_cvref != 0)
				return +a.buffer & transform([](auto&& wrap) -> auto&& { return PP_COPY_TYPE(result_type)(wrap.obj); });
			else
				return Template<empty_iterator>(result_type)();
		}
		constexpr auto end(PParray auto&& a) noexcept
		{
			return begin(PP_FORWARD(a)) + a.value;
		}

		template <typename T, typename C> constexpr auto&& array<T, C>::operator[](size_t i) & { return begin(*this)[i]; }
		template <typename T, typename C> constexpr auto&& array<T, C>::operator[](size_t i) const& { return begin(*this)[i]; }
		template <typename T, typename C> constexpr auto&& array<T, C>::operator[](size_t i) && { return begin(move(*this))[i]; }
		template <typename T, typename C> constexpr auto&& array<T, C>::operator[](size_t i) const&& { return begin(move(*this))[i]; }
	}

	template <typename T, size_t count>
	using array = detail::array<T, value_t<count>>;

	PP_FUNCTOR(make_array_pack, auto&&... args)
	{
		return detail::array{ PP_FORWARD(args)... };
	}};
}
