#pragma once

template <typename T>
concept decrementable_c = requires(T t)
{
    { --t } -> T&;
    { t-- } -> T;
};

template <typename T>
constexpr T operator--(T& t, int)
{
    auto copy = t;
    --t;
    return copy;
}