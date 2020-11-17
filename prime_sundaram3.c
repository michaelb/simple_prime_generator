#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//a really fast implementation of the sundaram method, but needs O(n) memory
int main()
{
  uint64_t max = 1000 * 1000 * 1000; // (exclusive) max value to calculate primes up to
  uint64_t half = max / 2;
  uint64_t initial = 4;

  uint64_t* sieve = calloc(max, sizeof(int));

  for (uint64_t step = 3; step < max + 1; step += 2) {
    for (uint64_t j = initial; j < half; j += step) {
      sieve[j - 1] = 1;
    }
    initial += 2 * (step + 1);
    if (initial > half) {
      break;
    }
  }

  int is_not_prime = 0;
  uint64_t value = 0;
  uint64_t count = 1;

  // sieve contains the position, (off by 3) of primes above 3
  for (uint64_t i = 0; i < half - 1; i++) {
    is_not_prime = sieve[i];
    if (!is_not_prime) {
      value = i * 2 + 3;
      /* printf("%lu, ", value); */ //don't  forget 2, this array of primes starts at 3!
      count++;
    }
  }
  printf("\n%lu primes counted up to %lu\n", count, max);
  free(sieve);
}
