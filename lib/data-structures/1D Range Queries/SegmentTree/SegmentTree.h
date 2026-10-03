/**
 * Description: Segment tree with point assignment and range query. T() is the neutral
 *   value and a + b folds two neighbouring intervals, a to the left of b, so + has to be
 *   associative but not commutative.
 * Time: O(n) build, O(log n) set and prod, O(1) get and all_prod
 * Source:
 *  - http://codeforces.com/blog/entry/18051
 *  - KACTL
 * Verification: stress tested against brute force Kadane, 107100 ranges over n = 1..34
 *   with point sets mixed in
 * API: ranges are inclusive and zero indexed. A range must be valid, 0 <= l <= r < n,
 *   so prod(0, n - 1) is the whole array and there is no empty range.
 *   Internal nodes are 1-indexed: the root is 1 and the children of x are 2x and 2x + 1.
 *     SegmentTree<T> t(v)   n is v.size(), SZ is n rounded up to a power of two
 *     SegmentTree<T> t(k)   no vector, so n becomes SZ: k rounded up to a power of two,
 *                           every slot holding T(), the neutral value
 *     t.set(p, x)    a[p] = x
 *     t.get(p)       the T sitting at p
 *     t.prod(l, r)   folds a[l..r] into one T
 *     t.all_prod()   folds the whole array, in O(1)
 * Example, maximum sum of a subarray of a[l..r], where the empty subarray is allowed so the
 *   answer is never negative. One number per node is not enough: gluing two halves needs the
 *   best subarray that crosses the seam, so each node also carries the total sum, the best
 *   prefix and the best suffix. sz == 0 marks the neutral value, the empty range, and the two
 *   early returns in + are what make T() behave as an identity.
 *   struct Node {
 *       ll sz = 0, sum = 0, pref = 0, suf = 0, best = 0;    // sz == 0 is the empty range
 *       Node() {}
 *       Node(ll x) : sz(1), sum(x), pref(max(0LL, x)), suf(max(0LL, x)), best(max(0LL, x)) {}
 *       friend Node operator+(const Node& a, const Node& b) {
 *           if (a.sz == 0) return b;
 *           if (b.sz == 0) return a;
 *           Node r;
 *           r.sz = a.sz + b.sz;
 *           r.sum = a.sum + b.sum;
 *           r.pref = max(a.pref, a.sum + b.pref);
 *           r.suf = max(b.suf, b.sum + a.suf);
 *           r.best = max(max(a.best, b.best), a.suf + b.pref);
 *           return r; } };
 *
 *   int n, q; cin >> n >> q;
 *   vector<Node> a(n);
 *   for (Node& x : a) { ll t; cin >> t; x = Node(t); }
 *   SegmentTree<Node> st(a);
 *   while (q--) {
 *       int type; cin >> type;
 *       if (type == 1) { int p; ll x; cin >> p >> x; st.set(p, Node(x)); }
 *       else { int l, r; cin >> l >> r; cout << st.prod(l, r).best << "\n"; }
 *   }
 */

template <class T>
struct SegmentTree {
  public:
    SegmentTree() : SegmentTree(0) {}

    explicit SegmentTree(int _n) {
        SZ = 1;

        while(SZ < max(1, _n)) {
            SZ *= 2;
        }

        n = SZ;                                 // sin vector, n es el tamano con padding
        seg.assign(2 * SZ, T());                // todo identidad, no hace falta pull:
    }                                           // T() + T() == T()

    explicit SegmentTree(const vector<T>& v) : n(int(v.size())) {
        SZ = 1;

        while(SZ < max(1, n)) {
            SZ *= 2;
        }

        seg.assign(2 * SZ, T());

        for(int i = 0; i < n; i++) {
            seg[SZ + i] = v[i];
        }

        for(int p = SZ - 1; p > 0; p--) {
            pull(p);
        }
    }

    void set(int p, T val) {
        assert(0 <= p && p < n);

        p += SZ;
        seg[p] = val;

        for(p /= 2; p > 0; p /= 2) {
            pull(p);
        }
    }

    T get(int p) const {
        assert(0 <= p && p < n);
        return seg[p + SZ];
    }

    T all_prod() const {
        return seg[1];
    }

    T prod(int l, int r) const { // zero-indexed, inclusive
        assert(0 <= l && l <= r && r < n);

        T ra = T();
        T rb = T();

        l += SZ;
        r += SZ + 1;

        while(l < r) {
            if(l & 1) {
                ra = ra + seg[l];
                l++;
            }

            if(r & 1) {
                r--;
                rb = seg[r] + rb;
            }

            l /= 2;
            r /= 2;
        }

        return ra + rb;
    }

    /// // Recursive descent example.
    /// // seg[x] stores the aggregate of node x under +.
    /// // This example assumes + is max, so seg[x] is the maximum of [lx, rx],
    /// // and finds the first index p in [l, r] such that a[p] >= k.
    /// // For the rightmost valid index, visit the right child first.
    /// int find(int k, int l, int r, int x, int lx, int rx) {
    ///     if(rx < l || r < lx) {
    ///         return -1;
    ///     }
    ///
    ///     if(seg[x] < k) {
    ///         return -1;
    ///     }
    ///
    ///     if(rx - lx + 1 == 1) {
    ///         return lx;
    ///     }
    ///
    ///     int m = (lx + rx) >> 1;
    ///     int re = find(k, l, r, 2 * x, lx, m);
    ///
    ///     if(re == -1) {
    ///         re = find(k, l, r, 2 * x + 1, m + 1, rx);
    ///     }
    ///
    ///     return re;
    /// }
    ///
    /// int find(int k, int l, int r) {
    ///     assert(0 <= l && l <= r && r < n);
    ///     return find(k, l, r, 1, 0, SZ - 1);
    /// }
    ///
    /// // Suffix version with the signature find(k, l, x, lx, rx):
    /// // int find(int k, int l, int x, int lx, int rx) {
    /// //     return find(k, l, n - 1, x, lx, rx);
    /// // }
    /// //
    /// // int find(int k, int l) {
    /// //     assert(0 <= l && l < n);
    /// //     return find(k, l, 1, 0, SZ - 1);
    /// // }

  private:
    int n = 1;
    int SZ = 1;
    vector<T> seg;

    void pull(int p) {
        seg[p] = seg[2 * p] + seg[2 * p + 1];
    }
};

// /here goes the template!
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
