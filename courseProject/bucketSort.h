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
        if (!buckets[i].empty()) {
            // Apply Counting Sort directly within the bucket
            T minBucketValue = *std::min_element(buckets[i].begin(), buckets[i].end());
            T maxBucketValue = *std::max_element(buckets[i].begin(), buckets[i].end());
            setOps += 2 * (buckets[i].size() - 1);

            std::vector<int> count(static_cast<size_t>(maxBucketValue - minBucketValue + 1), 0);

            for (size_t j = 0; j < buckets[i].size(); ++j) {
                count[static_cast<size_t>(buckets[i][j] - minBucketValue)]++;
                setOps++;
            }

            size_t bucketIndex = 0;
            for (size_t j = 0; j < count.size(); ++j) {
                while (count[j]-- > 0) {
                    buckets[i][bucketIndex++] = j + minBucketValue;
                    setOps++;
                }
            }
        }

        for (const T& elem : buckets[i]) {
            arr[index++] = elem;
            setOps++;
        }
    }
}

#endif // BUCKETSORT_H
