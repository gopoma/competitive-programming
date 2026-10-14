# PersistentSegmentTree

Segment tree persistente: **cada `set` devuelve la raíz de una versión NUEVA** y deja la vieja intacta. Las raíces son tuyas: podés leer o ramificar desde cualquiera en cualquier momento.

Una raíz es simplemente un `int`.

Convenciones, contrato del `Node`, el pool y el monoide de ejemplo: [README.md](README.md).

## API

Todas las operaciones toman la raíz de forma **explícita**. No hay estado implícito de "versión actual": vos manejás el historial.

```cpp
PersistentSegmentTree<T> st(n, q)        // reserva el pool, los dos argumentos obligatorios
vector<int> roots = {st.build(a)};       // el patron de uso
```

| método | costo | nodos nuevos | qué hace |
|---|---|---|---|
| `st.build(a)` | O(n) | `2n − 1` | raíz de la versión inicial |
| `st.build()` | **O(1)** | **0** | raíz de la versión todo-`T()` |
| `st.set(root, p, x)` | O(log n) | `C + 1` | raíz nueva; la vieja sigue válida |
| `st.copy(root)` | **O(1)** | **1** | duplica una versión |
| `st.get(root, p)` | O(log n) | 0 | la `T` en `p` de esa versión |
| `st.prod(root, l, r)` | O(log n) | 0 | pliega `a[l..r]` de esa versión |
| `st.all_prod(root)` | **O(1)** | 0 | pliega todo de esa versión |
| `st.max_right(root, l, r, f)` | O(log n) | **0** | mayor `p` con `f(prod(l, p))`, o `l - 1` |
| `st.min_left(root, l, r, f)` | O(log n) | **0** | menor `p` con `f(prod(p, r))`, o `r + 1` |
| `st.nodes_used()` | O(1) | — | cuánto del pool se consumió |
| `st.dump(root)` | O(n) | **0** | vuelca esa versión entera, para depurar |
| `st.descend2(rA, rB, f)` | O(log n) | **0** | baja por **dos** versiones a la vez |

con `C = ceil(log2 n)`. **Las consultas no crean nodos**, solo `set`, `build` y `copy`.

## Por qué `build()` sin argumentos es gratis

El **nodo 0 es el nodo nulo**: representa un subárbol enteramente `T()`. `build()` devuelve `0` y no aloca nada, y un `set` desde ahí materializa solo el camino que toca.

Eso tiene una consecuencia que conviene tener presente: si tu problema necesita *ceros de verdad* y `T()` no es tu cero, arrancá de `build(vector<T>(n, T(0)))`, no de `build()`.

## Memoria

```
max_nodes(n, q) = 2n + (ceil(log2 n) + 1) * q + 1
```

Pesimista: asume que **cada** consulta es un `set`, que es lo más caro, y cubre **un** `build`. Si vas a hacer más de un `build`, sumalos aparte.

Medido con un `T` de 40 bytes (el `Node` de 5 campos del ejemplo), o sea 48 bytes por nodo interno:

| n | q | nodos usados | estructura | pico | build | `q` sets | `q` prods |
|---|---|---|---|---|---|---|---|
| 200 000 | 200 000 | 4 137 847 | 189.4 MB | 208.1 MB | 0.006 s | 0.228 s | 0.362 s |
| 1 000 000 | 1 000 000 | 22 951 213 | 1050.6 MB | 1121.0 MB | 0.050 s | 1.836 s | 3.443 s |

**El cuello de botella es la memoria, nunca el tiempo.** A 256 MB el techo práctico es `q ≈ 2.7·10⁵` con `n = 2·10⁵` (unos 21 nodos por `set`). Con un `T` de 8 bytes el techo sube proporcionalmente.

## Ejemplo

Una lista de arreglos con máxima suma de subarreglo por rango: set en un punto del arreglo `k`, consulta sobre el arreglo `k`, y clonar el arreglo `k` (el `Node` está en el [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido)):

```cpp
int n, q; cin >> n >> q;
vector<Node> a(n);
for (Node& x : a) { ll t; cin >> t; x = Node(t); }
PersistentSegmentTree<Node> st(n, q);
vector<int> roots = {st.build(a)};
while (q--) {
    int type, k; cin >> type >> k; k--;
    if (type == 1) { int p; ll x; cin >> p >> x; p--;
                     roots[k] = st.set(roots[k], p, Node(x)); }
    else if (type == 2) { int l, r; cin >> l >> r; l--, r--;
                          cout << st.prod(roots[k], l, r).best << "\n"; }
    else roots.push_back(st.copy(roots[k]));
}
```

Fijate que `roots[k] = st.set(roots[k], ...)` **reemplaza** la versión `k` en tu vector, mientras que `roots.push_back(st.copy(...))` **agrega** una. Esa diferencia es todo el control de historial que necesitás: el template no decide nada por vos.

## Por qué `reserve` y no `assign` con un contador

La alternativa habitual es predimensionar el arreglo de nodos y llevar un `timer` que avanza con cada creación. Medí las dos:

