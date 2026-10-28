# SegmentTree

Estructura para un [monoide](https://en.wikipedia.org/wiki/Monoid) $(S, \cdot : S \times S \to S, e \in S)$.

Dado un arreglo $a$ de largo $n$, procesa en $O(\log n)$:

- asignar un elemento,
- calcular el producto de un intervalo,
- buscar el borde de un intervalo donde un predicado monótono cambia de valor.

El monoide se pasa **como un tipo**, no como oráculos `op`/`e`: el tipo `T` tiene que definir
`T()` (que vale $e$) y `operator+` (que vale $\cdot$, asociativa). Catálogo de nodos listos para
copiar en [README.md](README.md).

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos**: cada método que recibe un
rango hace `assert(0 <= l && l <= r && r < n)`. `n` es el largo del vector original; internamente
el arreglo se rellena hasta `SZ`, la potencia de dos siguiente.

El descenso es **iterativo** (medido: 1.77–3.85× más rápido que el recursivo). Los detalles de la
estructura interna están en el header.

## Constructor

```cpp
(1) SegmentTree<T> seg;
(2) SegmentTree<T> seg(int len);
(3) SegmentTree<T> seg(const vector<T>& init);
```

- (1): vacío, `n = 0`.
- (2): largo `len`, todos los elementos en `T()`.
- (3): largo `init.size()`, inicializado con `init`.

**Complejidad**: $O(n)$.

## set

```cpp
void seg.set(int pos, T val)
```

`a[pos] = val`.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(\log n)$.

## get / operator[]

```cpp
T seg.get(int pos) const
T seg.operator[](int pos) const
```

Devuelve `a[pos]`.

`seg[pos]` es exactamente `get(pos)`, para que la estructura se lea como un `vector`:

```cpp
for (int i = 0; i < n; i++) cout << seg[i].sum << " ";
```

**Es de solo lectura**: devuelve por valor y es `const`. Una versión que devolviera una
referencia dejaría escribir sin subir el camino con `pull`, y el agregado de los ancestros
quedaría desactualizado en silencio. Para escribir va `set(pos, val)`.

**Restricciones**: $0 \le pos < n$. · **Complejidad**: $O(1)$ los dos.

## prod

```cpp
T seg.prod(int l, int r) const
```

Devuelve `a[l] + a[l+1] + ... + a[r]`.

**Restricciones**: $0 \le l \le r < n$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
T seg.all_prod() const
```

Devuelve `a[0] + ... + a[n-1]`.

**Complejidad**: $O(1)$.

## max_right

```cpp
template <class F> int seg.max_right(int l, int r, F pred) const
```

Devuelve el **mayor** $p \in [l, r]$ tal que `pred(prod(l, p))` es cierto, o `l - 1` si ninguno lo
cumple.

**Restricciones**: $0 \le l \le r < n$, y `pred` monótono sobre el rango (cierto en un prefijo de
los $p$ y falso desde ahí) y sin efectos de lado. · **Complejidad**: $O(\log n)$.

## min_left

```cpp
template <class F> int seg.min_left(int l, int r, F pred) const
```

Devuelve el **menor** $p \in [l, r]$ tal que `pred(prod(p, r))` es cierto, o `r + 1` si ninguno lo
cumple.

**Restricciones**: $0 \le l \le r < n$, y `pred` monótono al **decrecer** $p$. ·
**Complejidad**: $O(\log n)$.

## dump

```cpp
vector<T> seg.dump() const
```

Devuelve los `n` elementos en orden, para depurar.

**Complejidad**: $O(n)$.

---

### Los centinelas

`l - 1` y `r + 1` están elegidos para que el largo del tramo encontrado salga **sin un `if`**:

$$\texttt{max\_right} \longrightarrow p - l + 1, \qquad \texttt{min\_left} \longrightarrow r - p + 1$$

Con el centinela los dos dan $0$. Y como el rango es cerrado y no vacío, el centinela nunca es un
índice válido: `p == l - 1` significa exactamente "ninguno".

## Examples

### Mínimo de un rango (RMQ)

```cpp
struct NodeMn {
    int mn = INT_MAX;                           // INT_MAX es la identidad de min
    NodeMn() {}
    NodeMn(int x) : mn(x) {}
    friend NodeMn operator+(const NodeMn& a, const NodeMn& b) { return NodeMn(min(a.mn, b.mn)); }
};

SegmentTree<NodeMn> seg(a);                     // a es vector<NodeMn>
cout << seg.prod(l, r).mn << "\n";
seg.set(p, NodeMn(x));
```

### Suma de un rango, y el $k$-ésimo uno

Con valores 0/1, `max_right` con `sum < k` da la posición del $k$-ésimo uno:

```cpp
SegmentTree<NodeSum> seg(a);
int p = seg.max_right(0, n - 1, [&](const NodeSum& v) { return v.sum < k; });
cout << p + 1 << "\n";                          // si no hay k unos, p == n-1 y p+1 == n
```

### Primer $j \ge l$ con $a_j \ge x$

El predicado `mx < x` es monótono **siempre**: el máximo de un prefijo no decrece al extenderlo.

```cpp
int p = seg.max_right(l, n - 1, [&](const NodeMx& v) { return v.mx < x; });
cout << (p == n - 1 ? -1 : p + 1) << "\n";      // p == n-1 es el "no existe"
```

### Último $j \le r$ con $a_j \ge x$

El espejo, con `min_left`:

```cpp
int p = seg.min_left(0, r, [&](const NodeMx& v) { return v.mx < x; });
cout << (p == 0 ? -1 : p - 1) << "\n";
```

### Prefijo más largo de $[l, r]$ con suma $\le S$

Necesita valores no negativos, si no la suma no es monótona:

```cpp
int p = seg.max_right(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << p - l + 1 << "\n";                      // el largo, sin if: con p == l-1 da 0
```

### Sufijo más largo de $[l, r]$ con suma $\le S$

```cpp
int p = seg.min_left(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << r - p + 1 << "\n";
```

### Máxima suma de un subarreglo

El monoide no conmutativo del [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido):

```cpp
SegmentTree<Node> seg(a);
cout << seg.prod(l, r).best << "\n";
```

### Paréntesis balanceados en $[l, r]$

El primer `Node` con un combine no obvio, y **no conmutativo**: el mínimo prefijo de `a + b`
depende de dónde arrancan los prefijos de `b`.

```cpp
struct NodeSumMnPref {
    ll sum = 0;                                 // '(' vale +1, ')' vale -1
    ll mnpref = 0;                              // el minimo sobre TODOS los prefijos, el vacio incluido

    NodeSumMnPref() {}                          // (0, 0) es la identidad
    NodeSumMnPref(ll x) : sum(x), mnpref(min(0LL, x)) {}

    friend NodeSumMnPref operator+(const NodeSumMnPref& a, const NodeSumMnPref& b) {
        NodeSumMnPref r;
        r.sum = a.sum + b.sum;
        r.mnpref = min(a.mnpref, a.sum + b.mnpref);   // los prefijos de b arrancan en a.sum
        return r;
    }
};
```

Incluir el prefijo vacío es lo que hace que `(0, 0)` sea la identidad: así `mnpref` siempre es
$\le 0$, y entonces `min(a.mnpref, a.sum)` ya vale `a.mnpref` sin tener que chequear nada.

```cpp
NodeSumMnPref v = seg.prod(l, r);
bool balanceado = v.sum == 0 && v.mnpref == 0;  // cierra en 0 y ningun prefijo se fue a negativo
```

Y `max_right` da **dónde se rompe**: el último $p$ tal que `a[l..p]` todavía no se fue a negativo.

```cpp
int p = seg.max_right(l, r, [&](const NodeSumMnPref& v) { return v.mnpref == 0; });
// si p < r, el primer ')' de sobra esta en p + 1
```

El predicado es monótono porque `mnpref` no crece al extender el prefijo.

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

`Node` de 8 B (solo `sum`). Carga: 25% `set`, 50% `prod`, 25% `max_right`, rangos al azar.

### Tiempo total (build + consultas)

| n \ q | 10⁵ | 2·10⁵ | 5·10⁵ | 10⁶ | 2·10⁶ | 5·10⁶ | 10⁷ |
|---|---|---|---|---|---|---|---|
| **10⁵** | 13 ms | 22 ms | 62 ms | 130 ms | 220 ms | 519 ms | 933 ms |
| **2·10⁵** | 10 ms | 20 ms | 49 ms | 100 ms | 217 ms | 476 ms | 1.1 s |
| **5·10⁵** | 24 ms | 59 ms | 68 ms | 141 ms | 306 ms | 772 ms | 1.3 s |
| **10⁶** | 38 ms | 82 ms | 90 ms | 158 ms | 304 ms | 788 ms | 2.2 s |
| **2·10⁶** | 27 ms | 44 ms | 95 ms | 189 ms | 401 ms | 1.0 s | 2.6 s |
| **5·10⁶** | 68 ms | 97 ms | 159 ms | 266 ms | 508 ms | 1.3 s | 3.0 s |
| **10⁷** | 210 ms | 175 ms | 232 ms | 396 ms | 902 ms | 1.8 s | 2.7 s |

### Pico de memoria en MiB

`PeakWorkingSetSize` del proceso entero, así que **incluye el vector de entrada**, que es lo que de verdad vas a tener en memoria.

| n \ q | 10⁵ | 2·10⁵ | 5·10⁵ | 10⁶ | 2·10⁶ | 5·10⁶ | 10⁷ |
|---|---|---|---|---|---|---|---|
| **10⁵** | 7 | 7 | 7 | 7 | 7 | 7 | 7 |
| **2·10⁵** | 10 | 10 | 10 | 10 | 10 | 10 | 10 |
| **5·10⁵** | 16 | 16 | 16 | 16 | 16 | 16 | 16 |
| **10⁶** | 28 | 28 | 28 | 28 | 28 | 28 | 28 |
| **2·10⁶** | 52 | 52 | 52 | 52 | 52 | 52 | 52 |
| **5·10⁶** | 171 | 171 | 171 | 171 | 171 | 171 | 171 |
| **10⁷** | 337 | 337 | 337 | 337 | 337 | 337 | 337 |

**Las 49 combinaciones entran en 5 s**, y la peor es 3.0 s. Es la única de la familia que aguanta la grilla completa.

La memoria **no depende de `q`** en absoluto: son $2 \cdot SZ$ nodos reservados en el constructor, así que cada fila es una constante. Eso la vuelve la opción obvia cuando `q` es grande y `n` moderado: a $n = 10^5$ con $q = 10^7$ son 933 ms y 7 MiB.

El tiempo crece casi lineal en `q` y muy poco en `n`: con $q = 10^6$ fijo, pasar de $n = 10^5$ a $n = 10^7$ va de 130 a 396 ms — un factor 3 para `n` cien veces mayor, que es el $\log n$ más la localidad.
