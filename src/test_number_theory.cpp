#include <iostream>
#include <cstdlib>
#include <ctime>

#include "math/number_theory.hpp"
#include "gtest/gtest.h"

using namespace std;

TEST (GcdTest, Case0)
{
    EXPECT_EQ (gcd (1, 0), 1);
    EXPECT_EQ (gcd (12, 27), 3);
    EXPECT_EQ (gcd (-5, -10), 5);
    EXPECT_EQ (gcd (5, -10), 5);
}

TEST (LcmTest, Case0)
{
    EXPECT_EQ (lcm (1, 0), 0);
    EXPECT_EQ (lcm (12, 27), 108);
    EXPECT_EQ (lcm (-5, -10), 10);
    EXPECT_EQ (lcm (-5, 10), 10);
}

TEST (ExtendedEuclideanTest, Case0)
{
    auto pair = extended_euclidean (56, 44);
    EXPECT_EQ (pair.first * 56 + pair.second * 44, gcd (56, 44));
}

TEST (QuickMultiplyTest, Case0)
{
    srand (time (NULL));
    for (int i = 0; i < 10; ++i)
    {
        int x = rand(), y = rand();
        EXPECT_EQ (x * y, quick_multiply (x, y));
    }
}

TEST (QuickMultiplyModuloTest, Case0)
{
    srand (time (NULL));
    for (int i = 0; i < 10; ++i)
    {
        int x = rand(), y = rand(), m = rand();
        EXPECT_EQ (x * y % m, quick_multiply_modulo (x, y, m));
    }
}

TEST (QuickMultiplyModuloTest, Case1)
{
    u64 a = 314882150829468584, b = 427197303358170108, m = 2009731336725594113;
    EXPECT_EQ (quick_multiply_modulo (a, b, m), 1068339687814403024);
}

TEST (QuickPowerTest, Case0)
{
    EXPECT_EQ (quick_power (2, 0), 1);
    EXPECT_EQ (quick_power (2, 10), 1 << 10);
    EXPECT_EQ (quick_power (2, 20), 1 << 20);
    EXPECT_EQ (quick_power (2, 30), 1 << 30);
}

TEST (QuickPowerModuloTest, Case0)
{
    EXPECT_EQ (quick_power_modulo (2, 0, 1), 0);
    EXPECT_EQ (quick_power_modulo (2, 10, 100), 24);
    EXPECT_EQ (quick_power_modulo (2, 20, 1000), (1 << 20) % 1000);
    EXPECT_EQ (quick_power_modulo (4, 15, 100000), (1 << 30) % 100000);
}

TEST (EulerTest, Case0)
{
    EXPECT_EQ (euler (1), 1);
    EXPECT_EQ (euler (10), 4);
    EXPECT_EQ (euler (17), 16);
    EXPECT_EQ (euler (100), 40);
    EXPECT_EQ (euler (1000), 400);
}

TEST (MultiplePowerModuloTest, Case0)
{
    u64 a = 3423748327827483274, b = 3, c = 2020, m = 43857843758454553;
    EXPECT_EQ (multiple_power_modulo (a, m, b, c), 42253204095794777);
}

TEST (ModularMultiplicativeInverseTest, Case0)
{
    EXPECT_EQ (modular_multiplicative_inverse (17, 13), 10);
    EXPECT_EQ (modular_multiplicative_inverse (2, 5), 3);
    EXPECT_EQ (modular_multiplicative_inverse (13, 105), 97);
}

TEST (ChineseRemainderTheoremTest, Case0)
{
    const uint n = 4;
    int a[n] = {1, 1, 3, 5}, m[n] = {2, 3, 5, 7};
    EXPECT_EQ (chinese_remainder_theorem (n, a, m), 103);
}

TEST (ChineseRemainderTheoremTest, Case1)
{
    const uint n = 4;
    int a[n] = {1, 2, 3, 4}, m[n] = {11, 3, 5, 7};
    EXPECT_EQ (chinese_remainder_theorem (n, a, m), 683);
}

TEST (ChineseRemainderTheoremTest, Case2)
{
    const uint n = 3;
    int a[n] = {2, 3, 2}, m[n] = {3, 5, 7};
    EXPECT_EQ (chinese_remainder_theorem (n, a, m), 23);
}

TEST (ChineseRemainderTheoremTest, Case3)
{
    const uint n = 2;
    int a[n] = {16, 1}, m[n] = {9, 7};
    EXPECT_EQ (chinese_remainder_theorem (n, a, m), 43);
}