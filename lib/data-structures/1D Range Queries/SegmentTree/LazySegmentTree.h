/**
 * Author: gopoma
 * Date: 2026-10-01
 * Source: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/SegmentTree/LazySegmentTree.h
 *   algorithm after atcoder.github.io/ac-library
 * Description: Segment tree with lazy propagation. Node() neutral, a + b associative,
 *   node *= f applies an update to a whole interval, f *= g stacks g after f.
 *   max_right / min_left descend the tree. Manual: LazySegmentTree.md
 * Time: O(n) build, O(log n) per operation, O(1) all_prod
 * Status: Codeforces EDU submission 394467936, AC 125 ms (uses max_right).
 *   Stress-tested, plus 811620 checks on operator[].
 */

template <class Node, class LazyUpdate>
struct LazySegmentTree {
  public:
    LazySegmentTree() : LazySegmentTree(0) {}

    explicit LazySegmentTree(int len) {
        SZ = 1, LOG = 0;

        while (SZ < max(1, len)) {
            SZ *= 2;
            ++LOG;
        }

        n = SZ;                                 // sin vector, n es el tamano con padding
        seg.assign(2 * SZ, Node());             // todo identidad, no hace falta pull:
        lazy.assign(SZ, LazyUpdate());          // Node() + Node() == Node()
    }

    explicit LazySegmentTree(const vector<Node>& init) : n(int(init.size())) {
        SZ = 1, LOG = 0;

        while (SZ < max(1, n)) {
            SZ *= 2;
            ++LOG;
        }

        seg.assign(2 * SZ, Node());
        lazy.assign(SZ, LazyUpdate());

        for (int i = 0; i < n; i++) {
            seg[SZ + i] = init[i];
        }

        for (int i = SZ - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void set(int pos, Node val) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        seg[pos] = val;

        for (int i = 1; i <= LOG; i++) {
            pull(pos >> i);
        }
    }

    Node get(int pos) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        return seg[pos];
    }

    // Azucar de lectura, para que se lea como un vector: seg[i] es exactamente get(i).
    // Devuelve por VALOR, pero NO es const, y es el unico de la familia asi: leer obliga a
    // bajar el lazy del camino con push. O sea que no se puede leer de un const&.
    Node operator[](int pos) {
        return get(pos);
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

    void apply(int pos, LazyUpdate upd) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        seg[pos] *= upd;

        for (int i = 1; i <= LOG; i++) {
            pull(pos >> i);
        }
    }

    void apply(int l, int r, LazyUpdate upd) {
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
                all_apply(l++, upd);
            }

            if (!(r & 1)) {
                all_apply(r--, upd);
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
    int max_right(int l, int r, F pred) {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_izq(l, r, 1, 0, SZ - 1, acc, pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template <class F>
    int min_left(int l, int r, F pred) {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_der(l, r, 1, 0, SZ - 1, acc, pred) + 1;
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

struct NodeSumMnMx { // data you need to store for each interval
    long long size = 0, sum = 0, mx = 0, mn = 0;  // size == 0 es el rango vacio

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
