#include "prime_generators.h"
#include "is_prime.h"
#include "multi_primes.h"
#include <future>
#include <list>
#include <thread>
#include <vector>

using namespace std;

vector<int> gen::naive(int n) {
  vector<int> primes;

  for (int i = 2; i <= n; ++i) {
    if (isPrime::naive(i))
      primes.push_back(i);
  }

  return primes;
}

vector<int> gen::smart(int n) {
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

  return primes;
}

vector<int> gen::multi_op(int n) {
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

  return primes;
}

struct thread_info {
  int startNum;
  int endNum;
};

vector<int> gen::multi_thread(int n) {
  int threads = std::thread::hardware_concurrency();

  int bucketSize = n / threads;

  int leftover = n % threads;

  int bucketSizes[threads];

  for (int i = 0; i < threads; ++i) {
    bucketSizes[i] = bucketSize;
  }

  for (int i = leftover; i > 0; --i) {
    bucketSizes[i]++;
  }

  thread_info init_values[threads];
  int num = 0;
  for (int i = 0; i < threads; ++i) {
    int startNum = num - ((num - 5) % 6);
    int combinedNum = startNum + bucketSizes[i];
    int endNum = combinedNum - ((combinedNum - 5) % 6);

    if (endNum > n)
      endNum = n;

    init_values[i] = {startNum, endNum};
    num = endNum + 6;
  }

  std::list<std::vector<int>> primeList;

  std::vector<int> low_primes;
  low_primes.push_back(2);
  low_primes.push_back(3);

  primeList.push_back(low_primes);

  std::vector<std::future<std::vector<int>>> handles;

  {
    for (thread_info info : init_values) {
      handles.push_back(std::async(std::launch::async, prime_thread,
                                   info.startNum, info.endNum));
    }
  }

  for (auto &handle : handles) {
    handle.wait();
    primeList.push_back(handle.get());
  }

  std::vector<int> out;
  out.reserve((n << 1) / 3);

  for (std::vector<int> primes : primeList)
    for (int prime : primes)
      out.push_back(prime);

  return out;
}
