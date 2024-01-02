# CSES Problem Set

## Introductory Problems

* __Digit Queries:__ `Binary Search` on rightmost number that could contain the kth digit.

## Sorting and Searching

* __Josephus Problem I:__ Simulation with `<ext/rope>`.

* __Factory Machines:__ `Binary Search` on answer, be careful with **overflows**.

```C++
// kills the program on integer overﬂows (but is really slow).
#pragma GCC optimize ("trapv")
```

* __Sum of Three Values:__ `Hashing` or `Two Pointers Technique`, for Hashing, combine the **type definitions** of the cp-book and **chash** from cp-notebook/kactl, for Two Pointers Technique, follow the steps that the Competitive Programming Handbook describes in Amortized analysis chapter for 2SUM problem (page 88).
    * `https://github.dev/ecnerwala/cp-book`
    * `https://github.dev/bqi343/cp-notebook`
    * `https://github.dev/kth-competitive-programming/kactl`

## Mathematics

### Exponentiation

`Modular Binary Exponentiation`.

### Exponentiation II

`Fermat's little theorem` and `Modular Binary Exponentiation`.

Another method for finding modular inverse is to use `Euler's theorem`, which states that the following congruence is true if $a$ and $m$ are **coprime**:

$$a^{\phi(m)} \equiv 1 \mod m$$

If $m$ is a prime number, this simplifies to `Fermat's little theorem`:

$$a^{m-1} \equiv 1 \mod m$$

### Counting Divisors

`Pollard’s Rho Algorithm for Prime Factorization` and explicit formula (refer to page 208 of Competitive Programming Handbook) for **number of divisors**:

$$\tau(n) = \prod_{i = 1}^{k} (a_{i} + 1)$$

### Common Divisors

Store frequencies of each array elements and then sweep over the **possible** greatest divisor $d$, we know that it is possible if the count of numbers that $d$ sweeps is **greater than** $1$.

The time complexity is $O(\max(x_{i}) \log(\max(x_{i})))$ (like `Sieve of Eratosthenes`) if frequence access is $O(1)$ with `Hashing` or a vector.

### Divisor Analysis

Let $w = x_{1}^{k_{1}} x_{2}^{k_{2}} ... x_{n}^{k_{n}}$

The **number** of divisors of a number $n$ is

$$\tau(w) = \prod_{i = 1}^{n} (k_{i} + 1)$$

The **sum** of divisors of $n$ is

$$\sigma(w) = \prod_{i = 1}^{n} \frac{x_{i}^{k_{i} + 1} - 1}{x_{i} - 1}$$

The **product** of factors of n is

* $\mu(w) = w^{\lfloor \frac{\tau(w)}{2} \rfloor} \sqrt w$ if $w$ is a **Perfect Square**.
* $\mu(w) = w^{\frac{\tau(w)}{2}}$ otherwise.

That evaluation **could** be **hard**, since `Fermat's little theorem` should be used in the exponent, take advantage of you can skip the `Modular Multiplicative Inverse` restriction ($2$ and $10^{9}+6$ should be coprime), don't know **why**.

**Alternative Approach for product:** Let the product and number of divisors when only considering the first $i$ prime factors be
$P_{i}$ and $C_{i}$ respectively. The answer will be $P_{N}$.

$$P_{i} = P_{i-1}^{k_{i} + 1} (x_{i}^{k_{i} (k_{i} + 1)/2})^{C_{i - 1}}$$

**Note:** $C_{i}$ **should** be calculated over modulo $10^{9} + 6$ as a consequence of the `Fermat's little theorem`.

### Binomial Coefficients

`ModFact` benchmarking.
