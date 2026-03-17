#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <iomanip>

// A large array to make sure we're not just fitting everything in L1/L2 cache
const int NUM_ELEMENTS = 10000000; // 10 million elements

// This function sums elements of the vector with a given stride
long long accessWithStride(const std::vector<int>& vec, int stride) {
    long long sum = 0;
    for (int i = 0; i < NUM_ELEMENTS; i += stride) {
        sum += vec[i];
    }
    return sum;
}

int main() {
    std::vector<int> vec;
    // Pre-fill the vector with some values
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        vec.push_back(i % 100); // Use modulo to keep values small
    }

    std::cout << "Benchmarking array access with different strides..." << std::endl;
    std::cout << "Assuming 4-byte integers and a 64-byte cache line." << std::endl;
    std::cout << "A stride of 16 means every access should be in a new cache line (16 * 4 = 64 bytes)." << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(8) << "Stride" << std::setw(20) << "Total Time (ns)" << std::setw(28) << "Time per Access (ns)" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    for (int stride = 1; stride <= 64; stride *= 2) {
        auto start = std::chrono::high_resolution_clock::now();
        
        // Run the access function
        long long sum = accessWithStride(vec, stride);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        
        int accesses = NUM_ELEMENTS / stride;
        double timePerAccess = static_cast<double>(duration.count()) / accesses;

        std::cout << std::setw(8) << stride 
                  << std::setw(20) << duration.count()
                  << std::setw(28) << std::fixed << std::setprecision(2) << timePerAccess
                  << "   (sum: " << sum << ")" << std::endl; // Print sum to prevent optimization
    }
    
    std::cout << "--------------------------------------------------------------------------" << std::endl;
    std::cout << "\nNotice the jump in 'Time per Access' when the stride is >= 16." << std::endl;

    return 0;
}
