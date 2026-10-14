# SparseSegmentTree

Segment tree sobre un universo **demasiado grande para alocar**, hasta 10¹⁸. Los nodos se crean solo cuando un `set` los toca, así que la memoria sigue a la cantidad de consultas y no a `n`.

`n` y los índices son `long long` — eso es todo el punto: un árbol denso necesitaría `2n` nodos.

Convenciones, contrato del `Node`, el pool y el monoide de ejemplo: [README.md](README.md).

## Antes de usarlo: probablemente no lo necesitás

Si las coordenadas que vas a tocar son a lo sumo `q`, **comprimirlas y usar [`SegmentTree`](SegmentTree.md) es mejor en todo**: más rápido y con menos memoria. El sparse sirve cuando no podés comprimir — típicamente porque las consultas llegan online y no conocés las coordenadas de antemano.

Medido a `n = 10¹⁸`, `q = 2·10⁵`: el sparse usa 8.7 millones de nodos y ~400 MB. El denso con coordenadas comprimidas resolvería lo mismo en 20 MB.

## API

```cpp
SparseSegmentTree<T> st(n, q)   // reserva el pool, los dos argumentos obligatorios
```

No hay `build`: el árbol **arranca vacío**, con todas las posiciones en `T()`.

| método | costo | qué hace |
|---|---|---|
| `st.set(p, x)` | O(log n) | `a[p] = x` |
| `st.get(p)` | O(log n) | la `T` en `p` |
| `st.prod(l, r)` | O(log n) | pliega `a[l..r]` |
| `st.all_prod()` | **O(1)** | pliega todo el universo |
| `st.size()` | O(1) | `n` |
| `st.max_right(l, r, f)` | O(log n) | mayor `p` con `f(prod(l, p))`, o `l - 1` |
| `st.min_left(l, r, f)` | O(log n) | menor `p` con `f(prod(p, r))`, o `r + 1` |
| `st.nodes_used()` | O(1) | cuánto del pool se consumió |
| `st.dump()` | O(n) | vuelca el universo entero, para depurar |

A diferencia de los persistentes, acá **no hay raíces explícitas**: el `set` muta en el lugar. Un camino que ya existe no cuesta nodos nuevos.

## Las posiciones intactas valen `T()`

Nunca materializadas, las posiciones no tocadas se comportan como `T()`. Para un monoide basado en sumas eso sale gratis: un cero no cambia ni una suma ni el mejor subarreglo, así que dejarlas afuera del árbol da la misma respuesta que guardarlas.

Pero si tu `T()` no es el valor por defecto que tu problema quiere, el sparse **no tiene** cómo expresarlo: no hay un `fill` inicial que no cueste O(n) nodos. Esa es la limitación real de la estructura.

## Memoria

```
max_nodes(n, q) = (ceil(log2 n) + 1) * q + 1
```

Asume que cada consulta es un `set`, que materializa un nodo por nivel. Es pesimista **dos veces**: un `set` que recorre un camino que ya existe no cuesta nada, y los nodos cerca de la raíz los comparten todos los caminos.

Medido con un `T` de 40 bytes (48 por nodo interno):

| n | q | nodos usados | estructura | pico | `q` sets | `q` prods |
|---|---|---|---|---|---|---|
| 200 000 | 200 000 | 314 240 | 14.4 MB | 23.6 MB | 0.096 s | 0.157 s |
| 1 000 000 | 1 000 000 | 1 561 880 | 71.5 MB | 99.0 MB | 0.990 s | 2.104 s |
| 10⁹ | 200 000 | 2 684 739 | 122.9 MB | 132.1 MB | 0.220 s | 0.376 s |
| **10¹⁸** | 200 000 | 8 668 775 | 396.8 MB | 406.0 MB | 0.518 s | 0.458 s |
| 10¹⁸ | 10⁶ | 41 026 645 | 1878.1 MB | 1905.6 MB | 3.196 s | 4.208 s |

A 256 MB el techo es `q ≈ 1.3·10⁵` con `n = 10¹⁸` (unos 43 nodos por `set`). Fijate cómo el costo por `set` crece con `log n`: 43 nodos a 10¹⁸ contra 21 a 2·10⁵.

