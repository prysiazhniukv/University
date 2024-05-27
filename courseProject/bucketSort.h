#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
void bucketSort(std::vector<T>& arr, unsigned long long& setOps) {
    if (arr.empty()) return;

    T minValue = *std::min_element(arr.begin(), arr.end());
    T maxValue = *std::max_element(arr.begin(), arr.end());
    setOps += 2 * (arr.size() - 1);

    size_t bucketCount = arr.size();
    std::vector<std::vector<T>> buckets(bucketCount);

    T range = maxValue - minValue;

    if (range == 0) {
        range = 1;
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        size_t bucketIndex = static_cast<size_t>((arr[i] - minValue) * (bucketCount - 1) / range);  // Properly scaled index
        buckets[bucketIndex].push_back(arr[i]);
        setOps++;
    }

    size_t index = 0;
    for (size_t i = 0; i < bucketCount; ++i) {
        // Insertion Sort within each bucket
        for (size_t j = 1; j < buckets[i].size(); ++j) {
            T key = buckets[i][j];
            int k = j - 1;

            while (k >= 0 && buckets[i][k] > key) {
                buckets[i][k + 1] = buckets[i][k];
                setOps++;
                k--;
            }
            buckets[i][k + 1] = key;
            setOps++;
        }

        for (const T& elem : buckets[i]) {
            arr[index++] = elem;
            setOps++;
        }
    }
}

#endif // BUCKETSORT_H
