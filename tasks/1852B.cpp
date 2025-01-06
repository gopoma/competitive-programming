//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
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


vl slv(ll n, vl a) {
    vl ans(n);
    for(int i = 0; i < n; i++) if(a[i] == 0) ans[i] = -n;

    map<ll, vl> b;
    vl u;
    for(int i = 0; i < n; i++) if(a[i] != 0) {
        b[a[i]].eb(i);
        u.eb(a[i]);
    }
    remDup(u);

    ll m = sz(u);

    ll L = -m;
    ll R = +m;
    if(abs(L) == abs(R)) L++;

    int i = 0;
    int j = sz(u) - 1;
    // dbg(L, R, i, j);
    bool turn = true;
    while(i <= j) {
        // dbg(i, j);
        if(turn) {
            for(auto& k: b[u[j]]) {
                ans[k] = R;
            }
            R -= 2;
            if(R == 0) R--;
            j--;
        } else {
            for(auto& k: b[u[i]]) {
                ans[k] = L;
            }
            L += 2;
            if(L == 0) L++;
            i++;
        }
        turn = !turn;
    }


    vl c = ans; sor(c);
    // dbg(ans, c);
    vl temp(n);

    for(int i = 0; i < n; i++) {
        // c[i] + c[j] > 0
        // c[j] > -c[i]
        temp[i] = upper_bound(all(c), BIG) - lower_bound(all(c), -c[i] + 1);
    }
    sor(temp);
    sor(a);
    if(temp != a) ans = vl();

    return ans;
}

void brute(ll n) {
    auto check = [&](vl& a) -> bool {
        chk(sz(a) == n);
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(a[i] + a[j] == 0) return false;
        return true;
    };

    auto get = [&](vl arr) -> vl {
        if(sz(arr) < n) return vl();
        vl a(n);
        for(int i = 0; i< n; i++) {
            ll count = 0;
            for(int j = 0; j < n; j++) {
                count += (arr[i] + arr[j] > 0);
            }
            a[i] = count;
        }
        return a;
    };

    set<vl> possible;

    vl arr;
    // map<vl, vl> constructive;
    map<vl, vvl> constructive;
    auto backtrack = [&](const auto& backtrack) -> void {
        if(sz(arr) == n) {
            if(!check(arr)) return;

            vl a = get(arr);

            if(is_sorted(all(a)) && is_sorted(all(arr))) {
                possible.emplace(a);
                // constructive[a] = arr;
                constructive[a].eb(arr);
            }

            return;
        }
        for(int x = -n; x <= +n; x++) {
            arr.eb(x);
            backtrack(backtrack);
            arr.pop_back();
        }
    }; backtrack(backtrack);

    // for(auto& x: possible) dbg(x, constructive[x]);
    // dbg(sz(possible));

    vl a;
    auto dfs = [&](const auto& dfs) -> void {
        if(sz(a) == n) {
            vl temp = a; sor(temp);
            vl temp2 = get(slv(n, a));
            if(possible.count(temp)) {
                sor(temp2);
                if(temp != temp2) {
                    dbg("should");
                    dbg(a, temp2);
                    chk(false);
                }
            } else {
                if(!temp2.empty()) {
                    dbg("shouldn't");
                    dbg(a, temp2);
                    chk(false);
                }
            }
            return;
        }
        for(int x = 1; x <= n; x++) {
            a.eb(x);
            dfs(dfs);
            a.pop_back();
        }
    }; dfs(dfs);
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    dbg(n);
    dbg(a);
    vl ans = slv(n, a);
    if(ans.empty()) cout << "NO\n";
    else {
        cout << "YES\n";
        for(auto& x: ans) cout << x << " ";
        cout << "\n";
    }
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    for(int n = 1; n <= 7; n++) {
        RAYA;
        dbg(n);
        // brute(n);
    }

    //? Stress Testing
    while(0) {
        RAYA;
    }

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
