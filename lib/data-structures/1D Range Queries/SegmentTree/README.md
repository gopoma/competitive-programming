# Familia SegmentTree

Seis templates que comparten las mismas convenciones y los mismos contratos. Este archivo tiene lo común; cada uno tiene su manual con lo propio.

## Cuál usar

| necesitás | template |
|---|---|
| set en un punto, consulta de rango | [`SegmentTree.h`](SegmentTree.md) |
| además update de rango | [`LazySegmentTree.h`](LazySegmentTree.md) |
| además leer versiones viejas | [`PersistentSegmentTree.h`](PersistentSegmentTree.md) |
| versiones viejas **y** update de rango | [`PersistentLazySegmentTree.h`](PersistentLazySegmentTree.md) |
| `n` hasta 10¹⁸ (no entra en memoria) | [`SparseSegmentTree.h`](SparseSegmentTree.md) |
| `n` hasta 10¹⁸ **y** update de rango | [`SparseLazySegmentTree.h`](SparseLazySegmentTree.md) |

Dos avisos antes de elegir:

- **El sparse casi nunca es la respuesta.** Si las coordenadas que tocás son a lo sumo `q`, comprimirlas y usar el denso es más rápido y usa menos memoria. El sparse sirve cuando no podés comprimir, por ejemplo porque las consultas llegan online.
- **Si además necesitás `insert`, `erase`, `reverse`, `rotate` o `move`**, ningún segment tree puede: eso es [`../ImplicitTreap.h`](../ImplicitTreap.md), a cambio de ~1.8× de constante.

## Las cinco reglas

Todos los seis las cumplen, y es lo que los hace intercambiables:

1. **Rangos inclusivos `[l, r]`**, siempre. `prod(0, n - 1)` es todo el arreglo.
2. **Se parametriza con structs**, no con punteros a función: nada de `op`, `e`, `mapping`, `composition`, `id`.
3. **No hay `max_right` ni `min_left`.**
4. **Solo intervalos válidos**: `assert(0 <= l && l <= r && r < n)`. No existe el rango vacío, y `r == n` dispara el assert — es el error típico al traducir código semiabierto.
5. **`n` es el tamaño del vector original** (o `SZ` si no se pasa vector), y `SZ` es la potencia de dos.

Y las tres convenciones de forma: sin `#pragma once`, sin `#include`, sin `using namespace std`. El header asume que quien lo incluye ya tiene todo eso.

## Contrato del `Node`

Según el template, el `Node` tiene que proveer dos, tres o cuatro cosas:

| | `+` | `operator*=` | `apply(f, len)` |
|---|---|---|---|
| `SegmentTree`, `PersistentSegmentTree`, `SparseSegmentTree` | sí | — | — |
| `LazySegmentTree`, `PersistentLazySegmentTree` | sí | **sí** | — |
| `SparseLazySegmentTree` | sí | — | **sí** |

### `Node()` y `a + b`

`Node()` es la **identidad** de `+`, y por eso representa el **rango vacío**. `a + b` pliega dos intervalos vecinos con `a` a la **izquierda** de `b`, y tiene que ser **asociativo**. No hace falta que conmute.

El patrón para marcar la identidad es un campo `sz` con dos salidas tempranas:

```cpp
friend Node operator+(const Node& a, const Node& b) {
    if (a.sz == 0) return b;          // a es la identidad
    if (b.sz == 0) return a;          // b es la identidad
    ...
}
```

> **La trampa clásica**: que `Node()` **no** sea la identidad. En una versión anterior de `LazySegmentTree` el constructor por defecto dejaba `sz = 1` en vez de `0`, y el campo `sz` de **todos** los resultados de consulta salía inflado — 5000 de 5000 mal. `sum` y `mn` sobrevivían por casualidad, así que el bug era invisible si solo mirabas esos.

### `node *= f` (los dos lazy densos)

Aplica el update a **todo el intervalo de una vez**, y **tiene que dejar la identidad quieta**: `Node() *= f` sigue siendo `Node()`. De ahí el `if (sz == 0) return *this;`.

