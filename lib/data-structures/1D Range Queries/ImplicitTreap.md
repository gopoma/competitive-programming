# ImplicitTreap

Un `vector` que además responde consultas de rango, donde **insertar, borrar, invertir, rotar o mover un bloque cuesta O(log n)** en vez de O(n).

Ningún nodo guarda su índice: la posición se deduce contando cuántos nodos lo preceden en orden simétrico, leyendo los tamaños de subárbol. Por eso insertar en el medio no renumera nada — y eso es lo único que un segment tree no puede hacer de ninguna forma.

## Cuándo usarlo y cuándo no

| necesitás                                                                  | usá                                                                     |
|----------------------------------------------------------------------------|-------------------------------------------------------------------------|
| consulta y update de rango, tamaño fijo                                    | **`SegmentTree/LazySegmentTree.h`** — hace lo mismo 1.8× más rápido     |
| además `insert` / `erase` / `reverse` / `rotate` / `move` / concatenar     | **`ImplicitTreap.h`**                                                   |

La regla: el treap entra cuando **cambia la forma de la secuencia**, no solo sus valores. Si no necesitás ninguna de esas cinco operaciones, el segment tree es estrictamente mejor.

|                                 | `vector`   | `LazySegmentTree`   | `ImplicitTreap`   |
|---------------------------------|------------|---------------------|-------------------|
| `a[i]`                          | O(1)       | O(1)                | O(log n)          |
| `prod(l, r)`                    | O(n)       | O(log n)            | O(log n)          |
| `apply(l, r, f)`                | O(n)       | O(log n)            | O(log n)          |
| `all_prod()`                    | O(n)       | O(1)                | O(1)              |
| `insert` / `erase`              | O(n)       | **imposible**       | O(log n)          |
| `reverse` / `rotate` / `move`   | O(n)       | **imposible**       | O(log n)          |
| tamaño                          | dinámico   | **fijo**            | dinámico          |
| constante relativa              | 1×         | 1×                  | **1.8×**          |

Dos límites reales más allá de la constante:

- **Los agregados que dependen de la posición absoluta no funcionan.** Si tu `Node` necesita saber "estoy en el índice `i`" (por ejemplo `Σ i·a[i]`), el segment tree sí puede y el treap no, en cuanto haya `insert`, `erase` o `reverse`: las posiciones dejan de ser estables.
- **`reverse` endurece el contrato del `Node`** (ver más abajo). Un segment tree nunca paga eso porque no puede invertir.

## API

Rangos **inclusivos** `[l, r]`, base cero, y tienen que ser válidos: `0 <= l <= r < size()`.

A diferencia de un segment tree, **`size()` cambia**: `insert` y `erase` lo mueven, así que los asserts miran el tamaño actual. No hay padding ni potencias de dos en ninguna parte.

### Constructores

```cpp
ImplicitTreap<Node> t(v, q)                 // desde un vector<Node>
ImplicitTreap<Node, LazyUpdate> t(v, q)     // igual, más apply
ImplicitTreap<Node> t(n, q, gen)            // llama gen(0), gen(1), ... EN ORDEN
ImplicitTreap<Node> t(q)                    // arranca vacío
```

El segundo argumento es **cuántos `insert` esperás**, no cuántas consultas. Solo `insert` crea nodos:

```
max_nodes(n, q) = n + q
```

