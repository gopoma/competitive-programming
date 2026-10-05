/**
 * Description: Persistent lazy segment tree; reads never write, they carry the pending update
 *   in a local. Pool: max_nodes(n, q) = 2n + 4 * (ceil(log2 n) + 1) * q + 1.
 * Time: O(n) build, O(log n) set, apply, get and prod, O(1) all_prod and copy
 * Source: own, algorithm after AtCoder Library. Manual: PersistentLazySegmentTree.md
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
struct LazyUpdate { // lazy update
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

struct Node { // data you need to store for each interval
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

    // sz es lo que permite que el update escale a todo el intervalo de una sola vez.
    Node& operator*=(const LazyUpdate& f) {
        if(sz == 0) {                           // la identidad se queda identidad
            return *this;
        }

        if(f.has) {
            sum = (f.v + f.a) * sz;
            mx = mn = f.v + f.a;
        } else {
            sum += f.a * sz;
            mx += f.a;
            mn += f.a;
        }

        return *this;
    }
};
