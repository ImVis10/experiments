#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <numeric>

const int NUM_ELEMENTS = 100000;

int main() {
    // Create and populate a vector (acting as an array)
    std::vector<int> vec;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        vec.push_back(i);
    }

    // Create and populate a linked list
    std::list<int> linkedList;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        linkedList.push_back(i);
    }

    // Benchmark array traversal
    auto startArray = std::chrono::high_resolution_clock::now();
    long long arraySum = 0;
    for (int x : vec) {
        arraySum += x;
    }
    auto endArray = std::chrono::high_resolution_clock::now();
    auto arrayDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(endArray - startArray);

    // Benchmark linked list traversal
    auto startList = std::chrono::high_resolution_clock::now();
    long long listSum = 0;
    for (int x : linkedList) {
        listSum += x;
    }
    auto endList = std::chrono::high_resolution_clock::now();
    auto listDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(endList - startList);

    std::cout << "Summing " << NUM_ELEMENTS << " integers:" << std::endl;
    std::cout << "- Array (std::vector)      : " << arrayDuration.count() << " ns" << std::endl;
    std::cout << "- Linked List (std::list)  : " << listDuration.count() << " ns" << std::endl;
    
    // To ensure the sums are actually used and not optimized away
    if (arraySum != listSum) {
        std::cout << "Error: Sums do not match!" << std::endl;
    }

    return 0;
}
