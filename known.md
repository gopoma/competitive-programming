# To Take into Consideration

* Some statements gets simplified if you `fix` something.

* Try to write a simplified formula if you can, to avoid using something that you don't know.

* `Try` to simulate `all` the test cases in paper.

* `Don't overthink`, maybe it is not as complicated as you think!

* Try `Proof by AC`.

* No divagues >:v.

```C++
// Rotate vector left 3 times.
int rotL = 3;

// rotate function
rotate(vec1.begin(), vec1.begin() + rotL, vec1.end());

// go

// Rotate vector right 4 times.
int rotR = 4;

// rotate function
rotate(vec2.begin(), vec2.begin() + vec2.size() - rotR, vec2.end());
```

* `Complexity in Recursive dp`: Complejidad que acarrea la tabla en sí por la Complejidad de un cálculo simple de estado.

* It is my impression that `Top-Down` dp is best for counting.

* Think in `invariants`.

* `Always analyze constraints`.

* Check if some part of the Complexity can be reduced to $n \log(n)$ by doing.

```C++
for (i = 1; i <= n; i++)
   for (int j = i; j <= n; j += i)
```

* If you've got WA, `debug, don't blame the lib` >:v!

* Think hard in paper, also implement sth

* `Try to code the brute force approach and use it as a comparator to a greedy that you've built, with the help of an infinite loop`.

* Iterate small ranges.

* Check memory consumption.

* Remember that `multiset` exists.

* Always use `long long` to avoid overflow.

* in 0-1 dp, want to ignore the case where we don't pick anything, just put a carry and switch states.

* watch `carefully` the `constraints`, maybe it can be divided in two cases.

* Exploit numeric constrains, ask yourself: ¿What is the maximum amount of **different values**?

* `Try to implement the brute`, then make observations of what can be optimized.

* In case you think that are **INF** possibilities, remember the `visited` array.

* **Think hard** in paper. Try to optimize the naive with Greedy.

* **Forgot** a `break` that `should` end current loop and outer loop (`rage quit`)?

* **Read** `Carefully` the `Constraints` >:v

* **Both** `Lazy Segment Tree` templates require that size must be a power of $2$.

* `Simulate your algorithm in paper` >:v

* When working nearly `BIG`, ensure you enable `trapv` if you don't know where is the WA.

* `Sort` the input if possible before processing; it might resolve issues with `dp` or make a `Greedy` approach feasible.

* do `Coordinate Compression` when working with segments and Lazy Segment Tree (**check carefully** the **constraints** in case of `multitest`).

* `sqrt` is not safe for `long long` integers. Try to use `Binary Search` and `bigint` when possible. **Refer to:** https://atcoder.jp/contests/abc361/submissions/55416069

* $N=2000, M=1000$ and $O(N{M}^{2})$, but:
$dp[idx][current] = \sum_{x = l}^{r} dp[idx + 1][x]$? (note the `contiguous` range (`subarray`)) try to store `prefix sum` in each `dp[i][j]` and now: $dp[idx][current] = dp[idx + 1][r] - dp[idx + 1][l - 1] + dp[idx][current - 1]$ (just be aware of indexing), **Refer to:** https://leetcode.com/submissions/detail/1352504065/

* `always` use `long long` >:v

* `hash_map` doesn't preserve order

* sometimes pragmas don't work, if so, just comment it!

* sometimes `#undef _GLIBCXX_DEBUG` doesn't work, if so, just comment it!

## Intersection

-   **Link:** https://atcoder.jp/contests/abc261/tasks/abc261_a
-   **Description**: This problem asks to find the `length of the common segment` of $[L_{1}, R_{1}]$ and $[L_{2}, R_{2}]$.
-   **Solution**: https://atcoder.jp/contests/abc261/editorial/4493
-   **Solution** $\max(0, \min(R_{1}, R_{2}) - \max(L_{1}, L_{2}))$
