/**
 * Description: Persistent segment tree. Every set returns the root of a NEW version and a
 *   root is just an int. Pool: max_nodes(n, q) = 2n + (ceil(log2 n) + 1) * q + 1.
 * Time: O(n) build, O(log n) set, get and prod, O(1) all_prod and copy
 * Source: own, after usaco.guide/adv/persistent. Manual: PersistentSegmentTree.md
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


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(rt, l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template<class F>
    int max_right(int rt, int l, int r, F f) const {
        assert(valid(rt));
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_izq(rt, 0, n - 1, l, r, acc, f) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(rt, p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template<class F>
    int min_left(int rt, int l, int r, F f) const {
        assert(valid(rt));
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_der(rt, 0, n - 1, l, r, acc, f) + 1;
    }

    // Vuelca el arreglo logico de UNA version: dump(rt)[i] es lo que da get(rt, i).
    // Sirve para mirar cualquier version, incluso vieja, y no consume nodos del pool.
    // Baja por DOS versiones a la vez hasta una hoja, y devuelve su posicion.
    // Es lo que hace falta para el k-esimo menor de un rango: ninguna version sola alcanza,
    // porque el conteo del rango sale de RESTAR dos prefijos. izq(a, b) recibe los agregados
    // del hijo IZQUIERDO de las dos versiones y dice si hay que bajar por ahi; puede llevar
    // estado, por ejemplo descontar k. La resta corre por cuenta de izq, asi que el monoide
    // no necesita inverso: el contrato de + se queda como esta.
    template<class F>
    int descend2(int rtA, int rtB, F izq) const {
        assert(valid(rtA) && valid(rtB));

        int a = rtA, b = rtB;
        int lx = 0, rx = n - 1;

        while(lx < rx) {
            int mx = (lx + rx) / 2;

            if(izq(st[st[a].l].val, st[st[b].l].val)) {
                a = st[a].l;                    // st[0] es el nodo nulo: sus hijos son 0 y
                b = st[b].l;                    // su val ya es T(), asi que no hay caso aparte
                rx = mx;
            } else {
                a = st[a].r;
                b = st[b].r;
                lx = mx + 1;
            }
        }

        return lx;
    }

    vector<T> dump(int rt) const {
        assert(valid(rt));

        vector<T> out;
        out.reserve(size_t(n));
        dump(rt, 0, n - 1, out);
        return out;
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

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, lx - 1).
    // st[0] es el nodo nulo y su val ya es T(), asi que un subarbol sin materializar no
    // necesita caso aparte: aporta la identidad y no mueve acc.
    template<class F>
    int corte_izq(int cur, int lx, int rx, int l, int r, T& acc, F f) const {
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

        int mx = (lx + rx) / 2;
        int res = corte_izq(st[cur].l, lx, mx, l, r, acc, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur].r, mx + 1, rx, l, r, acc, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(rx + 1, r).
    template<class F>
    int corte_der(int cur, int lx, int rx, int l, int r, T& acc, F f) const {
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

        int mx = (lx + rx) / 2;
        int res = corte_der(st[cur].r, mx + 1, rx, l, r, acc, f);   // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur].l, lx, mx, l, r, acc, f);
    }

    // st[0] es el nodo nulo: sus hijos son 0 y su val ya es T(), asi que un subarbol sin
    // materializar no necesita caso aparte.
    void dump(int cur, int lx, int rx, vector<T>& out) const {
        if(lx == rx) {
            out.push_back(st[cur].val);
            return;
        }

        int mx = (lx + rx) / 2;
        dump(st[cur].l, lx, mx, out);
        dump(st[cur].r, mx + 1, rx, out);
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
