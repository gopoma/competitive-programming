#include <iostream>
#include <vector>
#include <thread>


using namespace std;


void sumPartial(const vector<int>& arr, size_t start, size_t end, int& partialSum) {
    for (size_t i = start; i < end; ++i) {
        partialSum += arr[i];
    }
}


int main() {
    const int arraySize = 10;


    vector<int> arr(arraySize);
    for (int i = 0; i < arraySize; ++i) {
        arr[i] = i + 1;
    }


    const int numThreads = 4;


    int elementsPerThread = arraySize / numThreads;


    vector<thread> threads;


    vector<int> partialSums(numThreads, 0);


    for (int i = 0; i < numThreads; ++i) {
        size_t start = i * elementsPerThread;
        size_t end = (i == numThreads - 1) ? arraySize : start + elementsPerThread;
        threads.emplace_back(sumPartial, ref(arr), start, end, ref(partialSums[i]));
    }


    for (auto& thread : threads) {
        thread.join();
    }


    int totalSum = 0;
    for (int partialSum : partialSums) {
        totalSum += partialSum;
    }


    cout << "La suma total de los elementos del arreglo es: " << totalSum << endl;


    return 0;
}
