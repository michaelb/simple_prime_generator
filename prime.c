#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024 * 1024 // max 1M 64bit uints malloc'd
// b careful about the double-evaluation problem
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

struct primeTable {
  uint64_t* Table;
  uint64_t size;
  uint64_t max_size;
};

struct primeTable t = { NULL, 0, MAX_SIZE };

////// utility functions

unsigned char bit_width(unsigned long long x)
{
  return x == 0 ? 1 : 64 - __builtin_clzll(x);
}

uint64_t isqrt(const uint64_t n) //return floor (sqrt(n)) for any integer n
{
  unsigned char shift = bit_width(n);
  shift += shift & 1; // round up to next multiple of 2

  unsigned result = 0;

  do {
    shift -= 2;
    result <<= 1;                             // leftshift the result to make the next guess
    result |= 1;                              // guess that the next bit is 1
    result ^= result * result > (n >> shift); // revert if guess too high
  } while (shift != 0);

  return result;
}

///// calculus of primes here

bool isPrime(uint64_t number)
{
  if (t.size < MAX_SIZE) { // putting value in the table phase

    for (uint64_t i = 0; i < MIN(MAX_SIZE, t.size); i++) {
      if (number % t.Table[i] == 0) {
        return false;
      }
    }
    t.Table[t.size] = number;
    t.size += 1;
    return true;
  } else {
    // no putting more value in table as too much memory used
    // so we have to go slower to go further
    for (uint64_t i = 0; i < MAX_SIZE; i++) {
      if (number % t.Table[i] == 0) {
        return false;
      }
    }
    for (uint64_t i = MAX_SIZE; i < isqrt(number); i++) {
      if (number % t.Table[i] == 0) {
        return false;
      }
    }
    return true;
  }
}

int main()
{
  uint64_t up_to = ~0; //max value ever (hard limit)
  uint64_t* Table = malloc(MAX_SIZE * sizeof(uint64_t));
  t.Table = Table;
  t.Table[0] = 2;
  t.size = 1;

  uint64_t count = 1; //2,3 and 5 are skipped because of the wheel

  // CHOOSE YOUR MAX NUMBER HERE (primes above won't be searched)
  uint64_t cap = 1000 * 1000;
  //value to stop the program at, and not wait decades (soft limit)

  uint64_t limit = MIN(cap, up_to);         // get real limit, always almost cap
  for (uint64_t j = 3; j < limit; j += 2) { //small '2' wheel
    if (isPrime(j)) {
      /* printf("%lu\n", j); */
      //j is the prime you want!
      count++;
    }
  }

  printf("there are %lu primes up to%lu\n", count, cap);
}
