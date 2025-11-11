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


void solve() {
    int n, k; cin >> n >> k;
    vl arr(n); each(x, arr) cin >> x;

    dbg(n, k);
    dbg(arr);


    // TODO: Online Median Sliding Window
    multiset<ll> L, R;
    ll sum_L = 0, sum_R = 0;

    auto add_L = [&](ll x) { L.emplace(x); sum_L += x; };
    auto add_R = [&](ll x) { R.emplace(x); sum_R += x; };
    auto del_L = [&](ll x) { safeErase(L, x); sum_L -= x; assert(sum_L >= 0); };
    auto del_R = [&](ll x) { safeErase(R, x); sum_R -= x; assert(sum_R >= 0); };

    auto fix = [&]() {
        if(sz(L) > sz(R) + 1) {
            assert(sz(L) == sz(R) + 2);

            //? should delete MAX element of L
            ll tar = *L.rbegin();

            //? safeErase(L, tar);
            //? R.emplace(tar);

            del_L(tar);
            add_R(tar);

            assert(sz(L) == sz(R));
        } else if(sz(L) < sz(R)) {
            assert(sz(R) == sz(L) + 1);

            //? should delete MIN element of R

            ll tar = *R.begin();

            //? safeErase(R, tar);
            //? L.emplace(tar);

            del_R(tar);
            add_L(tar);
        }

        assert(sz(L) == sz(R) || sz(L) == sz(R) + 1);
    };

    auto add = [&](ll x) {
        assert(sz(L) >= sz(R));

        if(L.empty()) {
            //? L.emplace(x);
            add_L(x);
        } else {
            assert(!L.empty());

            if((*L.rbegin()) <= x) {
                //? R.emplace(x);
                add_R(x);
            } else {
                //? L.emplace(x);
                add_L(x);
            }

            fix();
        }
    };

    auto del = [&](ll x) {
        assert(!L.empty());

        if(R.find(x) != R.end()) {
            //? safeErase(R, x);
            del_R(x);
        } else {
            assert(L.find(x) != L.end());
            //? safeErase(L, x);
            del_L(x);
        }

        fix();
    };

    auto get_median = [&]() {
        RAYA;
        dbg(L, R);
        return (*L.rbegin());
    };

    auto calc = [&]() {
        assert(!L.empty());

        ll mid = get_median();

        ll wL = sz(L);
        ll wR = sz(R);

        ll sL = sum_L;
        ll sR = sum_R;

        ll partial1 = wL * mid - sL;
        ll partial2 = sR - wR * mid;

        ll ans = partial1 + partial2;
        return ans;
    };



    for(int i = 0; i < k; i++) add(arr[i]);
    vl ans; ans.eb(calc()); dbg(get_median());

    for(int i = k; i < n; i++) {
        del(arr[i - k]);
        add(arr[i]);

        dbg(get_median());

        ans.eb(calc());
    }

    dbg(ans);

    {
        const int m = sz(ans);
        for(int i = 0; i < m; i++) {
            cout << ans[i] << " \n"[i == m - 1];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    //? cin >> t;

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
