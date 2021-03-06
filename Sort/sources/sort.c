#include "sort.h"

void insertionSort(int array[], int length, int gap, bool isAscend)
{
    int temp, j;

    // i always points to the first position of unsorted subarray.
    for (int i = gap; i < length; i++)
    {
        temp = array[i];

        // j's initial value is always the end of sorted subarray, and its direction of movement is from back to front.
        for (j = i - gap; j >= 0 && (isAscend ? temp < array[j] : temp > array[j]); j -= gap)
        {
            array[j + gap] = array[j]; // right shift.
        }
        array[j + gap] = temp; // insert the element i into the proper position.
    }
}

void simpleInsertionSort(int array[], int length, bool isAscend)
{
    // Simple inserion sort, the gap is 1.
    insertionSort(array, length, 1, isAscend);
}

void shellSort(int array[], int length, bool isAscend)
{
    // The initial value of gap is length / 2, then it will divide by 2 each cycle.
    for (int gap = length >> 1; gap > 0; gap >>= 1)
        insertionSort(array, length, gap, isAscend);
}

void bubbleSort(int array[], int length, bool isAscend)
{
    bool isSortedFlag = false;
    for (int i = length - 1; i >= 0; i--)
    {
        isSortedFlag = false;
        for (int j = 0; j < i; j++)
        {
            if (isAscend ? array[j] > array[j + 1] : array[j] < array[j + 1])
            {
                // exchange the value between array[j] and array[j + 1]
                array[j] = array[j] ^ array[j + 1];
                array[j + 1] = array[j] ^ array[j + 1];
                array[j] = array[j] ^ array[j + 1];

                isSortedFlag = true;
            }
        }
        if (!isSortedFlag)
        {
            break;
        }
    }
}

void selectionSort(int array[], int length, bool isAscend)
{
    int index = 0;  // Store the index of the value when it's max or min.

    // i points to the first element of unsorted subarray.
    for (int i = 0; i < length - 1; i++)
    {
        index = i;

        // j is used to traverse the unsorted subarray.
        for (int j = i + 1; j < length; j++)
        {
            if (isAscend ? array[index] > array[j] : array[index] < array[j])
            {
                index = j;
            }
        }

        // Find the max or min value and exchange it with i.
        if (i != index)
        {
            array[i] = array[i] ^ array[index];
            array[index] = array[i] ^ array[index];
            array[i] = array[i] ^ array[index];
        }
    }
}

void merge(int array[], int start, int mid, int end, bool isAscend)
{
    int* temp = (int *)calloc(end - start + 1, sizeof(int));    // temp array is for the merge operation from two devided parts
    int index1 = start, index2 = mid + 1, tempIndex = 0;

    // Merge the two parts into temp array in some order.
    while (index1 <= mid && index2 <= end)
    {
        if (array[index1] <= array[index2])
            temp[tempIndex++] = isAscend ? array[index1++] : array[index2++];
        else
            temp[tempIndex++] = isAscend ? array[index2++] : array[index1++];
    }

    // If right part isn't completed, merge the rest into the temp array.
    while(index1 <= mid)
        temp[tempIndex++] = array[index1++];

    // If left part isn't completed, merge the rest into the temp array as well.
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

        // Divide left part.
        division(array, start, mid, isAscend);

        // Divide right part.
        division(array, mid + 1, end, isAscend);

        // Though it has no regularity when dividing into two parts, there is a rule that when merging two parts, the beginning of two parts both are the min(max) element, and the end of two parts are the max(min) element in their respective parts. If the end of right part is less than the beginning of the left, means these two parts have been sorted, don't need to do merging operation, or else carry out the merge function.
        if (isAscend ? array[mid] > array[mid + 1] : array[mid] < array[mid + 1])
            merge(array, start, mid, end, isAscend);
    }
}

void mergeSortRecursion(int array[], int length, bool isAscend)
{
    if (length != 0)
        division(array, 0, length - 1, isAscend);
}

/ Find the median
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

    // Swap the pivot with the first element because it's convenient for the code implementation if the pivot is the first element. According to the following code, the first element will be overwritten by the proper right element, at that time, the right element will appear twice, and then it will also be overwritten by other left element...all elements have chance to appear twice except for the first one, on account of that, if the pivot is the first one, the first element can appear not only in array[0], but also in pivot, and don't need to worry about the overwritten problem. Eventually, the pivot can overwrite the element where the left and the right index point simultaneously.
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

    if (lChild < length && (isAscend ? array[lChild] > array[extremum] : array[lChild] < array[extremum]))
        extremum = lChild;

    if (rChild < length && (isAscend ? array[rChild] > array[extremum] : array[rChild] < array[extremum]))
        extremum = rChild;

    // if the maximum or minimum is not the root index.
    if (extremum != rootIndex)
    {
        // Swap the value of root with the smallest(largest) one.
        array[rootIndex] = array[rootIndex] ^ array[extremum];
        array[extremum] = array[rootIndex] ^ array[extremum];
        array[rootIndex] = array[rootIndex] ^ array[extremum];

        // Recursively adjusting the heap
        heapify(array, length, extremum, isAscend);
    }
}

void heapSort(int array[], int length, bool isAscend)
{
    // Build the heap(complete binary tree), the index of the first non-leaf node is "length/2 - 1", we choose it as the first node (which has child nodes) to recursively build heap.
    for (int adjIndex = (length / 2) - 1; adjIndex >= 0; adjIndex--)
        heapify(array, length, adjIndex, isAscend);

    // Owing to the first element is the largest or smallest one in the heap(i.e. the root node in complete binary tree), after swapping the first element with the last element and adjusting heap each cycle, you will get the sorted array at last.
    for (int i = length - 1; i > 0; i--)
    {
        array[0] = array[0] ^ array[i];
        array[i] = array[0] ^ array[i];
        array[0] = array[0] ^ array[i];

        heapify(array, i, 0, isAscend);
    }
}