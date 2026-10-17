# SparseLazySegmentTree

[`SparseSegmentTree`](SparseSegmentTree.md) más updates de rango: nodos creados al tocarlos, largo
hasta $10^{18}$, y `apply(l, r, upd)` en $O(\log n)$.

El contrato del `Node` es el único distinto de la familia: **no** es `operator*=`, es

```cpp
void apply(const LazyUpdate& f, long long len)
```

porque el árbol **le pasa el largo**. Un nodo sparse puede representar un tramo gigante que nunca
se materializó, así que no puede llevar su propio `size`. El `LazyUpdate` sí es igual al de
[`LazySegmentTree`](LazySegmentTree.md): `LazyUpdate()` es $\mathrm{id}$ y `operator*=` es $\circ$.
Catálogo en [README.md](README.md).

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos**: `assert(0 <= l && l <= r && r < n)`.
Los índices son `long long`.

**Pool**: el factor 4 sale de que un `apply` de rango toca hasta cuatro caminos.

$$\texttt{max\_nodes}(n, q) = 4(\lceil \log_2 n \rceil + 1)\,q + 1$$

> El lazy **no se baja con `push`**: eso materializaría nodos durante una lectura. Lo pendiente
> viaja como parámetro en el descenso, así que todas las lecturas son `const`.

## Constructor

```cpp
SparseLazySegmentTree<Node, LazyUpdate> st(long long len, long long max_ops);
```

Reserva el pool para un árbol de largo `len` y `max_ops` operaciones que creen nodos.

**Restricciones**: $len \ge 1$, $max\_ops \ge 0$. · **Complejidad**: $O(1)$ — solo reserva.

## max_nodes

```cpp
static long long SparseLazySegmentTree<Node, LazyUpdate>::max_nodes(long long len, long long max_ops)
```

Devuelve cuántos nodos va a reservar el constructor con esos parámetros, para presupuestar memoria
antes de instanciar.

**Complejidad**: $O(1)$.

## set

```cpp
void st.set(long long pos, Node val)
```

`a[pos] = val`, materializando el camino hasta `pos` si hacía falta.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## apply

```cpp
(1) void st.apply(long long pos, LazyUpdate upd)
(2) void st.apply(long long l, long long r, LazyUpdate upd)
```

- (1): `a[pos] = upd(a[pos])`.
- (2): `a[i] = upd(a[i])` para todo `i` en `[l, r]`.

**Restricciones**: (1) $0 \le pos < n$; (2) $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## get

```cpp
Node st.get(long long pos) const
```

Devuelve `a[pos]`, con los `apply` pendientes ya resueltos.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## prod

```cpp
Node st.prod(long long l, long long r) const
```

Devuelve `a[l] + ... + a[r]`.

**Restricciones**: $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
Node st.all_prod() const
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
vector<Node> st.dump() const
```

Devuelve los `n` elementos en orden, incluyendo los tramos que nunca se materializaron (con los
`apply` pendientes ya aplicados), para depurar. Hace `assert(n <= DUMP_MAX)` con
`DUMP_MAX = 10'000'000`.

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

### Add y suma de rango sobre coordenadas gigantes

El `Node` recibe el largo, así que no necesita `size`:

```cpp
struct LazyAdd {
    long long a = 0;
    LazyAdd() {}
    LazyAdd(long long x) : a(x) {}
    LazyAdd& operator*=(const LazyAdd& f) { a += f.a; return *this; }
};

struct NodeSum {
    long long sum = 0;
    NodeSum() {}
    NodeSum(long long x) : sum(x) {}
    friend NodeSum operator+(const NodeSum& a, const NodeSum& b) { return NodeSum(a.sum + b.sum); }
    void apply(const LazyAdd& f, long long len) { sum += f.a * len; }   // el largo lo da el arbol
};