## El detalle del punto medio

El cálculo del medio es `mx = lx + (rx - lx) / 2`, **no** `(lx + rx) / 2`. Con `n` cerca de 2⁶³ la segunda forma desborda. Es la clase de error que no aparece en los tests chicos y revienta exactamente en el caso para el que existe la estructura.

## Ejemplo

Máxima suma de un subarreglo de `a[l..r]` con coordenadas hasta 10¹⁸ (el `Node` está en el [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido)):

```cpp
const ll N = 1000000000000000000LL;
int q; cin >> q;
SparseSegmentTree<Node> st(N, q);
while (q--) {
    int type; cin >> type;
    if (type == 1) { ll p, x; cin >> p >> x; st.set(p, Node(x)); }
    else { ll l, r; cin >> l >> r; cout << st.prod(l, r).best << "\n"; }
}
```

## Alternativa: usar el persistente como sparse

`PersistentSegmentTree` también materializa solo los caminos que toca, así que con `long long` en los índices haría de sparse. Lo contrasté y **no conviene**: el persistente clona en cada `set` en vez de mutar en el lugar, así que gasta muchos más nodos para el mismo trabajo. Dos templates separados es la decisión correcta, y la API de cada uno queda más intuitiva (uno con raíces explícitas, el otro sin).

# Los dos descensos

$$
\texttt{max\_right}(\dots,l,r,f) \;=\; \max\{\, p \in [l,r] \;:\; f(\text{prod}(l,p)) \,\}, \qquad l-1 \text{ si es vacío}
$$

$$
\texttt{min\_left}(\dots,l,r,f) \;=\; \min\{\, p \in [l,r] \;:\; f(\text{prod}(p,r)) \,\}, \qquad r+1 \text{ si es vacío}
$$

