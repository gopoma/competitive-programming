#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
 
using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f  first
#define s  second



#define tcT template <class T
#define tcTU tcT, class U

tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

// vectors
// oops size(x), rbegin(x), rend(x) need C++17
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



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



//? Template
/**
 * Description: Disjoint Set Union with path compression
 	* and union by size. Add edges and test connectivity.
 	* Use for Kruskal's or Boruvka's minimum spanning tree.
 * Time: O(\alpha(N))
 * Source: CSAcademy, KACTL
 * Verification: *
 */

struct DSU {
	vi e; void init(int N) { e = vi(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};

/**tcT> T kruskal(int N, vector<pair<T,pi>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N); // edges that unite are in MST
	each(a,ed) if (D.unite(a.s.f,a.s.s)) ans += a.f;
	return ans;
}*/
//? /Template

void solve() {
    ll n, q; cin >> n >> q;
    vl p(n); each(x, p) { cin >> x; x--; }
    str S; cin >> S;
    vl queries(q); each(x, queries) { cin >> x; x--; }
    dbg(n, q);
    dbg(p);
    dbg(S);
    dbg(queries);

    vl where(n);
    for(int i = 0; i < n; i++) where[p[i]] = i;

    DSU dsu; dsu.init(n);
    for(int i = 0; i < n; i++) {
        if(i < where[i]) {
            int right = where[i];
            while(!dsu.sameSet(i, right)) {
                dsu.unite(right, right - 1);
                right--;
            }
        }
        if(i < where[p[i]]) {
            int right = where[p[i]];
            while(!dsu.sameSet(i, right)) {
                dsu.unite(right, right - 1);
                right--;
            }
        }
    }
    for(int u = 0; u < n; u++) dbg(u, dsu.get(u));

    int bads = 0;
    for(int i = 0; i + 1 < n; i++) {
        if(S[i] == 'L' && S[i + 1] == 'R' && dsu.sameSet(i, i + 1)) {
            bads++;
        }
    }

    for(auto& x: queries) {
        if(S[x] == 'L') {
            if(S[x - 1] == 'L')  {
                if(dsu.sameSet(x, x - 1)) {
                    bads++;
                }
            }
            if(x + 1 < n && S[x + 1] == 'R') {
                if(dsu.sameSet(x, x + 1)) {
                    bads--;
                }
            }
        } else {
            if(S[x + 1] == 'R') {
                if(dsu.sameSet(x, x + 1)) {
                    bads++;
                }
            }
            if(x - 1 >= 0 && S[x - 1] == 'L') {
                if(dsu.sameSet(x, x - 1)) {
                    bads--;
                }
            }
        }
        S[x] = (S[x] == 'L')? 'R' : 'L';
        bool ok = (bads == 0);
        cout << (ok?"YES":"NO") << "\n";
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int t = 1; cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        solve();
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
