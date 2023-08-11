#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>


using namespace std;




void findMaxPartial(const vector<int>& arr, size_t start, size_t end, int& partialMax) {
    partialMax = *max_element(arr.begin() + start, arr.begin() + end);
}


int main() {
   
    const int arraySize = 100;


    vector<int> arr(arraySize);
    for (int i = 0; i < arraySize; ++i) {
        arr[i] = i + 1;
    }


    const int numThreads = 4;


   
    int elementsPerThread = arraySize / numThreads;


    vector<thread> threads;


    vector<int> partialMaxValues(numThreads, 0);


    for (int i = 0; i < numThreads; ++i) {
        size_t start = i * elementsPerThread;
        size_t end = (i == numThreads - 1) ? arraySize : start + elementsPerThread;
        threads.emplace_back(findMaxPartial, ref(arr), start, end, ref(partialMaxValues[i]));
    }


    for (auto& thread : threads) {
        thread.join();
    }


    int maxValue = *max_element(partialMaxValues.begin(), partialMaxValues.end());


    cout << "El valor máximo del arreglo es: " << maxValue << endl;


    return 0;
}
