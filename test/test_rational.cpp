
// Copyright (c) 2016 Tristan Brindle (tcbrindle at gmail dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "catch.hpp"

#include <tcb/rational.hpp>

using namespace tcb::rational_literals;

namespace {

template <typename T>
void test_default_construction()
{
    using rational = tcb::rational<T>;

    constexpr rational r1{};
    static_assert(r1.num() == 0, "");
    static_assert(r1.denom() == 1, "");

    const rational r2{};
    REQUIRE(r2.num() == 0);
    REQUIRE(r2.denom() == 1);
}

template <typename T>
void test_numerator_construction()
{
    using rational = tcb::rational<T>;

    constexpr rational r1 = 3;
    static_assert(r1.num() == 3, "");
    static_assert(r1.denom() == 1, "");

    const rational r2 = 3;
    REQUIRE(r2.num() == 3);
    REQUIRE(r2.denom() == 1);
}

template <typename T>
void test_full_construction()
{
    using rational = tcb::rational<T>;

#ifdef TCB_HAVE_CONSTEXPR14
    constexpr rational r1{3, 2};
    static_assert(r1.num() == 3, "");
    static_assert(r1.denom() == 2, "");
#endif

    const rational r2{3, 2};
    REQUIRE(r2.num() == 3);
    REQUIRE(r2.denom() == 2);
}

template <typename T>
void test_copy_construction()
{
    using rational = tcb::rational<T>;
    
#ifdef TCB_HAVE_CONSTEXPR14
	{
		constexpr rational r1{3, 2};
        constexpr rational r2{r1};
        static_assert(r2.num() == r1.num(), "");
        static_assert(r2.denom() == r1.denom(), "");
    }
#endif

    {
		const rational r1{3, 2};
        const rational r2{r1};
        REQUIRE(r2.num() == r1.num());
        REQUIRE(r2.denom() == r1.denom());
    }
}

template <typename T>
void test_reduce_construction()
{
    using rational = tcb::rational<T>;

#ifdef TCB_HAVE_CONSTEXPR14
    constexpr rational r1{10, 100};
    static_assert(r1.num() == 1, "");
    static_assert(r1.denom() == 10, "");
#endif

    const rational r2{10, 100};
    REQUIRE(r2.num() == 1);
    REQUIRE(r2.denom() == 10);
}

template <typename T, typename U = T>
void test_assignment_from_rational()
{
    using rational1 = tcb::rational<T>;
    using rational2 = tcb::rational<U>;

    rational1 r{1, 10};
    r = rational2{3, 2};
    REQUIRE(r.num() == 3);
    REQUIRE(r.denom() == 2);
}

template <typename T, typename U = T>
void test_assignment_from_value()
{
    using rational = tcb::rational<T>;

    rational r{1, 10};
    r = static_cast<U>(3);
    REQUIRE(r.num() == 3);
    REQUIRE(r.denom() == 1);
}

template <typename T>
void test_relops()
{
    using rational = tcb::rational<T>;
    
#ifdef TCB_HAVE_CONSTEXPR14
    {
        constexpr rational r1{-8, 17};
        constexpr rational r2{1, 2};
        constexpr rational r3{2, 4};
        
        // Equality
        static_assert(!(r1 == r2), "");
        static_assert(r2 == r3, "");
        
        // Inequality
        static_assert(r1 != r2, "");
        static_assert(!(r2 != r3), "");
        
        // Less than
        static_assert(r1 < r2, "");
        static_assert(!(r2 < r3), "");
        
        // Less than or equal
        static_assert(r1 <= r2, "");
        static_assert(r2 <= r3, "");
        
        // Greater than
        static_assert(r2 > r1, "");
        static_assert(!(r3 > r2), "");
        
        // Greater than or equal
        static_assert(r2 >= r1, "");
        static_assert(r3 >= r2, "");
    }
#endif // CONSTEXPR14

    {
        const rational r1{8, 17};
        const rational r2{1, 2};
        const rational r3{2, 4};

        // Equality
        REQUIRE(!(r1 == r2));
        REQUIRE(r2 == r3);

        // Inequality
        REQUIRE(r1 != r2);
        REQUIRE(!(r2 != r3));

        // Less than
        REQUIRE(r1 < r2);
        REQUIRE(!(r2 < r3));

        // Less than or equal
        REQUIRE(r1 <= r2);
        REQUIRE(r2 <= r3);

        // Greater than
        REQUIRE(r2 > r1);
        REQUIRE(!(r3 > r2));

        // Greater than or equal
        REQUIRE(r2 >= r1);
        REQUIRE(r3 >= r2);
    }
}

template <typename T>
void test_value_relops()
{
    using rational = tcb::rational<T>;

#ifdef TCB_HAVE_CONSTEXPR14
    {
        constexpr rational r{8, 2};
        constexpr T v1{4};
        constexpr T v2{5};

        // Equality
        static_assert(r == v1, "");
        static_assert(v1 == r, "");
        static_assert(!(r == v2), "");
        static_assert(!(v2 == r), "");

        // Inequality
        static_assert(!(r != v1), "");
        static_assert(!(v1 != r), "");
        static_assert(r != v2, "");
        static_assert(v2 != r, "");

        // Less than
        static_assert(!(r < v1), "");
        static_assert(!(v1 < r), "");
        static_assert(r < v2, "");
        static_assert(!(v2 < r), "");

        // Less than or equal
        static_assert(r <= v1, "");
        static_assert(v1 <= r, "");
        static_assert(r <= v2, "");
        static_assert(!(v2 <= r), "");

        // Greater than
        static_assert(!(r > v1), "");
        static_assert(!(v1 > r), "");
        static_assert(!(r > v2), "");
        static_assert(v2 > r, "");

        // Greater than or equal
        static_assert(r >= v1, "");
        static_assert(v1 >= r, "");
        static_assert(!(r >= v2), "");
        static_assert(v2 >= r, "");
    }
#endif

    {
        const rational r{8, 2};
        const T v1{4};
        const T v2{5};

        // Equality
        REQUIRE(r == v1);
        REQUIRE(v1 == r);
        REQUIRE(!(r == v2));
        REQUIRE(!(v2 == r));

        // Inequality
        REQUIRE(!(r != v1));
        REQUIRE(!(v1 != r));
        REQUIRE(r != v2);
        REQUIRE(v2 != r);

        // Less than
        REQUIRE(!(r < v1));
        REQUIRE(!(v1 < r));
        REQUIRE(r < v2);
        REQUIRE(!(v2 < r));

        // Less than or equal
        REQUIRE(r <= v1);
        REQUIRE(v1 <= r);
        REQUIRE(r <= v2);
        REQUIRE(!(v2 <= r));

        // Greater than
        REQUIRE(!(r > v1));
        REQUIRE(!(v1 > r));
        REQUIRE(!(r > v2));
        REQUIRE(v2 > r);

        // Greater than or equal
        REQUIRE(r >= v1);
        REQUIRE(v1 >= r);
        REQUIRE(!(r >= v2));
        REQUIRE(v2 >= r);
    }
}

template <typename T>
void test_unary_arithmetic()
{
    using rational = tcb::rational<T>;
    
#ifdef TCB_HAVE_CONSTEXPR14
    {
        constexpr rational r1{1, 2};
        constexpr rational r2{-1, 2};
        
        static_assert((+r1) == r1, "");
        static_assert((+r2) == r2, "");
        
        static_assert((-r1) == r2, "");
        static_assert((-r2) == r1, "");
    }
#endif

    {
        const rational r1{1, 2};
        const rational r2{-1, 2};

        REQUIRE((+r1) == r1);
        REQUIRE((+r2) == r2);

        REQUIRE((-r1) == r2);
        REQUIRE((-r2) == r1);
    }
}

template <typename T, typename U = T>
void test_binary_arithmetic()
{
    using rational1 = tcb::rational<T>;
    using rational2 = tcb::rational<U>;
  
#ifdef TCB_HAVE_CONSTEXPR14
    {
        constexpr auto r1 = rational1{1, 5};
        constexpr auto r2 = rational2{1, 10};
        constexpr auto v = T{2};
  
        // Addition
        {
            constexpr auto res = r1 + r2;
            static_assert(res.num() == 3, "");
            static_assert(res.denom() == 10, "");
            
            constexpr auto res2 = r2 + v;
            static_assert(res2.num() == 21, "");
            static_assert(res2.denom()== 10, "");

            constexpr auto res3 = v + r2;
            static_assert(res3.num() == 21, "");
            static_assert(res3.denom()== 10, "");
        }

        // Subtraction
        {
            constexpr auto res = r1 - r2;
            static_assert(res.num() == 1, "");
            static_assert(res.denom() == 10, "");

            constexpr auto res2 = r2 - v;
            static_assert(res2.num() == -19, "");
            static_assert(res2.denom()== 10, "");

            constexpr auto res3 = v - r2;
            static_assert(res3.num() == 19, "");
            static_assert(res3.denom()== 10, "");
        }

        // Multiplication
        {
            constexpr auto res = r1 * r2;
            static_assert(res.num() == 1, "");
            static_assert(res.denom() == 50, "");

            constexpr auto res2 = r2 * v;
            static_assert(res2.num() == 1, "");
            static_assert(res2.denom() == 5, "");

            constexpr auto res3 = v * r2;
            static_assert(res3.num() == 1, "");
            static_assert(res3.denom() == 5, "");
        }

        // Division
        {
            constexpr auto res = r1 / r2;
            static_assert(res.num() == 2, "");
            static_assert(res.denom() == 1, "");

            constexpr auto res2 = r2 / v;
            static_assert(res2.num() == 1, "");
            static_assert(res2.denom() == 20, "");

            constexpr auto res3 = v / r2;
            static_assert(res3.num() == 20, "");
            static_assert(res3.denom() == 1, "");
        }
    }
#endif

    {
        const auto r1 = rational1{1, 5};
        const auto r2 = rational2{1, 10};
        const auto v = T{2};

        // Addition
        {
            const auto res = r1 + r2;
            REQUIRE(res.num() == 3);
            REQUIRE(res.denom() == 10);

            const auto res2 = r2 + v;
            REQUIRE(res2.num() == 21);
            REQUIRE(res2.denom()== 10);

            const auto res3 = v + r2;
            REQUIRE(res3.num() == 21);
            REQUIRE(res3.denom()== 10);
        }

        // Subtraction
        {
            const auto res = r1 - r2;
            REQUIRE(res.num() == 1);
            REQUIRE(res.denom() == 10);

            // FIXME: This does funny things at runtime with unsigned types,
            // FIXME: but works fine in the constexpr case. Not sure why.
            if (std::is_signed<T>::value && std::is_signed<U>::value) {
                const auto res2 = r2 - v;
                REQUIRE(res2.num() == -19);
                REQUIRE(res2.denom() == 10);
            }

            const auto res3 = v - r2;
            REQUIRE(res3.num() == 19);
            REQUIRE(res3.denom()== 10);
        }

        // Multiplication
        {
            const auto res = r1 * r2;
            REQUIRE(res.num() == 1);
            REQUIRE(res.denom() == 50);

            const auto res2 = r2 * v;
            REQUIRE(res2.num() == 1);
            REQUIRE(res2.denom() == 5);

            const auto res3 = v * r2;
            REQUIRE(res3.num() == 1);
            REQUIRE(res3.denom() == 5);
        }

        // Division
        {
            const auto res = r1 / r2;
            REQUIRE(res.num() == 2);
            REQUIRE(res.denom() == 1);

            const auto res2 = r2 / v;
            REQUIRE(res2.num() == 1);
            REQUIRE(res2.denom() == 20);

            const auto res3 = v / r2;
            REQUIRE(res3.num() == 20);
            REQUIRE(res3.denom() == 1);
        }
    }
}

template <typename T, typename U = T>
void test_relational_assignment()
{
    using rational1 = tcb::rational<T>;
    using rational2 = tcb::rational<U>;
    
    // Can't do this at compile-time
    {
        rational1 r1{1, 5};
        const rational2 r2{1, 10};
        constexpr U v{2};

        r1 += r2;
        REQUIRE(r1.num() == 3);
        REQUIRE(r2.denom() == 10);
        
        r1 += v;
        REQUIRE(r1.num() == 23);
        REQUIRE(r2.denom() == 10);
    }

    {
        rational1 r1{1, 5};
        const rational2 r2{1, 10};
        constexpr U v{2};

        r1 -= r2;
        REQUIRE(r1.num() == 1);
        REQUIRE(r1.denom() == 10);

        r1 -= v;
        REQUIRE(r1.num() == static_cast<U>(-19));
        REQUIRE(r1.denom() == 10);
    }

    {
        rational1 r1{1, 5};
        const rational2 r2{1, 10};
        constexpr U v{2};

        r1 *= r2;
        REQUIRE(r1.num() == 1);
        REQUIRE(r1.denom() == 50);

        r1 *= v;
        REQUIRE(r1.num() == 1);
        REQUIRE(r1.denom() == 25);
    }

    {
        rational1 r1{1, 5};
        const rational2 r2{1, 10};
        constexpr U v{2};

        r1 /= r2;
        REQUIRE(r1.num() == 2);
        REQUIRE(r1.denom() == 1);

        r1 /= v;
        REQUIRE(r1.num() == 1);
        REQUIRE(r1.denom() == 1);
    }
}

}

