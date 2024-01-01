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

* __Sum of Three Values:__ `Hashing` or `Two Pointers Technique`, for Hashing, combine the type definitions of the cp-book and chash from kactl, for Two Pointers Technique, follow the steps that the Competitive Programming Handbook describes in Amortized analysis chapter for 2SUM problem (page 88).
    * `https://github.dev/ecnerwala/cp-book`
    * `https://github.dev/kth-competitive-programming/kactl`

## Mathematics

* __Exponentiation:__ `Modular Binary Exponentiation`.
* __Counting Divisors:__ `Pollard’s Rho Algorithm for Prime Factorization` and explicit formula (refer to page 198 of Competitive Programming Handbook).
