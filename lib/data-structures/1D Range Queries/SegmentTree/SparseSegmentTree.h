/**
 * Description: Segment tree over a universe up to 1e18; nodes are created only when a set
 *   touches them. Pool: max_nodes(n, q) = (ceil(log2 n) + 1) * q + 1.
 * Time: O(log n) set, get and prod, O(1) all_prod. No build: it starts empty.
 * Source: own, after usaco.guide/plat/sparse-segtree. Manual: SparseSegmentTree.md
 */

template <class T>
struct SparseSegmentTree {
  public:
    SparseSegmentTree(long long _n, long long q) : n(_n) {
        assert(n >= 1 && q >= 0);

        st.reserve(size_t(max_nodes(n, q)));
        st.push_back(InternalNode());           // el nodo nulo: todo el subarbol en T()
    }

    static long long max_nodes(long long _n, long long q) {
        assert(_n >= 1 && q >= 0);
        return (long long)(ceil_log2(_n) + 1) * q + 1;
    }

    void set(long long p, T x) {
        assert(0 <= p && p < n);
        root = set(root, 0, n - 1, p, x);
    }

    T get(long long p) const {
        assert(0 <= p && p < n);
        return get(root, 0, n - 1, p);
    }

    T prod(long long l, long long r) const {
        assert(0 <= l && l <= r && r < n);
        return prod(root, 0, n - 1, l, r);
    }

    T all_prod() const {
        return st[root].val;
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

        long long mx = lx + (rx - lx) / 2;       // asi no desborda con n cerca de 2^63

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
    // sz == 0 es el rango vacio, la identidad de +. pref, suf y best son sumas de
    // subarreglos, y el vacio cuenta, asi que ninguna de las tres baja de cero.
    long long sz = 0, sum = 0, pref = 0, suf = 0, best = 0;

    Node() {}
    Node(long long x)
        : sz(1), sum(x), pref(max(0LL, x)), suf(max(0LL, x)), best(max(0LL, x)) {}

    friend Node operator+(const Node& a, const Node& b) {
        if(a.sz == 0) {
            return b;
        }

        if(b.sz == 0) {
            return a;
        }

        Node res;
        res.sz = a.sz + b.sz;
        res.sum = a.sum + b.sum;
        res.pref = max(a.pref, a.sum + b.pref);
        res.suf = max(b.suf, b.sum + a.suf);
        res.best = max(max(a.best, b.best), a.suf + b.pref);  // el que cruza la union
        return res;
    }
};
