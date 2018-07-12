#include <stdio.h>
#include <stdlib.h>
#include "commonDivisor.h"

int main()
{
    int m, n, c;
    do
    {
        printf("please input two nums: ");
        scanf("%d %d", &m, &n);
        printf("the greatest common divisor of %d and %d is : %d\n", m, n, stein_nonRecursion(m, n));
        c = getchar();
    } while (c == '\n');
}
