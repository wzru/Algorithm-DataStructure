#ifndef NUMBER_THEORY_HPP
#define NUMBER_THEORY_HPP

#include <utility>
#include <cmath>

using i32 = int;
using u32 = unsigned int;
using uint = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;

template<typename T>
inline T gcd (const T &a, const T &b)
{
    return b == 0 ? abs (a) : gcd (b, a % b);
}

template<typename T>
inline T lcm (const T &a, const T &b)
{
    return abs (a / gcd (a, b) * b);
}

template<typename T>
inline std::pair<T, T> extended_euclidean (const T &a, const T &b)
{
    if (b == 0)
    {
        return std::make_pair (1, 0);
    }
    std::pair<T, T> tmp = extended_euclidean (b, a % b);
    return std::make_pair (tmp.second, tmp.first - a / b * tmp.second);
}

template<typename T>
inline T extended_euclidean (const T &a, const T &b, T &x, T &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    auto d = extended_euclidean (b, a % b, y, x);
    y -= a / b * x;
    return d;
}

template<typename T>
inline T quick_multiply (T a, T b)
{
    T res (0);
    if (a < b)
    {
        std::swap (a, b);
    }
    while (b)
    {
        if (b & 1)
        {
            res += a;
        }
        a <<= 1;
        b >>= 1;
    }
    return res;
}

template<typename T>
inline T quick_multiply_modulo (T a, T b, const T &modu)
{
    T res (0);
    a %= modu, b %= modu;
    if (a < b)
    {
        std::swap (a, b);
    }
    while (b)
    {
        if (b & 1)
        {
            res += a;
            if (res >= modu)
            {
                res -= modu;
            }
        }
        a <<= 1;
        if (a >= modu)
        {
            a -= modu;
        }
        b >>= 1;
    }
    return res;
}

inline i32 quick_multiply_modulo (i32 a, i32 b, i32 modu)
{
    return (i64) a * b % modu;
}

inline i64 quick_multiply_modulo (i64 a, i64 b, i64 modu)
{
    return ( (a * b - i64 ( (ld) a / modu * b) * modu) % modu + modu) % modu;
}

template<typename T>
inline T quick_power (T base, T expo)
{
    T res (1);
    while (expo)
    {
        if (expo & 1)
        {
            res *= base;
        }
        base *= base;
        expo >>= 1;
    }
    return res;
}

template<typename T>
inline T quick_power_modulo (T base, T expo, const T &modu)
{
    T res (1);
    base %= modu;
    while (expo)
    {
        if (expo & 1)
        {
            res = quick_multiply_modulo (res, base, modu);
        }
        base = quick_multiply_modulo (base, base, modu);
        expo >>= 1;
    }
    return res % modu;
}

template<typename T>
inline T euler (T n)
{
    T m = T (sqrt (n + 0.5)), ans = n;
    for (T i = 2; i <= m; ++i)
        if (n % i == 0)
        {
            ans = ans / i * (i - 1);
            while (n % i == 0)
            {
                n /= i;
            }
        }
    if (n > 1)
    {
        ans = ans / n * (n - 1);
    }
    return ans;
}

template<typename T, typename... TS>
inline T multiple_power_modulo (T base, const T &modu, T expo, TS... expos)
{
    if constexpr (sizeof... (expos) == 0)
    {
        return quick_power_modulo (base, expo, modu);
    }
    else
    {
        return quick_power_modulo (base,
                                   multiple_power_modulo (expo, euler (modu), expos...),
                                   modu);
    }
}

template<typename T>
inline T modular_multiplicative_inverse (const T &a, const T &modu)
{
    T x, y;
    return extended_euclidean (a, modu, x, y) == 1 ? (x % modu + modu) % modu : -1;
}

template<typename T>
inline T chinese_remainder_theorem (uint n, T a[], T m[])
{
    T M = 1, ans = 0;
    for (uint i = 0; i < n; ++i)
    {
        M *= m[i];
    }
    for (uint i = 0; i < n; ++i)
    {
        auto t = M / m[i];
        ans = (ans + t * extended_euclidean (t, m[i]).first * a[i]) % M;
    }
    if (ans < 0)
    {
        ans += M;
    }
    return ans;
}

#endif