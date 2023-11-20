#include "multi_primes.h"
#include "prime_generators.h"
#include <algorithm>
#include <bits/chrono.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

class Primes {
protected:
  Primes();
  int cacheSize;
  int highesValueChecked = 1;

  // normal method
  void genPrimes(int);
  std::vector<int> primeCache;

  // SIMD implementation
  void genPrimesSIMD(int);

  // booleans
  std::vector<bool> primeCacheBool;
  void genPrimesBool(int);

  // multithread 'simd' implementation
  void genPrimesMulti(int);

private:
  // normal method
  bool isPrime(int);

  // possible simd implementation
  bool isPrimeSIMD(int);
};

Primes::Primes() {
  // highesValueChecked = 3;
  primeCache.push_back(2);
  primeCache.push_back(3);
}

bool Primes::isPrimeSIMD(int n) {
  int num;
  num = 5;

  int lim = n;
  bool isPrime = (n % 2 != 0 && n % 3 != 0);
  bool completed = !isPrime || 25 > lim;
  while (!completed) {
    isPrime = n % num != 0 && n % (num + 2) != 0 && n % (num + 6) != 0 &&
              n % (num + 8) != 0 && n % (num + 12) != 0 &&
              n % (num + 14) != 0 && n % (num + 18) != 0 && n % (num + 20) != 0;

    completed = !isPrime || (num + 20) * (num + 20) > lim;

    num += 24;
  }

  highesValueChecked = n;
  return isPrime;
}

bool Primes::isPrime(int n) {
  int num = 5;
  int lim = n;
  bool isPrime = (n % 2 != 0 && n % 3 != 0);
  bool completed = !isPrime || 25 > lim; // 25 = num * num
  while (!completed) {
    isPrime = n % (num + 2) != 0 && n % num != 0;
    completed = !isPrime || ((num + 2) * (num + 2) > lim);

    num += 6;
  }

  highesValueChecked = n;
  return isPrime;
}

void Primes::genPrimes(int n) {
  int upperPrimeLimit = (int)(n / 3);
  upperPrimeLimit = upperPrimeLimit << 1;
  primeCache.reserve(upperPrimeLimit);

  for (int i = 5; i <= n; i += 6) {
    if (isPrime(i)) {
      primeCache.push_back(i);
    }

    if (isPrime(i + 2)) {
      primeCache.push_back(i + 2);
    }
  }

  cacheSize = primeCache.size();
}

void Primes::genPrimesSIMD(int n) {
  int upperPrimeLimit = (int)(n / 3);
  upperPrimeLimit = upperPrimeLimit << 1;
  primeCache.reserve(upperPrimeLimit);

  for (int i = 5; i <= n; i += 6) {
    if (isPrimeSIMD(i)) {
      primeCache.push_back(i);
    }

    if (isPrimeSIMD(i + 2)) {
      primeCache.push_back(i + 2);
    }
  }

  cacheSize = primeCache.size();
}

// This exists if I ever run into space problems
// until then, it's not faster and it just makes
// it so I know less about my data
void Primes::genPrimesBool(int n) {
  int cacheSize = (int)(n / 3);
  cacheSize = cacheSize << 1;
  primeCacheBool.reserve(cacheSize);

  int index = 0;
  for (int i = 5; i <= n; i += 6) {
    primeCacheBool.push_back(isPrime(i));
    primeCacheBool.push_back(isPrime(i + 2));

    index += 2;
  }
}

void Primes::genPrimesMulti(int n) {}

/* ----------------- */

class TestPrimes : Primes {
private:
  // universal thingies
  int limit;

public:
  // constructor
  TestPrimes(int limit);

  // current working normal version
  void calcNormalPrimes();
  void testNormalPrimes();

  // version with boolean
  void calcBooleanPrimes();
  void testBooleanPrimes();

  // SIMD version
  void calcSIMDPrimes();
  void testSIMDPrimes();
};

TestPrimes::TestPrimes(int limit) { this->limit = limit; }

void TestPrimes::calcNormalPrimes() { genPrimes(limit); }

void TestPrimes::testNormalPrimes() {
  calcNormalPrimes();

  for (int prime : primeCache) {
    std::cout << prime << std::endl;
  }

  std::cout << std::endl
            << "Found " << primeCache.size() << " in the cache" << std::endl;
}

void TestPrimes::calcBooleanPrimes() { genPrimesBool(limit); }

