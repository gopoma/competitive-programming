# SegmentTree

Segment tree clásico: **set en un punto, consulta de rango**. El más simple y el más rápido de la familia; si no necesitás update de rango, versiones ni `n` gigante, es este.

Convenciones, contrato del `Node` y monoides de ejemplo: [README.md](README.md).

## API

```cpp
SegmentTree<T> t(v)    // n = v.size(), SZ = n redondeado a potencia de dos
SegmentTree<T> t(k)    // sin vector: n pasa a ser SZ, con T() en cada lugar
```

| método | costo | qué hace |
|---|---|---|
| `t.set(p, x)` | O(log n) | `a[p] = x` |
| `t.get(p)` | **O(1)** | la `T` que está en `p` |
| `t.prod(l, r)` | O(log n) | pliega `a[l..r]` |
| `t.all_prod()` | **O(1)** | pliega todo el arreglo |

Build en O(n). Los nodos internos son 1-indexados: la raíz es `1` y los hijos de `x` son `2x` y `2x+1`.

El `get` es O(1) porque el elemento `p` vive literalmente en `seg[SZ + p]` — no hay nada que bajar. Es la única estructura de la familia donde eso vale; en `LazySegmentTree` el `get` es O(log n) porque antes hay que resolver los lazy pendientes del camino.

## Ojo con el constructor de un argumento

`SegmentTree<T> t(k)` **no** te da `k` elementos: te da `SZ` elementos, con `SZ` la potencia de dos que cubre `k`, y todos valen `T()` — el **neutro**, no el cero de tu problema.

Si querés `k` ceros de verdad, usá `SegmentTree<T>(vector<T>(k, T(0)))`. La diferencia importa cuando `T()` y `T(0)` no son lo mismo, que es justo el caso del monoide del ejemplo (`sz = 0` contra `sz = 1`).

## Ejemplo

Máxima suma de un subarreglo de `a[l..r]`, con el vacío permitido (el `Node` está en el [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido)):

```cpp
int n, q; cin >> n >> q;
vector<Node> a(n);
for (Node& x : a) { ll t; cin >> t; x = Node(t); }
SegmentTree<Node> st(a);
while (q--) {
    int type; cin >> type;
    if (type == 1) { int p; ll x; cin >> p >> x; st.set(p, Node(x)); }
    else { int l, r; cin >> l >> r; cout << st.prod(l, r).best << "\n"; }
}
```

## Memoria

`2 · SZ` nodos, sin pool ni `reserve`: el tamaño se conoce desde el constructor. Con `SZ` la potencia de dos que cubre `n`, el peor caso es `SZ = 2n − 2`, o sea hasta **4n** nodos cuando `n` queda justo arriba de una potencia de dos.

| n | q | tiempo build | `q` sets | `q` prods | memoria de la estructura |
|---|---|---|---|---|---|
| 200 000 | 200 000 | 0.007 s | 0.037 s | 0.048 s | 20.0 MB |
| 1 000 000 | 1 000 000 | 0.027 s | 0.409 s | 0.386 s | 80.0 MB |

(con el `Node` de 5 campos del ejemplo, 40 bytes cada uno)

## Reasignar el neutro

Si `T` es un tipo primitivo como `int`, `T()` es `0` y no lo podés cambiar — y para un mínimo de rango querrías `+infinito`. No hay forma de inyectar un neutro distinto: **envolvelo en un struct**. Eso es lo que la regla 2 de la familia pide de todas formas, y cuesta cuatro líneas:

```cpp
struct Mn {
    ll v = LLONG_MAX;                            // el neutro del minimo
    Mn() {}
    Mn(ll x) : v(x) {}
    friend Mn operator+(const Mn& a, const Mn& b) { return Mn(min(a.v, b.v)); }
};
```

## Verificación

Estresado contra Kadane de fuerza bruta: **107 100 rangos** sobre `n = 1..34` con sets intercalados, junto con `PersistentSegmentTree` y `SparseSegmentTree` usando el mismo `Node`. Cero discrepancias.

El ejemplo de arriba se extrae del comentario del header, se compila tal cual con `-Wall -Wextra` y se vuelve a correr el estrés con ese struct exacto.

**Sin link de juez todavía.** El campo `Verification` del header decía `SPOJ Fenwick` antes de esta verificación; si esa sumisión era real, conviene restaurarla además de lo de acá.
