# PolyDifference

Array de diferencias generalizado a polinomios: suma un polinomio de grado $\le K$ a un rango en
$O(K^2)$ y materializa los $n$ valores en $O(nK)$, con **un solo array** de $n + K + 2$.

Es **offline en dos fases**, y eso es lo primero que hay que tener claro:

```cpp
PolyDifference<2, mi> pd(n);                    // mi es el modular de ModInt.h
pd.add(l, r, {mi(3), mi(2), mi(1)});            // REGISTRA: no calcula nada
pd.add(l2, r2, {mi(0), mi(0), mi(5)});          // registra otro
vector<mi> a = pd.build();                      // recien aca se calcula, en O(nK)
```

`add` solo anota. `build` es lo que hace el trabajo.

## El convenio de los coeficientes

**`coef[j]` multiplica $x^j$ con $x = i - l$: es relativo al extremo izquierdo del rango, no el
índice absoluto.** Es el error número uno.

```cpp
pd.add(5, 9, {0, 1});                           // suma 0 + 1*x, con x = i - 5
// a[5] += 0,  a[6] += 1,  a[7] += 2,  a[8] += 3,  a[9] += 4
// NO:  a[7] += 7
```

Si tu polinomio está en el índice absoluto, convertilo primero: $c_0 + c_1 i$ sobre $[l, r]$ es
`{c0 + c1*l, c1}` en este convenio.

Para un grado menor que `K`, los coeficientes de arriba van en cero. El `K` del template es el
grado **máximo**, no el exacto.

## El límite real: los números, no el algoritmo

Un polinomio de grado $k$ sobre $n$ posiciones produce valores del orden de $n^k$. Medido:

| grado | mayor `n` que entra en `long long` |
|---|---|
| 1 | $9.2\cdot10^{18}$ |
| 2 | $3.0\cdot10^{9}$ |
| 3 | $2.1\cdot10^{6}$ |
| 4 | $5.5\cdot10^{4}$ |
| 5 | $6.2\cdot10^{3}$ |
| 6 | $1.4\cdot10^{3}$ |
| 7 | **512** |

**Desde grado 4 con `n` realista, usar un entero modular no es opcional.** A $n = 10^6$ y grado 7
el valor es $10^{42}$, y `__int128` llega a $1.7\cdot10^{38}$: tampoco alcanza.

Y esto **no es una limitación de esta estructura**: es que la respuesta no cabe. Cualquier
algoritmo que calcule lo mismo tiene el mismo techo.

## Contrato de `T`

| requisito | notas |
|---|---|
| `T(0)`, `T(1)`, `T(long long)` | construcción desde entero |
| `a + b`, `a - b`, `a * b` | un anillo conmutativo alcanza |

**No hace falta división ni inverso modular.** Por eso el constructor solo usa la columna $K$ de
Pascal en lugar de factoriales: así `T` puede ser un modular sin exponenciación.

Para grados bajos va `long long` directo. Desde grado 4 va el **`mi` de la librería**
([`ModInt.h`](../../number-theory/Modular%20Arithmetic/ModInt.h)), que cumple el contrato tal
cual y pesa **4 bytes**: la mitad que un modular escrito sobre `long long`, y eso se ve entero en
el pico de memoria.

## API

### Constructor

```cpp
PolyDifference<K, T> pd(int len);
```

`len` posiciones, `a[0 .. len-1]`, todas en `T(0)`. El grado `K` es de compilación a propósito:
con `K` en tiempo de ejecución harían falta vectores anidados.

**Restricciones**: $len \ge 1$. · **Complejidad**: $O(n + K^2)$.

### add

```cpp
void pd.add(int l, int r, const array<T, K + 1>& coef)
```

Registra que `a[l + x] += coef[0] + coef[1]*x + ... + coef[K]*x^K` para $x = 0 \dots r-l$.
**No calcula nada.**

**Restricciones**: $0 \le l \le r < n$. · **Complejidad**: $O(K^2)$, y toca $2(K+1)$ posiciones.

### build

```cpp
vector<T> pd.build() const
```

Los `n` valores que resultan de todo lo registrado hasta ahora.

Es `const` y **no reserva memoria aparte**: el vector que devuelve *es* el buffer de trabajo. Por
eso se puede llamar varias veces, y **cada llamada refleja los `add` hechos hasta ese momento**.
O sea que podés intercalar `add` / `build` / `add` / `build` y obtener snapshots — «offline» acá
significa «pagás $O(nK)$ por snapshot», no «una sola vez».

**Complejidad**: $O(nK)$ — son $K+1$ pasadas de suma de prefijos.

### clear

```cpp
void pd.clear()
```

Olvida todo lo registrado conservando la capacidad, para problemas con varios casos de prueba.

**Complejidad**: $O(n)$.

### size

```cpp
int pd.size() const
```

**Complejidad**: $O(1)$.

## Cómo funciona