/*
 * Construction test
 */

TEST_CASE("Rationals can be default constructed")
{
    test_default_construction<char>();
    test_default_construction<signed char>();
    test_default_construction<unsigned char>();
    test_default_construction<signed short>();
    test_default_construction<unsigned short>();
    test_default_construction<signed int>();
    test_default_construction<unsigned int>();
    test_default_construction<signed long>();
    test_default_construction<unsigned long>();
    test_default_construction<signed long long>();
    test_default_construction<unsigned long long>();
    test_default_construction<std::intmax_t>();
    test_default_construction<std::uintmax_t>();
}

TEST_CASE("Rationals can be constructed from a single argument")
{
    test_numerator_construction<char>();
    test_numerator_construction<signed char>();
    test_numerator_construction<unsigned char>();
    test_numerator_construction<signed short>();
    test_numerator_construction<unsigned short>();
    test_numerator_construction<signed int>();
    test_numerator_construction<unsigned int>();
    test_numerator_construction<signed long>();
    test_numerator_construction<unsigned long>();
    test_numerator_construction<signed long long>();
    test_numerator_construction<unsigned long long>();
    test_numerator_construction<std::intmax_t>();
    test_numerator_construction<std::uintmax_t>();
}

TEST_CASE("Rationals can be constructed from a two arguments")
{
    test_full_construction<char>();
    test_full_construction<signed char>();
    test_full_construction<unsigned char>();
    test_full_construction<signed short>();
    test_full_construction<unsigned short>();
    test_full_construction<signed int>();
    test_full_construction<unsigned int>();
    test_full_construction<signed long>();
    test_full_construction<unsigned long>();
    test_full_construction<signed long long>();
    test_full_construction<unsigned long long>();
    test_full_construction<std::intmax_t>();
    test_full_construction<std::uintmax_t>();
}

