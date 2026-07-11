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
const vector<string> __C_DBG{
    "\033[1;34m",
    "\033[0;32m = \033[35m",
    "\033[0m",
    "]\033[35m:",
    "\033[101m",
    "\033[0m"
};

#define MACRO(code) do {code} while (false)

#define dbg(x)      MACRO(  \
    auto xd = x;    \
    cerr << "Line(" << __LINE__ << "): " << __C_DBG[0] << #x << __C_DBG[1] << to_string(xd) << __C_DBG[2] << endl;  \
)



#define dbg(...)    MACRO(  \
    cerr << "Line(" << __LINE__ << "): " << __C_DBG[0] << "[" << #__VA_ARGS__ << __C_DBG[3];    \
    debug_out(__VA_ARGS__);     \
    cerr << __C_DBG[2];     \
)

#define GA          dbg(0)
// RAYA tiene 32 caracteres "="
#define RAYA        cerr << __C_DBG[4] << "================================" << __C_DBG[5] << endl;

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
#define mp make_pair
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



const int MOD = int(1e9) + 7;
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); }  // # of bits set
constexpr int bits(int x) {  // assert(x >= 0); // make C++11 compatible until
	                         // USACO updates ...
	return x == 0 ? 0 : 31 - __builtin_clz(x);
}  // floor(log2(x))
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }

ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

tcTU > T fstTrue(T lo, T hi, U f) {
	++hi;
	assert(lo <= hi);  // assuming f is increasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo) / 2;
		f(mid) ? hi = mid : lo = mid + 1;
	}
	return lo;
}
tcTU > T lstTrue(T lo, T hi, U f) {
	--lo;
	assert(lo <= hi);  // assuming f is decreasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo + 1) / 2;
		f(mid) ? lo = mid : hi = mid - 1;
	}
	return lo;
}
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



void setIn(string s) { freopen(s.c_str(), "r", stdin); }
void setOut(string s) { freopen(s.c_str(), "w", stdout); }

const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}



//? Custom Helpers
template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;
//? /Custom Helpers



//* Template
/**
 * Description: Tests primality up to $SZ$. Runs faster if only
 	* odd indices are stored.
 * Time: O(SZ\log\log SZ) or O(SZ)
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/primesieve
 */
//! Be careful that every prime in primes are int

template<int SZ> struct Sieve {
	bitset<SZ> is_prime; vi primes;
	Sieve() {
		is_prime.set(); is_prime[0] = is_prime[1] = 0;
		for (int i = 4; i < SZ; i += 2) is_prime[i] = 0;
		for (int i = 3; i*i < SZ; i += 2) if (is_prime[i])
			for (int j = i*i; j < SZ; j += i*2) is_prime[j] = 0;
		F0R(i,SZ) if (is_prime[i]) primes.pb(i);
	}
	// int sp[SZ]{}; // smallest prime that divides
	// Sieve() { // above is faster
	// 	FOR(i,2,SZ) {
	// 		if (sp[i] == 0) sp[i] = i, primes.pb(i);
	// 		for (int p: primes) {
	// 			if (p > sp[i] || i*p >= SZ) break;
	// 			sp[i*p] = p;
	// 		}
	// 	}
	// }
};

Sieve<int(400)> st;

// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);
}

// return double in [L,R] inclusive
db rng_db(db L, db R) { assert(L <= R);
	return uniform_real_distribution<db>(L,R)(rng);
}

template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
	assert(N >= 1 && back >= 0); vpi ed;
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed;
}

//* /Template

vpi check(vvi re) {
    const int n = sz(re);

    for(int r1 = 0; r1 < n; r1++) {
        for(int c1 = 0; c1 < n; c1++) {
            for(int r2 = r1 + 1; r2 < n; r2++) {
                for(int c2 = c1 + 1; c2 < n; c2++) {
                    if(
                        re[r1][c1] == -67 ||
                        re[r2][c2] == -67 ||
                        re[r1][c2] == -67 ||
                        re[r2][c1] == -67
                    ) {continue;}

                    int x = re[r1][c1] + re[r2][c2];
                    int y = re[r1][c2] + re[r2][c1];
                    x %= n;
                    y %= n;

                    if(x == y) {
                        return vpi{{r1, c1}, {r2, c2}};
                    }
                }
            }
        }
    }

    return vpi{};
};


