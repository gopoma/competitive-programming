# SparseSegmentTree

Igual que [`SegmentTree`](SegmentTree.md) — monoide $(S, \cdot, e)$, `T()` es $e$ y `operator+` es
$\cdot$ — pero **los nodos se crean recién cuando se los toca**, así que el largo puede ser
$10^{18}$ sin comprimir coordenadas.

Dado un largo $n$ (que puede no entrar en un `int`), procesa en $O(\log n)$: asignar, calcular el
producto de un intervalo, y buscar un borde por descenso. Los índices son `long long`.

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos**: `assert(0 <= l && l <= r && r < n)`.
Catálogo de nodos en [README.md](README.md).

**Pool**: hay que declarar de antemano cuántas operaciones vas a hacer.

$$\texttt{max\_nodes}(n, q) = (\lceil \log_2 n \rceil + 1)\,q + 1$$

No hay costo de construcción: un árbol de $10^{18}$ recién instanciado tiene **un** nodo.

## Constructor

```cpp
SparseSegmentTree<T> st(long long len, long long max_ops);
```

Reserva el pool para un árbol de largo `len` y `max_ops` operaciones que creen nodos.

**Restricciones**: $len \ge 1$, $max\_ops \ge 0$. · **Complejidad**: $O(1)$ — solo reserva.

## max_nodes

```cpp
static long long SparseSegmentTree<T>::max_nodes(long long len, long long max_ops)
```

Devuelve cuántos nodos va a reservar el constructor con esos parámetros, para presupuestar memoria
antes de instanciar.

**Complejidad**: $O(1)$.

## set

```cpp
void st.set(long long pos, T val)
```

`a[pos] = val`, materializando el camino hasta `pos` si hacía falta.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$, y crea hasta
$\lceil \log_2 n \rceil + 1$ nodos.

## get

```cpp
T st.get(long long pos) const
```

Devuelve `a[pos]`, o `T()` si esa posición nunca se tocó.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## prod

```cpp
T st.prod(long long l, long long r) const
```

Devuelve `a[l] + ... + a[r]`.

**Restricciones**: $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
T st.all_prod() const
```

Devuelve `a[0] + ... + a[n-1]`.

**Complejidad**: $O(1)$.

## max_right

```cpp
template <class F> long long st.max_right(long long l, long long r, F pred) const
```

Devuelve el **mayor** $p \in [l, r]$ tal que `pred(prod(l, p))` es cierto, o `l - 1` si ninguno lo
cumple.

**Restricciones**: $0 \le l \le r < n$, `pred` monótono sobre el rango y sin efectos de lado. ·
**Complejidad**: $O(\log n)$.

## min_left

```cpp
template <class F> long long st.min_left(long long l, long long r, F pred) const
```

Devuelve el **menor** $p \in [l, r]$ tal que `pred(prod(p, r))` es cierto, o `r + 1` si ninguno lo
cumple.

**Restricciones**: las mismas, con `pred` monótono al **decrecer** $p$. ·
**Complejidad**: $O(\log n)$.

## dump

```cpp
vector<T> st.dump() const
```

Devuelve los `n` elementos en orden, incluyendo los que nunca se tocaron (que valen `T()`), para
depurar. Hace `assert(n <= DUMP_MAX)` con `DUMP_MAX = 10'000'000`, porque con el `n` real de un
sparse el vector no cabría.

**Complejidad**: $O(n)$.

## size / nodes_used

```cpp
long long st.size() const
long long st.nodes_used() const
```

El largo del árbol, y cuántos nodos del pool se materializaron — para depurar el presupuesto.

**Complejidad**: $O(1)$.

---

### Los centinelas

`l - 1` y `r + 1` están elegidos para que el largo del tramo salga **sin un `if`**:
`p - l + 1` y `r - p + 1`. Con el centinela los dos dan $0$, y como el rango es cerrado y no
vacío, el centinela nunca es un índice válido.

## Examples

### Suma de rango sobre coordenadas gigantes

Sin comprimir, sin ordenar las consultas, y sin saber de antemano qué índices van a aparecer:

```cpp
SparseSegmentTree<NodeSum> st(1'000'000'000'000'000'000LL, q);

