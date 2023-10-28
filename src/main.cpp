#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

class Primes {
public:
  Primes();
  void genPrimes(int);
  bool contains(int);
  std::vector<int> primeCache;
  int cacheSize;
  int highesValueChecked = 1;

  // booleans
  std::vector<bool> primeCacheBool;
  void genPrimesBool(int);

private:
  bool isPrime(int);

  // possible simd implementation
  bool isPrimeSIMD(int);
};

Primes::Primes() {
  // highesValueChecked = 3;
  primeCache.push_back(2);
  primeCache.push_back(3);
}

bool Primes::isPrimeSIMD(int n) { // TODO NOT IMPLEMENTED YET
  // TODO try this configuration with simd

  std::cout << "The SIMD configuration is not yet implemented" << std::endl;
  exit(-1);

  int i = 0;
  int prime1, prime2, prime3, prime4, prime5;
  prime1 = 2;
  prime2 = 3;
  prime3 = 5;
  prime4 = 7;
  prime5 = 11;

  bool notPrime;
  bool completed = false;
  while (!completed) {
    notPrime = n % prime1 == 0 || n % prime2 == 0 || n % prime3 == 0 ||
               n % prime4 == 0 || n % prime5 == 0;
    completed = notPrime || prime5 * prime5 > n;

    i += 5;
    prime1 = primeCache[i];
    prime2 = primeCache[i + 1];
    prime3 = primeCache[i + 2];
    prime4 = primeCache[i + 3];
    prime5 = primeCache[i + 4];

    // make sure that the next prime is not less than the previous
    prime2 = std::max(prime1, prime2);
    prime3 = std::max(prime2, prime3);
    prime4 = std::max(prime3, prime4);
    prime5 = std::max(prime4, prime5);
  }

  highesValueChecked = n;
  return !notPrime;
}

bool Primes::isPrime(int n) {
  // fsr this speeds up the code
  // if (n <= highesValueChecked) {
  //   return contains(n);
  // }

  // TODO see if I can infer the next prime from the current prime (idfk)

  // Don't check cache
  // working version
  int num = 5;
  int lim = n;
  bool isPrime = (n % 2 != 0 && n % 3 != 0);
  bool completed = !isPrime || (num * num) > lim;
  while (!completed) {
    isPrime = n % num != 0 && n % (num + 2) != 0;
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

int main(int argc, char *argv[]) {
  Primes p;

  // version that stores the primes in a boolean vector instead
  // p.genPrimesBool(1000000);

  // std::cout << 2 << std::endl << 3 << std::endl;

  // int counter = 2;
  // int number = 5;
  // for (int i = 0; i < p.primeCacheBool.size(); i += 2) {
  //   if (p.primeCacheBool[i]) {
  //     // std::cout << number << std::endl;
  //     counter++;
  //   }
  //
  //   if (p.primeCacheBool[i + 1]) {
  //     // std::cout << number + 2 << std::endl;
  //     counter++;
  //   }
  //
  //   // number += 6;
  // }
  //
  // std::cout << "Found " << counter << " primes in the cache" << std::endl;

  // current working version
  p.genPrimes(1000000);

  // for (int el : p.primeCache) {
  //   std::cout << el << std::endl;
  // }

  std::cout << p.cacheSize << std::endl;

  return 0;
}
