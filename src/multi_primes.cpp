#include "multi_primes.h"
#include "is_prime.h"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int> prime_thread(int start, int end) {
  if ((start - 5) % 6 != 0) {
    std::cerr << "ERROR: invalid start number in thread "
              << std::this_thread::get_id() << std::endl;
    std::cerr << "The invalid start num is " << start << std::endl;
    exit(1);
  }

  std::vector<int> primes;
  for (int i = start; i <= end; i += 6) {
    if (isPrime::smart(i))
      primes.push_back(i);

    if (isPrime::smart(i + 2))
      primes.push_back(i + 2);
  }

  return primes;
}
