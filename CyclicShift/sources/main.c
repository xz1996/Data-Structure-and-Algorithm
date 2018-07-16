#include <stdio.h>
#include <stdlib.h>

#include "reverse.h"

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i ++)
    {
        printf(" %d", array[i]);
    }
    printf("\n");
}

int main()
{
    int p[] = {1, 2 , 3, 4, 5};
    int array_size = 5;     // array size
    int left_shift_num = 0;
    int right_shift_num = 0;
    printf("the raw array is :");
    printArray(p, array_size);

    // cyclic left shift.
    printf("please input the left shift num: ");
    scanf("%d", &left_shift_num);

    reverse(p, 0, left_shift_num - 1);
    reverse(p, left_shift_num, array_size - 1);
    reverse(p, 0, array_size - 1);

    printf("after cyclic left shift %d position, the new array is :", left_shift_num);
    printArray(p, array_size);

    // cyclic right shift.
    printf("please input the right shift num: ");
    scanf("%d", &right_shift_num);

    reverse(p, 0, array_size - right_shift_num - 1);
    reverse(p, array_size - right_shift_num, array_size - 1);
    reverse(p, 0, array_size -1);

    printf("after cyclic right shift %d position, the new array is :", right_shift_num);
    printArray(p, array_size);
}