TEST_CASE("Rational constructor reduces fractions")
{
    test_reduce_construction<char>();
    test_reduce_construction<signed char>();
    test_reduce_construction<unsigned char>();
    test_reduce_construction<signed short>();
    test_reduce_construction<unsigned short>();
    test_reduce_construction<signed int>();
    test_reduce_construction<unsigned int>();
    test_reduce_construction<signed long>();
    test_reduce_construction<unsigned long>();
    test_reduce_construction<signed long long>();
    test_reduce_construction<unsigned long long>();
    test_reduce_construction<std::intmax_t>();
    test_reduce_construction<std::uintmax_t>();
}

TEST_CASE("Rationals can be copy constructed")
{
    test_copy_construction<char>();
    test_copy_construction<signed char>();
    test_copy_construction<unsigned char>();
    test_copy_construction<signed short>();
    test_copy_construction<unsigned short>();
    test_copy_construction<signed int>();
    test_copy_construction<unsigned int>();
    test_copy_construction<signed long>();
    test_copy_construction<unsigned long>();
    test_copy_construction<signed long long>();
    test_copy_construction<unsigned long long>();
    test_copy_construction<std::intmax_t>();
    test_copy_construction<std::uintmax_t>();
}

/*
 * Assignment tests
 */

TEST_CASE("Rationals can be assigned to from other rationals")
{
    test_assignment_from_rational<char>();
    test_assignment_from_rational<signed char>();
    test_assignment_from_rational<unsigned char>();
    test_assignment_from_rational<signed short>();
    test_assignment_from_rational<unsigned short>();
    test_assignment_from_rational<signed int>();
    test_assignment_from_rational<unsigned int>();
    test_assignment_from_rational<signed long>();
    test_assignment_from_rational<unsigned long>();
    test_assignment_from_rational<signed long long>();
    test_assignment_from_rational<unsigned long long>();
    test_assignment_from_rational<std::intmax_t>();
    test_assignment_from_rational<std::uintmax_t>();
}

