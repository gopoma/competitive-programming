/**
 * Description: 1D point update and range query where \texttt{cmb} is
 * any associative operation. \texttt{all_prod()==prod(0,N-1)}.
 * Time: O(\log N)
 * Source:
 *  - http://codeforces.com/blog/entry/18051
 *  - KACTL
 * Verification: SPOJ Fenwick
 * API: SegmentTree<node> tree(vector<node> v);
 *  - prod(l, r) is zero-indexed and inclusive.
 *  - Internal segment tree nodes are 1-indexed: root is 1, children of x are
 *    2 * x and 2 * x + 1.
 */

tcT> struct SegmentTree { // cmb(ID, b) = b
    // const T ID{};
    // T cmb(T a, T b) const { return a + b; }

    T ID{};

    T cmb(T a, T b) const {
        return a + b;
    }

    int sz = 0;
    int n = 1;
    V<T> seg;

    SegmentTree() {
        init(0);
    }

    explicit SegmentTree(int _n) {
        init(_n);
    }

    explicit SegmentTree(const V<T>& v) {
        build(v);
    }

    void init(int _n) {
        sz = _n;
        n = 1;

        while(n < max(1, _n)) {
            n *= 2;
        }

        seg.assign(2 * n, ID);
    }

    void build(const V<T>& a) {
        init((int)a.size());

        for(int i = 0; i < sz; i++) {
            seg[n + i] = a[i];
        }

        for(int p = n - 1; p > 0; p--) {
            pull(p);
        }
    }

    void pull(int p) {
        seg[p] = cmb(seg[2 * p], seg[2 * p + 1]);
    }

    void set(int p, T val) {
        assert(0 <= p && p < sz);

        p += n;
        seg[p] = val;

        for(p /= 2; p > 0; p /= 2) {
            pull(p);
        }
    }

    T get(int p) const {
        assert(0 <= p && p < sz);
        return seg[p + n];
    }

    T all_prod() const {
        return seg[1];
    }

    T prod(int l, int r) const { // zero-indexed, inclusive
        assert(0 <= l && l <= r && r < sz);

        T ra = ID;
        T rb = ID;

        l += n;
        r += n + 1;

        while(l < r) {
            if(l & 1) {
                ra = cmb(ra, seg[l]);
                l++;
            }

            if(r & 1) {
                r--;
                rb = cmb(seg[r], rb);
            }

            l /= 2;
            r /= 2;
        }

        return cmb(ra, rb);
    }

    /// // Recursive descent example.
    /// // seg[x] stores the aggregate of node x according to cmb.
    /// // This example assumes cmb is max, so seg[x] is the maximum of [lx, rx],
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
    ///     assert(0 <= l && l <= r && r < sz);
    ///     return find(k, l, r, 1, 0, n - 1);
    /// }
    ///
    /// // Suffix version with the signature find(k, l, x, lx, rx):
    /// // int find(int k, int l, int x, int lx, int rx) {
    /// //     return find(k, l, sz - 1, x, lx, rx);
    /// // }
    /// //
    /// // int find(int k, int l) {
    /// //     assert(0 <= l && l < sz);
    /// //     return find(k, l, 1, 0, n - 1);
    /// // }
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
