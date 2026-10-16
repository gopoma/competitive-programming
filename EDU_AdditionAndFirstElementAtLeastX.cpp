// Codeforces EDU — ITMO Academy, Segment Tree part 2
// C. Addition and First element at least X
//
//   1 l r v   sumar v a a[l .. r-1]            <- SEMIABIERTO [l, r), 0-indexado
//   2 x l     el menor j >= l con a[j] >= x, o -1   <- ojo el orden: x y DESPUES l
//
// n, m <= 1e5;  0 <= v <= 1e4;  0 <= x <= 1e9;  indices desde 0.
//
// Por que max_right: "el menor j >= l con a[j] >= x" es lo mismo que
// "el mayor p tal que TODO a[l..p] es < x", mas uno. Y el predicado mx < x es monotono
// siempre, porque el maximo de un prefijo no decrece al extenderlo: no hace falta pedirle
// nada a los datos. (Con suma seria distinto: ahi haria falta que v fuera no negativo.)
//
// El centinela encaja solo: si a[l] >= x, max_right devuelve l-1 y la respuesta es l.
// Y max_right nunca puede devolver n-1 habiendo respuesta, asi que p == n-1 es exactamente
// el caso "no existe" -> -1.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct LazyUpdate {                             // alcanza con add: el problema no tiene assign
    ll a = 0;

    LazyUpdate() {}
    LazyUpdate(ll x) : a(x) {}

    LazyUpdate& operator*=(const LazyUpdate& f) {
        a += f.a;                               // dos add se acumulan
        return *this;
    }
};

struct Node {                                   // alcanza con el maximo
    ll sz = 0, mx = 0;                          // sz == 0 es el rango vacio, la identidad de +

    Node() {}
    Node(ll x) : sz(1), mx(x) {}

    friend Node operator+(const Node& a, const Node& b) {
        if(a.sz == 0) {
            return b;
        }

        if(b.sz == 0) {
            return a;
        }

        Node res;
        res.sz = a.sz + b.sz;
        res.mx = max(a.mx, b.mx);
        return res;
    }

    Node& operator*=(const LazyUpdate& f) {
        if(sz == 0) {                           // la identidad se queda identidad
            return *this;
        }

        mx += f.a;
        return *this;
    }
};

/**
 * Description: Segment tree with lazy propagation. Node() neutral, a + b associative,
 *   node *= f applies an update to a whole interval, f *= g stacks g after f.
 *   max_right / min_left descend the tree to find a boundary, like the AtCoder Library.
 * Time: O(n) build, O(log n) per operation, O(1) all_prod
 * Source: atcoder.github.io/ac-library. Manual and stress tests: LazySegmentTree.md
 * Verification: codeforces.com/edu submission 394467936, 125 ms (uses max_right)
 */

template <class Node, class LazyUpdate>
struct LazySegmentTree {
  public:
    LazySegmentTree() : LazySegmentTree(0) {}

    explicit LazySegmentTree(int len) {
        SZ = 1, LOG = 0;

        while (SZ < max(1, len)) {
            SZ *= 2;
            ++LOG;
        }

        n = SZ;                                 // sin vector, n es el tamano con padding
        seg.assign(2 * SZ, Node());             // todo identidad, no hace falta pull:
        lazy.assign(SZ, LazyUpdate());          // Node() + Node() == Node()
    }

    explicit LazySegmentTree(const vector<Node>& init) : n(int(init.size())) {
        SZ = 1, LOG = 0;

        while (SZ < max(1, n)) {
            SZ *= 2;
            ++LOG;
        }

        seg.assign(2 * SZ, Node());
        lazy.assign(SZ, LazyUpdate());

        for (int i = 0; i < n; i++) {
            seg[SZ + i] = init[i];
        }

        for (int i = SZ - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void set(int pos, Node val) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        seg[pos] = val;

        for (int i = 1; i <= LOG; i++) {
            pull(pos >> i);
        }
    }

    Node get(int pos) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        return seg[pos];
    }

    Node prod(int l, int r) {
        assert(0 <= l && l <= r && r < n);

        l += SZ, r += SZ;                       // hojas inclusivas: seg[l] .. seg[r]

        for (int i = LOG; i >= 1; i--) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {                 // l no arranca su bloque de 2^i
                push(l >> i);
            }

            if ((r & m) != m) {                 // r no termina su bloque de 2^i
                push(r >> i);
            }
        }

        Node sml, smr;

        while (l <= r) {
            if (l & 1) {                        // l es hijo derecho: su padre se sale
                sml = sml + seg[l++];
            }

            if (!(r & 1)) {                     // r es hijo izquierdo: su padre se sale
                smr = seg[r--] + smr;
            }

            l >>= 1, r >>= 1;
        }

