# Primitives

La base de toda la librería de geometría. Todo lo demás (`Circles`, `Polygons`, `Misc`) se apoya en `Point.h`.

## Índice

- [Cómo se arma la submission](#cómo-se-arma-la-submission)
- [El contrato de tipos (`Point.h`)](#el-contrato-de-tipos-pointh)
  - [Elegir `T`: `db` o `ll`](#elegir-t-db-o-ll)
  - [Cuánto aguanta `db`](#cuánto-aguanta-db)
- [`Point.h`](#pointh)
  - [Operadores](#operadores)
  - [`sgn`](#sgn)
  - [`sq`](#sq)
  - [`abs2` y `abs`](#abs2-y-abs)
  - [`arg`](#arg)
  - [`conj`](#conj)
  - [`perp`](#perp)
  - [`dir`](#dir)
  - [`unit`](#unit)
  - [`dot` (dos formas)](#dot-dos-formas)
  - [`cross` (dos formas), la función más importante](#cross-dos-formas-la-función-más-importante)
  - [`reflect`](#reflect)
  - [`foot`](#foot)
  - [`onSeg`](#onseg)
- [`AngleCmp.h`](#anglecmph)
  - [`half`](#half)
  - [`angleCmp`](#anglecmp)
- [`SegDist.h`](#segdisth)
  - [`lineDist`](#linedist)
  - [`segDist`](#segdist)
- [`SegIsect.h`](#segisecth)
  - [`lineIsect`](#lineisect)
  - [`strictIsect`](#strictisect)
  - [`segIsect`](#segisect)
- [Casos de uso recurrentes, de punta a punta](#casos-de-uso-recurrentes-de-punta-a-punta)
  - [¿De qué lado de la recta cae el punto?](#de-qué-lado-de-la-recta-cae-el-punto)
  - [Área de un triángulo](#área-de-un-triángulo)
  - [¿Están alineados?](#están-alineados)
  - [Ángulo orientado en un vértice](#ángulo-orientado-en-un-vértice)
  - [Rotar un punto alrededor de otro](#rotar-un-punto-alrededor-de-otro)
  - [Ordenar puntos alrededor de un centro](#ordenar-puntos-alrededor-de-un-centro)
  - [El punto más cercano de un segmento](#el-punto-más-cercano-de-un-segmento)
  - [Distancia entre dos segmentos](#distancia-entre-dos-segmentos)
- [Verificación](#verificación)

## Cómo se arma la submission

El flujo es: copiás `templateHeavy.cpp` en `E.cpp` y pegás el **código** de los headers que necesites dentro de la sección de template.

> **Los `#include` no van en la solución.** Ningún header de esta librería tiene `#include`, y vos tampoco escribís ninguno. El campo `Requiere:` del encabezado es solo un **indicador**: te dice qué otros templates hay que pegar también, y en qué orden.

| si pegás | pegá antes |
|---|---|
| `Point.h` | — es la base |
| `AngleCmp.h` | `Point.h` |
| `SegDist.h` | `Point.h` |
| `SegIsect.h` | `Point.h` |

En la sección de template queda el código, uno abajo del otro:

```cpp
//* Template
// ---------- Point.h ----------        <- primero, siempre
using T = db;
const T EPS = 1e-9;
using P = pair<T,T>; using vP = V<P>; using Line = pair<P,P>;
int sgn(T a) { return (a>EPS)-(a<-EPS); }
// ... el resto de Point.h

// ---------- SegIsect.h ----------     <- despues, en cualquier orden
vP lineIsect(const Line& a, const Line& b) { /* ... */ }
// ... el resto de SegIsect.h
//* /Template
```

`Point.h` va **una sola vez**: pegarlo dos veces da errores de redefinición.

---

## El contrato de tipos (`Point.h`)

```cpp
using T = db;                   // el escalar. db = long double, o ll
const T EPS = 1e-9;
using P = pair<T,T>;            // un punto, o un vector
using vP = V<P>;
using Line = pair<P,P>;         // dos puntos: una recta, o un segmento
```

`P` es a la vez **punto** y **vector**: no hay distinción de tipos. `Line` es a la vez **recta infinita** y **segmento** — cuál de las dos depende de la función que lo recibe, y está dicho en cada caso.

### Elegir `T`: `db` o `ll`

Un solo `T` cubre dos necesidades que quieren tipos distintos:

| | `T = db` (default) | `T = ll` |
|---|---|---|
| predicados (`sgn`, `cross`) | aproximados, con `EPS` | **exactos** |
| métrica (`abs`, `arg`, `unit`, `foot`) | correctos | **truncan en silencio** |

Con `T = ll`, `EPS = 1e-9` trunca a `0`, así que `sgn` se vuelve exacto — eso es deseable. Pero `abs({1,1})` devuelve `1` en lugar de $\sqrt{2}$, y `arg` devuelve `0` casi siempre.

**Regla práctica:** si el problema trae coordenadas enteras y solo necesitás orientación, área o comparar distancias, usá `T = ll` y evitá `abs`/`arg`/`unit`. Si necesitás distancias o ángulos reales, dejá `T = db`.

### Cuánto aguanta `db`

Medido con cross reales de magnitud $\le 4$ (el caso casi degenerado, que es el peor):

| `db` | $C = 10^6$ | $C = 10^8$ | $C = 10^9$ | $C = 10^{12}$ |
|---|---|---|---|---|
| `long double` (64 bits de mantisa) | exacto | exacto | **exacto** | 62% mal |
| `double` (53 bits) | exacto | 25% mal | **62% mal** | 62% mal |

`long double` tiene mantisa de 64 bits, así que un cross de enteros de hasta $\approx 9.2 \cdot 10^{18}$ es **exacto**. Con coordenadas de $10^9$ el producto llega a $4 \cdot 10^{18}$: entra.

> **No cambies `db` a `double`** si usás geometría. Tu `templateHeavy.cpp` dice *"or double if tight TL"*; con `double` los predicados se rompen desde coordenadas de $10^8$.

Los fallos son siempre del tipo "cross real colapsa a 0" (un caso degenerado se lee como colineal), nunca signo invertido.

---

## `Point.h`

### Operadores

```cpp
P operator+(P, P);   P operator-(P, P);
P operator*(P, T);   P operator*(T, P);   P operator/(P, T);
P operator*(P, P);   P operator/(P, P);
P& operator+=(P&, const P&);   P& operator-=(P&, const P&);
P& operator*=(P&, const T&);   P& operator/=(P&, const T&);
ostream& operator<<(ostream&, P);
```

Suma, resta y escalado son los de vectores. Los dos interesantes son los de `P` con `P`:

- **`a * b` es multiplicación de complejos**, no producto componente a componente. Si $a = (x_1,y_1)$ y $b = (x_2,y_2)$, entonces `a*b` $= (x_1x_2 - y_1y_2,\ x_1y_2 + x_2y_1)$. En módulo y argumento: $|ab| = |a||b|$ y $\arg(ab) = \arg a + \arg b$. O sea: **multiplicar rota y escala**.
- **`a / b` es división de complejos**: $\arg(a/b) = \arg a - \arg b$.

Casos de uso recurrentes:

```cpp
P q = p * dir(ang);              // rotar p un angulo ang alrededor del origen
P q = c + (p-c) * dir(ang);      // rotar p alrededor de c
P q = p * perp(P(1,0));          // rotar 90 grados (equivale a perp(p))
T ang = arg((a-c)/(b-c));        // el angulo orientado a-c-b, con signo
```

Ese último es el truco que hace que `reflect` y `foot` sean de una línea.

`operator<<` imprime `(x,y)`; sirve para depurar con `cout << p`.

### `sgn`

```cpp
int sgn(T a);
```

Devuelve `-1`, `0` o `1` según el signo de `a`, tratando como cero todo lo que esté a menos de `EPS`. **Es el único lugar donde `EPS` entra en la librería.**

- Complejidad: $O(1)$.
- Caso de uso: envolver todo cross o dot antes de comparar con cero. `sgn(cross(p,a,b)) > 0` en vez de `cross(p,a,b) > 0`.

> Con `T = ll` el `EPS` trunca a `0` y `sgn` queda exacto, que es lo que querés con enteros.

### `sq`

```cpp
T sq(T a);
```

$a^2$. Existe para no repetir `a*a`.

- Complejidad: $O(1)$.

### `abs2` y `abs`

```cpp
T abs2(P p);    // |p|^2
T abs(P p);     // |p|
```

`abs2` da el módulo **al cuadrado**; `abs` el módulo, con una raíz.

- Complejidad: $O(1)$ las dos.
- **Preferí `abs2` siempre que puedas.** Comparar $|a|^2 < |b|^2$ equivale a $|a| < |b|$, evita la raíz, y con enteros es **exacto**. Por eso `HullDiameter` devuelve el diámetro al cuadrado.
- Caso de uso: ordenar por distancia, buscar el punto más cercano o más lejano, comparar radios.

> Con `T = ll`, `abs` trunca: `abs({1,1})` da `1`.

### `arg`

```cpp
T arg(P p);
```

El ángulo de `p` respecto del eje $x$ positivo, vía `atan2`, en el rango $(-\pi, \pi]$.

- Complejidad: $O(1)$.
- Casos de uso: barridos angulares donde hace falta el ángulo en sí (no solo comparar), y medir ángulos con `arg((a-c)/(b-c))`.

> **Para ordenar por ángulo no uses `arg`: usá `angleCmp`.** Es más rápido y no pierde precisión. El header de `AngleCmp.h` lo avisa explícitamente.
>
> Con `T = ll` devuelve `0` casi siempre.

### `conj`

```cpp
P conj(P p);     // (x, -y)
```

El conjugado complejo: espeja respecto del eje $x$.

- Complejidad: $O(1)$.
- Caso de uso: casi siempre es interno (`operator/`, `reflect`, `ccCenter`). Suelto sirve para espejar sobre el eje $x$.

### `perp`

```cpp
P perp(P p);     // (-y, x)
```

Rota `p` 90° en sentido antihorario.

- Complejidad: $O(1)$.
- Casos de uso: obtener la **normal** de una recta o segmento; construir la dirección de un semiplano; `perp(l.f - l.s)` es el vector normal a la recta `l`.

### `dir`

```cpp
P dir(T ang);    // (cos ang, sin ang)
```

El vector unitario que apunta en la dirección `ang`.

- Complejidad: $O(1)$.
- Caso de uso: rotar. `p * dir(ang)` rota `p` un ángulo `ang`. También `dir(PI/2)` es la rotación de 90°, equivalente a `perp`.

### `unit`

```cpp
P unit(const P& p);
```

Normaliza: devuelve `p` con módulo 1 y la misma dirección.

- Complejidad: $O(1)$.
- **Precondición: `p` no es el origen** (si no, divide por cero).
- Caso de uso: moverse una distancia dada en una dirección: `a + unit(b-a)*d`.

### `dot` (dos formas)

```cpp
T dot(const P& a, const P& b);                   // a . b
T dot(const P& p, const P& a, const P& b);       // (a-p) . (b-p)
```

Producto escalar. La forma de tres argumentos lo mide **en el vértice `p`**.

- Complejidad: $O(1)$.
- El signo dice el ángulo: $>0$ agudo, $0$ perpendicular, $<0$ obtuso.
- Casos de uso:
  - Proyectar: la proyección de `a` sobre `b` tiene longitud `dot(a,b)/abs(b)`.
  - Decidir si un punto cae "antes" o "después" de un extremo de segmento — es exactamente lo que hace `segDist`.
  - Detectar perpendicularidad: `sgn(dot(a,b)) == 0`.

### `cross` (dos formas), la función más importante

```cpp
T cross(const P& a, const P& b);                 // a x b
T cross(const P& p, const P& a, const P& b);     // (a-p) x (b-p)
```

El producto vectorial en 2D: la componente $z$ del producto en 3D. Es un escalar.

- Complejidad: $O(1)$.
- **La forma de tres argumentos es el predicado de orientación**, y es la base de casi toda la geometría computacional:

| `sgn(cross(p,a,b))` | significado |
|---|---|
| `> 0` | `p → a → b` gira a la **izquierda** (antihorario) |
| `== 0` | los tres son **colineales** |
| `< 0` | gira a la **derecha** (horario) |

- $|cross(p,a,b)|$ es el **área del paralelogramo** `p,a,b`; la mitad es el área del triángulo.
- Casos de uso: convex hull, punto en polígono, intersección de segmentos, área, ordenar por ángulo, decidir de qué lado de una recta cae un punto. Prácticamente todo.

> La forma de tres argumentos **resta primero** y después multiplica. Eso es lo que la hace numéricamente robusta: los productos se calculan sobre las diferencias, que son chicas, no sobre las coordenadas absolutas.

### `reflect`

```cpp
P reflect(const P& p, const Line& l);
```

Espeja `p` respecto de la **recta infinita** que pasa por `l.f` y `l.s`.

- Complejidad: $O(1)$.
- **Precondición: `l.f != l.s`.**
- Casos de uso: problemas de espejos y rebotes (la trayectoria de una pelota que rebota en una pared se endereza reflejando); minimizar $|PA| + |PB|$ con $P$ sobre una recta (se refleja uno de los dos puntos y se une en línea recta).

### `foot`

```cpp
P foot(const P& p, const Line& l);
```

El pie de la perpendicular: la **proyección** de `p` sobre la recta infinita `l`. Es el punto de `l` más cercano a `p`.

- Complejidad: $O(1)$.
- **Precondición: `l.f != l.s`.**
- Casos de uso: distancia punto-recta (aunque para eso está `lineDist`); intersección círculo-recta (`isect(Circ,Line)` lo usa); proyectar puntos sobre una dirección.

### `onSeg`

```cpp
bool onSeg(const P& p, const Line& l);
```

Dice si `p` está sobre el **segmento** `l`, extremos incluidos.

- Complejidad: $O(1)$.
- Usa `sgn`, o sea **tolera `EPS`**: un punto a $10^{-12}$ del segmento cuenta como "sobre el segmento".
- Funciona también con `l` degenerado (los dos extremos iguales): ahí pregunta si `p` coincide con ese punto.
- Casos de uso: `segIsect` e `inPoly` lo usan para detectar el borde. Suelto sirve para "¿este punto está sobre alguna de estas paredes?".

---

## `AngleCmp.h`

**Requiere:** `Point.h`

### `half`

```cpp
int half(P x);
```

Clasifica `x` en tres grupos, que es el paso que hace posible ordenar por ángulo sin `atan2`:

| valor | qué cae ahí | rango de ángulo |
|---|---|---|
| `-1` | semiplano inferior y eje $x$ **positivo** | $(-\pi, 0]$ |
| `0` | el origen | — |
| `1` | semiplano superior y eje $x$ **negativo** | $(0, \pi]$ |

- Complejidad: $O(1)$.
- Cada grupo abarca un rango de exactamente $\pi$, y **dentro de un rango de $\pi$ el `cross` ordena correctamente por ángulo**. De ahí sale `angleCmp`.

> **No lo declares `bool` por error.** El header lo avisa: devuelve tres valores, y con `bool` el orden sale mal en silencio.

### `angleCmp`

```cpp
bool angleCmp(P a, P b);
```

Comparador que ordena puntos por ángulo en sentido antihorario alrededor del origen, con el **mismo orden que `atan2`**: el rango es $(-\pi, \pi]$, así que los puntos del eje $x$ negativo quedan **al final**.

```cpp
vP v; sort(all(v), angleCmp);
```

- Complejidad: $O(1)$ por comparación, $O(n \log n)$ el sort.
- Equivale a `sort(all(v), [](P a, P b){ return atan2(a.s,a.f) < atan2(b.s,b.f); })`, pero sin `atan2`.
- **Por qué no usar `atan2` directo:** es más lento y pierde precisión; el header dice *"no uses atan2, pasan cosas raras!"* con dos submissions de Codeforces como evidencia.
- Casos de uso: barrido angular (contar pares visibles, rotar una recta alrededor de un punto), ordenar vecinos alrededor de un vértice, intersección de semiplanos.

> El origen (`half == 0`) queda en un grupo aparte. Si tu entrada puede traer el punto $(0,0)$, saltealo antes de ordenar: no tiene ángulo definido.

---

## `SegDist.h`

**Requiere:** `Point.h`

### `lineDist`

```cpp
T lineDist(const P& p, const Line& l);
```

Distancia de `p` a la **recta infinita** que pasa por `l.f` y `l.s`.

- Complejidad: $O(1)$.
- **Precondición: `l.f != l.s`** (divide por `abs(l.f-l.s)`).
- Implementación: $|cross| / |AB|$, o sea el área del paralelogramo dividida por la base.
- Casos de uso: ancho de una franja; distancia de un punto a una recta de soporte; verificar tangencia (`sgn(lineDist(c, l) - r) == 0`).

### `segDist`

```cpp
T segDist(const P& p, const Line& l);
```

Distancia de `p` al **segmento** `l`, que no es lo mismo: si la proyección cae fuera del segmento, la distancia es al extremo más cercano.

- Complejidad: $O(1)$.
- Resuelve los tres casos con el signo de `dot`: proyección antes de `l.f`, después de `l.s`, o adentro.
- Funciona con `l` degenerado: devuelve la distancia al punto.
- Casos de uso: distancia entre un punto y una pared finita; distancia entre dos segmentos (es el mínimo de cuatro `segDist`, si no se cruzan); el radio mínimo de un círculo centrado en `p` que toca el segmento.

**Verificación:** 60.000 casos contra una fórmula independiente, con coordenadas hasta $10^9$. Peor error relativo: $4.3 \cdot 10^{-16}$.

---

## `SegIsect.h`

**Requiere:** `Point.h`

Tres funciones, de la más permisiva a la más completa. La que casi siempre querés es **`segIsect`**.

### `lineIsect`

```cpp
vP lineIsect(const Line& a, const Line& b);
```

Intersección de dos **rectas infinitas**. Devuelve:

| resultado | significado |
|---|---|
| 1 punto | se cortan ahí |
| 2 puntos (`{b.f, b.s}`) | son la **misma recta** |
| vacío | son **paralelas** y distintas |

- Complejidad: $O(1)$.
- Casos de uso: circuncentro a mano (intersección de dos mediatrices); centro de una homotecia; cerrar un polígono recortado por semiplanos.

> Usa `sgn` para decidir paralelismo, no `==`. Con rectas **casi** paralelas devuelve vacío, que es lo correcto; antes devolvía un punto basura en $-1.02 \cdot 10^{18}$.

### `strictIsect`

```cpp
vP strictIsect(const Line& a, const Line& b);
```

Devuelve el punto de corte solo si está en el **interior de los dos segmentos** — un cruce propio. Si se tocan en un extremo, o si son colineales, devuelve vacío.

- Complejidad: $O(1)$.
- Casos de uso: contar cruces propios en un conjunto de segmentos; detectar si un polígono es simple (ninguna pareja de lados no adyacentes se cruza propiamente).

### `segIsect`

```cpp
vP segIsect(const Line& a, const Line& b);
```

La intersección completa de dos **segmentos**, con extremos y solapamientos incluidos. Los segmentos pueden ser degenerados (un punto).

| resultado | significado |
|---|---|
| vacío | no se tocan |
| 1 punto | se cortan, o se tocan en un extremo |
| 2 puntos | son colineales y **se solapan** en un tramo; devuelve los dos extremos del tramo |

- Complejidad: $O(1)$ a efectos prácticos (usa un `set` de hasta 4 puntos).
- Casos de uso: lo que casi siempre pide un problema de "¿se cortan estos dos segmentos?"; unir tramos solapados; detectar si un camino poligonal se auto-intersecta.

**Verificación:** 140.000 casos contra una referencia de `cross` exacto en `ll`, con coordenadas de $2$ a $10^9$, incluyendo degeneración fuerte ($C=2$, $C=3$) y segmentos-punto. 0 diferencias.

---

## Casos de uso recurrentes, de punta a punta

### ¿De qué lado de la recta cae el punto?

```cpp
int lado = sgn(cross(a, b, p));   // >0 izquierda, 0 sobre la recta, <0 derecha
```

### Área de un triángulo

```cpp
T area2 = abs(cross(a, b, c));    // el DOBLE del area; con enteros queda exacta
```

Trabajar con el doble del área evita dividir y mantiene todo entero.

### ¿Están alineados?

```cpp
bool alineados = sgn(cross(a, b, c)) == 0;
```

### Ángulo orientado en un vértice

```cpp
T ang = arg((a - c) / (b - c));   // angulo a-c-b, con signo, en (-pi, pi]
```

### Rotar un punto alrededor de otro

```cpp
P rotado = c + (p - c) * dir(ang);
```

### Ordenar puntos alrededor de un centro

```cpp
each(p, v) p -= centro;
sort(all(v), angleCmp);
each(p, v) p += centro;
```

### El punto más cercano de un segmento

```cpp
P q = foot(p, l);
if (!onSeg(q, l)) q = (abs2(p - l.f) < abs2(p - l.s)) ? l.f : l.s;
```

### Distancia entre dos segmentos

```cpp
T d = sz(segIsect(a, b)) ? 0 : min({segDist(a.f, b), segDist(a.s, b),
                                    segDist(b.f, a), segDist(b.s, a)});
```

---

## Verificación

| rutina | casos | contra |
|---|---|---|
| `segIsect`, `strictIsect`, `onSeg` | 140.000 | `cross` exacto en `ll`, $C$ de 2 a $10^9$ |
| `segDist`, `lineDist` | 60.000 | fórmula independiente, error $\le 4.3 \cdot 10^{-16}$ |
| `sgn(cross(...))` | 38.000 | `__int128`, casos casi degenerados |
| `angleCmp` | — | orden monótono por `atan2` verificado |

Todos los headers compilan con las flags del `Makefile` (`-Wall -Wextra -Wconversion -Wshadow -Wfloat-equal -D_GLIBCXX_DEBUG`) sin warnings.
