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
vector<string> chunk;

// here goes the work!
// The main recursive method
// to print all possible
// strings of length k
void printAllKLengthRec(vector<char>& set, string prefix, int n, int k) {
    // Base case: k is 0,
    // print prefix
    if (k == 0) {
        chunk.eb(prefix);
        return;
    }

    // One by one add all characters
    // from set and recursively
    // call for k equals to k-1
    for (int i = 0; i < n; i++) {
        string newPrefix;

        // Next character of input added
        newPrefix = prefix + set[i];

        // k is decreased, because
        // we have added a new character
        printAllKLengthRec(set, newPrefix, n, k - 1);
    }
}

void printAllKLength(vector<char>& set, int k, int n) {
    chunk.clear();
    printAllKLengthRec(set, "", n, k);
}
// /here goes the template!

// here goes the work!
void solve() {
    const int n = 4;
    V<V<int>> grid(n, V<int>(n));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> grid[i][j];
    // for(auto& v: grid) DBG(v);

    const int k = 8;
    vector<char> set1 = {'1', '2', '3', '4'};
    printAllKLength(set1, k, sz(set1));

    // for(auto& e: chunk) DBG(e);
    V<pair<int, int>> tobeassigned(8);
    tobeassigned[0] = mp(0, 2);
    tobeassigned[1] = mp(0, 3);
    tobeassigned[2] = mp(1, 2);
    tobeassigned[3] = mp(1, 3);
    tobeassigned[4] = mp(2, 0);
    tobeassigned[5] = mp(2, 1);
    tobeassigned[6] = mp(3, 0);
    tobeassigned[7] = mp(3, 1);

    auto good = [&]() {
        bool ok = true;
        // every row
        for(int i = 0; i < n; i++) {
            set<int> S;
            for(int j = 0; j < n; j++) {
                S.ins(grid[i][j]);
            }
            ok &= (sz(S) == 4);
        }

        // every column
        for(int j = 0; j < n; j++) {
            set<int> S;
            for(int i = 0; i < n; i++) {
                S.ins(grid[i][j]);
            }
            ok &= (sz(S) == 4);
        }

        // every 2x2 block
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                set<int> S;
                for(int x = 0; x < 2; x++) {
                    for(int y = 0; y < 2; y++) {
                        S.ins(grid[2 * i + x][2 * j + y]);
                    }
                }
                ok &= (sz(S) == 4);
            }
        }
        return ok;
    };

    bool found = false;
    V<V<int>> res;
    for(auto& assign: chunk) {
        for(int i = 0; i < 8; i++) {
            grid[tobeassigned[i].first][tobeassigned[i].second] = assign[i] - '0';
        }

        // check
        if(good()) {
            found = true;
            res = grid;
        }


        for(int i = 0; i < 8; i++) {
            grid[tobeassigned[i].first][tobeassigned[i].second] = 0;
        }
    }

    if(!found) cout << "No\n";
    else {
        cout << "Yes\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << res[i][j] << " ";
            }
            cout << n_l;
        }
    }
}

// https://codeforces.com/gym/104755/problem/K
// K. Quadroku
signed main() {
    // read read read
	setIO();
    // cout << fixed << setprecision(12);

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