        return sml + smr;
    }

    Node all_prod() const {
        return seg[1];
    }

    // Vuelca el arreglo logico para depurar: dump()[i] es exactamente lo que da get(i).
    // NO es const: baja todos los lazy pendientes, igual que get hace sobre un solo camino.
    // El orden k = 1 .. SZ-1 es correcto por construccion, porque el padre de k es k / 2 < k.
    vector<Node> dump() {
        for (int k = 1; k < SZ; k++) {
            push(k);
        }

        return vector<Node>(seg.begin() + SZ, seg.begin() + SZ + n);
    }

    void apply(int pos, LazyUpdate upd) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        seg[pos] *= upd;

        for (int i = 1; i <= LOG; i++) {
            pull(pos >> i);
        }
    }

    void apply(int l, int r, LazyUpdate upd) {
        assert(0 <= l && l <= r && r < n);

        l += SZ, r += SZ;                       // hojas inclusivas: seg[l] .. seg[r]

        for (int i = LOG; i >= 1; i--) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {
                push(l >> i);
            }

            if ((r & m) != m) {
                push(r >> i);
            }
        }

        int l2 = l, r2 = r;

        while (l <= r) {
            if (l & 1) {
                all_apply(l++, upd);
            }

            if (!(r & 1)) {
                all_apply(r--, upd);
            }

            l >>= 1, r >>= 1;
        }

        l = l2, r = r2;

        for (int i = 1; i <= LOG; i++) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {
                pull(l >> i);
            }

            if ((r & m) != m) {
                pull(r >> i);
            }
        }
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template <class F>
    int max_right(int l, int r, F pred) {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_izq(l, r, 1, 0, SZ - 1, acc, pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template <class F>
    int min_left(int l, int r, F pred) {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_der(l, r, 1, 0, SZ - 1, acc, pred) + 1;
    }


  private:
    int n, SZ, LOG;
    vector<Node> seg;
    vector<LazyUpdate> lazy;

    void pull(int k) {
        seg[k] = seg[2 * k] + seg[2 * k + 1];
    }

    // Keeps seg[k] equal to the true aggregate of the subtree at k: f lands on the value
    // right away, and only an internal node has to remember it for its children.
    void all_apply(int k, const LazyUpdate& f) {
        seg[k] *= f;

        if (k < SZ) {
            lazy[k] *= f;
        }
    }

    void push(int k) {
        all_apply(2 * k, lazy[k]);
        all_apply(2 * k + 1, lazy[k]);
        lazy[k] = LazyUpdate();
    }

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, L - 1).
    // El agregado se lee sin push: all_apply mantiene seg[ind] siempre al dia.
    template <class F>
    int corte_izq(int l, int r, int ind, int L, int R, Node& acc, F f) {
        if (R < l || r < L) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if (l <= L && R <= r) {                 // el nodo entra completo en [l, r]
            Node t = acc + seg[ind];            // acc a la izquierda, el nodo a la derecha

            if (f(t)) {
                acc = t;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if (L == R) {
                return L;                       // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        push(ind);                              // una hoja nunca llega aca

        int M = (L + R) / 2;
        int res = corte_izq(l, r, 2 * ind, L, M, acc, f);

        if (res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(l, r, 2 * ind + 1, M + 1, R, acc, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(R + 1, r).
    template <class F>
    int corte_der(int l, int r, int ind, int L, int R, Node& acc, F f) {
        if (R < l || r < L) {
            return l - 1;
        }

        if (l <= L && R <= r) {
            Node t = seg[ind] + acc;            // el nodo a la IZQUIERDA de acc

            if (f(t)) {
                acc = t;
                return l - 1;
            }

            if (L == R) {
                return L;
            }
        }

        push(ind);

        int M = (L + R) / 2;
        int res = corte_der(l, r, 2 * ind + 1, M + 1, R, acc, f);   // el DERECHO primero

        if (res >= l) {
            return res;
        }

        return corte_der(l, r, 2 * ind, L, M, acc, f);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    // OJO: vector<Node>(n) daria n copias de Node() con sz = 0, o sea el rango VACIO, y
    // entonces operator*= no haria nada y todos los add se perderian en silencio.
    // Node(0) es "un elemento que vale cero", que es lo que pide el enunciado.
    LazySegmentTree<Node, LazyUpdate> st(vector<Node>(n, Node(0)));

    while(m--) {
        int tipo;
        cin >> tipo;

        if(tipo == 1) {
            int l, r;
            ll v;
            cin >> l >> r >> v;

            st.apply(l, r - 1, LazyUpdate(v));  // [l, r) del enunciado -> [l, r-1] inclusivo
        } else {
            ll x;
            int l;
            cin >> x >> l;                      // x PRIMERO, l despues

            int p = st.max_right(l, n - 1, [&](const Node& v) { return v.mx < x; });
            cout << (p == n - 1 ? -1 : p + 1) << "\n";
        }
    }

    return 0;
}
