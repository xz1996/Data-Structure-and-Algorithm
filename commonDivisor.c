#include "commonDivisor.h"

int euclidean_recursion(int m, int n)
{
    int max = m > n ? m : n;
    int min = m < n ? m : n;
    if (min == 0)
        return max;
    return euclidean_recursion(min, max % min);
}

int euclidean_nonRecursion(int m, int n)
{
    if (m == 0 || n == 0)
    {
        printf("0 with any other number doesn't have the greatest common divisor!\n");
        return -1;
    }
    int max = m > n ? m : n;
    int min = m < n ? m : n;
    while (min != 0)
    {
        int remainder = max % min;
        max = min;
        min = remainder;
    }
    return max;
}

int stein_recursion(int m, int n)
{
    int min = m > n ? n : m;
    if (min == 0)
    {
        // return the another value.
        return m + n - min;
    }
    if ((m & 1) == 0 && (n & 1) == 0)
    {
        // m and n are all even number.
        return stein_recursion(m >> 1, n >> 1) << 1;
    }
    else if ((m & 1) != 0 && (n & 1) == 0)
    {
        // m is odd number, n is even number.
        return stein_recursion(m, n >> 1);
    }
    else if ((m & 1) == 0 && (n & 1) == 0)
    {
        // m is even number, n is odd number.
        return stein_recursion(m >> 1, n);
    }
    else
    {
        return stein_recursion(abs(m - n), min);
    }
}

int stein_nonRecursion(int m, int n)
{
    int min, m_temp, acc = 0;
    if (m == 0 || n == 0)
    {
        printf("0 with any other number doesn't have the greatest common divisor!\n");
        exit(EXIT_FAILURE);
    }

    while ((m & 1) == 0 && (n & 1) == 0)
    {
        m >>= 1;
        n >>= 1;
        ++acc;
    }
    do
    {
        while ((m & 1) == 0) {
            m >>= 1;
        }
        while ((n & 1) == 0) {
            n >>= 1;
        }
        m_temp = m;
        m = abs(m - n);
        n = m_temp > n ? n : m_temp;
        min = m > n ? n : m;
    } while (min != 0);
    return (m + n - min) << acc;
}
