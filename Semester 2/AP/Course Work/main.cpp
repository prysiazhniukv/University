#include "radixSort.h"
#include "bucketSort.h"
#include "countSort.h"
#include <chrono>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

void fillVector(std::vector<int>& vec, int numElements, int min, int max) {
  vec.clear();
  srand(static_cast<unsigned int>(time(NULL)));
  for (int i = 0; i < numElements; ++i) {
    int randomValue = min + (rand() % (max - min + 1));
    vec.push_back(randomValue);
  }
}

int main() {
  srand(static_cast<unsigned int>(time(NULL)));
  std::vector<int> vec;
  fillVector(vec, 1000000, 1, 1000000);
  std::vector<int> vec1 = vec;
  std::vector<int> vec2 = vec;

  auto start = std::chrono::high_resolution_clock::now();
  radixSort(vec);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time taken by Radix Sort: " << duration.count() << " milliseconds" << std::endl;

  auto start1 = std::chrono::high_resolution_clock::now();
  bucketSort(vec1);
  auto stop1 = std::chrono::high_resolution_clock::now();
  auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
  std::cout << "Time taken by Bucket Sort: " << duration1.count() << " milliseconds" << std::endl;

  auto start2 = std::chrono::high_resolution_clock::now();
  countSort(vec2);
  auto stop2 = std::chrono::high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);
  std::cout << "Time taken by Count Sort: " << duration2.count() << " milliseconds" << std::endl;

  return 0;
}
