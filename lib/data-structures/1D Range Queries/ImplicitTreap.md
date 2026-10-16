# ImplicitTreap

Un `vector` con todo en $O(\log n)$: un [monoide](https://en.wikipedia.org/wiki/Monoid)
$(S, \cdot, e)$ y un conjunto $F$ de mapeos $S \to S$ cerrado bajo composición, igual que
[`LazySegmentTree`](SegmentTree/LazySegmentTree.md), **más** las operaciones que un segment tree no
puede hacer: `insert`, `erase`, `reverse`, `rotate`, `move`, `swap_blocks`.

Dada una secuencia de largo $n$, procesa en $O(\log n)$ **esperado**:

- insertar y borrar en cualquier posición,
- aplicar un mapeo $f \in F$ a todos los elementos de un intervalo,
- calcular el producto de un intervalo,
- invertir, rotar, mover e intercambiar intervalos,
- buscar el borde de un intervalo donde un predicado monótono cambia de valor.

**Todos los rangos son cerrados, `[l, r]`, y no pueden ser vacíos.** Los índices son los del
estado **actual**: cualquier `insert` / `erase` corre lo que está a la derecha, y
`rotate` / `move` / `swap_blocks` los reordenan.

| | `vector` | `LazySegmentTree` | `ImplicitTreap` |
|---|---|---|---|
| `prod` / `apply` de rango | $O(n)$ | $O(\log n)$ | $O(\log n)$ |
| `insert` / `erase` | $O(n)$ | **imposible** | $O(\log n)$ |
| `reverse` / `rotate` / `move` | $O(n)$ | **imposible** | $O(\log n)$ |
| constante relativa | 1× | 1× | **1.8×** |

Si no necesitás `insert`/`erase`/`reverse`, usá `LazySegmentTree`: hace lo mismo 1.8× más rápido.

## Contrato del `Node`

Cuatro cosas, y **ninguna es un tamaño** — el árbol conoce todos los largos y los entrega.

| requisito | notas |
|---|---|
| `Node()` | **nunca llega a `operator+`**: el árbol saltea los subárboles vacíos, así que no hace falta identidad ni guardas de rango vacío |
| `a + b` | pliega dos intervalos vecinos, `a` a la **izquierda**. Tiene que ser **asociativo**; no hace falta que conmute ni que tenga inverso |
| `void reverse()` | el agregado leído **al revés**. Vacío si `+` conmuta; `swap(fwd, bwd)` si no |
| `void apply(const LazyUpdate& f, long long len)` | solo con `LazyUpdate`. El árbol pasa `1` para el elemento propio y el tamaño del subárbol para el agregado |

`LazyUpdate` necesita `LazyUpdate()` (el update neutro) y `f *= g` (apila `g` sobre `f`, de modo
que **`g` actúa después de `f`**). Si omitís el segundo argumento del template queda `NoLazy`, que
cuesta **cero bytes** y hace que `apply` no compile con un `static_assert` claro.

> **El `reverse()` es lo que la gente deja mal.** Vacío con un monoide no conmutativo da mal *solo*
> después de una inversión y *solo* en el campo no conmutativo: una suite hecha de sumas no lo caza
> nunca. Y aun con el monoide correcto es esquivo — la versión con el bug coincide en 6 de 7
> lecturas. El único caso que lo destapa es leer un subárbol de **varios** elementos bajo una
> inversión pendiente.

> **La asociatividad importa más que en un segment tree.** Allá la descomposición de `[l, r]` la
> fija la estructura: siempre el mismo paréntesis. Acá el agregado se armó a lo largo de los
> `pull`, en una forma que depende de las prioridades aleatorias — dos sorteos dan **paréntesis
> distintos del mismo producto ordenado**.

**Pool**: $\texttt{max\_nodes}(n, q) = n + q$, con `q` = inserciones esperadas. Pasarse de largo
es gratis; quedarse corto cuesta hasta 1.57× de memoria pico. Los nodos borrados **no se
reciclan**, e `insert(i, v)` cuenta como `|v|` inserciones, no como una.

## Constructor

```cpp
(1) ImplicitTreap<Node, LazyUpdate> t(long long max_ops);
(2) ImplicitTreap<Node, LazyUpdate> t(int len, long long max_ops, F gen);
(3) ImplicitTreap<Node, LazyUpdate> t(const vector<Node>& init, long long max_ops);
```

- (1): vacío, con pool para `max_ops` inserciones.
- (2): largo `len`, con `gen(i)` llamado para `i = 0, 1, ..., len-1` **en ese orden** — así se lee
  de un stream sin armar ningún vector intermedio.
- (3): largo `init.size()`, inicializado con `init`.

**Complejidad**: (1) $O(1)$, (2) y (3) $O(n)$.

## max_nodes / node_bytes

```cpp
static long long ImplicitTreap<Node, LazyUpdate>::max_nodes(long long len, long long max_ops)
static size_t    ImplicitTreap<Node, LazyUpdate>::node_bytes()
```

Cuántos nodos reserva el constructor, y cuánto pesa uno — para presupuestar memoria antes de
instanciar.

**Complejidad**: $O(1)$.

## size / nodes_used

```cpp
int       t.size() const
long long t.nodes_used() const
```

Cuántos elementos hay ahora, y cuánto del pool se consumió.

**Complejidad**: $O(1)$.

## clear

```cpp
void t.clear()
```

Vacía el treap **conservando la capacidad del pool**, así un problema con varios casos de prueba
no vuelve a reservar.

**Complejidad**: $O(1)$.

## insert

```cpp
(1) void t.insert(int pos, Node val)
(2) void t.insert(int pos, const vector<Node>& block)
```

- (1): `val` pasa a ser `a[pos]`; `pos == size()` agrega al final.
- (2): inserta toda la secuencia `block` antes del viejo `a[pos]`, con un solo `merge`.

**Restricciones**: $0 \le pos \le size()$. · **Complejidad**: (1) $O(\log n)$,
(2) $O(|block| + \log n)$.

## push_back / push_front

```cpp
void t.push_back(Node val)
void t.push_front(Node val)
```

Agregan al final y al principio.

**Complejidad**: $O(\log n)$.

## erase

```cpp
(1) void t.erase(int pos)
(2) void t.erase(int l, int r)
```

- (1): quita `a[pos]`.
- (2): borra todo `a[l..r]` de una vez — **plano**, borrar 10 o 100 000 cuesta lo mismo (medido,
  18× más rápido que `erase(i)` repetido), porque solo desconecta el bloque sin recorrerlo.

**Restricciones**: (1) $0 \le pos < size()$; (2) $0 \le l \le r < size()$. ·
**Complejidad**: $O(\log n)$.

## pop_back / pop_front

```cpp
void t.pop_back()
void t.pop_front()
```

Quitan el último y el primero.

**Complejidad**: $O(\log n)$.

## set

```cpp
void t.set(int pos, Node val)
```

`a[pos] = val`.

**Restricciones**: $0 \le pos < size()$. · **Complejidad**: $O(\log n)$.

## get / front / back

```cpp
Node t.get(int pos) const
Node t.front() const
Node t.back() const
```

El `Node` en `pos`, el primero y el último.

**Restricciones**: `get` pide $0 \le pos < size()$; `front` y `back` piden $size() > 0$. ·
**Complejidad**: $O(\log n)$.

## prod

```cpp
Node t.prod(int l, int r) const
```

Devuelve `a[l] + a[l+1] + ... + a[r]`.

**Restricciones**: $0 \le l \le r < size()$. · **Complejidad**: $O(\log n)$.

## all_prod

```cpp
Node t.all_prod() const
```

Devuelve el producto de toda la secuencia.

**Complejidad**: $O(1)$.

## apply

```cpp
(1) void t.apply(int pos, LazyUpdate upd)
(2) void t.apply(int l, int r, LazyUpdate upd)
```

Aplica `upd` a `a[pos]` (1) o a todo `a[l..r]` (2). Necesita `LazyUpdate`.

**Restricciones**: (1) $0 \le pos < size()$; (2) $0 \le l \le r < size()$. ·
**Complejidad**: $O(\log n)$.

## reverse

```cpp
void t.reverse(int l, int r)
```

Da vuelta `a[l..r]`.

**Restricciones**: $0 \le l \le r < size()$. · **Complejidad**: $O(\log n)$.

## rotate

```cpp
void t.rotate(int l, int r, long long shift)
```

Rota `a[l..r]` a la **izquierda** en `shift`: el viejo `a[l+shift]` pasa a ser `a[l]`.

`shift` acepta **cualquier valor** y se normaliza internamente: negativo rota a la derecha, y un
múltiplo del largo no hace nada. O sea que no hace falta escribir `((k % len) + len) % len` en
el llamador, que es donde se olvida el segundo `% len` o se suma antes del módulo y se desborda.

Es `long long` y no `int` **a propósito**: con `int` un valor fuera de rango se estrecha *antes*
de entrar al método, así que la normalización recibiría un número que no es el que escribiste.
La cuenta se hace en `long long`, por lo que no hay desborde posible: como `len ≥ 1`, el resto
cae en $(-len, 0]$ y al sumarle `len` queda en $(0, len]$.

Con `shift` ya en $[0, len)$ equivale a `std::rotate(b+l, b+l+shift, b+r+1)`.

**Restricciones**: $0 \le l \le r < size()$. · **Complejidad**: $O(\log n)$.

## move

```cpp
void t.move(int l, int r, int to)
```

Corta `a[l..r]` y lo pega justo antes del que era `a[to]`.

**Restricciones**: $0 \le l \le r < size()$, y `to` se cuenta sobre el arreglo **original** y tiene
que caer afuera del bloque: $to \le l$ o $to > r$. · **Complejidad**: $O(\log n)$.

## swap_blocks

```cpp
void t.swap_blocks(int l1, int r1, int l2, int r2)
```

Intercambia dos bloques disjuntos, que pueden ser adyacentes y de largos distintos.

**Restricciones**: $0 \le l_1 \le r_1 < l_2 \le r_2 < size()$. · **Complejidad**: $O(\log n)$.

## max_right

```cpp
template <class F> int t.max_right(int l, int r, F pred) const
```

Devuelve el **mayor** $p \in [l, r]$ tal que `pred(prod(l, p))` es cierto, o `l - 1` si ninguno lo
cumple.

**Restricciones**: $0 \le l \le r < size()$, `pred` monótono sobre el rango y sin efectos de lado. ·
**Complejidad**: $O(\log n)$ esperado, **sin escribir nada**.

## min_left

```cpp
template <class F> int t.min_left(int l, int r, F pred) const
```

Devuelve el **menor** $p \in [l, r]$ tal que `pred(prod(p, r))` es cierto, o `r + 1` si ninguno lo
cumple.

**Restricciones**: las mismas, con `pred` monótono al **decrecer** $p$. ·
**Complejidad**: $O(\log n)$ esperado.

## dump / copy_range

```cpp
vector<Node> t.dump() const
vector<Node> t.copy_range(int l, int r) const
```

Toda la secuencia en orden, y los valores de `a[l..r]`. `copy_range` se compone con `insert` para
duplicar un bloque: `t.insert(j, t.copy_range(l, r))`.

**Restricciones**: `copy_range` pide $0 \le l \le r < size()$. ·
**Complejidad**: $O(n)$ y $O(r - l + \log n)$.

---

### Los centinelas

`l - 1` y `r + 1` están elegidos para que el largo del tramo salga **sin un `if`**:
`p - l + 1` y `r - p + 1`. Con el centinela los dos dan $0$, y como el rango es cerrado y no
vacío, el centinela nunca es un índice válido.

### El `p` vale para el estado de **ahora**

Única diferencia real de contrato con los `SegmentTree/`: ahí los índices son estables, acá se
mueven. Guardar un `p` y usarlo después de una mutación es un error que allá no existe, y es fácil
de cometer porque el resultado *parece* algo que se guarda.

### La semilla de las prioridades

Sale **del reloj**, no es fija. Con una semilla fija las prioridades son idénticas en cada corrida,
y un atacante que conoce la secuencia puede elegir las posiciones de `insert` para hacer el árbol
profundo — medido, un hill climbing de 3000 evaluaciones **duplica** la profundidad. Para depurar
con una corrida reproducible, definí `IMPLICIT_TREAP_SEED`.

## Examples

### Solo manipulación: un `vector` con `insert`, `erase` y `reverse` baratos

```cpp
struct NodeSum {
    long long sum = 0;
    NodeSum() {}
    NodeSum(long long x) : sum(x) {}
    friend NodeSum operator+(const NodeSum& a, const NodeSum& b) { return NodeSum(a.sum + b.sum); }
    void reverse() {}                           // la suma conmuta
};

ImplicitTreap<NodeSum> t(a, q);                 // a es vector<NodeSum>, q = inserciones
t.insert(3, NodeSum(7));
t.erase(0, 2);
t.reverse(1, 4);
cout << t.prod(0, t.size() - 1).sum << "\n";
```

### Con update de rango: add y suma

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
    void reverse() {}
    void apply(const LazyAdd& f, long long len) { sum += f.a * len; }   // el largo lo da el arbol
};

