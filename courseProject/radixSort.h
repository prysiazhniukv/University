#include <iostream>
#include <vector>
#include <algorithm> // Include for std::max_element

template<typename T>
void radixSort(std::vector<T>& arr, unsigned long long& setOps) {
    if (arr.empty()) return; // Early exit if array is empty

    // Use std::max_element to find the maximum element in the array
    T max = *std::max_element(arr.begin(), arr.end());
    setOps += arr.size() - 1; // Increment setOps for each comparison in max_element

    for (T exp = 1; max / exp > 0; exp *= 10) {
        std::vector<T> output(arr.size());
        int count[10] = {0};

        // Count occurrences of each digit
        for (size_t i = 0; i < arr.size(); i++) {
            count[(arr[i] / exp) % 10]++;
        }

        // Change count[i] so it contains actual position of this digit in output[]
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            setOps++; // Increment set operation for each element placement in output
            count[(arr[i] / exp) % 10]--;
        }

        // Copy the output array to arr[], so that arr[] now contains sorted numbers
        for (size_t i = 0; i < arr.size(); i++) {
            arr[i] = output[i];
            setOps++; // Increment set operation for copying back to the main array
        }
    }
}
