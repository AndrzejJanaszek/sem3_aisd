#ifndef SORT_ALG
#define SORT_ALG

#include <iostream>

void swap(int& el1, int& el2){
    int tmp = el1;
    el1 = el2;
    el2 = tmp;
}

void bubbleSort(int* arr, int n, int& comparisonCount, int& swapCount) {
    bool swapped;
  
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisonCount++;
            if (arr[j] > arr[j + 1]) {
                swapCount++;
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
      
        if (!swapped)
            break;
    }
}

void insertionSort(int arr[], int n, int& comparisonCount, int& swapCount)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        swapCount++;
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            comparisonCount++;
            swapCount++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        comparisonCount++;
        swapCount++;
        arr[j + 1] = key;
    }
}

void selectionSort(int* arr, int n, int& comparisonCount, int& swapCount) {
    for (int i = 0; i < n - 1; ++i) {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; ++j) {
            comparisonCount++;
            if (arr[j] < arr[min_idx]) {

                // Update min_idx if a smaller
                // element is found
                min_idx = j; 
            }
        }

        // Move minimum element to its
        // correct position
        swapCount++;
        swap(arr[i], arr[min_idx]);
    }
}

int getNextGap(int gap)
{
    // Shrink gap by Shrink factor
    gap = (gap*10)/13;

    if (gap < 1)
        return 1;
    return gap;
}

void combSort(int a[], int n, int& comparisonCount, int& swapCount)
{
    // Initialize gap
    int gap = n;

    // Initialize swapped as true to make sure that
    // loop runs
    bool swapped = true;

    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == true)
    {
        // Find next gap
        gap = getNextGap(gap);

        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = false;

        // Compare all elements with current gap
        for (int i=0; i<n-gap; i++)
        {
            comparisonCount++;
            if (a[i] > a[i+gap])
            {
                swapCount++;
                swap(a[i], a[i+gap]);
                swapped = true;
            }
        }
    }
}

void shellSort(int arr[], int n, int& comparisonCount, int& swapCount)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted 
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];
            swapCount++;

            // shift earlier gap-sorted elements up until the correct 
            // location for a[i] is found
            int j;            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                comparisonCount++;
                swapCount++;
                arr[j] = arr[j - gap];
            }
            comparisonCount++;
            
            //  put temp (the original a[i]) in its correct location
            swapCount++;
            arr[j] = temp;
        }
    }
}

#endif