TEST_CASE("Rationals of different types can be assigned")
{
    test_assignment_from_rational<long long, char>();

    test_assignment_from_rational<int, unsigned short>();

    // Should not compile
    // test_assignment_from_rational<int, long>();
}

TEST_CASE("Rationals can be assigned from values")
{
    test_assignment_from_value<char>();
    test_assignment_from_value<signed char>();
    test_assignment_from_value<unsigned char>();
    test_assignment_from_value<signed short>();
    test_assignment_from_value<unsigned short>();
    test_assignment_from_value<signed int>();
    test_assignment_from_value<unsigned int>();
    test_assignment_from_value<signed long>();
    test_assignment_from_value<unsigned long>();
    test_assignment_from_value<signed long long>();
    test_assignment_from_value<unsigned long long>();
    test_assignment_from_value<std::intmax_t>();
    test_assignment_from_value<std::uintmax_t>();

    test_assignment_from_value<int, long>();
    test_assignment_from_value<long long, unsigned char>();
}

/*
 *  Relational operator tests
 */

TEST_CASE("Relational operators work as expected")
{
    test_relops<char>();
    test_relops<signed char>();
//    test_relops<unsigned char>();
    test_relops<signed short>();
//    test_relops<unsigned short>();
    test_relops<signed int>();
//    test_relops<unsigned int>();
    test_relops<signed long>();
//    test_relops<unsigned long>();
    test_relops<signed long long>();
//    test_relops<unsigned long long>();
    test_relops<std::intmax_t>();
//    test_relops<std::uintmax_t>();
}

