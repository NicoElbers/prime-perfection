#ifndef PRIME_GENERATOR
#define PRIME_GENERATOR

#include <memory>
#include <vector>

namespace gen {
// Return a unique pointer
// to the vector with all primes generated
// by the function
//
// Simple algorithm
std::vector<int> naive(int);

// Return a unique pointer
// to the vector with all primes generated
// by the function
//
// Smart, optimized algorithm
std::vector<int> smart(int);

// Return a unique pointer
// to the vector with all primes generated
// by the function
//
// Smart, optimized algorithm
std::vector<int> multi_op(int);

// Return a unique pointer
// to the vector with all primes generated
// by the function
//
// Smart, optimized algorithm and multi threaded
std::vector<int> multi_thread(int n, int threads);
} // namespace gen

#endif
