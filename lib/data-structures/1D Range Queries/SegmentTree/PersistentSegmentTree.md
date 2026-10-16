# PersistentSegmentTree

Igual que [`SegmentTree`](SegmentTree.md) — monoide $(S, \cdot, e)$, `T()` es $e$ y `operator+` es
$\cdot$ — pero **cada `set` devuelve la raíz de una versión nueva** y deja intactas las anteriores.
Una raíz es un `int`, así que guardarlas es gratis.

Dado un largo $n$, procesa en $O(\log n)$: asignar (creando una versión), consultar el producto de
un intervalo de *cualquier* versión, y buscar un borde por descenso — sobre una versión o sobre la
**diferencia de dos**.

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos**: `assert(0 <= l && l <= r && r < n)`.
Catálogo de nodos en [README.md](README.md).

**Pool**: hay que declarar de antemano cuántas operaciones vas a hacer.

$$\texttt{max\_nodes}(n, q) = 2n + (\lceil \log_2 n \rceil + 1)\,q + 1$$

Pasarse de largo es gratis (se reserva de más y no se usa); quedarse corto hace crecer el `vector`
y reubicar. `build()` sin argumentos **no consume nodos**.

## Constructor

```cpp
PersistentSegmentTree<T> st(int len, long long max_ops);
```

Reserva el pool para un árbol de largo `len` y `max_ops` operaciones que creen versiones.

**Restricciones**: $len \ge 1$, $max\_ops \ge 0$. · **Complejidad**: $O(1)$ — solo reserva.

## max_nodes

```cpp
static long long PersistentSegmentTree<T>::max_nodes(int len, long long max_ops)
```

Devuelve cuántos nodos va a reservar el constructor con esos parámetros, para presupuestar memoria
antes de instanciar.

**Complejidad**: $O(1)$.

## build

```cpp
(1) int st.build()
(2) int st.build(const vector<T>& init)
```

- (1): la versión "todo en `T()`", que **no gasta un solo nodo** del pool.
- (2): la versión inicializada con `init`, que cuesta $2n$ nodos.

Las dos devuelven la raíz.

**Restricciones**: (2) `init.size() == n`. · **Complejidad**: (1) $O(1)$, (2) $O(n)$.

## set

```cpp
int st.set(int root, int pos, T val)
```

Devuelve la raíz de una versión nueva, idéntica a `root` salvo que `a[pos] = val`.

**Restricciones**: `root` válido, $0 \le pos < n$. · **Complejidad**: $O(\log n)$, y crea
$\lceil \log_2 n \rceil + 1$ nodos.

## get

```cpp
T st.get(int root, int pos) const
```

Devuelve el `a[pos]` de la versión `root`.

**Restricciones**: `root` válido, $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## prod

```cpp
T st.prod(int root, int l, int r) const
```

Devuelve `a[l] + ... + a[r]` en la versión `root`.

**Restricciones**: `root` válido, $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
T st.all_prod(int root) const
```

Devuelve `a[0] + ... + a[n-1]` en la versión `root`.

**Complejidad**: $O(1)$.

## max_right

```cpp
(1) template <class F> int st.max_right(int root, int l, int r, F pred) const
(2) template <class F> int st.max_right(int root_before, int root_after, int l, int r, F pred) const
```

- (1): el **mayor** $p \in [l, r]$ con `pred(prod(root, l, p))` cierto, o `l - 1`.
- (2): ídem, pero `pred` recibe **dos** agregados — el de `root_before` y el de `root_after` sobre
  el mismo tramo — así que la lambda puede restarlos sin que el monoide necesite inverso.

**Restricciones**: $0 \le l \le r < n$, `pred` monótono sobre el rango y sin efectos de lado. ·
**Complejidad**: $O(\log n)$. La de dos versiones cuesta 1.08–1.22× la de una (medido).

## min_left

```cpp
(1) template <class F> int st.min_left(int root, int l, int r, F pred) const
(2) template <class F> int st.min_left(int root_before, int root_after, int l, int r, F pred) const
```

El espejo: el **menor** $p \in [l, r]$ con `pred(prod(p, r))` cierto, o `r + 1`.

**Restricciones**: las mismas, con `pred` monótono al **decrecer** $p$. ·
**Complejidad**: $O(\log n)$.

## dump

```cpp
vector<T> st.dump(int root) const
```

Devuelve los `n` elementos de la versión `root` en orden, para depurar.

**Complejidad**: $O(n)$.

## copy

```cpp
int st.copy(int root)
```

Devuelve otra raíz que apunta al mismo contenido, sin copiar nada.

**Complejidad**: $O(1)$.

## size / nodes_used

```cpp
int st.size() const
long long st.nodes_used() const
```

El largo del árbol, y cuántos nodos del pool se consumieron — para depurar el presupuesto.

**Complejidad**: $O(1)$.

---

### Los centinelas

`l - 1` y `r + 1` están elegidos para que el largo del tramo salga **sin un `if`**:
`p - l + 1` y `r - p + 1`. Con el centinela los dos dan $0$, y como el rango es cerrado y no
vacío, el centinela nunca es un índice válido.

## Examples

### Viaje en el tiempo: consultar una versión vieja

```cpp
PersistentSegmentTree<NodeSum> st(n, q);
vector<int> ver;
ver.push_back(st.build(a));                     // version 0

