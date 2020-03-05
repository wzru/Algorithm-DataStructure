#ifndef NUMBER_THEORY_HPP
#define NUMBER_THEORY_HPP

#include <utility>
#include <cmath>

using int64 = long long;
using i64 = long long;
using u64 = unsigned long long;

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

#endif