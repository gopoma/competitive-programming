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

* It is my impression that Pull dp is best for counting.

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

* in 0-1 dp, want to ignore the case where we don't pick anything, just put a carry and switch states
