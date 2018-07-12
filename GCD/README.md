# Computing the greatest common divisor

## Euclidean -- (欧几里得算法、辗转相除法)

假设两个数a,b且a>b。 设a除以b商k，余数为r，那么会有a=k*b+r，那么b和r的最大公约数，就是a和b的最大公约数。所以问题就转换求成除数和余数的最大公约数，依次递归，递归的出口就是一个已知的条件：如果a能够被b整除,那么b就是a和b的最大公约数。

证明：

    不妨设A > B，设A和B的最大公约数为X，所以 A=aX，B=bX，其中a和b都为正整数且a>b。

    A除以B的余数： R = A - k*B，其中k为正整数是A除以B的商，所以
    R=A−k∗B=aX−kbX=(a−kb)X

    因为a、k、b均为正整数，所以R也能被X整除
    即A、B、R的公约数相同，所以有gcd(A，B) = gcd(B，A mod B)

Code

* Recursion

```C
int euclidean_Recursion(int m, int n)
{
    int max = m > n ? m : n;
    int min = m < n ? m : n;
    if (min == 0)
        return max;
    return euclidean_Recursion(min, max % min);
 }
```

* Non-Recursion

```C
 int euclidean_nonRecursion(int m, int n)
 {
    int max = m > n ? m : n;
    int min = m < n ? m : n;
    while (min != 0) {
        int remainder = max % min;
        max = min;
        min = remainder;
    }
    return max;
 }
```

```求多个数的最大公约数，可以将多个数两两分组，再用欧几里得算法进行求取。```

## Stein algorithm

欧几里德算法是计算两个数最大公约数的传统算法，无论从理论还是从实际效率上都是很好的。但是却有一个致命的缺陷，这个缺陷在素数比较小的时候一般是感觉不到的，只有在大素数时才会显现出来：一般实际应用中的整数很少会超过64位（当然现在已经允许128位了），对于这样的整数，计算两个数之间的模是很简单的。对于字长为32位的平台，计算两个不超过32位的整数的模，只需要一个指令周期，而计算64位以下的整数模，也不过几个周期而已。但是对于更大的素数，这样的计算过程就不得不由用户来设计，为了计算两个超过64位的整数的模，用户也许不得不采用类似于多位数除法手算过程中的试商法，这个过程不但复杂，而且消耗了很多CPU时间。对于现代密码算法，要求计算128位以上的素数的情况比比皆是，比如说RSA加密算法至少要求500bit密钥长度，设计这样的程序迫切希望能够抛弃除法和取模。

Stein算法很好的解决了欧几里德算法中的这个缺陷，Stein算法只有整数的移位和加减法。下面就来说一下Stein算法的原理：

* 若a和b都是偶数，则记录下公约数2，然后都除以2（即右移1位）；

* 若其中一个数是偶数，则偶数除2，因为此时2不可能是这两个数的公约数了；

* 若两个都是奇数，则a = |a-b|，b = min(a,b)，因为若d是a和b的公约数，那么d也是|a-b|和min(a,b)的公约数。

这里面可能就第三句话难理解一点，这里进行简单的证明：

    不妨设奇数A>B，A和B的公约数为X，即A=jX，B=kX，其中j，k均为正整数且j>k,
    A − B = (j − k)X

    因为j，k均为整数，所以X也是A-B的公约数。
    min(A,B)=B

    所以A-B与min(A,B)公约数相同，因为A，B都是奇数，所以A-B必然是偶数，偶数又可以二除移位了。

Code

* Recursion

```C

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

```

* Non-Recursion

```C

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

        // Record the times of simultaneous right shift of m and n.
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

```

## The least common multiple

1. Computing the greatest common divisor;

2. Multiply these number and divide the GCD, then you will get the LCM.

---
The more info, click [here](https://blog.csdn.net/Holmofy/article/details/76401074)