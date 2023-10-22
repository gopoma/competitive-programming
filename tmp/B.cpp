// sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>

using namespace std;



// building blocks
using ll = long long;
using db = long double; // or double, if TL is tight
using str = string; // yay python!
// using u128 = __uint128_t; // for Number Theory related
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
void solve(long long xd) {
    RAYA;

    int N;
    cin >> N;

    vector<long long> A(N);
    vector<long long> B(N);

    for(auto& a: A) cin >> a;
    for(auto& b: B) cin >> b;

    vector<string> aux(N);
    int equs = 0;
    int idx_eq = -1;

    for(int i = 0; i < N; i++) {
        if(A[i] > B[i]) {
            aux[i] = "u";
        } else if(A[i] < B[i]) {
            aux[i] = "d";
        } else {
            assert(A[i] == B[i]);
            aux[i] == "d";
            idx_eq = i;

            equs++;
        }
    }

    // DBG(A);
    // DBG(B);
    // DBG(aux);

    // we want d d d u u u
    if(((N % 2 == 0) && equs != 0) || ((N % 2 != 0) && equs != 1)) {
        cout << "Case #" << xd << ": -1\n";
        return;
    }

    // verify d d d u u u u u u
    bool ok1 = (aux[0] == "d");
    bool change1 = false;
    for(int i = 1; i < N; i++) {
        assert(aux[i] == "u" || aux[i] == "d");

        if(change1) {
            if(aux[i] == "u") {
                continue;
            } else {
                ok1 = false;
            }
        } else {
            if(aux[i] == "d") {
                continue;
            } else {
                change1 = true;
            }
        }
    }

    // verify u u u d d d d d d
    bool ok2 = (aux[0] == "u");
    bool change2 = false;
    for(int i = 1; i < N; i++) {
        assert(aux[i] == "u" || aux[i] == "d");

        if(change) {
            if(aux[i] == "d") {
                continue;
            } else {
                ok2 = false;
            }
        } else {
            if(aux[i] == "u") {
                continue;
            } else {
                change = true;
            }
        }
    }

    if(!ok1 && !ok2) {
        cout << "Case #" << xd << ": -1\n";
        return;
    } else {
        if(N % 2 == 0) {
            assert(equs != 0);
            int ans = 0;
        } else {
            assert(equs != 1);
        }
    }
}

signed main() {
    // read read read
    setIO();

    long long T = 1LL;
    cin >> T;

    for(ll i = 1LL; i <= T; i++) {
        solve(i);
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
