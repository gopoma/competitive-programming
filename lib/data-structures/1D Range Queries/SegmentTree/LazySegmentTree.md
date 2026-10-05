# LazySegmentTree

Segment tree con propagación perezosa: **update de rango y consulta de rango**. El caballo de batalla de la familia. Algoritmo tomado del `lazy_segtree` de la AtCoder Library, con las máscaras de bajada adaptadas a rangos inclusivos.

Convenciones, contrato del `Node`/`LazyUpdate` y monoides de ejemplo: [README.md](README.md).

## API

```cpp
LazySegmentTree<Node, LazyUpdate> t(v)   // n = v.size(), SZ = n redondeado a potencia de dos
LazySegmentTree<Node, LazyUpdate> t(k)   // sin vector: n pasa a ser SZ, con Node() en cada lugar
```

| método | costo | qué hace |
|---|---|---|
| `t.set(p, x)` | O(log n) | `a[p] = x` |
| `t.get(p)` | O(log n) | el `Node` que está en `p` |
| `t.apply(p, f)` | O(log n) | `f` sobre `a[p]` |
| `t.apply(l, r, f)` | O(log n) | `f` sobre todo `a[l..r]` |
| `t.prod(l, r)` | O(log n) | pliega `a[l..r]` |
| `t.all_prod()` | **O(1)** | pliega todo |
| `t.query(l, r)` | O(log n) | la misma respuesta que `prod`, pero recursiva |

Build en O(n).

El `get` es O(log n), no O(1) como en `SegmentTree`: antes de leer `seg[SZ + p]` hay que bajar los lazy pendientes de todo el camino desde la raíz. Está adaptado del `get` de la AtCoder Library.

### Para qué está `query` si ya está `prod`

`prod` es el bucle ascendente, que es el rápido y el que vas a usar. `query` es la versión **recursiva** de la misma respuesta, y está ahí como **plantilla para editar**: cuando necesitás navegar el árbol buscando un índice dentro de `[l, r]` —el primer elemento ≥ x, el k-ésimo que cumple algo— lo que querés es un descenso recursivo, y lo escribís modificando `query`, no `prod`.

Esa es también la razón de que no haya `max_right` ni `min_left` (regla 3): esas búsquedas son demasiado específicas de cada problema para que valga la pena una firma genérica. `query` te da el esqueleto.

## El `push` es incondicional, y es a propósito

En `split`, `merge` y los descensos, el `push` baja el lazy **siempre**, sin chequear si es la identidad. Eso no es un descuido.

Lo probé reordenando el chequeo de disjunto para evitar algunos `push`: **4602 de 5000 sumas y 2237 de 5000 mínimos salieron mal**. El `push` sin condición es lo que mantiene el invariante de que el agregado de un nodo ya tiene aplicado su propio lazy mientras lo pendiente es solo para los hijos. Sacarlo rompe el invariante, no ahorra trabajo.

## Ejemplo

Suma, máximo y mínimo de `a[l..r]`, con assign y add de rango (el `Node` y el `Upd` están en el [README](README.md#b-suma-máximo-y-mínimo-con-assign-y-add-de-rango)):

```cpp
int n, q; cin >> n >> q;
vector<Node> a(n);
for (Node& x : a) { ll t; cin >> t; x = Node(t); }
LazySegmentTree<Node, Upd> st(a);
while (q--) {
    int type, l, r; cin >> type >> l >> r;
    if (type == 1) { ll v; cin >> v; st.apply(l, r, Upd::assign(v)); }
    else if (type == 2) { ll v; cin >> v; st.apply(l, r, Upd::add(v)); }
    else { Node res = st.prod(l, r);
           cout << res.sum << " " << res.mx << " " << res.mn << "\n"; }
}
```

Ese `Upd` combinado es el que importa: assign y add **no conmutan**, así que es el caso que caza un `f *= g` con el orden invertido. Con un lazy puramente aditivo el error pasa desapercibido.

## Qué le pide a tu monoide

Más allá de la asociatividad de `+`, el lazy exige **distributividad**:

```
(a ⊙ b) ⊗ f  =  (a ⊗ f) ⊙ (b ⊗ f)
```

Si tu update no distribuye sobre tu agregado, no hay forma de escribir `operator*=` que funcione — el problema no es la implementación, es que la operación no es compatible con la propagación perezosa.

## Memoria

`2 · SZ` nodos más `SZ` lazy, sin pool ni `reserve`.

| n | q | build | `q` applies | `q` prods | memoria |
|---|---|---|---|---|---|
| 200 000 | 200 000 | 0.008 s | 0.112 s | 0.083 s | 22.0 MB |
| 1 000 000 | 1 000 000 | 0.033 s | 0.886 s | 0.798 s | 88.0 MB |

(con el `Node` de 4 campos y el `Upd` de 3 del ejemplo)

Para dimensionar: en la carga de afín de rango más suma de rango a `n = q = 5·10⁵` tarda **0.37 s** con `-O2 -march=native`. Eso es la referencia contra la que se mide [`ImplicitTreap`](../ImplicitTreap.md), que hace lo mismo 1.8× más lento a cambio de poder insertar y borrar.

## Verificación

- **Codeforces EDU (ITMO), dos problemas aceptados**: *Assignment and Maximal Segment* y *Addition and First element at least X*. Es el único de la familia con jueces de verdad. (Los links no están en el header; si los tenés a mano conviene agregarlos.)
- Estresado contra fuerza bruta: **69 440 rangos** sobre `n = 1..30` con assign y add mezclados, verificando suma, máximo y mínimo a la vez, junto con `PersistentLazySegmentTree` y `SparseLazySegmentTree` usando el mismo par.
- Contrastado contra el `lazy_segtree` de la AtCoder Library en los casos borde que su documentación enumera (`n = 10⁸` para las operaciones O(n), `n = 5·10⁶` para las O(log n)): rendimiento equivalente, diferencias dentro del ruido.