Aplicar $K+1$ sumas de prefijos a un delta en la posición `start` da $\binom{i-start+K}{K}$. Por
lo tanto un delta en `start + m` aporta $d_m\binom{i-start-m+K}{K}$.

Esos $K+1$ polinomios en $(i - start)$ son una **base** de los de grado $\le K$, y el sistema es
**triangular** porque $\binom{K}{K} = 1$:

$$d_m = P(\text{offset} + m) - \sum_{j<m} d_j \binom{K+m-j}{K}$$

Eso se resuelve por sustitución hacia adelante en $O(K^2)$, tocando solo $K+1$ posiciones. Y
**$P$ se evalúa únicamente en argumentos chicos**, `offset .. offset+K`, que es lo que evita la
expansión binomial de $l^j$ que tendría la formulación por coeficientes absolutos.

Un `add` son dos aplicaciones de un lado: sumar el polinomio en la cola $[l, n)$ y cancelarlo en
la cola $[r+1, n)$ con el offset corrido.

### Por qué un array y no $K+1$

La alternativa natural es escribir $P(i-l)$ en el índice absoluto, $c_m = \sum_{j \ge m} a_j
\binom{j}{m}(-l)^{j-m}$, y llevar $K+1$ arrays de diferencias de primer orden, uno por
coeficiente. Funciona, pero medido a $n = q = 10^6$ y grado 7:

| | tiempo | memoria |
|---|---|---|
| $K+1$ arrays, base absoluta | 694 ms | 66 MiB |
| **un array, la base de acá** | **585 ms** | **12 MiB** |

> Esos números son de **prototipos con aritmética `long long` cruda**, y el de un array sumaba
> los prefijos in situ en lugar de devolver un buffer. La comparación entre los dos es válida
> porque comparten esas dos cosas, pero **no son comparables con la tabla de «Hasta dónde
> llega»**, que mide esta implementación con `mi`: ahí el grado 7 a $n = q = 10^6$ da 837 ms y
> 12 MiB.

La memoria es la diferencia grande: **no crece con el grado**. Lo que crece es la cantidad de
pasadas de prefijo, y esas son secuenciales y cachean bien.

## Errores frecuentes

| error | síntoma |
|---|---|
| pasar el polinomio en índice absoluto | todo corrido: con `l = 5` y `{0, 1}` esperabas `a[7] += 7` y te da `2` |
| grado 4 o más con `long long` | desborde silencioso; ver la tabla de arriba |
| creer que `add` ya calculó | lees `a` antes del `build` y está en cero |
| llamar `add` después de `build` y no volver a buildear | el `build` viejo no se actualiza solo |
| olvidar rellenar con ceros los coeficientes altos | basura de grado alto, porque `array` sin inicializar |
| reusar el objeto entre casos de prueba sin `clear()` | los updates del caso anterior siguen registrados |

## Examples

### Progresión aritmética

El caso grado 1: sumar `b, b+d, b+2d, ...` a `a[l..r]`.

```cpp
PolyDifference<1, long long> pd(n);
pd.add(l, r, {b, d});
vector<long long> a = pd.build();
```

Con `long long` acá no hay problema de desborde salvo que `b` y `d` sean enormes: grado 1 aguanta
$n$ hasta $9\cdot10^{18}$.

### Suma de cuadrados en un rango

Sumar $x^2$ a `a[l..r]`, o sea $0, 1, 4, 9, \dots$:

```cpp
PolyDifference<2, long long> pd(n);
pd.add(l, r, {0, 0, 1});
```

Grado 2 aguanta `long long` hasta $n \approx 3\cdot10^9$, así que tampoco hace falta módulo.

### Grado 7, que ya exige módulo

```cpp
PolyDifference<7, mi> pd(n);
pd.add(l, r, {0, 0, 0, 0, 0, 0, 0, mi(5)});     // suma 5*x^7
vector<mi> a = pd.build();
```

### Varios polinomios de grados distintos

Un solo objeto con el grado máximo, rellenando con ceros:

```cpp
PolyDifference<3, mi> pd(n);
pd.add(0, 9,  {mi(1), mi(0), mi(0), mi(0)});    // constante 1
pd.add(5, 14, {mi(0), mi(2), mi(0), mi(0)});    // 2x
pd.add(3, 12, {mi(0), mi(0), mi(0), mi(7)});    // 7x^3
vector<mi> a = pd.build();                      // los tres acumulados
```

### Snapshots intercalados

Como `build()` es `const` y no consume nada:

```cpp
pd.add(l1, r1, c1);
vector<mi> tras_el_primero = pd.build();
pd.add(l2, r2, c2);
vector<mi> tras_los_dos = pd.build();
```

Cada uno cuesta $O(nK)$, así que esto sirve para unos pocos cortes, no para $q$ de ellos.

### Si no es offline

