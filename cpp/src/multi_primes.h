#ifndef MULTI_PRIMES_H
#define MULTI_PRIMES_H

#include <future>
#include <memory>
#include <vector>

// Will act as a single thread to generate all primes between start and end
// It is assume that (start - 5) is divisible by 6
//
// Returns a vector with all the generated primes in order
std::vector<int> prime_thread(int start, int end);

#endif
