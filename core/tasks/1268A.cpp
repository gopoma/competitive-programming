//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

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
#define f  first
#define s  second



#define tcT template <class T
#define tcTU tcT, class U

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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



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



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



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

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
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

//? __builtin_popcountll
ll GetBit(ll mask, ll bit) { return (mask >> bit) & 1LL; }
void TurnOn(ll& mask, ll bit) { mask = mask | (1LL << bit); }
void TurnOff(ll& mask, ll bit) { mask = mask & (~(1LL << bit)); }

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0);

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? /Template

str brute(str N, ll K) {
    auto check = [&](ll X) -> bool {
        str XX = ts(X);
        for(ll i = 0; i < K; i++) {
            set<char> U;
            ll j = i;
            while(j < sz(XX)) {
                U.emplace(XX[j]);
                j += K;
            }
            if(sz(U) > 1) return false;
        }
        return true;
    };
    ll X = stoll(N);
    while(!check(X)) { X++; }
    return ts(X);
}

str slv(str N, ll K) {
    const ll n = sz(N);
    auto komp = [&](str& S, str& T) -> bool {
        chk(n == sz(S) && sz(S) == sz(T));
        for(int i = 0; i < n; i++) {
            if(S[i] == T[i]) continue;
            return (S[i] > T[i]);
        }
        return true;
    };
    str response;
    auto check = [&](int middle) -> bool {
        str S = str(n, '$');
        auto apply = [&](int i, char c) -> void {
            int j = i;
            while(j < n) {
                S[j] = c;
                j += K;
            }
        };
        for(int i = 0; i < middle; i++) {
            apply(i, N[i]);
        }
        for(int i = middle; i < K; i++) {
            if(N[i] == '9') apply(i, N[i]);
            else {
                apply(i, N[i] + 1);
                for(int j = i + 1; j < K; j++) apply(j, '0');
                break;
            }
        }
        dbg(S, middle, komp(S, N));
        if(komp(S, N)) {
            response = S;
            return true;
        }
        return false;
    };
    int left = -1; //? always good
    int right = K + 1; //? always bad
    while(left + 1 < right) {
        int middle = (left + right) >> 1;
        if(check(middle)) left = middle;
        else right = middle;
    }
    return response;
}

void solve() {
    //? <>
    ll n, K; cin >> n >> K;
    str N; cin >> N;
    dbg(n, K);
    dbg(N);
    str response = slv(N, K);
    dbg(response);
    cout << sz(response) << "\n";
    cout << response << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        ll n = rng_ll(2, 7);
        ll K = rng_ll(1, n - 1);
        str N;
        N.pb(char('1'+rng_int(0, 8)));
        rep(n - 1) {
            N.pb(char('0'+rng_int(0, 9)));
        }
        dbg(n, K);
        dbg(N);
        dbg("Brute");
        str ans = brute(N, K);
        dbg("/Brute");
        dbg("Greedy");
        str greedy = slv(N, K);
        dbg("/Greedy");

        dbg(ans);
        dbg(greedy);
        chk(ans == greedy);
    }

    int t = 1; //! cin >> t;
    for(int i = 0; i < t; i++) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