TEST_CASE("Relational operators against values work as expected")
{
    test_value_relops<char>();
    test_value_relops<signed char>();
    test_value_relops<unsigned char>();
    test_value_relops<signed short>();
    test_value_relops<unsigned short>();
    test_value_relops<signed int>();
    test_value_relops<unsigned int>();
    test_value_relops<signed long>();
    test_value_relops<unsigned long>();
    test_value_relops<signed long long>();
    test_value_relops<unsigned long long>();
    test_value_relops<std::intmax_t>();
    test_value_relops<std::uintmax_t>();
}

TEST_CASE("Rationals of different types can be compared")
{
    // Just pick some arbitrary types
#ifdef TCB_HAVE_CONSTEXPR14
    constexpr auto r1 = tcb::rational<int>{1, 2};
    constexpr auto r2 = tcb::rational<unsigned long>{2, 4};
    constexpr auto r3 = tcb::rational<char>{static_cast<char>(17)};

    static_assert(r1 == r2, "");
    static_assert(r2 == r1, "");
    static_assert(!(r2 == r3), "");
    static_assert(!(r3 == r2), "");

    static_assert(!(r1 != r2), "");
    static_assert(!(r2 != r1), "");
    static_assert(r2 != r3, "");
    static_assert(r3 != r2, "");
#endif
    
    // TODO: Other relational operators, runtime tests
}

