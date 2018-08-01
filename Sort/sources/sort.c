#include "sort.h"

void insertionSort(int array[], int length, int gap, bool isAscend)
{
    int temp, j;

    // i always points to the first position of unsorted subarray.
    for (int i = gap; i < length; i++)
    {
        temp = array[i];

        // j always points to the sorted subarray from the back to the front.
        for (j = i - gap; j >= 0 && (isAscend ? temp < array[j] : temp > array[j]); j -= gap)
        {
            array[j + gap] = array[j]; // right shift.
        }
        array[j + gap] = temp;
    }
}

void simpleInsertionSort(int array[], int length, bool isAscend)
{
   insertionSort(array, length, 1, isAscend);
}

void shellSort(int array[], int length, bool isAscend)
{
    for (int gap = length >> 1; gap > 0; gap >>= 1)
        insertionSort(array, length, gap, isAscend);
}

void bubbleSort(int array[], int length, bool isAscend)
{
    bool isSortdFlag = false;
    for (int i = length - 1; i >= 0; i--)
    {
        isSortdFlag = false;
        for (int j = 0; j < i; j++)
        {
            if (isAscend ? array[j] > array[j + 1] : array[j] < array[j + 1])
            {
                array[j] = array[j] ^ array[j + 1];
                array[j + 1] = array[j] ^ array[j + 1];
                array[j] = array[j] ^ array[j + 1];
                isSortdFlag = true;
            }
        }
        if (!isSortdFlag)
        {
            break;
        }
    }
}

void selectionSort(int array[], int length, bool isAscend)
{
    int value = 0;
    int index = 0;

    // i points to the first element of unsorted subarray.
    for (int i = 0; i < length - 1; i++)
    {
        index = i + 1;
        value = array[index];

        // j is used to traverse the unsorted subarray.
        for (int j = index; j < length; j++)
        {
            if (isAscend ? value > array[j] : value < array[j])
            {
                value = array[j];
                index = j;
            }
        }

        array[i] = array[i] ^ array[index];
        array[index] = array[i] ^ array[index];
        array[i] = array[i] ^ array[index];
    }
}

void merge(int array[], int start, int mid, int end, bool isAscend)
{
    int* temp = (int *)calloc(end - start + 1, sizeof(int));
    int index1 = start, index2 = mid + 1, tempIndex = 0;

    while (index1 <= mid && index2 <= end)
    {
        if (array[index1] <= array[index2])
            temp[tempIndex++] = isAscend ? array[index1++] : array[index2++];
        else
            temp[tempIndex++] = isAscend ? array[index2++] : array[index1++];
    }
    while(index1 <= mid)
        temp[tempIndex++] = array[index1++];
    while (index2 <= end)
        temp[tempIndex++] = array[index2++];

    // Copy the sorted temp array into the actual array.
    for (index1 = start, tempIndex = 0; tempIndex < end - start + 1;)
        array[index1++] = temp[tempIndex++];
    free(temp);
}

void division(int array[], int start, int end, bool isAscend)
{
    if (end > start)
    {
        int mid = (start + end) >> 1;
        division(array, start, mid, isAscend);
        division(array, mid + 1, end, isAscend);
        if (isAscend ? array[mid] > array[mid + 1] : array[mid] < array[mid + 1])
            merge(array, start, mid, end, isAscend);
    }
}

void mergeSortRecursion(int array[], int length, bool isAscend)
{
    if (length != 0)
        division(array, 0, length - 1, isAscend);
}

int findMidVal(int a, int b, int c)
{
    int max = a > b ? a : b;
    int min = a < b ? a : b;
    max = max > c ? max : c;
    min = min < c ? min : c;
    return a + b + c - max - min;
}

int partition(int array[], int start, int end, bool isAscend)
{
    // Find the proper pivot.
    int mid = (start + end) >> 1;
    int pivotValue = findMidVal(array[start], array[mid], array[end]);
    int pivotIndex = (pivotValue == array[start]) ? start : (pivotValue == array[mid] ? mid : end);
    int left = start, right = end;

    // Swap the pivot value with the start element.
    if (pivotIndex != start)
    {
        array[start] = array[start] ^ array[pivotIndex];
        array[pivotIndex] = array[start] ^ array[pivotIndex];
        array[start] = array[start] ^ array[pivotIndex];
        pivotIndex = start;
    }

    while (left < right)
    {
        while (left < right && (isAscend ? array[right] >= pivotValue : array[right] <= pivotValue))
            right--;

        if (left < right)
            array[left++] = array[right];

        while (left < right && (isAscend ? array[left] <= pivotValue : array[left] >= pivotValue))
            left++;

        if (left < right)
            array[right--] = array[left];
    }

    array[left] = pivotValue;
    return left;
}

void quickSort(int array[], int start, int end, bool isAscend)
{
    if (end > start)
    {
        int pivotIndex = partition(array, start, end, isAscend);
        if (pivotIndex > start)
            quickSort(array, start, pivotIndex - 1, isAscend);
        if (pivotIndex < end)
            quickSort(array, pivotIndex + 1, end, isAscend);
    }
}

// Adjust the heap to maximum heap or minimum heap.
void heapify(int array[], int length, int rootIndex, bool isAscend)
{
    int extremum = rootIndex;
    int lChild = 2 * rootIndex + 1;
    int rChild = 2 * rootIndex + 2;

    if (lChild < length && (isAscend ? array[lChild] > array[rootIndex] : array[lChild] < array[rootIndex]))
        extremum = lChild;

    if (rChild < length && (isAscend ? array[rChild] > array[extremum] : array[rChild] < array[extremum]))
        extremum = rChild;

    // if the maximum or minimum is not the root index.
    if (extremum != rootIndex)
    {
        // Swap the value of root index and the largest one.
        array[rootIndex] = array[rootIndex] ^ array[extremum];
        array[extremum] = array[rootIndex] ^ array[extremum];
        array[rootIndex] = array[rootIndex] ^ array[extremum];

        heapify(array, length, extremum, isAscend);
    }
}

void heapSort(int array[], int length, bool isAscend)
{
    // Build the heap, the index of the first non-leaf node is "length/2 - 1"
    for (int adjIndex = (length / 2) - 1; adjIndex >= 0; adjIndex--)
        heapify(array, length, adjIndex, isAscend);

    // Owing to the first element is the largest or smallest one in the heap,
    // so after swap the first element with the last element each cycle and you will get the sorted array at last.
    for (int i = length - 1; i > 0; i--)
    {
        array[0] = array[0] ^ array[i];
        array[i] = array[0] ^ array[i];
        array[0] = array[0] ^ array[i];

        heapify(array, i, 0, isAscend);
    }
}