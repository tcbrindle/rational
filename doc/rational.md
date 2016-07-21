# Header file `../include/tcb/rational.hpp`


```cpp
#define TCB_RATIONAL_HPP_INCLUDED 

#include <cstdint>

#include <ratio>

#include <type_traits>

#include <iostream>

#define TCB_HAVE_CONSTEXPR14 

#define TCB_CONSTEXPR14 constexpr

namespace tcb
{
    template <typename T>
    class rational;
    
    template <typename T>
    void swap(rational<T>& r1, rational<T>& r2);
    
    using rational8_t = rational<std::int_least8_t>;
    
    using rational16_t = rational<std::int_least16_t>;
    
    using rational32_t = rational<std::int_least32_t>;
    
    using rational64_t = rational<std::int_least64_t>;
    
    using rational_max_t = rational<std::intmax_t>;
    
    template <typename T, typename = void>
    struct is_rational;
    
    template <typename T>
    struct is_rational<rational<;
    
    template <std::intmax_t Num, std::intmax_t Denom>
    struct is_rational<std::ratio<;
    
    template <typename T>
    using rational_value_t = typename detail::rational_value_type<T>::type;
    
    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    constexpr T numerator(T value);
    
    template <typename T>
    constexpr T numerator(const rational<T>& r);
    
    template <std::intmax_t Num, std::intmax_t Denom>
    constexpr std::intmax_t numerator(std::ratio<Num, Denom>);
    
    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    constexpr T denominator(T);
    
    template <typename T>
    constexpr T denominator(const rational<T>& r);
    
    template <std::intmax_t Num, std::intmax_t Denom>
    constexpr std::intmax_t denominator(std::ratio<Num, Denom>);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr bool operator==(const T& lhs, const U& rhs);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr bool operator!=(const T& lhs, const U& rhs);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr bool operator<(const T& lhs, const U& rhs);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr bool operator>(const T& lhs, const U& rhs);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr bool operator<=(const T& lhs, const U& rhs);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr bool operator>=(const T& lhs, const U& rhs);
    
    template <typename T>
    constexpr rational<T> operator+(const rational<T>& r);
    
    template <typename T>
    constexpr rational<T> operator-(const rational<T>& r);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr auto operator+(const T& lhs, const U& rhs);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr auto operator-(const T& lhs, const U& rhs);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr auto operator*(const T& lhs, const U& rhs);
    
    template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
    constexpr auto operator/(const T& lhs, const U& rhs);
    
    namespace rational_literals
    {
        constexpr auto operator""_rs(unsigned long long i);
        
        constexpr auto operator""_rus(unsigned long long i);
        
        constexpr auto operator""_r(unsigned long long i);
        
        constexpr auto operator""_ru(unsigned long long i);
        
        constexpr auto operator""_rl(unsigned long long i);
        
        constexpr auto operator""_rul(unsigned long long i);
        
        constexpr auto operator""_rll(unsigned long long i);
        
        constexpr auto operator""_rull(unsigned long long i);
        
        constexpr auto operator""_r8(unsigned long long i);
        
        constexpr auto operator""_ru8(unsigned long long i);
        
        constexpr auto operator""_r16(unsigned long long i);
        
        constexpr auto operator""_ru16(unsigned long long i);
        
        constexpr auto operator""_r32(unsigned long long i);
        
        constexpr auto operator""_ru32(unsigned long long i);
        
        constexpr auto operator""_r64(unsigned long long i);
        
        constexpr auto operator""_ru64(unsigned long long i);
    }
    
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const rational<T>& r);
}
```


## Class template `tcb::rational<T>`