void TestPrimes::testBooleanPrimes() {
  calcBooleanPrimes();

  int counter = 2;
  int number = 5;
  for (int i = 0; i < primeCacheBool.size(); i += 2) {
    if (primeCacheBool[i]) {
      std::cout << number << std::endl;
      counter++;
    }

    if (primeCacheBool[i + 1]) {
      std::cout << number + 2 << std::endl;
      counter++;
    }

    number += 6;
  }

  std::cout << "Found " << counter << " primes in the cache" << std::endl;
}

void TestPrimes::calcSIMDPrimes() { genPrimesSIMD(limit); }

void TestPrimes::testSIMDPrimes() {
  calcSIMDPrimes();

  for (int prime : primeCache) {
    std::cout << prime << std::endl;
  }

  std::cout << std::endl
            << "Found " << primeCache.size() << " in the cache" << std::endl;
}

int main(int argc, char *argv[]) {
  // std::cout << "started main" << std::endl;
  //
  // std::vector<int> cache;
  //
  // int calc = 1000000;
  // int itr = 10;
  // double avg_time;
  // double tot_time;
  // double max_time;
  // double min_time;
  //
  // std::cout << "Calculating unil " << calc << " with " << itr << "
  // iterations"
  //           << std::endl;
  // std::cout << std::endl;
  //
  // // min_time = MAXFLOAT;
  // // max_time = -1;
  // // tot_time = 0;
  // // for (int i = 0; i < itr; i++) {
  // //   auto start = std::chrono::high_resolution_clock::now();
  // //   cache = *gen::naive(calc);
  // //   auto end = std::chrono::high_resolution_clock::now();
  // //
  // //   std::chrono::duration<double> dur = end - start;
  // //
  // //   tot_time += dur.count();
  // //
  // //   max_time = std::max(max_time, dur.count());
  // //   min_time = std::min(min_time, dur.count());
  // // }
  //
  // // avg_time = tot_time / itr;
  // //
  // // std::cout << "Generated naive primes with length " << cache.size()
  // //           << std::endl;
  // // std::cout << "This took " << tot_time << " seconds in total" <<
  // std::endl;
  // // std::cout << "This took " << avg_time << " seconds on average" <<
  // // std::endl; std::cout << "Minimum time " << min_time << " seconds" <<
  // // std::endl; std::cout << "Maximum time " << max_time << " seconds" <<
  // // std::endl; std::cout << "Max diff " << max_time - min_time << " seconds"
  // <<
  // // std::endl; std::cout << std::endl;
  //
  // min_time = MAXFLOAT;
  // max_time = -1;
  // tot_time = 0;
  // for (int i = 0; i < itr; i++) {
  //   auto start = std::chrono::high_resolution_clock::now();
  //   cache = *gen::smart(calc);
  //   auto end = std::chrono::high_resolution_clock::now();
  //
  //   std::chrono::duration<double> dur = end - start;
  //
  //   tot_time += dur.count();
  //
  //   max_time = std::max(max_time, dur.count());
  //   min_time = std::min(min_time, dur.count());
  // }
  //
  // avg_time = tot_time / itr;
  //
  // std::cout << "Generated smart primes with length " << cache.size()
  //           << std::endl;
  // std::cout << "This took " << tot_time << " seconds in total" << std::endl;
  // std::cout << "This took " << avg_time << " seconds on average" <<
  // std::endl; std::cout << "Minimum time " << min_time << " seconds" <<
  // std::endl; std::cout << "Maximum time " << max_time << " seconds" <<
  // std::endl; std::cout << "Max diff " << max_time - min_time << " seconds" <<
  // std::endl; std::cout << std::endl;
  //
  // min_time = MAXFLOAT;
  // max_time = -1;
  // tot_time = 0;
  // for (int i = 0; i < itr; i++) {
  //   auto start = std::chrono::high_resolution_clock::now();
  //   cache = *gen::multi_op(calc);
  //   auto end = std::chrono::high_resolution_clock::now();
  //
  //   std::chrono::duration<double> dur = end - start;
  //
  //   tot_time += dur.count();
  //
  //   max_time = std::max(max_time, dur.count());
  //   min_time = std::min(min_time, dur.count());
  // }
  //
  // avg_time = tot_time / itr;
  //
  // std::cout << "Generated multi_op primes with length " << cache.size()
  //           << std::endl;
  // std::cout << "This took " << tot_time << " seconds in total" << std::endl;
  // std::cout << "This took " << avg_time << " seconds on average" <<
  // std::endl; std::cout << "Minimum time " << min_time << " seconds" <<
  // std::endl; std::cout << "Maximum time " << max_time << " seconds" <<
  // std::endl; std::cout << "Max diff " << max_time - min_time << " seconds" <<
  // std::endl; std::cout << std::endl;

  gen::multi_thread(1000000, 16);

  std::cout << std::endl;
  return 0;
}
