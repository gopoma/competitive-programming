/**
 * Description: Lazy segment tree over a universe up to 1e18. The Node needs apply(f, len):
 *   the tree supplies the length. Pool: max_nodes(n, q) = 4 * (ceil(log2 n) + 1) * q + 1.
 * Time: O(log n) set, apply, get and prod, O(1) all_prod. No build: it starts empty.
 * Source: own, after usaco.guide/plat/sparse-segtree. Manual: SparseLazySegmentTree.md
 * Public: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/SegmentTree/SparseLazySegmentTree.h
 */

template <class Node, class LazyUpdate>
struct SparseLazySegmentTree {
  public:
    SparseLazySegmentTree(long long len, long long max_ops) : n(len) {
        assert(n >= 1 && max_ops >= 0);

        st.reserve(size_t(max_nodes(n, max_ops)));
        st.push_back(InternalNode());           // el nodo nulo: nadie lo toco todavia
    }

    static long long max_nodes(long long len, long long max_ops) {
        assert(len >= 1 && max_ops >= 0);
        return 4LL * (ceil_log2(len) + 1) * max_ops + 1;
    }

    void set(long long pos, Node val) {
        assert(0 <= pos && pos < n);
        root = set(root, 0, n - 1, pos, val);
    }

    void apply(long long pos, LazyUpdate upd) {
        assert(0 <= pos && pos < n);
        apply(pos, pos, upd);
    }

    void apply(long long l, long long r, LazyUpdate upd) {
        assert(0 <= l && l <= r && r < n);
        root = apply(root, 0, n - 1, l, r, upd);
    }

    Node get(long long pos) const {
        assert(0 <= pos && pos < n);
        return prod(pos, pos);
    }

    Node prod(long long l, long long r) const {
        assert(0 <= l && l <= r && r < n);
        return prod(root, 0, n - 1, l, r, LazyUpdate());
    }

    Node all_prod() const {
        return st[root].val;
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template<class F>
    long long max_right(long long l, long long r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_izq(root, 0, n - 1, l, r, acc, LazyUpdate(), pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template<class F>
    long long min_left(long long l, long long r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_der(root, 0, n - 1, l, r, acc, LazyUpdate(), pred) + 1;
    }

    // Tope de dump(): n puede valer 1e18 y volcarlo entero no entra en memoria.
    static const long long DUMP_MAX = 10000000;

    // Vuelca el universo entero para depurar: dump()[i] es lo que da get(i). Las posiciones
    // sin materializar vuelven como Node() con apply(f, 1) encima.
    // No consume nodos del pool.
    vector<Node> dump() const {
        assert(n <= DUMP_MAX);

        vector<Node> out;
        out.reserve(size_t(n));
        dump(root, 0, n - 1, LazyUpdate(), out);
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

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, lx - 1).
    // st[0] es el nodo nulo y su val ya es Node(), asi que un subarbol sin materializar no
    // necesita caso aparte: aporta la identidad y no mueve acc.
    // g es el lazy pendiente que baja desde arriba, igual que en prod.
    template<class F>
    long long corte_izq(int cur, long long lx, long long rx, long long l, long long r, Node& acc, LazyUpdate g, F f) const {
        if(rx < l || r < lx) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if(l <= lx && rx <= r) {                // el nodo entra completo en [l, r]
            Node pieza = st[cur].val;
            pieza.apply(g, rx - lx + 1);        // el arbol es el que sabe el largo
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

        long long mx = lx + (rx - lx) / 2;
        long long res = corte_izq(st[cur].lc, lx, mx, l, r, acc, down, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur].rc, mx + 1, rx, l, r, acc, down, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(rx + 1, r).
    template<class F>
    long long corte_der(int cur, long long lx, long long rx, long long l, long long r, Node& acc, LazyUpdate g, F f) const {
        if(rx < l || r < lx) {
            return l - 1;
        }

        if(l <= lx && rx <= r) {
            Node pieza = st[cur].val;
            pieza.apply(g, rx - lx + 1);
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

        long long mx = lx + (rx - lx) / 2;
        long long res = corte_der(st[cur].rc, mx + 1, rx, l, r, acc, down, f);   // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur].lc, lx, mx, l, r, acc, down, f);
    }

    // Aca el carry NO es opcional: push materializa los dos hijos, asi que un dump que
    // empujara crearia nodos y podria reventar el pool.
    void dump(int cur, long long lx, long long rx, LazyUpdate f, vector<Node>& out) const {
        if(lx == rx) {
            Node res = st[cur].val;             // si cur es 0, es Node(), el rango vacio
            res.apply(f, 1);                    // una sola posicion
            out.push_back(res);
            return;
        }

        LazyUpdate down = st[cur].lz;
        down *= f;

        long long mx = lx + (rx - lx) / 2;
        dump(st[cur].lc, lx, mx, down, out);
        dump(st[cur].rc, mx + 1, rx, down, out);
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

struct NodeSumMnMx {
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

    // El arbol es la autoridad sobre cuantas posiciones cubre el intervalo, asi que apply
    // FIJA size: un subarbol sin materializar llega como NodeSumMnMx() y sale como len posiciones
    // intactas, que para este problema valen cero.
    void apply(const LazyUpdate& f, long long len) {
        size = len;

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
