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
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? /Template



void solve() {
    //? <>
//?    for(ll x = 0; x <= 30; x++) {
//?        bool ok = false;
//?        for(ll a = 0; a * a <= 2000; a++) {
//?            for(ll b = 0; b * b <= 2000; b++) {
//?                ok |= (a * a - b * b == x);
//?            }
//?        }
//?        if(!ok) dbg(x);
//?    }

    auto tokenize = [&](str S) -> vl {
        vl tokens;
        deque<char> current;
        auto norm = [&]() {
            while(!current.empty() && current.ft == ' ') current.pop_front();
            while(!current.empty() && current.bk == ' ') current.pop_back();
        };
        auto add = [&]() {
            norm();
            if(current.empty()) return;
            str partial;
            each(c, current) partial.pb(c);
            tokens.eb(stoll(partial));
            current.clear();
        };
        each(c, S) {
            if(c == ' ') {
                add();
            } else {
                current.pb(c);
            }
        }
        add();
        return tokens;
    };

    str S;
    vvl input;
    while(getline(cin, S)) {
        input.eb(tokenize(S));
    }
    each(x, input) {
        RAYA;
        dbg(x);
        if(sz(x) == 1) {
            dbg("1st");
            ll N = x.ft;
            bool neg = N < 0;
            N = abs(N);
            bool found = false;
            for(ll d = 1LL; d * d <= N; d++) {
                if(N % d == 0) {
                    ll d2 = fdiv(N, d);
                    ll xx = d;
                    ll yy = d2;
                    //? a + b = d
                    //? a - b = d2
                    //? 2 * a = d + d2
                    //? a = (d + d2) / 2
                    //? b = d - a
                    if((xx + yy) % 2LL == 0LL) {
                        ll a = (xx + yy) / 2LL;
                        ll b = xx - a;
                        if(0 <= a && 0 <= b) {
                            found = true;
                            if(neg) {
                                cout << b << " " << a << "\n";
                            } else {
                                cout << a << " " << b << "\n";
                            }
                            break;
                        }  
                    }
                    if((yy + xx) % 2LL == 0LL) {
                        ll a = (yy + xx) / 2LL;
                        ll b = yy - a;
                        if(0 <= a && 0 <= b) {
                            found = true;
                            if(neg) {
                                cout << b << " " << a << "\n";
                            } else {
                                cout << a << " " << b << "\n";
                            }
                            break;
                        }  
                    }
                }
            }
            if(!found) {
                if(N & 1LL) cout << "Spinster Number.\n";
                else cout << "Bachelor Number.\n"; 
            }
        } else {
            dbg("2nd");
            auto n1 = x.ft;
            auto n2 = x.bk;
            ll L = cdiv(n1 - 2LL, 4LL);
            ll R = fdiv(n2 - 2LL, 4LL);
            if(L > R) cout << "0\n";
            else cout << (R - L + 1LL) << "\n";
        }
    }
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
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
