#include "prime_generators.h"
#include "is_prime.h"
#include <iostream>
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

unique_ptr<vector<int>> gen::multi_thread(int n, int threads) {
  int bucketSize = n / threads;

  int leftover = n % threads;

  int bucketSizes[threads];

  for (int bucket : bucketSizes) {
    bucket = bucketSize;
  }

  for (int i = leftover; i > 0; --i) {
    bucketSizes[i]++;
  }

  int startNums[threads];
  int num = 0;
  for (int i = 0; i < threads; ++i) {

    startNums[i] = num - ((num - 5) % 6);
    num += bucketSizes[i];

    cout << "Num is now " << num << endl;

    int goodNum = num - ((num - 5) % 6);
    cout << "Counts from " << goodNum << " to " << goodNum + bucketSizes[i]
         << endl;
  }

  return make_unique<vector<int>>(vector<int>());
}