- **Tiempo**: inconsistente, 1.17×/1.39×/0.78× según la corrida. No hay ganador.
- **Memoria**: `reserve` usa **41–42% menos**, porque solo las páginas tocadas entran en el working set.

La ganancia del `reserve` es memoria, no velocidad — y en esta estructura la memoria es justo el recurso escaso.

## Si `p` se va de rango

El assert lo caza. Un `set` con `p = 10⁸` sobre un árbol construido con `n = 2` dispara `assert(0 <= p && p < n)` antes de tocar nada. Esta estructura **no** es sparse: `n` es un `int` y el pool se dimensionó para él. Si necesitás coordenadas gigantes, es [`SparseSegmentTree`](SparseSegmentTree.md).

# Los dos descensos

$$
\texttt{max\_right}(\dots,l,r,f) \;=\; \max\{\, p \in [l,r] \;:\; f(\text{prod}(l,p)) \,\}, \qquad l-1 \text{ si es vacío}
$$

$$
\texttt{min\_left}(\dots,l,r,f) \;=\; \min\{\, p \in [l,r] \;:\; f(\text{prod}(p,r)) \,\}, \qquad r+1 \text{ si es vacío}
$$

`max_right` ancla en $l$ y acumula **prefijos**; `min_left` ancla en $r$ y acumula **sufijos**. Los centinelas, el requisito de monotonía de $f$ y la tabla de predicados están en el [README](README.md#los-dos-descensos) y desarrollados con ejemplos en [SegmentTree.md](SegmentTree.md#los-dos-descensos).

**El centinela, en corto:** si $f$ falla ya en el primer elemento, `max_right` devuelve $l-1$ y `min_left` devuelve $r+1$. Los dos **pueden ser índices válidos**, así que el chequeo es `p == l - 1`, nunca `p < 0`. Y el largo del tramo sale sin ramas: $p-l+1$ y $r-p+1$.

## El root entra por parámetro: podés descender sobre cualquier versión

Es la diferencia con el denso. `max_right(root, l, r, f)` toma la raíz de la versión que quieras, incluso una vieja, y **no crea nodos**: el descenso es `const` y cuesta 0 del pool.

```cpp
vector<ll> a{1, 0, 1, 1, 0, 1, 0, 0};
vector<Cnt> iv(8);
for (int i = 0; i < 8; i++) iv[i] = Cnt(a[i]);
PersistentSegmentTree<Cnt> t(8, 10);
int v0 = t.build(iv);
int v1 = t.set(v0, 1, Cnt(1));           // a[1] = 1  ->  {1,1,1,1,0,1,0,0}
int v2 = t.set(v1, 5, Cnt(0));           // a[5] = 0  ->  {1,1,1,1,0,0,0,0}

// k-esimo uno, en la version que quieras
auto f = [&](const Cnt& x) { return x.sum < k; };
int p = t.max_right(v, 0, 7, f);
int ans = (p == 7 ? -1 : p + 1);
```

| $k$ | en `v0` | en `v1` | en `v2` |
|---|---|---|---|
| 1 | 0 | 0 | 0 |
| 2 | 2 | 1 | 1 |
| 3 | 3 | 2 | 2 |
| 4 | 5 | 3 | 3 |

Y sobre un subrango de una versión vieja:

```
max_right(v0, 2, 6, sum <= 2) = 4        min_left(v0, 2, 6, sum <= 2) = 3
nodes_used antes = 23,  despues = 23     <- el descenso no consumio pool
```

## `descend2`: bajar por dos versiones a la vez

El uso estrella del persistente es el **$k$-ésimo menor de un rango**, y no sale con `max_right`: ese toma una sola raíz, y acá el conteo del rango se obtiene **restando** dos prefijos.

La idea: construir $N+1$ versiones de un contador sobre el dominio de **valores** (comprimidos a $[0, m)$), donde `ver[i]` cuenta cuántas veces aparece cada valor en $a_0 \dots a_{i-1}$. Entonces

$$
\#\{\, j \in [l, r) : a_j = v \,\} \;=\; 	exttt{ver}[r][v] - 	exttt{ver}[l][v]
$$

y lo mismo vale para **cualquier subárbol**, no solo para una hoja. Por eso se puede bajar: en cada nodo, la cantidad de elementos del rango que caen en el hijo izquierdo es la resta de ese hijo en las dos versiones.

```cpp
template<class F>
int descend2(int rtA, int rtB, F izq) const;
```

`izq(a, b)` recibe los agregados del hijo **izquierdo** de las dos versiones y devuelve si hay que bajar por ahí. Puede llevar estado. **La resta corre por cuenta de `izq`**, así que el monoide no necesita inverso y el contrato de `+` se queda como está.

El $k$-ésimo menor queda en seis líneas:

```cpp
int falta = k + 1;                              // k viene 0-indexado
int pos = st.descend2(ver[l], ver[r], [&](const Cnt& iz_l, const Cnt& iz_r) {
    int c = iz_r.cnt - iz_l.cnt;                // cuantos de a[l..r-1] caen a la izquierda
    if(falta <= c) return true;
    falta -= c;                                 // no alcanzan: los descarto y voy a la derecha
    return false;
});
cout << vals[pos] << "
";                      // pos es un indice de valor comprimido
```

Es $O(\log n)$, `const`, y **no consume pool**: una consulta de lectura no te come nodos, verificado comparando `nodes_used()` antes y después.

La solución completa está en `LC_RangeKthSmallest.cpp`, en la raíz del repo.

### Lo que no cubre

`descend2` baja hasta una **hoja**, así que sirve para «¿qué valor?» y no para «¿cuántos?». Para contar cuántos elementos de $a_l \dots a_{r-1}$ caen en $[x, y]$ hace falta un recorrido distinto —dos `prod` restados— que con este monoide se escribe afuera: `st.prod(ver[r], x, y).cnt - st.prod(ver[l], x, y).cnt`.

Tampoco está en `PersistentLazySegmentTree`: con lazy habría que arrastrar **dos** carries y no hay un caso de uso canónico que lo justifique. Si aparece, es la misma idea con dos `LazyUpdate` más en la firma.

## `dump()`: ver el estado para depurar

Devuelve el arreglo lógico completo como un `vector`, con tres propiedades que valen en los seis templates de la familia:

$$
\texttt{dump()}[i] = \texttt{get}(i), \qquad
\textstyle\bigoplus \texttt{dump()} = \texttt{all\_prod()}, \qquad
\textstyle\bigoplus_{i=l}^{r} \texttt{dump()}[i] = \texttt{prod}(l,r)
$$

Devuelve **`n` elementos, no `SZ`**: el relleno $[n, SZ)$ no es parte del arreglo lógico. (Con el constructor de un argumento `t(k)` resulta $n = SZ$, así que ahí el relleno *sí* aparece — porque en ese caso es el arreglo.)

Es el mismo nombre y el mismo contrato que [`ImplicitTreap::dump()`](../ImplicitTreap.md).

La diferencia con el denso: **el root entra por parámetro**, así que podés volcar cualquier versión, incluso una vieja. Y **no consume nodos del pool** — es `const` y está verificado comparando `nodes_used()` antes y después.

Es la forma natural de contestar *«¿cómo se veía la versión 3?»*:

```cpp
for (int ver = 0; ver < (int)roots.size(); ver++) {
    cerr << "v" << ver << ":";
    for (const Node& x : st.dump(roots[ver])) cerr << " " << x.sum;
    cerr << "\n";
}
```

Un subárbol sin materializar no necesita caso aparte: `st[0]` es el nodo nulo, sus hijos son `0` y su `val` ya es `T()`, así que la recursión baja por ceros y emite `T()` en cada hoja — exactamente lo que devuelve `get`.

## Verificación

- Contra Kadane de fuerza bruta: **107 100 rangos** sobre `n = 1..34`, junto con `SegmentTree` y `SparseSegmentTree` usando el mismo `Node`.
- **212 940 rangos** leídos desde **todas** las versiones del historial, ramificando desde raíces arbitrarias (no solo desde la última).

Ese segundo test es el que importa acá: una implementación que comparte nodos mal puede dar bien sobre la versión actual y mal sobre las viejas.

**Sin link de juez todavía.** Hay una solución escrita para CSES *Range Queries and Copies* usando este template, verificada localmente pero no enviada.

### Los descensos

| test | comprobaciones |
|---|---|
| el descenso sobre **todas** las versiones, ramificando | 18 126 consultas |

Cuatro controles negativos, los cuatro cazados por la suite: invertir el orden de `+` en `min_left`, podar sin chequear si el predicado rompe, no componer el lazy que baja, y pasarle a `apply` un largo fijo en vez del largo del nodo. El primero **solo** lo detecta un `Node` no conmutativo — con sumas pasa inadvertido, y de hecho mi primera versión del test no lo cazaba.

### `dump()`

| test | comprobaciones |
|---|---|
| `dump(root)` sobre **30 000 versiones vivas**, pool intacto | 1 177 780 |

Diez controles negativos sobre los seis, los diez cazados por la suite: dar vuelta el vector, devolver `SZ` en vez de `n`, sacar el `push` de `LazySegmentTree`, invertirle el orden, visitar los hijos al revés, invertir la composición del lazy que baja, no aplicar el lazy en la hoja, y pasarle a `apply` un largo distinto de 1.

### `descend2` y el k-ésimo menor

| test | comprobaciones |
|---|---|
| **todos** los $(l, r, k)$ sobre $n \le 12$, contra ordenar e indexar | 3 378 856 |
| el sample de Library Checker *Range Kth Smallest* | exacto |

Cuatro controles negativos, los cuatro cazados: pasarle a `izq` los hijos **derechos**, bajar por la rama opuesta a la que `izq` eligió, partir mal el rango (`rx = mx + 1`), e ignorar una de las dos versiones. Y `nodes_used()` no cambia en ninguna consulta.

Tiempos con $N = Q = 2 \cdot 10^5$ (límite 5 s), 50 MB de pico y pool al 89 % de lo reservado:

| entrada | tiempo |
|---|---|
| valores todos distintos | 0.731 s |
| muchos repetidos ($m = 10$) | 0.254 s |
| ordenado, rangos completos | 0.310 s |
