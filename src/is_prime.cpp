#include "is_prime.h"
#include <iostream>

bool isPrime::naive(int n) {
  if (n <= 1)
    return false;

  for (int i = 2; i < n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}

bool isPrime::smart(int n) {
  int num = 5;
  int lim = n;

  // Check whether n is divisible by 2 or 3
  // or if it is 2 or 3
  bool could_be_prime = (n % 2 != 0 && n % 3 != 0) || n == 2 || n == 3;
  bool completed = !could_be_prime || 25 > lim; // 25 = num * num

  while (!completed) {
    // Check whether n is divisible by num or num + 2
    could_be_prime = n % num != 0 && n % (num + 2) != 0;

    // Check whether n was not yet divisible by any
    // number and the last checked number was less than
    // sqrt(lim)
    completed = !could_be_prime || ((num + 2) * (num + 2)) > lim;

    // numbers divisible by 2 and 3 are ignored in this way
    num += 6;
  }

  // could_be_prime at this point indicates whether the number is
  // prime or not
  return could_be_prime;
}
