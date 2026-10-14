# SegmentTree

Segment tree clásico: **set en un punto, consulta de rango**. El más simple y el más rápido de la familia; si no necesitás update de rango, versiones ni $n$ gigante, es este.

Convenciones, contrato del `Node` y monoides de ejemplo: [README.md](README.md).

## Los ocho métodos que expone

```cpp
SegmentTree<T> t(v)    // n = v.size(), SZ = n redondeado a potencia de dos
SegmentTree<T> t(k)    // sin vector: n pasa a ser SZ, con T() en cada lugar
```

| método | costo | qué hace |
|---|---|---|
| constructor con `vector` | $O(n)$ | copia las hojas y hace `pull` de abajo hacia arriba |
| constructor con `int` | $O(SZ)$ | todo `T()`; no hace falta `pull` porque `T() + T() == T()` |
| `t.set(p, x)` | $O(\log n)$ | $a_p \leftarrow x$, y repara el camino hasta la raíz |
| `t.get(p)` | $\mathbf{O(1)}$ | la `T` que está en $p$ |
| `t.prod(l, r)` | $O(\log n)$ | pliega $a_l \oplus a_{l+1} \oplus \dots \oplus a_r$ |
| `t.all_prod()` | $\mathbf{O(1)}$ | pliega todo el arreglo: es `seg[1]` |
| `t.dump()` | $O(n)$ | vuelca el arreglo entero, para depurar |
| `t.max_right(l, r, f)` | $O(\log n)$ | la mayor $p$ con $f(\text{prod}(l,p))$, o $l-1$ |
| `t.min_left(l, r, f)` | $O(\log n)$ | la menor $p$ con $f(\text{prod}(p,r))$, o $r+1$ |

No hay nada más. Los cuatro helpers (`pull` y los bucles internos de los descensos) son privados.

## Cómo está armado por dentro

Un **árbol binario completo guardado en un arreglo plano** `seg` de $2\,SZ$ posiciones, con $SZ$ la menor potencia de dos $\ge n$. No hay punteros ni nodos alocados: la posición en el arreglo *es* la identidad del nodo.

| | |
|---|---|
| raíz | `seg[1]`, cubre $[0,\ SZ-1]$ |
| hijos de `x` | `seg[2x]` (izquierdo) y `seg[2x + 1]` (derecho) |
| padre de `x` | `seg[x / 2]` |
| **hoja de la posición $p$** | **`seg[SZ + p]`** — ahí viven los rangos de un solo elemento |
| nodos internos | `seg[1] .. seg[SZ - 1]` |
| hojas | `seg[SZ] .. seg[2·SZ - 1]` |
| `seg[0]` | no se usa |

Con $n = 8$ (y entonces $SZ = 8$) el mapa completo es:

```
                       1 = [0,7]
            2 = [0,3]              3 = [4,7]
      4=[0,1]    5=[2,3]     6=[4,5]    7=[6,7]
    8=[0] 9=[1] 10=[2] 11=[3] 12=[4] 13=[5] 14=[6] 15=[7]
```

Un nodo interno cumple siempre $\text{seg}[x] = \text{seg}[2x] \oplus \text{seg}[2x+1]$, y eso es todo lo que hace `pull`.

De ahí salen dos cosas:

**`get(p)` es $O(1)$** porque el elemento $p$ vive literalmente en `seg[SZ + p]` — no hay nada que bajar ni que resolver. Es la única estructura de la familia donde eso vale; en `LazySegmentTree` el `get` es $O(\log n)$ porque antes hay que bajar los lazy pendientes del camino.

**La cola $[n,\ SZ)$ existe y vale `T()`.** Si $n$ no es potencia de dos, `seg` tiene hojas de relleno que valen el neutro. No molestan en `prod` (el neutro no cambia el pliegue) y los descensos nunca entran ahí, porque `assert(r < n)` más el chequeo de rango las excluye.

## Ojo con el constructor de un argumento

`SegmentTree<T> t(k)` **no** te da $k$ elementos: te da $SZ$ elementos, con $SZ$ la potencia de dos que cubre $k$, y todos valen `T()` — el **neutro**, no el cero de tu problema.