ImplicitTreap<NodeSum, LazyAdd> t(a, q);
t.apply(l, r, LazyAdd(v));
t.reverse(l, r);
cout << t.prod(l, r).sum << "\n";
```

Library Checker [Range Reverse Range Sum](https://judge.yosupo.jp/problem/range_reverse_range_sum),
**AC en 303 ms** ([envío 407984](https://judge.yosupo.jp/submission/407984)).

### Monoide NO conmutativo: componer funciones afines

Acá `reverse()` **no** puede quedar vacío: el nodo lleva los dos productos y los intercambia.

```cpp
struct Node {
    long long a = 1, b = 0;                     // x -> a*x + b, leido hacia adelante
    long long ra = 1, rb = 0;                   // el mismo producto leido al reves
    Node() {}
    Node(long long A, long long B) : a(A), b(B), ra(A), rb(B) {}

    friend Node operator+(const Node& x, const Node& y) {   // primero x, despues y
        Node r;
        r.a = y.a * x.a;   r.b = y.a * x.b + y.b;
        r.ra = x.ra * y.ra; r.rb = x.ra * y.rb + x.rb;
        return r;
    }

    void reverse() { swap(a, ra); swap(b, rb); }
};
```

Library Checker
[Dynamic Sequence Range Affine Range Sum](https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum).

### Duplicar un bloque

```cpp
t.insert(j, t.copy_range(l, r));                // O(r - l + log n)
```

### Mover un bloque, rotar, intercambiar

```cpp
t.move(l, r, to);                               // cortar y pegar antes del viejo a[to]
t.rotate(l, r, k);                              // el viejo a[l+k] pasa a ser a[l]
t.rotate(l, r, -1);                             // k negativo rota a la derecha, sin normalizar
t.swap_blocks(l1, r1, l2, r2);                  // l1 <= r1 < l2 <= r2
```

### Primer $j \ge l$ con $a_j \ge x$

El predicado `mx < x` es monótono **siempre**: el máximo de un prefijo no decrece al extenderlo.

```cpp
struct NodeMx {
    ll mx = LLONG_MIN;
    NodeMx() {}
    NodeMx(ll x) : mx(x) {}
    friend NodeMx operator+(const NodeMx& a, const NodeMx& b) { return NodeMx(max(a.mx, b.mx)); }
    void reverse() {}                           // el treap SIEMPRE pide reverse()
};

