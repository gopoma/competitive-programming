/**
 * Description: Segment tree with point assignment and range query. T() is the neutral
 *   value and a + b folds two neighbouring intervals, a to the left of b, so + has to be
 *   associative but not commutative.
 * Time: O(n) build, O(log n) set and prod, O(1) get and all_prod
 * Source:
 *  - http://codeforces.com/blog/entry/18051
 *  - KACTL
 * Verification: SPOJ Fenwick
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
    static long long Mod;

    long long val;

    Node() : val(1LL) {
    }

    Node(long long _val) : val(_val) {
    }

    Node operator+(const Node& rhs) const {
        return Node((val * rhs.val) % Mod);
    }
};