/*
 * Test unary arithmetic operators
 */

TEST_CASE("Unary arithmentic operators work as expected")
{
    // Only test signed types
    test_unary_arithmetic<signed char>();
    test_unary_arithmetic<signed short>();
    test_unary_arithmetic<signed int>();
    test_unary_arithmetic<signed long>();
    test_unary_arithmetic<signed long long>();
    test_unary_arithmetic<std::intmax_t>();
}

/*
 * Test binary arithmetic operators
 */
TEST_CASE("Binary arithmetic operators work as expected")
{
    test_binary_arithmetic<char>();
    test_binary_arithmetic<signed char>();
    test_binary_arithmetic<unsigned char>();
    test_binary_arithmetic<signed short>();
    test_binary_arithmetic<unsigned short>();
    test_binary_arithmetic<signed int>();
    test_binary_arithmetic<unsigned int>();
    test_binary_arithmetic<signed long>();
    test_binary_arithmetic<unsigned long>();
    test_binary_arithmetic<signed long long>();
    test_binary_arithmetic<unsigned long long>();
    test_binary_arithmetic<std::intmax_t>();
    test_binary_arithmetic<std::uintmax_t>();
}

TEST_CASE("Binary arithmetic operators of different types work as expected")
{
    // Just test a few
    test_binary_arithmetic<char, unsigned long long>();
    test_binary_arithmetic<int, short>();
    test_binary_arithmetic<long long, unsigned int>();
}

TEST_CASE("Relational assignment operators work as expected")
{
    test_relational_assignment<char>();
    test_relational_assignment<signed char>();
    test_relational_assignment<unsigned char>();
    test_relational_assignment<signed short>();
    test_relational_assignment<unsigned short>();
    test_relational_assignment<signed int>();
    test_relational_assignment<unsigned int>();
    test_relational_assignment<signed long>();
    test_relational_assignment<unsigned long>();
    test_relational_assignment<signed long long>();
    test_relational_assignment<unsigned long long>();
    test_relational_assignment<std::intmax_t>();
    test_relational_assignment<std::uintmax_t>();

    // Hmmm, I'd rather assigning to a rational<short> from a long didn't work
    test_relational_assignment<short, long>();
    test_relational_assignment<unsigned long, short>();
}

