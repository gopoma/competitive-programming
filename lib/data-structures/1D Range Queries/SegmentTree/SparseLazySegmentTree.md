# SparseLazySegmentTree

Segment tree **con propagación perezosa** sobre un universo de hasta 10¹⁸. Combina el universo gigante de [`SparseSegmentTree`](SparseSegmentTree.md) con el update de rango de [`LazySegmentTree`](LazySegmentTree.md).

Es el único de la familia cuyo `Node` usa **`apply(f, len)`** en vez de `operator*=`, y eso no es un capricho: está explicado abajo.

Convenciones, contrato del `Node`/`LazyUpdate`, el pool y el monoide de ejemplo: [README.md](README.md).

## Antes de usarlo: el aviso es más fuerte que en el sparse sin lazy

Un `apply` de rango cuesta **~150 nodos** a `n = 10¹⁸`. Con `q = 10⁶` eso son **~9 GB**: no entra en ningún juez. Lo medí y el proceso paginó.

Si un problema realmente pide eso, la salida es **comprimir coordenadas y usar `LazySegmentTree`**: 10⁶ consultas dan a lo sumo 2·10⁶ extremos, y el denso lo resuelve en ~88 MB.

El sparse lazy sirve para `q` moderado (≲ 10⁵) sobre un universo que no podés comprimir.

## API

```cpp
SparseLazySegmentTree<Node, LazyUpdate> st(n, q)
```

No hay `build`: arranca vacío.

| método | costo | qué hace |
|---|---|---|
| `st.set(p, x)` | O(log n) | `a[p] = x` |
| `st.apply(p, f)` | O(log n) | `f` sobre `a[p]` |
| `st.apply(l, r, f)` | O(log n) | `f` sobre `a[l..r]` |
| `st.get(p)` | O(log n) | el `Node` en `p` |
| `st.prod(l, r)` | O(log n) | pliega `a[l..r]` |
| `st.all_prod()` | **O(1)** | pliega todo el universo |
| `st.size()` | O(1) | `n` |
| `st.max_right(l, r, f)` | O(log n) | mayor `p` con `f(prod(l, p))`, o `l - 1` |
| `st.min_left(l, r, f)` | O(log n) | menor `p` con `f(prod(p, r))`, o `r + 1` |
| `st.nodes_used()` | O(1) | cuánto del pool se consumió |
| `st.dump()` | O(n) | vuelca el universo entero, para depurar |

## Por qué `apply(f, len)` y no `operator*=`

En los lazy densos el nodo conoce su propio largo, porque existe. Acá **un subárbol que nadie materializó no tiene forma de saber cuántas posiciones cubre** — pero el árbol sí, y se lo pasa:

```cpp
void apply(const Upd& f, ll len) {
    sz = len;                                    // FIJA, no suma
    ...
}
```

Ese `sz = len` (fijar, no acumular) es la parte que se presta a confusión. La distinción es:

| | significa |
|---|---|
| `Node()` sola | **ninguna** posición: el rango vacío, la identidad de `+` |
| `apply(f, len)` sobre `Node()` | **`len` posiciones** que nunca fueron tocadas |

Son dos cosas distintas y el `sz` es lo que las separa. Si `apply` sumara a `sz` en vez de fijarlo, un subárbol no materializado reportaría largo cero y los agregados que escalan con el largo saldrían mal.

> Lo probé al revés para estar seguro: saqué el `sz` del `Node`, y `prod(0, 0)` devolvía `mn = 0` en vez de 3, porque el caso disjunto devuelve `Node()` y sin `sz` no hay forma de distinguirlo de «una posición cuyo valor es 0». El `sz` es necesario, y `apply` tiene que fijarlo.

Mismo contrato que usa [`../ImplicitTreap.h`](../ImplicitTreap.md), por la misma razón.

## El `push` materializa los dos hijos

Cuando un `apply` parcial llega a un nodo, `push` tiene que **materializar los dos hijos aunque estén vacíos**: lo pendiente tiene que quedar guardado en algún lado. De ahí sale el factor 4 de la fórmula del pool — hasta cuatro nodos por nivel en vez de uno.

La lectura, en cambio, **no materializa nada**: `prod` lleva lo pendiente en una variable local, igual que el persistente lazy.

## Memoria

```
max_nodes(n, q) = 4 * (ceil(log2 n) + 1) * q + 1
```

Pesimista dos veces (un update sobre nodos ya materializados no crea ninguno, y los nodos cerca de la raíz los comparten todos los caminos), pero el `apply` de rango es genuinamente caro.

