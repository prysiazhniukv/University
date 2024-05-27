#include "radixSort.h"
#include "bucketSort.h"
#include "countSort.h"
#include <chrono>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>

namespace chrono = std::chrono;

void fillVectorRandom(std::vector<int>& vec, int numElements, int min, int max) {
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < numElements; ++i) {
        int randomValue = min + (rand() % (max - min + 1));
        vec.push_back(randomValue);
    }
}

void fillDecreasingVector(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        vec[i] = n - i;
    }
}

void fillIncreasingVector(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        vec[i] = i;
    }
}

void fillConstantVector(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        vec[i] = 0;
    }
}

int main() {

    int rand_Size, minrand, maxrand;

    std::cout << "Please set the array size for Random array:" << std::endl;
    std::cin >> rand_Size;
    std::cout << "Please set the minimum element in Random array:" << std::endl;
    std::cin >> minrand;
    std::cout << "Please set the maximum element in Random array:" << std::endl;
    std::cin >> maxrand;

    std::vector<int> Rand_vec1(rand_Size);
    fillVectorRandom(Rand_vec1, rand_Size, minrand, maxrand);
    std::vector<int> Rand_vec2 = Rand_vec1;
    std::vector<int> Rand_vec3 = Rand_vec1;

    int dec_Size;

    std::cout << "Please set the array size for Decreasing array:" << std::endl;
    std::cin >> dec_Size;

    std::vector<int> Dec_vec1(dec_Size);
    fillDecreasingVector(Dec_vec1);
    std::vector<int> Dec_vec2 = Dec_vec1;
    std::vector<int> Dec_vec3 = Dec_vec1;

    int inc_Size;

    std:: cout << "Please set the array size for Increasing array:" << std::endl;
    std::cin >> inc_Size;
    std::vector<int> Inc_vec1(inc_Size);
    fillIncreasingVector(Inc_vec1);
    std::vector<int> Inc_vec2 = Inc_vec1;
    std::vector<int> Inc_vec3 = Inc_vec1;

    int cst_Size;
    std::cout << "Please set the array size for Constant array:" << std::endl;
    std::cin >> cst_Size;
    std::vector<int> Cst_vec1(cst_Size);
    fillConstantVector(Cst_vec1);
    std::vector<int> Cst_vec2 = Cst_vec1;
    std::vector<int> Cst_vec3 = Cst_vec1;

    unsigned long long Radix_setOps = 0, Bucket_setOps = 0, Count_setOps = 0;

    std::cout << "\n" << std::endl;
    std::cout << "Running test's:" << std::endl;
    std::cout << "\n" << std::endl;

    // Radix Sort for Random Vector
    std::cout << "Radix Sort for Random Vector" << std::endl;
    auto start = chrono::high_resolution_clock::now();
    radixSort(Rand_vec1, Radix_setOps);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    double seconds = duration * 1e-9;
    std::cout << "Radix Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Radix_setOps << std::endl;

    // Bucket Sort for Random Vector
    std::cout << "Bucket Sort for Random Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    bucketSort(Rand_vec2, Bucket_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Bucket Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Bucket_setOps << std::endl;

    // Counting Sort for Random Vector
    std::cout << "Counting Sort for Random Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    countSort(Rand_vec3, Count_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Counting Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Count_setOps << std::endl;

    std::cout << "\n\n";

    // Radix Sort for Decreasing Vector
    std::cout << "Radix Sort for Decreasing Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    radixSort(Dec_vec1, Radix_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Radix Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Radix_setOps << std::endl;

    // Bucket Sort for Decreasing Vector
    std::cout << "Bucket Sort for Decreasing Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    bucketSort(Dec_vec2, Bucket_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Bucket Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Bucket_setOps << std::endl;

    // Counting Sort for Decreasing Vector
    std::cout << "Counting Sort for Decreasing Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    countSort(Dec_vec3, Count_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Counting Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Count_setOps << std::endl;

    std::cout << "\n\n";

    // Radix Sort for Increasing Vector
    std::cout << "Radix Sort for Increasing Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    radixSort(Inc_vec1, Radix_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Radix Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Radix_setOps << std::endl;

    // Bucket Sort for Increasing Vector
    std::cout << "Bucket Sort for Increasing Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    bucketSort(Inc_vec2, Bucket_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Bucket Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Bucket_setOps << std::endl;

    // Counting Sort for Increasing Vector
    std::cout << "Counting Sort for Increasing Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    countSort(Inc_vec3, Count_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Counting Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Count_setOps << std::endl;

    std::cout << "\n\n";

    // Radix Sort for Constant Vector
    std::cout << "Radix Sort for Constant Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    radixSort(Cst_vec1, Radix_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Radix Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Radix_setOps << std::endl;

    // Bucket Sort for Constant Vector
    std::cout << "Bucket Sort for Constant Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    bucketSort(Cst_vec2, Bucket_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Bucket Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Bucket_setOps << std::endl;

    // Counting Sort for Constant Vector
    std::cout << "Counting Sort for Constant Vector" << std::endl;
    start = chrono::high_resolution_clock::now();
    countSort(Cst_vec3, Count_setOps);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    seconds = duration * 1e-9;
    std::cout << "Counting Sort took " << std::fixed << std::setprecision(15) << seconds << " seconds" << std::endl;
    std::cout << "Set Operations: " << Count_setOps << std::endl;

    return 0;
}
