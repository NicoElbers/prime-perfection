#include <iostream>
#include <ostream>
#include <vector>

class Primes {
public:
  Primes();
  void genPrimes(int);
  bool contains(int);
  std::vector<int> primeCache;
  int cacheSize;
  int highesValueChecked = 3;

private:
  bool isPrime(int);
};

Primes::Primes() {
  // highesValueChecked = 3;
  primeCache.push_back(2);
  primeCache.push_back(3);
}

bool Primes::contains(int n) {
  for (int i = primeCache.size() - 1; i >= 0; --i) {
    if (n == primeCache[i])
      return true;
  }
  return false;
}

bool Primes::isPrime(int n) {
  // fsr this speeds up the code
  if (n <= highesValueChecked) {
    return contains(n);
  }
  // TODO see if I can do this functionally

  // TODO try this configuration with simd

  // int i = 0;
  // int prime1, prime2, prime3, prime4, prime5;
  // prime1 = 2;
  // prime2 = 3;
  // prime3 = 5;
  // prime4 = 7;
  // prime5 = 11;
  //
  // bool notPrime;
  // bool completed = false;
  // while (!completed) {
  //   notPrime = n % prime1 == 0 || n % prime2 == 0 || n % prime3 == 0 ||
  //              n % prime4 == 0 || n % prime5 == 0;
  //   completed = notPrime || prime5 * prime5 > n;
  //
  //   i += 5;
  //   prime1 = primeCache[i];
  //   prime2 = primeCache[i + 1];
  //   prime3 = primeCache[i + 2];
  //   prime4 = primeCache[i + 3];
  //   prime5 = primeCache[i + 4];
  //
  //   // make sure that the next prime is not less than the previous
  //   prime2 = std::max(prime1, prime2);
  //   prime3 = std::max(prime2, prime3);
  //   prime4 = std::max(prime3, prime4);
  //   prime5 = std::max(prime4, prime5);
  // }
  //
  // highestValueChecked = n;
  // return !notPrime;

  // Working implementation
  int i = 0;
  int currentPrime = primeCache[i];
  bool notPrime;
  bool completed = false;
  while (!completed) {
    notPrime = n % currentPrime == 0;
    completed = notPrime || (currentPrime * currentPrime > n);

    i++;
    currentPrime = primeCache[i];
  }

  highesValueChecked = n;
  return !notPrime;
}

void Primes::genPrimes(int n) {
  int upperPrimeLimit = (int)(n / 3);
  upperPrimeLimit = upperPrimeLimit << 1;
  primeCache.reserve(upperPrimeLimit);

  for (int i = 7; i <= n; i += 6) {
    if (isPrime(i - 2)) {
      primeCache.push_back(i - 2);
    }
    if (isPrime(i)) {
      primeCache.push_back(i);
    }
  }

  cacheSize = primeCache.size();
}

int main(int argc, char *argv[]) {
  Primes p;

  p.genPrimes(10000000);

  std::cout << p.cacheSize << std::endl;

  return 0;
}
