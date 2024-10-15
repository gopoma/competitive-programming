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



// Pocochuk Adapter
using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;



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

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)
//? /Template

using E = tuple<ll, ll, ll>;
const ll BIG = ll(1e18);
void solve() {
    ll caso = 0;
    V<vs> final_responses;
    while(1) {
        caso++;
        ll C, S, Q; cin >> C >> S >> Q; if(C == 0 && S == 0 && Q == 0) break;
        V<E> edges;
        rep(S) {
            ll u, v, d; cin >> u >> v >> d;
            u--; v--;
            edges.eb(d, u, v);
        }
        vpl queries(Q); each(x, queries) { cin >> x.f >> x.s; x.f--; x.s--; }

        sor(edges);

        dbg(C, S, Q);
        dbg(edges);
        dbg(queries);

        V<vpl> adj(C);
        DSU dsu; dsu.init(C);
        V<E> good_edges;
        for(auto& [w, u, v]: edges) {
            if(dsu.unite(u, v)) {
                adj[u].eb(v, w);
                adj[v].eb(u, w);
                good_edges.eb(w, u, v);
            }
        }
        dbg(good_edges);
        //? for(auto& [w, u, v]: good_edges) cout << (u + 1) << " " << (v + 1) << " " << w << "\n";

        vvl ans(C, vl(C, -BIG));
        for(int u = 0; u < C; u++) {
            for(int v = 0; v < C; v++) {
                if(u != v && dsu.sameSet(u, v)) {
                    vpl stk;
                    vb vis(C);
                    bool rage = false;
                    function<void(int)> dfs = [&](int src) -> void {
                        if(rage) return;
                        if(vis[src]) return;
                        vis[src] = true;

                        for(auto& [nxt, w]: adj[src]) {
                            stk.eb(src, w);

                            if(nxt == v) {
                                ll response = -BIG;
                                while(stk.bk.f != u) {
                                    ckmax(response, stk.bk.s);
                                    stk.pop_back();
                                }
                                ckmax(response, stk.bk.s);
                                ans[u][v] = response;
                                rage = true;
                                if(rage) return;
                            }

                            dfs(nxt);
                            if(rage) return;
                            stk.pop_back();
                        }
                        if(rage) return;
                    }; dfs(u);
                }
            }
        }


        //? cout << "Case #" << caso << "\n";
        vs current_response;
        for(auto& [u, v]: queries) {
            dbg(u + 1, v + 1, ans[u][v]);
            if(ans[u][v] == -BIG) {
                current_response.eb("no path");
            } else current_response.eb(ts(ans[u][v]));
        }
        final_responses.eb(current_response);
        RAYA;
    }
    dbg(final_responses);
    {
        const int N = sz(final_responses);
        for(int i = 0; i < N; i++) {
            cout << "Case #" << (i + 1) << "\n";

            const int M = sz(final_responses[i]);
            for(int j = 0; j < M; j++) {
                cout << final_responses[i][j] << "\n";
            }

            if(i == N - 1) continue;
            else cout << "\n";
        }
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int t = 1; //! cin >> t;
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
