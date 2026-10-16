# LazySegmentTree

Segment tree con propagación perezosa: **update de rango y consulta de rango**. El caballo de batalla de la familia. Algoritmo tomado del `lazy_segtree` de la AtCoder Library, con las máscaras de bajada adaptadas a rangos inclusivos.

Convenciones, contrato del `Node`/`LazyUpdate` y monoides de ejemplo: [README.md](README.md).

## Los diez métodos que expone

```cpp
LazySegmentTree<Node, LazyUpdate> t(v)   // n = v.size(), SZ = n redondeado a potencia de dos
LazySegmentTree<Node, LazyUpdate> t(k)   // sin vector: n pasa a ser SZ, con Node() en cada lugar
```

| método | costo | qué hace |
|---|---|---|
| constructor con `vector` | $O(n)$ | copia las hojas y hace `pull` de abajo hacia arriba |
| constructor con `int` | $O(SZ)$ | todo `Node()` y todo `LazyUpdate()` |
| `t.set(pos, val)` | $O(\log n)$ | $a_p \leftarrow x$ (baja los lazy del camino, escribe, repara) |
| `t.get(pos)` | $O(\log n)$ | el `Node` que está en $p$ |
| `t.apply(pos, upd)` | $O(\log n)$ | aplica $f$ a $a_p$ |
| `t.apply(l, r, upd)` | $O(\log n)$ | aplica $f$ a **todo** $a_l \dots a_r$ |
| `t.prod(l, r)` | $O(\log n)$ | pliega $a_l \oplus \dots \oplus a_r$ (bucle ascendente) |
| `t.all_prod()` | $\mathbf{O(1)}$ | pliega todo: es `seg[1]` |
| `t.dump()` | $O(n)$ | vuelca el arreglo entero, para depurar (**no `const`**) |
| `t.max_right(l, r, pred)` | $O(\log n)$ | la mayor $p$ con $f(\text{prod}(l,p))$, o $l-1$ |
| `t.min_left(l, r, pred)` | $O(\log n)$ | la menor $p$ con $f(\text{prod}(p,r))$, o $r+1$ |

Privados quedan `pull`, `all_apply`, `push` y los dos recursivos de los descensos.

**Ninguno es `const`**, ni siquiera `prod`: el `push` escribe. Es la diferencia visible con `SegmentTree`, donde `prod`, `get` y los dos descensos sí lo son.

## Cómo está armado por dentro

Dos arreglos planos, sin punteros ni nodos alocados:

- `seg` de $2\,SZ$ posiciones — el agregado de cada nodo
- `lazy` de $SZ$ posiciones — solo los **nodos internos** tienen lazy pendiente

con $SZ$ la menor potencia de dos $\ge n$, y $LOG = \log_2 SZ$.

| | |
|---|---|
| raíz | `seg[1]`, cubre $[0,\ SZ-1]$ |
| hijos de `x` | `seg[2x]` (izquierdo) y `seg[2x + 1]` (derecho) |
| padre de `x` | `seg[x / 2]` |
| **hoja de la posición $p$** | **`seg[SZ + p]`** — ahí viven los rangos de un solo elemento |
| nodos internos | `seg[1] .. seg[SZ - 1]`, y son los únicos con `lazy[x]` |
| hojas | `seg[SZ] .. seg[2·SZ - 1]`, sin lazy (no tienen hijos a quién bajárselo) |

Con $n = 8$ (y entonces $SZ = 8$, $LOG = 3$):

```
                       1 = [0,7]
            2 = [0,3]              3 = [4,7]
      4=[0,1]    5=[2,3]     6=[4,5]    7=[6,7]
    8=[0] 9=[1] 10=[2] 11=[3] 12=[4] 13=[5] 14=[6] 15=[7]
```

### La invariante del lazy, que es lo único que hay que entender

$$
\texttt{seg[x]} \;=\; \text{el agregado VERDADERO del subárbol de } x
$$

$$
\texttt{lazy[x]} \;=\; \text{lo que les falta aplicar a los HIJOS de } x
$$

Eso lo mantiene `all_apply`:

```cpp
void all_apply(int k, const LazyUpdate& f) {
    seg[k] *= f;                 // el valor se actualiza YA
    if (k < SZ) lazy[k] *= f;    // y solo un nodo interno tiene que recordarlo
}
```

De esa invariante salen tres consecuencias prácticas:

**`seg[x]` se puede leer sin `push`.** Los descensos y `prod` consultan agregados de nodos sin bajar nada: ya están al día. El `push` hace falta únicamente antes de mirar a los **hijos**.

**`get(p)` es $O(\log n)$ y no $O(1)$.** Antes de leer `seg[SZ + p]` hay que bajar los lazy pendientes de los $LOG$ ancestros. En `SegmentTree` no hay nada pendiente y el `get` es $O(1)$.

**El `push` es incondicional, y es a propósito.** Baja el lazy siempre, sin chequear si es la identidad. Lo probé reordenando el chequeo de disjunto para evitar algunos `push`: **4602 de 5000 sumas y 2237 de 5000 mínimos salieron mal**. El `push` sin condición es lo que mantiene la invariante; sacarlo la rompe, no ahorra trabajo.

## Todos los métodos, con resultados reales

Con $a = \{3, 1, 4, 1, 5, 9, 2, 6\}$ y el `Node` de cuatro campos (`size, sum, mx, mn`) más el `Upd` de assign+add del [README](README.md#b-suma-máximo-y-mínimo-con-assign-y-add-de-rango):

```cpp
vector<Node> iv(8);
for (int i = 0; i < 8; i++) iv[i] = Node(a[i]);
LazySegmentTree<Node, LazyUpdate> t(iv);     // n = 8, SZ = 8, LOG = 3
```

| llamada | `size` | `sum` | `mx` | `mn` |
|---|---|---|---|---|
| `prod(0, 7)` | 8 | 31 | 9 | 1 |
| `prod(2, 4)` | 3 | 10 | 5 | 1 |
| `all_prod()` | 8 | 31 | 9 | 1 |

`get(5).sum` da 9. Notá que `all_prod()` y `prod(0, 7)` dan lo mismo, pero `all_prod` es $O(1)$.

Ahora los updates de rango:

```cpp
t.apply(2, 5, LazyUpdate::add(10));      // a = {3, 1, 14, 11, 15, 19, 2, 6}
```

| llamada | `size` | `sum` | `mx` | `mn` |
|---|---|---|---|---|
| `prod(0, 7)` | 8 | 71 | 19 | 1 |
| `prod(2, 5)` | 4 | 59 | 19 | 11 |

```cpp
t.apply(0, 3, LazyUpdate::assign(7));    // a = {7, 7, 7, 7, 15, 19, 2, 6}
```

| llamada | `size` | `sum` | `mx` | `mn` |
|---|---|---|---|---|
| `prod(0, 7)` | 8 | 70 | 19 | 2 |
| `prod(0, 3)` | 4 | 28 | 7 | 7 |

y `get(2).sum` da 7, o sea que el assign se ve a través del lazy pendiente.

Update de punto y `set`, que son cosas distintas:

```cpp
t.apply(6, LazyUpdate::add(100));        // get(6).sum == 102   (SUMA sobre lo que habia)
t.set(6, Node(2));                       // get(6).sum == 2     (REEMPLAZA)
```

**`apply(p, f)` compone, `set(p, x)` sobrescribe.** Los dos cuestan $O(\log n)$ y los dos bajan los lazy del camino antes de tocar la hoja.

# Los dos descensos

## Qué devuelven, y el centinela

$$
\texttt{max\_right}(l,r,f) \;=\; \max\{\, p \in [l,r] \;:\; f(\text{prod}(l,p)) \,\}, \qquad l-1 \text{ si el conjunto es vacío}
$$

$$
\texttt{min\_left}(l,r,f) \;=\; \min\{\, p \in [l,r] \;:\; f(\text{prod}(p,r)) \,\}, \qquad r+1 \text{ si el conjunto es vacío}
$$

`max_right` ancla en $l$ y acumula **prefijos**; `min_left` ancla en $r$ y acumula **sufijos**.

**El centinela, explícito:**

| caso | `max_right` devuelve | `min_left` devuelve |
|---|---|---|
| $f$ falla ya en el primer elemento | $l - 1$ **(centinela)** | $r + 1$ **(centinela)** |
| $f$ aguanta todo el rango | $r$ | $l$ |

Y la trampa: **$l-1$ y $r+1$ pueden ser índices válidos.** Con $l = 3$ el centinela es $2$, una posición que existe.

```cpp
if (p == l - 1) { /* ninguna posicion cumple */ }     // asi
if (p < 0)      { /* MAL: solo funciona si l == 0 */ }
```

Estos centinelas están elegidos para que el **largo del tramo salga sin ramas**:

$$
\text{largo} = p - l + 1 \ \ (\texttt{max\_right}), \qquad \text{largo} = r - p + 1 \ \ (\texttt{min\_left})
$$

En el centinela dan $0$, en el otro extremo dan el intervalo completo, y nunca hace falta un `if`.

## Qué le piden a $f$

$f$ tiene que ser **monótona** al extender el rango: $\texttt{T T T F F F}$, una vez falsa falsa para siempre. Para `max_right`:

$$
f(\text{prod}(l,p)) = \texttt{false} \;\Longrightarrow\; f(\text{prod}(l,p')) = \texttt{false} \quad \forall\, p' > p
$$

Si no, la poda saltea un subárbol donde estaba la respuesta y **devuelve algo incorrecto en silencio** — medido, 5.6 % de respuestas mal con sumas que incluyen negativos.

$f$ recibe el `Node` acumulado y **nunca** se la llama sobre `Node()` pelado, así que no hace falta que $f(\texttt{Node()})$ sea verdadera — la AtCoder Library sí lo exige con un `assert`, y eso rechaza predicados como `mx < x` con $x \le 0$ que acá funcionan bien.

**Los descensos conviven con el lazy sin que hagas nada.** Leen agregados ya actualizados (la invariante de arriba) y hacen `push` solo cuando bajan. Todos los ejemplos de abajo están verificados con `add` y `assign` de rango intercalados.

## Ejemplo 1 — suma $\le S$

Requiere valores **no negativos**: si no, la suma del prefijo no es monótona.

```cpp
int p = t.max_right(l, r, [&](const Node& v) { return v.sum <= S; });
// a[l..p] suma <= S.  largo = p - l + 1
```

Sobre $a = \{7, 7, 7, 7, 15, 19, 2, 6\}$ (el estado tras los dos `apply` de arriba), rango $[0,7]$:

```
max_right(0, 7, sum <=    0) = -1   largo = 0   <- CENTINELA l-1
max_right(0, 7, sum <=    6) = -1   largo = 0   <- CENTINELA: a[0] = 7 > 6
max_right(0, 7, sum <=   28) =  3   largo = 4   suma 0..3 = 28, con a[4] = 15 se pasa
max_right(0, 7, sum <= 1000) =  7   largo = 8   <- aguanto todo

min_left (0, 7, sum <=    0) =  8   largo = 0   <- CENTINELA r+1
min_left (0, 7, sum <=    8) =  6   largo = 2   suma 6..7 = 8
min_left (0, 7, sum <= 1000) =  0   largo = 8   <- aguanto todo
```

## Ejemplo 2 — $k$-ésimo uno y $k$-ésimo cero

Con valores en $\{0,1\}$: `sum` cuenta los unos y `size - sum` cuenta los ceros. Acá **sí** va el $+1$.

```cpp
// k-esimo UNO en [l, r]
int p   = t.max_right(l, r, [&](const Node& v) { return v.sum < k; });
int ans = (p == r ? -1 : p + 1);          // -1 si no hay k unos en el rango

// k-esimo CERO: mismo descenso, otro campo
int p   = t.max_right(l, r, [&](const Node& v) { return v.size - v.sum < k; });
int ans = (p == r ? -1 : p + 1);

// k-esimo uno contando DESDE LA DERECHA
int p   = t.min_left(l, r, [&](const Node& v) { return v.sum < k; });
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

**La regla del $+1$**: va cuando preguntás *«dónde ocurre el $k$-ésimo»*, y no va cuando preguntás *«hasta dónde llego»*. El descenso es el mismo. De hecho `sum < k` y `sum <= k - 1` son el mismo predicado en enteros, así que el $k$-ésimo uno **es** suma $\le S$ con $S = k - 1$.

El `p == r` detecta la inexistencia sin un `prod` extra: si la respuesta estuviera en $q \le r$, en $p = q$ el predicado ya sería falso y `max_right` daría $\le q-1 < r$.

Esto se combina con el lazy: un `apply(l, r, assign(1))` convierte un rango en todos unos y el $k$-ésimo uno sigue funcionando, sin reconstruir nada.

## Ejemplo 3 — las cuatro variantes de umbral

| querés el tramo donde… | predicado | por qué |
|---|---|---|
| **todos** $< x$ | `v.mx < x` | el máximo del tramo tiene que quedar abajo |
| **todos** $\le x$, o sea *ninguno $> x$* | `v.mx <= x` | ídem, no estricto |
| **todos** $> x$ | `v.mn > x` | el mínimo del tramo tiene que quedar arriba |
| **todos** $\ge x$, o sea *ninguno $< x$* | `v.mn >= x` | ídem, no estricto |

Las cuatro son monótonas **siempre**, sin hipótesis sobre los datos: `mx` del prefijo no decrece y `mn` no crece al extender. Esa es la diferencia con suma $\le S$.

Sobre $a = \{7, 7, 7, 7, 15, 19, 2, 6\}$ con $x = 7$, rango $[0,7]$:

```
todos  < 7  (mx <  7):  max_right = -1    <- CENTINELA: a[0] = 7 no es < 7
todos <= 7  (mx <= 7):  max_right =  3    'ninguno > 7': a[0..3] = 7, y a[4] = 15 rompe
todos  > 7  (mn >  7):  max_right = -1    <- CENTINELA: a[0] = 7 no es > 7
todos >= 7  (mn >= 7):  max_right =  5    'ninguno < 7': a[0..5], y a[6] = 2 rompe
```

Mirá el contraste entre la primera y la segunda fila, y entre la tercera y la cuarta: cambiar estricto por no estricto mueve la respuesta de un centinela a una posición real. Es el error de signo más común de todos.

Las lecturas derivadas, sumando o restando uno:

| querés… | cómo |
|---|---|
| primer $i \in [l,r]$ con $a_i \ge x$ | `max_right(l, r, mx < x) + 1` |
| primer $i$ con $a_i > x$ | `max_right(l, r, mx <= x) + 1` |
| primer $i$ con $a_i \le x$ | `max_right(l, r, mn > x) + 1` |
| primer $i$ con $a_i < x$ | `max_right(l, r, mn >= x) + 1` |
| **último** $i$ con $a_i \ge x$ | `min_left(l, r, mx < x) - 1` |
| **último** $i$ con $a_i < x$ | `min_left(l, r, mn >= x) - 1` |

Sobre el mismo $a$ con $x = 7$:

```
primer i con a[i] > 7:  max_right(mx <= 7) + 1 =  4   (a[4] = 15)
ultimo i con a[i] < 7:  min_left (mn >= 7) - 1 =  7   (a[7] = 6)
```

Esto es lo que resuelve *Addition and First element at least X* de Codeforces EDU, que es uno de los dos problemas con los que este template está verificado en juez.

## Otros usos del mismo molde

| problema | `Node` | $f$ | lectura |
|---|---|---|---|
| hasta dónde llego con combustible $F$ | `sum` $\ge 0$ | `sum <= F` | tal cual |
| prefijo que nunca baja de cero (paréntesis) | `sum, minpref` | `minpref >= 0` | tal cual |
| tramo no decreciente | `pri, ult, ord` | `ord` | tal cual |
| tramo con todos iguales (Chtholly) | `igual, val` | `igual` | tal cual |
| primer cero del rango (MEX, slots libres) | `mn` | `mn > 0` | $+1$ |

El de paréntesis es el patrón general para volver monótona una propiedad frágil: guardá el **peor** valor visto, no el actual. `minpref` del prefijo es no creciente al extender, así que funciona incluso con negativos — al contrario de `sum <= S`.

## Por qué acá son recursivos (y en `SegmentTree` iterativos)

No es un descuido. Probé la versión iterativa en este template y **empata**:

| $n$ | $q$ | recursiva | iterativa | mejora |
|---|---|---|---|---|
| $10^5$ | $10^6$ | 0.6273 s | 0.4675 s | 1.34× |
| $10^6$ | $10^5$ | 0.1173 s | 0.1180 s | **0.99×** |
| $10^6$ | $10^6$ | 1.1898 s | 1.1033 s | 1.08× |
| $4\cdot10^6$ | $10^6$ | 1.6261 s | 1.5740 s | 1.03× |
| $4\cdot10^6$ | $10^7$ | 23.04 s | 20.76 s | 1.11× |

La causa está medida: la iterativa acotada tiene que limpiar los **dos** caminos del borde por adelantado —las piezas canónicas del borde derecho cuelgan del camino hasta $r$, no del de $l$— los use o no, y eso le da **1.51× más `push`**:

| $n$ | `push`/consulta recursiva | iterativa |
|---|---|---|
| $10^5$ | 29.6 | 44.9 |
| $10^6$ | 35.9 | 54.2 |
| $4\cdot10^6$ | 39.8 | 60.2 |

La recursiva empuja solo donde efectivamente baja. En `SegmentTree`, donde no hay `push`, la misma iterativa gana 1.8×–3.9×. **La API es idéntica en los dos**, así que la diferencia no se ve desde afuera y los templates siguen siendo intercambiables.

Si solo te interesa el prefijo o el sufijo completo, la firma de ACL sin $r$ es apenas $1.03\times$ más rápida acá que pasarle $r = n-1$ a esta. No vale una variante aparte.

## Ejemplo completo de un problema

Suma, máximo y mínimo de $a_l \dots a_r$, con assign y add de rango (el `Node` y el `Upd` están en el [README](README.md#b-suma-máximo-y-mínimo-con-assign-y-add-de-rango)):

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

$$
(a \oplus b) \otimes f \;=\; (a \otimes f) \oplus (b \otimes f)
$$

Si tu update no distribuye sobre tu agregado, no hay forma de escribir `operator*=` que funcione — el problema no es la implementación, es que la operación no es compatible con la propagación perezosa.

## Memoria

$2\,SZ$ nodos más $SZ$ lazy, sin pool ni `reserve`.

| $n$ | $q$ | build | $q$ applies | $q$ prods | memoria |
|---|---|---|---|---|---|
| 200 000 | 200 000 | 0.008 s | 0.112 s | 0.083 s | 22.0 MB |
| 1 000 000 | 1 000 000 | 0.033 s | 0.886 s | 0.798 s | 88.0 MB |

(con el `Node` de 4 campos y el `Upd` de 3 del ejemplo)

Y con los descensos, midiendo $q$ de ellos sobre el `Node` de 4 campos:

| $n$ | $q$ | tiempo | memoria |
|---|---|---|---|
| $10^5$ | $10^6$ | 0.627 s | 34 MB |
| $10^6$ | $10^6$ | 1.190 s | 138 MB |
| $4\cdot10^6$ | $10^6$ | 1.626 s | 494 MB |
| $8\cdot10^6$ | $10^5$ | — | **954 MB** |

A $n = 8\cdot10^6$ estás al borde del GiB: si necesitás más, hay que adelgazar el `Node` o construir en streaming. El pico incluye el `vector<Node>` de entrada, que es un tercio del total.

Los descensos recursivos usan $\sim 124$ bytes de pila por nivel: 2.4 KB a $n = 10^6$, 3.1 KB a $n = 1.6\cdot10^7$. Irrelevante contra el límite de pila.

Para dimensionar: en la carga de afín de rango más suma de rango a $n = q = 5\cdot10^5$ tarda **0.37 s** con `-O2 -march=native`. Esa es la referencia contra la que se mide [`ImplicitTreap`](../ImplicitTreap.md), que hace lo mismo 1.8× más lento a cambio de poder insertar y borrar.

## `dump()`: ver el estado para depurar

Devuelve el arreglo lógico completo como un `vector`, con tres propiedades que valen en los seis templates de la familia:

$$
\texttt{dump()}[i] = \texttt{get}(i), \qquad
\textstyle\bigoplus \texttt{dump()} = \texttt{all\_prod()}, \qquad
\textstyle\bigoplus_{i=l}^{r} \texttt{dump()}[i] = \texttt{prod}(l,r)
$$

Devuelve **`n` elementos, no `SZ`**: el relleno $[n, SZ)$ no es parte del arreglo lógico. (Con el constructor de un argumento `t(k)` resulta $n = SZ$, así que ahí el relleno *sí* aparece — porque en ese caso es el arreglo.)

Es el mismo nombre y el mismo contrato que [`ImplicitTreap::dump()`](../ImplicitTreap.md).

**Acá `dump()` no es `const`**, al contrario de los otros cinco: baja todos los lazy pendientes antes de leer las hojas, con

```cpp
for (int k = 1; k < SZ; k++) push(k);
```

El orden creciente es correcto por construcción, porque el padre de `k` es `k / 2 < k` y entonces ya se bajó cuando llegamos a `k`.

La alternativa era arrastrar el lazy como parámetro —que es lo que hacen los otros cuatro templates, y lo dejaría `const`— pero eso es un camino de código nuevo con un argumento de correctitud nuevo, para un método cuyo propósito es que confíes en lo que ves. El `push` reusa la máquina que ya usa `get`. Y como `prod`, `get`, `set` y `apply` tampoco son `const` acá, no rompe ninguna expectativa.

El dump funciona con lazy pendiente sin resolver: está verificado llamándolo justo después de un `apply` de rango.

```cpp
auto v = t.dump();
for (int i = 0; i < (int)v.size(); i++) cerr << v[i].sum << " ";
cerr << "\n";
```

## Verificación

- **Codeforces EDU (ITMO), submission 394467936** — *C. Addition and First element at least X*, **Accepted, 125 ms / 3000 KB** con `-std=c++23`. Es la verificación en juez de **`max_right`**: el problema pide *el menor j ≥ l con a[j] ≥ x* bajo add de rango, y sale con el predicado `mx < x` más la lectura `max_right(l, n-1, f) + 1`. El código de envío está en `EDU_AdditionAndFirstElementAtLeastX.cpp`, en la raíz del repo.
- **Codeforces EDU (ITMO), *Assignment and Maximal Segment***, aceptado en su momento; el número de submission no quedó registrado.
- Estresado contra fuerza bruta: **69 440 rangos** sobre $n = 1..30$ con assign y add mezclados, verificando suma, máximo y mínimo a la vez, junto con `PersistentLazySegmentTree` y `SparseLazySegmentTree` usando el mismo par.
- Contrastado contra el `lazy_segtree` de la AtCoder Library en los casos borde que su documentación enumera ($n = 10^8$ para las operaciones $O(n)$, $n = 5\cdot10^6$ para las $O(\log n)$): rendimiento equivalente, diferencias dentro del ruido.

Los descensos, aparte:

| test | comprobaciones |
|---|---|
| los siete problemas, con `apply(add/assign)` intercalado | 381 683 |
| las cuatro variantes de umbral, las dos direcciones | 480 000 |
| lecturas derivadas (primer/último índice, $\pm 1$) | 360 000 |
| suma $\le S$, $k$-ésimo uno, $k$-ésimo cero, $k$-ésimo desde la derecha | 300 000 |
| equivalencia con la firma sin $r$ de ACL | 1 076 612 |
| coinciden con los de `SegmentTree` usando el mismo `Node` | 40 000 |

Tres controles negativos, los tres cazados por la suite: invertir el orden de `+` en `min_left`, podar sin chequear si el predicado rompe, y sacar el corte temprano. El primero **solo** lo detecta un `Node` no conmutativo, porque la suma conmuta — un test con sumas no prueba nada sobre el orden.

### `dump()`

| test | comprobaciones |
|---|---|
| `dump()` con lazy pendiente sin resolver, `Node` no conmutativo | 873 828 |

Diez controles negativos sobre los seis, los diez cazados por la suite: dar vuelta el vector, devolver `SZ` en vez de `n`, sacar el `push` de `LazySegmentTree`, invertirle el orden, visitar los hijos al revés, invertir la composición del lazy que baja, no aplicar el lazy en la hoja, y pasarle a `apply` un largo distinto de 1.