st.set(123456789012345LL, NodeSum(7));
st.set(999999999999999LL, NodeSum(3));
cout << st.prod(0, 1'000'000'000'000'000LL).sum << "\n";   // 10
```

### Conteo de puntos en un rango (compresión implícita)

```cpp
SparseSegmentTree<NodeSum> st(LIM, q);
vector<long long> cuantos;                      // o un unordered_map si se repiten

for(auto x : puntos) {
    st.set(x, NodeSum(1));                      // o acumular si hay repetidos
}

cout << st.prod(lo, hi).sum << "\n";
```

### $k$-ésimo punto, sin comprimir

```cpp
long long p = st.max_right(0, n - 1, [&](const NodeSum& v) { return v.sum < k; });
cout << p + 1 << "\n";                          // la coordenada del k-esimo
```

### Primer índice $\ge l$ con $a_j \ge x$ sobre un dominio enorme

```cpp
long long p = st.max_right(l, n - 1, [&](const NodeMx& v) { return v.mx < x; });
cout << (p == n - 1 ? -1 : p + 1) << "\n";
```

Entre dos posiciones materializadas el predicado es **constante**, así que el descenso salta los
tramos vacíos de una: el costo es $O(\log n)$ aunque el rango barra $10^{18}$ índices.

### Prefijo más largo de $[l, r]$ con suma $\le S$

```cpp
long long p = st.max_right(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << p - l + 1 << "\n";                      // el largo, sin if
```

### Contar inversiones sin comprimir

```cpp
SparseSegmentTree<NodeSum> st(LIM, n);
long long inv = 0;

for(int i = 0; i < n; i++) {
    if(a[i] + 1 <= LIM - 1) {
        inv += st.prod(a[i] + 1, LIM - 1).sum;  // cuantos de los ya vistos son > a[i]
    }

    st.set(a[i], NodeSum(st.get(a[i]).sum + 1));   // get evita llevar un map de conteos
}
```

El `get` antes del `set` es lo que permite no llevar ningún `map`: el árbol mismo guarda el
conteo. Con `BIT.h` esto es más rápido, pero te obliga a comprimir primero — el sparse sirve
justamente cuando las consultas llegan **online** y no podés.

---

### Lo que `T()` tiene que cumplir, y lo que por eso no se puede

En un árbol sparse `T()` hace **dos trabajos a la vez**:

1. es el agregado que se devuelve por un hijo nulo, o sea **el valor verdadero de un tramo que
   nadie tocó**;
2. es con lo que arranca el acumulador de `max_right` / `min_left` (`T acc = T();` y después
   `acc + st[cur].val`), o sea **la identidad algebraica de `operator+`**.

Con suma las dos coinciden en $0$, y con máximo sobre valores $\ge 0$ también. Por eso los
ejemplos de arriba funcionan.

Pero eso **descarta** los predicados que necesitan que "sin tocar" signifique *ocupado*. El caso
típico es *"el primer índice libre $\ge l$"* con $1$ = ocupado y mínimo: para que el predicado
`mn > 0` ("todo ocupado") sirva, la identidad del mínimo tendría que ser $+\infty$, pero un tramo
sin tocar está **libre**, así que `T()` tiene que valer $0$. Las dos demandas se contradicen, el
acumulador queda clavado en $0$ y `max_right` devuelve el centinela siempre. No es un bug del
template: es que el problema necesita otra estructura.

---

## Hasta dónde llega

Intel Core Ultra 7 155U, g++ 13.2.0 `-O2 -DNDEBUG`, proceso fijado a un core con prioridad alta,
**un proceso por corrida** y el mínimo de 3. Cada celda es **tiempo total (build + consultas) ·
pico de memoria**. El pico es `PeakWorkingSetSize` del proceso entero, así que incluye el vector
de entrada, que es lo que de verdad vas a tener en memoria.

Referencia: **5 s** y **1024 MiB**. `!` marca lo que se pasa de 5 s; `~` lo que queda **en el
borde**, entre 4 y 6.5 s — ahí la medición varía hasta un 15% entre corridas según el estado
térmico de la máquina, así que no te fíes de un pass/fail: medí tu caso.

`T` de 8 B, `InternalNode` de 16 B. Carga: 25% `set` en posición al azar, 50% `prod`, 25% `max_right`. No hay build.

| n \ q | 10⁴ | 10⁵ | 10⁶ | 2·10⁶ |
|---|---|---|---|---|
| **10⁶** | 4 ms · 5 MiB | 50 ms · 7 MiB | 970 ms · 17 MiB | 2.4 s · 22 MiB |
| **10¹⁸** | 10 ms · 6 MiB | 129 ms · 22 MiB | 2.1 s · 169 MiB | 5.6 s · 325 MiB `~` |

El **techo medido** (la `q` más grande que entró en 5 s, buscada a mano y no extrapolada):

A $n = 10^{18}$: **$q = 10^6$** en 2.2 s y 169 MiB. A $n = 10^6$ entra $q = 2\cdot10^6$ en 2.4 s.

**El `n` sí influye, y bastante.** Con el mismo $q = 10^6$, pasar de $n = 10^6$ a $n = 10^{18}$ cuesta **2.2x el tiempo y 10x la memoria** (970 ms y 17 MiB contra 2.1 s y 169 MiB), porque cada `set` materializa $\lceil\log_2 n\rceil + 1$ nodos: 20 contra 60. El build sigue siendo gratis a cualquier `n` — un árbol de $10^{18}$ recién instanciado tiene un nodo.

Si podés comprimir coordenadas y usar el `SegmentTree` denso, hacelo: a $q = 10^6$ es **8.6x** más rápido (247 ms contra 2.1 s) y usa 6x menos memoria.
