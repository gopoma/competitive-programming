// sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>

using namespace std;



// building blocks
using ll = long long;
using ull = unsigned long long;
using db = long double; // or double, if TL is tight
using str = string; // yay python!
// using u128 = __uint128_t; // for Number Theory related
// using i128 = __int128;
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>; // minima



// pairs
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;

#define mp make_pair
#define f first
#define s second



#define tcT template<class T
#define tcTU tcT, class U
// ^ lol this makes everything look weird but I'll try it



tcT> using V = vector<T>; //?
tcT, size_t SZ> using AR = array<T,SZ>;
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
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }



// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { // assert(x >= 0); // make C++11 compatible until USACO updates ...
	return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x))
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }



ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down



#define tcTUU tcT, class ...U

inline namespace FileIO {
	void setIn(str s)  { freopen(s.c_str(),"r",stdin); }
	void setOut(str s) { freopen(s.c_str(),"w",stdout); }
	void setIO(str s = "") {
		cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
		// cin.exceptions(cin.failbit);
		// throws exception when do smth illegal
		// ex. try to read letter into int
		if (sz(s)) setIn(s+".in"), setOut(s+".out"); // for old USACO
	}
}



// for debugging!
#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < int(v.size()); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

template <typename T>
ostream& operator <<(ostream &os, const set<T>& v) {
    vector<T> tmp;
    for(auto& e: v) {
        tmp.emplace_back(e);
    }

    return os << tmp;
}

template <typename T>
ostream& operator <<(ostream &os, const pair<T, T>& v) {
    return os << "{" << v.first << ", " << v.second << "}";
}



mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

// Direction vectors
int dRow[] = { -1, 0, 1,  0 };
int dCol[] = {  0, 1, 0, -1 };

const int MOD = (int)1e9+7; // 998244353;
const int MX = (int)2e5+5;
const ll BIG = 1e18; // not too close to LLONG_MAX
const db PI = acos((db)-1);
const char n_l = '\n';

template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

template<typename T>
T pot(T a, T b) { // a^b
    assert(b >= 0);

    T res = 1;
    for(int _ = 1; _ <= b; _++) res *= a;
    return res;
}

// here goes the template!
// /here goes the template!

// here goes the work!
bool check(vector<int>& a, vector<int>& b) {
    // DBG2(a, b);
    bool ok = true;
    for(auto& e: b) ok &= (e == 1 || e == 2 || e == 3);

    // DBG(ok);

    bool ok1 = false;
    bool ok2 = false;
    bool ok3 = false;
    assert(sz(a) == sz(b));
    const int n = sz(a);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            bool pp1 = (a[i] == a[j] && b[i] == 1 && b[j] == 2);
            bool pp2 = (a[i] == a[j] && b[i] == 1 && b[j] == 3);
            bool pp3 = (a[i] == a[j] && b[i] == 2 && b[j] == 3);

            // if(pp1) { DBG4(a[i], a[j], b[i], b[j]); }
            // if(pp2) { DBG4(a[i], a[j], b[i], b[j]); }
            // if(pp3) { DBG4(a[i], a[j], b[i], b[j]); }

            ok1 |= pp1;
            ok2 |= pp2;
            ok3 |= pp3;
        }
    }

    int cnt = 0;
    cnt += ok1;
    cnt += ok2;
    cnt += ok3;
    // DBG4(ok1, ok2, ok3, cnt);

    ok &= (cnt == 2);
    return ok;
}

void solve() {
    int n;
    cin >> n;

    V<int> a(n);
    for(auto& e: a) cin >> e;

    map<int, vector<int>> mps;
    for(int i = 0; i < n; i++) {
        mps[a[i]].eb(i);
    }

    // for(auto& it: mps) DBG2(it.first, it.second);

    vector<vector<int>> goods;
    vector<vector<int>> bads;
    for(auto& it: mps) {
        if(sz(it.second) >= 2) {
            // good
            goods.eb(it.second);
        }
    }

    if(sz(goods) >= 2) {
        vector<int> ans(n, -1);
        vector<int> ff = goods.back(); goods.pop_back();
        vector<int> bb = goods.back(); goods.pop_back();

        ans[ff[0]] = 1;
        ans[ff[1]] = 2;
        for(int i = 2; i < sz(ff); i++) ans[ff[i]] = 2;

        ans[bb[0]] = 1;
        ans[bb[1]] = 3;
        for(int i = 2; i < sz(bb); i++) ans[bb[i]] = 3;

        for(auto& g: goods) {
            for(int i = 0; i < sz(g); i++) {
                ans[g[i]] = 1;
            }

        }

        for(int i = 0; i < n; i++) {
            if(ans[i] == -1) ans[i] = 1;
        }

        // assert(check(a, ans));
        for(int i = 0; i < n; i++) {
            cout << ans[i] << " \n"[i == n - 1];
        }
    } else {
        cout << "-1\n";
    }
    // RAYA;
}

signed main() {
    // read read read
	setIO();
    // cout << fixed << setprecision(12);

    long long t = 1LL;
    cin >> t;

    while(t--) {
        solve();
    }

    // should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/

//! ERASE DBGs xd or TLE