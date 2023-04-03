
#include <tcb/rational.hpp>

int main()
{
    // This is a small demonstration of how to use rational.hpp, in leiu of
    // having any proper documentation yet.

    // Everything is in namespace tcb. We'll include it all here for brevity.
    using namespace tcb;

    // tcb::rational is a template class modeling a mathematical rational number.
    // The template parameter can be any integer type. Here we'll use int.
    // Note that unless you're using MSVC, everything in the library is
    // constexpr, so it works at compile time just as well as at runtime
    constexpr auto r1 = rational<int>{};

    // The above rational was default-constructed, so it has a numerator of 0
    // and a denominator of 1. We can also construct a rational with one
    // argument, which is the numerator...
    constexpr auto r2 = rational<int>{3};

    // ...or we can supply both the numerator and denominator
    constexpr auto r3 = rational<int>{3, 10};

    // Note that supplying a denominator of 0 is undefined behaviour -- we don't
    // bother checking for it, and it will probably just crash. Don't do it!
    // Negative denominators are fine to pass to the constructor however.

    // We can read the numerator and denominator using the num() and denom()
    // member functions:
    static_assert(r3.num() == 3, "");
    static_assert(r3.denom() == 10, "");

    // Or, if you prefer, there are numerator() and denominator() free functions:
    static_assert(numerator(r3) == 3, "");
    static_assert(denominator(r3) == 10, "");

    // The rational class maintains the invariants that
    //   i) The denominator is always strictly positive
    //   ii) The numerator and denominator are always stored in their lowest
    //       possible terms
    // The second condition means that fractions will be simplified during
    // construction or assignment, for example:
    constexpr auto r4 = rational<int>{5, 10};
    static_assert(r4.num() == 1, "");
    static_assert(r4.denom() == 2, "");

    // As you might expect, we can perform the usual arithmetic operations on
    // a rational, for example:
    static_assert(rational<int>{1, 10} + rational<int>{1, 5} == rational<int>{3, 10}, "");

    // As the above demonstrates, we can also use the standard logic operators
    // on rationals, for example:
    static_assert(rational<int>{8, 17} < rational<int>{1, 2}, "");

    // Writing rational<int> all the time is getting tedious. Fortunately,
    // we have user-defined literals available to make life easier. These
    // are hidden away in namespace tcb::rational_literals, which you have
    // to explicitly ask for:
    using namespace tcb::rational_literals;

    // There are rational literal operators defined for every common integer
    // type, for example...
    constexpr auto r5 = 1/10_r;   // _r means rational<int>
    constexpr auto r6 = 1/10_rul; // _rul means rational<unsigned long>
    constexpr auto r7 = 1/10_r64; // _r64 means rational<std::int64_t>

    // Note that the literal suffix goes on the denominator of the fraction,
    // so that it looks pretty. Attempting to do the following is a compile-time
    // error:
    // constexpr auto r8 = 1_r/10;

    // We can convert between rationals of different types, but if such a
    // conversion would be narrowing then we need to explicitly static_cast:
    constexpr rational<int64_t> r8 = 1/10_r32; // assignment of int32 to int64, fine
    // constexpr rational<int32_t> r9 = r8; // assignment of int64 to int32, error
    constexpr rational<int32_t> r9 = static_cast<rational<int32_t>>(r8); // Okay


    // Mathematically, the rational numbers are a subset of the reals. It's
    // pretty hard to represent a real number on a computer, but IEEE floating
    // point is the best we've got. We supply an implicit conversion
    // operator so you can mix rationals into a floating point computations just
    // like you can with ints
    static_assert(3/5_r + 0.1 < 1.0, "");

    // Speaking of mathematics, the integers are in fact a subset of the
    // rationals. We model this by defining a Rational concept. Every integer
    // type is a model of Rational, as is rational<T> itself of course.
    // All the free functions are defined for any Rational: that means that you
    // can ask for the numerator and denominator of an integer:
    static_assert(numerator(12) == 12, "");
    static_assert(denominator(12) == 1, "");

    // ...or perform operations freely between rationals and compatible
    // integer types
    static_assert(15 * 1/3_r == 5, "");

    // We also provide overloads so that the std::ratio class becomes a model
    // of Rational. That means that it's legal to do daft things like this:
    static_assert(std::kilo{} * (1/10_r) == 100, "");
    // Whether or not this is a good idea is left to your discretion.

    // You can test whether something matches the Rational concept using
    // the is_rational<T> type trait, or the is_rational_v<T> shortcut. For
    // example:
    static_assert(is_rational<int>::value, "");
    static_assert(!is_rational_v<float>, "");
    static_assert(is_rational_v<decltype(1/10_r)>, "");

    // If you're really fancy and using a recent GCC, we provide a real
    // Concept which wraps the is_rational<T> test:
#ifdef TCB_HAVE_CONCEPTS
    static_assert(Rational<decltype(1/10_r)>(), "");
#endif

    // Lastly, we provide an output stream function to print rationals:
    std::cout << 22/7_r << " is nearly pi!\n";

    // If you don't want to #include <iostream> when including rational.hpp,
    // just define the symbol TCB_RATIONAL_NO_IOSTREAMS beforehand. We'll get
    // the message.

    // That about wraps it up. I hope you find rational.hpp useful. If you have
    // any comments, questions, bug reports or pull requests then give me a
    // shout.

    // Thanks!
}