```cpp
template <typename T>
class rational
{
public:
    using value_type = T;
    constexpr rational() = default;
    template <typename U, typename = std::enable_if_t<std::is_integral<U>::value>>
    constexpr rational(U num);
    constexpr rational(value_type num, value_type denom);
    constexpr rational(const rational&) = default;
    template <typename U, typename = std::enable_if_t<detail::is_nonnarrowing_assignable_v<T, U>>>
    constexpr rational(const rational<U>& other);
    constexpr rational& operator=(const rational&) = default;
    template <typename U, typename = std::enable_if_t<detail::is_nonnarrowing_assignable_v<T, U>>>
    constexpr rational& operator=(const rational<U>& other);
    constexpr void swap(rational& other);
    constexpr value_type num() const;
    constexpr value_type denom() const;
    template <typename U>
    constexpr rational& operator+=(const rational<U>& other);
    template <typename U, typename = std::enable_if_t<std::is_integral<U>::value>>
    constexpr rational& operator+=(U other);
    template <typename U>
    constexpr rational& operator-=(const rational<U>& other);
    template <typename U>
    constexpr rational& operator-=(U other);
    template <typename U>
    constexpr rational& operator*=(const rational<U>& other);
    template <typename U>
    constexpr rational& operator*=(U other);
    template <typename U>
    constexpr rational& operator/=(const rational<U>& other);
    template <typename U>
    constexpr rational& operator/=(U other);
    template <typename U>
    explicit constexpr operator rational<U>() const;
    constexpr operator long double() const;
};
```

Basic class template for a rational type

*Requires:* `std::is_integral<T>::value` is `true`

### Constructor `tcb::rational<T>::rational`


```cpp
constexpr rational() = default;
```

Default-constructs a rational

*Effects:* this->num() == 0, this->denom() == 1

### Function template `tcb::rational<T>::rational<U>`


```cpp
template <typename U, typename = std::enable_if_t<std::is_integral<U>::value>>
constexpr rational(U num);
```

Constructs a rational from a value

*Requires:* Assignment from `U` to `T` is non-narrowing

*Effects:* this->num() == value, this->denom() == 1

### Constructor `tcb::rational<T>::rational`


```cpp
constexpr rational(value_type num, value_type denom);
```

Constructs a rational from the given numerator an denominator

*Effects:* this->num() == num, this->denom() == denom

*Requires:* `denom` is not equal to zero

### Constructor `tcb::rational<T>::rational`


```cpp
constexpr rational(const rational&) = default;
```

Defaulted copy construction

### Function template `tcb::rational<T>::rational<U>`


```cpp
template <typename U, typename = std::enable_if_t<detail::is_nonnarrowing_assignable_v<T, U>>>
constexpr rational(const rational<U>& other);
```

Copy-constructs a rational<T> from rational<U>

*Requires:* Assignment from `T` to `U` is non-narrowing

*Effects:* this->num() == other.num(), this->denom() == other.denom()

### Function `tcb::rational<T>::operator=`


```cpp
constexpr rational& operator=(const rational&) = default;
```

Defaulted copy-assignment

### Function template `tcb::rational<T>::operator=<U>`


```cpp
template <typename U, typename = std::enable_if_t<detail::is_nonnarrowing_assignable_v<T, U>>>
constexpr rational& operator=(const rational<U>& other);
```

Copy-assigns a from rational of a different type

*Requires:* Assignment from `T` to `U` is non-narrowing

*Effects:* this->num() == other.num(), this->denom() == other.denom()

### Function `tcb::rational<T>::swap`


```cpp
constexpr void swap(rational& other);
```


*Effects:* Swaps the values of `this` and `other`

### Function `tcb::rational<T>::num`


```cpp
constexpr value_type num() const;
```


*Returns:* The value of the numerator of the rational


---

## Function template `tcb::operator==<T, U>`


```cpp
template <typename T, typename U, typename = std::enable_if_t<is_rational_v<T> && is_rational_v<U>>>
constexpr bool operator==(const T& lhs, const U& rhs);
```


*Returns:* `true` if `lhs` and `rhs` are equal

*Requires:* `T` and `U` are models of `Rational`

