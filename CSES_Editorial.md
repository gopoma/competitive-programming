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

## Graph Algorithms

### Counting Rooms

Count the `Connected Components`, implementation could be using `BFS` or `DFS` on `grid`.

### Labyrinth

Since we need the `shortest` path and we don't have a `weighted graph`, we could assume that all edges have the same cost, for `that` case, with `BFS`, we could start filling a `dists` array and updating an unvisited cell with one plus the value of dist of the previously visited cell. Finally, to recover the `shortest` path, start from the end and keep going one minus the current distance value.

### Building Roads

Note that we have an `undirected graph`, so it is feasible to check the `connected components`, let this amount as $x$.

* `minimum number of roads required` $= x - 1$

* `Which roads should be built?` Note that we just need one road to connect two components.

### Message Route

It's similar to `Labyrinth`, but we don't have a grid this time.

### Building Teams

`Bipartiteness check`. For each component, assign an arbitrary a 1 to any node and spread the oposite to the neighbors, if we have already visited a neighbor, check that the values are distinct, if not, it is `IMPOSSIBLE`.

### Round Trip

`DFS tree`. To check where an undirected graph has a `Cycle`, we must look for a `Back Edge`. For implementation, it is useful to have the `color` array. Finally, to recover the nodes that compound the cycle, we could use a `stack` and carefully remove nodes until one is repeated.

### Shortest Routes I

`Dijkstra on sparse graphs`

Note that you could have `multiple equal edges` with different costs.

The time complexity should be $O(n \log(n) + m)$.

**References:**

* `https://cp-algorithms.com/graph/dijkstra_sparse.html`

### Shortest Routes II

`Floyd-Warshall Algorithm`

Note that you couldn't have multiple equal edges, but use `ckmin` instead.

The time complexity should be $O(n^{3})$.

**References:**

* `https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html`

## Mathematics

### Exponentiation

`Modular Binary Exponentiation`.

### Exponentiation II

`Fermat's little theorem` and `Modular Binary Exponentiation`.

Another method for finding modular inverse is to use `Euler's theorem`, which states that the following congruence is true if $a$ and $m$ are **coprime**:

$$a^{\phi(m)} \equiv 1 \mod m$$

If $m$ is a prime number, this simplifies to `Fermat's little theorem`:

$$a^{m-1} \equiv 1 \mod m$$

**References:**

* `https://cp-algorithms.com/algebra/module-inverse.html`

### Counting Divisors

`Pollard’s Rho Algorithm for Prime Factorization` and explicit formula (refer to page 208 of Competitive Programming Handbook) for **number of divisors**:

$$\tau(n) = \prod_{i = 1}^{k} (a_{i} + 1)$$

### Common Divisors

Store frequencies of each array elements and then sweep over the **possible** greatest divisor $d$, we know that it is possible if the count of numbers that $d$ sweeps is **greater than** $1$.

The time complexity is $O(\max(x_{i}) \log(\max(x_{i})))$ (like `Sieve of Eratosthenes`) if frequence access is $O(1)$ with `Hashing` or a vector.

### Sum of Divisors

**Start from** the **divisors** instead of the numbers.

So now, to get our answer all we have to do is calculate the below expression:
$$\sum_{d=1}^{n} d\left\lfloor \frac{n}{d}\right\rfloor$$

However, if you list out the values of $\left\lfloor \frac{n}{d}\right\rfloor$ (henceforth referred to as $q$)
for large enough values of $n$, notice that the values start to form long "chains" of the same
value. For example, here's the list of values for $n=20$:
$$[20, 10, 6, 5, 4, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]$$
Taking this pattern further, it's possible to show that there's at most
$2\sqrt{n}$ distinct values of $q$
(proof `https://math.stackexchange.com/questions/1069460/how-many-distinct-values-of-floorn-i-exists-for-i-1-to-n`).

Knowing this, we can quickly process all terms in the summation with the same value of
$q$.
We start with $d=1$ and `jump` to the next value that yields a different value of $q$ instead of naively increasing it by
$1$.

**References:**

* `https://usaco.guide/problems/cses-1082-sum-of-divisors/solution`

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

**References:**
* `https://usaco.guide/problems/cses-2182-divisor-analysis/solution`

### Prime Multiples

#### The Inclusion-Exclusion Principle

The `inclusion-exclusion principle` is an important combinatorial way to compute the size of a set or the probability of complex events. It relates the sizes of individual sets with their union.

##### The formulation in terms of sets

The above definition can be expressed mathematically as follows:

$$\left\lvert \bigcup_{i = 1}^{n} A_{i} \right\rvert = \sum_{i = 1}^{n} \left\lvert A_{i} \right\rvert - \sum_{1 \le i < j \le n}^{} \left\lvert A_{i} \cap A_{j} \right\rvert + \sum_{1 \le i < j < k \le n}^{} \left\lvert A_{i} \cap A_{j} \cap A_{k} \right\rvert - ... + (-1)^{n - 1} \left\lvert A_{1} \cap ... \cap A_{n}\right\rvert$$

**Tip:** Traverse **subsets** and check **bit count parity**, be careful with **overflows**.

### Counting Coprime Pairs

Let's define the `Möbius function` $\mu(x)$ for the integer $X$ as:

* $\mu(X)$ is $0$ if $X$ is not a square-free integer.
* $\mu(X)$ is $1$ if $X$ is a square-free integer and the number of $X$'s prime divisors is **even**.
* $\mu(X)$ is $-1$ if $X$ is a square-free integer and the number of X’s prime divisors is **odd**.

Then, let's define the function $D(X)$ for the integer X as:

* $D(X)$ is the number of integers in the given sequence that are divisible by $X$.

**Answer:**

$$\sum_{X = 1}^{\max(x_{i})} \mu(x) \binom{D(X)}{2} = \sum_{X = 1}^{\max(x_{i})} \mu(x) \frac{D(X)(D(X) - 1)}{2}$$

**Notes:**

* Note that if $X$ is greater than the maximal number that occurs in the sequence, then the correspondent term in the sum will be equal to **zero**, so you can safely consider only the first $10^{6}$ terms because this is the **upper bound** on the sequence's numbers.

* This could be `extended` to `triplets`.

* The definition of `Möbius function` $\mu(x)$ matches `https://codeforces.com/group/OyefIGO3t4/contest/447287/problem/H`, should reuse.

**References:**
* `https://discuss.codechef.com/t/coprime3-editorial/6051`

### Binomial Coefficients

`ModFact` benchmarking.

### Creating Strings II

Store frequency of each letter and note that order **matters**.

#### Permutations with Repetition

The number of permutations of $n$ objects with $n_{1}$ identical objects of type $1$, $n_{2}$ identical objects of type $2$, $...$, and $n_{k}$ identical objects of type $k$ is

$$\frac{n!}{n_{1}! n_{2}! ... n_{k}!}$$

In the case all objects are distinct, we have $n_{1} = n_{2} = ... = n_{d} = 1$, and the above theorem shows that the number of permutations is

$$\frac{n!}{n_{1}! n_{2}! ... n_{d}!} = \frac{n!}{1! 1! ... 1!} = n!$$

which we have seen in **Permutations without Repetition**. Note that we have **assumed** that the permutation contains **all** of the objects in the ordering. In the case that we would only like to include **some** of the objects in the ordering, see **Permutations with Restriction**.

**References:**

* `https://brilliant.org/wiki/permutations-with-repetition/`

## String Algorithms

### Minimal Rotation

`Minimum Cyclic Shift`

The time complexity should be $O(N)$.

**References:**

* `https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/strings%20(14)/Light/MinRotation.h`