Requiere además **distributividad**: `(a ⊙ b) ⊗ f = (a ⊗ f) ⊙ (b ⊗ f)`. Si tu update no distribuye sobre tu agregado, el lazy no sirve, no importa cómo lo escribas.

Y el `sz` del nodo es lo que permite escalar: `sum += f.a * sz`.

### `apply(f, len)` (solo el sparse lazy)

Ahí el nodo **no puede** conocer su propio largo: un subárbol que nadie materializó no sabe cuántas posiciones cubre, pero el árbol sí, y se lo pasa. Por eso `apply` **fija** `sz = len` en vez de sumarle.

Mantené los dos casos separados: `Node()` solo significa *ninguna posición*, mientras que `apply(f, len)` sobre ella significa *`len` posiciones que nunca se tocaron*.

## Contrato del `LazyUpdate`

| requisito | notas |
|---|---|
| `LazyUpdate()` | el update que no cambia nada |
| `f *= g` | apila `g` sobre `f`, de modo que **`g` actúa después de `f`** |

El `push` es **incondicional**: no hay bandera de "está vacío" ni variables `static` o `constexpr` en el `LazyUpdate`. Si el update es la identidad, aplicarlo igual es correcto y más barato que chequear.

> **La trampa del orden.** Un lazy aditivo conmuta, así que un `f *= g` escrito al revés **pasa igual** y el bug queda latente. Se destapa recién con un update no conmutativo como assign o afín. En esta librería lo verificamos con el `Upd` de assign+add de abajo, que es justamente el caso que lo caza.

## Los dos monoides de ejemplo

Los seis manuales usan estos dos, así que están definidos acá una sola vez.

### A) Máxima suma de un subarreglo, con el vacío permitido

Para los tres **sin lazy**. Un número por nodo no alcanza: pegar dos mitades necesita el mejor subarreglo que **cruza la unión**, así que cada nodo lleva también la suma total, el mejor prefijo y el mejor sufijo. Como el subarreglo vacío cuenta, `best` nunca es negativo.

```cpp
struct Node {
    ll sz = 0, sum = 0, pref = 0, suf = 0, best = 0;    // sz == 0 es el rango vacio
    Node() {}
    Node(ll x) : sz(1), sum(x), pref(max(0LL, x)), suf(max(0LL, x)), best(max(0LL, x)) {}
    friend Node operator+(const Node& a, const Node& b) {
        if (a.sz == 0) return b;
        if (b.sz == 0) return a;
        Node r;
        r.sz = a.sz + b.sz;
        r.sum = a.sum + b.sum;
        r.pref = max(a.pref, a.sum + b.pref);
        r.suf = max(b.suf, b.sum + a.suf);
        r.best = max(max(a.best, b.best), a.suf + b.pref);   // el que cruza la union
        return r; }
};
```

### B) Suma, máximo y mínimo, con assign y add de rango

Para los tres **con lazy**. El update tiene que llevar **las dos clases a la vez**, leído como *«si `has`, asignar `v`; después sumar `a`»*, porque no conmutan: en la composición un assign posterior gana y borra el add que tenía pendiente debajo, mientras que un add posterior solo se acumula.

```cpp
struct Upd {
    bool has = false; ll v = 0, a = 0;
    Upd() {}
    static Upd assign(ll x) { Upd f; f.has = true; f.v = x; return f; }
    static Upd add(ll x) { Upd f; f.a = x; return f; }
    Upd& operator*=(const Upd& f) {              // f actua DESPUES
        if (f.has) { has = true; v = f.v; a = f.a; }
        else a += f.a;
        return *this; }
};
struct Node {
    ll sz = 0, sum = 0, mx = 0, mn = 0;          // sz == 0 es el rango vacio
    Node() {}
    Node(ll x) : sz(1), sum(x), mx(x), mn(x) {}
    friend Node operator+(const Node& a, const Node& b) {
        if (a.sz == 0) return b;
        if (b.sz == 0) return a;
        Node r;
        r.sz = a.sz + b.sz;
        r.sum = a.sum + b.sum;
        r.mx = max(a.mx, b.mx);
        r.mn = min(a.mn, b.mn);
        return r; }
    Node& operator*=(const Upd& f) {             // densos: el nodo sabe su largo
        if (sz == 0) return *this;               // la identidad se queda identidad
        if (f.has) { sum = (f.v + f.a) * sz; mx = mn = f.v + f.a; }
        else { sum += f.a * sz; mx += f.a; mn += f.a; }
        return *this; }
};
```

