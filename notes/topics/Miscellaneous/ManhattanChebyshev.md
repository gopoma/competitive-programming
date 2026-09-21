# Manhattan <> Chebyshev

Short Description:

For two points $(x_{1}, y_{1})$ and $(x_{2}, y_{2})$, we have the following relations between Manhattan and Chebyshev distance:




## Manhattan -> Chebyshev:

Manhattan Distance = $|x_{1} - x_{2}| + |y_{1} - y_{2}|$

Trick: Rotate $45$ degrees.
Let:
$$p_{1} = x_{1} + y_{1}$$
$$p_{2} = x_{2} + y_{2}$$

$$q_{1} = x_{1} - y_{1}$$
$$q_{2} = x_{2} - y_{2}$$

then Chebyshev Distance = $max(|p_{1} - p_{2}|, |q_{1} - q_{2}|)$




## Chebyshev -> Manhattan:

Chebyshev Distance = $max(|x_{1} - x_{2}|, |y_{1} - y_{2}|)$

Trick: Rotate $45$ degrees. Then Manhattan Distance = $\frac{1}{2} (|p_{1} - p_{2}| + |q_{1} - q_{2}|)$
