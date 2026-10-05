/**
 * Description: Lazy segment tree over a universe up to 1e18. The Node needs apply(f, len):
 *   the tree supplies the length. Pool: max_nodes(n, q) = 4 * (ceil(log2 n) + 1) * q + 1.
 * Time: O(log n) set, apply, get and prod, O(1) all_prod. No build: it starts empty.
 * Source: own, after usaco.guide/plat/sparse-segtree. Manual: SparseLazySegmentTree.md
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
