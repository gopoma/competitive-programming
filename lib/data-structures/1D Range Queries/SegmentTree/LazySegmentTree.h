/**
 * Description: Segment tree with lazy propagation. Node() neutral, a + b associative,
 *   node *= f applies an update to a whole interval, f *= g stacks g after f.
 *   max_right / min_left descend the tree to find a boundary, like the AtCoder Library.
 * Time: O(n) build, O(log n) per operation, O(1) all_prod
 * Source: atcoder.github.io/ac-library. Manual and stress tests: LazySegmentTree.md
 * Verification: codeforces.com/edu submission 394467936, 125 ms (uses max_right)
 */

template <class Node, class LazyUpdate>
struct LazySegmentTree {
  public:
    LazySegmentTree() : LazySegmentTree(0) {}

    explicit LazySegmentTree(int _n) {
        SZ = 1, LOG = 0;

        while (SZ < max(1, _n)) {
            SZ *= 2;
            ++LOG;
        }

        n = SZ;                                 // sin vector, n es el tamano con padding
        seg.assign(2 * SZ, Node());             // todo identidad, no hace falta pull:
        lazy.assign(SZ, LazyUpdate());          // Node() + Node() == Node()
    }

    explicit LazySegmentTree(const vector<Node>& v) : n(int(v.size())) {
        SZ = 1, LOG = 0;

        while (SZ < max(1, n)) {
            SZ *= 2;
            ++LOG;
        }

        seg.assign(2 * SZ, Node());
        lazy.assign(SZ, LazyUpdate());

        for (int i = 0; i < n; i++) {
            seg[SZ + i] = v[i];
        }

        for (int i = SZ - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void set(int p, Node x) {
        assert(0 <= p && p < n);

        p += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(p >> i);
        }

        seg[p] = x;

        for (int i = 1; i <= LOG; i++) {
            pull(p >> i);
        }
    }

    Node get(int p) {
        assert(0 <= p && p < n);

        p += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(p >> i);
        }

        return seg[p];
    }

    Node prod(int l, int r) {
        assert(0 <= l && l <= r && r < n);

        l += SZ, r += SZ;                       // hojas inclusivas: seg[l] .. seg[r]

        for (int i = LOG; i >= 1; i--) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {                 // l no arranca su bloque de 2^i
                push(l >> i);
            }

            if ((r & m) != m) {                 // r no termina su bloque de 2^i
                push(r >> i);
            }
        }

        Node sml, smr;

        while (l <= r) {
            if (l & 1) {                        // l es hijo derecho: su padre se sale
                sml = sml + seg[l++];
            }

            if (!(r & 1)) {                     // r es hijo izquierdo: su padre se sale
                smr = seg[r--] + smr;
            }

            l >>= 1, r >>= 1;
        }

        return sml + smr;
    }

    Node all_prod() const {
        return seg[1];
    }

    // Vuelca el arreglo logico para depurar: dump()[i] es exactamente lo que da get(i).
    // NO es const: baja todos los lazy pendientes, igual que get hace sobre un solo camino.
    // El orden k = 1 .. SZ-1 es correcto por construccion, porque el padre de k es k / 2 < k.
    vector<Node> dump() {
        for (int k = 1; k < SZ; k++) {
            push(k);
        }

        return vector<Node>(seg.begin() + SZ, seg.begin() + SZ + n);
    }

    void apply(int p, LazyUpdate f) {
        assert(0 <= p && p < n);

        p += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(p >> i);
        }

        seg[p] *= f;

        for (int i = 1; i <= LOG; i++) {
            pull(p >> i);
        }
    }

    void apply(int l, int r, LazyUpdate f) {
        assert(0 <= l && l <= r && r < n);

        l += SZ, r += SZ;                       // hojas inclusivas: seg[l] .. seg[r]

        for (int i = LOG; i >= 1; i--) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {
                push(l >> i);
            }

            if ((r & m) != m) {
                push(r >> i);
            }
        }

        int l2 = l, r2 = r;

        while (l <= r) {
            if (l & 1) {
                all_apply(l++, f);
            }

            if (!(r & 1)) {
                all_apply(r--, f);
            }

            l >>= 1, r >>= 1;
        }

        l = l2, r = r2;

        for (int i = 1; i <= LOG; i++) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {
                pull(l >> i);
            }

            if ((r & m) != m) {
                pull(r >> i);
            }
        }
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template <class F>
    int max_right(int l, int r, F f) {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_izq(l, r, 1, 0, SZ - 1, acc, f) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template <class F>
    int min_left(int l, int r, F f) {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_der(l, r, 1, 0, SZ - 1, acc, f) + 1;
    }


  private:
    int n, SZ, LOG;
    vector<Node> seg;
    vector<LazyUpdate> lazy;

    void pull(int k) {
        seg[k] = seg[2 * k] + seg[2 * k + 1];
    }

    // Keeps seg[k] equal to the true aggregate of the subtree at k: f lands on the value
    // right away, and only an internal node has to remember it for its children.
    void all_apply(int k, const LazyUpdate& f) {
        seg[k] *= f;

        if (k < SZ) {
            lazy[k] *= f;
        }
    }

    void push(int k) {
        all_apply(2 * k, lazy[k]);
        all_apply(2 * k + 1, lazy[k]);
        lazy[k] = LazyUpdate();
    }

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, L - 1).
    // El agregado se lee sin push: all_apply mantiene seg[ind] siempre al dia.
    template <class F>
    int corte_izq(int l, int r, int ind, int L, int R, Node& acc, F f) {
        if (R < l || r < L) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if (l <= L && R <= r) {                 // el nodo entra completo en [l, r]
            Node t = acc + seg[ind];            // acc a la izquierda, el nodo a la derecha

            if (f(t)) {
                acc = t;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if (L == R) {
                return L;                       // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        push(ind);                              // una hoja nunca llega aca

        int M = (L + R) / 2;
        int res = corte_izq(l, r, 2 * ind, L, M, acc, f);

        if (res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(l, r, 2 * ind + 1, M + 1, R, acc, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(R + 1, r).
    template <class F>
    int corte_der(int l, int r, int ind, int L, int R, Node& acc, F f) {
        if (R < l || r < L) {
            return l - 1;
        }

        if (l <= L && R <= r) {
            Node t = seg[ind] + acc;            // el nodo a la IZQUIERDA de acc

            if (f(t)) {
                acc = t;
                return l - 1;
            }

            if (L == R) {
                return L;
            }
        }

        push(ind);

        int M = (L + R) / 2;
        int res = corte_der(l, r, 2 * ind + 1, M + 1, R, acc, f);   // el DERECHO primero

        if (res >= l) {
            return res;
        }

        return corte_der(l, r, 2 * ind, L, M, acc, f);
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
