#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
using namespace std;



using ll = long long;
using db = long double; // or double if tight TL
using str = string;



using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f first
#define s second



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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



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



#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



// Debugger
const string PAIR_LEFT = "(";
const string PAIR_RIGHT = ")";
const string IT_LEFT = "[";
const string IT_RIGHT = "]";
const string PAIR_SEP = ", ";
const string IT_SEP = ", ";

// benq - print any container + pair
template<typename T, typename = void> struct is_iterable : false_type {};
template<typename T> struct is_iterable<T, void_t<decltype(begin(declval<T>())),decltype(end(declval<T>()))>> : true_type {};
template<typename T> typename enable_if<is_iterable<T>::value&&!is_same<T, string>::value,ostream&>::type operator<<(ostream &cout, T const &v);
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << PAIR_LEFT << p.f << PAIR_SEP << p.s << PAIR_RIGHT; }
template<typename T> typename enable_if<is_iterable<T>::value&&!is_same<T, string>::value,ostream&>::type operator<<(ostream &cout, T const &v) {
    cout << IT_LEFT;
    for (auto it = v.begin(); it != v.end();) {
        cout << *it;
        if (++it != v.end()) cout << IT_SEP;
    }
    return cout << IT_RIGHT;
}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) {
    cin >> p.first;
    return cin >> p.second;
}

template<typename T> void debug(string s, T x) {cerr << "\033[1;34m" << s << "\033[0;32m = \033[35m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
        if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;34m" << s.substr(0, i) << "\033[0;32m = \033[35m" << x << "\033[31m | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}
template<typename T> void debug_nameless(T x) {cerr << "\033[35m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug_nameless(T x, Args... args) {cerr << "\033[35m" << x << "\033[31m | "; debug_nameless(args...);}



#ifdef LOCAL
    const bool isDebugging = true;

    #define MACRO(code) do {code} while (false)
    #define dbg(...) MACRO(cerr << "Line(" << __LINE__ << "): "; debug(#__VA_ARGS__, __VA_ARGS__);)
    #define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);
    #define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
    const bool isDebugging = false;

    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }
// /Debugger



const int MOD = 1e9+7;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)



//* Template
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}
//* /Template

void slv(int n, int root, vi parent, vi should) {
    chk(root != -1);
    parent[root] = -1;
    vvi adj(n);
    for(int u = 0; u < n; u++) {
        if(u == root) continue;
        adj[u].eb(parent[u]);
        adj[parent[u]].eb(u);
    }
    {
        vi subtree_size(n);
        auto dfs = [&](const auto& dfs, int src, int par) -> void {
            subtree_size[src] = 1;
            for(auto& nxt: adj[src]) {
                if(nxt == par) continue;
                dfs(dfs, nxt, src);
                subtree_size[src] += subtree_size[nxt];
            }
        }; dfs(dfs, root, -1);
        for(int u = 0; u < n; u++) {
            // dbg(u, should[u], subtree_size[u]);
            // dbg(adj[u]);
            if(should[u] >= subtree_size[u]) {
                cout << "NO\n";
                return;
            }
        }
    }

    set<int> S;
    auto dfs = [&](const auto& dfs, int src, int par) -> vpi {
        vpi children_data;
        for(auto& nxt: adj[src]) {
            if(nxt == par) continue;
            auto partial = dfs(dfs, nxt, src);
            for(auto& it: partial) children_data.eb(it);
        }
        vpi ans;
        if(children_data.empty()) {
            int cur = -1;
            if(S.empty()) {
                cur = 1;
            } else {
                cur = (*S.rbegin()) + 1;
            }
            chk(cur != -1);
            swap(ans, children_data);
            ans.eb(cur, src);
            S.emplace(cur);
        } else {
            sor(children_data);
            children_data.insert(children_data.begin() + should[src], mp(0, src));

            for(int i = should[src] + 1; i < sz(children_data); i++) {
                children_data[i].f++;
            }

            if(0 <= should[src] - 1) {
                children_data[should[src]].f = children_data[should[src] - 1].f + 1;
            } else {
                chk(should[src] + 1 < sz(children_data));
                children_data[should[src]].f = children_data[should[src] + 1].f - 1;
            }
            S.emplace(children_data.ft.f);
            S.emplace(children_data.bk.f);
            swap(ans, children_data);
        }
        // dbg(src, par, ans);
        return ans;
    };
    auto temp = dfs(dfs, root, -1);
    vi response(n);
    for(auto& [val, i]: temp) response[i] = val;
    dbg(response);
    cout << "YES\n";
    for(auto& x: response) cout << x << " ";
    cout << "\n";
    if(isDebugging) {
        vi cnt(n);
        for(int u = 0; u < n; u++) {
            auto dfs2 = [&](const auto& dfs2, int src, int par) -> void {
                if(src == parent[u]) return;
                cnt[u] += (response[u] > response[src]);
                for(auto& nxt: adj[src]) {
                    if(nxt == par) continue;
                    dfs2(dfs2, nxt, src);
                }
            }; dfs2(dfs2, u, -1);
            // dbg(u, cnt[u]);
        }
        dbg(cnt, should);
        chk(cnt == should);

        remDup(response);
        chk(sz(response) == n);

        for(auto& x: response) chk(1 <= x && x <= ll(1e9));
    }
}

void solve() {
    int n; cin >> n;
    int root = -1;
    vi parent(n);
    vi should(n);
    for(int u = 0; u < n; u++) {
        int p, c; cin >> p >> c;
        if(p == 0) {
            root = u;
        } else {
            p--;
            parent[u] = p;
        }
        should[u] = c;
    }
    dbg(n, root);
    dbg(parent);
    dbg(should);
    slv(n, root, parent, should);
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
	assert(N >= 1 && back >= 0); vpi ed;
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    dbg(isDebugging);

    //? Stress Testing
    while(0) {
        RAYA;
        int n = rng_int(1, 1000);
        int root = rng_int(0, n - 1);
        vi parent(n);
        vi should(n);
        {
            vpi edges = treeRand(n, rng_int(0, n + 5));
            vvi adj(n);
            for(auto& [u, v]: edges) {
                adj[u].eb(v);
                adj[v].eb(u);
            }
            vi subtree_size(n);
            auto dfs = [&](const auto& dfs, int src, int par) -> void {
                parent[src] = par;
                subtree_size[src] = 1;
                for(auto& nxt: adj[src]) {
                    if(nxt == par) continue;
                    dfs(dfs, nxt, src);
                    subtree_size[src] += subtree_size[nxt];
                }
            }; dfs(dfs, root, -1);
            for(int u = 0; u < n; u++) should[u] = rng_int(0, subtree_size[u] - 1);
        }
        // dbg(n, root);
        // dbg(parent);
        // dbg(should);
        slv(n, root, parent, should);
    }

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
