# PersistentLazySegmentTree

Segment tree persistente **con propagación perezosa**: cada `set` y cada `apply` devuelven la raíz de una versión nueva. Combina las versiones de [`PersistentSegmentTree`](PersistentSegmentTree.md) con el update de rango de [`LazySegmentTree`](LazySegmentTree.md), y es el más caro de la familia en memoria.

Convenciones, contrato del `Node`/`LazyUpdate`, el pool y el monoide de ejemplo: [README.md](README.md).

## API

```cpp
PersistentLazySegmentTree<Node, LazyUpdate> st(n, q)
vector<int> roots = {st.build(a)};
```

| método | costo | nodos nuevos | qué hace |
|---|---|---|---|
| `st.build(a)` | O(n) | `2n − 1` | raíz de la versión inicial |
| `st.build()` | **O(1)** | **0** | raíz de la versión todo-`Node()` |
| `st.set(root, p, x)` | O(log n) | `2C + 1` | raíz nueva, `a[p] = x` |
| `st.apply(root, p, f)` | O(log n) | `2C + 1` | raíz nueva, `f` sobre `a[p]` |
| `st.apply(root, l, r, f)` | O(log n) | `4C − 1` | raíz nueva, `f` sobre `a[l..r]` |
| `st.copy(root)` | **O(1)** | **1** | duplica una versión |
| `st.get(root, p)` | O(log n) | **0** | el `Node` en `p` |
| `st.prod(root, l, r)` | O(log n) | **0** | pliega `a[l..r]` |
| `st.all_prod(root)` | **O(1)** | **0** | pliega todo |
| `st.nodes_used()` | O(1) | — | cuánto del pool se consumió |

con `C = ceil(log2 n)`.

## Lo que hace que la persistencia funcione: las lecturas no escriben

En un lazy segment tree normal, una consulta **baja** los lazy pendientes del camino — o sea, escribe. Si hiciera eso acá, modificaría nodos compartidos con versiones viejas y las corrompería.

Entonces `get` y `prod` llevan lo pendiente **en una variable local** y nunca tocan el árbol:

```cpp
LazyUpdate down = st[cur].lz;
down *= f;                     // el lz del nodo primero, el carry despues
```

**El orden de esa composición es de hoja a raíz, y es crítico.** Lo tuve al revés y los tests pasaban igual, porque el lazy que estaba probando era aditivo y la suma conmuta. Con un lazy de assign+add el orden correcto da 16400 lecturas bien y el invertido falla. Es el mismo tipo de bug que el `f *= g` del README, pero del lado de la lectura.

Esa es también la razón de que esta estructura sea más caro por operación que la no persistente: `set` cuesta `2C + 1` nodos en vez de `C + 1`, porque el descenso tiene que clonar y bajar el lazy a la vez.

## Memoria

```
max_nodes(n, q) = 2n + 4 * (ceil(log2 n) + 1) * q + 1
```

Pesimista: asume que **cada** consulta es un `apply` de rango, que es la más cara, y cubre **un** `build`.

Y acá la cota es **ajustada**, no holgada: en la carga donde todas las consultas son `apply` de rango usó **84% de su cota**. Esta es la estructura de la familia donde más vale estimar bien.

Medido con un `Node` de 32 bytes y un `LazyUpdate` de 24, o sea 64 bytes por nodo interno:

| n | q | nodos usados | estructura | pico | build | `q` applies | `q` prods |
|---|---|---|---|---|---|---|---|
| 200 000 | 50 000 | 3 588 745 | 219.0 MB | 224.7 MB | 0.008 s | 0.124 s | 0.189 s |
| 200 000 | 200 000 | 13 152 143 | 802.7 MB | 812.3 MB | 0.009 s | 0.571 s | 0.883 s |
| 1 000 000 | 50 000 | 5 638 907 | 344.2 MB | 349.8 MB | 0.043 s | 0.191 s | 0.263 s |

**A 256 MB el techo es `q ≈ 6·10⁴` con `n = 2·10⁵`** (unos 66 nodos por `apply` de rango). Es un orden de magnitud menos `q` que la versión sin lazy, y la razón es directa: un `apply` de rango cuesta 3–4× lo que un `set`.

El tiempo nunca es el problema: en ninguna configuración que entre en RAM se acerca a 1 s.

## Cuidado con `build()` sin argumentos

Como un update **tiene que dejar `Node()` quieta** (ver el [contrato](README.md#node--f-los-dos-lazy-densos)), aplicar sobre la versión que devuelve `build()` **no hace nada**. Es correcto y es coherente, pero no es lo que querés casi nunca.

Para valores reales arrancá de `build(vector<Node>(n, Node(0)))`.

## Ejemplo

Una lista de arreglos con suma, máximo y mínimo por rango, y dos clases de update de rango por arreglo, más clonar (el `Node` y el `Upd` están en el [README](README.md#b-suma-máximo-y-mínimo-con-assign-y-add-de-rango)):

```cpp
int n, q; cin >> n >> q;
vector<Node> a(n);
for (Node& x : a) { ll t; cin >> t; x = Node(t); }
PersistentLazySegmentTree<Node, Upd> st(n, q);
vector<int> roots = {st.build(a)};
while (q--) {
    int type, k; cin >> type >> k; k--;
    if (type == 4) { roots.push_back(st.copy(roots[k])); continue; }
    int l, r; cin >> l >> r; l--, r--;
    if (type == 1) { ll v; cin >> v; roots[k] = st.apply(roots[k], l, r, Upd::assign(v)); }
    else if (type == 2) { ll v; cin >> v; roots[k] = st.apply(roots[k], l, r, Upd::add(v)); }
    else { Node res = st.prod(roots[k], l, r);
           cout << res.sum << " " << res.mx << " " << res.mn << "\n"; }
}
```

Esta es la forma que **más estresa el pool**, porque el `apply` de rango es la operación más cara de todas.

## Verificación

- Contra fuerza bruta: **69 440 rangos** sobre `n = 1..30` con assign y add mezclados, verificando suma, máximo y mínimo a la vez, junto con `LazySegmentTree` y `SparseLazySegmentTree` usando el mismo par.
- **131 560 rangos** leídos desde **todas** las versiones, ramificando desde raíces arbitrarias.

El segundo es el que caza los errores propios de esta estructura: una lectura que escribiera, o un carry compuesto en el orden equivocado, puede dar bien sobre la versión actual y mal sobre las viejas.

**Sin link de juez todavía.**
