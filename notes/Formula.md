# Geometry

## Polygon Area

The (signed) area of a planar non-self-intersecting polygon with vertices $(x_{1}, y_{1}),...,(x_{n}, y_{n})$ is

$$A = \frac{1}{2} \sum_{i = 1}^{n} (x_{i}y_{i + 1} - x_{i + 1}y_{i})$$

Note that the area of a **convex polygon** is defined to be **positive** if the points are arranged in a **counterclockwise** order and **negative** if they are in **clockwise** order.

**Reference:** https://mathworld.wolfram.com/PolygonArea.html

## Polygon Centroid

The positions of the geometric centroid of a planar non-self-intersecting polygon with vertices $(x_{1}, y_{1}),...,(x_{n}, y_{n})$ are

$$\overline{x} = \frac{1}{6A} \sum_{i = 1}^{n} (x_{i} + x_{i + 1})(x_{i}y_{i + 1} - x_{i + 1}y_{i})$$

$$\overline{y} = \frac{1}{6A} \sum_{i = 1}^{n} (y_{i} + y_{i + 1})(x_{i}y_{i + 1} - x_{i + 1}y_{i})$$

where $A$ is the polygon area and $x_{n + 1}=x_{1}$ and $y_{n + 1} = y_{1}$.

**Reference:** https://mathworld.wolfram.com/PolygonCentroid.html
