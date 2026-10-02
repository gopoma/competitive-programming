/**
 * Description: Persistent segment tree with lazy propagation. Every set and every apply
 *   returns the root of a NEW version and leaves the old one alone, so the roots are yours
 *   to keep and you can read or branch from any of them at any time. A root is just an int.
 *   Node() is the neutral value and a + b folds two neighbouring intervals, a to the left
 *   of b, so + has to be associative but not commutative. node *= f applies the update f to
 *   a whole interval at once and must leave the neutral value alone, Node() *= f stays
 *   Node(). LazyUpdate() changes nothing and f *= g stacks g onto f, so g acts after f.
 * Time: O(n) build, O(log n) set, apply, get and prod, O(1) all_prod and copy
 * Memory: the pool is reserved once and never grows, so n and the number of queries are
 *   both required. The budget is pessimistic, it assumes every query is a range apply,
 *   which is the costliest operation, and it covers ONE build. With C = ceil(log2 n) the
 *   exact worst case is 2n - 1 nodes for build, 2C + 1 for set and point apply, 4C - 1 for
 *   range apply, and 0 for every query:
 *     max_nodes(n, q) = 2n + 4 * (ceil(log2 n) + 1) * q + 1
 * Source: own, algorithm after https://atcoder.github.io/ac-library (lazy_segtree)
 * Verification: TODO
 * API: ranges are inclusive and zero indexed, and must be valid, 0 <= l <= r < n.
 *   Reads never write, which is what persistence needs: get and prod carry the pending
 *   updates down in a local variable instead of pushing them into the tree.
 *   Node 0 is the null node, a subtree entirely Node() with nothing pending, which is why
 *   build() is free. Since an update has to leave Node() alone, applying to that version
 *   does nothing; for real values start from build(vector<Node>(n, Node(0))) instead.
 *     PersistentLazySegmentTree<Node, LazyUpdate> st(n, q)   reserves the pool
 *     st.build(a)                root of the initial version, 2n - 1 nodes
 *     st.build()                 root of the all-Node() version, 0 nodes
 *     st.set(root, p, x)         new root, a[p] = x
 *     st.apply(root, p, f)       new root, f applied to a[p]
 *     st.apply(root, l, r, f)    new root, f applied to a[l..r]
 *     st.copy(root)              duplicate a version, 1 node
 *     st.get(root, p)            the Node at p
 *     st.prod(root, l, r)        folds a[l..r]
 *     st.all_prod(root)          folds the whole array, in O(1)
 * Example, CSES Range Queries and Copies: a list of arrays, point set, range sum, clone.
 *   The point set goes through apply with an assign update, which is what exercises the
 *   lazy path; sz is what lets an assign recompute the sum, and sz == 0 marks the neutral.
 *   struct Assign { bool has = false; ll v = 0; Assign() {} Assign(ll x) : has(true), v(x) {}
 *       Assign& operator*=(const Assign& f) {
 *           if (f.has) { has = true; v = f.v; }
 *           return *this; } };
 *   struct Sum { ll sz = 0, sum = 0; Sum() {} Sum(ll x) : sz(1), sum(x) {}
 *       friend Sum operator+(const Sum& a, const Sum& b) {
 *           if (a.sz == 0) return b;
 *           if (b.sz == 0) return a;
 *           Sum r; r.sz = a.sz + b.sz; r.sum = a.sum + b.sum; return r; }
 *       Sum& operator*=(const Assign& f) {
 *           if (sz == 0 || !f.has) return *this;
 *           sum = f.v * sz; return *this; } };
 *
 *   int n, q; cin >> n >> q;
 *   vector<Sum> a(n);
 *   for (Sum& x : a) { ll t; cin >> t; x = Sum(t); }
 *   PersistentLazySegmentTree<Sum, Assign> st(n, q);
 *   vector<int> roots = {st.build(a)};
 *   while (q--) {
 *       int type, k; cin >> type >> k; k--;
 *       if (type == 1) { int p; ll x; cin >> p >> x; p--;
 *                        roots[k] = st.apply(roots[k], p, Assign(x)); }
 *       else if (type == 2) { int l, r; cin >> l >> r; l--, r--;
 *                             cout << st.prod(roots[k], l, r).sum << "\n"; }
 *       else roots.push_back(st.copy(roots[k]));
 *   }
 */

template <class Node, class LazyUpdate>
struct PersistentLazySegmentTree {
  public:
    PersistentLazySegmentTree(int _n, long long q) : n(_n) {
        assert(n >= 1 && q >= 0);

        st.reserve(size_t(max_nodes(n, q)));
        st.push_back(InternalNode());           // el nodo nulo: subarbol entero en Node()
    }

    static long long max_nodes(int _n, long long q) {
        assert(_n >= 1 && q >= 0);
        return 2LL * _n + 4LL * (ceil_log2(_n) + 1) * q + 1;
    }

    int build() {
        return 0;
    }

    int build(const vector<Node>& a) {
        assert(int(a.size()) == n);
        return build(0, n - 1, a);
    }

    int set(int rt, int p, Node x) {
        assert(valid(rt));
        assert(0 <= p && p < n);

        return set(rt, 0, n - 1, p, x, LazyUpdate());
    }

    int apply(int rt, int p, LazyUpdate f) {
        assert(0 <= p && p < n);
        return apply(rt, p, p, f);
    }

    int apply(int rt, int l, int r, LazyUpdate f) {
        assert(valid(rt));
        assert(0 <= l && l <= r && r < n);

        return apply(rt, 0, n - 1, l, r, f, LazyUpdate());
    }

    int copy(int rt) {
        assert(valid(rt));
        return new_node(st[rt].lc, st[rt].rc, st[rt].val, st[rt].lz);
    }

