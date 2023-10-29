#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>
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

  if (argc < 2)
    exit(-22);

  int inputLimit = atoi(argv[1]);

  TestPrimes app(inputLimit);

  // app.testSIMDPrimes();
  app.calcSIMDPrimes();

  return 0;
}
