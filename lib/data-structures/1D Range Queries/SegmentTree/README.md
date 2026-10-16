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
3. **`max_right` y `min_left` reciben el predicado como parámetro**, con la misma idea que la AtCoder Library pero sobre rango inclusivo: `max_right(l, r, pred)`. Están en los seis. Ver [Los dos descensos](#los-dos-descensos).
4. **Solo intervalos válidos**: `assert(0 <= l && l <= r && r < n)`. No existe el rango vacío, y `r == n` dispara el assert — es el error típico al traducir código semiabierto.
5. **`n` es el tamaño del vector original** (o `SZ` si no se pasa vector), y `SZ` es la potencia de dos.

Y los seis exponen **`dump()`** con el mismo contrato: devuelve el arreglo lógico completo (`n` elementos, no `SZ`), con `dump()[i] == get(i)`. En los persistentes toma el root, así que volcás cualquier versión. Es el mismo nombre que [`ImplicitTreap::dump()`](../ImplicitTreap.md). Detalles por template en cada manual.

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

El patrón para marcar la identidad es un campo `size` con dos salidas tempranas:

```cpp
friend Node operator+(const Node& a, const Node& b) {
    if (a.size == 0) return b;          // a es la identidad
    if (b.size == 0) return a;          // b es la identidad
    ...
}
```

> **La trampa clásica**: que `Node()` **no** sea la identidad. En una versión anterior de `LazySegmentTree` el constructor por defecto dejaba `size = 1` en vez de `0`, y el campo `size` de **todos** los resultados de consulta salía inflado — 5000 de 5000 mal. `sum` y `mn` sobrevivían por casualidad, así que el bug era invisible si solo mirabas esos.

### `node *= f` (los dos lazy densos)

Aplica el update a **todo el intervalo de una vez**, y **tiene que dejar la identidad quieta**: `Node() *= f` sigue siendo `Node()`. De ahí el `if (size == 0) return *this;`.

Requiere además **distributividad**: `(a ⊙ b) ⊗ f = (a ⊗ f) ⊙ (b ⊗ f)`. Si tu update no distribuye sobre tu agregado, el lazy no sirve, no importa cómo lo escribas.

Y el `size` del nodo es lo que permite escalar: `sum += f.a * size`.

### `apply(f, len)` (solo el sparse lazy)

Ahí el nodo **no puede** conocer su propio largo: un subárbol que nadie materializó no sabe cuántas posiciones cubre, pero el árbol sí, y se lo pasa. Por eso `apply` **fija** `size = len` en vez de sumarle.

Mantené los dos casos separados: `Node()` solo significa *ninguna posición*, mientras que `apply(f, len)` sobre ella significa *`len` posiciones que nunca se tocaron*.

## Contrato del `LazyUpdate`

| requisito | notas |
|---|---|
| `LazyUpdate()` | el update que no cambia nada |
| `f *= g` | apila `g` sobre `f`, de modo que **`g` actúa después de `f`** |

El `push` es **incondicional**: no hay bandera de "está vacío" ni variables `static` o `constexpr` en el `LazyUpdate`. Si el update es la identidad, aplicarlo igual es correcto y más barato que chequear.

> **La trampa del orden.** Un lazy aditivo conmuta, así que un `f *= g` escrito al revés **pasa igual** y el bug queda latente. Se destapa recién con un update no conmutativo como assign o afín. En esta librería lo verificamos con el `LazyUpdate` de assign+add de abajo, que es justamente el caso que lo caza.

## Cómo se llaman los `Node`

Un archivo de solución puede necesitar más de un árbol —uno de sumas y uno de mínimos, por ejemplo— y ahí `Node` a secas no alcanza. La convención:

| nombre | cuándo |
|---|---|
| `Node` | cuando el monoide es **complejo**, con campos que no se leen del nombre (máxima subsuma, convex hull trick, matrices) |
| `NodeSum`, `NodeMn`, `NodeMx`, `NodeMnMx`, `NodeSumMnMx` | cuando el nombre **puede** decir qué agrega |
| `LazyUpdate` | el update perezoso, siempre |

Por eso el monoide de máxima subsuma se llama `Node` y el de suma/máximo/mínimo `NodeSumMnMx`.

## Nodos listos para copiar

Los cuatro casos simples. **Sin lazy no hace falta campo de tamaño**: el neutro de cada uno se escribe directo.

```cpp
struct NodeSum {
    ll sum = 0;                                  // el neutro de + ya es el cero
    NodeSum() {}
    NodeSum(ll x) : sum(x) {}
    friend NodeSum operator+(const NodeSum& a, const NodeSum& b) { return NodeSum(a.sum + b.sum); }
};

struct NodeMn {
    ll mn = LLONG_MAX;                           // el neutro del minimo es +infinito
    NodeMn() {}
    NodeMn(ll x) : mn(x) {}
    friend NodeMn operator+(const NodeMn& a, const NodeMn& b) { return NodeMn(min(a.mn, b.mn)); }
};

struct NodeMx {
    ll mx = LLONG_MIN;                           // y el del maximo, -infinito
    NodeMx() {}
    NodeMx(ll x) : mx(x) {}
    friend NodeMx operator+(const NodeMx& a, const NodeMx& b) { return NodeMx(max(a.mx, b.mx)); }
};

struct NodeMnMx {
    ll mn = LLONG_MAX, mx = LLONG_MIN;           // cada campo con SU propio neutro
    NodeMnMx() {}
    NodeMnMx(ll x) : mn(x), mx(x) {}
    friend NodeMnMx operator+(const NodeMnMx& a, const NodeMnMx& b) {
        NodeMnMx res;
        res.mn = min(a.mn, b.mn);
        res.mx = max(a.mx, b.mx);
        return res;
    }
};
```

**Con lazy la cosa cambia**: el update tiene que escalar al largo del intervalo, así que ahí sí aparece el campo `size` y con él la guardia del rango vacío.

```cpp
struct LazyAdd {
    ll a = 0;
    LazyAdd() {}
    LazyAdd(ll x) : a(x) {}
    LazyAdd& operator*=(const LazyAdd& g) { a += g.a; return *this; }
};

struct NodeSumLazy {
    ll size = 0, sum = 0;                        // size == 0 es el rango vacio
    NodeSumLazy() {}
    NodeSumLazy(ll x) : size(1), sum(x) {}
    friend NodeSumLazy operator+(const NodeSumLazy& a, const NodeSumLazy& b) {
        if (a.size == 0) return b;
        if (b.size == 0) return a;
        NodeSumLazy res;
        res.size = a.size + b.size;
        res.sum = a.sum + b.sum;
        return res;
    }
    NodeSumLazy& operator*=(const LazyAdd& g) {
        if (size == 0) return *this;             // la identidad se queda identidad
        sum += g.a * size;
        return *this;
    }
};
```

Un mínimo o un máximo con lazy **no** necesitan `size` (sumarle una constante a todo el rango le suma lo mismo al mínimo), pero sí la guardia del rango vacío, para que la identidad no se contamine.

Los cinco están verificados contra fuerza bruta: 651 988 consultas los cuatro sin lazy, 20 173 el de suma con `add` de rango.

## Los dos monoides de ejemplo

Los seis manuales usan estos dos, así que están definidos acá una sola vez.

### A) Máxima suma de un subarreglo, con el vacío permitido

Para los tres **sin lazy**. Un número por nodo no alcanza: pegar dos mitades necesita el mejor subarreglo que **cruza la unión**, así que cada nodo lleva también la suma total, el mejor prefijo y el mejor sufijo. Como el subarreglo vacío cuenta, `best` nunca es negativo.

```cpp
struct Node {
    ll size = 0, sum = 0, pref = 0, suf = 0, best = 0;    // size == 0 es el rango vacio
    Node() {}
    Node(ll x) : size(1), sum(x), pref(max(0LL, x)), suf(max(0LL, x)), best(max(0LL, x)) {}
    friend Node operator+(const Node& a, const Node& b) {
        if (a.size == 0) return b;
        if (b.size == 0) return a;
        Node r;
        r.size = a.size + b.size;
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
struct LazyUpdate {
    bool has = false; ll v = 0, a = 0;
    LazyUpdate() {}
    static LazyUpdate assign(ll x) { LazyUpdate f; f.has = true; f.v = x; return f; }
    static LazyUpdate add(ll x) { LazyUpdate f; f.a = x; return f; }
    LazyUpdate& operator*=(const LazyUpdate& f) {              // f actua DESPUES
        if (f.has) { has = true; v = f.v; a = f.a; }
        else a += f.a;
        return *this; }
};
struct NodeSumMnMx {
    ll size = 0, sum = 0, mx = 0, mn = 0;          // size == 0 es el rango vacio
    NodeSumMnMx() {}
    NodeSumMnMx(ll x) : size(1), sum(x), mx(x), mn(x) {}
    friend NodeSumMnMx operator+(const NodeSumMnMx& a, const NodeSumMnMx& b) {
        if (a.size == 0) return b;
        if (b.size == 0) return a;
        NodeSumMnMx r;
        r.size = a.size + b.size;
        r.sum = a.sum + b.sum;
        r.mx = max(a.mx, b.mx);
        r.mn = min(a.mn, b.mn);
        return r; }
    NodeSumMnMx& operator*=(const LazyUpdate& f) {             // densos: el nodo sabe su largo
        if (size == 0) return *this;               // la identidad se queda identidad
        if (f.has) { sum = (f.v + f.a) * size; mx = mn = f.v + f.a; }
        else { sum += f.a * size; mx += f.a; mn += f.a; }
        return *this; }
};
```

Para `SparseLazySegmentTree` el mismo `LazyUpdate`, y el `NodeSumMnMx` cambia `operator*=` por:

```cpp
    void apply(const LazyUpdate& f, ll len) {           // sparse: el arbol dicta el largo
        size = len;                                // FIJA, no suma
        if (f.has) { sum = (f.v + f.a) * len; mx = mn = f.v + f.a; }
        else { sum += f.a * len; mx += f.a; mn += f.a; } }
```

## Los dos descensos

`SegmentTree` y `LazySegmentTree` tienen `max_right` y `min_left`. Misma idea que la [AtCoder Library](https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html) —el predicado va como parámetro— pero sobre rango inclusivo, con un `r` que ACL no tiene.

| método | devuelve | si ninguna cumple |
|---|---|---|
| `t.max_right(l, r, pred)` | la **mayor** `p` de `[l, r]` con `f(prod(l, p))` verdadera | `l - 1` |
| `t.min_left(l, r, pred)` | la **menor** `p` de `[l, r]` con `f(prod(p, r))` verdadera | `r + 1` |

`max_right` ancla en `l` y acumula **prefijos**; `min_left` ancla en `r` y acumula **sufijos**. Los dos son O(log n) en los dos templates.

### Los dos no usan la misma estrategia, y es a propósito

| | implementación | por qué |
|---|---|---|
| `SegmentTree` | **iterativa** (estilo AtCoder Library, acotada a `[l, r]`) | 1.8×–3.9× más rápida, medida |
| `LazySegmentTree` | **recursiva** | la iterativa empata (0.99×–1.11×) y cuesta 51% más `push` |

La iterativa recorre la descomposición de `[l, r]` absorbiendo nodos enteros, y cuando uno rompe baja por él. ACL no lleva la posición ni el largo del nodo porque su versión **no tiene `r`**: cualquier hermano que tome entra en el rango. Con rango inclusivo hay que **agrandar** mientras el padre entre y **encoger** cuando el hermano se pase de `r` — sin ese segundo bucle la respuesta se va de `r`.

En el lazy la iterativa tiene que limpiar los **dos** caminos del borde por adelantado (las piezas del borde derecho cuelgan del camino hasta `r`, no del de `l`), los use o no, y eso le da 1.51× más `push` que la recursiva, que empuja solo donde baja. Ahí se come toda la ventaja del recorrido. La recursiva es la mitad de código y se lee de arriba abajo.

La API es **la misma en los dos**, así que siguen siendo intercambiables.

Los centinelas están elegidos para que el largo del tramo salga **sin ramas**: `p - l + 1` con `max_right`, `r - p + 1` con `min_left`. En el centinela da 0 y en el otro extremo da el intervalo completo, sin un `if`. Son los mismos de `fstTrue`/`lstTrue` del template de contest. Ojo que `l - 1` y `r + 1` pueden ser índices válidos, así que el chequeo es `p == l - 1`, no `p < 0`.

### El predicado tiene que ser monótono

`f` tiene que ser `T T T F F F` al extender el rango: una vez falsa, falsa para siempre. Si no, la poda saltea un subárbol donde la respuesta estaba y **te devuelve algo incorrecto en silencio** — medido, 5.6% de respuestas mal con sumas que incluyen negativos.

El patrón para convertir una propiedad frágil en monótona: guardá el **peor** valor visto, no el actual. `minPref` en vez de `sum` para «el prefijo nunca se fue a negativo».

| problema | campos del `Node` | `f` |
|---|---|---|
| k-ésimo 1 en `[l, r]` | `sum` sobre 0/1 | `sum < k`, y la respuesta es `max_right + 1` |
| tramo con todos `< x` | `mx` | `mx < x` |
| tramo con todos `> x` | `mn` | `mn > x` |
| hasta dónde llego con `S` | `sum` **no negativo** | `sum <= S` |
| máxima subsuma acotada | el monoide A | `best <= S` |
| tramo no decreciente | `pri, ult, ok` | `ok` |

### Si no te alcanza, hay una red de seguridad

`lstTrue(l, r, p -> f(prod(l, p)))` del template de contest da la misma respuesta en O(log² n), y es trivialmente correcta. Medido contra la versión recursiva, el descenso le gana 3.4×–4.4×. Si estás justo de tiempo el descenso vale; si tenés margen, `lstTrue` es menos código que puede salir mal, y te sirve de referencia para el stress test.

Y si solo te interesa el prefijo o el sufijo **completo** (`r = n - 1`, o `l = 0`), la firma de ACL sin `r` es apenas **1.10×** más rápida que pasarle `r = n - 1` a esta, y en el lazy es un empate. No vale mantener una variante aparte.

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

## Convivencia con `templateHeavy`

Los seis conviven con [`templateHeavy.cpp`](../../../../templateHeavy.cpp) sin conflictos, y eso **no es gratuito**: el template de contest define macros que pisan identificadores comunes.

| macro | cómo rompe |
|---|---|
| `#define sz(x) int((x).size())` | es **con paréntesis**, así que `Node(ll x) : sz(1), ...` expande a `int((1).size())` |
| `#define f first`, `#define s second` | son **sin paréntesis**: *toda* aparición de `f` o `s` como identificador se reemplaza |
| `#define mp make_pair`, `ins`, `pb`, `eb`, `lb`, `ub`, `ft`, `bk`, `ts`, `rsz` | ídem |

Por eso el campo de tamaño del `Node` se llama **`size`** y no `sz` en los seis. Es el único nombre que hubo que cambiar, pero conviene saber por qué está así antes de «mejorarlo».

Por eso el predicado se llama **`pred`** y el update **`upd`**, no `f`: con `#define f first` toda aparición de `f` se reemplazaba, y aunque el rename era consistente y compilaba, se rompía apenas tu `Node` tuviera un campo llamado `first`.

Y por eso los nombres de parámetros son **descriptivos y no de una letra**: `pos`, `val`, `pred`, `upd`, `root`, `len`, `max_ops`. Es lo que muestra el hint del IDE cuando escribís la llamada, así que `t.set(pos, val)` dice algo que `t.set(p, x)` no.

Verificado: los seis templates más [`ImplicitTreap`](../ImplicitTreap.md) se insertan en `templateHeavy.cpp` en el lugar de `//* Template`, compilan con `-Wall -Wextra` sin warnings y corren.

## Errores frecuentes

| error | síntoma |
|---|---|
| traducir código semiabierto y pasar `r == n` | assert, inmediato — es el más común |
| `Node()` que no es la identidad de `+` | los campos derivados salen mal; `sum` y `min` suelen sobrevivir y tapan el bug |
| `f *= g` con el orden invertido | invisible con un lazy aditivo, revienta con assign o afín |
| un update que no distribuye sobre el agregado | resultados mal en cuanto un `apply` cubra un nodo interno |
| en el sparse lazy, `apply` que **suma** a `size` en vez de fijarlo | mal en los subárboles no materializados |
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
| `max_right`/`min_left` en los dos, siete problemas, con `apply` intercalado | 381 683 consultas |
| el descenso iterativo de `SegmentTree`, **exhaustivo** `n = 1..40`, todo `(l, r)` y todo `S` | 4 818 802 consultas |

El descenso iterativo de `SegmentTree` se verificó además contra el recursivo que reemplazó, celda por celda, y contra la firma sin `r` de ACL (`max_right_acl(l, f) - 1 == max_right(l, n-1, f)`, 1 076 612 comprobaciones). El bug que encontré al adaptarlo —el hermano del nodo absorbido puede pasarse de `r`, lo que sin el bucle de encoger devuelve un índice fuera del rango— está cubierto por el barrido exhaustivo.

Los tres invariantes de los descensos tienen control negativo: invertir el orden de `+` en `min_left`, podar sin chequear si el predicado rompe, y sacar el corte temprano. Los tres hacen fallar la suite. El primero **solo** lo detecta el monoide A, porque la suma conmuta y el de máxima subsuma no — un test con `Node` conmutativo no prueba nada sobre el orden.

Los nodos de este catálogo se compilan **tal cual** con `-Wall -Wextra` y se corren con esos structs, no con otros. De los seis manuales se verifica además que cada método documentado exista en el header y que cada tipo que aparece en un `Examples` esté definido ahí o acá.

**Solo `LazySegmentTree` tiene juez**: Codeforces EDU submission **394467936** (*Addition and First element at least X*, Accepted, 125 ms), que además es la primera verificación en juez de **`max_right`**. Los otros cinco siguen sin link.
