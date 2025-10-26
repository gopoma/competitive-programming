struct FenwickTree2D {
	int n, m;
	vector<vector<long long>> ft;

	FenwickTree2D(vector<vector<long long>> &a) {
		n = int(a.size());
		m = int(a[0].size());

		ft = vector<vector<long long>>(n + 1, vector<long long>(m + 1, 0LL));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				update(i + 1, j + 1, a[i][j]); // i + 1 -> 1-indexed, j + 1 -> 1-indexed
			}
		}
	}

	void update(int x, int y, long long val) { // 1-indexed, O(logn)
		for(int i = x; i <= n; i += (-i) & i) {
			for(int j = y; j <= m; j += (-j) & j) {
				ft[i][j] += val;
			}
		}
	}

	long long query(int x, int y) { // 1-indexed, O(logn)
		long long res = 0;
		for(int i = x; i > 0; i &= i - 1) {
			for(int j = y; j > 0; j &= j - 1) {
				res += ft[i][j];
			}
		}
		return res;
	}

	long long range_query(int x1, int y1, int x2, int y2) {
		return query(x2, y2) + query(x1 - 1, y1 - 1) - query(x1 - 1, y2) - query(x2, y1 - 1);
	}
};
