/**
 * Description: Segment tree with lazy propagation.
 * Time: O(n) build, O(log n) per operation, O(1) all_prod
 * Source: algorithm from https://atcoder.github.io/ac-library (lazy_segtree)
 * Verification: TODO
 * API: ranges are inclusive and zero indexed. A range must be valid, 0 <= l <= r < n,
 *   so prod(0, n - 1) is the whole array and there is no empty range; r == n trips the
 *   assert, which is the usual slip coming from half-open code.
 *     LazySegmentTree<Node, LazyUpdate> t(v)   n is v.size(), SZ is n rounded to a power of 2
 *     LazySegmentTree<Node, LazyUpdate> t(k)   no vector, so n becomes SZ: k rounded up to a
 *                                              power of 2, every slot holding Node(), the
 *                                              NEUTRAL value. For k real zeroes instead use
 *                                              t(vector<Node>(k, Node(0)))
 *     t.set(p, x)        a[p] = x
 *     t.get(p)           the Node sitting at p
 *     t.apply(p, f)      applies f to a[p]
 *     t.apply(l, r, f)   applies f to every element of a[l..r]
 *     t.prod(l, r)       folds a[l..r] into one Node
 *     t.all_prod()       folds the whole array, in O(1)
 *     t.query(l, r)      same answer as prod but written recursively
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


    Node query(int l, int r, int ind, int L, int R) {
        if (r < L || R < l) {
            return Node();                      // disjunto del rango pedido
        }

        if (l <= L && R <= r) {
            return seg[ind];                    // cubierto: seg[ind] ya es el agregado
        }

        push(ind);                              // recien ahora los hijos son legibles

        int M = (L + R) / 2;
        return query(l, r, 2 * ind, L, M) + query(l, r, 2 * ind + 1, M + 1, R);
    }

    Node query(int l, int r) {
        assert(0 <= l && l <= r && r < n);

        return query(l, r, 1, 0, SZ - 1);
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
};




struct LazyUpdate { // lazy update
    long long add = 0;

    LazyUpdate() {}
    LazyUpdate(long long x) : add(x) {}

    LazyUpdate& operator*=(const LazyUpdate& f) {
        add += f.add;
        return *this;
    }
};

struct Node { // data you need to store for each interval
    long long sz = 0, mn = 0, sum = 0;

    Node() {}
    Node(long long x) : sz(1), mn(x), sum(x) {}

    friend Node operator+(const Node& a, const Node& b) {
        if (a.sz == 0) {
            return b;
        }

        if (b.sz == 0) {
            return a;
        }

        Node res;
        res.sz = a.sz + b.sz;
        res.mn = min(a.mn, b.mn);
        res.sum = a.sum + b.sum;
        return res;
    }

    Node& operator*=(const LazyUpdate& f) {
        if (sz == 0) {
            return *this;
        }

        mn += f.add;
        sum += sz * f.add;
        return *this;
    }
};
