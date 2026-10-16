/**
 * Description: Persistent lazy segment tree; reads never write, they carry the pending update
 *   in a local. Pool: max_nodes(n, q) = 2n + 4 * (ceil(log2 n) + 1) * q + 1.
 * Time: O(n) build, O(log n) set, apply, get and prod, O(1) all_prod and copy
 * Source: own, algorithm after AtCoder Library. Manual: PersistentLazySegmentTree.md
 */

template <class Node, class LazyUpdate>
struct PersistentLazySegmentTree {
  public:
    PersistentLazySegmentTree(int len, long long max_ops) : n(len) {
        assert(n >= 1 && max_ops >= 0);

        st.reserve(size_t(max_nodes(n, max_ops)));
        st.push_back(InternalNode());           // el nodo nulo: subarbol entero en Node()
    }

    static long long max_nodes(int len, long long max_ops) {
        assert(len >= 1 && max_ops >= 0);
        return 2LL * len + 4LL * (ceil_log2(len) + 1) * max_ops + 1;
    }

    int build() {
        return 0;
    }

    int build(const vector<Node>& init) {
        assert(int(init.size()) == n);
        return build(0, n - 1, init);
    }

    int set(int root, int pos, Node val) {
        assert(valid(root));
        assert(0 <= pos && pos < n);

        return set(root, 0, n - 1, pos, val, LazyUpdate());
    }

    int apply(int root, int pos, LazyUpdate upd) {
        assert(0 <= pos && pos < n);
        return apply(root, pos, pos, upd);
    }

    int apply(int root, int l, int r, LazyUpdate upd) {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        return apply(root, 0, n - 1, l, r, upd, LazyUpdate());
    }

    // Vuelca el arreglo logico de UNA version: dump(rt)[i] es lo que da get(rt, i).
    // Sirve para mirar cualquier version, incluso vieja, y no consume nodos del pool.
    vector<Node> dump(int root) const {
        assert(valid(root));

        vector<Node> out;
        out.reserve(size_t(n));
        dump(root, 0, n - 1, LazyUpdate(), out);
        return out;
    }

    int copy(int root) {
        assert(valid(root));
        return new_node(st[root].lc, st[root].rc, st[root].val, st[root].lz);
    }

    Node get(int root, int pos) const {
        assert(valid(root));
        assert(0 <= pos && pos < n);

        return get(root, 0, n - 1, pos);
    }

    Node prod(int root, int l, int r) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        return prod(root, 0, n - 1, l, r, LazyUpdate());
    }

    Node all_prod(int root) const {
        assert(valid(root));
        return st[root].val;
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(rt, l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template<class F>
    int max_right(int root, int l, int r, F pred) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_izq(root, 0, n - 1, l, r, acc, LazyUpdate(), pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(rt, p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template<class F>
    int min_left(int root, int l, int r, F pred) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_der(root, 0, n - 1, l, r, acc, LazyUpdate(), pred) + 1;
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
    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, lx - 1).
    // st[0] es el nodo nulo y su val ya es Node(), asi que un subarbol sin materializar no
    // necesita caso aparte: aporta la identidad y no mueve acc.
    // g es el lazy pendiente que baja desde arriba, igual que en prod.
    template<class F>
    int corte_izq(int cur, int lx, int rx, int l, int r, Node& acc, LazyUpdate g, F f) const {
        if(rx < l || r < lx) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if(l <= lx && rx <= r) {                // el nodo entra completo en [l, r]
            Node pieza = st[cur].val;
            pieza *= g;                         // el pendiente que viene de arriba
            Node t = acc + pieza;
            if(f(t)) {
                acc = t;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if(lx == rx) {
                return lx;                      // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        LazyUpdate down = st[cur].lz;           // no se puede hacer push: la version es de solo
        down *= g;                              // lectura. Lo pendiente viaja como parametro.

        int mx = (lx + rx) / 2;
        int res = corte_izq(st[cur].lc, lx, mx, l, r, acc, down, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur].rc, mx + 1, rx, l, r, acc, down, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(rx + 1, r).
    template<class F>
    int corte_der(int cur, int lx, int rx, int l, int r, Node& acc, LazyUpdate g, F f) const {
        if(rx < l || r < lx) {
            return l - 1;
        }

        if(l <= lx && rx <= r) {
            Node pieza = st[cur].val;
            pieza *= g;
            Node t = pieza + acc;               // el nodo a la IZQUIERDA de acc
            if(f(t)) {
                acc = t;
                return l - 1;
            }

            if(lx == rx) {
                return lx;
            }
        }

        LazyUpdate down = st[cur].lz;           // no se puede hacer push: la version es de solo
        down *= g;                              // lectura. Lo pendiente viaja como parametro.

        int mx = (lx + rx) / 2;
        int res = corte_der(st[cur].rc, mx + 1, rx, l, r, acc, down, f);   // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur].lc, lx, mx, l, r, acc, down, f);
    }

    // No se puede hacer push: la version es de solo lectura. Lo pendiente viaja en f,
    // igual que en prod y en los dos descensos.
    void dump(int cur, int lx, int rx, LazyUpdate f, vector<Node>& out) const {
        if(lx == rx) {
            Node res = st[cur].val;             // si cur es 0, st[0].val ya es Node()
            res *= f;
            out.push_back(res);
            return;
        }

        LazyUpdate down = st[cur].lz;
        down *= f;

        int mx = (lx + rx) / 2;
        dump(st[cur].lc, lx, mx, down, out);
        dump(st[cur].rc, mx + 1, rx, down, out);
    }

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

struct NodeSumMnMx { // data you need to store for each interval
    long long size = 0, sum = 0, mx = 0, mn = 0;  // size == 0 es el rango vacio, la identidad

    NodeSumMnMx() {}
    NodeSumMnMx(long long x) : size(1), sum(x), mx(x), mn(x) {}

    friend NodeSumMnMx operator+(const NodeSumMnMx& a, const NodeSumMnMx& b) {
        if(a.size == 0) {
            return b;
        }

        if(b.size == 0) {
            return a;
        }

        NodeSumMnMx res;
        res.size = a.size + b.size;
        res.sum = a.sum + b.sum;
        res.mx = max(a.mx, b.mx);
        res.mn = min(a.mn, b.mn);
        return res;
    }

    // size es lo que permite que el update escale a todo el intervalo de una sola vez.
    NodeSumMnMx& operator*=(const LazyUpdate& f) {
        if(size == 0) {                         // la identidad se queda identidad
            return *this;
        }

        if(f.has) {
            sum = (f.v + f.a) * size;
            mx = mn = f.v + f.a;
        } else {
            sum += f.a * size;
            mx += f.a;
            mn += f.a;
        }

        return *this;
    }
};
