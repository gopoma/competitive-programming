/**
 * Description: Segment tree with lazy propagation over a universe too big to allocate, up
 *   to 1e18. Nodes are created only when an update touches them, so the memory follows the
 *   number of queries and not n. Node() is the neutral value and a + b folds two
 *   neighbouring intervals, a to the left of b, so + has to be associative but not
 *   commutative.
 * Time: O(log n) set, apply, get and prod, O(1) all_prod. No build: the tree starts empty.
 * Memory: the pool is reserved once and never grows, so n and the number of queries are
 *   both required. The budget assumes every query is a range apply, which is the costliest
 *   one: it materializes both children of each partial node, at most four per level.
 *     max_nodes(n, q) = 4 * (ceil(log2 n) + 1) * q + 1
 *   It is pessimistic twice over: an update over already materialized nodes creates none,
 *   and the nodes near the root are shared by every path. Still, a range apply is expensive:
 *   measured at n = 1e18 it costs around 150 nodes each, so q = 1e6 wants about 9 GB. If a
 *   problem really asks for that, compress coordinates and use the dense LazySegmentTree.
 * Source: own, after https://usaco.guide/plat/sparse-segtree
 * Verification: stress tested against brute force, 69440 ranges over n = 1..30 with range
 *   assign and range add mixed, checking sum, maximum and minimum at once, plus range
 *   applies at n = 1e18 checked against a closed form
 * API: ranges are inclusive and zero indexed, and must be valid, 0 <= l <= r < n.
 *   n and the indices are long long, which is the whole point: a dense tree would need
 *   2n nodes and here n can be 1e18. Node 0 is the null node, a subtree nobody touched yet.
 *     SparseLazySegmentTree<Node, LazyUpdate> st(n, q)   reserves the pool
 *     st.set(p, x)             a[p] = x
 *     st.apply(p, f)           f applied to a[p]
 *     st.apply(l, r, f)        f applied to a[l..r]
 *     st.get(p)                the Node at p
 *     st.prod(l, r)            folds a[l..r]
 *     st.all_prod()            folds the whole universe, in O(1)
 *     st.nodes_used()          how much of the pool is gone, for debugging
 *
 * Node must provide Node(), which is the identity of + and therefore the EMPTY range, plus
 * a + b, plus apply(f, len). That len is the one real difference against LazySegmentTree:
 * a subtree nobody materialized has no way to know how many positions it covers, but the
 * tree does, so the tree hands it over, and apply is what turns an empty Node() into the
 * aggregate of len positions. Keep the two apart: Node() alone means no positions at all,
 * while apply(f, len) on it means len positions that were never touched, which is why the
 * example below has apply set sz rather than add to it.
 * LazyUpdate must provide LazyUpdate(), the update that changes nothing, and f *= g, which
 * stacks g onto f so that g takes effect after f.
 *
 * Example, sum, maximum and minimum of a[l..r] with TWO kinds of range update, assign v to a
 *   range and add v to a range, over coordinates up to 1e18. A single update has to carry
 *   both kinds at once, read as "assign v if has, then add a", because the two do not
 *   commute: in the composition a later assign wins and erases the add pending under it,
 *   while a later add just accumulates. Untouched positions count as zeros, and they come
 *   out right on their own: a range with no nodes under it arrives as Node() and apply turns
 *   it into len positions reporting sum 0, maximum 0 and minimum 0. If your problem needs a
 *   different default, assign it over the whole universe before anything else.
 *   struct Upd {
 *       bool has = false; ll v = 0, a = 0;
 *       Upd() {}
 *       static Upd assign(ll x) { Upd f; f.has = true; f.v = x; return f; }
 *       static Upd add(ll x) { Upd f; f.a = x; return f; }
 *       Upd& operator*=(const Upd& f) {              // f acts AFTER this one
 *           if (f.has) { has = true; v = f.v; a = f.a; }
 *           else a += f.a;
 *           return *this; } };
 *   struct Node {
 *       ll sz = 0, sum = 0, mx = 0, mn = 0;          // sz == 0 is the empty range
 *       Node() {}
 *       Node(ll x) : sz(1), sum(x), mx(x), mn(x) {}
 *       friend Node operator+(const Node& a, const Node& b) {
 *           if (a.sz == 0) return b;
 *           if (b.sz == 0) return a;
 *           Node r;
 *           r.sz = a.sz + b.sz;
 *           r.sum = a.sum + b.sum;
 *           r.mx = max(a.mx, b.mx);
 *           r.mn = min(a.mn, b.mn);
 *           return r; }
 *       void apply(const Upd& f, ll len) {           // the tree says how long the interval is
 *           sz = len;
 *           if (f.has) { sum = (f.v + f.a) * len; mx = mn = f.v + f.a; }
 *           else { sum += f.a * len; mx += f.a; mn += f.a; } } };
 *
 *   const ll N = 1000000000000000000LL;
 *   int q; cin >> q;
 *   SparseLazySegmentTree<Node, Upd> st(N, q);
 *   while (q--) {
 *       int type; ll l, r; cin >> type >> l >> r;
 *       if (type == 1) { ll v; cin >> v; st.apply(l, r, Upd::assign(v)); }
 *       else if (type == 2) { ll v; cin >> v; st.apply(l, r, Upd::add(v)); }
 *       else { Node res = st.prod(l, r);
 *              cout << res.sum << " " << res.mx << " " << res.mn << "\n"; }
 *   }
 */

