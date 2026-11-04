# Misc

Par más cercano, MST con distancia Manhattan, y máxima cantidad de puntos colineales.

Manual de consulta: **qué hace cada método, qué le podés pasar y hasta dónde aguanta.** Los problemas donde practicar están en [PROBLEMS.md](../PROBLEMS.md).

## Índice

- [Cómo se arma la submission](#cómo-se-arma-la-submission)
- [Choques de nombres](#choques-de-nombres)
- [`ClosestPair.h`](#closestpairh)
  - [`solve`](#solve)
- [`ManhattanMST.h`](#manhattanmsth)
  - [`manhattanMst`](#manhattanmst)
- [`MaxCollinear.h`](#maxcollinearh)
  - [`getline`](#getline)
  - [`solve`](#solve-1)
- [Casos degenerados](#casos-degenerados)
- [Ejemplo completo](#ejemplo-completo)
- [Verificación](#verificación)

## Cómo se arma la submission

Copiás `templateHeavy.cpp` en `E.cpp` y pegás el **código** del header en la sección de template.

> **Los `#include` no van en la solución.** Ningún header de esta librería tiene uno. El campo `Requiere:` es solo un indicador de qué más pegar, y en qué orden.

| header | tipo de entrada | pegá antes |
|---|---|---|
| `ClosestPair.h` | `vP` = `vector<pair<T,T>>` | **`Point.h`** |
| `ManhattanMST.h` | `vpi` = `vector<pair<int,int>>` | — nada |
| `MaxCollinear.h` | `vpi` = `vector<pair<int,int>>` | — nada |

Los dos últimos trabajan con coordenadas **`int`** y son independientes del resto de la librería.

## Choques de nombres

| nombre | choca con | resultado |
|---|---|---|
| `solve` de `ClosestPair.h` | `solve` de `MaxCollinear.h` | conviven (sobrecarga `vP` vs `vpi`) |
| ambos `solve` | tu `void solve()` de `templateHeavy.cpp` | conviven (la tuya no toma argumentos) |
| `getline` de `MaxCollinear.h` | `std::getline` | conviven (`getline(cin, s)` sigue andando) |

Los tres compilados y corridos. Pero si pegás `ClosestPair.h` y dentro de tu `solve()` escribís `solve(v)`, mirá a quién estás llamando.

---

## `ClosestPair.h`

**Requiere:** `Point.h`

### `solve`

```cpp
pair<P,P> solve(vP v);
```

Los **dos puntos más cercanos** del conjunto. Devuelve el par, no la distancia: `abs(r.f - r.s)`.

Si hay puntos repetidos devuelve ese punto dos veces y corta de entrada.

**Restricciones**: $n \ge 2$ · **Tipo**: `db` (usa `abs`, que con `ll` trunca) · **Aguanta**: coordenadas hasta $\approx 4.3 \cdot 10^9$ con `db` = `long double` · **Complejidad**: $O(n \log n)$, barrido con `set`.

![el barrido y la franja activa](../img/closestpair-franja.svg)

Toma `v` **por copia**: lo ordena.

```cpp
solve({{0,0},{5,5},{0,0}})  ->  (0,0) (0,0)     // duplicado: distancia 0
solve({{0,0},{3,4}})        ->  dist = 5
```

---

## `ManhattanMST.h`

**Independiente** (no requiere `Point.h`)

### `manhattanMst`

```cpp
V<pair<ll,pi>> manhattanMst(vpi v);
```

Devuelve **hasta $4n$ aristas** que contienen un MST del grafo completo con peso $|p_x - q_x| + |p_y - q_y|$. Formato: `{distancia, {índice_origen, índice_destino}}`.

> **No devuelve el MST, devuelve las candidatas.** Hay que correrles un MST encima.

**Restricciones**: coordenadas `int`; **puede haber repetidos** (generan aristas de peso 0); **no requiere ningún orden** de entrada · **Tipo**: entrada `int`, pesos `ll` · **Aguanta**: coordenadas hasta $10^9$ — las diferencias llegan a $2 \cdot 10^9$ y las sumas a $4 \cdot 10^9$, por eso los pesos son `ll` y un `int` desbordaría · **Complejidad**: $O(n \log n)$.

![los 8 octantes y el vecino más cercano](../img/manhattan-octantes.svg)

Toma `v` **por copia**: le hace cuatro rotaciones del plano.

**Las aristas pueden venir repetidas** — un mismo par puede ser el vecino más cercano en más de un octante. Kruskal las descarta solo; no hace falta deduplicar.

```cpp
manhattanMst({{0,0}})          ->  0 aristas
manhattanMst({{0,0},{0,0}})    ->  4 aristas, todas de peso 0
manhattanMst(50 puntos)        ->  157 aristas   (la cota 4n seria 200)
```

**También sirve para distancia Chebyshov** ($L_\infty$): rotando el plano 45° ($x' = x+y$, $y' = x-y$), $L_\infty$ pasa a ser $L_1$. Cada peso resultante es el **doble** de la distancia Chebyshov.

---

## `MaxCollinear.h`

**Independiente** (no requiere `Point.h`)

### `getline`

```cpp
pair<pi,ll> getline(pi a, pi b);
```

La **clave canónica** de la recta que pasa por `a` y `b`. Dos pares de puntos de la misma recta dan la misma clave.

**Restricciones**: **`a != b`** — un `assert` lo verifica; con dos puntos iguales la dirección es $(0,0)$, `gcd(0,0)` da 0 y se divide por cero · **Tipo**: entrada `int`, desplazamiento `ll` · **Aguanta**: con coordenadas de $10^5$ el desplazamiento ya llega a $10^{10}$ y un `int` desbordaría; con `ll` entra hasta $10^9$ · **Complejidad**: $O(\log \max|c|)$, lo domina el `gcd`.

```cpp
getline({0,0}, {2,2})  ->  {(-1,1), 0}
getline({3,3}, {5,5})  ->  {(-1,1), 0}    // misma recta y = x, misma clave
```

> El nombre choca con `std::getline`, pero conviven.

### `solve`

```cpp
int solve(vpi p);
```

La **máxima cantidad de puntos sobre una misma recta**.

**Restricciones**: **no puede haber dos puntos iguales** (el `assert` de `getline` lo corta) · **Tipo**: entrada `int` · **Aguanta**: coordenadas hasta $10^9$ verificado; **el límite real es $n$**: son $\binom{n}{2}$ inserciones en un `map`, así que $n \approx 2000$ es el techo práctico y con $n = 10^5$ es inviable · **Complejidad**: $O(n^2 \log n)$.

```cpp
solve({})                        ->  0
solve({{0,0}})                   ->  1
solve({{0,0},{1,1},{2,2}})       ->  3    // todos alineados
solve({{0,0},{1,0},{0,1}})       ->  2    // ninguna recta tiene 3
```

---

## Casos degenerados

Todas las salidas de esta tabla son de correr el código, no estimadas.

| entrada | `ClosestPair::solve` | `manhattanMst` | `MaxCollinear::solve` |
|---|---|---|---|
| vacío | **precondición rota** ($n \ge 2$) | 0 aristas | `0` |
| 1 punto | **precondición rota** | 0 aristas | `1` |
| 2 puntos iguales | el punto dos veces, dist 0 | 4 aristas de peso 0 | **`assert` de `getline`** |
| todos colineales | el par más cercano, normal | normal | `n` |
| todos iguales | el punto dos veces, dist 0 | aristas de peso 0 | **`assert`** |

## Ejemplo completo

MST Manhattan de 5 puntos, con las salidas intermedias:

```cpp
vpi v = {{0,0},{3,1},{1,4},{5,5},{2,2}};

auto ed = manhattanMst(v);
cout << sz(ed) << "\n";                       // 9      (la cota 4n seria 20)
sort(all(ed));
each(e, ed) cout << e.f << ":" << e.s.f << "-" << e.s.s << " ";
// 2:1-4  2:1-4  3:4-2  4:1-0  4:4-0  5:3-2  6:3-1  6:3-4  6:3-4
//        ^^^^^ repetida, Kruskal la descarta sola

DSU D; D.init(sz(v));
ll total = 0; int usadas = 0;
each(e, ed) if (D.unite(e.s.f, e.s.s)) { total += e.f; ++usadas; }
// toma 1-4 (2), 4-2 (3), 1-0 (4), 3-2 (5)
cout << total << " " << usadas << "\n";       // 14 4   (usadas == n-1 => conexo)
```

De los 10 pares posibles nunca se generan tres: **0–2 (5)**, **0–3 (10)** y **1–2 (5)**. Los tres son el máximo **estricto** de un ciclo, así que ningún MST los usaría:

| ausente | ciclo | pesos |
|---|---|---|
| 0–2 (5) | 0–4–2–0 | 4, 3, **5** |
| 0–3 (10) | 0–4–2–3–0 | 4, 3, 5, **10** |
| 1–2 (5) | 1–4–2–1 | 2, 3, **5** |

Chebyshov con el mismo header:

```cpp
vpi w; each(p, v) w.pb({p.f + p.s, p.f - p.s});   // rota 45 grados
auto ed2 = manhattanMst(w);                       // cada peso es el DOBLE
```

## Verificación

| rutina | casos | contra |
|---|---|---|
| `manhattanMst` | 6.300 | MST del grafo completo $O(n^2)$, $C$ hasta $10^9$ |
| `getline`, `solve` (MaxCollinear) | 6.000 | fuerza bruta en `__int128`, $C$ hasta $10^9$ |
| `solve` (ClosestPair) | 5.500 | fuerza bruta $O(n^2)$, con duplicados y colineales |

Los tres compilan con las flags del `Makefile` sin warnings.

`ManhattanMST.h` **no compilaba** antes del commit `57c7c7f` (incluía `"DSU (7.6).h"`, una ruta inexistente), y `MaxCollinear.h` **crasheaba** con duplicados y desbordaba su clave con coordenadas de $10^5$.
