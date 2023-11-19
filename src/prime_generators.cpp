#include "prime_generators.h"
#include "is_prime.h"
#include <memory>
#include <vector>

using namespace std;

unique_ptr<vector<int>> gen::naive(int n) {
  vector<int> primes;

  for (int i = 2; i <= n; ++i) {
    if (isPrime::naive(i))
      primes.push_back(i);
  }

  return make_unique<vector<int>>(primes);
}

unique_ptr<vector<int>> gen::smart(int n) {
  vector<int> primes;
  primes.reserve((n / 3) << 1);

  primes.push_back(2);
  primes.push_back(3);

  for (int i = 5; i <= n; i += 6) {
    if (isPrime::smart(i))
      primes.push_back(i);

    if (isPrime::smart(i + 2))
      primes.push_back(i + 2);
  }

  return make_unique<vector<int>>(primes);
}

unique_ptr<vector<int>> gen::multi_op(int n) {
  vector<int> primes;
  primes.reserve((n / 3) << 1);

  primes.push_back(2);
  primes.push_back(3);

  for (int i = 5; i <= n; i += 6) {
    if (isPrime::multi_op(i))
      primes.push_back(i);

    if (isPrime::multi_op(i + 2))
      primes.push_back(i + 2);
  }

  return make_unique<vector<int>>(primes);
}