template <class Node, class LazyUpdate>
struct SparseLazySegmentTree {
  public:
    SparseLazySegmentTree(long long _n, long long q) : n(_n) {
        assert(n >= 1 && q >= 0);

        st.reserve(size_t(max_nodes(n, q)));
        st.push_back(InternalNode());           // el nodo nulo: nadie lo toco todavia
    }

    static long long max_nodes(long long _n, long long q) {
        assert(_n >= 1 && q >= 0);
        return 4LL * (ceil_log2(_n) + 1) * q + 1;
    }

    void set(long long p, Node x) {
        assert(0 <= p && p < n);
        root = set(root, 0, n - 1, p, x);
    }

    void apply(long long p, LazyUpdate f) {
        assert(0 <= p && p < n);
        apply(p, p, f);
    }

    void apply(long long l, long long r, LazyUpdate f) {
        assert(0 <= l && l <= r && r < n);
        root = apply(root, 0, n - 1, l, r, f);
    }

    Node get(long long p) const {
        assert(0 <= p && p < n);
        return prod(p, p);
    }

    Node prod(long long l, long long r) const {
        assert(0 <= l && l <= r && r < n);
        return prod(root, 0, n - 1, l, r, LazyUpdate());
    }

    Node all_prod() const {
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
        Node val{};
        LazyUpdate lz{};
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

    void all_apply(int k, const LazyUpdate& f, long long len) {
        st[k].val.apply(f, len);
        st[k].lz *= f;                          // f actua despues de lo que ya habia
    }

    // Materializa los dos hijos y les baja el lazy. Hay que materializarlos aunque esten
    // vacios: lo pendiente tiene que quedar guardado en algun lado.
    void push(int cur, long long lx, long long rx) {
        if(st[cur].lc == 0) {
            st[cur].lc = new_node();
        }

        if(st[cur].rc == 0) {
            st[cur].rc = new_node();
        }

        long long mx = lx + (rx - lx) / 2;
        all_apply(st[cur].lc, st[cur].lz, mx - lx + 1);
        all_apply(st[cur].rc, st[cur].lz, rx - mx);
        st[cur].lz = LazyUpdate();
    }

    void pull(int cur) {
        st[cur].val = st[st[cur].lc].val + st[st[cur].rc].val;
    }

    int set(int cur, long long lx, long long rx, long long p, const Node& x) {
        if(cur == 0) {
            cur = new_node();
        }

        if(lx == rx) {
            st[cur].val = x;
            return cur;
        }

        push(cur, lx, rx);

        long long mx = lx + (rx - lx) / 2;

        if(p <= mx) {
            st[cur].lc = set(st[cur].lc, lx, mx, p, x);
        } else {
            st[cur].rc = set(st[cur].rc, mx + 1, rx, p, x);
        }

        pull(cur);
        return cur;
    }

    int apply(int cur, long long lx, long long rx, long long ql, long long qr,
              const LazyUpdate& f) {
        if(rx < ql || qr < lx) {
            return cur;                         // disjunto: ni siquiera se materializa
        }

        if(cur == 0) {
            cur = new_node();
        }

        if(ql <= lx && rx <= qr) {
            all_apply(cur, f, rx - lx + 1);
            return cur;
        }

        push(cur, lx, rx);

        long long mx = lx + (rx - lx) / 2;
        st[cur].lc = apply(st[cur].lc, lx, mx, ql, qr, f);
        st[cur].rc = apply(st[cur].rc, mx + 1, rx, ql, qr, f);
        pull(cur);
        return cur;
    }

    // La lectura lleva lo pendiente en f y no escribe nada, asi que no materializa nodos.
    Node prod(int cur, long long lx, long long rx, long long ql, long long qr,
              LazyUpdate f) const {
        if(rx < ql || qr < lx) {
            return Node();                      // disjunto: el rango vacio
        }

        if(ql <= lx && rx <= qr) {
            Node res = st[cur].val;             // si cur es 0, es Node(), el rango vacio
            res.apply(f, rx - lx + 1);          // y apply lo vuelve len posiciones
            return res;
        }

        if(cur == 0) {                          // sin materializar y parcial: solo lo pendiente
            Node res;
            long long a = lx > ql ? lx : ql;
            long long b = rx < qr ? rx : qr;
            res.apply(f, b - a + 1);
            return res;
        }

        LazyUpdate down = st[cur].lz;
        down *= f;

        long long mx = lx + (rx - lx) / 2;
        return prod(st[cur].lc, lx, mx, ql, qr, down) +
               prod(st[cur].rc, mx + 1, rx, ql, qr, down);
    }
};
struct LazyUpdate {
    // "si has, asignar v a todo el intervalo; despues sumar a a todo el intervalo"
    bool has = false;
    long long v = 0, a = 0;