Si las consultas están intercaladas en el tiempo y cada una solo ve los `add` anteriores, esta
estructura no sirve: colapsa el tiempo. Ahí va un
[`LazySegmentTree`](SegmentTree/LazySegmentTree.md) con el `Node` llevando
$\sum i^0, \dots, \sum i^K$ de su rango y el `LazyUpdate` los $K+1$ coeficientes en índice
**absoluto** — porque el `push` del template manda el mismo `LazyUpdate` a los dos hijos, así que
un lazy relativo al extremo no funcionaría.

Cuesta $O(\log n)$ por operación, pero a grado 7 el `Node` pasa a 9 `long long` y a $n = 10^6$ el
árbol son ~150 MiB contra los 20 de acá. **Si podés offline, hacelo offline.**

---

## Hasta dónde llega

Intel Core Ultra 7 155U, g++ 13.2.0 `-O2 -DNDEBUG`, proceso fijado a un core con prioridad alta,
**un proceso por corrida**; mínimo de 5 en la columna de $10^6$ y de 3 en la de $10^7$. `T` es el
**`mi` de la librería**. Cada celda es **tiempo de los `add` + tiempo del `build` · pico de
memoria**.

| grado | n = q = 10⁶ | n = q = 10⁷ |
|---|---|---|
| 1 | 67 + 3 ms · 12 MiB | 1.3 s + 30 ms · 81 MiB |
| 2 | 118 + 4 ms · 12 MiB | 3.7 s + 71 ms · 81 MiB |
| 3 | 195 + 5 ms · 12 MiB | 4.6 s + 91 ms · 81 MiB |
| 4 | 299 + 6 ms · 12 MiB | 6.1 s + 91 ms · 81 MiB |
| 5 | 413 + 7 ms · 12 MiB | 5.3 s + 64 ms · 81 MiB |
| 6 | 591 + 8 ms · 12 MiB | 7.8 s + 89 ms · 81 MiB |
| 7 | 828 + 9 ms · 12 MiB | 14.1 s + 146 ms · 81 MiB |

**El `build` es casi gratis**: 9 ms contra 828 de los `add` a grado 7. Todo el costo está en el
$O(K^2)$ por update, no en las $K+1$ pasadas de prefijo. Si tu `q` es chico y tu `n` grande, esta
estructura casi no te cobra.

**La memoria no depende del grado ni de `q`**: son dos arreglos de `n` de 4 bytes cada uno, el
`diff` y el que devuelve `build`. Grado 1 y grado 7 usan lo mismo.

> **El `T` que elijas cambia los números, y bastante.** Con un modular escrito a mano sobre
> `long long` que hace `(x % MOD + MOD) % MOD` en el constructor, el grado 7 a $n = q = 10^6$
> pasa de **828 ms a 1328**, y la memoria de **12 MiB a 20** porque el campo mide 8 bytes en
> lugar de 4. Usá el `mi` de la librería.

> La columna de $10^7$ no es monótona en el grado (el 5 da menos que el 4) y eso es **deriva
> térmica**, no una propiedad: las celdas de varios segundos varían hasta un 15% entre corridas.
> El veredicto —desde grado 2 con $q = 10^7$ te pasás de 5 s— sí es robusto.

Referencias: **5 s** y **1024 MiB**. A grado 7 entra $n = q = 10^6$ con holgura de 6x, y la
memoria nunca es el problema en ninguna celda.

## Verificación

| test | comprobaciones |
|---|---|
| contra fuerza bruta, grados 0 a 7, con `long long` y con un modular a mano | **142 202** |
| ídem con el **`mi` de la librería** | **80 325** |
| incluye `build()` repetido tras cada `add`, y `clear()` | en las mismas corridas |
| controles negativos dirigidos | **los 15 cazados** |

Los controles cubren: el signo de la cancelación, cancelar en `r` y no en `r+1`, la cancelación
sin offset y con el offset corrido en uno, `binom[m]` y `binom[j]` en lugar de `binom[m-j]`, el
signo de la sustitución, incluir `j == m`, hacer $K$ o $K+2$ pasadas de prefijo, dos sabotajes de
la extracción de Pascal, evaluar en $x+1$, y escribir en `start` en lugar de `start + m`.

Tres cosas que salieron de armar esos controles y de medir:

- **`C(K+d, d)` y `C(K+d, K)` son el mismo número** por la simetría del binomio, así que un
  control que cambiaba una columna por la otra pasó. No era un bug: probaba una identidad.
- **La guarda `start + m < diff.size()` era código muerto.** `start` llega a $r+1 \le n$ y `m` a
  $K$, así que `start + m` $\le n+K$ y `diff` mide $n+K+2$: nunca dispara. Se quitó y la cota
  quedó documentada en el código.
- **El primer juego de mediciones usó un modular escrito a mano** en lugar del `mi` de la
  librería, y eso sobreestimaba el tiempo en ~1.6x y la memoria en 1.7x. La tabla de arriba es la
  corregida.

Compila sin warnings con `-Wall -Wextra -Wpedantic` en C++17 y C++20. **Sin envío a juez
todavía.**
