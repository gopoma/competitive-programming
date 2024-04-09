//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

#ifdef LOCAL
    #include "helpers/debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif

// building blocks
using ll  = long long;
using db  = long double; // or double, if TL is tight
using str = string;      // yay python!

//? priority_queue for minimum
//? template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

//? using ull  = unsigned long long;
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
//! ^ lol this makes everything look weird but I'll try it

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
tcT > int lwb(V<T> &a, const T &b) { return int(lb(all(a), b) - bg(a)); }
tcT > int upb(V<T> &a, const T &b) { return int(ub(all(a), b) - bg(a)); }



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0);



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



#define tcTUU tcT, class ...U

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

inline namespace FileIO {
void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void setIO(str s = "") {
	cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
	//? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);
	cin.exceptions(cin.failbit);
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) setIn(s + ".in"), setOut(s + ".out");  // for old USACO
}
}  // namespace FileIO



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

//? /Custom Helpers



//* Template
//* /Template

const int INF = int(1e9);
int dp[905][8105];

void precompute() {
    for(int sum = 0; sum <= 900; sum++) {
        for(int sqr_sum = 0; sqr_sum <= 8100; sqr_sum++) {
            //? current -> dp[sum][sqr_sum]
            if(sum == 0 && sqr_sum == 0) dp[sum][sqr_sum] = 0;
            else if(sum < 0 || sqr_sum < 0) dp[sum][sqr_sum] = INF;
            else {
                dp[sum][sqr_sum] = INF;
                for(int x = 9; x >= 1; x--) {
                    if((sum - x >= 0) && (sqr_sum - x * x >= 0)) {
                        ckmin(dp[sum][sqr_sum], dp[sum - x][sqr_sum - x * x] + 1);
                    }
                }
            }
        }
    }

//?    dbg(dp[9][81]);
//?    dbg(dp[12][9]);
//?    dbg(dp[6][10]);
//?    dbg(dp[7][9]);
//?    dbg(dp[111][111]);
}

int get(int xx, int yy) {
    vector<vb> vis(905, vb(8105));
    vector<vi> memo(905, vi(8105));

    function<int(int, int)> solve = [&](int sum, int sqr_sum) {
        if(sum == 0 && sqr_sum == 0) return 0;
        if(sum < 0 || sqr_sum < 0) return INF;

        if(vis[sum][sqr_sum]) return memo[sum][sqr_sum];
        vis[sum][sqr_sum] = true;

        int ans = INF;
        for(int x = 9; x >= 1; x--) {
            ckmin(ans, solve(sum - x, sqr_sum - x * x) + 1);
        }
        return memo[sum][sqr_sum] = ans;
    };

//?    dbg(dp(9, 81));
//?    dbg(dp(12, 9));
//?    dbg(dp(6, 10));
//?    dbg(dp(7, 9));
//?    dbg(dp(111, 111));

    return solve(xx, yy);
}

str build(int sum, int sqr_sum) {
    if(sum > 900 || sqr_sum > 8100) return "No solution";

    int ans = dp[sum][sqr_sum];

    if(ans > 100) return "No solution";
    else {
        str result;

        int current_sum = sum;
        int current_sqr_sum = sqr_sum;
        rep(ans) {
            if(current_sum == 0 && current_sqr_sum == 0) break;

            bool ok = false;
            for(int x = 1; x < 10; x++) {
                if((current_sum - x < 0) || (current_sqr_sum - x * x) < 0) continue;

                if(dp[current_sum][current_sqr_sum] == dp[current_sum - x][current_sqr_sum - x * x] + 1) {
                    current_sum -= x;
                    current_sqr_sum -= x * x;

                    result.pb(ts(x).ft);
                    ok = true;
                    break;
                }
            }
            assert(ok);
        }

        return result;
    }

//?    dbg(build(9, 81));
//?    dbg(build(12, 9));
//?    dbg(build(6, 10));
//?    dbg(build(7, 9));
//?    dbg(build(111, 111));
};

str solve(int sum, int sqr_sum) {
    //? <>

    return build(sum, sqr_sum);
}

void solve2() {
    //? <>
    vi alphabet;
    for(int x = 1; x <= 9; x++) alphabet.eb(x);

    const int lim = 3;
    vector<tuple<int, int, vi, vi>> values;
    function<void(int, vi, vi, int)> backtrack = [&](int n, vi for_sum, vi for_sqr_sum, int last) {
        if(n == lim) {
            sor(for_sum);
            sor(for_sqr_sum);

            chk(sz(for_sum) == lim);
            chk(sz(for_sqr_sum) == lim);

            int sum = accumulate(all(for_sum), 0);
            int sqr_sum = accumulate(all(for_sqr_sum), 0);

            values.eb(sum, sqr_sum, for_sum, for_sqr_sum);

            return;
        }

        each(x, alphabet) {
            if(x <= last) {
                vi new_for_sum = for_sum; new_for_sum.eb(x);
                vi new_for_sqr_sum = for_sqr_sum; new_for_sqr_sum.eb(x * x);

                backtrack(n + 1, new_for_sum, new_for_sqr_sum, x);
            }
        }
    }; backtrack(0, vi(), vi(), INF);

    sor(values);

    set<pi> xd;
    each(val, values) {
        auto [S, sqr_S, arr_S, sqr_arr_S] = val;
        dbg(S, arr_S, sqr_S, sqr_arr_S);

        xd.emplace(S, sqr_S);
    }

    dbg(sz(values));
    dbg(sz(xd));
}

str brute(int sum, int sqr_sum) {
    //? <>
    int need = get(sum, sqr_sum);
    dbg(need);
    const int lim = need;

    str mn = "No solution";
    if(need > 100) return mn;
    function<void(int, str)> backtrack = [&](int n, str current) {
        if(n == lim) {
            int S = 0, SS = 0;
            each(val, current) {
                int d = val - '0';
                S += d;
                SS += d * d;
            }

            if(S == sum && SS == sqr_sum) {
                ckmin(mn, current);
                return;
            }
            return;
        }

        for(int x = 1; x < 10; x++) {
            str new_current = current;
            new_current.pb(ts(x).ft);

            backtrack(n + 1, new_current);
        }
    }; backtrack(0, "");

    return mn;
};

//? Generator
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator


signed main() {
    setIO();

    precompute();

    while(false) {
        RAYA;
        int sum = rng_int(1, 10);
        int sqr_sum = rng_int(1, sum * sum);

        str ans = brute(sum, sqr_sum);
        str greedy = solve(sum, sqr_sum);

        dbg(sum, sqr_sum);
        dbg(ans, greedy);

        if(ans != greedy) dbg("jaaa");
        chk(ans == greedy);
    }

    ll t = 1;
    cin >> t;

    FOR(i, 1, t + 1) {
        RAYA;
        RAYA;

        int sum, sqr_sum; cin >> sum >> sqr_sum;

        str ans = solve(sum, sqr_sum);
        dbg(ans);
        dbg(sz(ans));
        cout << ans << "\n";
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
