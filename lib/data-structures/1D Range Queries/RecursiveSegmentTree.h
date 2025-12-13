template <class T>
struct SegmentTree {
    T ID{};
    T cmb(T a, T b) { return a + b; }



    vector<T> seg;
    int n = 1;

    void init(int _n) {
        while(n < _n) n *= 2;

        seg.assign(2 * n, ID);
    }

    void build(vector<ll>& a, int x, int lx, int rx) {
        if(rx - lx + 1 == 1) {
            if(lx < sz(a)) {
                seg[x] = T(a[lx]);
            }
            return;
        }

        int m = (lx + rx) / 2;

        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m + 1, rx);

        seg[x] = cmb(seg[2 * x + 1], seg[2 * x + 2]);
    }

    void build(vector<ll>& a) {
        build(a, 0, 0, n - 1);
    }

    void update(int i, T v, int x, int lx, int rx) {
        if(rx - lx + 1 == 1) {
            seg[x] = v;
            return;
        }

        int m = (lx + rx) / 2;

        if(i <= m) {
            assert(lx <= i && i <= m);
            update(i, v, 2 * x + 1, lx, m);
        } else {
            assert(m + 1 <= i && i <= rx);
            update(i, v, 2 * x + 2, m + 1, rx);
        }

        seg[x] = cmb(seg[2 * x + 1], seg[2 * x + 2]);
    }

    void update(int i, T v) {
        update(i, v, 0, 0, n - 1);
    }

    T query(int l, int r, int x, int lx, int rx) {
        if(rx < l || r < lx)   return ID;
        if(l <= lx && rx <= r) return seg[x];

        int m = (lx + rx) / 2;

        T s1 = query(l, r, 2 * x + 1, lx, m);
        T s2 = query(l, r, 2 * x + 2, m + 1, rx);

        return cmb(s1, s2);
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, n - 1);
    }
};

struct node {
    ll mx_sum;
    ll mx_pref;
    ll mx_suff;
    ll sum;

	node() {
        mx_sum = 0;
        mx_pref = 0;
        mx_suff = 0;
        sum = 0;
    }

	node(ll v) {
        mx_sum = max(v, 0LL);
        mx_pref = max(v, 0LL);
        mx_suff = max(v, 0LL);
        sum = v;
    }

    node(ll _mx_sum, ll _mx_pref, ll _mx_suff, ll _sum) {
        mx_sum  = _mx_sum;
        mx_pref = _mx_pref;
        mx_suff = _mx_suff;
        sum = _sum;
    }

	node operator + (const node &rhs) const {
		ll new_mx_sum = max({mx_sum, rhs.mx_sum, mx_suff + rhs.mx_pref, 0LL});
        ll new_mx_pref = max({mx_pref, sum + rhs.mx_pref, 0LL});
        ll new_mx_suff = max({rhs.mx_suff, mx_suff + rhs.sum, 0LL});
        ll new_sum = sum + rhs.sum;

        return node(
            new_mx_sum,
            new_mx_pref,
            new_mx_suff,
            new_sum
        );
	}
};