Medido con un `Node` de 32 bytes y un `LazyUpdate` de 24, o sea 64 por nodo interno:

| n | q | nodos usados | estructura | pico | `q` applies | `q` prods |
|---|---|---|---|---|---|---|
| 200 000 | 200 000 | 379 113 | 23.1 MB | 30.8 MB | 0.213 s | 0.208 s |
| 10⁹ | 200 000 | 8 344 955 | 509.3 MB | 517.0 MB | 0.668 s | 0.599 s |
| **10¹⁸** | 25 000 | 4 336 163 | 264.7 MB | 269.7 MB | 0.163 s | 0.120 s |
| 10¹⁸ | 100 000 | 16 540 727 | 1009.6 MB | 1015.8 MB | 0.668 s | 0.543 s |
| 10¹⁸ | 10⁶ | 152 095 887 | **9283.2 MB** | 8527.4 MB | 17.3 s | 34.4 s |

A 256 MB el techo es `q ≈ 2.7·10⁴` con `n = 10¹⁸`. Esa última fila es la que hay que mirar antes de elegir esta estructura: los 17 y 34 segundos son **paginación**, no algoritmo — el pico medido (8527 MB) sale menor que la memoria de los nodos (9283 MB) justamente porque el sistema no pudo mantenerlos residentes.

## Ejemplo

