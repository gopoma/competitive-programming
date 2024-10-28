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

void solve() {
    ll N, Q; cin >> N >> Q;
    vl salary(N); each(x, salary) cin >> x;
    vl happiness(N);
    rep(Q) {
        int type; cin >> type;
        if(type == 0) {
            ll l, r, c; cin >> l >> r >> c; l--; r--;
            for(int i = l; i <= r; i++) {
                if(salary[i] < c) happiness[i]++;
                else if(salary[i] > c) happiness[i]--;
                salary[i] = c;
            }
        } else if(type == 1) {
            ll l, r, c; cin >> l >> r >> c; l--; r--;
            for(int i = l; i <= r; i++) {
                if(c > 0) happiness[i]++;
                else if(c < 0) happiness[i]--;
                salary[i] += c;
            }
        } else if(type == 2) {
            ll l, r; cin >> l >> r; l--; r--;
            ll sum = 0;
            for(int i = l; i <= r; i++) sum += salary[i];
            ll tot = (r - l + 1);
            if(sum == 0) {
                cout << "0/1\n";
            } else {
                ll g = gcd(sum, tot);
                ll isPositive = (sum > 0);
                sum = abs(sum);
                sum /= g;
                tot /= g;
                if(!isPositive) sum *= -1;
                cout << sum << "/" << tot << "\n";
            }
        } else if(type == 3) {
            ll l, r; cin >> l >> r; l--; r--;
            ll sum = 0;
            for(int i = l; i <= r; i++) sum += happiness[i];
            ll tot = (r - l + 1);
            if(sum == 0) {
                cout << "0/1\n";
            } else {
                ll g = gcd(sum, tot);
                ll isPositive = (sum > 0);
                sum = abs(sum);
                sum /= g;
                tot /= g;
                if(!isPositive) sum *= -1;
                cout << sum << "/" << tot << "\n";
            }
        } else assert(false);
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

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
