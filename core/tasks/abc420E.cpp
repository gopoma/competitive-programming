#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

const int INF = int(1e9) + 5;

/**
 * Description: Disjoint Set Union with path compression
 	* and union by size. Add edges and test connectivity.
 	* Use for Kruskal's or Boruvka's minimum spanning tree.
 * Time: O(\alpha(N))
 * Source: CSAcademy, KACTL
 * Verification: *
 */

struct DSU {
	vector<int> e; void init(int N) { e = vector<int>(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
        //* Small-To-Large Merging
        //* x has bigger set count
		e[x] += e[y]; e[y] = x; return 1;
	}
};

/**tcT> T kruskal(int N, vector<pair<T,pi>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N); // edges that unite are in MST
	each(a,ed) if (D.unite(a.s.f,a.s.s)) ans += a.f;
	return ans;
}*/

// #define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0
#define RAYA   dbg("========================");

void solve() {
    int n, q; cin >> n >> q;

    DSU dsu; dsu.init(n);

    vector<int> dp(n);
    vector<bool> mark(n);
    for(int _ = 0; _ < q; _++) {
        int type; cin >> type;

        if(type == 1) {
            int u, v; cin >> u >> v;
            u--; v--;

            int ru = dsu.get(u);
            int rv = dsu.get(v);
            int vu = dp[ru];
            int vv = dp[rv];

            if(dsu.unite(u, v)) {
                dp[dsu.get(u)] = 0;
                dp[dsu.get(u)] += vu;
                dp[dsu.get(u)] += vv;
            }
        } else if(type == 2) {
            int v; cin >> v;
            v--;

            if(mark[v]) {
                dp[dsu.get(v)]--;
            } else {
                dp[dsu.get(v)]++;
            }
            mark[v] = !mark[v];
        } else {
            assert(type == 3);

            int v; cin >> v;
            v--;

            cout << (dp[dsu.get(v)] > 0 ? "Yes" : "No") << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
