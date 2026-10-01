// A. Assignment and Maximal Segment
// Asigna v a a[l..r-1] y, tras cada asignacion, reporta la maxima subsuma del arreglo.
// Se permite el segmento vacio, asi que la respuesta nunca es negativa.

#include <bits/stdc++.h>
using namespace std;

/**
 * Description: Segment tree with lazy propagation.
 * Time: O(n) build, O(log n) per operation, O(1) all_prod
 * Source: algorithm from https://atcoder.github.io/ac-library (lazy_segtree)
 * Verification: TODO
 * API: ranges are inclusive and zero indexed, so prod(0, n - 1) is the whole array,
 *   l == r + 1 is the empty range, and r == n is a mistake that trips an assert.
 *     LazySegmentTree<Node, LazyUpdate> t(v)   built from a vector<Node>
 *     LazySegmentTree<Node, LazyUpdate> t(n)   n copies of Node(), the NEUTRAL value, so
 *                                              for n zeroes write t(vector<Node>(n, Node(0)))
 *     t.set(p, x)        a[p] = x
 *     t.get(p)           the Node sitting at p
 *     t.apply(p, f)      applies f to a[p]
 *     t.apply(l, r, f)   applies f to every element of a[l..r]
 *     t.prod(l, r)       folds a[l..r] into one Node
 *     t.all_prod()       folds the whole array, in O(1)
 *     t.query(l, r)      same answer as prod but written recursively
 */

template <class Node, class LazyUpdate>
struct LazySegmentTree {
  public:
    LazySegmentTree() : LazySegmentTree(0) {}

    explicit LazySegmentTree(int _n) : LazySegmentTree(vector<Node>(_n, Node())) {}

    explicit LazySegmentTree(const vector<Node>& v) : n(int(v.size())) {
        SZ = 1, LOG = 0;

        while (SZ < n) {
            SZ *= 2;
            ++LOG;
        }

        seg.assign(2 * SZ, Node());
        lazy.assign(SZ, LazyUpdate());

        for (int i = 0; i < n; i++) {
            seg[SZ + i] = v[i];
        }

        for (int i = SZ - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void set(int p, Node x) {
        assert(0 <= p && p < n);

        p += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(p >> i);
        }

        seg[p] = x;

        for (int i = 1; i <= LOG; i++) {
            pull(p >> i);
        }
    }

    Node get(int p) {
        assert(0 <= p && p < n);

        p += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(p >> i);
        }

        return seg[p];
    }

    Node prod(int l, int r) {
        assert(0 <= l && l <= r + 1 && r < n);

        if (l > r) {
            return Node();
        }

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

    void apply(int p, LazyUpdate f) {
        assert(0 <= p && p < n);

        p += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(p >> i);
        }

        seg[p] *= f;

        for (int i = 1; i <= LOG; i++) {
            pull(p >> i);
        }
    }

    void apply(int l, int r, LazyUpdate f) {
        assert(0 <= l && l <= r + 1 && r < n);

        if (l > r) {
            return;
        }

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
                all_apply(l++, f);
            }

            if (!(r & 1)) {
                all_apply(r--, f);
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


    Node query(int l, int r, int ind, int L, int R) {
        if (r < L || R < l) {
            return Node();                      // disjunto del rango pedido
        }

        if (l <= L && R <= r) {
            return seg[ind];                    // cubierto: seg[ind] ya es el agregado
        }

        push(ind);                              // recien ahora los hijos son legibles

        int M = (L + R) / 2;
        return query(l, r, 2 * ind, L, M) + query(l, r, 2 * ind + 1, M + 1, R);
    }

    Node query(int l, int r) {
        assert(0 <= l && l <= r + 1 && r < n);

        if (l > r) {
            return Node();
        }

        return query(l, r, 1, 0, SZ - 1);
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
};


// --------------------------------------------------------------------------------------
// Node y LazyUpdate para este problema.
//
// Node lleva lo que hace falta para la maxima subsuma: la longitud del intervalo, su suma,
// el mejor prefijo, el mejor sufijo y la mejor subsuma interior. Se permite el segmento
// vacio, asi que pref, suf y best nunca bajan de 0.
//
// len == 0 marca la identidad, y ademas es lo que permite que una asignacion recalcule el
// nodo entero de una vez: sum = v * len. Esa es la condicion de distributividad, asignar v
// a dos mitades y combinar da lo mismo que combinar y asignar v al todo.
struct LazyUpdate {
    bool has = false;                        // identidad: no hay asignacion pendiente
    long long v = 0;

    LazyUpdate() {}
    LazyUpdate(long long x) : has(true), v(x) {}

    LazyUpdate& operator*=(const LazyUpdate& f) {
        if (f.has) {                         // f actua despues, su asignacion tapa la anterior
            has = true;
            v = f.v;
        }

        return *this;
    }
};

struct Node {
    long long len = 0, sum = 0, pref = 0, suf = 0, best = 0;

    Node() {}
    Node(long long x) : len(1), sum(x), pref(max(0LL, x)), suf(max(0LL, x)), best(max(0LL, x)) {}

    friend Node operator+(const Node& a, const Node& b) {
        if (a.len == 0) {
            return b;
        }

        if (b.len == 0) {
            return a;
        }

        Node r;
        r.len = a.len + b.len;
        r.sum = a.sum + b.sum;
        r.pref = max(a.pref, a.sum + b.pref);
        r.suf = max(b.suf, b.sum + a.suf);
        r.best = max(max(a.best, b.best), a.suf + b.pref);
        return r;
    }

    Node& operator*=(const LazyUpdate& f) {
        if (len == 0 || !f.has) {
            return *this;
        }

        sum = f.v * len;
        pref = suf = best = max(0LL, sum);
        return *this;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    LazySegmentTree<Node, LazyUpdate> t(vector<Node>(n, Node(0)));

    while (m--) {
        int l, r;
        long long v;
        cin >> l >> r >> v;
        t.apply(l, r - 1, LazyUpdate(v));
        cout << t.all_prod().best << "\n";
    }

    return 0;
}
