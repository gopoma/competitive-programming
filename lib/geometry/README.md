# Geometría

**21 headers** en 4 directorios, con un manual por directorio y 19 figuras.

Todos compilan juntos con las flags del `Makefile` (`-Wall -Wextra -Wconversion -Wshadow -Wfloat-equal -D_GLIBCXX_DEBUG`) **sin un solo warning**, y están verificados contra fuerza bruta o una referencia independiente en **~910.000 casos**.

---

## Índice

- [Los cuatro directorios](#los-cuatro-directorios)
- [Los 21 headers](#los-21-headers)
  - [Primitives](#primitives)
  - [Polygons](#polygons)
  - [Circles](#circles)
  - [Misc](#misc)
- [Qué depende de qué](#qué-depende-de-qué)
- [Elegir `T`: `db` o `ll`](#elegir-t-db-o-ll)
- [Cómo se arma la submission](#cómo-se-arma-la-submission)
- [Choques de nombres](#choques-de-nombres)
- [Verificación](#verificación)
- [Lo que no está](#lo-que-no-está)

---

## Los cuatro directorios

| directorio | qué cubre | headers | manual | figuras |
|---|---|---:|---|---:|
| [`Primitives/`](Primitives) | el tipo punto y todo lo que se construye sobre él: orientación, distancias, intersección de segmentos, orden angular | 4 | [manual](Primitives/README.md) | 6 |
| [`Polygons/`](Polygons) | convex hull, área, punto en polígono, tangentes, Minkowski, semiplanos | 9 | [manual](Polygons/README.md) | 8 |
| [`Circles/`](Circles) | intersección, tangentes, circuncentro, círculo mínimo | 5 | [manual](Circles/README.md) | 3 |
| [`Misc/`](Misc) | par más cercano, MST Manhattan, máximos colineales | 3 | [manual](Misc/README.md) | 2 |

Las figuras están en [`img/`](img) como SVG, y se adaptan al tema claro y al oscuro.

**Empezá por [`Primitives/README.md`](Primitives/README.md).** Todo lo demás da por sentado `Point.h`.

---

## Los 21 headers

### Primitives

| header | qué da | complejidad |
|---|---|---|
| [`Point.h`](Primitives/Point.h) | el tipo `P`, `cross`, `dot`, `sgn`, `abs`, `arg`, `dir`, `unit`, `perp`, `conj`, `reflect`, `foot`, `onSeg` | $O(1)$ |
| [`AngleCmp.h`](Primitives/AngleCmp.h) | `angleCmp`: orden antihorario alrededor del origen, sin `atan2` | $O(1)$ |
| [`SegDist.h`](Primitives/SegDist.h) | `lineDist` (recta infinita) y `segDist` (segmento) | $O(1)$ |
| [`SegIsect.h`](Primitives/SegIsect.h) | `lineIsect`, `segIsect`, `strictIsect` | $O(1)$ |

→ [manual de Primitives](Primitives/README.md)

### Polygons

| header | qué da | complejidad |
|---|---|---|
| [`ConvexHull.h`](Polygons/ConvexHull.h) | `hull` por cadena monótona, y `ulHull` (cadenas de arriba y abajo por separado) | $O(N \log N)$ |
| [`ConvexHullGraham.h`](Polygons/ConvexHullGraham.h) | `hull` por Graham scan — **alternativa** a la anterior, no complemento | $O(N \log N)$ |
| [`PolygonCenArea.h`](Polygons/PolygonCenArea.h) | `cenArea`: centroide y área **con signo** | $O(N)$ |
| [`InPolygon.h`](Polygons/InPolygon.h) | `inPoly`: adentro / borde / afuera, en polígono simple | $O(N)$ |
| [`HullDiameter.h`](Polygons/HullDiameter.h) | `diameter2`: cuadrado de la máxima distancia (rotating calipers) | $O(N \log N)$ |
| [`HullTangents.h`](Polygons/HullTangents.h) | `tangents`: las dos tangentes desde un punto exterior | $O(\log N)$ |
| [`MinkowskiSum.h`](Polygons/MinkowskiSum.h) | `minkowski_sum` de dos convexos en CCW | $O(N)$ |
| [`LineHull.h`](Polygons/LineHull.h) | `lineHull` (recta contra convexo) y `extrVertex` | $O(\log N)$ |
| [`HalfPlaneIsect.h`](Polygons/HalfPlaneIsect.h) | `halfPlaneIsect`: vértices de la intersección de semiplanos | $O(N \log N)$ |

→ [manual de Polygons](Polygons/README.md)

### Circles

| header | qué da | complejidad |
|---|---|---|
| [`Circle.h`](Circles/Circle.h) | el tipo `Circ`, `in` (adentro/borde/afuera), `arcLength` | $O(1)$ |
| [`CircleIsect.h`](Circles/CircleIsect.h) | `isect(Circ,Circ)`, `isect(Circ,Line)`, `isect_area` | $O(1)$ |
| [`CircleTangents.h`](Circles/CircleTangents.h) | `tangent`, `external`, `internal` | $O(1)$ |
| [`Circumcenter.h`](Circles/Circumcenter.h) | `ccCenter`: circuncentro y circunradio de un triángulo | $O(1)$ |
| [`MinEnclosingCirc.h`](Circles/MinEnclosingCirc.h) | `mec`: círculo mínimo que contiene todos los puntos | $O(N)$ esperado |

→ [manual de Circles](Circles/README.md)

### Misc

| header | qué da | complejidad |
|---|---|---|
| [`ClosestPair.h`](Misc/ClosestPair.h) | `solve`: los dos puntos más cercanos, por barrido | $O(N \log N)$ |
| [`ManhattanMST.h`](Misc/ManhattanMST.h) | `manhattanMst`: hasta $4N$ aristas que contienen un MST | $O(N \log N)$ |
| [`MaxCollinear.h`](Misc/MaxCollinear.h) | `solve`: máxima cantidad de puntos sobre una misma recta | $O(n^2 \log n)$ |

→ [manual de Misc](Misc/README.md)

---

## Qué depende de qué

```
Point.h  ──────────────────────────────────┐
  │                                        │
  ├── AngleCmp.h ──┐                       │ (todo Polygons,
  │                │                       │  todo Misc,
  │                ▼                       │  todo Circles)
  │        HalfPlaneIsect.h                │
  │                                        │
  ├── Circle.h ──┬── CircleIsect.h         │
  │              ├── CircleTangents.h      │
  │              └── Circumcenter.h ── MinEnclosingCirc.h
  │
  └── ConvexHull.h  (o ConvexHullGraham.h) ── HullDiameter.h
```

Los demás headers solo necesitan `Point.h`. Las únicas tres dependencias que no son `Point.h`:

- `HalfPlaneIsect.h` → también **`AngleCmp.h`**
- `HullDiameter.h` → también **un hull** (llama a `hull()`; sirve cualquiera de los dos)
- `MinEnclosingCirc.h` → también **`Circumcenter.h`** (y `Circle.h`)

`ManhattanMST.h` no usa `Point.h`: trabaja con `vpi` directamente. Después hay que correrle un MST encima (Kruskal + `DSU`).

---

## Elegir `T`: `db` o `ll`

`Point.h` abre con un solo escalar que cubre dos necesidades enfrentadas:

```cpp
using T = db;        // db = long double, o ll
const T EPS = 1e-9;
```

| | `T = db` (default) | `T = ll` |
|---|---|---|
| predicados (`sgn`, `cross`) | aproximados, con `EPS` | **exactos** |
| métrica (`abs`, `arg`, `unit`, `foot`) | correctos | **truncan en silencio** |

**Regla práctica:** coordenadas enteras y solo necesitás orientación, área o comparar distancias → `T = ll`, y no uses `abs`/`arg`/`unit`. Necesitás distancias o ángulos reales → dejá `T = db`.

> **No cambies `db` a `double`.** `long double` tiene mantisa de 64 bits y hace exacto el `cross` de enteros de hasta $10^9$; con `double` los predicados empiezan a fallar desde $10^8$.

El detalle completo, con la tabla de errores medidos: [Primitives → Elegir `T`](Primitives/README.md#elegir-t-db-o-ll) y [Cuánto aguanta `db`](Primitives/README.md#cuánto-aguanta-db).

---

## Cómo se arma la submission

Copiás `templateHeavy.cpp` en `E.cpp` y pegás el **código** de los headers que necesites en la sección de template.

> **Los `#include` no van en la solución.** Ningún header de esta librería tiene `#include`. El campo `Requiere:` del encabezado es solo un **indicador** de qué otros templates hay que pegar también, y en qué orden.

El orden es el del diagrama de arriba: `Point.h` primero, siempre.

Cada manual trae la tabla *"si pegás / pegá antes"* de su directorio:
[Primitives](Primitives/README.md#cómo-se-arma-la-submission) ·
[Polygons](Polygons/README.md#cómo-se-arma-la-submission) ·
[Circles](Circles/README.md#cómo-se-arma-la-submission) ·
[Misc](Misc/README.md#cómo-se-arma-la-submission)

---

## Choques de nombres

| nombre | choca con | resultado |
|---|---|---|
| `hullInd`, `hull` en `ConvexHull.h` | lo mismo en `ConvexHullGraham.h` | **no conviven** — son alternativas, elegí una |
| `solve` en `ClosestPair.h` | `solve` en `MaxCollinear.h` | conviven (sobrecarga: `vP` vs `vpi`) |
| `solve` en los dos | tu `void solve()` de `templateHeavy.cpp` | conviven (la tuya no toma argumentos) |
| `getline` en `MaxCollinear.h` | `std::getline` | conviven (`getline(cin, s)` sigue andando) |

Los últimos tres los compilé y corrí. Detalle en [Misc → choques de nombres](Misc/README.md#tres-choques-de-nombres-todos-verificados).

---

## Verificación

| directorio | casos | contra |
|---|---:|---|
| Primitives | 238.000 | `cross` exacto en `ll` y `__int128`, fórmulas independientes |
| Polygons | 403.951 | fuerza bruta $O(n^2)$, *shoelace*, *crossing number*, Sutherland-Hodgman |
| Circles | 249.900 | invariantes de tangencia, fuerza bruta sobre pares y ternas |
| Misc | 17.800 | MST del grafo completo, fuerza bruta en `__int128` |
| **total** | **909.651** | |

La tabla por rutina está al final de cada manual:
[Primitives](Primitives/README.md#verificación) ·
[Polygons](Polygons/README.md#verificación) ·
[Circles](Circles/README.md#verificación) ·
[Misc](Misc/README.md#verificación)

---

## Lo que no está

De los 36 headers de geometría del [cp-notebook de Benq](https://github.com/bqi343/cp-notebook/tree/master/Implementations/content/geometry%20(13)) quedaron afuera 15, a propósito:

| qué | por qué |
|---|---|
| `3D` (5 headers) | otro tipo punto; fuera de alcance para CF/AtCoder |
| `Delaunay` (3) | muy raro en contest; arrastra dependencias |
| `KD-tree` (2) | 9 errores contra esta librería, y su $O(\log N)$ solo vale para puntos uniformes |
| `Complex`, `ComplexComp`, `PointShort` | **reemplazos** de `Point.h` (20, 5 y 24 errores) |
| `HalfPlaneSet` | redefine `T`, `INF` y `Line` (32 errores) y su `Maximize` está marcado UNTESTED |
| `_old_HalfPlaneIsect` | versión vieja de `HalfPlaneIsect.h` |

Tampoco hay **punto en polígono convexo en $O(\log n)$** como rutina propia: `inPoly` es $O(n)$, y la versión logarítmica sale de `tangents` en ~10 líneas. Benq tampoco la tiene.
