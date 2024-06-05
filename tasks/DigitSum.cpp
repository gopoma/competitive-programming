//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debugICPC.h"

#define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define chk(...)
#define RAYA
#endif

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}



// building blocks
using ll  = long long;
using db  = long double; // or double, if TL is tight
using str = string;      // yay python!

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
#define f first
#define s second



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



// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



const int MOD = 1e9+7;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64



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

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
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
//? /Custom Helpers

ll brute(ll L, ll R) {
    auto get = [&](ll x) -> ll {
        str S = ts(x);
        ll sum = 0;
        for(auto& c: S) sum += int(c - '0');

        return sum;
    };

    ll ans = 0;
    for(ll x = L; x <= R; x++) {
        ans += get(x);
    }

    return ans;
}

ll slv(ll L, ll R) {
    chk(L <= R);

    auto get = [&](ll right) -> ll {
        if(right <= 0) return 0;

        const int MAX_DIGITS = sz(ts(right));
        vi digits_right;
        for(auto& c: ts(right)) digits_right.eb(int(c - '0'));

        const int leading_zero = 10;
        ll memo[MAX_DIGITS][11][2][150];
        memset(memo, -1, sizeof(memo));
        function<ll(int, int, int, int)> dp = [&](int idx, int last, int reached_lower, int sum) -> ll {
            if(idx == MAX_DIGITS) {
                return sum;
            }
            if(memo[idx][last][reached_lower][sum] != -1) return memo[idx][last][reached_lower][sum];

            ll ans = 0;
            if(last == leading_zero) {
                ans += dp(idx + 1, leading_zero, false, sum);

                if(0 < idx) {
                    for(int d = 1; d <= 9; d++) {
                        ans += dp(idx + 1, d, true, sum + d);
                    }
                } else {
                    for(int d = 1; d <= digits_right[idx]; d++) {
                        ans += dp(idx + 1, d, d < digits_right[idx], sum + d);
                    }
                }
            } else {
                if(reached_lower) {
                    for(int d = 0; d <= 9; d++) {
                        ans += dp(idx + 1, d, true, sum + d);
                    }
                } else {
                    for(int d = 0; d <= digits_right[idx]; d++) {
                        ans += dp(idx + 1, d, d < digits_right[idx], sum + d);
                    }
                }
            }

            return memo[idx][last][reached_lower][sum] = ans;
        };

        ll ans = dp(0, leading_zero, false, 0);
        return ans;
    };

    ll right = get(R);
    ll left = get(L - 1);
    dbg(right, left);

    return right - left;
}

void solve() {
    //? <>
    ll a, b; cin >> a >> b;
    dbg(a, b);

    ll ans = slv(a, b);
    dbg(ans);
    cout << ans << "\n";
}

// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(0) {
        RAYA;
        ll L = rng_ll(0, ll(1e1));
        ll R = rng_ll(L, ll(1e2));

        dbg(L, R);

        ll ans = brute(L, R);
        ll greedy = slv(L, R);

        dbg(ans);
        dbg(greedy);

        chk(ans == greedy);
    }

    int t = 1;
    cin >> t;

    for(int idx = 0; idx < t; idx++) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
