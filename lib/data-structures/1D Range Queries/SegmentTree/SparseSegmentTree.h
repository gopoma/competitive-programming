/**
 * Description: Segment tree over a universe up to 1e18; nodes are created only when a set
 *   touches them. Pool: max_nodes(n, q) = (ceil(log2 n) + 1) * q + 1.
 * Time: O(log n) set, get and prod, O(1) all_prod. No build: it starts empty.
 * Source: own, after usaco.guide/plat/sparse-segtree. Manual: SparseSegmentTree.md
 * Public: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/SegmentTree/SparseSegmentTree.h
 */

template <class T>
struct SparseSegmentTree {
  public:
    SparseSegmentTree(long long len, long long max_ops) : n(len) {
        assert(n >= 1 && max_ops >= 0);

        st.reserve(size_t(max_nodes(n, max_ops)));
        st.push_back(InternalNode());           // el nodo nulo: todo el subarbol en T()
    }

    static long long max_nodes(long long len, long long max_ops) {
        assert(len >= 1 && max_ops >= 0);
        return (long long)(ceil_log2(len) + 1) * max_ops + 1;
    }

    void set(long long pos, T val) {
        assert(0 <= pos && pos < n);
        root = set(root, 0, n - 1, pos, val);
    }

    T get(long long pos) const {
        assert(0 <= pos && pos < n);
        return get(root, 0, n - 1, pos);
    }

    T prod(long long l, long long r) const {
        assert(0 <= l && l <= r && r < n);
        return prod(root, 0, n - 1, l, r);
    }

    T all_prod() const {
        return st[root].val;
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template<class F>
    long long max_right(long long l, long long r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_izq(root, 0, n - 1, l, r, acc, pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template<class F>
    long long min_left(long long l, long long r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_der(root, 0, n - 1, l, r, acc, pred) + 1;
    }

    // Tope de dump(): n puede valer 1e18 y volcarlo entero no entra en memoria.
    static const long long DUMP_MAX = 10000000;

    // Vuelca el universo entero para depurar: dump()[i] es lo que da get(i). Las posiciones
    // sin materializar vuelven como T(), que es el RANGO VACIO y no "un cero".
    // No consume nodos del pool.
    vector<T> dump() const {
        assert(n <= DUMP_MAX);

        vector<T> out;
        out.reserve(size_t(n));
        dump(root, 0, n - 1, out);
        return out;
    }

    long long size() const {
        return n;
    }

    long long nodes_used() const {
        return (long long)st.size() - 1;
    }

  private:
    struct InternalNode {
        int lc = 0;
        int rc = 0;
        T val{};
    };

    long long n;
    int root = 0;
    vector<InternalNode> st;

    static int ceil_log2(long long x) {
        int c = 0;

        while((1LL << c) < x) {
            ++c;
        }

        return c;
    }

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, lx - 1).
    // st[0] es el nodo nulo y su val ya es T(), asi que un subarbol sin materializar no
    // necesita caso aparte: aporta la identidad y no mueve acc.
    template<class F>
    long long corte_izq(int cur, long long lx, long long rx, long long l, long long r, T& acc, F f) const {
        if(rx < l || r < lx) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if(l <= lx && rx <= r) {                // el nodo entra completo en [l, r]
            T t = acc + st[cur].val;            // acc a la izquierda, el nodo a la derecha
            if(f(t)) {
                acc = t;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if(lx == rx) {
                return lx;                      // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        long long mx = lx + (rx - lx) / 2;
        long long res = corte_izq(st[cur].lc, lx, mx, l, r, acc, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur].rc, mx + 1, rx, l, r, acc, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(rx + 1, r).
    template<class F>
    long long corte_der(int cur, long long lx, long long rx, long long l, long long r, T& acc, F f) const {
        if(rx < l || r < lx) {
            return l - 1;
        }

        if(l <= lx && rx <= r) {
            T t = st[cur].val + acc;            // el nodo a la IZQUIERDA de acc
            if(f(t)) {
                acc = t;
                return l - 1;
            }

            if(lx == rx) {
                return lx;
            }
        }

        long long mx = lx + (rx - lx) / 2;
        long long res = corte_der(st[cur].rc, mx + 1, rx, l, r, acc, f);   // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur].lc, lx, mx, l, r, acc, f);
    }

    // st[0] es el nodo nulo: sus hijos son 0 y su val ya es T().
    void dump(int cur, long long lx, long long rx, vector<T>& out) const {
        if(lx == rx) {
            out.push_back(st[cur].val);
            return;
        }

        long long mx = lx + (rx - lx) / 2;
        dump(st[cur].lc, lx, mx, out);
        dump(st[cur].rc, mx + 1, rx, out);
    }

    int new_node() {
        st.push_back(InternalNode());
        return int(st.size()) - 1;
    }

    // Devuelve el indice del nodo que cubre [lx, rx]. Si era el nodo nulo lo materializa,
    // y si ya existia lo modifica en el lugar: por eso un camino repetido no cuesta nodos.
    int set(int cur, long long lx, long long rx, long long p, const T& x) {
        if(cur == 0) {
            cur = new_node();
        }

        if(lx == rx) {
            st[cur].val = x;
            return cur;
        }

        long long mx = lx + (rx - lx) / 2;      // asi no desborda con n cerca de 2^63

        if(p <= mx) {
            st[cur].lc = set(st[cur].lc, lx, mx, p, x);
        } else {
            st[cur].rc = set(st[cur].rc, mx + 1, rx, p, x);
        }

        st[cur].val = st[st[cur].lc].val + st[st[cur].rc].val;
        return cur;
    }

    T get(int cur, long long lx, long long rx, long long p) const {
        while(lx != rx) {
            if(cur == 0) {                      // subarbol sin materializar
                return T();
            }

            long long mx = lx + (rx - lx) / 2;

            if(p <= mx) {
                cur = st[cur].lc;
                rx = mx;
            } else {
                cur = st[cur].rc;
                lx = mx + 1;
            }
        }

        return st[cur].val;                     // si cur es 0, st[0].val ya es T()
    }

    T prod(int cur, long long lx, long long rx, long long ql, long long qr) const {
        if(cur == 0 || rx < ql || qr < lx) {
            return T();
        }

        if(ql <= lx && rx <= qr) {
            return st[cur].val;
        }

        long long mx = lx + (rx - lx) / 2;
        return prod(st[cur].lc, lx, mx, ql, qr) + prod(st[cur].rc, mx + 1, rx, ql, qr);
    }
};
struct Node {
    // size == 0 es el rango vacio, la identidad de +. pref, suf y best son sumas de
    // subarreglos, y el vacio cuenta, asi que ninguna de las tres baja de cero.
    long long size = 0, sum = 0, pref = 0, suf = 0, best = 0;

    Node() {}
    Node(long long x)
        : size(1), sum(x), pref(max(0LL, x)), suf(max(0LL, x)), best(max(0LL, x)) {}

    friend Node operator+(const Node& a, const Node& b) {
        if(a.size == 0) {
            return b;
        }

        if(b.size == 0) {
            return a;
        }

        Node res;
        res.size = a.size + b.size;
        res.sum = a.sum + b.sum;
        res.pref = max(a.pref, a.sum + b.pref);
        res.suf = max(b.suf, b.sum + a.suf);
        res.best = max(max(a.best, b.best), a.suf + b.pref);  // el que cruza la union
        return res;
    }
};