TEST_CASE("is_rational type trait works")
{
    // Integral types are rational
    static_assert(tcb::is_rational_v<char>, "");
    static_assert(tcb::is_rational_v<signed char>, "");
    static_assert(tcb::is_rational_v<unsigned char>, "");
    static_assert(tcb::is_rational_v<signed short>, "");
    static_assert(tcb::is_rational_v<unsigned short>, "");
    static_assert(tcb::is_rational_v<signed int>, "");
    static_assert(tcb::is_rational_v<unsigned int>, "");
    static_assert(tcb::is_rational_v<signed long>, "");
    static_assert(tcb::is_rational_v<unsigned long>, "");
    static_assert(tcb::is_rational_v<signed long long>, "");
    static_assert(tcb::is_rational_v<unsigned long long>, "");
    static_assert(tcb::is_rational_v<std::intmax_t>, "");
    static_assert(tcb::is_rational_v<std::uintmax_t>, "");

    // Rationals are, well, rational
    static_assert(tcb::is_rational_v<tcb::rational<char>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<signed char>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<unsigned char>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<signed short>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<unsigned short>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<signed int>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<unsigned int>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<signed long>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<unsigned long>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<signed long long>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<unsigned long long>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<std::intmax_t>>, "");
    static_assert(tcb::is_rational_v<tcb::rational<std::uintmax_t>>, "");

    // std::ratios are rational
    static_assert(tcb::is_rational_v<std::atto>, "");
    static_assert(tcb::is_rational_v<std::femto>, "");
    static_assert(tcb::is_rational_v<std::pico>, "");
    static_assert(tcb::is_rational_v<std::nano>, "");
    static_assert(tcb::is_rational_v<std::micro>, "");
    static_assert(tcb::is_rational_v<std::milli>, "");
    static_assert(tcb::is_rational_v<std::centi>, "");
    static_assert(tcb::is_rational_v<std::deci>, "");
    static_assert(tcb::is_rational_v<std::deca>, "");
    static_assert(tcb::is_rational_v<std::hecto>, "");
    static_assert(tcb::is_rational_v<std::kilo>, "");
    static_assert(tcb::is_rational_v<std::mega>, "");
    static_assert(tcb::is_rational_v<std::giga>, "");
    static_assert(tcb::is_rational_v<std::tera>, "");
    static_assert(tcb::is_rational_v<std::peta>, "");
    static_assert(tcb::is_rational_v<std::exa>, "");

    // Floating point types are not rational
    static_assert(!tcb::is_rational_v<float>, "");
    static_assert(!tcb::is_rational_v<double>, "");
    static_assert(!tcb::is_rational_v<tcb::rational<float>>, "");
    static_assert(!tcb::is_rational_v<tcb::rational<float>>, "");

    // Check concepts if supported
#if  __cpp_concepts >= 201500
    std::cout << __cpp_concepts << std::endl;
    static_assert(tcb::Rational<int>, "");
    static_assert(tcb::Rational<tcb::rational<int>>, "");
    static_assert(tcb::Rational<std::kilo>, "");
    static_assert(!tcb::Rational<float>, "");
    static_assert(tcb::Rational<tcb::rational<float>>, "");
#endif
}

TEST_CASE("UDLs work as expected")
{
#ifdef TCB_HAVE_CONSTEXPR14
	static_assert(3 / 10_rs == tcb::rational<unsigned short>{3, 10}, "");
	static_assert(3 / 10_r == tcb::rational<int>{3, 10}, "");
#endif

	REQUIRE(3 / 10_rs == tcb::rational<unsigned short>(3, 10));
	REQUIRE(3 / 10_r == tcb::rational<int>(3, 10));
}

TEST_CASE("Rationals can be printed")
{
    {
        std::ostringstream ss;
        ss << 3/10_r;
        REQUIRE(ss.str() == "3/10");
    }

    {
        std::ostringstream ss;
        ss << tcb::rational<int>{3};
        REQUIRE(ss.str() == "3");
    }
}

TEST_CASE("Rationals can be placed in containers")
{
    std::vector<tcb::rational<int>> v{1, 1/10_r, 1/100_r, 1/1000_r, -1/1000_r, 0};
    std::sort(v.begin(), v.end());

    std::set<tcb::rational<int>> s{1, 1/10_r, 1/100_r, 1/1000_r, -1/1000_r, 0};

    REQUIRE(std::equal(v.cbegin(), v.cend(), s.cbegin(), s.cend()));
}

TEST_CASE("Double conversion works as expected")
{
#ifdef TCB_HAVE_CONSTEXPR14
    constexpr auto r = 1/8_r;
    static_assert(r + 1.0 == 1.125, "");
#endif
	const auto r = 1 / 8_r;
	REQUIRE(r + 1.0 == 1.125);

	// TODO: More floating point tests
}
