#include "sort.h"

#define ARRAY_SIZE 6

void printArray(int array[], int length)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{
    int array[ARRAY_SIZE] = {5, 4, 80, 555, 8, 9};
/*
    printf("Simple insertion sort: ");
    simpleInsertionSort(array, ARRAY_SIZE, true);
    printArray(array, ARRAY_SIZE);

    printf("Shell sort: ");
    shellSort(array, ARRAY_SIZE, true);
    printArray(array, ARRAY_SIZE);

    printf("Bubble sort: ");
    bubbleSort(array, ARRAY_SIZE, false);
    printArray(array, ARRAY_SIZE);

    printf("Selection sort: ");
    selectionSort(array, ARRAY_SIZE, true);
    printArray(array, ARRAY_SIZE);

    printf("Merge sort: ");
    mergeSortRecursion(array, ARRAY_SIZE, false);
    printArray(array, ARRAY_SIZE);

    printf("Quick sort: ");
    quickSort(array, 0, ARRAY_SIZE - 1, true);
    printArray(array, ARRAY_SIZE);
*/

    printf("Heap sort: ");
    heapSort(array, ARRAY_SIZE, false);
    printArray(array, ARRAY_SIZE);

    return 0;
}