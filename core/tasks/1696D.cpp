//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;

//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return string(1, c);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A>
string to_string(A v);

string to_string(vector<bool> v) {
    bool first = true;
    string res = "[";
    for (auto x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += x ? "true" : "false";
    }
    res += "]";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}


template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "[";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "]";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(xd) << "\033[0m" << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m";)

#define GA          dbg(0)
#define RAYA        cout << "\033[101m" << "================================" << "\033[0m" << endl;

const bool isDebugging = true;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA

const bool isDebugging = false;
#endif
//* /Debugger

using ll = long long;
using db = long double; // or double if tight TL
using str = string;

using pi = pair<int,int>;
using pl = pair<ll, ll>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vl = V<ll>;
using vb = V<bool>;
using vpi = V<pi>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7;
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}


//* Template
/**
 * Description: 1D point update and range query where \texttt{cmb} is
 	* any associative operation. \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 * API: SegTree<node> tree; tree.init(int(n));
 */

tcT> struct SegTreeMax { // cmb(ID,b) = b
	// const T ID{}; T cmb(T a, T b) { return a+b; }
    T ID{-BIG}; T cmb(T a, T b) { return max(a, b); }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// zero-indexed, inclusive
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}
	/// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
	/// 	if (r < lo || val > seg[ind]) return -1;
	/// 	if (l == r) return l;
	/// 	int m = (l+r)/2;
	/// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
	/// 	return first_at_least(lo,val,2*ind+1,m+1,r);
	/// }
};

tcT> struct SegTreeMin { // cmb(ID,b) = b
	// const T ID{}; T cmb(T a, T b) { return a+b; }
    T ID{BIG}; T cmb(T a, T b) { return min(a, b); }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// zero-indexed, inclusive
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}
	/// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
	/// 	if (r < lo || val > seg[ind]) return -1;
	/// 	if (l == r) return l;
	/// 	int m = (l+r)/2;
	/// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
	/// 	return first_at_least(lo,val,2*ind+1,m+1,r);
	/// }
};
// /here goes the template!

struct node {
    static long long Mod;

	long long val;

	node(): val(1LL) {}

	node(long long _val) : val(_val) {}

	node operator + (const node &rhs) const {
		return node((val * rhs.val) % Mod);
	}
};

//* /Template

ll brute(ll n, vl a) {
    V<vl> adj(n + 1);
    for(ll u = 1; u <= n; u++) {
        for(ll v = 1; v <= n; v++) {
            ll mn = BIG, mx = -BIG;
            for(ll k = min(u, v); k <= max(u, v); k++) {
                mn = min(mn, a[k]);
                mx = max(mx, a[k]);
            }
            if((mn == a[u] && mx == a[v]) || (mn == a[v] && mx == a[u])) {
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
            }
        }
    }
    vb vis(n + 1);
    vl dist(n + 1);
    deque<ll> q;

    vis[1] = true;
    dist[1] = 0;
    q.emplace_back(1);

    while(!q.empty()) {
        auto cur = q.front(); q.pop_front();
        for(auto& nxt: adj[cur]) {
            if(!vis[nxt]) {
                vis[nxt] = true;
                dist[nxt] = dist[cur] + 1;
                q.emplace_back(nxt);
            }
        }
    }

    assert(vis[n]);
    return dist[n];
}

ll brute2(ll n, vl a) {
    // <>
    V<vl> adj(n + 1);
    for(ll u = 1; u <= n; u++) {
        ll nxt = u;
        for(ll v = u; v <= n; v++) {
            ll mn = BIG, mx = -BIG;
            for(ll k = min(u, v); k <= max(u, v); k++) {
                mn = min(mn, a[k]);
                mx = max(mx, a[k]);
            }
            if((mn == a[u] && mx == a[v]) || (mn == a[v] && mx == a[u])) {
                nxt = v;
            }
        }
        adj[u].emplace_back(nxt);
        adj[nxt].emplace_back(u);
    }
    vb vis(n + 1);
    vl dist(n + 1);
    deque<ll> q;

    vis[1] = true;
    dist[1] = 0;
    q.emplace_back(1);

    while(!q.empty()) {
        auto cur = q.front(); q.pop_front();
        for(auto& nxt: adj[cur]) {
            if(!vis[nxt]) {
                vis[nxt] = true;
                dist[nxt] = dist[cur] + 1;
                q.emplace_back(nxt);
            }
        }
    }

    assert(vis[n]);
    return dist[n];
}


