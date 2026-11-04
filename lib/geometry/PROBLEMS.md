# Geometría — problemas

Dónde practicar cada header. Los manuales de cada directorio documentan **solo los métodos**; esto es lo que está aparte.

Lista curada a partir de [USACO Guide](https://usaco.guide/plat/geo-pri) (sus archivos `*.problems.json`). Las dificultades son las de ellos.

- [Primitives](#primitives)
- [Polygons](#polygons)
- [Circles](#circles)
- [Misc](#misc)

## Primitives

| header | problema ancla | dificultad |
|---|---|---|
| `Point.h` | [CSES — Point Location Test](https://cses.fi/problemset/task/2189) | Easy |
| `AngleCmp.h` | [Library Checker — Sort Points by Argument](https://judge.yosupo.jp/problem/sort_points_by_argument) | Easy |
| `SegDist.h` | [Kattis — Segment Distance](https://open.kattis.com/problems/segmentdistance) | Easy |
| `SegIsect.h` | [CSES — Line Segment Intersection](https://cses.fi/problemset/task/2190) | Medium |

Más práctica:

| fuente | problema | dificultad | con qué |
|---|---|---|---|
| Kattis | [Segment Intersection](https://open.kattis.com/problems/segmentintersection) | Easy | `segIsect` con punto de corte |
| LeetCode | [Maximum Number of Visible Points](https://leetcode.com/problems/maximum-number-of-visible-points/description/) | Medium | `angleCmp` + ventana deslizante |
| CF | [Cut Length](https://codeforces.com/contest/598/problem/F) | Hard | `lineIsect` sobre cada arista |

## Polygons

| header | problema ancla | dificultad |
|---|---|---|
| `ConvexHull.h` | [Kattis — Convex Hull](https://open.kattis.com/problems/convexhull) | Easy |
| `PolygonCenArea.h` | [CSES — Polygon Area](https://cses.fi/problemset/task/2191) | Medium |
| `InPolygon.h` | [CSES — Point in Polygon](https://cses.fi/problemset/task/2192) | Medium |
| `HullDiameter.h` | [Kattis — Robert Hood](https://open.kattis.com/problems/roberthood) | Easy |
| `MinkowskiSum.h` | [CF — Geometers Anonymous Club](https://codeforces.com/problemset/problem/1195/F) | Medium |
| `HalfPlaneIsect.h` | [Kattis — Big Brother](https://open.kattis.com/problems/bigbrother) | Hard |

`HullTangents.h` y `LineHull.h` no tienen un problema canónico: aparecen como pieza dentro de otros.

Más práctica:

| fuente | problema | dificultad | con qué |
|---|---|---|---|
| Kattis | [Polygon Area](https://open.kattis.com/problems/polygonarea) | Easy | `cenArea` |
| Kattis | [Point in Polygon](https://open.kattis.com/problems/pointinpolygon) | Easy | `inPoly` |
| CF | [Water Balance](https://codeforces.com/problemset/problem/1299/C) | Easy | hull de la suma prefija |
| CSES | [Polygon Lattice Points](https://cses.fi/problemset/task/2193) | Medium | área + teorema de Pick |
| USACO Plat | [Balance Beam](http://www.usaco.org/index.php?page=viewproblem2&cpid=864) | Medium | hull inferior |
| USACO Old Gold | [Cow Curling](http://www.usaco.org/index.php?page=viewproblem2&cpid=382) | Medium | punto en convexo |
| Kattis | [Fence Orthogonality](https://open.kattis.com/problems/fenceortho) | Hard | hull + calipers |
| Balkan OI 2011 | [Timeismoney](http://oj.uz/problem/view/balkan11_timeismoney) | Hard | hull sobre el espacio de soluciones |

## Circles

**USACO Guide no tiene módulo de círculos** — su sección de geometría son primitivas, convex hull, sweep line y CHT. Por eso esta lista es corta: los círculos casi no aparecen como tema propio.

| fuente | problema | dificultad | con qué |
|---|---|---|---|
| LeetCode | [Maximum Darts Inside a Circular Dartboard](https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/description/) | Hard | círculo fijado por 2 o 3 puntos |
| Kattis | [Birthday Cake](https://open.kattis.com/problems/birthdaycake) | Hard | recta que parte un círculo |

> Si estás preparando CF o AtCoder, los círculos rinden menos que polígonos por hora invertida. `mec` e `isect` son los dos que vale la pena tener a mano.

## Misc

| header | problema ancla | dificultad |
|---|---|---|
| `ClosestPair.h` | [Kattis — Closest Pair](https://open.kattis.com/problems/closestpair2) | Medium |
| `ManhattanMST.h` | [Kattis — Grid MST](https://open.kattis.com/problems/gridmst) | Medium |
| `MaxCollinear.h` | [Kattis — Max Collinear](https://open.kattis.com/problems/maxcolinear) | Hard |

Más práctica:

| fuente | problema | dificultad | con qué |
|---|---|---|---|
| LeetCode | [Max Points on a Line](https://leetcode.com/problems/max-points-on-a-line/description/) | Easy | `MaxCollinear.h`, versión chica |
| AtCoder | [Manhattan Multifocal Ellipse](https://atcoder.jp/contests/abc366/tasks/abc366_e) | Hard | $L_1$, sin MST |
| CS Academy | [The Sprawl](https://csacademy.com/contest/archive/task/the-sprawl) | Hard | MST Manhattan |