`max_right` ancla en $l$ y acumula **prefijos**; `min_left` ancla en $r$ y acumula **sufijos**. Los centinelas, el requisito de monotonía de $f$ y la tabla de predicados están en el [README](README.md#los-dos-descensos) y desarrollados con ejemplos en [SegmentTree.md](SegmentTree.md#los-dos-descensos).

**El centinela, en corto:** si $f$ falla ya en el primer elemento, `max_right` devuelve $l-1$ y `min_left` devuelve $r+1$. Los dos **pueden ser índices válidos**, así que el chequeo es `p == l - 1`, nunca `p < 0`. Y el largo del tramo sale sin ramas: $p-l+1$ y $r-p+1$.

## Lo que hay que entender acá: las posiciones intactas son la identidad

El descenso cuesta $O(\log n)$ con $n$ el **universo**, no la cantidad de posiciones usadas. Con $n = 10^{18}$ son ~60 niveles, el triple que un denso de $10^6$.

Y lo más importante: una posición que nunca se puso vale `T()`, que es el **rango vacío**, no «un elemento con valor cero». Como `acc + T() == acc`, extender el prefijo sobre una zona intacta **no mueve el agregado**, así que el predicado es constante entre dos posiciones materializadas consecutivas. El descenso respeta eso y **no materializa nada**: es `const` y cuesta 0 del pool.

```cpp
const ll N = 1000000000000000000LL;
SparseSegmentTree<Cnt> t(N, 20);
for (ll q : {5LL, 7LL, 1000000LL, 500000000000LL, 999999999999999998LL}) t.set(q, Cnt(1));
// nodes_used = 185  de 1221 reservados
```

$k$-ésimo uno sobre **todo** $[0,\ 10^{18})$:

| $k$ | `max_right` | el $k$-ésimo uno está en |
|---|---|---|
| 1 | 4 | 5 |
| 2 | 6 | 7 |
| 3 | 999 999 | 1 000 000 |
| 4 | 499 999 999 999 | 500 000 000 000 |
| 5 | 999 999 999 999 999 997 | 999 999 999 999 999 998 |
| 6 | 999 999 999 999 999 999 $= r$ | no hay tantos |

```
primer uno en [8, 1e18):   max_right(8, N-1, sum < 1) + 1 = 1000000
ultimo uno en [0, 1e9]:    min_left (0, 1e9, sum < 1) - 1 = 1000000
```

Y el caso que conviene tener claro:

```
en un rango SIN nada puesto, [100, 200]:  max_right = 200 = r
```

o sea «aguantó todo el rango», porque no hay ningún elemento ahí que pueda romper el predicado. **Eso no es un bug, es la semántica**: el sparse modela un arreglo donde lo no puesto está *ausente*, no en cero. Si tu problema necesita que las posiciones intactas valgan cero *de verdad* y que cuenten como elementos, el sparse sin lazy no te lo da — usá [`SparseLazySegmentTree`](SparseLazySegmentTree.md) con un `apply` que materialice el largo, o comprimí coordenadas y usá el denso.

## `dump()`: ver el estado para depurar

Devuelve el arreglo lógico completo como un `vector`, con tres propiedades que valen en los seis templates de la familia:

$$
\texttt{dump()}[i] = \texttt{get}(i), \qquad
\textstyle\bigoplus \texttt{dump()} = \texttt{all\_prod()}, \qquad
\textstyle\bigoplus_{i=l}^{r} \texttt{dump()}[i] = \texttt{prod}(l,r)
$$

Devuelve **`n` elementos, no `SZ`**: el relleno $[n, SZ)$ no es parte del arreglo lógico. (Con el constructor de un argumento `t(k)` resulta $n = SZ$, así que ahí el relleno *sí* aparece — porque en ese caso es el arreglo.)

Es el mismo nombre y el mismo contrato que [`ImplicitTreap::dump()`](../ImplicitTreap.md).

Dos cosas propias del sparse.

**Las posiciones sin materializar vuelven como `T()`**, que es el **rango vacío** y no «un elemento que vale cero». Es lo mismo que devuelve `get` en esas posiciones, y es coherente con [cómo el sparse modela el arreglo](#las-posiciones-intactas-valen-t). No materializa nada: `nodes_used()` no cambia.

**Hay un tope.** `n` puede valer $10^{18}$ y volcarlo entero no entra en memoria, así que

```cpp
static const long long DUMP_MAX = 10000000;
assert(n <= DUMP_MAX);
```

El assert hace que falle fuerte y temprano en vez de que el sistema mate el proceso. Si necesitás inspeccionar una ventana de un universo gigante, `dump(l, r)` es un agregado de dos líneas sobre el mismo recorrido.

## Verificación

- Contra Kadane de fuerza bruta: **107 100 rangos** sobre `n = 1..34`, junto con `SegmentTree` y `PersistentSegmentTree` usando el mismo `Node`.
- A `n = 10¹⁸`: **20 000 sets y 400 consultas de rango** contrastadas contra un `map`, con 933 284 nodos usados. Cero errores.

Ese segundo test es el que importa: verifica la aritmética de índices en el rango donde el `(lx + rx) / 2` desbordaría.

**Sin link de juez todavía.**

### Los descensos

| test | comprobaciones |
|---|---|
| el descenso contra `SegmentTree`, con posiciones sin materializar | 29 994 consultas |
| el descenso a $n = 10^{18}$ contra un `map` | 500 consultas |

Cuatro controles negativos, los cuatro cazados por la suite: invertir el orden de `+` en `min_left`, podar sin chequear si el predicado rompe, no componer el lazy que baja, y pasarle a `apply` un largo fijo en vez del largo del nodo. El primero **solo** lo detecta un `Node` no conmutativo — con sumas pasa inadvertido, y de hecho mi primera versión del test no lo cazaba.

### `dump()`

| test | comprobaciones |
|---|---|
| `dump()` con 80 925 huecos devueltos como `T()`, pool intacto | 907 098 |

Diez controles negativos sobre los seis, los diez cazados por la suite: dar vuelta el vector, devolver `SZ` en vez de `n`, sacar el `push` de `LazySegmentTree`, invertirle el orden, visitar los hijos al revés, invertir la composición del lazy que baja, no aplicar el lazy en la hoja, y pasarle a `apply` un largo distinto de 1.