for(int i = 0; i < q; i++) {
    // ... leer la operacion
    ver.push_back(st.set(ver.back(), pos, NodeSum(val)));
}

cout << st.prod(ver[t], l, r).sum << "\n";      // como estaba en el tiempo t
```

### $k$-ésimo menor de un rango (el patrón clave)

El árbol vive sobre el dominio de **valores** comprimidos, no de posiciones: `ver[i]` cuenta
cuántas veces aparece cada valor en `a[0..i-1]`. Entonces

$$\#\{j \in [l, r) : a_j = v\} = \texttt{ver}[r][v] - \texttt{ver}[l][v]$$

y eso vale para cualquier subárbol. Por eso hace falta bajar por **las dos versiones a la vez**:
con una sola no se puede, y la resta no está en el contrato del monoide — va en la lambda.

```cpp
int p = st.max_right(ver[l], ver[r], 0, m - 1,
    [&](const NodeSum& antes, const NodeSum& despues) {
        return despues.sum - antes.sum < k;     // menos de k elementos <= vals[p]
    });

cout << vals[p + 1] << "\n";                    // el k-esimo menor
```

Library Checker [Range Kth Smallest](https://judge.yosupo.jp/problem/range_kth_smallest).

### Cantidad de distintos en un rango

`ver[i]` marca con 1 la posición de la aparición **más reciente** de cada valor en `a[0..i]`.
Entonces los distintos de `[l, r]` son `prod(ver[r], l, r)`:

```cpp
vector<int> ultimo(m, -1);
ver[0] = st.build();

for(int i = 0; i < n; i++) {
    int rt = ver[i];
    if(ultimo[a[i]] != -1) rt = st.set(rt, ultimo[a[i]], NodeSum(0));
    ver[i + 1] = st.set(rt, i, NodeSum(1));
    ultimo[a[i]] = i;
}

cout << st.prod(ver[r + 1], l, r).sum << "\n";
```

### Suma de los $k$ menores de un rango

Con un `Node` que lleve conteo **y** suma, el mismo descenso de dos versiones da el corte y de
paso el acumulado:

```cpp
struct NodeSumCnt {
    long long cnt = 0, sum = 0;
    NodeSumCnt() {}
    NodeSumCnt(long long c, long long s) : cnt(c), sum(s) {}
    friend NodeSumCnt operator+(const NodeSumCnt& a, const NodeSumCnt& b) {
        return NodeSumCnt(a.cnt + b.cnt, a.sum + b.sum);
    }
};

int p = st.max_right(ver[l], ver[r], 0, m - 1,
    [&](const NodeSumCnt& antes, const NodeSumCnt& despues) {
        return despues.cnt - antes.cnt <= k;
    });
```

### `mex` de un rango

El árbol guarda, para cada valor $v$, la última posición donde aparece. El `mex` de `[l, r]` es el
menor $v$ cuya última aparición es $< l$, o sea un `max_right` con `mn >= l`:

```cpp
int p = st.max_right(ver[r], 0, m - 1, [&](const NodeMn& v) { return v.mn >= l; });
cout << p + 1 << "\n";
```
