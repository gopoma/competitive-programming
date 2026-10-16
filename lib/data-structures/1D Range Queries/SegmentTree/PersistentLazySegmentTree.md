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
| `st.set(root, pos, val)` | O(log n) | `2C + 1` | raíz nueva, `a[p] = x` |
| `st.apply(root, pos, upd)` | O(log n) | `2C + 1` | raíz nueva, `f` sobre `a[p]` |
| `st.apply(root, l, r, upd)` | O(log n) | `4C − 1` | raíz nueva, `f` sobre `a[l..r]` |
| `st.copy(root)` | **O(1)** | **1** | duplica una versión |
| `st.get(root, pos)` | O(log n) | **0** | el `Node` en `p` |
| `st.prod(root, l, r)` | O(log n) | **0** | pliega `a[l..r]` |
| `st.all_prod(root)` | **O(1)** | **0** | pliega todo |
| `st.max_right(root, l, r, pred)` | O(log n) | **0** | mayor `p` con `f(prod(l, p))`, o `l - 1` |
| `st.min_left(root, l, r, pred)` | O(log n) | **0** | menor `p` con `f(prod(p, r))`, o `r + 1` |
| `st.nodes_used()` | O(1) | — | cuánto del pool se consumió |
| `st.dump(root)` | O(n) | **0** | vuelca esa versión entera, para depurar |

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

# Los dos descensos

$$
\texttt{max\_right}(\dots,l,r,f) \;=\; \max\{\, p \in [l,r] \;:\; f(\text{prod}(l,p)) \,\}, \qquad l-1 \text{ si es vacío}
$$

$$
\texttt{min\_left}(\dots,l,r,f) \;=\; \min\{\, p \in [l,r] \;:\; f(\text{prod}(p,r)) \,\}, \qquad r+1 \text{ si es vacío}
$$

`max_right` ancla en $l$ y acumula **prefijos**; `min_left` ancla en $r$ y acumula **sufijos**. Los centinelas, el requisito de monotonía de $f$ y la tabla de predicados están en el [README](README.md#los-dos-descensos) y desarrollados con ejemplos en [SegmentTree.md](SegmentTree.md#los-dos-descensos).

**El centinela, en corto:** si $f$ falla ya en el primer elemento, `max_right` devuelve $l-1$ y `min_left` devuelve $r+1$. Los dos **pueden ser índices válidos**, así que el chequeo es `p == l - 1`, nunca `p < 0`. Y el largo del tramo sale sin ramas: $p-l+1$ y $r-p+1$.

## El lazy viaja como parámetro, no se hace `push`

Acá está la particularidad. En el denso el descenso hace `push` y escribe; sobre una versión persistente **eso sería corromper el pasado**. Entonces el lazy pendiente baja como argumento, exactamente como lo hace `prod`:

```cpp
LazyUpdate down = st[cur].lz;
down *= g;                               // g es lo que vino de arriba
```

y el agregado de un nodo cubierto se lee en una copia local con `pieza *= g`. Resultado: el descenso es **`const`** y consume **0 nodos** del pool. Es la misma propiedad que hace que las lecturas no inventen versiones.

```cpp
PersistentLazySegmentTree<Node, LazyUpdate> t(8, 20);
int v0 = t.build(iv);                                      // {3,1,4,1,5,9,2,6}
int v1 = t.apply(v0, 2, 5, LazyUpdate::add(10));            // {3,1,14,11,15,19,2,6}
int v2 = t.apply(v1, 0, 3, LazyUpdate::assign(7));          // {7,7,7,7,15,19,2,6}
```

| `sum <= S` | en `v0` | en `v1` | en `v2` |
|---|---|---|---|
| $S = 0$ | $-1$ *(centinela)* | $-1$ | $-1$ |
| $S = 8$ | 2 | 1 | 0 |
| $S = 28$ | 6 | 2 | 3 |
| $S = 1000$ | 7 | 7 | 7 |

Y una de las cuatro variantes de umbral sobre la versión más nueva:

```
'ninguno > 7' en v2:  max_right(v2, 0, 7, mx <= 7) = 3     (a[0..3] = 7, a[4] = 15 rompe)
nodes_used = 25   <- el descenso no clono nada
```

Las tres filas de `S = 8` muestran lo que se gana: la misma pregunta contra tres estados históricos del arreglo, sin reconstruir ninguno.

## `dump()`: ver el estado para depurar

Devuelve el arreglo lógico completo como un `vector`, con tres propiedades que valen en los seis templates de la familia:

$$
\texttt{dump()}[i] = \texttt{get}(i), \qquad
\textstyle\bigoplus \texttt{dump()} = \texttt{all\_prod()}, \qquad
\textstyle\bigoplus_{i=l}^{r} \texttt{dump()}[i] = \texttt{prod}(l,r)
$$

Devuelve **`n` elementos, no `SZ`**: el relleno $[n, SZ)$ no es parte del arreglo lógico. (Con el constructor de un argumento `t(k)` resulta $n = SZ$, así que ahí el relleno *sí* aparece — porque en ese caso es el arreglo.)

Es el mismo nombre y el mismo contrato que [`ImplicitTreap::dump()`](../ImplicitTreap.md).

El root entra por parámetro, así que volcás cualquier versión, y **no consume pool** (verificado con `nodes_used()` antes y después).

No se puede hacer `push`: la versión es de solo lectura y empujar la corrompería. El lazy pendiente viaja como parámetro, con la misma composición que usan `prod` y los dos descensos:

```cpp
LazyUpdate down = st[cur].lz;
down *= f;                                   // el lz del nodo primero, el carry despues
```

```cpp
for (int ver = 0; ver < (int)roots.size(); ver++) {
    cerr << "v" << ver << ":";
    for (const Node& x : st.dump(roots[ver])) cerr << " " << x.sum;
    cerr << "\n";
}
```

## Verificación

- Contra fuerza bruta: **69 440 rangos** sobre `n = 1..30` con assign y add mezclados, verificando suma, máximo y mínimo a la vez, junto con `LazySegmentTree` y `SparseLazySegmentTree` usando el mismo par.
- **131 560 rangos** leídos desde **todas** las versiones, ramificando desde raíces arbitrarias.

El segundo es el que caza los errores propios de esta estructura: una lectura que escribiera, o un carry compuesto en el orden equivocado, puede dar bien sobre la versión actual y mal sobre las viejas.

**Sin link de juez todavía.**

### Los descensos

| test | comprobaciones |
|---|---|
| el descenso sobre todas las versiones, con el lazy de parámetro | 31 956 consultas |
| el descenso con `Node` **no conmutativo** (tramo ordenado) | 40 296 consultas |

Cuatro controles negativos, los cuatro cazados por la suite: invertir el orden de `+` en `min_left`, podar sin chequear si el predicado rompe, no componer el lazy que baja, y pasarle a `apply` un largo fijo en vez del largo del nodo. El primero **solo** lo detecta un `Node` no conmutativo — con sumas pasa inadvertido, y de hecho mi primera versión del test no lo cazaba.

### `dump()`

| test | comprobaciones |
|---|---|
| `dump(root)` sobre **16 800 versiones vivas**, pool intacto | 575 302 |

Diez controles negativos sobre los seis, los diez cazados por la suite: dar vuelta el vector, devolver `SZ` en vez de `n`, sacar el `push` de `LazySegmentTree`, invertirle el orden, visitar los hijos al revés, invertir la composición del lazy que baja, no aplicar el lazy en la hoja, y pasarle a `apply` un largo distinto de 1.
