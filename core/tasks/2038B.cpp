#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//? #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing
#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "helpers/debug.h"
    #define GA dbg(0);
#else
    #define dbg(...)     0
    #define chk(...)     0
    #define GA 0;

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
const int MOD = 998244353;
// const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const ll INF = 1e18;
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
// mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng(0);

//? Generator
int rng_int(int L, int R) {
    assert(L <= R);
    return uniform_int_distribution<int>(L, R)(rng);
} 
ll rng_ll(ll L, ll R) {
    assert(L <= R);
    return uniform_int_distribution<ll>(L, R)(rng);
}
//? /Generator

#define lb lower_bound
#define ub upper_bound
tcT > int lwb(V<T>& a, const T& b) { return int(lb(all(a), b) - bg(a)); }
tcT > int upb(V<T>& a, const T& b) { return int(ub(all(a), b) - bg(a)); }

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

int brute(int n, vi a) {
    map<vi, bool> vis; vis[a] = true;
    map<vi, int> dist; dist[a] = 0;
    deque<vi> q; q.eb(a);
    auto check = [](vi arr) -> bool {
        each(x, arr) if(x < -10) return false;
        return true;
    };
    auto good = [&](vi arr) -> bool {
        bool ok = true;
        int tar = arr.ft;
        for(auto& x: arr) ok &= (x == tar);
        return ok;
    };
    while(!q.empty()) {
        auto current = q.ft; q.pop_front();
        if(good(current)) return dist[current];
        for(int i = 0; i < n; i++) {
            int nxt = (i + 1) % n;
            vi newCurrent = current;
            newCurrent[i] -= 2;
            newCurrent[nxt]++;

            if(check(newCurrent) && !vis[newCurrent]) {
                vis[newCurrent] = true;
                dist[newCurrent] = dist[current] + 1;
                q.eb(newCurrent);
            }
        }
    }
    return -1;
    //? int mn = int(1e9);
    //? for(auto& [vec, d]: dist) {
    //?     if(good(vec)) {
    //?         //? dbg(vec, d);
    //?         ckmin(mn, d);
    //?     }
    //? }
    //? return mn;
}

ll a[int(2e5) + 5];
ll b[int(2e5) + 5];
ll solve(ll n) {
    ll sum = 0;
    for (int i = 0; i < n; ++i) sum += a[i];

    auto check2 = [&](ll down, ll goal) -> pair<ll, bool> {
        for(int i = 0; i < n; i++) b[i] = a[i];
        b[0] -= 2LL * down;
        b[1] += down;
        ll total = down;

        bool allGood = true;
        for (int i = 1; i < n; ++i) {
            ll toUse = 0;
            if (goal <= b[i]) toUse = (b[i] - goal) >> 1LL;
            total += toUse;

            b[i] -= toUse << 1LL;
            if(i + 1 < n) b[i + 1] += toUse;
            else b[0] += toUse;
            //? b[(i + 1) % n] += toUse;

            //? dbg(i, b[i], goal);
            if (b[i] != goal)  allGood = false;
        }
        //? dbg(b[0], goal);
        if (b[0] != goal) allGood = false;

        return {total, allGood};
    };

    auto check = [&](ll value) -> bool {
        ll goal = sum - value * n;
        ll l = 0LL, r = goal;
        while (l < r) {
            ll mid = (l + r) >> 1LL;

            auto [res, good] = check2(mid, value);
            if (res >= goal) {
                r = mid;
            } else {
                l = mid + 1LL;
            }
        }

        //? dbg(l, value);
        auto [res, good] = check2(l, value);
        //? dbg(res, good);
        
        return (good);
    };

    ll l1 = 0LL, r1 = min(ll(1e9), sum);
    while (l1 < r1) {
        ll mid1 = (l1 + r1 + 1LL) / 2LL;

        if (check(mid1)) {
            l1 = mid1;
        } else {
            r1 = mid1 - 1LL;
        }
    }

    //? dbg(l1);
    if (check(l1)) {
        //? dbg(sum - l1 * n);
        // cout << sum - l1 * n << "\n";
        return sum - l1 * ll(n);
    } else {
        //? dbg(-1);
        // cout << -1 << "\n";
        return -1;
    }
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    while(0) {
        RAYA;
        int n = rng_int(int(2e5), int(2e5));
        dbg(n);
        //? vl a(n); 
        for(int i = 0; i < n; i++) a[i] = rng_ll(int(8e8), int(1e9));
        db last = time_elapsed();
        ll ans = solve(n);
        db current = time_elapsed();
        db taken = current - last;
        dbg(taken);
        if(taken > db(2)) {
            chk(false);
        }
    }
    int t = 1; 
    cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        ll n;
        cin >> n;
        //? vl a(n);
        for (int j = 0; j < n; ++j) cin >> a[j];
        cout << solve(n) << "\n";
    }
    RAYA;
    RAYA;


    // while(1) {
    //     GA;
    //     RAYA;
    //     int n = rng_int(2, 4);
    //     vi a(n); for(auto& x: a) x = rng_int(1, 10);
    //     int ans = brute(n, a);
    //     dbg("acabo");
    //     int greedy = solve(n, a);
    //     dbg(ans, greedy);
    //     dbg(n, a);
    //     chk(ans == greedy);
    // }

    #ifndef LOCAL
        cout << endl;
    #endif

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}