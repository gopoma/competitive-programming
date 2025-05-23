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



//? Template
const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



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
//? /Template
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}

void brute(ll n, ll k) {
    vl a(n); iota(all(a), 1);
    vl can;
    for(int mask = 0; mask < (1 << n); mask++) {
        vl C;
        for(int i = 0; i < n; i++) {
            if(mask & (1 << i)) C.eb(1);
            else C.eb(0);
        }

        vvl partitions;
        vl current_arr{a.ft};
        ll current = C.ft;
        for(int i = 1; i < n; i++) {
            if(C[i] == current) {
                current_arr.eb(a[i]);
            } else {
                partitions.eb(current_arr);
                current = C[i];
                current_arr.clear();
                current_arr.eb(a[i]);
            }
        }
        partitions.eb(current_arr);
        bool ok = sz(partitions) & 1;
        each(x, partitions) ok &= (sz(x) & 1);
        if(!ok) continue;
        
        vl xd;
        each(x, partitions) {
            sor(x);
            xd.eb(x[sz(x) / 2]);
        }
        sor(xd);
        dbg(partitions, xd[sz(xd) / 2]);
        can.eb(xd[sz(xd) / 2]);
    }
    remDup(can);
    dbg(can);
}

void solve() {
    ll n, k; cin >> n >> k;
    dbg(n, k);
    if(n == 1) {
        if(k == 1) {
            cout << "1\n";
            cout << "1\n";
        } else cout << "-1\n";
    } else if(n == 3) {
        if(k == 2) {
            cout << "3\n";
            cout << "1 2 3\n";
        } else cout << "-1\n";
    } else {
        if(2 <= k && k <= (n - 1)) {
            ll L = 1;
            ll cL = k - 1;
            ll cR = k + 1;
            ll R = n;
            
            ll sL = (cL - L + 1);
            ll sR = (R - cR + 1);
            if((sL % 2 == 1) && (sR % 2 == 1)) {
                cout << "3\n";
                cout << 1 << " " << k << " " << (k + 1) << "\n";
            } else {
                cout << "5\n";
                cout << 1 << " " << (k - 1) << " " << k << " " << (k + 1) << " " << (k + 2) << "\n";
            }
        } else cout << "-1\n";
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int t = 1; cin >> t;
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
