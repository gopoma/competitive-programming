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
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
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
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

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

tcT> struct SegTree { // cmb(ID,b) = b
	// const T ID{}; T cmb(T a, T b) { return a+b; }
    T ID{}; T cmb(T a, T b) { return max(a, b); }
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


bool check(string& S) {
    const int n = sz(S);
    string stk;
    for(auto& c: S) {
        if(c == '(') stk.push_back('x');
        else {
            if(stk.empty()) return false;
            stk.pop_back();
        }
    }
    return stk.empty();
}

ll brute(ll n, vl a) {
    ll res = 0;
    for(ll mask = 0; mask < (1 << (2 * n)); mask++) {
        string S;
        ll tot = 0;
        for(ll bit = 0; bit < 2 * n; bit++) {
            if(mask & (1LL << bit)) {
                tot += a[bit];
                S.push_back('(');
            }
            else { S.push_back(')'); }
        }
        if(check(S)) {
            ckmax(res, tot);
        }
    }

    for(ll mask = 0; mask < (1 << (2 * n)); mask++) {
        string S;
        ll tot = 0;
        for(ll bit = 0; bit < 2 * n; bit++) {
            if(mask & (1LL << bit)) {
                tot += a[bit];
                S.push_back('(');
            }
            else { S.push_back(')'); }
        }
        if(check(S) && tot == res) {
            dbg(S, tot, res);
        }
    }
    return res;
}

const ll BIG = 1e18;
ll slv(ll n, vl a) {
    ll res = 0;

    multiset<ll> ms;
    ll extra = 1;
    for(int i = 2 * n - 2; i >= 0; i--) {
        if(extra > 0) {
            ms.emplace(a[i]);
            res += a[i];
            extra--;
        } else {
            ll mn = *ms.begin();
            if(a[i] > mn) {
                ms.erase(ms.find(mn));
                res -= mn;

                ms.emplace(a[i]);
                res += a[i];
                extra++;
            } else {
                extra++;
            }
        }
    }
    return res;
}

void solve() {
    ll n; cin >> n;
    vl a(2 * n); for(auto& x: a) cin >> x;
    dbg(n);
    dbg(a);
    ll res = slv(n, a);
    dbg(res);
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(1) {
        RAYA;
        ll n = rng_ll(1, 9);
        vl a(2 * n); for(auto& x: a) x = rng_ll(0, ll(1e9));
        dbg(n);
        dbg(a);
        ll ans = brute(n, a);
        ll greedy = slv(n, a);
        dbg(ans, greedy);
        assert(ans == greedy);
    }

    ll t; cin >> t;
    while(t--) {
        solve();
    }
}