Para `SparseLazySegmentTree` el mismo `Upd`, y el `Node` cambia `operator*=` por:

```cpp
    void apply(const Upd& f, ll len) {           // sparse: el arbol dicta el largo
        sz = len;                                // FIJA, no suma
        if (f.has) { sum = (f.v + f.a) * len; mx = mn = f.v + f.a; }
        else { sum += f.a * len; mx += f.a; mn += f.a; } }
```

## El pool y el `reserve`

Los cuatro que alocan nodos dinámicamente (los dos persistentes y los dos sparse) reservan el pool **una sola vez** y nunca crecen, así que **siempre hay que pasarles `n` y la cantidad de consultas esperada `q`**. Las fórmulas son **pesimistas**: asumen que *cada* consulta es la operación más cara.

| template | `max_nodes(n, q)` | la operación más cara |
|---|---|---|
| `PersistentSegmentTree` | `2n + (C+1)·q + 1` | un `set`: `C+1` nodos |
| `PersistentLazySegmentTree` | `2n + 4(C+1)·q + 1` | un `apply` de rango: `4C−1` nodos |
| `SparseSegmentTree` | `(C+1)·q + 1` | un `set`: un nodo por nivel |
| `SparseLazySegmentTree` | `4(C+1)·q + 1` | un `apply` de rango: hasta cuatro por nivel |

con `C = ceil(log2 n)`. El **nodo 0 es el nodo nulo**: representa un subárbol enteramente `Node()`, y es lo que hace que `build()` sin argumentos cueste cero y que un `set` solo materialice el camino que toca.

`nodes_used()` te dice cuánto del pool se consumió de verdad; comparado con `max_nodes` te dice si la estimación fue razonable.

## Errores frecuentes

| error | síntoma |
|---|---|
| traducir código semiabierto y pasar `r == n` | assert, inmediato — es el más común |
| `Node()` que no es la identidad de `+` | los campos derivados salen mal; `sum` y `min` suelen sobrevivir y tapan el bug |
| `f *= g` con el orden invertido | invisible con un lazy aditivo, revienta con assign o afín |
| un update que no distribuye sobre el agregado | resultados mal en cuanto un `apply` cubra un nodo interno |
| en el sparse lazy, `apply` que **suma** a `sz` en vez de fijarlo | mal en los subárboles no materializados |
| usar el sparse cuando podías comprimir | funciona, pero más lento y con más memoria que el denso |
| un `q` corto en los que llevan pool | el pool no crece: **comportamiento indefinido** |

## Verificación

Los seis están estresados contra fuerza bruta con los dos monoides de arriba:

| escenario | comprobaciones |
|---|---|
| A, los tres sin lazy contra Kadane de fuerza bruta, `n = 1..34` | 107 100 rangos × 3 estructuras |
| A, el persistente leyendo **todas** las versiones y ramificando | 212 940 rangos |
| A, el sparse a `n = 10¹⁸` contra un `map` | 20 000 sets + 400 consultas |
| B, los tres con lazy, assign y add mezclados, `n = 1..30` | 69 440 rangos × 3 estructuras × 3 agregados |
| B, el persistente lazy sobre **todas** las versiones | 131 560 rangos |
| B, el sparse lazy a `n = 10¹⁸` contra fórmula cerrada | 8 propiedades |

Los ejemplos de los seis manuales se extraen de los comentarios, se compilan **tal cual** con `-Wall -Wextra` y se vuelven a correr con esos structs, no con otros. Cero discrepancias.

**Ninguno tiene link de juez todavía**, salvo `LazySegmentTree`, que pasó dos problemas de Codeforces EDU.
