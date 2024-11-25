#include <iostream>
#include <chrono>
#include "sort_alg.h"


#define ARR_SIZE_1 1000
#define ARR_SIZE_2 4000
#define ARR_SIZE_3 16000

#define MAX_ELEMENT_VALUE INT32_MAX

void fillArrayWithRandomValues(int* arr, size_t n);

int main(int argc, char const *argv[])
{
    // --- --- --- SETUP --- --- ---
    srand(time(0));

    int arr1[ARR_SIZE_1] = {0};
    int arr2[ARR_SIZE_2] = {0};
    int arr3[ARR_SIZE_3] = {0};
    
    fillArrayWithRandomValues(arr1, ARR_SIZE_1);
    fillArrayWithRandomValues(arr2, ARR_SIZE_2);
    fillArrayWithRandomValues(arr3, ARR_SIZE_3);

    void (*sortFunctions[])(int*,int,int&, int&) = { bubbleSort, insertionSort, selectionSort, combSort, shellSort};
    std::string sortFunctionNames[5] = { "bubbleSort", "insertionSort", "selectionSort", "combSort", "shellSort"};

    int swapCount[3] = {0};
    int comparisonCount[3] = {0};
    std::chrono::microseconds durations[3];

    for(int f = 0; f < 5; f++){
        auto start = std::chrono::high_resolution_clock::now();
        sortFunctions[f](arr1, ARR_SIZE_1, comparisonCount[0], swapCount[0]);
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds durations[0] = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);


        start = std::chrono::high_resolution_clock::now();
        sortFunctions[f](arr2, ARR_SIZE_2, comparisonCount[1], swapCount[1]);
        stop = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds durations[0] = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);


        start = std::chrono::high_resolution_clock::now();
        sortFunctions[f](arr3, ARR_SIZE_3, comparisonCount[2], swapCount[2]);
        stop = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds durations[0] = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    }

    for(int f = 0; f < 5; f++){
        std::cout << "ALGORYTM: " << sortFunctionNames[f] << "\n";
        std::cout << "ALGORYTM: " << sortFunctionNames[f] << "\n";

    }
    

    return 0;
}

void fillArrayWithRandomValues(int* arr, size_t n){
    for(int i = 0; i < n; i++){
        arr[i] = rand() % MAX_ELEMENT_VALUE;
    }
}
