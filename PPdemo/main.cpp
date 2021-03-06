#include <iostream>
#include <vector>

#include "PP/cv_decomposition.hpp"
#include "PP/promotion_type.hpp"
#include "PP/value_sequence.hpp"

std::ostream& print_cv(PP::cv_decomposition_element e, std::ostream& out)
{
	switch (e.cv)
	{
	case PP::cv_qualifier::none:
		out << "none";				break;
	case PP::cv_qualifier::Const:
		out << "const";				break;
	case PP::cv_qualifier::Volatile:
		out << "volatile";			break;
	case PP::cv_qualifier::const_volatile:
		out << "const volatile";	break;
	}

	out << " ";

	switch (e.type)
	{
	case PP::cv_decomposition_type::pointer:
		out << "p";				break;
	case PP::cv_decomposition_type::pointer_to_member:
		out << "pm";				break;
	case PP::cv_decomposition_type::array_known:
		out << "ak";			break;
	case PP::cv_decomposition_type::array_unknown:
		out << "au";	break;
	case PP::cv_decomposition_type::none:
		out << "none";	break;
	}

	return out << " " << e.extent;
}

using U = int;

template <typename T>
using ptr = T*;
template <typename T>
using unknown_bound = T[];
template <typename T>
using known_bound = T[1];

using From = ptr<known_bound<const volatile ptr<const U>>>;
using To = ptr<unknown_bound<const volatile ptr<const U>>>;

int main()
{
	[[maybe_unused]] PP::type_t<void> a = PP::get_promotion_type(PP::type<int>);
	[[maybe_unused]] PP::type_t<void> b = PP::get_promotion_type(PP::type<short>);
	[[maybe_unused]] PP::type_t<void> c = PP::get_promotion_type(PP::type<bool>);
	[[maybe_unused]] PP::type_t<void> d = PP::get_promotion_type(PP::type<decltype(nullptr)>);
	[[maybe_unused]] PP::type_t<void> e = PP::get_promotion_type(PP::type<long>);
	[[maybe_unused]] PP::type_t<void> f = PP::get_promotion_type(PP::type<long long>);
	[[maybe_unused]] PP::type_t<void> g = PP::get_promotion_type(PP::type<char>);
	[[maybe_unused]] PP::type_t<void> h = PP::get_promotion_type(PP::type<wchar_t>);

	std::cout.flush();
	return 0;
}
