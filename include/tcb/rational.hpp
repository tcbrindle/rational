
// Copyright (c) 2016 Tristan Brindle (tcbrindle at gmail dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TCB_RATIONAL_HPP_INCLUDED
#define TCB_RATIONAL_HPP_INCLUDED

#include <cstdint>
#include <ratio>
#include <type_traits>

#ifndef TCB_RATIONAL_NO_IOSTREAMS
#include <iostream>
#endif

#if __cpp_constexpr >= 201304
#define TCB_HAVE_CONSTEXPR14
#endif

#ifdef TCB_HAVE_CONSTEXPR14
#define TCB_CONSTEXPR14 constexpr
#else
#define TCB_CONSTEXPR14
#endif

#if __cpp_concepts >= 201500
#define TCB_HAVE_CONCEPTS
#endif

namespace tcb {

namespace detail {

template <typename T>
TCB_CONSTEXPR14 T gcd(T a, T b)
{
    while (b != 0) {
        T t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// These are not guaranteed to be constexpr in the standard library
template <typename T>
constexpr T sign(T val)
{
    return val < 0 ? -1 : 1;
}

template <typename T>
constexpr T abs(T val)
{
    return val < 0 ? -val : val;
}


template<typename...>
using void_t = void;

template <typename T, typename U, typename = void>
struct is_nonnarrowing_assignable : std::false_type {};

template <typename T, typename U>
struct is_nonnarrowing_assignable<T, U, void_t<decltype(T{std::declval<U>()})>>
    : std::true_type{};

template <typename T, typename U>
constexpr bool is_nonnarrowing_assignable_v = is_nonnarrowing_assignable<T, U>::value;

} // end namespace detail

template <typename T>
class rational {
public:
    static_assert(std::is_integral<T>::value,
                  "tcb::rational<T> requires T to be an integral type");

    using value_type = T;

    /* Construction */

    constexpr rational() = default;

    template <typename U, typename = std::enable_if_t<std::is_integral<U>::value>>
    constexpr rational(U num)
        : num_(num)
    {}

    TCB_CONSTEXPR14 rational(value_type num, value_type denom)
        : num_{num}, denom_{denom}
    {
        simplify();
    }

    constexpr rational(const rational&) = default;

    template <typename U,
              typename = std::enable_if_t<detail::is_nonnarrowing_assignable_v<T, U>>>
    constexpr rational(const rational<U>& other)
            : num_(other.num()), denom_(other.denom())
    {}

    /* Assignment */

    constexpr rational& operator=(const rational&) = default;

    template <typename U,
              typename = std::enable_if_t<detail::is_nonnarrowing_assignable_v<T, U>>>
    TCB_CONSTEXPR14 rational& operator=(const rational<U>& other)
    {
        num_ = value_type{other.num()};
        denom_ = value_type{other.denom()};
        return *this;
    }

    TCB_CONSTEXPR14 void swap(rational& other)
    {
        using std::swap;
        swap(num_, other.num_);
        swap(denom_, other.denom_);
    }

    /* Member access */

    constexpr value_type num() const { return num_; }

    constexpr value_type denom() const { return denom_; }

    /* Compound assignment */

    template <typename U>
    TCB_CONSTEXPR14 rational& operator+=(const rational<U>& other)
    {
        num_ *= other.denom();
        num_ += denom_ * other.num();
        denom_ *= other.denom();
        simplify();
        return *this;
    }

    template <typename U,
              typename = std::enable_if_t<std::is_integral<U>::value>>
    TCB_CONSTEXPR14 rational& operator+=(U other)
    {
        return *this += rational<U>{other};
    }

    template <typename U>
    TCB_CONSTEXPR14 rational& operator-=(const rational<U>& other)
    {
        num_ *= other.denom();
        num_ -= denom_ * other.num();
        denom_ *= other.denom();
        simplify();
        return *this;
    }

    template <typename U>
    TCB_CONSTEXPR14 rational& operator-=(U other)
    {
        return *this -= rational<U>{other};
    }

    template <typename U>
    TCB_CONSTEXPR14 rational& operator*=(const rational<U>& other)
    {
        num_ *= other.num();
        denom_ *= other.denom();
        simplify();
        return *this;
    }

    template <typename U>
    TCB_CONSTEXPR14 rational& operator*=(U other)
    {
        return *this *= rational<U>{other};
    }

    template <typename U>
    TCB_CONSTEXPR14 rational& operator/=(const rational<U>& other)
    {
        num_ *= other.denom();
        denom_ *= other.num();
        simplify();
        return *this;
    }

    template <typename U>
    TCB_CONSTEXPR14 rational& operator/=(U other)
    {
        return *this /= rational<U>{other};
    }

    /* Conversion */

    template <typename U>
    constexpr explicit operator rational<U>() const
    {
        return rational<U>{static_cast<U>(num_), static_cast<U>(denom_)};
    }

    constexpr operator long double() const
    {
        return num_/static_cast<long double>(denom_);
    }

private:
    value_type num_ = 0;
    value_type denom_ = 1;

    TCB_CONSTEXPR14 void simplify()
    {
        using namespace detail;
        auto g = abs(gcd(num_, denom_));
        num_ = sign(denom_) * num_/g;
        denom_ = abs(denom_)/g;
    }

};

/*
 * Nonmember swap support
 */

template <typename T>
void swap(rational<T>& r1, rational<T>& r2)
{
    r1.swap(r2);
}

/*
 * Some sized aliases for rational<T>
 */

using rational8_t = rational<std::int_least8_t>;
using rational16_t = rational<std::int_least16_t>;
using rational32_t = rational<std::int_least32_t>;
using rational64_t = rational<std::int_least64_t>;
using rational_max_t = rational<std::intmax_t>;

/*
 * SFINAE-able type trait for rational types
 */

template <typename T, typename = void>
struct is_rational : std::is_integral<T> {};

template <typename T>
struct is_rational<rational<T>>
        : std::conditional_t<std::is_integral<T>::value,
                             std::true_type, std::false_type> {};

template <std::intmax_t Num, std::intmax_t Denom>
struct is_rational<std::ratio<Num, Denom>> : std::true_type {};

template <typename T>
constexpr bool is_rational_v = is_rational<T>::value;

namespace detail {

template <typename T, typename = void>
struct rational_value_type {};

template <typename T>
struct rational_value_type<T, detail::void_t<std::enable_if_t<std::is_integral<T>::value>>> {
    using type = T;
};

template <typename T>
struct rational_value_type<rational<T>> {
    using type = T;
};

template <std::intmax_t Num, std::intmax_t Denom>
struct rational_value_type<std::ratio<Num, Denom>> {
    using type = std::intmax_t;
};

} // end namespace detail

template <typename T>
using rational_value_t = typename detail::rational_value_type<T>::type;

#ifdef TCB_HAVE_CONCEPTS

template <typename T>
concept bool Rational()
{
    return is_rational_v<T>;
}

#endif

/*
 * numerator() and denominator() free functions for Rational types
 */

template <typename T,
          typename = std::enable_if_t<std::is_integral<T>::value>>
constexpr T numerator(T value)
{
    return value;
}

template <typename T>
constexpr T numerator(const rational<T>& r)
{
    return r.num();
}

template <std::intmax_t Num, std::intmax_t Denom>
constexpr std::intmax_t numerator(std::ratio<Num, Denom>)
{
    return std::ratio<Num, Denom>::num;
}

template <typename T,
          typename = std::enable_if_t<std::is_integral<T>::value>>
constexpr T denominator(T)
{
    return 1;
}

template <typename T>
constexpr T denominator(const rational<T>& r)
{
    return r.denom();
}

template <std::intmax_t Num, std::intmax_t Denom>
constexpr std::intmax_t denominator(std::ratio<Num, Denom>)
{
    return std::ratio<Num, Denom>::den;
}


/*
 * Comparison operators
 */

// Equality
template <typename T, typename U,
          typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr bool operator==(const T& lhs, const U& rhs)
{
    return numerator(lhs) == numerator(rhs) &&
            denominator(lhs) == denominator(rhs);
}

// Inequality
template <typename T, typename U,
          typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr bool operator!=(const T& lhs, const U& rhs)
{
    return !(lhs == rhs);
}

// Less than
template <typename T, typename U,
          typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr bool operator<(const T& lhs, const U& rhs)
{
    return numerator(lhs) * denominator(rhs) < numerator(rhs) * denominator(lhs);
}

// Greater than
template <typename T, typename U,
          typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr bool operator>(const T& lhs, const U& rhs)
{
    return rhs < lhs;
}

// less than or equal
template <typename T, typename U,
          typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr bool operator<=(const T& lhs, const U& rhs)
{
    return !(lhs > rhs);
}

// Greater than or equal
template <typename T, typename U,
          typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr bool operator>=(const T& lhs, const U& rhs)
{
    return !(lhs < rhs);
}

/*
 * Unary arithmetic operationalns
 */

template <typename T>
constexpr rational<T> operator+(const rational<T>& r)
{
    return r;
}

template <typename T>
constexpr rational<T> operator-(const rational<T>& r)
{
    return rational<T>{static_cast<T>(-r.num()), r.denom()};
}

/*
 * Binary arithmetic operations
 */

// Addition
template <typename T, typename U,
          typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr auto
operator+(const T& lhs, const U& rhs)
{
    using value_type = decltype(std::declval<rational_value_t<T>>() +
                                std::declval<rational_value_t<U>>());
    return rational<value_type>{
            denominator(lhs) * numerator(rhs) + denominator(rhs) * numerator(lhs),
            denominator(lhs) * denominator(rhs)};
}

// Subtraction
template <typename T, typename U,
        typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr auto
operator-(const T& lhs, const U& rhs)
{
    using value_type = decltype(std::declval<rational_value_t<T>>() -
            std::declval<rational_value_t<U>>());
    return rational<value_type>{
            numerator(lhs) * denominator(rhs) - numerator(rhs) * denominator(lhs),
            denominator(lhs) * denominator(rhs)};
}

// Multiplication
template <typename T, typename U,
          typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr auto
operator*(const T& lhs, const U& rhs)
{
    using value_type = decltype(std::declval<rational_value_t<T>>() *
            std::declval<rational_value_t<U>>());
    return rational<value_type>{
            numerator(lhs) * numerator(rhs),
            denominator(lhs) * denominator(rhs)};
}

// Division
template <typename T, typename U,
        typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr auto
operator/(const T& lhs, const U& rhs)
{
    using value_type = decltype(std::declval<rational_value_t<T>>() /
            std::declval<rational_value_t<U>>());
    return rational<value_type>{
            numerator(lhs) * denominator(rhs),
            denominator(lhs) * numerator(rhs)};
}

/*
 * User-defined literals support
 */

namespace rational_literals {

namespace detail {

template <typename T>
struct rational_literal_proxy {
    T value;
};

template <typename T, typename U,
          typename = std::enable_if_t<std::is_integral<T>::value>>
constexpr rational<U>
operator/(T t, rational_literal_proxy<U> p)
{
    return rational<U>(t, p.value);
}

template <typename T>
constexpr rational_literal_proxy<T> make_literal_proxy(unsigned long long i)
{
    return {static_cast<T>(i)};
}

} // end namespace detail

constexpr auto operator""_rs(unsigned long long i)
{
    return detail::make_literal_proxy<short>(i);
}

constexpr auto operator""_rus(unsigned long long i)
{
    return detail::make_literal_proxy<unsigned short>(i);
}

constexpr auto operator""_r(unsigned long long i)
{
    return detail::make_literal_proxy<int>(i);
}

constexpr auto operator""_ru(unsigned long long i)
{
    return detail::make_literal_proxy<unsigned int>(i);
}

constexpr auto operator""_rl(unsigned long long i)
{
    return detail::make_literal_proxy<long>(i);
}

constexpr auto operator""_rul(unsigned long long i)
{
    return detail::make_literal_proxy<unsigned long>(i);
}

constexpr auto operator""_rll(unsigned long long i)
{
    return detail::make_literal_proxy<long long>(i);
}

constexpr auto operator""_rull(unsigned long long i)
{
    return detail::make_literal_proxy<unsigned long long>(i);
}

constexpr auto operator""_r8(unsigned long long i)
{
    return detail::make_literal_proxy<std::int_least8_t>(i);
}

constexpr auto operator""_ru8(unsigned long long i)
{
    return detail::make_literal_proxy<std::uint_least8_t>(i);

}

constexpr auto operator""_r16(unsigned long long i)
{
    return detail::make_literal_proxy<std::int_least16_t>(i);
}

constexpr auto operator""_ru16(unsigned long long i)
{
    return detail::make_literal_proxy<std::uint_least16_t>(i);
}

constexpr auto operator""_r32(unsigned long long i)
{
    return detail::make_literal_proxy<std::int_least32_t>(i);
}

constexpr auto operator""_ru32(unsigned long long i)
{
    return detail::make_literal_proxy<std::uint_least32_t>(i);
}

constexpr auto operator""_r64(unsigned long long i)
{
    return detail::make_literal_proxy<std::int_least64_t>(i);
}

constexpr auto operator""_ru64(unsigned long long i)
{
    return detail::make_literal_proxy<std::uint_least64_t>(i);
}

} // end namespace rational_literals

#ifndef TCB_RATIONAL_NO_IOSTREAMS
template <typename T>
std::ostream& operator<<(std::ostream& os, const rational<T>& r)
{
    os << r.num();
    if (r.denom() != 1) {
        os << '/' << r.denom();
    }
    return os;
}
#endif

} // end namespace tcb

#undef TCB_CONSTEXPR14

#endif // TCB_RATIONAL_HPP_INCLUDED
