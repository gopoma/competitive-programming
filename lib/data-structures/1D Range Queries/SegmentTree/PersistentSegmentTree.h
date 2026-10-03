/**
 * Description: Persistent segment tree. Every set returns the root of a NEW version and
 *   leaves the old one alone, so the roots are yours to keep and you can read or branch
 *   from any of them at any time. A root is just an int. T() is the neutral value and
 *   a + b folds two neighbouring intervals, a to the left of b, so + has to be associative
 *   but not commutative.
 * Time: O(n) build, O(log n) set, get and prod, O(1) all_prod and copy
 * Memory: the pool is reserved once and never grows, so n and the number of queries are
 *   both required. The budget is pessimistic, it assumes every query is a set, which is
 *   the costliest operation at ceil(log2 n) + 1 nodes, and it covers ONE build:
 *     max_nodes(n, q) = 2n + (ceil(log2 n) + 1) * q + 1
 * Source: own, after https://usaco.guide/adv/persistent
 * Verification: stress tested against brute force Kadane, 107100 ranges over n = 1..34,
 *   plus 212940 ranges read back from EVERY version while branching from arbitrary roots
 * API: ranges are inclusive and zero indexed, and must be valid, 0 <= l <= r < n.
 *   Node 0 is the null node: it stands for a subtree that is entirely T(), which is why
 *   build() costs nothing and why set only materializes the path it touches.
 *     PersistentSegmentTree<T> st(n, q)   reserves the pool, both arguments required
 *     st.build(a)                         root of the initial version, 2n - 1 nodes
 *     st.build()                          root of the all-T() version, 0 nodes
 *     st.set(root, p, x)                  new root; the old one stays valid
 *     st.copy(root)                       duplicate a version, 1 node
 *     st.get(root, p)                     the T at p
 *     st.prod(root, l, r)                 folds a[l..r]
 *     st.all_prod(root)                   folds the whole array, in O(1)
 * Example, a list of arrays with maximum subarray sum per range: point set on array k, ask
 *   the maximum sum of a subarray of a[l..r] of array k with the empty subarray allowed, and
 *   clone array k. One number per node is not enough: gluing two halves needs the best
 *   subarray that crosses the seam, so each node also carries the total sum, the best prefix
 *   and the best suffix. sz == 0 marks the neutral value, the empty range, and the two early
 *   returns in + are what make T() behave as an identity.
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
 *   int n, q; cin >> n >> q;
 *   vector<Node> a(n);
 *   for (Node& x : a) { ll t; cin >> t; x = Node(t); }
 *   PersistentSegmentTree<Node> st(n, q);
 *   vector<int> roots = {st.build(a)};
 *   while (q--) {
 *       int type, k; cin >> type >> k; k--;
 *       if (type == 1) { int p; ll x; cin >> p >> x; p--;
 *                        roots[k] = st.set(roots[k], p, Node(x)); }
 *       else if (type == 2) { int l, r; cin >> l >> r; l--, r--;
 *                             cout << st.prod(roots[k], l, r).best << "\n"; }
 *       else roots.push_back(st.copy(roots[k]));
 *   }
 */

template <class T>
struct PersistentSegmentTree {
  public:
    PersistentSegmentTree(int _n, long long q) : n(_n) {
        assert(n >= 1 && q >= 0);

        st.reserve(size_t(max_nodes(n, q)));
        st.push_back(InternalNode());           // el nodo nulo: subarbol entero en T()
    }

    static long long max_nodes(int _n, long long q) {
        assert(_n >= 1 && q >= 0);
        return 2LL * _n + (long long)(ceil_log2(_n) + 1) * q + 1;
    }

    int build() {
        return 0;
    }

    int build(const vector<T>& a) {
        assert(int(a.size()) == n);
        return build(0, n - 1, a);
    }

    int set(int rt, int p, T x) {
        assert(valid(rt));
        assert(0 <= p && p < n);

        return set(rt, 0, n - 1, p, x);
    }

    T get(int rt, int p) const {
        assert(valid(rt));
        assert(0 <= p && p < n);

        return get(rt, 0, n - 1, p);
    }

    T prod(int rt, int l, int r) const {
        assert(valid(rt));
        assert(0 <= l && l <= r && r < n);

        return prod(rt, 0, n - 1, l, r);
    }

    T all_prod(int rt) const {
        assert(valid(rt));
        return st[rt].val;
    }

    int copy(int rt) {
        assert(valid(rt));
        return clone(rt);
    }

    int size() const {
        return n;
    }

    long long nodes_used() const {
        return (long long)st.size() - 1;
    }

  private:
    struct InternalNode {
        int l = 0;
        int r = 0;
        T val{};
    };

    int n;
    vector<InternalNode> st;

    static int ceil_log2(int x) {
        int c = 0;

        while((1 << c) < x) {
            ++c;
        }

        return c;
    }

    bool valid(int rt) const {
        return 0 <= rt && rt < int(st.size());
    }

    // El nodo se arma entero antes de entrar al pool, asi que nunca se lee st[...] con una
    // referencia viva mientras se inserta.
    int new_node(int l, int r, const T& val) {
        InternalNode nd;
        nd.l = l;
        nd.r = r;
        nd.val = val;
        st.push_back(nd);
        return int(st.size()) - 1;
    }

    int clone(int k) {
        return new_node(st[k].l, st[k].r, st[k].val);
    }

    int build(int lx, int rx, const vector<T>& a) {
        if(lx == rx) {
            return new_node(0, 0, a[lx]);
        }

        int mx = (lx + rx) / 2;
        int lc = build(lx, mx, a);
        int rc = build(mx + 1, rx, a);
        return new_node(lc, rc, st[lc].val + st[rc].val);
    }

    int set(int cur, int lx, int rx, int p, const T& x) {
        if(lx == rx) {
            return new_node(0, 0, x);
        }

        int mx = (lx + rx) / 2;
        int lc = st[cur].l;
        int rc = st[cur].r;

        if(p <= mx) {
            lc = set(lc, lx, mx, p, x);
        } else {
            rc = set(rc, mx + 1, rx, p, x);
        }

        return new_node(lc, rc, st[lc].val + st[rc].val);
    }

    T get(int cur, int lx, int rx, int p) const {
        while(lx != rx) {
            if(cur == 0) {                      // subarbol sin materializar
                return T();
            }

            int mx = (lx + rx) / 2;

            if(p <= mx) {
                cur = st[cur].l;
                rx = mx;
            } else {
                cur = st[cur].r;
                lx = mx + 1;
            }
        }

        return st[cur].val;                     // si cur es 0, st[0].val ya es T()
    }

    T prod(int cur, int lx, int rx, int ql, int qr) const {
        if(cur == 0 || rx < ql || qr < lx) {
            return T();
        }

        if(ql <= lx && rx <= qr) {
            return st[cur].val;
        }

        int mx = (lx + rx) / 2;
        return prod(st[cur].l, lx, mx, ql, qr) + prod(st[cur].r, mx + 1, rx, ql, qr);
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
