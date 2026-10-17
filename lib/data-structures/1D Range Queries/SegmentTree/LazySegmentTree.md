# LazySegmentTree

Estructura para un [monoide](https://en.wikipedia.org/wiki/Monoid) $(S, \cdot, e)$ y un conjunto
$F$ de mapeos $S \to S$ que cumple:

- $F$ contiene la identidad $\mathrm{id}$,
- $F$ es cerrado bajo composición: $f \circ g \in F$ para todos $f, g \in F$,
- $f(x \cdot y) = f(x) \cdot f(y)$ para todos $f \in F$ y $x, y \in S$.

Dado un arreglo $a$ de largo $n$, procesa en $O(\log n)$:

- aplicar un mapeo $f \in F$ a todos los elementos de un intervalo,
- calcular el producto de un intervalo,
- buscar el borde de un intervalo donde un predicado monótono cambia de valor.

Los dos se pasan **como tipos**, no como oráculos: `Node` define `Node()` ($= e$) y `operator+`
($= \cdot$); `LazyUpdate` define `LazyUpdate()` ($= \mathrm{id}$) y `operator*=`
($= \circ$); y `Node::operator*=(const LazyUpdate&)` es la aplicación. El `Node` tiene que llevar
su propio largo si el mapeo lo necesita — el árbol no lo pasa. Contrato completo y catálogo en
[README.md](README.md).

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos**: `assert(0 <= l && l <= r && r < n)`.
`n` es el largo del vector original; internamente se rellena hasta `SZ`, la potencia de dos siguiente.

El descenso es **recursivo** a propósito: el iterativo empata en tiempo (0.99–1.11×) porque hace
1.51× más `push`.

> Casi ningún método es `const`: leer obliga a bajar el lazy pendiente. Solo `all_prod()` lo es.

## Constructor

```cpp
(1) LazySegmentTree<Node, LazyUpdate> seg;
(2) LazySegmentTree<Node, LazyUpdate> seg(int len);
(3) LazySegmentTree<Node, LazyUpdate> seg(const vector<Node>& init);
```

- (1): vacío, `n = 0`.
- (2): largo `len`, todos los elementos en `Node()`. **Ojo**: `Node()` suele ser el rango *vacío*,
  no "un elemento que vale cero" — si el `Node` lleva `size`, con (2) queda en `0` y los `apply`
  se pierden en silencio. Para `n` ceros de verdad: `vector<Node>(n, Node(0))`.
- (3): largo `init.size()`, inicializado con `init`.

**Complejidad**: $O(n)$.

## set

```cpp
void seg.set(int pos, Node val)
```

`a[pos] = val`.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## get

```cpp
Node seg.get(int pos)
```

Devuelve `a[pos]`.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## prod

```cpp
Node seg.prod(int l, int r)
```

Devuelve `a[l] + a[l+1] + ... + a[r]`.

**Restricciones**: $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
Node seg.all_prod() const
```

Devuelve `a[0] + ... + a[n-1]`.

**Complejidad**: $O(1)$.

## apply

```cpp
(1) void seg.apply(int pos, LazyUpdate upd)
(2) void seg.apply(int l, int r, LazyUpdate upd)
```

- (1): `a[pos] = upd(a[pos])`.
- (2): `a[i] = upd(a[i])` para todo `i` en `[l, r]`.

**Restricciones**: (1) $0 \le pos < n$; (2) $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## max_right

```cpp
template <class F> int seg.max_right(int l, int r, F pred)
```

Devuelve el **mayor** $p \in [l, r]$ tal que `pred(prod(l, p))` es cierto, o `l - 1` si ninguno lo
cumple.

**Restricciones**: $0 \le l \le r < n$, y `pred` monótono sobre el rango (cierto en un prefijo de
los $p$ y falso desde ahí) y sin efectos de lado. · **Complejidad**: $O(\log n)$.

## min_left

```cpp
template <class F> int seg.min_left(int l, int r, F pred)
```

Devuelve el **menor** $p \in [l, r]$ tal que `pred(prod(p, r))` es cierto, o `r + 1` si ninguno lo
cumple.

**Restricciones**: $0 \le l \le r < n$, y `pred` monótono al **decrecer** $p$. ·
**Complejidad**: $O(\log n)$.

## dump

```cpp
vector<Node> seg.dump()
```

Devuelve los `n` elementos en orden, con el lazy ya bajado, para depurar.

**Complejidad**: $O(n)$.

---

### Los centinelas

`l - 1` y `r + 1` están elegidos para que el largo del tramo encontrado salga **sin un `if`**:

$$\texttt{max\_right} \longrightarrow p - l + 1, \qquad \texttt{min\_left} \longrightarrow r - p + 1$$

Con el centinela los dos dan $0$. Y como el rango es cerrado y no vacío, el centinela nunca es un
índice válido: `p == l - 1` significa exactamente "ninguno".

## Examples

### Add de rango, suma de rango

```cpp
struct LazyAdd {
    long long a = 0;
    LazyAdd() {}
    LazyAdd(long long x) : a(x) {}
    LazyAdd& operator*=(const LazyAdd& f) { a += f.a; return *this; }
};

struct NodeSum {
    long long size = 0, sum = 0;                // size == 0 es el rango vacio: la identidad
    NodeSum() {}
    NodeSum(long long x) : size(1), sum(x) {}
    friend NodeSum operator+(const NodeSum& a, const NodeSum& b) {
        NodeSum r; r.size = a.size + b.size; r.sum = a.sum + b.sum; return r;
    }
    NodeSum& operator*=(const LazyAdd& f) { sum += f.a * size; return *this; }
};

LazySegmentTree<NodeSum, LazyAdd> seg(vector<NodeSum>(n, NodeSum(0)));
seg.apply(l, r, LazyAdd(v));
cout << seg.prod(l, r).sum << "\n";
```

### Assign de rango, con mínimo y máximo

El `LazyUpdate` que compone assign y add está en el
[README](README.md#b-suma-máximo-y-mínimo-con-assign-y-add-de-rango).

### Afín de rango: $a_i \to p\,a_i + q$, suma de rango

El clásico de clásicos, y **el único ejemplo que obliga a acertar el orden de `f *= g`**: con un
lazy aditivo el orden conmuta y un error queda latente, acá revienta.

```cpp
static const ll MOD = 998244353;

struct LazyAffine {                             // x -> p*x + q
    ll p = 1, q = 0;                            // (1, 0) es la identidad

    LazyAffine() {}
    LazyAffine(ll P, ll Q) : p(P), q(Q) {}

    // g actua DESPUES de f:  g(f(x)) = g.p*(p*x + q) + g.q
    LazyAffine& operator*=(const LazyAffine& g) {
        p = g.p * p % MOD;
        q = (g.p * q + g.q) % MOD;
        return *this;
    }
};

struct NodeSum {
    ll size = 0, sum = 0;                       // size == 0 es el rango vacio: la identidad

    NodeSum() {}
    NodeSum(ll x) : size(1), sum(x % MOD) {}

    friend NodeSum operator+(const NodeSum& a, const NodeSum& b) {
        NodeSum r;
        r.size = a.size + b.size;
        r.sum = (a.sum + b.sum) % MOD;
        return r;
    }

    NodeSum& operator*=(const LazyAffine& f) {
        sum = (f.p * sum + f.q * size) % MOD;   // cada x_i -> p*x_i + q, en size posiciones
        return *this;
    }
};

LazySegmentTree<NodeSum, LazyAffine> seg(a);
seg.apply(l, r, LazyAffine(p, q));
cout << seg.prod(l, r).sum << "\n";
```

Library Checker [Range Affine Range Sum](https://judge.yosupo.jp/problem/range_affine_range_sum).

### Máximo solapamiento de intervalos

El sweep line, que es la aplicación más común de add + máximo: sumá $1$ en cada intervalo y pedí
el máximo global.

```cpp
LazySegmentTree<NodeMxLazy, LazyAdd> seg(vector<NodeMxLazy>(n, NodeMxLazy(0)));

for(auto& [l, r] : intervalos) {
    seg.apply(l, r, LazyAdd(1));
}

ll best = seg.all_prod().mx;                    // cuantos intervalos se pisan como maximo
```

Y `max_right` dice **dónde**: el primer índice que alcanza ese máximo es
`seg.max_right(0, n - 1, [&](const NodeMxLazy& v) { return v.mx < best; }) + 1`.

### Primer $j \ge l$ con $a_j \ge x$, con add de rango

Codeforces EDU, ITMO Academy, segment tree part 2, problema C — **AC en 125 ms**
([envío 394467936](https://codeforces.com/edu/course/2/lesson/5/3)):

```cpp
int p = seg.max_right(l, n - 1, [&](const NodeMxLazy& v) { return v.mx < x; });
cout << (p == n - 1 ? -1 : p + 1) << "\n";      // p == n-1 es el "no existe"
```

El predicado `mx < x` es monótono **siempre**: el máximo de un prefijo no decrece al extenderlo,
y eso no le pide nada a los datos. Con suma sería distinto: ahí haría falta que `v` fuera no
negativo.

### $k$-ésimo uno, con flips de rango

Con valores 0/1 y un `LazyUpdate` que invierte (`sum = size - sum`):

```cpp
int p = seg.max_right(0, n - 1, [&](const NodeSum& v) { return v.sum < k; });
cout << p + 1 << "\n";
```

### Prefijo más largo de $[l, r]$ con suma $\le S$

Necesita valores no negativos, si no la suma no es monótona:

```cpp
int p = seg.max_right(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << p - l + 1 << "\n";                      // el largo, sin if: con p == l-1 da 0
```

### Máxima suma de un subarreglo, con assign de rango

El monoide no conmutativo del [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido),
combinado con el `LazyUpdate` de assign:

```cpp
seg.apply(l, r, LazyUpdate::assign(v));
cout << seg.prod(l, r).best << "\n";
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

`Node` de 16 B (`size` + `sum`) y `LazyUpdate` de 8 B. Carga: 25% `apply` de rango, 50% `prod`, 25% `max_right`, rangos al azar.

### Tiempo total (build + consultas)

| n \ q | 10⁵ | 2·10⁵ | 5·10⁵ | 10⁶ | 2·10⁶ | 5·10⁶ | 10⁷ |
|---|---|---|---|---|---|---|---|
| **10⁵** | 29 ms | 50 ms | 130 ms | 287 ms | 439 ms | 1.2 s | 2.9 s |
| **2·10⁵** | 40 ms | 76 ms | 185 ms | 314 ms | 511 ms | 1.8 s | 3.9 s |
| **5·10⁵** | 49 ms | 86 ms | 290 ms | 484 ms | 843 ms | 2.5 s | 4.4 s `~` |
| **10⁶** | 112 ms | 95 ms | 201 ms | 390 ms | 854 ms | 2.5 s | 5.0 s `~` |
| **2·10⁶** | 144 ms | 116 ms | 246 ms | 502 ms | 939 ms | 3.0 s | 6.2 s `~` |
| **5·10⁶** | 150 ms | 216 ms | 361 ms | 675 ms | 1.5 s | 4.0 s `~` | 8.0 s `!` |
| **10⁷** | 379 ms | 481 ms | 728 ms | 1.3 s | 2.0 s | 4.8 s `~` | 10.5 s `!` |

### Pico de memoria en MiB

`PeakWorkingSetSize` del proceso entero, así que **incluye el vector de entrada**, que es lo que de verdad vas a tener en memoria.

| n \ q | 10⁵ | 2·10⁵ | 5·10⁵ | 10⁶ | 2·10⁶ | 5·10⁶ | 10⁷ |
|---|---|---|---|---|---|---|---|
| **10⁵** | 11 | 11 | 11 | 11 | 11 | 11 | 11 |
| **2·10⁵** | 18 | 18 | 18 | 18 | 18 | 18 | 18 |
| **5·10⁵** | 32 | 32 | 32 | 32 | 32 | 32 | 32 |
| **10⁶** | 60 | 60 | 60 | 60 | 60 | 60 | 60 |
| **2·10⁶** | 115 | 115 | 115 | 115 | 115 | 115 | 115 |
| **5·10⁶** | 401 | 401 | 401 | 401 | 401 | 401 | 401 |
| **10⁷** | 797 | 797 | 797 | 797 | 797 | 797 | 797 |

Cuesta entre **2x y 3x** el `SegmentTree` con la misma carga (a $n = q = 10^6$, 390 ms contra 158), que es el precio del `push`. Se cae de los 5 s solo en la columna $q = 10^7$: a $n = 10^6$ roza (5.0 s) y desde $n = 2\cdot10^6$ se pasa claro.

Como en el no lazy, **la memoria no depende de `q`**. Y ahí está el límite real: a $n = 10^7$ son **797 MiB** con un `Node` de 16 B. Si el tuyo pesa más, a $n = 10^7$ no entrás en 1024 MiB — y la matriz de tiempo no te va a avisar, porque el tiempo sí entra.