Suma, máximo y mínimo con assign y add de rango, coordenadas hasta 10¹⁸ (el `Upd` está en el [README](README.md#b-suma-máximo-y-mínimo-con-assign-y-add-de-rango); el `Node` es la variante con `apply(f, len)` que figura ahí mismo):

```cpp
const ll N = 1000000000000000000LL;
int q; cin >> q;
SparseLazySegmentTree<Node, Upd> st(N, q);
while (q--) {
    int type; ll l, r; cin >> type >> l >> r;
    if (type == 1) { ll v; cin >> v; st.apply(l, r, Upd::assign(v)); }
    else if (type == 2) { ll v; cin >> v; st.apply(l, r, Upd::add(v)); }
    else { Node res = st.prod(l, r);
           cout << res.sum << " " << res.mx << " " << res.mn << "\n"; }
}
```

Las posiciones intactas cuentan como ceros y salen bien solas: un rango sin nodos debajo llega como `Node()` y `apply` lo convierte en `len` posiciones reportando suma 0, máximo 0 y mínimo 0. **Si tu problema necesita otro valor por defecto, asignalo sobre todo el universo antes que nada.**

# Los dos descensos

$$
\texttt{max\_right}(\dots,l,r,f) \;=\; \max\{\, p \in [l,r] \;:\; f(\text{prod}(l,p)) \,\}, \qquad l-1 \text{ si es vacío}
$$

$$
\texttt{min\_left}(\dots,l,r,f) \;=\; \min\{\, p \in [l,r] \;:\; f(\text{prod}(p,r)) \,\}, \qquad r+1 \text{ si es vacío}
$$

`max_right` ancla en $l$ y acumula **prefijos**; `min_left` ancla en $r$ y acumula **sufijos**. Los centinelas, el requisito de monotonía de $f$ y la tabla de predicados están en el [README](README.md#los-dos-descensos) y desarrollados con ejemplos en [SegmentTree.md](SegmentTree.md#los-dos-descensos).

**El centinela, en corto:** si $f$ falla ya en el primer elemento, `max_right` devuelve $l-1$ y `min_left` devuelve $r+1$. Los dos **pueden ser índices válidos**, así que el chequeo es `p == l - 1`, nunca `p < 0`. Y el largo del tramo sale sin ramas: $p-l+1$ y $r-p+1$.

## El descenso lleva el lazy y le pide el largo al árbol

Dos cosas se juntan acá. El lazy pendiente baja como parámetro (nada de `push`, así el descenso no materializa nodos y es `const`), y el agregado de un nodo cubierto se arma con

```cpp
Node pieza = st[cur].val;
pieza.apply(g, rx - lx + 1);             // el arbol es el que sabe cuantas posiciones cubre
```

Es el mismo contrato que `prod`: **el árbol es la autoridad sobre el largo**, porque un subárbol sin materializar no sabe cuántas posiciones abarca. Por eso `apply` **fija** `sz = len` en vez de sumarle.

A diferencia del sparse sin lazy, acá sí podés hacer que todo el universo cuente como posiciones reales, con un `apply` que lo materialice:

```cpp
const ll N = 1000000000000000000LL;
SparseLazySegmentTree<CntLen, LazyUpdate> t(N, 20);
t.apply(0, N - 1, LazyUpdate::assign(0));      // 1e18 posiciones en 0, de una
t.apply(10, 19, LazyUpdate::assign(1));        // diez unos
t.apply(1000, 1004, LazyUpdate::assign(2));    // cinco dos
// nodes_used = 147,  prod(0, N-1).sum = 20
```

| `sum <= S` | `max_right(0, N-1, ...)` | por qué |
|---|---|---|
| $S = 0$ | 9 | $[0,9]$ son todos cero; en 10 arranca el primer uno |
| $S = 5$ | 14 | cinco unos: $[10,14]$ |
| $S = 10$ | 999 | los diez unos, y después ceros hasta 999 |
| $S = 14$ | 1 001 | $10 + 2\cdot2 = 14$ |
| $S = 20$ | 999 999 999 999 999 999 $= r$ | el total es 20, aguanta todo |

```
min_left(0, N-1, sum <= 0) = 1005        <- el sufijo de ceros arranca justo despues del ultimo dos
```

Fijate en la fila de $S = 10$: la respuesta es 999 y no 19, porque extender sobre los ceros de $[20, 999]$ no cambia la suma. El descenso devuelve **la mayor** posición que cumple, y eso incluye toda la cola de ceros.

## `dump()`: ver el estado para depurar

Devuelve el arreglo lógico completo como un `vector`, con tres propiedades que valen en los seis templates de la familia:

$$
\texttt{dump()}[i] = \texttt{get}(i), \qquad
\textstyle\bigoplus \texttt{dump()} = \texttt{all\_prod()}, \qquad
\textstyle\bigoplus_{i=l}^{r} \texttt{dump()}[i] = \texttt{prod}(l,r)
$$

Devuelve **`n` elementos, no `SZ`**: el relleno $[n, SZ)$ no es parte del arreglo lógico. (Con el constructor de un argumento `t(k)` resulta $n = SZ$, así que ahí el relleno *sí* aparece — porque en ese caso es el arreglo.)

Es el mismo nombre y el mismo contrato que [`ImplicitTreap::dump()`](../ImplicitTreap.md).

Las posiciones sin materializar vuelven como `Node()` con `apply(f, 1)` encima — una sola posición, igual que haría `get`. Y rige el mismo tope de $10^7$ que en el sparse sin lazy, porque `n` puede valer $10^{18}$.

**Acá el carry no es opcional.** El `push` de este template **materializa los dos hijos**, así que un `dump` que empujara crearía nodos y podría reventar el pool. Bajando el lazy como parámetro, el dump no toca el pool: verificado con `nodes_used()` antes y después.

## Verificación

- Contra fuerza bruta: **69 440 rangos** sobre `n = 1..30` con assign y add mezclados, verificando suma, máximo y mínimo a la vez, junto con `LazySegmentTree` y `PersistentLazySegmentTree` usando el mismo par.
- A `n = 10¹⁸`, ocho propiedades contra fórmula cerrada: assign global, add a media mitad, assign al centro, y `prod`/`get` sobre cada región. Con 123 nodos usados — que es el otro punto: a esa escala, unas pocas operaciones de rango sobre rangos gigantes casi no cuestan nodos.

**Sin link de juez todavía.**

### Los descensos

| test | comprobaciones |
|---|---|
| el descenso contra fuerza bruta, con `apply(f, len)` | 37 618 consultas |
| el descenso con `Node` **no conmutativo** (tramo ordenado) | 32 116 consultas |

Cuatro controles negativos, los cuatro cazados por la suite: invertir el orden de `+` en `min_left`, podar sin chequear si el predicado rompe, no componer el lazy que baja, y pasarle a `apply` un largo fijo en vez del largo del nodo. El primero **solo** lo detecta un `Node` no conmutativo — con sumas pasa inadvertido, y de hecho mi primera versión del test no lo cazaba.

### `dump()`

| test | comprobaciones |
|---|---|
| `dump()` con `apply(f, 1)`, pool intacto | 381 195 |

Diez controles negativos sobre los seis, los diez cazados por la suite: dar vuelta el vector, devolver `SZ` en vez de `n`, sacar el `push` de `LazySegmentTree`, invertirle el orden, visitar los hijos al revés, invertir la composición del lazy que baja, no aplicar el lazy en la hoja, y pasarle a `apply` un largo distinto de 1.
