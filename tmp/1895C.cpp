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



// using u128 = __uint128_t;
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;



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

// here goes the template!
// /here goes the template!

// here goes the work!
ll sum(string S) {
    ll res = 0LL;
    for(auto& c: S) res += ll(c - '0');

    return res;
}

// bool lucky(string& a, string& b) {
//     string c = a + b;
//     assert(sz(c) % 2 == 0);
//
//     string fhalf = "";
//     string shalf = "";
//     for(int i = 0; i < sz(c)/2; i++) {
//         fhalf += c[i];
//     }
//     for(int i = sz(c)/2; i < sz(c); i++) {
//         shalf += c[i];
//     }
//
//     return (sum(fhalf) == sum(shalf));
// }

void solve() {
    int n;
    cin >> n;

    vector<string> a(n);
    for(auto& e: a) cin >> e;

    // 1 3 5 -> 1 + 1 | 1 + 3 | 1 + 5 | 3 + 1 | 3 + 3 | 3 + 5 | 5 + 1 | 5 + 3 | 5 + 5
    // 2 4 -> 2 + 2 | 2 + 4 | 4 + 2 | 4 + 4

    // map<pair<int, int>, pair<vector<int>, vector<int>>> aux;
    map<pair<int, int>, pair<map<int, int>, map<int, int>>> xd;

    vector<pair<int, int>> keys;
    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= 5; j++) {
            if(i % 2 == 1 && j % 2 == 1) {
                keys.eb(make_pair(i, j));
            } else if(i % 2 == 0 && j % 2 == 0) {
                keys.eb(make_pair(i, j));
            }
        }
    }

    // for(auto& it: keys) DBG2(it.first, it.second);

    for(int i = 0; i < n; i++) {
        for(auto& k: keys) {
            if(k.first == sz(a[i])) {
                if(k.first < k.second) {
                    // aux[k].first.eb(sum(a[i]));

                    xd[k].first[sum(a[i])]++;
                } else if(k.first > k.second) {
                    int take = (k.first + k.second) / 2;
                    //! aux[k].first.eb(sum(a[i].substr(0, take)) - sum(a[i].substr(take, sz(a) - take)));

                    xd[k].first[sum(a[i].substr(0, take)) - sum(a[i].substr(take, sz(a) - take))]++;
                } else {
                    assert(k.first == k.second);
                    // aux[k].first.eb(sum(a[i]));
                    // aux[k].second.eb(sum(a[i]));

                    xd[k].first[sum(a[i])]++;
                    xd[k].second[sum(a[i])]++;
                }
            } else if(k.second == sz(a[i])) {
                if(k.second < k.first) {
                    // aux[k].second.eb(sum(a[i]));

                    xd[k].second[sum(a[i])]++;
                } else if(k.second > k.first) {
                    int take = (k.first + k.second) / 2;
                    // DBG4(k.first, k.second, a[i], take);
                    int notake = sz(a[i]) - take;
                    // DBG4(k.first, k.second, sum(a[i].substr(sz(a[i]) - take, take)), sum(a[i].substr(0, notake)));

                    //! aux[k].second.eb(sum(a[i].substr(sz(a[i]) - take, take)) - sum(a[i].substr(0, notake)));

                    xd[k].second[sum(a[i].substr(sz(a[i]) - take, take)) - sum(a[i].substr(0, notake))]++;
                } else {
                    assert(k.first == k.second);
                    // aux[k].first.eb(sum(a[i]));
                    // aux[k].second.eb(sum(a[i]));

                    xd[k].first[sum(a[i])]++;
                    xd[k].second[sum(a[i])]++;
                }
            }
        }
    }

    // for(auto& it: aux) {
    //     DBG2(it.first, it.second);
    // }

    //! map<pair<int, int>, pair<map<int, int>, map<int, int>>> xd;
    ll ans = 0LL;
    for(auto& it: xd) {
        pair<map<int, int>, map<int, int>> it2 = xd[it.first];
        map<int, int> left = it2.first;
        map<int, int> right = it2.second;

        for(auto& x: left) {
            ans += ll(left[x.first]) * ll(right[x.first]);
        }
    }
    cout << ans << n_l;

    /*
    // int ans = 0;
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         if(((sz(a[i]) % 2) == (sz(a[j]) % 2)) && lucky(a[i], a[j])) {
    //             DBG4(i, j, a[i], a[j]);
    //             ans++;
    //         }
    //     }
    // }
    // DBG(ans);
    */
}

signed main() {
    // read read read
	setIO();

    long long t = 1LL;
    // cin >> t;

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