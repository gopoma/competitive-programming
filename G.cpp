#ifdef LOCAL
    #ifdef _WIN32
        #define WIN32_LEAN_AND_MEAN
        #define NOMINMAX
        #include <windows.h>
        #include <psapi.h>
    #else
        #include <sys/resource.h>
    #endif
#endif




//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//! #pragma GCC optimize ("trapv")


#include <bits/stdc++.h> //? if you don't want IntelliSense


#undef _GLIBCXX_DEBUG //? for Stress Testing
#pragma GCC target ("avx,avx2")

using namespace std;



//* Debugger
void print_memory_usage() {
#ifdef LOCAL
    #ifdef _WIN32
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            long double block = 1024;
            long double taken = pmc.PeakWorkingSetSize / (block * block);

            std::cerr << "\n";
            std::cerr << "\033[42m++++++++++++++++++++\033[0m\n";
            std::cerr << "\033[42m[Memory] Peak Working Set: "
            << taken << " MB\033[0m\n";
            std::cerr << "\033[42m++++++++++++++++++++\033[0m";
        }
    #else
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        #ifdef __APPLE__
            double peak_mb = usage.ru_maxrss / (1024.0 * 1024.0); // macOS en Bytes
        #else
            double peak_mb = usage.ru_maxrss / 1024.0;            // Linux en KiB
        #endif
        std::cerr << "[Memory] Peak RSS: " << peak_mb << " MB\n";
    #endif
#endif
}




#ifdef LOCAL
    #include "helpers/debug.h"

    const bool isDebugging = true;
#else
    #define dbg(...)     0
    #define chk(...)     0
    #define RAYA         0

    const bool isDebugging = false;
#endif
//* /Debugger



using ll = long long;
using db = long double; // or double if tight TL
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;
#define f  first
#define s  second



#define tcT template<class T
#define tcTU tcT, class U

tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()
#define ts to_string

#define lb lower_bound
#define ub upper_bound
tcT > int lwb(V<T> &a, const T &b) { return int(lb(all(a), b) - bg(a)); }
tcT > int upb(V<T> &a, const T &b) { return int(ub(all(a), b) - bg(a)); }



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}












struct Sqrt {
	int block_size;
	vector<int> nums;
	vector<int> blocks;

    Sqrt() {}
	Sqrt(int sqrtn, vector<int> &arr) : block_size(sqrtn), blocks(sqrtn, 0) {
		nums = arr;
		for (int i = 0; i < nums.size(); i++) { blocks[i / block_size] += nums[i]; }
	}

    void init(int n, int sqrtn) {
        block_size = sqrtn;
        nums = vector<int>(n, 0);
        blocks = vector<int>(block_size, 0);
    }

	/** O(1) update to set nums[x] to v */
	void update(int x, int v) {
		blocks[x / block_size] -= nums[x];
		nums[x] = v;
		blocks[x / block_size] += nums[x];
	}

	/** O(sqrt(n)) query for sum of [0, r) */
	int query(int r) {
		int res = 0;
		for (int i = 0; i < r / block_size; i++) { res += blocks[i]; }
		for (int i = (r / block_size) * block_size; i < r; i++) { res += nums[i]; }
		return res;
	}

	/** O(sqrt(n)) query for sum of [l, r) */
	int query(int l, int r) { return query(r) - query(l); }
};






const int MAXN = 1e6 + 1;
const int MAXQ = 2e5 + 1;
const int MAXLOG = 18;

int n, q, timer, block_size;
int v[MAXN + 5], ans[MAXQ + 5];
int depth[MAXN + 5], node_at[MAXN + 5];
int start[MAXN + 5], en[MAXN + 5];
int up[MAXN + 5][MAXLOG + 5];
bool seen[MAXN];
vector<vector<int>> g(MAXN + 5);
int hist[MAXN];
Sqrt st;


struct Query {
	int l, r, lca, id, a, b;
	bool operator<(const Query &oth) const {
		int b1 = l / block_size, b2 = oth.l / block_size;
		return b1 < b2 || (b1 == b2 && r < oth.r);
	}
};

vector<Query> queries;

void dfs(int node, int parent) {
	start[node] = ++timer;
	node_at[timer] = node;
	depth[node] = depth[parent] + 1;
	up[node][0] = parent;
	for (int i = 1; i < MAXLOG; i++) { up[node][i] = up[up[node][i - 1]][i - 1]; }
	for (int son : g[node]) {
		if (son == parent) { continue; }
		dfs(son, node);
	}
	en[node] = ++timer;
	node_at[timer] = node;
}

int get_lca(int x, int y) {
	if (depth[x] > depth[y]) { swap(x, y); }
	int diff = depth[y] - depth[x];
	for (int i = 0; (1 << i) <= diff; i++) {
		if ((1 << i) & diff) { y = up[y][i]; }
	}
	if (x == y) { return x; }
	for (int i = MAXLOG; i >= 0; i--) {
		if (up[x][i] != up[y][i]) {
			x = up[x][i];
			y = up[y][i];
		}
	}
	return up[x][0];
}

void add_value(int node) { // node in [1, n]
	if (seen[node]) { // TODO: Implement remove action
        chk(hist[v[node]] > 0);
        st.update(hist[v[node]], st.nums[hist[v[node]]] - 1);

        hist[v[node]]--;

        if(hist[v[node]] > 0) {
            st.update(hist[v[node]], st.nums[hist[v[node]]] + 1);
        }
	} else { // TODO: Implement add action
        if(hist[v[node]] > 0) {
            st.update(hist[v[node]], st.nums[hist[v[node]]] - 1);
        }

        hist[v[node]]++;

        st.update(hist[v[node]], st.nums[hist[v[node]]] + 1);
	}
	seen[node] = !seen[node];
}

void solve() {
	cin >> n >> q;

	for (int i = 1; i <= n; i++) { cin >> v[i]; }

	for (int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	dfs(1, 1);

	block_size = (int)sqrt(2 * n);
    st.init(n + 1, block_size);
    dbg(block_size);

	for (int i = 1; i <= q; i++) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		if (start[x] > start[y]) { swap(x, y); }
		int l = get_lca(x, y);
		if (l == x) {
			queries.push_back({start[x], start[y], -1, i, a, b});
		} else {
			queries.push_back({en[x], start[y], l, i, a, b});
		}
	}

	sort(queries.begin(), queries.end());

	for (int i = 0, l = 1, r = 0; i < q; i++) {
		while (l > queries[i].l) { add_value(node_at[--l]); }
		while (r < queries[i].r) { add_value(node_at[++r]); }
		while (l < queries[i].l) { add_value(node_at[l++]); }
		while (r > queries[i].r) { add_value(node_at[r--]); }

		// Check the lca value
		int lc = queries[i].lca;
		if (lc != -1) { add_value(lc); }

        // Answer query
        int a = queries[i].a;
        int b = queries[i].b;
        if(isDebugging) {
            vi dump = st.nums;
            dbg(i, dump, st.blocks, a, b, l, r);
        }
        ans[queries[i].id] = st.query(a, b + 1);

		if (lc != -1) { add_value(lc); }
	}

	for (int i = 1; i <= q; i++) { cout << ans[i] << '\n'; }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    if(isDebugging) {
        dbg("debug");
        // setIn("xd.in");
    }

    int t = 1;
    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        solve();
    }


    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";

        print_memory_usage();
    #endif
}