```cpp
SegmentTree<Suma> z(5);
// all_prod().sz == 0  y  all_prod().sum == 0
// SZ = 8, no 5, y cada lugar vale Suma() con sz = 0, NO Suma(0) con sz = 1
```

Si querés $k$ ceros de verdad, usá `SegmentTree<T>(vector<T>(k, T(0)))`. La diferencia importa cuando `T()` y `T(0)` no son lo mismo, que es justo el caso de los monoides de ejemplo.

## Todos los métodos, con resultados reales

Con $a = \{3, 1, 4, 1, 5, 9, 2, 6\}$ y un `Node` que solo lleva `sz` y `sum`:

```cpp
vector<Suma> iv(8);
for (int i = 0; i < 8; i++) iv[i] = Suma(a[i]);
SegmentTree<Suma> t(iv);                 // n = 8, SZ = 8

t.get(0).sum                             // 3
t.get(5).sum                             // 9
t.prod(0, 7).sum                         // 31   = 3+1+4+1+5+9+2+6
t.prod(2, 4).sum                         // 10   = 4+1+5
t.prod(3, 3).sum                         // 1    un solo elemento, rango valido
t.all_prod().sum                         // 31   igual que prod(0, 7), pero O(1)

t.set(5, Suma(0));
t.get(5).sum                             // 0
t.all_prod().sum                         // 22   31 - 9
```

`prod(l, r)` exige $0 \le l \le r < n$. **No existe el rango vacío**: `prod(3, 2)` dispara el assert, y `prod(0, n)` también — es el error típico al traducir código semiabierto.

# Los dos descensos

## Qué devuelven, y el centinela

$$
\texttt{max\_right}(l,r,f) \;=\; \max\{\, p \in [l,r] \;:\; f(\text{prod}(l,p)) \,\}, \qquad l-1 \text{ si el conjunto es vacío}
$$

$$
\texttt{min\_left}(l,r,f) \;=\; \min\{\, p \in [l,r] \;:\; f(\text{prod}(p,r)) \,\}, \qquad r+1 \text{ si el conjunto es vacío}
$$

`max_right` ancla en $l$ y acumula **prefijos** $\text{prod}(l,p)$ al crecer $p$. `min_left` ancla en $r$ y acumula **sufijos** $\text{prod}(p,r)$ al decrecer $p$.

**El centinela, explícito.** Hay dos extremos y conviene tenerlos separados:

| caso | `max_right` devuelve | `min_left` devuelve |
|---|---|---|
| $f$ falla ya en el primer elemento | $l - 1$ **(centinela)** | $r + 1$ **(centinela)** |
| $f$ aguanta todo el rango | $r$ | $l$ |

Y la trampa: **$l-1$ y $r+1$ pueden ser índices válidos del arreglo.** Si $l = 3$, el centinela es $2$, que es una posición que existe. El chequeo correcto es

```cpp
if (p == l - 1) { /* ninguna posicion cumple */ }     // asi
if (p < 0)      { /* MAL: solo funciona si l == 0 */ }
```

El motivo de elegir estos centinelas y no $-1$ es que el **largo del tramo sale sin ramas**:

$$
\text{largo} = p - l + 1 \ \ (\texttt{max\_right}), \qquad \text{largo} = r - p + 1 \ \ (\texttt{min\_left})
$$

En el centinela dan $0$ y en el otro extremo dan el intervalo completo, sin un `if`. Verificado contra el largo real en 40 000 casos:

```
en [2, 6] con S =   0:  p =  1,  largo = p - l + 1 = 0     <- centinela
en [2, 6] con S =   8:  p =  3,  largo = p - l + 1 = 2
en [2, 6] con S = 100:  p =  6,  largo = p - l + 1 = 5     <- todo el rango
en [2, 6] con S =   0:  p =  7,  largo = r - p + 1 = 0     <- centinela
en [2, 6] con S =   8:  p =  6,  largo = r - p + 1 = 1
en [2, 6] con S = 100:  p =  2,  largo = r - p + 1 = 5
```

## Qué le piden a $f$

**$f$ tiene que ser monótona** al extender el rango: $\texttt{T T T F F F}$, una vez falsa falsa para siempre. Formalmente, para `max_right`:

