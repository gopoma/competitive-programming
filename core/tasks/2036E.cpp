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



const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



//? Template
//? /Template

void solve() {
    ll n, k, q; cin >> n >> k >> q;
    vvl a(n, vl(k));
    for(int i = 0; i < n; i++) for(int j = 0; j < k; j++) cin >> a[i][j];
    dbg(n, k, q);
    dbg("a");
    each(x, a) dbg(x);
    vvl b = a;
    for(int i = 0; i < n; i++) for(int j = 0; j < k; j++) {
        if(0 <= i - 1) {
            b[i][j] |= b[i - 1][j];
        }
    }
    RAYA;
    dbg("b");
    each(x, b) dbg(x);

    vvl C;
    for(int j = 0; j < k; j++) {
        vl current_line;
        for(int i = 0; i < n; i++) {
            current_line.eb(b[i][j]);
        }
        C.eb(current_line);
    }
    RAYA;
    dbg("C");
    each(x, C) dbg(x);
    RAYA;
    RAYA;
    RAYA;
    RAYA;
    
    auto check = [&](int i) -> bool {
        return (0 <= i && i < n);
    };

    auto get = [&](int L, int R, int l, int r) -> pair<bool, pair<ll, ll>> {
        chk(L <= R);
        chk(l <= r);
        if(L > l) {
            swap(L, l);
            swap(R, r);
        } 
        if(R < l) {
            return mp(false, mp(-1, -1));
        } else {
            return mp(true, mp(l, R));
        }
    };

    rep(q) {
        RAYA;
        int m; cin >> m;
        dbg(m);

        ll L = -25;
        ll R = n + 25;
        bool ok = true;

        rep(m) {
            ll r;
            char o;
            ll c;
            cin >> r >> o >> c;
            r--;
            dbg(r, o, c);


            if(o == '<') {
                if(C[r].ft >= c) ok = false;
                else {
                    int left = 0;
                    int right = upper_bound(all(C[r]), c - 1) - C[r].begin();
                    right--;
                    chk(check(left));
                    chk(check(right));
                    dbg("current", left, right);
                    
                    auto [isGood, it2] = get(L, R, left, right);
                    auto [newL, newR] = it2;
                    L = newL;
                    R = newR;
                    ok &= isGood;
                }
            } else {
                chk(o == '>');
                if(C[r].bk <= c) ok = false;
                else {
                    int left = lower_bound(all(C[r]), c + 1) - C[r].begin();
                    int right = n - 1;
                    chk(check(left));
                    chk(check(right));
                    dbg("current", left, right);

                    auto [isGood, it2] = get(L, R, left, right);
                    auto [newL, newR] = it2;
                    L = newL;
                    R = newR;
                    ok &= isGood;
                }
            }
            dbg("partial", ok, L, R);
        }

        dbg(ok, L, R);
        if(!ok) {
            cout << "-1\n";
        } else {
            assert(check(L));
            dbg("ans", L, L + 1);
            cout << (L + 1) << "\n";
        }
    }
}



void setIn(str s) { freopen(s.c_str(), "r", stdin); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
    }

    int t = 1; //? cin >> t;
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
