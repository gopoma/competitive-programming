#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef bitset<1225> B;
typedef vector<int> vi;

struct DSU {  // for Kruskal's
	vi e;
	void init(int n) { e = vi(n, -1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return 0;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y];
		e[y] = x;
		return 1;
	}
};

int N, M, K;
vector<array<int, 3>> ed;

struct Partition {
	B ban;
	vi span;
	int wei = 0,
	    fix = 0;  // "fix" smallest edges must be contained in spanning tree
	Partition(B _ban, int _fix) : ban(_ban), fix(_fix) {
		DSU D;
		D.init(N);  // now find MST within subspace
		for (int i = 0; i < M; ++i)
			if (!ban[i] && D.unite(ed[i][1], ed[i][2]))
				span.push_back(i),
				    wei += ed[i][0];  // run Kruskal's ignoring banned edges
	}
};
bool operator<(const Partition &l, const Partition &r) {
	return l.wei > r.wei;
}  // for pq

// https://usaco.guide/adv/fracturing-search?lang=cpp#k-th-smallest-spanning-tree-usaco-camp-2018
// $K$-th Smallest Spanning Tree (USACO Camp 2018)
// https://atcoder.jp/contests/abc328/tasks/abc328_e
// E - Modulo MST
signed main() {
	cin >> N >> M >> K;
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		ed.push_back({c, a - 1, b - 1});
	}
	sort(begin(ed), end(ed));
	priority_queue<Partition> pq;
	pq.push({B(), 0});  // start with MST

    long long ans = (long long)(1e16);
	for (int i = 1; ; ++i) {
		if (!pq.size()) {
			// cout << "-1\n";
			// exit(0);
            break;
		}
		auto a = pq.top();
		pq.pop();
		assert(a.span.size() == N - 1);
		// if (i == K) {
		// 	cout << a.wei << "\n";
		// 	exit(0);
		// }
        // cout << a.wei << "\n";
        ans = min(ans, a.wei % K);
                                       // print K-th smallest
		while (a.fix < a.span.size()) {  // insert O(N) children
			B t = a.ban;
			t[a.span[a.fix]] = 1;
			auto A = Partition(t, a.fix);
			if (A.span.size() == N - 1) pq.push(A);
			a.fix++;
		}
	}
    cout << ans << "\n";
}
