# Misc

Tres algoritmos sueltos que no entran en las otras categorías: par más cercano, MST con distancia Manhattan, y máxima cantidad de puntos colineales.

## Cómo se pega

```cpp
#include "Point.h"          // SOLO si usas ClosestPair.h
#include "ClosestPair.h"

#include "ManhattanMST.h"   // no necesita Point.h
#include "MaxCollinear.h"   // no necesita Point.h
```

**Los tipos de entrada son inconsistentes** entre los tres, y conviene saberlo antes de pelearse con el compilador:

| header | entrada | requiere `Point.h` |
|---|---|---|
| `ClosestPair.h` | `vP` = `vector<pair<T,T>>` | **sí** |
| `ManhattanMST.h` | `vpi` = `vector<pair<int,int>>` | no |
| `MaxCollinear.h` | `vpi` = `vector<pair<int,int>>` | no |

Los dos últimos trabajan con coordenadas **`int`** y son independientes del resto de la librería.

## Tres choques de nombres, todos verificados

Esta carpeta tiene los peores nombres de la librería. Ninguno rompe nada, pero hay que saberlo:

| nombre | con qué choca | resultado |
|---|---|---|
| `solve` en `ClosestPair.h` | `solve` en `MaxCollinear.h` | **conviven** (sobrecarga: `vP` vs `vpi`) |
| `solve` en los dos | tu `void solve()` de `templateHeavy.cpp` | **conviven** (la tuya no toma argumentos) |
| `getline` en `MaxCollinear.h` | `std::getline` | **conviven** (`getline(cin, s)` sigue funcionando) |

Los tres los compilé y corrí. Pero si pegás `ClosestPair.h` y dentro de tu `solve()` escribís `solve(v)`, mirá bien a quién estás llamando.

---

## `ClosestPair.h`

**Requiere:** `Point.h` · $O(n \log n)$

### `solve`

```cpp
pair<P,P> solve(vP v);
```

Los **dos puntos más cercanos** del conjunto.

- Complejidad: $O(n \log n)$ — barrido de línea con un `set` ordenado por $y$.
- Toma `v` por copia, porque lo ordena.
- Si hay **puntos repetidos** devuelve ese punto dos veces (distancia 0) y corta de entrada.
- **Precondición: al menos 2 puntos.**
- Devuelve el par, no la distancia: `abs(r.f - r.s)` te la da.
- Casos de uso:
  - El problema clásico *closest pair* (Kattis `closestpair2`).
  - Detectar si dos elementos están a menos de $d$ (comparar contra la distancia mínima).
  - Verificar que todos los puntos de una entrada son distintos, con la distancia en 0 como señal.
  - Cota inferior para problemas de "separar puntos" o empaquetado.

**Cómo funciona:** ordena por $x$ y barre de izquierda a derecha, manteniendo en un `set` ordenado por $y$ solo los puntos que están a menos de la mejor distancia actual en el eje $x$. Para cada punto nuevo, solo mira la franja de $\pm d$ en $y$ — que por geometría contiene un número constante de candidatos.

**Verificación:** 5.500 casos contra fuerza bruta $O(n^2)$, incluyendo configuraciones con muchos duplicados y colineales ($C=4$ con hasta 9 puntos), medias y dispersas ($C=10^5$ con hasta 120 puntos). 0 diferencias.

---

## `ManhattanMST.h`

**Independiente** (no requiere `Point.h`) · $O(n \log n)$

### `manhattanMst`

```cpp
V<pair<ll,pi>> manhattanMst(vpi v);
```

Dados $n$ puntos, devuelve **hasta $4n$ aristas** que están garantizadas a contener un árbol de expansión mínimo del grafo completo con peso

$$w(p,q) = |p_x - q_x| + |p_y - q_y|$$

Las aristas vienen como `{distancia, {índice_origen, índice_destino}}`.

- Complejidad: $O(n \log n)$.
- **No devuelve el MST: devuelve los candidatos.** Después hay que correr un MST cualquiera sobre ellas:

```cpp
auto ed = manhattanMst(v);
sort(all(ed));
DSU D; D.init(sz(v)); ll total = 0;
each(e, ed) if (D.unite(e.s.f, e.s.s)) total += e.f;
```

- Las distancias van en `ll`. Con coordenadas de $10^9$ un `int` desborda: las diferencias llegan a $2 \cdot 10^9$ y las sumas a $4 \cdot 10^9$.
- Toma `v` por copia, porque lo transforma internamente (hace cuatro rotaciones/reflexiones del plano).
- Casos de uso:
  - MST con distancia Manhattan, que es el caso de uso directo (Kattis `gridmst`).
  - Conectar puntos en una grilla donde solo se puede ir en horizontal y vertical: cableado, cañerías, calles.
  - Cualquier problema que diga "unir todos los puntos al mínimo costo" con costo $L_1$.
  - También sirve para **distancia Chebyshov** ($L_\infty$): rotando el plano 45° ($x' = x+y$, $y' = x-y$), $L_\infty$ se convierte en $L_1$.

**Por qué $4n$ aristas alcanzan:** para cada punto, en cada uno de los 8 octantes, solo el **vecino más cercano** puede formar parte de un MST. Las cuatro vueltas del bucle cubren los 8 octantes por simetría, y cada vuelta aporta a lo sumo una arista por punto.

**Verificación:** 6.300 casos comparando el peso del MST sacado de las $\le 4n$ aristas contra el MST del grafo **completo** $O(n^2)$, con $C$ de 3 a $10^9$. 0 diferencias. Fue la primera vez que este header se verificó: antes **no compilaba** (incluía una ruta muerta, `"DSU (7.6).h"`).

