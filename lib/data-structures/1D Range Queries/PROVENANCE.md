# Procedencia

De dónde sale cada template de esta carpeta y desde cuándo existe, para poder acreditarlo ante un
juez. Todo lo de acá es verificable: o apunta a una fuente pública, o apunta a un commit con fecha
en el historial de este repositorio.

**Repositorio**: <https://github.com/gopoma/competitive-programming>

La prueba de que un template pre-existe a una fecha **es el commit que lo introdujo**, no una URL.
Cualquiera puede comprobarlo:

```bash
git log --follow --diff-filter=A --format="%H %ad" -- "<ruta del archivo>"
```

## Divulgación de asistencia de IA

Parte del trabajo de esta carpeta se hizo con asistencia de IA (Claude). **No está oculto**: esos
commits llevan el trailer `Co-Authored-By: Claude Opus 5 <noreply@anthropic.com>` y se listan con

```bash
git log --grep="Co-Authored-By: Claude"
```

Son **10 commits**, del **2026-10-15 al 2026-10-16**. Cubren: `max_right` / `min_left` en las siete
estructuras, `dump()`, los descensos de dos versiones del persistente, la convención de nombres
`NodeX`, la normalización del `shift` de `rotate`, la reescritura de los siete manuales y los
benchmarks.

**Lo que esa asistencia no cubre**: los algoritmos, que vienen de las fuentes públicas de la tabla,
y la estructura base de los templates, que es anterior a esas fechas.

## Tabla por archivo

Tres fechas, porque las tres dicen cosas distintas y solo la tercera responde *"¿el código que estoy
enviando ya existía?"*:

| archivo | lineaje | en la ruta actual | último cambio | fuente del algoritmo |
|---|---|---|---|---|
| `SegmentTree/SegmentTree.h` | `fff9437` 2024-02-06 | `f3e171e` 2026-10-03 | `7c4bf9d` 2026-10-16 | <https://codeforces.com/blog/entry/18051> (Al.Cash, *Efficient and easy segment trees*) y <https://github.com/kth-competitive-programming/kactl> |
| `SegmentTree/LazySegmentTree.h` | `f886e76` 2026-10-01 | `f3e171e` 2026-10-03 | `9cb3302` 2026-10-16 | <https://github.com/atcoder/ac-library> · <https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html> |
| `SegmentTree/PersistentSegmentTree.h` | `f886e76` 2026-10-01 | `f3e171e` 2026-10-03 | `12bbaae` 2026-10-15 | propio, algoritmo según <https://usaco.guide/adv/persistent> |
| `SegmentTree/PersistentLazySegmentTree.h` | `6133f44` 2026-10-02 | `f3e171e` 2026-10-03 | `9cb3302` 2026-10-16 | propio, algoritmo según <https://github.com/atcoder/ac-library> |
| `SegmentTree/SparseSegmentTree.h` | `f3e171e` 2026-10-03 | `f3e171e` 2026-10-03 | `12bbaae` 2026-10-15 | propio, algoritmo según <https://usaco.guide/plat/sparse-segtree> |
| `SegmentTree/SparseLazySegmentTree.h` | `f3e171e` 2026-10-03 | `f3e171e` 2026-10-03 | `9cb3302` 2026-10-16 | propio, algoritmo según <https://usaco.guide/plat/sparse-segtree> |
| `ImplicitTreap.h` | `d1d5dd4` 2026-10-05 | `d1d5dd4` 2026-10-05 | `e4f7199` 2026-10-16 | propio |

**"propio" significa propio**: el código no se copió de ningún lado. Solo el algoritmo es conocido y
la columna dice de dónde se estudió. No hay una URL de la cual extraerlo porque no existe.

### El lineaje de 2024 de `SegmentTree.h` no quiere decir lo que parece

La fecha de 2024-02-06 sale de seguir renames con `--follow`, y **el archivo de entonces no es el
de ahora**: eran 52 líneas en `lib/data-structures/SegmentTree.h`, y el move del 2026-10-03 que lo
trajo a su ruta actual está marcado **R063** por git, o sea 63% de similitud — se reescribió
sustancialmente. Hoy son 237 líneas.

Si lo que hay que acreditar es que *el código enviado* pre-existe, la fecha honesta es la de la
columna **último cambio**, no la del lineaje. Las dos primeras columnas están para que se vea la
historia completa, no para elegir la que convenga.

### El caso de `max_right` / `min_left`

La **idea y la firma** (predicado como parámetro, búsqueda binaria descendiendo el árbol) son de
AtCoder Library: <https://atcoder.github.io/ac-library/production/document_en/segtree.html>.

La versión de acá difiere a propósito en dos cosas: trabaja sobre un rango **cerrado** `[l, r]` en
lugar de un prefijo o sufijo completo, y usa centinelas `l - 1` / `r + 1`. Esa adaptación es propia
y se escribió **con asistencia de IA el 2026-10-15 y 2026-10-16** (commits `12bbaae` y `8b574f6`).

## Verificación en juez

Lo que está efectivamente verificado, con el envío como prueba:

| template | juez | envío |
|---|---|---|
| `LazySegmentTree.h` | Codeforces EDU, *Addition and First element at least X* | **394467936**, AC 125 ms |
| `ImplicitTreap.h` | Library Checker, *Range Reverse Range Sum* | <https://judge.yosupo.jp/submission/407984>, AC 303 ms |

Los otros cinco no tienen envío a juez. `LC_RangeKthSmallest.cpp` está escrito y verificado
localmente contra fuerza bruta, pendiente de enviar a
<https://judge.yosupo.jp/problem/range_kth_smallest>.

## Lo que esta tabla no puede probar

1. **Que el repositorio sea público en la fecha del contest.** El historial prueba cuándo se
   escribió el código en esta máquina; para que un tercero lo verifique necesita poder ver el
   repositorio.
2. **Que las fechas de los commits no se hayan alterado.** Un commit local se puede fechar como
   uno quiera. Lo que no se puede falsificar es la fecha en que GitHub recibió el push, así que si
   hace falta prueba fuerte, lo que vale es el push, no el commit.