Quedarse corto no rompe nada, pero puede costar memoria: ver [Si el `q` queda corto](#si-el-q-queda-corto).

El constructor por generador manda cada valor directo al pool, sin armar ningún vector intermedio, así que podés leer de un stream:

```cpp
ImplicitTreap<Node> t(n, 0, [](int) { return Node(leer()); });
```

### Métodos

| método                       | costo                | qué hace                                                                   |
|------------------------------|----------------------|----------------------------------------------------------------------------|
| `size()`                     | O(1)                 | cuántos elementos hay ahora                                                |
| `clear()`                    | O(1)                 | vacia el treap conservando la capacidad del pool                           |
| `insert(i, x)`               | O(log n)             | `x` pasa a ser `a[i]`; `i == size()` agrega al final                       |
| `insert(i, v)`               | O(\|v\| + log n)     | inserta toda la secuencia `v` antes del viejo `a[i]`                       |
| `push_back(x)`               | O(log n)             | agrega al final                                                            |
| `push_front(x)`              | O(log n)             | agrega al principio                                                        |
| `erase(i)`                   | O(log n)             | quita `a[i]`                                                               |
| `erase(l, r)`                | O(log n)             | borra todo `a[l..r]` de una vez                                            |
| `pop_back()`                 | O(log n)             | quita el ultimo                                                            |
| `pop_front()`                | O(log n)             | quita el primero                                                           |
| `set(p, x)`                  | O(log n)             | `a[p] = x`                                                                 |
| `get(p)`                     | O(log n)             | el `Node` en `p`                                                           |
| `front()`                    | O(log n)             | el primer `Node`                                                           |
| `back()`                     | O(log n)             | el ultimo `Node`                                                           |
| `prod(l, r)`                 | O(log n)             | pliega `a[l..r]`                                                           |
| `all_prod()`                 | O(1)                 | pliega todo                                                                |
| `dump()`                     | O(n)                 | toda la secuencia en orden                                                 |
| `copy_range(l, r)`           | O(r - l + log n)     | los valores de `a[l..r]`                                                   |
| `apply(p, f)`                | O(log n)             | `f` sobre `a[p]` — necesita `LazyUpdate`                                   |
| `apply(l, r, f)`             | O(log n)             | `f` sobre `a[l..r]` — necesita `LazyUpdate`                                |
| `reverse(l, r)`              | O(log n)             | da vuelta `a[l..r]`                                                        |
| `rotate(l, r, k)`            | O(log n)             | rota `a[l..r]` a izquierda en `k`: el viejo `a[l+k]` pasa a ser `a[l]`     |
| `move(l, r, p)`              | O(log n)             | corta `a[l..r]` y lo pega antes del viejo `a[p]`                           |
| `swap_blocks(l1,r1,l2,r2)`   | O(log n)             | intercambia dos bloques disjuntos, `l1<=r1<l2<=r2`                         |
| `nodes_used()`               | O(1)                 | cuánto del pool se consumió, para depurar                                  |

En `move`, `p` se cuenta sobre el arreglo **original** y tiene que caer fuera de `[l, r]`.

### Correspondencia con la STL

La semántica de `insert`, `erase` y `rotate` coincide con la STL, y está verificada **contra las funciones de la STL mismas**, no contra una reimplementación:

| mío                         | equivalente STL                                   |
|-----------------------------|---------------------------------------------------|
| `t.insert(i, x)`            | `v.insert(v.begin() + i, x)`                      |
| `t.insert(t.size(), x)`     | `v.insert(v.end(), x)`                            |
| `t.erase(i)`                | `v.erase(v.begin() + i)`                          |
| `t.erase(l, r)`             | `v.erase(v.begin()+l, v.begin()+r+1)`             |
| `t.insert(i, v2)`           | `v.insert(v.begin()+i, v2.begin(), v2.end())`     |
| `t.rotate(l, r, k)`         | `std::rotate(b+l, b+l+k, b+r+1)`                  |
| `t.reverse(l, r)`           | `std::reverse(b+l, b+r+1)`                        |
| `t.prod(l, r)`              | `std::accumulate(b+l, b+r+1, 0)`                  |
| `t.move(l, r, p)`           | `erase` de rango + `insert` de rango              |

Dos diferencias de forma, a propósito:

- **Todo es por índice, no por iterador**, y los rangos son **inclusivos**, no semiabiertos. Eso sigue las convenciones de esta librería, no las de la STL.
- **`rotate` cambia la parametrización.** `std::rotate(first, middle, last)` son tres iteradores; el mío es `(l, r, k)`: rango inclusivo más desplazamiento. El resultado es el mismo, pero si escribís `rotate(l, mid, r)` por reflejo te sale otra cosa.

Y un detalle: **`insert` es el único lugar donde el índice puede valer `size()`**. El assert es `0 <= i && i <= size()`, no `i < size()`. Es deliberado: sin eso no se puede expresar "agregar al final", y es la misma libertad que `vector::insert(end(), x)`.

### `dump()` en lugar de `get(p)` repetido

Leer toda la secuencia con `get(p)` en un bucle es O(n log n); `dump()` hace un recorrido en orden simétrico y es O(n). Medido, mínimo de 5 corridas:

| n         | `dump()`         | n veces `get(p)`   |             |
|-----------|------------------|--------------------|-------------|
| 10 000    | 0.000050 s       | 0.000581 s         | 11.6×       |
| 100 000   | 0.000375 s       | 0.007826 s         | 20.9×       |
| 500 000   | **0.003827 s**   | 0.044045 s         | **11.5×**   |

Igual que `prod`, no escribe nada: lleva el update pendiente y la inversión pendiente en variables locales, así que podés volcar el estado sin ensuciar el árbol. `copy_range(l, r)` usa el mismo recorrido restringido al rango, y se compone con `insert` para duplicar un bloque:

```cpp
t.insert(j, t.copy_range(l, r));            // duplica a[l..r] antes del viejo a[j]
```

### Las versiones de rango valen la pena

`erase(l, r)` e `insert(i, v)` no son azúcar sobre las de un elemento: cambian el orden de crecimiento. `erase(l, r)` parte en tres y vuelve a pegar, O(log n) sin importar el largo del bloque. `insert(i, v)` arma un treap balanceado con los nuevos en O(\|v\|) y hace **un solo** `merge`.

Medido a `n = 2·10⁵`, mínimo de 5 corridas:

| L           | `erase(l, r)`      | L veces `erase(l)`     |                |
|-------------|--------------------|------------------------|----------------|
| 10          | 0.000001 s         | 0.000002 s             | 3×             |
| 1 000       | 0.000001 s         | 0.000137 s             | 152×           |
| 10 000      | 0.000001 s         | 0.001260 s             | 1 146×         |
| 100 000     | **0.000001 s**     | 0.009581 s             | **7 370×**     |

| L           | `insert(i, v)`     | L veces `insert`     |             |
|-------------|--------------------|----------------------|-------------|
| 10          | 0.000001 s         | 0.000002 s           | 2×          |
| 1 000       | 0.000023 s         | 0.000166 s           | 7×          |
| 10 000      | 0.000144 s         | 0.001897 s           | 13×         |
| 100 000     | **0.001298 s**     | 0.023607 s           | **18×**     |

El `erase` de rango es **plano**: borrar 10 o 100 000 elementos cuesta lo mismo, porque nunca toca el bloque — solo lo desconecta. El `insert` no puede ser plano (hay que crear \|v\| nodos), así que la ganancia se estabiliza en ~18×, que es el `log n` que se ahorra.

**Los nodos borrados quedan huérfanos.** El bloque que `erase` desconecta no se recicla: sus nodos siguen ocupando lugar en el pool. Eso ya pasaba con `erase(i)`, pero con rangos se nota. No afecta la fórmula `max_nodes(n, q) = n + q`, que cuenta elementos **insertados**; sí significa que una carga que inserta y borra bloques en ciclo consume pool proporcional al total insertado, no al tamaño vivo. Reciclarlos obligaría a recorrer el subárbol borrado, lo que volvería `erase(l, r)` O(L) y mataría justamente la ventaja de arriba.

**`insert(i, v)` cuenta como \|v\| inserciones para el pool**, no como una. Si insertás bloques, el `q` del constructor es la suma de los largos.

## Contrato del `Node`

Cuatro cosas, y **ninguna de ellas es un tamaño**: el árbol ya conoce todos los largos y los entrega.

### `Node()`

**Nunca llega a `operator+`.** El árbol saltea los subárboles vacíos por su cuenta, así que no hace falta identidad ni guardas de rango vacío. Es un contrato más simple que el de los segment trees de esta librería.

### `a + b`

Pliega dos intervalos vecinos con `a` a la **izquierda** de `b`. Tiene que ser **asociativo**. No hace falta que conmute ni que tenga inverso.

> La asociatividad es más esencial acá que en un segment tree. Allá la descomposición de `[l, r]` la fija la estructura: siempre el mismo paréntesis. En un treap el agregado se armó a lo largo de los `pull`, en una forma que depende de las prioridades aleatorias — dos sorteos distintos dan **paréntesis distintos del mismo producto ordenado**. La asociatividad es lo que hace que todos den lo mismo.

### `void reverse()`

**Esto es lo que la gente deja mal.** Una inversión da vuelta el orden dentro de un rango, así que el agregado de un rango invertido es el producto **leído al revés**.

- Si `+` **conmuta** (suma, máximo, mínimo), leído al revés es igual que leído al derecho, y `reverse()` queda **vacío**.
- Si `+` **no conmuta** (componer funciones, por ejemplo), el nodo tiene que llevar **los dos productos** y `reverse()` los intercambia.

```cpp
void reverse() {}                       // monoide conmutativo
void reverse() { swap(fwd, bwd); }      // monoide NO conmutativo
```

Dejarlo vacío en el segundo caso da mal **solo después de una inversión**, y **solo en el campo no conmutativo**. Una suite de tests hecha de sumas no lo caza nunca. Y aun con el monoide correcto es esquivo: en el ejemplo C de abajo, la versión con el bug **coincide en 6 de 7 lecturas**. El único caso que lo destapa es leer un subárbol de **varios** elementos bajo una inversión pendiente; si el descenso se parte hasta elementos sueltos, `fwd` y `bwd` coinciden y el error se esconde.

### `void apply(const LazyUpdate& f, long long len)`

Solo si pasás un `LazyUpdate`. Aplica el update a `len` posiciones de una vez.

**El árbol es la autoridad del largo**: pasa `1` para el elemento que el nodo tiene propio y el tamaño del subárbol para el agregado. Por eso el `Node` no necesita llevar un campo `sz`. Es el mismo contrato que `SegmentTree/SparseLazySegmentTree.h`, por la misma razón.

Y no es solo elegancia: tener `sz` dentro del `Node` lo mide **1.34× más lento** y el nodo pasa de 40 a 56 bytes, porque un nodo interno del treap guarda **dos `Node`** (el elemento propio y el agregado), así que cada campo se paga doble.

## Contrato del `LazyUpdate`

| requisito          | notas                                                             |
|--------------------|-------------------------------------------------------------------|
| `LazyUpdate()`     | el update que no cambia nada                                      |
| `f *= g`           | apila `g` sobre `f`, de modo que **`g` actúa después de `f`**     |

El `push` es **incondicional**, como en `LazySegmentTree.h`, así que no hace falta ninguna bandera de "está vacío".

Si omitís el segundo argumento del template, queda `NoLazy`, un struct vacío que **entra en el relleno que el nodo ya tenía**: cuesta cero bytes, el código del lazy desaparece de la instanciación, y `apply` deja de compilar con un `static_assert` claro.

## Ejemplos

Los tres estados intermedios de abajo están verificados: el programa que los produce los asevera uno por uno.

### A) Solo manipulación

```cpp
struct Node {
    ll sum = 0;
    Node() {}
    Node(ll x) : sum(x) {}
    friend Node operator+(const Node& a, const Node& b) { return Node(a.sum + b.sum); }
    void reverse() {}                          // la suma no distingue el orden
};

vector<Node> ini;
for (ll x : {10, 20, 30, 40, 50}) ini.push_back(Node(x));
ImplicitTreap<Node> t(ini, 2);                 // 2 = cuántos insert esperás
// a = [10 20 30 40 50]

t.size()            // 5
t.all_prod().sum    // 150
t.prod(1, 3).sum    // 90        inclusivo: 20+30+40
t.get(2).sum        // 30
t.nodes_used()      // 5

t.set(2, Node(99));            // a = [10 20 99 40 50]
t.insert(2, Node(7));          // a = [10 20 7 99 40 50]     inserta ANTES de la posición 2
t.insert(t.size(), Node(1));   // a = [10 20 7 99 40 50 1]   i == size(): al final
t.erase(0);                    // a = [20 7 99 40 50 1]
t.reverse(1, 4);               // a = [20 50 40 99 7 1]      prod(1, 4) = 196
t.rotate(0, 3, 1);             // a = [50 40 99 20 7 1]      el viejo a[1] pasa a ser a[0]
t.move(0, 1, 5);               // a = [99 20 7 50 40 1]      all_prod() = 217

// sizeof(InternalNode) = 40 B
```

### B) Con update de rango

```cpp
struct Upd {
    ll a = 1, b = 0;                           // f(x) = a*x + b
    Upd() {}
    Upd(ll x, ll y) : a(x), b(y) {}
    Upd& operator*=(const Upd& f) {             // f actúa DESPUÉS
        a = f.a * a;  b = f.a * b + f.b;  return *this; }
};
struct Node {
    ll sum = 0;
    Node() {}
    Node(ll x) : sum(x) {}
    friend Node operator+(const Node& a, const Node& b) { return Node(a.sum + b.sum); }
    void reverse() {}
    void apply(const Upd& f, ll len) { sum = f.a * sum + f.b * len; }   // el árbol pasa len
};

ImplicitTreap<Node, Upd> u(ini2, 1);
// a = [1 2 3 4 5]

u.apply(1, 3, Upd(2, 0));      // a = [1 4 6 8 5]            x -> 2x sobre a[1..3]
u.apply(0, 4, Upd(1, 10));     // a = [11 14 16 18 15]       all_prod() = 74
u.apply(2, Upd(0, 100));       // a = [11 14 100 18 15]      un solo elemento

u.apply(0, 1, Upd(2, 0));      // la composición NO conmuta:
u.apply(0, 1, Upd(1, 1));      // a = [23 29 100 18 15]      11*2+1 = 23, no (11+1)*2 = 24

u.reverse(0, 3);               // a = [18 100 29 23 15]      lazy pendiente + reverse
u.apply(0, 2, Upd(1, 1));      // a = [19 101 30 23 15]      prod(0, 2) = 150
u.insert(0, Node(1000));       // a = [1000 19 101 30 23 15] insert con lazy pendiente adentro

// sizeof(InternalNode) = 56 B
```

### C) Monoide NO conmutativo

Cada elemento es un mapa afín y el monoide es la composición.

```cpp
struct Lin { ll a = 1, b = 0; };
Lin comp(const Lin& f, const Lin& g) {         // primero f, después g
    return { g.a * f.a, g.a * f.b + g.b };
}
struct Node {
    Lin fwd, bwd;                              // fwd: izquierda a derecha. bwd: al revés
    Node() {}
    Node(Lin f) : fwd(f), bwd(f) {}
    friend Node operator+(const Node& a, const Node& b) {
        Node r;
        r.fwd = comp(a.fwd, b.fwd);            // primero a, después b
        r.bwd = comp(b.bwd, a.bwd);            // orden invertido
        return r; }
    void reverse() { swap(fwd, bwd); }         // <-- lo que NO puede faltar
};
```

```cpp
// a = [2x+1, 3x, x+5, 4x+2]
// prod(0, 2) compone f0, f1, f2:  x -> 2x+1 -> 3(2x+1) = 6x+3 -> 6x+8
c.prod(0, 2).fwd        // (6, 8)        en x=1 -> 14
c.prod(0, 3).fwd        // (24, 34)      en x=1 -> 58

c.reverse(0, 2);
// a = [x+5, 3x, 2x+1, 4x+2]
// ahora compone al revés:  x -> x+5 -> 3x+15 -> 2(3x+15)+1 = 6x+31
c.prod(0, 2).fwd        // (6, 31)       en x=1 -> 37     antes era 14

c.insert(0, Node(Lin{5, 0}));
// a = [5x, x+5, 3x, 2x+1, 4x+2]
c.prod(0, 4).fwd        // (120, 126)    en x=1 -> 246

c.reverse(1, 4);
// a = [5x, 4x+2, 2x+1, 3x, x+5]
c.prod(0, 4).fwd        // (120, 20)     en x=1 -> 140
                        //   con reverse() vacío daría 246: el único de 7 que lo delata
```

## Memoria

```
max_nodes(n, q) = n + q         q = cuántos insert esperás
```

| `Node`             | `LazyUpdate`     | `sizeof(InternalNode)`      |
|--------------------|------------------|-----------------------------|
| `{ll sum}`         | ninguno          | **40 B**                    |
| `{ll sum}`         | `{ll add}`       | 48 B                        |
| `{ll sum}`         | `{ll a, b}`      | 56 B                        |
| `{ll sz, sum}`     | ninguno          | 56 B — *sacale el `sz`*     |

Un nodo interno guarda **dos `Node`** (el elemento propio y el agregado del subárbol), así que cada campo del `Node` se paga dos veces.

### Si el `q` queda corto

**No se rompe nada.** El pool es un `vector`, así que `push_back` lo reubica, y eso es seguro acá porque `new_node` se llama solo desde el constructor y desde `insert`, y en ninguno de los dos hay una referencia viva al pool en ese momento. (`split` sí pasa referencias `int&` adentro del pool, pero nunca crea nodos. Si no fuera así, un `q` corto daría referencias colgantes y basura silenciosa.)

Verificado: con `q = 0` y 16 000 `insert`, 4018 consultas contra fuerza bruta sin un error; y el mismo arreglo construido con `q` exacto y con `q = 0` sale idéntico elemento por elemento.

**El costo no está en el tiempo sino en la memoria, y no es monótono.** Con `n = 2·10⁵` y 5·10⁵ `insert`, o sea 7·10⁵ nodos al final:

| `q` dado             | tiempo      | pico             | contra el exacto     |
|----------------------|-------------|------------------|----------------------|
| 500 000 (exacto)     | 0.696 s     | **32.98 MB**     | 1.00×                |
| 100 000              | 0.701 s     | **51.86 MB**     | **1.57×**            |
| 1 000                | 0.782 s     | 36.74 MB         | 1.11×                |
| 0                    | 0.712 s     | 36.60 MB         | 1.11×                |

Fijate que `q = 100000` sale **peor que `q = 0`**: no es «mientras más corto, peor». La causa es cómo duplica el `vector` — durante una reubicación el buffer viejo y el nuevo existen a la vez, y el peor caso es cuando la cantidad final de nodos **apenas cruza** un límite de capacidad:

| `q`         | capacidades que atraviesa       | coexisten en la última mudanza     |
|-------------|---------------------------------|------------------------------------|
| 500 000     | `[700001]`                      | nunca se muda: 37.4 MB             |
| 100 000     | `[300001, 600002, 1200004]`     | 32.0 + 64.1 = **96.1 MB**          |
| 1 000       | `[201001, 402002, 804004]`      | 21.5 + 42.9 = 64.4 MB              |
| 0           | `[200001, 400002, 800004]`      | 21.4 + 42.7 = 64.1 MB              |

Con `q = 100000` la capacidad arranca en 300 001, duplica a 600 002, y los 700 000 nodos finales fuerzan el salto a 1 200 004: pedís lugar para 1.2 millones de nodos cuando usás 700 000, y en ese instante tenés los dos buffers vivos.

### Pasarse de largo es gratis

| `q` dado                    | pico         |
|-----------------------------|--------------|
| 500 000 (exacto)            | 32.78 MB     |
| 2 000 000 (4× de más)       | 32.82 MB     |
| 10 000 000 (20× de más)     | 32.80 MB     |

Idéntico. `reserve` no confirma páginas: las que no se tocan no entran en el working set, así que reservar veinte veces de más no cuesta un byte de memoria pico.

**La regla: cuando dudes, pasá de más, nunca de menos.** Sobreestimar es literalmente gratis; subestimar puede costar hasta 1.57× de memoria pico por una razón que no podés anticipar de antemano. `nodes_used()` te dice después cuántos nodos se consumieron de verdad.

## Rendimiento medido

Todo con `-O2 -std=c++23 -march=native` (los flags de Library Checker), proceso fijado a un P-core, mínimo de varias corridas.

### Contra el segment tree, en la carga que ambos pueden hacer

`n = q = 5·10⁵`, afín de rango + suma de rango:

|                                                  | tiempo         | contra el segment tree     |
|--------------------------------------------------|----------------|----------------------------|
| `LazySegmentTree.h`                              | 0.37 s         | 1×                         |
| treap con `split`/`merge` para todo              | 1.47 s         | 4.0×                       |
| **treap con descenso** (esta implementación)     | **0.67 s**     | **1.8×**                   |

`prod` y `apply` **bajan por el árbol sin partirlo**, como un segment tree, y `prod` no escribe nada: lleva el update pendiente y la inversión pendiente en variables locales. `split`/`merge` queda solo para lo que cambia la forma. Responder consultas con `split`/`merge` —que es lo que hacen **todos** los treaps de Library Checker— mide el doble: cada una reescribe cuatro caminos raíz-hoja para una operación que no mueve nada.

### Contra los rivales, medido en el juez

[Submission 407984](https://judge.yosupo.jp/submission/407984): **AC, 303 ms / 11.27 MiB** en Range Reverse Range Sum. Comparado caso por caso con los dos treaps más rápidos del ranking:

| caso                                     | **este template**       | `hly1204` (291 ms)     | `oldyan` (269 ms)     |
|------------------------------------------|-------------------------|------------------------|-----------------------|
| `max_random_00/01/02`                    | **247 / 250 / 249**     | 289 / 290 / 291        | 225 / 230 / 230       |
| `almost_t0_00` (casi todo `reverse`)     | **303**                 | 291                    | 269                   |
| `almost_t1_00` (casi todo consulta)      | **168**                 | 259                    | 186                   |
| `random_00 / 01 / 02`                    | **216 / 154 / 225**     | 251 / 186 / 265        | 209 / 142 / 225       |
| `nq_01_06 / 07`                          | **4 / 5**               | 15 / 19                | 5 / 6                 |
| memoria máxima                           | 11.27 MiB               | 11.20 MiB              | 10.46 MiB             |

**Le gana a `hly1204` en todos los casos**, incluido 1.54× en el pesado en consultas — que es el descenso rindiendo. Pero el juez reporta el **máximo** sobre los casos, y para los tres ese máximo sale de `almost_t0_00`. Ahí pierde: 303 contra 291 y 269.

O sea que **el único punto flojo es la carga pesada en `reverse`**, y está confirmado en el juez. Es coherente con el diseño: cuando la operación cambia la forma de la secuencia los tres tienen que hacer `split`/`merge`, y la ventaja del descenso no aplica porque no hay consultas que responder.

Puesto ~30 entre usuarios distintos, por detrás de los tres treaps del board y por delante de la mayoría del resto.

> **Advertencia de método, por si proyectás tiempos entre máquinas.** Antes de enviar estimé ~230 ms usando un factor local/juez de 1.60, derivado de correr el código de un competidor en mi máquina y compararlo con su tiempo en el juez. Los tres casos de *ese* programa coincidían en 1.58–1.60, y lo tomé como constante de máquina. Era un error: con tres programas ya medidos de las dos formas, el factor va de **0.99 a 1.57 según el código** (pool plano con I/O propia ≈ 1.0–1.2; treap con punteros y `cin` ≈ 1.2–1.3; splay con `new` por nodo ≈ 1.5). La consistencia entre casos de un mismo programa no dice nada sobre la transferencia a otro. Lo que **sí** transfirió bien fue la comparación relativa local: las tres direcciones acertaron y la de la mezcla con dos decimales.

### Profundidad

A `n = 2·10⁵`, tras 2·10⁵ operaciones: máxima 48, promedio 22.7, con `log₂ n = 17.6`. Eso es la profundidad esperada de un treap aleatorio.

El `build` enlaza balanceado sin respetar la propiedad de heap, lo cual **medido no importa**: arranca en promedio 16.7 y converge al mismo 22.7 que si se construyera el árbol cartesiano correcto de las prioridades (que arranca en 22.0).

## La semilla de las prioridades

**La semilla sale del reloj, no es fija.** Eso es a propósito, por la misma razón que el `hash_map` de esta librería usa `chrono` en su hash: en Codeforces te pueden hackear.

Con una semilla fija la secuencia de prioridades es **idéntica en cada corrida**, así que un atacante la reproduce offline y busca con todo el tiempo del mundo una entrada que haga el árbol profundo. Y no es teórico: lo medí con un hill climbing tonto sobre la secuencia de posiciones de `insert`, que es lo único que el atacante controla.

| con `n = 1000`                            | profundidad        |
|-------------------------------------------|--------------------|
| `log₂ n`                                  | 9.97               |
| esperado de un treap aleatorio            | ~13.9              |
| entradas al azar, promedio de 30          | **22.6**           |
| entradas al azar, peor de 30              | 27                 |
| **tras el ataque, 3000 evaluaciones**     | **42** (1.86×)     |

Con 3000 evaluaciones y mutaciones al azar ya se duplica. Un atacante con horas y una construcción pensada llega mucho más lejos.

Con la semilla del reloj eso se cae solo. La misma secuencia adversaria que lograba profundidad 31 contra una semilla fija da **22–28** contra la del reloj — exactamente el rango de una entrada normal:

```
contra la semilla FIJA:                        31
la misma secuencia contra el RELOJ:  22 23 23 22 25 28
```

> Ese es también el motivo de que Library Checker tenga casos `wrong_avl_killer` y `wrong_splay_killer` pero **ningún** treap killer: a un treap bien sembrado no lo mata ningún dato fijo. La aleatoriedad es la defensa, y una semilla constante la tira a la basura.

### Para depurar

El precio de la semilla del reloj es que una falla rara deja de ser reproducible. Para fijarla, descomentá la línea que está en el header:

```cpp
// #define IMPLICIT_TREAP_SEED 2463534242u
```

Los tests contra fuerza bruta no dependen de la semilla —comparan contra la respuesta correcta, no contra una forma esperada— así que pasan igual con cualquiera de las dos.

## Errores frecuentes

| error                                               | síntoma                                                                                           |
|-----------------------------------------------------|---------------------------------------------------------------------------------------------------|
| fijar la semilla y competir en Codeforces           | hackeable: con la secuencia conocida se puede duplicar la profundidad                             |
| `reverse()` vacío con un monoide no conmutativo     | mal **solo** después de una inversión, y solo en el campo no conmutativo. Invisible con sumas     |
| `f *= g` con el orden al revés                      | pasa desapercibido con un lazy aditivo (conmuta) y revienta con afín o assign                     |
| contar `insert(i, v)` como una sola inserción       | pool corto: cuenta como \|v\|                                                                     |
| pasar un `q` de **más**                             | nada: reservar de sobra es gratis                                                                 |
| pasar un `q` **corto**                              | hasta 1.57× de memoria pico, y de forma no monótona. Corrección y tiempo intactos                 |
| olvidar que `size()` cambia                         | assert en el siguiente `prod` o `apply`                                                           |
| usar `rotate(l, mid, r)` por reflejo de la STL      | resultado silenciosamente distinto: la firma es `(l, r, k)`                                       |
| un agregado que depende del índice absoluto         | mal en cuanto haya un `insert`, `erase` o `reverse`                                               |

## Verificación

Contra fuerza bruta:

| test                                                                                      | comprobaciones                            |
|-------------------------------------------------------------------------------------------|-------------------------------------------|
| `insert`, `erase`, `reverse`, `rotate`, `move`, `prod` contra las funciones de la STL     | 3163                                      |
| más `apply(f, len)`, `set`, `get`                                                         | 2953                                      |
| monoide **no conmutativo** bajo inversión                                                 | 3347                                      |
| control negativo del anterior (agregado equivocado)                                       | **3105 de 3329 mal** — el test muerde     |
| constructor por generador contra el de vector                                             | 48993                                     |
| Library Checker Range Reverse Range Sum                                                   | muestra + 130 casos aleatorios            |
| Library Checker Dynamic Sequence Range Affine Range Sum                                   | muestra + 130 casos aleatorios            |

Compila con `-std=c++17 -Wall -Wextra -Wpedantic` sin warnings.

**Verificado en juez**: [Library Checker submission 407984](https://judge.yosupo.jp/submission/407984), AC 303 ms / 11.27 MiB en Range Reverse Range Sum. Dynamic Sequence Range Affine Range Sum está escrito y verificado localmente, pendiente de enviar.