ofstream out("D4.out");
void slv2(int n, vi b) {
    vi a;
    set<vvi> aux;
    auto dfs = [&](auto&& self, int iter) -> void {
        vi values = a; while(sz(values) < n * n) values.eb(-67);

        vvi re(n, vi(n, -67));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                re[i][j] = values[n * i + j];
            }
        }

        for(int i = 0; i < n; i++) {
            re[i][i] = b[i];
        }

        // dbg("Candidate");
        // for(auto& vec: re) dbg(vec);
        if(!check(re).empty()) return;




        if(iter == n * n) {
            aux.emplace(re);
            //dbg("Good Matrix");
            //for(auto& vec: re) {
            //    dbg(vec);
            //}
            out << "Good Matrix\n";
            for(auto& vec: re) {
                for(auto& x: vec) {
                    out << x << " ";
                }
                out << "\n";
            }
            return;
        }


        bool skip = false;
        for(int i = 0; i < n; i++) {
            int j = i;
            if(iter == (n * i + j)) {
                skip = true;
            }
        }

        if(skip) {
            a.eb(-67);
            self(self, iter + 1);
            a.pop_back();
        } else {
            for(int nxt = 0; nxt < n; nxt++) {
                a.eb(nxt);
                self(self, iter + 1);
                a.pop_back();
            }
        }
    }; dfs(dfs, 0);

    //for(auto& re: aux) {
    //    dbg("Good Matrix");
    //    for(auto& vec: re) {
    //        dbg(vec);
    //    }
    //}
    dbg(sz(aux));
    out << "Ways: " << sz(aux) << "\n";
}


void brute(int n) {
    vi a;
    auto dfs = [&](auto&& self, int iter) -> void {
        vvi re(n, vi(n, -67));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(n * i + j >= sz(a)) {
                    re[i][j] = -67;
                } else {
                    re[i][j] = a[n * i + j];
                }
            }
        }
        if(!check(re).empty()) return;

        if(iter == n * n) {
            dbg("Good Matrix");
            for(auto& vec: re) {
                dbg(vec);
            }

            return;
        }


        for(int nxt = 0; nxt < n; nxt++) {
            a.eb(nxt);
            self(self, iter + 1);
            a.pop_back();
        }
    }; dfs(dfs, 0);

    //for(auto& re: aux) {
    //    dbg("Good Matrix");
    //    for(auto& vec: re) {
    //        dbg(vec);
    //    }
    //}
}



void slv(int n, vi b) {
    vvi re(n, vi(n));
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < n; j++) {
            re[i][j] = re[i][j - 1] + i;
            re[i][j] %= n;
        }
    }
    if(isDebugging) assert(check(re).empty());

    for(int i = 0; i < n; i++) {
        int x = re[i][i];
        int inc = 0;
        while(x != b[i]) {
            x++;
            x %= n;

            inc++;
        }

        for(int j = 0; j < n; j++) {
            re[i][j] += inc;
            re[i][j] %= n;
        }
    }

    if(isDebugging) assert(check(re).empty());
    for(auto& vec: re) {
        for(auto& x: vec) cout << x << " ";
        cout << "\n";
    }
}

void solve() {
    // run A < A3.in
    // xd A < A4.in

    int n; cin >> n;
    vi b(n); for(auto& x: b) cin >> x;
    dbg(n);
    dbg(b);

    slv(n, b);
}




int main() {
    cin.tie(0)->sync_with_stdio(0);

    if(isDebugging && 0) {
        brute(3);
        return 0;
    }

    if(isDebugging && 0) {
        int n; cin >> n;
        vvi re(n, vi(n));
        for(auto& vec: re) for(auto& x: vec) cin >> x;
        auto v = check(re);
        dbg(v);
        assert(v.empty());
        return 0;
    }

    while(isDebugging && 0) {
        RAYA;
        RAYA;
        RAYA;

        int n = st.primes[rng_int(0, 10)];
        vi b(n); for(auto& x: b) x = rng_int(0, n - 1);
        dbg(n);
        dbg(b);

        slv(n, b);
    }

    if(isDebugging) {

    }

    int t = 1;
    //* cin >> t;
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
