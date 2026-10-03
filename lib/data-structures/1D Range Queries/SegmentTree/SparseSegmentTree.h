/**
 * Description: Segment tree over a universe too big to allocate, up to 1e18. Nodes are
 *   created only when a set touches them, so the memory follows the number of queries and
 *   not n. T() is the neutral value, every position starts there, and a + b folds two
 *   neighbouring intervals, a to the left of b, so + has to be associative but not
 *   commutative.
 * Time: O(log n) set, get and prod, O(1) all_prod. No build: the tree starts empty.
 * Memory: the pool is reserved once and never grows, so n and the number of queries are
 *   both required. The budget assumes every query is a set, which materializes one node
 *   per level:
 *     max_nodes(n, q) = (ceil(log2 n) + 1) * q + 1
 *   It is pessimistic twice over: a set that walks an existing path costs nothing, and the
 *   nodes near the root are shared by every path.
 * Source: own, after https://usaco.guide/plat/sparse-segtree
 * Verification: stress tested against brute force Kadane, 107100 ranges over n = 1..34,
 *   plus 20000 sets and 400 range queries at n = 1e18 checked against a map
 * API: ranges are inclusive and zero indexed, and must be valid, 0 <= l <= r < n.
 *   n and the indices are long long, which is the whole point: a dense tree would need
 *   2n nodes and here n can be 1e18. Node 0 is the null node, a subtree where every
 *   position is still T().
 *     SparseSegmentTree<T> st(n, q)   reserves the pool, both arguments required
 *     st.set(p, x)                    a[p] = x
 *     st.get(p)                       the T at p
 *     st.prod(l, r)                   folds a[l..r]
 *     st.all_prod()                   folds the whole universe, in O(1)
 *     st.nodes_used()                 how much of the pool is gone, for debugging
 * Example, maximum sum of a subarray of a[l..r] with the empty subarray allowed, so the
 *   answer is never negative, over coordinates up to 1e18. One number per node is not
 *   enough: gluing two halves needs the best subarray that crosses the seam, so each node
 *   also carries the total sum, the best prefix and the best suffix. sz == 0 marks the
 *   neutral value, the empty range, and the two early returns in + are what make T() behave
 *   as an identity. Untouched positions count as zeros, which this monoid handles for free:
 *   a zero changes neither a sum nor a best subarray, so leaving them out of the tree gives
 *   the same answer as storing them.
 *   struct Node {
 *       ll sz = 0, sum = 0, pref = 0, suf = 0, best = 0;    // sz == 0 is the empty range
 *       Node() {}
 *       Node(ll x) : sz(1), sum(x), pref(max(0LL, x)), suf(max(0LL, x)), best(max(0LL, x)) {}
 *       friend Node operator+(const Node& a, const Node& b) {
 *           if (a.sz == 0) return b;
 *           if (b.sz == 0) return a;
 *           Node r;
 *           r.sz = a.sz + b.sz;
 *           r.sum = a.sum + b.sum;
 *           r.pref = max(a.pref, a.sum + b.pref);
 *           r.suf = max(b.suf, b.sum + a.suf);
 *           r.best = max(max(a.best, b.best), a.suf + b.pref);
 *           return r; } };
 *
 *   const ll N = 1000000000000000000LL;
 *   int q; cin >> q;
 *   SparseSegmentTree<Node> st(N, q);
 *   while (q--) {
 *       int type; cin >> type;
 *       if (type == 1) { ll p, x; cin >> p >> x; st.set(p, Node(x)); }
 *       else { ll l, r; cin >> l >> r; cout << st.prod(l, r).best << "\n"; }
 *   }
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
