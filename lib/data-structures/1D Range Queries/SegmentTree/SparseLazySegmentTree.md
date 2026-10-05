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
| `st.nodes_used()` | O(1) | cuánto del pool se consumió |

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

## Verificación

- Contra fuerza bruta: **69 440 rangos** sobre `n = 1..30` con assign y add mezclados, verificando suma, máximo y mínimo a la vez, junto con `LazySegmentTree` y `PersistentLazySegmentTree` usando el mismo par.
- A `n = 10¹⁸`, ocho propiedades contra fórmula cerrada: assign global, add a media mitad, assign al centro, y `prod`/`get` sobre cada región. Con 123 nodos usados — que es el otro punto: a esa escala, unas pocas operaciones de rango sobre rangos gigantes casi no cuestan nodos.

**Sin link de juez todavía.**
