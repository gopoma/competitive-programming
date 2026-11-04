# Geometría

21 headers, 4 manuales, [19 figuras](img). Compilan juntos sin warnings; ~910.000 casos verificados.

[Headers](#headers) · [Dependencias](#dependencias) · [`T`: `db` o `ll`](#t-db-o-ll) · [Cómo se pega](#cómo-se-pega)

| directorio | qué cubre | headers |
|---|---|---:|
| [**Primitives**](Primitives/README.md) | punto, orientación, distancias, intersección, orden angular | 4 |
| [**Polygons**](Polygons/README.md) | hull, área, punto en polígono, tangentes, Minkowski, semiplanos | 9 |
| [**Circles**](Circles/README.md) | intersección, tangentes, circuncentro, círculo mínimo | 5 |
| [**Misc**](Misc/README.md) | par más cercano, MST Manhattan, máximos colineales | 3 |

Empezá por **Primitives**. Todo lo demás supone `Point.h`.

## Headers

**Primitives**

| header | qué da | |
|---|---|---|
| [`Point.h`](Primitives/Point.h) | el tipo `P` y 14 operaciones (`cross`, `dot`, `sgn`, `foot`, `onSeg`, …) | $O(1)$ |
| [`AngleCmp.h`](Primitives/AngleCmp.h) | orden antihorario, sin `atan2` | $O(1)$ |
| [`SegDist.h`](Primitives/SegDist.h) | distancia punto–recta y punto–segmento | $O(1)$ |
| [`SegIsect.h`](Primitives/SegIsect.h) | intersección recta/segmento | $O(1)$ |

**Polygons**

| header | qué da | |
|---|---|---|
| [`ConvexHull.h`](Polygons/ConvexHull.h) | hull por cadena monótona, + `ulHull` | $O(N \log N)$ |
| [`ConvexHullGraham.h`](Polygons/ConvexHullGraham.h) | hull por Graham — *alternativa*, no complemento | $O(N \log N)$ |
| [`PolygonCenArea.h`](Polygons/PolygonCenArea.h) | centroide y área con signo | $O(N)$ |
| [`InPolygon.h`](Polygons/InPolygon.h) | adentro / borde / afuera | $O(N)$ |
| [`HullDiameter.h`](Polygons/HullDiameter.h) | máxima distancia al cuadrado | $O(N \log N)$ |
| [`HullTangents.h`](Polygons/HullTangents.h) | tangentes desde un punto exterior | $O(\log N)$ |
| [`MinkowskiSum.h`](Polygons/MinkowskiSum.h) | suma de dos convexos | $O(N)$ |
| [`LineHull.h`](Polygons/LineHull.h) | recta contra convexo, vértice extremo | $O(\log N)$ |
| [`HalfPlaneIsect.h`](Polygons/HalfPlaneIsect.h) | intersección de semiplanos | $O(N \log N)$ |

**Circles**

| header | qué da | |
|---|---|---|
| [`Circle.h`](Circles/Circle.h) | tipo `Circ`, `in`, `arcLength` | $O(1)$ |
| [`CircleIsect.h`](Circles/CircleIsect.h) | círculo–círculo, círculo–recta, área común | $O(1)$ |
| [`CircleTangents.h`](Circles/CircleTangents.h) | tangentes internas y externas | $O(1)$ |
| [`Circumcenter.h`](Circles/Circumcenter.h) | circuncentro y circunradio | $O(1)$ |
| [`MinEnclosingCirc.h`](Circles/MinEnclosingCirc.h) | círculo mínimo | $O(N)$ esperado |

**Misc**

| header | qué da | |
|---|---|---|
| [`ClosestPair.h`](Misc/ClosestPair.h) | los dos puntos más cercanos | $O(N \log N)$ |
| [`ManhattanMST.h`](Misc/ManhattanMST.h) | $4N$ aristas que contienen un MST | $O(N \log N)$ |
| [`MaxCollinear.h`](Misc/MaxCollinear.h) | máximos puntos sobre una recta | $O(n^2 \log n)$ |

## Dependencias

Todos piden `Point.h` y nada más, salvo:

- `HalfPlaneIsect.h` → **+ `AngleCmp.h`**
- `HullDiameter.h` → **+ un hull** (llama a `hull()`; sirve cualquiera)
- `CircleIsect.h`, `CircleTangents.h`, `Circumcenter.h` → **+ `Circle.h`**
- `MinEnclosingCirc.h` → **+ `Circle.h`, `Circumcenter.h`**
- `ManhattanMST.h` → **nada** (trabaja con `vpi`; después corré Kruskal + `DSU`)

> `ConvexHull.h` y `ConvexHullGraham.h` definen los dos `hull` e `hullInd`: **son alternativas, elegí una.** Usá `ConvexHull.h`.

## `T`: `db` o `ll`

| | `db` (default) | `ll` |
|---|---|---|
| `sgn`, `cross` | con `EPS` | **exactos** |
| `abs`, `arg`, `unit`, `foot` | correctos | **truncan** |

Coordenadas enteras y solo orientación, área o comparar distancias → `ll`. Distancias o ángulos reales → `db`.

> **Nunca `double`.** `long double` hace exacto el `cross` hasta $10^9$; `double` falla desde $10^8$. — [detalle](Primitives/README.md#cuánto-aguanta-db)

## Cómo se pega

`templateHeavy.cpp` → `E.cpp`, y pegás el **código** del header en la sección de template, `Point.h` primero.

> **Los `#include` no van en la solución.** Ningún header tiene uno. El campo `Requiere:` solo indica qué más pegar y en qué orden.

---

Choques de nombres → [Misc](Misc/README.md#tres-choques-de-nombres-todos-verificados) · Verificación por rutina → final de cada manual · Lo que quedó afuera de cp-notebook → [Polygons](Polygons/README.md#lo-que-no-está)
