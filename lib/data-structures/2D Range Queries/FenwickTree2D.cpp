struct FenwickTree2D {
    vector<vector<ll>> bit;
    int n, m;

    void init(int a, int b) {
		n = a;
		m = b;

		bit.resize(n);
		for (int i = 0; i < n; ++i) {
			bit[i].resize(m);
		}
	 }

    ll sum(int x, int y) {
		if (x < 0 || y < 0) return 0;
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

	ll query(int xl, int xr, int yl, int yr) {
		ll response = sum(xr,yr)-sum(xl-1,yr)
			-sum(xr,yl-1)+sum(xl-1,yl-1);
		dbg(xl, xr, yl, yr, response);
		return response;
	}

    void add(int x, int y, ll delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};