SparseLazySegmentTree<NodeSum, LazyAdd> st(1'000'000'000'000'000'000LL, q);
st.apply(1'000'000, 2'000'000'000'000LL, LazyAdd(3));
cout << st.prod(0, 5'000'000'000'000LL).sum << "\n";
```

### Máximo solapamiento de intervalos, sin comprimir

El sweep line a $10^{18}$, que es la razón de existir de este template: nada de ordenar eventos ni
comprimir coordenadas.

```cpp
struct NodeMx {
    ll mx = 0;                                  // un tramo SIN TOCAR tiene 0 intervalos encima,
                                                // y 0 es la identidad del maximo con valores >= 0
    NodeMx() {}
    NodeMx(ll x) : mx(x) {}

    friend NodeMx operator+(const NodeMx& a, const NodeMx& b) { return NodeMx(max(a.mx, b.mx)); }

    void apply(const LazyAdd& f, ll) { mx += f.a; }   // el largo no hace falta para un maximo
};

SparseLazySegmentTree<NodeMx, LazyAdd> st(LIM, intervalos.size());

for(auto& [l, r] : intervalos) {
    st.apply(l, r, LazyAdd(1));
}

ll best = st.all_prod().mx;                     // cuantos se pisan como maximo
ll donde = st.max_right(0, LIM - 1, [&](const NodeMx& v) { return v.mx < best; }) + 1;
```

Acá `NodeMx()` vale `mx = 0`, y **eso es correcto por dos razones a la vez**: un tramo que nadie
tocó tiene de verdad $0$ intervalos encima, y $0$ es la identidad del máximo mientras los valores
sean $\ge 0$. En un árbol sparse `T()` tiene que cumplir las dos cosas — ver la nota al final.

### Pintar intervalos y contar

Con un `LazyUpdate` de assign, `apply(l, r, assign(1))` pinta y `prod` cuenta lo pintado:

```cpp
st.apply(l, r, LazyUpdate::assign(1));
cout << st.prod(0, n - 1).sum << "\n";          // cuantas posiciones quedaron pintadas
```

### Primer índice $\ge l$ con $a_j \ge x$ tras varios add de rango

Con el `NodeMx` de arriba:

```cpp
long long p = st.max_right(l, n - 1, [&](const NodeMx& v) { return v.mx < x; });
cout << (p == n - 1 ? -1 : p + 1) << "\n";
```

Entre dos posiciones materializadas el predicado es **constante**, así que el descenso salta los
tramos vacíos de una: el costo es $O(\log n)$ aunque el rango barra $10^{18}$ índices. Eso vale
también cuando el tramo vacío tiene un `apply` pendiente — el `Node` lo resuelve con el largo que
le pasa el árbol.

### Prefijo más largo de $[l, r]$ con suma $\le S$

```cpp
long long p = st.max_right(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << p - l + 1 << "\n";                      // el largo, sin if
```

### Sufijo más largo de $[l, r]$ con suma $\le S$

```cpp
long long p = st.min_left(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << r - p + 1 << "\n";
```

---

## Hasta dónde llega

Intel Core Ultra 7 155U, g++ 13.2.0 `-O2 -DNDEBUG`, proceso fijado a un core con prioridad alta,
**un proceso por corrida**. Las celdas que entran en 8 s son el mínimo de 3 corridas; las que se
pasan son una sola, porque afinar un número que ya no sirve es tiempo tirado.

> **Las celdas pesadas son órdenes de magnitud, no valores precisos.** La grilla entera tardó
> ~1.5 h y la máquina deriva térmicamente: una celda del treap que la grilla midió en 5.7 s dio
> 9.3–12.3 s al re-medirla después. Lo que **sí** es robusto es el veredicto (entra / no entra) y
> la forma de la matriz; el número exacto de una celda de más de 5 s no lo es.

Marcas, con las referencias **5 s** y **1024 MiB**:

| | en tiempo | en memoria |
|---|---|---|
| sin marca | entra | entra |
| `~` | 4–6.5 s: en el borde, medí tu caso | más de 820 MiB, o sea 80% del límite |
| `!` | se pasa de 5 s | se pasa de 1024 MiB |
| `≫` | no se corrió: con una `q` menor ya se había ido muy lejos, y el tiempo crece con `q` | — |
| `✕` | no terminó o no pudo reservar el pool | — |

`Node` de 8 B, `LazyUpdate` de 8 B. Carga: 25% `apply` de rango, 50% `prod`, 25% `max_right`. No hay build. La última fila es el caso que justifica el template.

### Tiempo total (build + consultas)

| n \ q | 10⁵ | 2·10⁵ | 5·10⁵ | 10⁶ | 2·10⁶ | 5·10⁶ | 10⁷ |
|---|---|---|---|---|---|---|---|
| **10⁵** | 60 ms | 146 ms | 298 ms | 571 ms | 1.2 s | 3.8 s | 9.1 s `!` |
| **2·10⁵** | 47 ms | 116 ms | 376 ms | 806 ms | 1.9 s | 5.4 s `~` | 13.4 s `!` |
| **5·10⁵** | 54 ms | 137 ms | 472 ms | 1.2 s | 2.2 s | 7.2 s `!` | 16.6 s `!` |
| **10⁶** | 41 ms | 101 ms | 353 ms | 777 ms | 1.8 s | 6.9 s `!` | 18.2 s `!` |
| **2·10⁶** | 46 ms | 126 ms | 412 ms | 1.1 s | 2.1 s | 7.3 s `!` | 22.1 s `!` |
| **5·10⁶** | 46 ms | 124 ms | 423 ms | 880 ms | 2.0 s | 7.5 s `!` | 19.6 s `!` |
| **10⁷** | 72 ms | 187 ms | 653 ms | 990 ms | 2.2 s | 7.4 s `!` | 19.8 s `!` |
| **10¹⁸** | 110 ms | 248 ms | 728 ms | 1.6 s | 4.9 s `~` | 21.9 s `!` | `✕` |

### Pico de memoria en MiB

`PeakWorkingSetSize` del proceso entero, así que **incluye el vector de entrada**, que es lo que de verdad vas a tener en memoria.

| n \ q | 10⁵ | 2·10⁵ | 5·10⁵ | 10⁶ | 2·10⁶ | 5·10⁶ | 10⁷ |
|---|---|---|---|---|---|---|---|
| **10⁵** | 8 | 8 | 9 | 9 | 9 | 9 | 9 |
| **2·10⁵** | 9 | 11 | 13 | 14 | 14 | 14 | 14 |
| **5·10⁵** | 11 | 14 | 19 | 23 | 26 | 27 | 28 |
| **10⁶** | 13 | 18 | 26 | 34 | 42 | 49 | 50 |
| **2·10⁶** | 15 | 22 | 35 | 48 | 63 | 83 | 93 |
| **5·10⁶** | 18 | 27 | 48 | 71 | 103 | 154 | 192 |
| **10⁷** | 20 | 32 | 58 | 90 | 138 | 224 | 303 |
| **10¹⁸** | 104 | 199 | 474 | 921 `~` | 1791 `!` | 4319 `!` | — |

**La única celda de las 357 que no pudo ni arrancar**: $n = 10^{18}$ con $q = 10^7$ falla al reservar el pool, porque $4(\lceil\log_2 n\rceil + 1)\,q$ son $2.4\cdot10^9$ nodos. No es que tarde: no entra en el espacio de direcciones.

Para $n \le 10^7$ la estructura es sorprendentemente manejable — a $n = q = 10^7$ son 19.8 s pero solo 303 MiB, y con $q \le 2\cdot10^6$ entra en tiempo en todas las filas de $n \le 10^7$. **El problema aparece con `n` enorme**: a $10^{18}$ el pico es de 921 MiB con $q = 10^6$ y 4.3 GiB con $q = 5\cdot10^6$, porque el factor 4 del `apply` de rango se multiplica por los 60 niveles.

Conclusión práctica: si tus coordenadas caben en $10^7$ después de comprimir, comprimí — con $q = 10^6$ eso te deja en 990 ms y 50 MiB en lugar de 1.7 s y 921 MiB.