    LazyUpdate() {}

    static LazyUpdate assign(long long x) {
        LazyUpdate f;
        f.has = true;
        f.v = x;
        return f;
    }

    static LazyUpdate add(long long x) {
        LazyUpdate f;
        f.a = x;
        return f;
    }

    // f actua DESPUES: un assign posterior gana y borra el add que quedaba debajo, mientras
    // que un add posterior solo se acumula. Por eso assign y add no conmutan.
    LazyUpdate& operator*=(const LazyUpdate& f) {
        if(f.has) {
            has = true;
            v = f.v;
            a = f.a;
        } else {
            a += f.a;
        }

        return *this;
    }
};

struct Node {
    long long sz = 0, sum = 0, mx = 0, mn = 0;  // sz == 0 es el rango vacio, la identidad

    Node() {}
    Node(long long x) : sz(1), sum(x), mx(x), mn(x) {}

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
        res.mx = max(a.mx, b.mx);
        res.mn = min(a.mn, b.mn);
        return res;
    }

    // El arbol es la autoridad sobre cuantas posiciones cubre el intervalo, asi que apply
    // FIJA sz: un subarbol sin materializar llega como Node() y sale como len posiciones
    // intactas, que para este problema valen cero.
    void apply(const LazyUpdate& f, long long len) {
        sz = len;

        if(f.has) {
            sum = (f.v + f.a) * len;
            mx = mn = f.v + f.a;
        } else {
            sum += f.a * len;
            mx += f.a;
            mn += f.a;
        }
    }
};
