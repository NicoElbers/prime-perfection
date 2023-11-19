#ifndef MULTI_PRIMES_H
#define MULTI_PRIMES_H

#include <memory>
#include <vector>

// Will act as a single thread to generate all primes between start and end
// It is assume that (start - 5) is divisible by 6
//
// Returns a unique pointer to a vector with all the generated primes in order
std::unique_ptr<std::vector<int>> prime_bucket_thread(int start, int end);

#endif
