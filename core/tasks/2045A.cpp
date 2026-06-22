//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

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

int brute(str S) {
    set<char> vowels;
    {
        str t = "AEIOU";
        for(auto& c: t) vowels.emplace(c);
    }
    auto vowel = [&](char c) {
        return vowels.count(c);
    };
    auto cons = [&](char c) {
        return !vowels.count(c);
    };

    vi input;
    {
        int N = 0;
        int G = 0;
        int extra = 0;
        int c = 0;
        int v = 0;
        for(auto& it: S) {
            if(it == 'Y') extra++;
            else if(vowel(it)) v++;
            else {
                if(it == 'N') N++;
                else if(it == 'G') G++;
                else c++;
            }
        }
        dbg(c, v, extra, N, G);
        input = vi{c, v, extra, N, G};
    }
    const int INF = int(1e9);
    vvi combinations{
        //? c - v - extra - N - G
        {2, 1, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 2, 0},
        {0, 1, 0, 2, 1},
        {0, 1, 0, 2, 2},
        {0, 1, 0, 0, 2},
        {0, 0, 3, 0, 0}
    };
    map<int, map<int, map<int, map<int, map<int, bool>>>>> vis;
    map<int, map<int, map<int, map<int, map<int, int>>>>> memo;
    auto dp = [&](const auto& dp, int c, int v, int extra, int N, int G) -> int {
        if(vis[c][v][extra][N][G]) return memo[c][v][extra][N][G];
        vis[c][v][extra][N][G] = true;

        int ans = 0;
        vi data{c, v, extra, N, G};
        for(auto& comb: combinations) {
            if(comb[3] > 0 && comb[4] > 0) {
                if(comb[3] > data[3] || comb[4] > data[4]) {
                    continue;
                }
            }
            int take = 0;
            for(int i = 0; i < 5; i++) {
                if(i == 2) continue;
                int adi = comb[i] - min(comb[i], data[i]);
                take += adi;
            }
            if((data[2] - comb[2] - take) >= 0) {
                vi new_data = data;
                for(int i = 0; i < 5; i++) {
                    if(i == 2) continue;
                    new_data[i] -= comb[i];
                    ckmax(new_data[i], 0);
                }
                new_data[2] -= take;
                new_data[2] -= comb[2];

                ckmax(ans, dp(dp, new_data[0], new_data[1], new_data[2], new_data[3], new_data[4]) + accumulate(all(comb), 0));
            }
        }
        //? dbg(c, v, extra, N, G, ans);
        return memo[c][v][extra][N][G] = ans;
    };
    dbg(input);
    int ans = dp(dp, input[0], input[1], input[2], input[3], input[4]);
    return ans;
}

int slv(str S) {
    //? return brute(S);
    set<char> vowels;
    {
        str t = "AEIOU";
        for(auto& c: t) vowels.emplace(c);
    }
    auto vowel = [&](char c) {
        return vowels.count(c);
    };
    auto cons = [&](char c) {
        return !vowels.count(c);
    };

    int v = 0;
    int c = 0;
    int extra = 0;
    int N = 0;
    int G = 0;

    for(auto& x: S) {
        if(x == 'Y') extra++;
        else if(vowel(x)) v++;
        else if (cons(x)) c++;
        else assert(false);

        if(x == 'N') N++;
        else if(x == 'G') G++;
    }

    int guarda_v = v;
    int guarda_c = c;
    dbg(c, v, extra, N, G);

    int blocks = 0;
    int cused = 0;
    while(true) {
        int usec = min(c, 2);
        int usev = min(v, 1);
        int need = (2 - usec) + (1 - usev);
        if(need <= extra) {
            c -= usec; cused += usec;
            v -= usev;
            extra -= need;
            blocks++;
            continue;
        }
        break;
    }

    //? dbg(blocks, N, G, extra);
    int o = guarda_c - cused; // no usé
    int G_no_usados = min(o, G);
    int G_usados = G - G_no_usados;
    G_no_usados += min(G_usados, extra);
    assert(o >= 0);
    //? dbg(o, blocks, N, G, cused);
    int ans = 3 * blocks + min(G_no_usados, min(cused, N));
    return ans;
}

void solve() {
    //? <>
    str S; cin >> S;
    int ans = slv(S);
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        int n = rng_int(1, 10);
        str S; rep(n) S.pb(rng_int(int('A'), int('Z')));
        dbg(n);
        dbg(S);
        dbg("Brute");
        int ans = brute(S);
        dbg("/Brute");
        dbg("Greedy");
        int greedy = slv(S);
        dbg("/Greedy");
        dbg(ans, greedy);
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