$$
f(\text{prod}(l,p)) = \texttt{false} \;\Longrightarrow\; f(\text{prod}(l,p')) = \texttt{false} \quad \forall\, p' > p
$$

Si no, la poda saltea un subárbol donde estaba la respuesta y **te devuelve algo incorrecto en silencio** — medido, 5.6 % de respuestas mal con sumas que incluyen negativos. El patrón para arreglarlo: guardá el **peor** valor visto, no el actual (`minpref` en vez de `sum`).

`f` recibe el `Node` acumulado, no un índice, y nunca se la llama sobre el neutro pelado: siempre sobre `acc + seg[k]` con `seg[k]` no vacío. Por eso no hace falta que $f(\texttt{T()})$ sea verdadera, a diferencia de la AtCoder Library, que lo exige con un `assert`.

## Ejemplo 1 — suma $\le S$

El caso base. **Requiere valores no negativos**, porque si no la suma del prefijo no es monótona.

```cpp
int p = t.max_right(l, r, [&](const Suma& v) { return v.sum <= S; });
// a[l..p] suma <= S, y agregando a[p+1] se pasa.  largo = p - l + 1
```

Con $a = \{3, 1, 4, 1, 5, 9, 2, 6\}$ sobre $[0,7]$:

```
max_right(0, 7, sum <=   0) = -1   <- CENTINELA l-1 = -1: ni a[0] = 3 entra
max_right(0, 7, sum <=   2) = -1   <- CENTINELA: 3 > 2
max_right(0, 7, sum <=   8) =  2   suma 0..2 = 8, con a[3] se pasa
max_right(0, 7, sum <=  13) =  3   suma 0..3 = 9, con a[4] se pasa a 14
max_right(0, 7, sum <= 100) =  7   <- aguanto todo: p == r

min_left (0, 7, sum <=   0) =  8   <- CENTINELA r+1 = 8: ni a[7] = 6 entra
min_left (0, 7, sum <=   6) =  7   suma 7..7 = 6
min_left (0, 7, sum <=   8) =  6   suma 6..7 = 8
min_left (0, 7, sum <= 100) =  0   <- aguanto todo: p == l
```

## Ejemplo 2 — $k$-ésimo uno y $k$-ésimo cero

Con valores en $\{0,1\}$, `sum` cuenta los unos y `sz - sum` cuenta los ceros. **El mismo descenso sirve para los dos**, y notá que acá hay que **sumar uno** al resultado:

```cpp
// k-esimo UNO en [l, r]
int p   = t.max_right(l, r, [&](const Suma& v) { return v.sum < k; });
int ans = (p == r ? -1 : p + 1);          // -1 si no hay k unos en el rango

// k-esimo CERO: mismo descenso, otro campo
int p   = t.max_right(l, r, [&](const Suma& v) { return v.sz - v.sum < k; });
int ans = (p == r ? -1 : p + 1);

// k-esimo uno contando DESDE LA DERECHA
int p   = t.min_left(l, r, [&](const Suma& v) { return v.sum < k; });
int ans = (p == l ? -1 : p - 1);
```

Con $b = \{1, 0, 1, 1, 0, 1, 0, 0\}$ sobre $[0,7]$:

| $k$ | `max_right` | $k$-ésimo **uno** | $k$-ésimo **cero** |
|---|---|---|---|
| 1 | $-1$ | posición 0 | posición 1 |
| 2 | 1 | posición 2 | posición 4 |
| 3 | 2 | posición 3 | posición 6 |
| 4 | 4 | posición 5 | posición 7 |
| 5 | 7 | $-1$, no hay tantos | $-1$, no hay tantos |

**La regla del $+1$**: va cuando preguntás *«dónde ocurre el $k$-ésimo»*, y **no** va cuando preguntás *«hasta dónde llego»*. El descenso es idéntico; cambia solo cómo lees la respuesta. Y de hecho `sum < k` y `sum <= k - 1` son el mismo predicado en enteros, así que el $k$-ésimo uno **es** el problema de suma $\le S$ con $S = k-1$.

Detectar que no existe sale gratis con `p == r`: si la respuesta estuviera en $q \le r$, en $p = q$ el predicado ya sería falso y entonces `max_right` $\le q-1 < r$. No hace falta un `prod` extra.

## Ejemplo 3 — las cuatro variantes de umbral

Acá es donde se mezclan los signos, así que las cuatro juntas. Con un `Node` que lleve `mx` y `mn`:

| querés el tramo donde… | predicado | por qué |
|---|---|---|
| **todos** $< x$ | `v.mx < x` | el máximo del tramo tiene que quedar abajo |
| **todos** $\le x$, o sea *ninguno $> x$* | `v.mx <= x` | ídem, no estricto |
| **todos** $> x$ | `v.mn > x` | el mínimo del tramo tiene que quedar arriba |
| **todos** $\ge x$, o sea *ninguno $< x$* | `v.mn >= x` | ídem, no estricto |

Las cuatro son monótonas **siempre**, sin pedirle nada a los datos: `mx` del prefijo no decrece y `mn` no crece al extender. Esa es la diferencia con suma $\le S$, que necesita la hipótesis de no negatividad.

Con $c = \{4, 4, 7, 2, 9, 9, 1, 5\}$ sobre $[0,7]$ y $x = 5$:

```
todos  < 5  (mx <  5):  max_right =  1    c[0..1] = {4,4}, y c[2] = 7 rompe
todos <= 5  (mx <= 5):  max_right =  1    'ninguno > 5': mismo tramo
todos  > 5  (mn >  5):  max_right = -1    <- CENTINELA: c[0] = 4 no es > 5
todos >= 5  (mn >= 5):  max_right = -1    <- CENTINELA: 'ninguno < 5' falla en c[0]
```

Y de ahí salen las lecturas de tipo `lower_bound`, sumando o restando uno:

| querés… | cómo |
|---|---|
| primer $i \in [l,r]$ con $a_i \ge x$ | `max_right(l, r, mx < x) + 1` |
| primer $i$ con $a_i > x$ | `max_right(l, r, mx <= x) + 1` |
| primer $i$ con $a_i \le x$ | `max_right(l, r, mn > x) + 1` |
| primer $i$ con $a_i < x$ | `max_right(l, r, mn >= x) + 1` |
| **último** $i$ con $a_i \ge x$ | `min_left(l, r, mx < x) - 1` |
| **último** $i$ con $a_i < x$ | `min_left(l, r, mn >= x) - 1` |

Sobre el mismo $c$ con $x = 5$:

```
primer i con c[i] >= 5:  max_right(mx <  5) + 1 =  2   (c[2] = 7)
primer i con c[i]  > 5:  max_right(mx <= 5) + 1 =  2   (c[2] = 7)
ultimo i con c[i] >= 5:  min_left (mx <  5) - 1 =  7   (c[7] = 5)
ultimo i con c[i]  < 5:  min_left (mn >= 5) - 1 =  6   (c[6] = 1)
```

Esto gana sobre `std::lower_bound` en tres cosas: **no pide que el arreglo esté ordenado**, anda sobre un subrango, y sobrevive a los `set`. Cuando el arreglo *está* ordenado y el rango es completo, coincide exactamente con `lower_bound` — verificado.

Un detalle honesto: para esta familia **el acumulador no aporta nada**. Como la invariante garantiza `acc.mx < x`, resulta que `f(acc + seg[k])` equivale a `seg[k].mx < x`, o sea que la poda es puramente local. Los descensos lo resuelven bien, pero pagás una copia de `Node` por nodo que no hacía falta.

## Ejemplo 4 — tramo no decreciente

Un `Node` que no es conmutativo, y por eso es el que caza los errores de orden:

```cpp
struct ND {
    ll sz = 0, pri = 0, ult = 0;
    bool ord = true;
    ND() {}
    ND(ll x) : sz(1), pri(x), ult(x), ord(true) {}
    friend ND operator+(const ND& a, const ND& b) {
        if (a.sz == 0) return b;
        if (b.sz == 0) return a;
        ND r;
        r.sz = a.sz + b.sz;
        r.pri = a.pri;                           // el primero viene de a
        r.ult = b.ult;                           // el ultimo viene de b
        r.ord = a.ord && b.ord && a.ult <= b.pri;  // y la union tiene que pegar
        return r;
    }
};

int fin = t.max_right(l, r, [](const ND& v) { return v.ord; });  // tramo que ARRANCA en l
int ini = t.min_left (l, r, [](const ND& v) { return v.ord; });  // tramo que TERMINA en r
```

Monótono sin hipótesis: una vez que el tramo se rompe, no se arregla. Y acá el centinela **no puede** aparecer, porque un tramo de un solo elemento siempre está ordenado: `max_right` devuelve al menos $l$.

## Ejemplo 5 — el prefijo que nunca se va a negativo

El patrón para volver monótona una propiedad frágil: guardá el **peor** valor, no el actual.

```cpp
struct PB {
    ll sz = 0, sum = 0, minpref = 0;             // minpref = la peor suma de un prefijo
    PB() {}
    PB(ll x) : sz(1), sum(x), minpref(min(0LL, x)) {}
    friend PB operator+(const PB& a, const PB& b) {
        if (a.sz == 0) return b;
        if (b.sz == 0) return a;
        PB r;
        r.sz = a.sz + b.sz;
        r.sum = a.sum + b.sum;
        r.minpref = min(a.minpref, a.sum + b.minpref);
        return r;
    }
};

// hasta donde puedo ir desde l sin que la suma corrida baje de cero
int p = t.max_right(l, r, [](const PB& v) { return v.minpref >= 0; });
```

Esto **sí** funciona con negativos, al contrario de `sum <= S`: `minpref` del prefijo es no creciente al extender, así que el predicado es monótono por construcción. Es el molde de los problemas de paréntesis balanceados y de «¿me alcanza el combustible en todo el camino?».

## Otros usos del mismo molde

| problema | `Node` | $f$ | lectura |
|---|---|---|---|
| hasta dónde llego con combustible $F$ | `sum` $\ge 0$ | `sum <= F` | el resultado tal cual |
| $k$-ésimo elemento de un multiset 0/1 | `sum` | `sum < k` | $+1$ |
| tramo con todos iguales (Chtholly) | `igual, val` | `igual` | tal cual |
| primer cero en el rango (MEX, slots libres) | `mn` | `mn > 0` | $+1$ |
| $r'$ máximo con máxima subsuma $\le S$ | el monoide A del [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido) | `best <= S` | tal cual |

## Por qué acá son iterativos

Los dos descensos son **iterativos** y `const`: sin lazy no hay nada que escribir al bajar. Medido contra la versión recursiva que usa `LazySegmentTree`:

| $n$ | $q$ | largo del rango | recursivo | iterativo | mejora |
|---|---|---|---|---|---|
| $10^5$ | $10^6$ | aleatorio | 0.3810 s | **0.1787 s** | 2.13× |
| $10^5$ | $10^6$ | 16 | 0.2309 s | **0.0600 s** | 3.85× |
| $10^6$ | $10^6$ | aleatorio | 0.8251 s | **0.4507 s** | 1.83× |
| $10^6$ | $10^6$ | 16 | 0.4658 s | **0.1327 s** | 3.51× |
| $4\cdot10^6$ | $10^6$ | aleatorio | 1.0949 s | **0.6039 s** | 1.81× |
| $4\cdot10^6$ | $10^6$ | 16 | 0.5143 s | **0.1467 s** | 3.51× |

La ventaja crece con rangos cortos, donde el bucle se queda en un subárbol chico que entra en caché. En `LazySegmentTree` la misma iterativa **empata**, por el `push`: el detalle está en [su manual](LazySegmentTree.md).

Si te alcanza $O(\log^2 n)$, `lstTrue(l, r, p -> f(prod(l, p)))` del template de contest da la misma respuesta y es trivialmente correcta. Te sirve además de referencia para el stress test.

## Ejemplo completo de un problema

Máxima suma de un subarreglo de $a_l \dots a_r$, con el vacío permitido (el `Node` está en el [README](README.md#a-máxima-suma-de-un-subarreglo-con-el-vacío-permitido)):

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

$2\,SZ$ nodos, sin pool ni `reserve`: el tamaño se conoce desde el constructor. Con $SZ$ la potencia de dos que cubre $n$, el peor caso es $SZ = 2n-2$, o sea hasta $\mathbf{4n}$ nodos cuando $n$ queda justo arriba de una potencia de dos.

| $n$ | $q$ | build | $q$ sets | $q$ prods | memoria |
|---|---|---|---|---|---|
| 200 000 | 200 000 | 0.007 s | 0.037 s | 0.048 s | 20.0 MB |
| 1 000 000 | 1 000 000 | 0.027 s | 0.409 s | 0.386 s | 80.0 MB |

(con el `Node` de 5 campos del ejemplo, 40 bytes cada uno)

Los descensos no alocan nada: el iterativo usa un marco de pila y cuatro `int`.

## Reasignar el neutro

Si `T` es un tipo primitivo como `int`, `T()` es `0` y no lo podés cambiar — y para un mínimo de rango querrías $+\infty$. No hay forma de inyectar un neutro distinto: **envolvelo en un struct**. Eso es lo que la regla 2 de la familia pide de todas formas, y cuesta cuatro líneas:

```cpp
struct Mn {
    ll v = LLONG_MAX;                            // el neutro del minimo
    Mn() {}
    Mn(ll x) : v(x) {}
    friend Mn operator+(const Mn& a, const Mn& b) { return Mn(min(a.v, b.v)); }
};
```

## `dump()`: ver el estado para depurar

Devuelve el arreglo lógico completo como un `vector`, con tres propiedades que valen en los seis templates de la familia:

$$
\texttt{dump()}[i] = \texttt{get}(i), \qquad
\textstyle\bigoplus \texttt{dump()} = \texttt{all\_prod()}, \qquad
\textstyle\bigoplus_{i=l}^{r} \texttt{dump()}[i] = \texttt{prod}(l,r)
$$

Devuelve **`n` elementos, no `SZ`**: el relleno $[n, SZ)$ no es parte del arreglo lógico. (Con el constructor de un argumento `t(k)` resulta $n = SZ$, así que ahí el relleno *sí* aparece — porque en ese caso es el arreglo.)

Es el mismo nombre y el mismo contrato que [`ImplicitTreap::dump()`](../ImplicitTreap.md).

Acá es literalmente una copia de las hojas `seg[SZ .. SZ + n - 1]`: no hay nada pendiente que resolver, así que es `const` y cuesta una pasada.

```cpp
auto v = t.dump();
for (int i = 0; i < (int)v.size(); i++) cerr << v[i].sum << " ";
cerr << "\n";
```

## Verificación

Estresado contra Kadane de fuerza bruta: **107 100 rangos** sobre $n = 1..34$ con sets intercalados, junto con `PersistentSegmentTree` y `SparseSegmentTree` usando el mismo `Node`. Cero discrepancias.

Los descensos, aparte:

| test | comprobaciones |
|---|---|
| **exhaustivo** $n = 1..40$, todo $(l,r)$, todo $S$, dos monoides | 4 818 802 |
| las cuatro variantes de umbral, las dos direcciones | 480 000 |
| lecturas derivadas (primer/último índice, $\pm 1$) | 360 000 |
| suma $\le S$, $k$-ésimo uno, $k$-ésimo cero, $k$-ésimo desde la derecha | 300 000 |
| tramo no decreciente (las dos puntas), prefijo no negativo | 180 000 |
| $p-l+1$ y $r-p+1$ contra el largo real, centinela incluido | 40 000 |

Tres controles negativos sobre el descenso iterativo, los tres cazados por la suite: sacar el bucle de encoger (el bug real que apareció al adaptar la versión de ACL, que devuelve un índice **fuera** de $[l,r]$), invertir el orden de `+` en `min_left`, y bajar por el hijo izquierdo en `min_left`.

El ejemplo del problema se extrae del comentario del header, se compila tal cual con `-Wall -Wextra` y se vuelve a correr el estrés con ese struct exacto.

**Sin link de juez todavía.** El campo `Verification` del header decía `SPOJ Fenwick` antes de esta verificación; si esa sumisión era real, conviene restaurarla además de lo de acá.

### `dump()`

| test | comprobaciones |
|---|---|
| `dump()` con `Node` no conmutativo, las tres propiedades del contrato | 868 308 |

Diez controles negativos sobre los seis, los diez cazados por la suite: dar vuelta el vector, devolver `SZ` en vez de `n`, sacar el `push` de `LazySegmentTree`, invertirle el orden, visitar los hijos al revés, invertir la composición del lazy que baja, no aplicar el lazy en la hoja, y pasarle a `apply` un largo distinto de 1.