---

## `MaxCollinear.h`

**Independiente** (no requiere `Point.h`) · $O(n^2 \log n)$

### `getline`

```cpp
pair<pi,ll> getline(pi a, pi b);
```

La **clave canónica** de la recta que pasa por `a` y `b`: `{dirección normal normalizada, desplazamiento}`. Dos pares de puntos de la **misma recta** producen la misma clave, y pares de rectas distintas producen claves distintas.

- Complejidad: $O(\log \max |c|)$ — lo domina el `gcd`.
- **Precondición: `a != b`.** Un `assert` lo verifica: con dos puntos iguales la dirección es $(0,0)$, `gcd(0,0)` da 0 y se dividiría por cero.
- La normalización tiene dos pasos: dividir por el `gcd` (para que la dirección sea primitiva) y fijar el signo con `ckmin` (para que una dirección y su opuesta den la misma clave).
- El desplazamiento va en **`ll`**: con dirección y coordenadas de $10^5$ el producto llega a $10^{10}$ y un `int` desborda.
- Caso de uso: agrupar pares de puntos por recta. Es la función interna de `solve`, pero suelta sirve para cualquier problema de "contar rectas distintas" o "agrupar puntos colineales".

> El nombre choca con `std::getline`. **No lo rompe** — conviven por sobrecarga y `getline(cin, s)` sigue leyendo bien, lo verifiqué. Pero es un nombre desafortunado.

### `solve`

```cpp
int solve(vpi p);
```

La **máxima cantidad de puntos que caen sobre una misma recta**.

- Complejidad: $O(n^2 \log n)$. Son $\binom{n}{2}$ claves y un `map`.
- **Límite práctico: $n \approx 2000$.** Con $n = 2000$ son 2 millones de inserciones en un `map`; con $n = 10^5$ es inviable.
- **Precondición: no hay dos puntos iguales.** El `assert` de `getline` lo corta.
- Con un solo punto devuelve 1; con cero puntos devuelve 0.
- Casos de uso:
  - El problema clásico *max collinear points* (Kattis `maxcolinear`).
  - "¿Cuántos puntos puedo alinear?" / "¿con cuántas rectas cubro todos los puntos?" (cota inferior).
  - Detectar si todos los puntos son colineales: `solve(p) == sz(p)`.

**Cómo funciona:** cuenta, para cada recta, cuántos **pares** de puntos la determinan. Una recta con $k$ puntos aporta exactamente $\binom{k}{2}$ pares, así que al final invierte esa relación: busca el mayor $k$ con $\binom{k}{2} \le \text{máximo}$.

> **Un detalle de robustez que conviene conocer.** Aunque el desplazamiento ahora va en `ll`, el esquema sigue siendo "agrupar por clave": si dos rectas distintas produjeran la misma clave, el conteo saldría mal. Con `ll` eso requeriría coordenadas absurdamente grandes, y 6.000 casos aleatorios hasta $10^9$ no encontraron ninguna colisión. Pero si necesitás garantía total con $n$ grande, el enfoque alternativo —para cada punto, ordenar las direcciones a los demás y contar el grupo más largo— es igual de $O(n^2 \log n)$, maneja duplicados de forma natural y no depende de ninguna clave.

**Verificación:** 6.000 casos contra fuerza bruta exacta en `__int128`, con $C$ de 6 a $10^9$. 0 diferencias.

---

## Casos de uso recurrentes, de punta a punta

### Distancia mínima entre dos puntos del conjunto

```cpp
auto r = solve(v);                  // ClosestPair
db d = (db)abs(r.f - r.s);
```

### ¿Hay puntos repetidos?

```cpp
auto r = solve(v);
bool repetidos = sgn(abs(r.f - r.s)) == 0;
```

### MST con distancia Manhattan

```cpp
auto ed = manhattanMst(v);
sort(all(ed));
DSU D; D.init(sz(v)); ll total = 0; int usadas = 0;
each(e, ed) if (D.unite(e.s.f, e.s.s)) { total += e.f; ++usadas; }
// usadas == sz(v)-1 si el grafo quedo conexo
```

### MST con distancia Chebyshov ($L_\infty$)

```cpp
vpi w; each(p, v) w.pb({p.f + p.s, p.f - p.s});   // rota 45 grados
auto ed = manhattanMst(w);                        // L_inf pasa a ser L_1
// cada peso resultante es el DOBLE de la distancia Chebyshov
```

### ¿Están todos los puntos alineados?

```cpp
bool todos = (solve(p) == sz(p));   // MaxCollinear, sin puntos repetidos
```

### Cuántas rectas distintas determinan los puntos

```cpp
set<pair<pi,ll>> rectas;
F0R(i, sz(p)) FOR(j, i+1, sz(p)) rectas.ins(getline(p[i], p[j]));
int cuantas = sz(rectas);
```

---

## Verificación

| rutina | casos | contra |
|---|---|---|
| `manhattanMst` | 6.300 | MST del grafo completo $O(n^2)$, $C$ hasta $10^9$ |
| `getline`, `solve` (MaxCollinear) | 6.000 | fuerza bruta en `__int128`, $C$ hasta $10^9$ |
| `solve` (ClosestPair) | 5.500 | fuerza bruta $O(n^2)$, con duplicados y colineales |

Los tres headers compilan con las flags del `Makefile` sin warnings.

`ManhattanMST.h` **no compilaba** antes del commit `57c7c7f` (incluía `"DSU (7.6).h"`, una ruta que no existe en este repo), y `MaxCollinear.h` **crasheaba** con puntos duplicados y desbordaba su clave con coordenadas de $10^5$.
