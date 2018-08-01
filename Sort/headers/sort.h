#ifndef SORT
#define SORT

/* ------------- header reference --------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ------------- method declaration -------------- */

/**
 * Following are the Time and Space complexity for the Insertion Sort algorithm.
 *
 * Worst Case Time Complexity [ Big-O ]: O(n^2)
 * Best Case Time Complexity [Big-omega]: O(n)
 * Average Time Complexity [Big-theta]: O(n^2)
 * Space Complexity: O(1)
 *
 * Insertion sort is stable.
 */
void simpleInsertionSort(int array[], int length, bool isAscend);

/**
 * Following are the Time and Space complexity for the Shell Sort algorithm.
 *
 * The time complexity of shell sort depends on the gap, while generally speaking:
 * Worst Case Time Complexity [ Big-O ]: O(n^2)
 * Best Case Time Complexity [Big-omega]: O(n)
 * Average Time Complexity [Big-theta]: O(n * log n)
 *
 * Space Complexity: O(1)
 *
 * Shell sort is unstable.
 */
void shellSort(int array[], int length, bool isAscend);

/**
 * Following are the Time and Space complexity for the Bubble Sort algorithm.
 *
 * Worst Case Time Complexity [ Big-O ]: O(n^2)
 * Best Case Time Complexity [Big-omega]: O(n)
 * Average Time Complexity [Big-theta]: O(n^2)
 * Space Complexity: O(1)
 *
 * Bubble sort is stable.
 */
void bubbleSort(int array[], int length, bool isAscend);

/**
 * Following are the Time and Space complexity for the Selection Sort algorithm.
 *
 * Worst Case Time Complexity [ Big-O ]: O(n^2)
 * Best Case Time Complexity [Big-omega]: O(n^2)
 * Average Time Complexity [Big-theta]: O(n^2)
 * Space Complexity: O(1)
 *
 * Selection sort is unstable.
 */
void selectionSort(int array[], int length, bool isAscend);

/**
 * Following are the Time and Space complexity for the Merge Sort algorithm.
 *
 * Worst Case Time Complexity [ Big-O ]: O(n*log n)
 * Best Case Time Complexity [Big-omega]: O(n*log n)
 * Average Time Complexity [Big-theta]: O(n*log n))
 * Space Complexity: O(n)
 *
 * Merge sort is stable.
 */
void mergeSortRecursion(int array[], int length, bool isAscend);

/**
 * Following are the Time and Space complexity for the Merge Sort algorithm.
 *
 * Worst Case Time Complexity [ Big-O ]: O(n^2)
 * Best Case Time Complexity [Big-omega]: O(n*log n)
 * Average Time Complexity [Big-theta]: O(n*log n))
 * Space Complexity (the stack of recursion):
 *      - Worst case O(n), it degenerates into bubble sort.
 *      - Best case O(log n).
 *
 * Quick sort is unstable.
 */
void quickSort(int array[], int start, int end, bool isAscend);

/**
 * Following are the Time and Space complexity for the Heap Sort algorithm.
 *
 * Worst Case Time Complexity [ Big-O ]: O(n*log n)
 * Best Case Time Complexity [Big-omega]: O(n*log n)
 * Average Time Complexity [Big-theta]: O(n*log n))
 * Space Complexity: O(1)
 *
 * Heap sort is unstable.
 */
void heapSort(int array[], int length, bool isAscend);

#endif // SORT