    Node get(int rt, int p) const {
        assert(valid(rt));
        assert(0 <= p && p < n);

        return get(rt, 0, n - 1, p);
    }

    Node prod(int rt, int l, int r) const {
        assert(valid(rt));
        assert(0 <= l && l <= r && r < n);

        return prod(rt, 0, n - 1, l, r, LazyUpdate());
    }

    Node all_prod(int rt) const {
        assert(valid(rt));
        return st[rt].val;
    }

    int size() const {
        return n;
    }

    long long nodes_used() const {
        return (long long)st.size() - 1;
    }

  private:
    struct InternalNode {
        int lc = 0;
        int rc = 0;
        Node val{};
        LazyUpdate lz{};
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
    int new_node(int lc, int rc, const Node& val, const LazyUpdate& lz) {
        InternalNode nd;
        nd.lc = lc;
        nd.rc = rc;
        nd.val = val;
        nd.lz = lz;
        st.push_back(nd);
        return int(st.size()) - 1;
    }

    // Un nodo nuevo igual al subarbol cur pero con f aplicado a todo el.
    int clone_with(int cur, const LazyUpdate& f) {
        Node v = st[cur].val;
        v *= f;

        LazyUpdate g = st[cur].lz;
        g *= f;                                 // f actua despues de lo que ya habia

        return new_node(st[cur].lc, st[cur].rc, v, g);
    }

    int build(int lx, int rx, const vector<Node>& a) {
        if(lx == rx) {
            return new_node(0, 0, a[lx], LazyUpdate());
        }

        int mx = (lx + rx) / 2;
        int lc = build(lx, mx, a);
        int rc = build(mx + 1, rx, a);
        return new_node(lc, rc, st[lc].val + st[rc].val, LazyUpdate());
    }

    // Raiz de un subarbol nuevo igual a cur con f aplicado a todo, y despues la posicion p
    // puesta en x. El f pendiente baja dentro del clon del hijo que queda fuera del camino,
    // asi un nivel cuesta dos nodos en vez de tres.
    int set(int cur, int lx, int rx, int p, const Node& x, const LazyUpdate& f) {
        if(lx == rx) {
            return new_node(0, 0, x, LazyUpdate());
        }

        int mx = (lx + rx) / 2;
        LazyUpdate down = st[cur].lz;
        down *= f;

        int lc;
        int rc;

        if(p <= mx) {
            lc = set(st[cur].lc, lx, mx, p, x, down);
            rc = clone_with(st[cur].rc, down);
        } else {
            lc = clone_with(st[cur].lc, down);
            rc = set(st[cur].rc, mx + 1, rx, p, x, down);
        }

        return new_node(lc, rc, st[lc].val + st[rc].val, LazyUpdate());
    }

    // Raiz de un subarbol nuevo igual a cur con f aplicado a todo, y despues g aplicado a
    // [ql, qr] intersectado con [lx, rx].
    int apply(int cur, int lx, int rx, int ql, int qr, const LazyUpdate& g, const LazyUpdate& f) {
        if(qr < lx || rx < ql) {
            return clone_with(cur, f);
        }

        if(ql <= lx && rx <= qr) {
            LazyUpdate h = f;
            h *= g;                             // primero f, despues g
            return clone_with(cur, h);
        }

        int mx = (lx + rx) / 2;
        LazyUpdate down = st[cur].lz;
        down *= f;

        int lc = apply(st[cur].lc, lx, mx, ql, qr, g, down);
        int rc = apply(st[cur].rc, mx + 1, rx, ql, qr, g, down);
        return new_node(lc, rc, st[lc].val + st[rc].val, LazyUpdate());
    }

    // Las dos lecturas bajan llevando lo pendiente en f y no escriben nada: en un arbol
    // persistente un push destruiria las versiones anteriores.
    Node get(int cur, int lx, int rx, int p) const {
        LazyUpdate f;

        while(lx != rx && cur != 0) {
            LazyUpdate down = st[cur].lz;
            down *= f;

            int mx = (lx + rx) / 2;

            if(p <= mx) {
                cur = st[cur].lc;
                rx = mx;
            } else {
                cur = st[cur].rc;
                lx = mx + 1;
            }

            f = down;
        }

        Node res = st[cur].val;                 // si cur es 0, st[0].val ya es Node()
        res *= f;
        return res;
    }

    Node prod(int cur, int lx, int rx, int ql, int qr, LazyUpdate f) const {
        if(cur == 0 || qr < lx || rx < ql) {
            return Node();
        }

        if(ql <= lx && rx <= qr) {
            Node res = st[cur].val;
            res *= f;
            return res;
        }

        LazyUpdate down = st[cur].lz;
        down *= f;

        int mx = (lx + rx) / 2;
        return prod(st[cur].lc, lx, mx, ql, qr, down) + prod(st[cur].rc, mx + 1, rx, ql, qr, down);
    }
};

struct LazyUpdate {
    long long add = 0;

    LazyUpdate() {}
    LazyUpdate(long long x) : add(x) {}

    LazyUpdate& operator*=(const LazyUpdate& f) {
        add += f.add;
        return *this;
    }
};

struct Node {
    long long sz = 0, mn = 0, sum = 0;

    Node() {}
    Node(long long x) : sz(1), mn(x), sum(x) {}

    friend Node operator+(const Node& a, const Node& b) {
        if(a.sz == 0) {
            return b;
        }

        if(b.sz == 0) {
            return a;
        }

        Node res;
        res.sz = a.sz + b.sz;
        res.mn = min(a.mn, b.mn);
        res.sum = a.sum + b.sum;
        return res;
    }

    Node& operator*=(const LazyUpdate& f) {
        if(sz == 0) {
            return *this;
        }

        mn += f.add;
        sum += sz * f.add;
        return *this;
    }
};