tcT, size_t SZ> struct RMQMax { // floor(log_2(x))
	static constexpr int level(int x) { return 31-__builtin_clz(x); }
	array<array<T,SZ>, level(SZ)+1> jmp;
	T cmb(T a, T b) { return max(a, b); }
	void init(const V<T>& v) { assert(sz(v) <= SZ);
		copy(all(v), begin(jmp[0]));
		for (int j = 1; 1<<j <= sz(v); ++j) {
			F0R(i,sz(v)-(1<<j)+1) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	T query(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
};


tcT, size_t SZ> struct RMQMin { // floor(log_2(x))
	static constexpr int level(int x) { return 31-__builtin_clz(x); }
	array<array<T,SZ>, level(SZ)+1> jmp;
	T cmb(T a, T b) { return min(a, b); }
	void init(const V<T>& v) { assert(sz(v) <= SZ);
		copy(all(v), begin(jmp[0]));
		for (int j = 1; 1<<j <= sz(v); ++j) {
			F0R(i,sz(v)-(1<<j)+1) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	T query(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
};

RMQMax<ll, 250000 + 5> stMax;
RMQMin<ll, 250000 + 5> stMin;
ll slv(ll n, vl a) {
    // <>
    auto work = [&](vl arr) -> vl {
       // dbg(arr);
        stMax.init(arr);
        stMin.init(arr);

        vl prv(n + 1); // for max
        vl nxt(n + 1); // for min
        for(int i = 1; i <= n; i++) {
            { // for max
                ll left = 0;  // always bad
                ll right = i; // always good
                while(left + 1 < right) {
                    ll middle = (left + right) >> 1LL;
                    if(stMax.query(middle, i) <= arr[i]) right = middle;
                    else left = middle;
                }
                prv[i] = right;
            }
            { // for min
                ll left = i;      // always good
                ll right = n + 1; // always bad
                while(left + 1 < right) {
                    ll middle = (left + right) >> 1LL;
                    if(stMin.query(i, middle) >= arr[i]) left = middle;
                    else right = middle;
                }
                nxt[i] = left;
            }
        }

        V<vl> todoAdd(n + 1), todoDelete(n + 1);
        for(int i = 1; i <= n; i++) {
            todoAdd[prv[i]].emplace_back(i);
            todoDelete[i].emplace_back(i);
       //     dbg(i, prv[i], nxt[i]);
        }
        vl re(n + 1);
        SegTreeMax<ll> st; st.init(n + 1);
        for(int i = 1; i <= n; i++) {
            for(auto& x: todoAdd[i]) {
                st.upd(x, x);
            }
            re[i] = st.query(i, nxt[i]);
            for(auto& x: todoDelete[i]) {
                st.upd(x, -BIG);
            }
        }
        return re;
    };
    vl nxt = work(a);
    vl b;
    for(int i = 1; i <= n; i++) b.emplace_back(a[i]);
    reverse(all(b));
    b.insert(b.begin(), 0LL);
    vl nxtRev = work(b);
    // dbg(a);
    // dbg(nxt);
    // dbg(b);
    // dbg(nxtRev);


    V<vl> adj(n + 1);
    for(int i = 1; i <= n; i++) {
        adj[i].emplace_back(nxt[i]);
        adj[nxt[i]].emplace_back(i);

        ll u = (n + 1) - nxtRev[i];
        ll v = (n + 1) - i;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vb vis(n + 1);
    vl dist(n + 1);
    deque<ll> q;

    vis[1] = true;
    dist[1] = 0;
    q.emplace_back(1);

    while(!q.empty()) {
        auto cur = q.front(); q.pop_front();
        for(auto& nxt: adj[cur]) {
            if(!vis[nxt]) {
                vis[nxt] = true;
                dist[nxt] = dist[cur] + 1;
                q.emplace_back(nxt);
            }
        }
    }

    assert(vis[n]);
    return dist[n];
}

void solve() {
    ll n; cin >> n;
    vl a(n + 1); for(int i = 1; i <= n; i++) cin >> a[i];
    dbg(n);
    dbg(a);
    ll re = slv(n, a);
    dbg(re);
    cout << re << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(0) {
        RAYA;
        RAYA;
        RAYA;
        ll n = rng_ll(int(2e5), int(2e5));

        vl a(n); iota(all(a), 1LL);
        shuffle(all(a), rng);
        a.insert(a.begin(), 0LL);
        dbg(n);
        //dbg(n, a);

        //ll ans = brute(n, a);
        ll gre = slv(n, a);
        //dbg(ans, gre);
        //assert(ans == gre);
    }

    int t = 1;
    cin >> t;
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
    #endif
}
