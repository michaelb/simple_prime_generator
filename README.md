a simple take on generating primes in a efficient (or not) way. It also illustrates time vs space(memory) complexity.

prime.c is a simple, slow, but robust implementation that should be able to go up to 2^64-1 (while not in a reasonable time)

prime_sundaram3.c is a very, very fast sieve but it needs O(n) memory (to calculate primes up to n-1). While memory compression could be achieved, this would be at the expense of performance.

## How to run:

- compile with your favorite (or not) compiler : `gcc prime.c`
- run the executable: `./a.out`

## How to use within your project (don't)

I'd suggest writing your own, but in case you don't want to, the code in the prime\_\*.c files should be clear enough to reuse: there is a section within the loops where the primes values are exposed.

Though, whether the program can output in real time the primes you need or if it needs time to calculate then output all at once depends on the implementation but also the method and may not be modifiable.

## Speed results

(on i5 4210u@1.7GHz, 8Go DDR3)

- prime.c: counted primes up to 1e6 in 40s
- prime_sundaram3.c: counted primes up to 1e9 in 1m02s, though it had to use a whopping 4Go of RAM to do so.

Both program are single threaded, and pale in comparison to state-of-the-art prime generators such as [primesieve](https://github.com/kimwalisch/primesieve) which achieve counting primes up to 1e9 in 0.180s, and use way less memory