int p = t.max_right(l, t.size() - 1, [&](const NodeMx& v) { return v.mx < x; });
cout << (p == t.size() - 1 ? -1 : p + 1) << "\n";
```

### Prefijo más largo de $[l, r]$ con suma $\le S$

Necesita valores no negativos, si no la suma no es monótona:

```cpp
int p = t.max_right(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << p - l + 1 << "\n";                      // el largo, sin if: con p == l-1 da 0
```

### $k$-ésimo uno, con `insert` y `erase` de por medio

Con valores 0/1 — y acá el treap se gana el lugar, porque el segment tree no puede insertar:

```cpp
int p = t.max_right(0, t.size() - 1, [&](const NodeSum& v) { return v.sum < k; });
cout << p + 1 << "\n";
t.erase(p + 1);                                 // y lo saco, que el segment tree no puede
```


### Sufijo más largo de $[l, r]$ con suma $\le S$

```cpp
int p = t.min_left(l, r, [&](const NodeSum& v) { return v.sum <= S; });
cout << r - p + 1 << "\n";
```

### Conjunto ordenado con agregados de rango

Esto es lo que `max_right` desbloquea, y **no lo hace ninguna otra estructura del repo**: una
secuencia *ordenada* y dinámica que además responde `prod` de rango. `max_right` ubica la posición
de inserción, así que el orden se mantiene solo.

```cpp
struct NodeSumMx {
    ll sum = 0, mx = LLONG_MIN;                 // Node() nunca llega a operator+ en el treap

    NodeSumMx() {}
    NodeSumMx(ll x) : sum(x), mx(x) {}

    friend NodeSumMx operator+(const NodeSumMx& a, const NodeSumMx& b) {
        NodeSumMx r;
        r.sum = a.sum + b.sum;
        r.mx = max(a.mx, b.mx);
        return r;
    }

    void reverse() {}                           // suma y maximo conmutan
};

using Conjunto = ImplicitTreap<NodeSumMx>;

// Cuantos elementos son < x. Con el centinela da 0 si x va al frente.
int cuantos_menores(const Conjunto& s, ll x) {
    if(s.size() == 0) {
        return 0;
    }

    return s.max_right(0, s.size() - 1, [&](const NodeSumMx& v) { return v.mx < x; }) + 1;
}

void insertar(Conjunto& s, ll x) {
    s.insert(cuantos_menores(s, x), NodeSumMx(x));
}

bool borrar_uno(Conjunto& s, ll x) {
    int p = cuantos_menores(s, x);

    if(p == s.size() || s.get(p).sum != x) {
        return false;                           // x no esta
    }

    s.erase(p);
    return true;
}
```

Y con la secuencia ordenada, de arriba salen gratis:

| consulta | cómo |
|---|---|
| cuántos $< x$ | `cuantos_menores(s, x)` |
| el $k$-ésimo menor | `s.get(k)` |
| suma de los $k$ menores | `s.prod(0, k - 1).sum` |
| el máximo de los $k$ menores | `s.prod(0, k - 1).mx` |

Un `multiset` hace el insert y el erase, pero **no** te da la suma de los $k$ menores.
