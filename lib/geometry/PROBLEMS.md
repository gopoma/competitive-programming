# Geometría — problemas

Dónde se usa cada template. Los manuales documentan los métodos; esto es dónde practicarlos.

Cada template tiene dos listas:

- **Directo** — el template *es* la solución. Sirve para aprender su contrato y sus bordes.
- **Como pieza** — el template es una parte de una idea más grande. Ordenados por dificultad.

**★** = en el rango objetivo: Codeforces 1900–2400, AtCoder 1600–2400.

La dificultad es el rating oficial en Codeforces, la estimación de [AtCoder Problems](https://kenkoooo.com/atcoder/) en AtCoder (≈), y la división en USACO.

## Índice

- [Primitives](#primitives)
  - [`Point.h` — orientación (`cross`)](#pointh--orientación-cross)
  - [`Point.h` — rotación (`P*P`, `dir`)](#pointh--rotación-pp-dir)
  - [`Point.h` — proyección y reflexión](#pointh--proyección-y-reflexión)
  - [`AngleCmp.h`](#anglecmph)
  - [`SegDist.h`](#segdisth)
  - [`SegIsect.h`](#segisecth)
- [Polygons](#polygons)
  - [`ConvexHull.h`](#convexhullh)
  - [`PolygonCenArea.h`](#polygoncenareah)
  - [`InPolygon.h`](#inpolygonh)
  - [Punto en convexo en O(log n) — no está en la librería](#punto-en-convexo-en-olog-n--no-está-en-la-librería)
  - [`HullDiameter.h`](#hulldiameterh)
  - [`MinkowskiSum.h`](#minkowskisumh)
  - [`HalfPlaneIsect.h`](#halfplaneisecth)
  - [`LineHull.h`](#linehullh)
- [Circles](#circles)
- [Misc](#misc)
- [Lo que el set no cubre](#lo-que-el-set-no-cubre)
- [Cómo se verificó](#cómo-se-verificó)

---

## Primitives

### `Point.h` — orientación (`cross`)

**Directo**

| juez | problema |
|---|---|
| CSES | [Point Location Test](https://cses.fi/problemset/task/2189) |
| Aizu | [CGL_1_C Counter-Clockwise](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C) |

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | ≈274 | [ABC181 C — Collinearity](https://atcoder.jp/contests/abc181/tasks/abc181_c) | `cross == 0` en cada terna; $n \le 100$ |
| | ≈516 | [ABC266 C — Convex Quadrilateral](https://atcoder.jp/contests/abc266/tasks/abc266_c) | convexo ⟺ los 4 giros consecutivos tienen el mismo signo |
| ★ | 1900 | [CF 552D — Vanya and Triangles](https://codeforces.com/problemset/problem/552/D) | contar ternas colineales agrupando direcciones desde cada punto |
| ★ | 2000 | [CF 961D — Pair Of Lines](https://codeforces.com/problemset/problem/961/D) | probar las rectas por 2 de los 3 primeros puntos; el resto, con `cross` |
| ★ | 2100 | [CF 340B — Maximal Area Quadrilateral](https://codeforces.com/problemset/problem/340/B) | fijar la diagonal; el mejor punto de cada lado por `cross` |

### `Point.h` — rotación (`P*P`, `dir`)

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | ≈180 | [ABC259 B — Counterclockwise Rotation](https://atcoder.jp/contests/abc259/tasks/abc259_b) | `p * dir(θ)` |
| | ≈831 | [ABC197 D — Opposite](https://atcoder.jp/contests/abc197/tasks/abc197_d) | rotar $2\pi/N$ alrededor del centro del polígono |
| ★ | ≈2074 | [ABC207 D — Congruence Points](https://atcoder.jp/contests/abc207/tasks/abc207_d) | centroides al origen, probar rotaciones con cociente complejo `a / b` |

### `Point.h` — proyección y reflexión

| juez | problema | |
|---|---|---|
| Aizu | [CGL_1_A Projection](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A) | `foot` |
| Aizu | [CGL_1_B Reflection](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B) | `reflect` |

### `AngleCmp.h`

**Directo**

| juez | problema |
|---|---|
| Library Checker | [Sort Points by Argument](https://judge.yosupo.jp/problem/sort_points_by_argument) |

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| ★ | ≈1678 | [ABC225 E — 7](https://atcoder.jp/contests/abc225/tasks/abc225_e) | cada 7 es un intervalo angular; ordenar los extremos con `cross`, sin `atan2` |
| | 1800 | [CF 257C — View Angle](https://codeforces.com/problemset/problem/257/C) | ordenar por ángulo y buscar el mayor hueco circular |
| ★ | 2300 | [CF 598C — Nearest vectors](https://codeforces.com/problemset/problem/598/C) | ordenar y comparar consecutivos, incluido el par último–primero |

### `SegDist.h`

**Directo**

| juez | problema |
|---|---|
| Aizu | [CGL_2_D Distance](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D) — segmento a segmento |
| Kattis | [Line Segment Distance](https://open.kattis.com/problems/segmentdistance) |
| AtCoder | [math-and-algorithm 033 — Distance](https://atcoder.jp/contests/math-and-algorithm/tasks/math_and_algorithm_ae) — punto a segmento |

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| ★ | 1900 | [CF 613A — Peter and Snow Blower](https://codeforces.com/problemset/problem/613/A) | radio interior = mínimo `segDist` a las aristas; exterior = vértice más lejano |
| ★ | 2300 | [CF 1046I — Say Hello](https://codeforces.com/problemset/problem/1046/I) | en el marco de uno, el otro recorre un segmento por intervalo: `segDist` al origen |

### `SegIsect.h`

**Directo**

| juez | problema |
|---|---|
| CSES | [Line Segment Intersection](https://cses.fi/problemset/task/2190) |
| Aizu | [CGL_2_B Intersection](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B) — ¿se cortan? |
| Aizu | [CGL_2_C Cross Point](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C) — el punto de corte |
| Kattis | [Line Segment Intersection](https://open.kattis.com/problems/segmentintersection) — con solapamientos |
| AtCoder | [math-and-algorithm 037 — Intersection](https://atcoder.jp/contests/math-and-algorithm/tasks/math_and_algorithm_ah) |

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | Silver | [USACO 2019 Open — Cow Steeplechase II](http://www.usaco.org/index.php?page=viewproblem2&cpid=943) | barrido de segmentos con `segIsect` como predicado |
| | Gold | [USACO 2013 Mar — Hill Walk](http://www.usaco.org/index.php?page=viewproblem2&cpid=266) | barrido; el orden vertical entre segmentos sale de `cross` |

---

## Polygons

### `ConvexHull.h`

**Directo**

| juez | problema |
|---|---|
| CSES | [Convex Hull](https://cses.fi/problemset/task/2195) |
| Aizu | [CGL_4_A Convex Hull](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A) |
| Kattis | [Convex Hull](https://open.kattis.com/problems/convexhull) |
| Library Checker | [Static Convex Hull](https://judge.yosupo.jp/problem/static_convex_hull) |

> **CSES y Aizu piden los puntos colineales del borde**, y este hull es estricto: los descarta. Ahí hay que adaptarlo (cambiar `>= 0` por `> 0` en `ulHull`).

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| ★ | 2100 | [CF 1299C — Water Balance](https://codeforces.com/problemset/problem/1299/C) | envolvente **inferior** de las sumas prefijas (`ulHull`) |
| | Platinum | [USACO 2018 Dec — Balance Beam](http://www.usaco.org/index.php?page=viewproblem2&cpid=864) | envolvente **superior** de los puntos $(k, f(k))$ |
| ★ | 2400 | [CF 1142C — U2](https://codeforces.com/problemset/problem/1142/C) | pasar a $(x,\ y - x^2)$ y contar aristas de la envolvente superior; **acá importa que sea estricto** |
| | ≈2905 | [ABC202 F — Integer Convex Hull](https://atcoder.jp/contests/abc202/tasks/abc202_f) | reto: DP sobre polígonos convexos con `cross` y paridad del área |

### `PolygonCenArea.h`

**Directo**

| juez | problema |
|---|---|
| CSES | [Polygon Area](https://cses.fi/problemset/task/2191) |
| Aizu | [CGL_3_A Area](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A) |
| Kattis | [Polygon Area](https://open.kattis.com/problems/polygonarea) — también pide la orientación (CW/CCW): sale del signo |
| Aizu | [CGL_3_B Is-Convex](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B) — con `cross`, no con el área |

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | — | [CSES — Polygon Lattice Points](https://cses.fi/problemset/task/2193) | área + puntos del borde por `gcd` → teorema de Pick |

### `InPolygon.h`

**Directo**

| juez | problema |
|---|---|
| CSES | [Point in Polygon](https://cses.fi/problemset/task/2192) |
| Aizu | [CGL_3_C Polygon-Point-Containment](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C) |
| Kattis | [Point in Polygon](https://open.kattis.com/problems/pointinpolygon) |
| AtCoder | [math-and-algorithm 098 — Polygon and Point](https://atcoder.jp/contests/math-and-algorithm/tasks/math_and_algorithm_bu) |

### Punto en convexo en O(log n) — no está en la librería

`inPoly` es $O(n)$ por consulta. Estos problemas tienen demasiadas consultas para eso: hace falta la binaria angular sobre el convexo (ver [Polygons → Lo que no está](Polygons/README.md#lo-que-no-está)).

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | Gold | [USACO 2014 Jan — Cow Curling](http://www.usaco.org/index.php?page=viewproblem2&cpid=382) | capturada ⟺ dentro del hull rival, **borde incluido**; $N = 5 \cdot 10^4$ |
| ★ | 2100 | [CF 166B — Polygons](https://codeforces.com/problemset/problem/166/B) | B adentro de A ⟺ cada vértice de B estrictamente dentro de A; A tiene hasta $10^5$ vértices |
| ★ | ≈2241 | [ABC296 G — Polygon and Points](https://atcoder.jp/contests/abc296/tasks/abc296_g) | $N, Q \le 2 \cdot 10^5$: con `inPoly` no alcanza |

### `HullDiameter.h`

**Directo**

| juez | problema |
|---|---|
| Aizu | [CGL_4_B Diameter of a Convex Polygon](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B) |
| Library Checker | [Furthest Pair of Points](https://judge.yosupo.jp/problem/furthest_pair) |
| Kattis | [Robert Hood](https://open.kattis.com/problems/roberthood) |

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | — | [Kattis — Fence Orthogonality](https://open.kattis.com/problems/fenceortho) | *rotating calipers* sobre el hull, pero con un rectángulo envolvente en vez del diámetro |

### `MinkowskiSum.h`

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | 2500 | [CF 1195F — Geometers Anonymous Club](https://codeforces.com/problemset/problem/1195/F) | vértices de la suma = direcciones de arista distintas; contar distintos en un rango |
| | 2600 | [CF 87E — Mogohu-Rea Idol](https://codeforces.com/problemset/problem/87/E) | sumar los 3 convexos; cada consulta es "¿$3q$ está en la suma?" |

### `HalfPlaneIsect.h`

**Directo**

| juez | problema |
|---|---|
| Kattis | [Big Brother](https://open.kattis.com/problems/bigbrother) — núcleo de un polígono |
| Kattis | [Art Appreciation](https://open.kattis.com/problems/artappreciation) |

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | ≈2468 | [ABC251 G — Intersection of Polygons](https://atcoder.jp/contests/abc251/tasks/abc251_g) | por cada arista de P, el traslado más restrictivo: quedan $N$ semiplanos |

### `LineHull.h`

| juez | problema | cómo entra |
|---|---|---|
| Aizu | [CGL_4_C Convex Cut](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C) | `lineHull` ubica las dos aristas que corta la recta; el área de un lado, con `cenArea` |

---

## Circles

**USACO Guide no tiene módulo de círculos**, y Codeforces casi no los usa como tema propio. El grueso de la práctica es el set CGL de Aizu, que los cubre método por método.

| template | juez | problema |
|---|---|---|
| `isect(Circ, Circ)` | Aizu | [CGL_7_A Intersection of Circles](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A) — la relación entre dos círculos |
| `isect(Circ, Circ)` | Aizu | [CGL_7_E Cross Points of Circles](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E) |
| `isect(Circ, Line)` | Aizu | [CGL_7_D Cross Points of a Circle and a Line](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D) |
| `isect_area` | Aizu | [CGL_7_I Area of Intersection between Two Circles](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_I) |
| `tangent` | Aizu | [CGL_7_F Tangent to a Circle](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F) |
| `external`, `internal` | Aizu | [CGL_7_G Common Tangent](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G) |
| `ccCenter` | Aizu | [CGL_7_C Circumscribed Circle of a Triangle](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C) |
| `mec` | Aizu | [CGL_5_B Minimum Enclosing Circle](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_B) |

**Como pieza**

| | dificultad | problema | cómo entra |
|---|---|---|---|
| ★ | ≈1671 | [ABC151 F — Enclose All](https://atcoder.jp/contests/abc151/tasks/abc151_f) | `mec` directo |
| ★ | 2000 | [CF 600D — Area of Two Circles' Intersection](https://codeforces.com/problemset/problem/600/D) | `isect_area` directo |
| ★ | 2100 | [CF 1C — Ancient Berland Circus](https://codeforces.com/problemset/problem/1/C) | `ccCenter` de los 3 pilares; los ángulos centrales dan la cantidad de lados |

---

## Misc

### `ClosestPair.h`

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | — | [CSES — Minimum Euclidean Distance](https://cses.fi/problemset/task/2194) | directo |
| | — | [Aizu — CGL_5_A Closest Pair](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A) | directo |
| | — | [Kattis — Closest Pair](https://open.kattis.com/problems/closestpair2) | directo |
| | — | [AtCoder — math-and-algorithm 034 Nearest Points](https://atcoder.jp/contests/math-and-algorithm/tasks/math_and_algorithm_af) | directo |
| ★ | 2200 | [CF 429D — Tricky Function](https://codeforces.com/problemset/problem/429/D) | los puntos $(i,\ \text{prefijo}_i)$: es un par más cercano |

### `ManhattanMST.h`

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | — | [Library Checker — Manhattan MST](https://judge.yosupo.jp/problem/manhattanmst) | directo |
| | — | [Kattis — Grid MST](https://open.kattis.com/problems/gridmst) | directo |
| | — | [CSES — Maximum Manhattan Distances](https://cses.fi/problemset/task/3410) | la rotación de 45° del manual ($x+y$, $x-y$), sin MST |

### `MaxCollinear.h`

| | dificultad | problema | cómo entra |
|---|---|---|---|
| | — | [Kattis — Maximum Number of Colinear Points](https://open.kattis.com/problems/maxcolinear) | directo |
| ★ | 1900 | [CF 1163C2 — Power Transmission (Hard)](https://codeforces.com/problemset/problem/1163/C2) | `getline` como clave canónica de cada recta; contar pares no paralelos |

---

## Lo que el set no cubre

- **`HullTangents.h`** no tiene un problema canónico verificado: aparece como pieza dentro de otros.
- **`LineHull.h`** solo tiene Convex Cut, que además se resuelve en $O(n)$ sin él.
- **Semiplanos en Codeforces**: no encontré uno verificable en el rango objetivo.
- **CSES Geometry** tiene 16 problemas; 8 **no** usan estos templates: Intersection Points y Area of Rectangles (barrido con una estructura de datos), All Manhattan Distances (la suma se separa por coordenada), Line Segments Trace I/II y Lines and Queries I/II (máximo de rectas en cada $x$: Li Chao), y Robot Path (simulación con segmentos alineados a los ejes).

## Cómo se verificó

Ningún problema entró sin verificar que exista **y** que pida lo que dice la columna "cómo entra".

| fuente | cantidad | verificación |
|---|---:|---|
| CSES | 8 | IDs sacados de la sección Geometry oficial |
| AtCoder | 14 | enunciado leído en atcoder.jp; dificultad del modelo de AtCoder Problems |
| Codeforces | 16 | rating de la API oficial; enunciado leído en el índice de [yuantiji.ac](https://yuantiji.ac/), porque Codeforces bloquea el acceso automatizado |
| USACO | 4 | enunciado leído en usaco.org |
| Aizu | 21 | página del problema: 200 y título |
| Kattis, Library Checker | 16 | 200 y título |

La búsqueda semántica de yuantiji encontró sobre todo los problemas **directos** (sus enunciados son abstractos y se parecen a la descripción del template). Los **como pieza** de Codeforces y AtCoder vienen envueltos en una historia y la búsqueda no los alcanza: esos salieron de filtrar los 431 problemas con tag `geometry` de la API de Codeforces y de leer cada enunciado.

Dos casos de ronda espejo: **613A** aparece en yuantiji como 614C, y **1142C** como 1143F. Mismo problema; acá va el ID que tiene rating.
