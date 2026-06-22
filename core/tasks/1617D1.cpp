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
mt19937 rng(0);

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? /Template

const ll MORE_IMPOSTORS = 0;
const ll MORE_CREWMATES = 1;

void slv(ll n, bool ddd, vb isImpostor) {
    set<ll> Impostors;
    for(int i = 0; i < sz(isImpostor); i++) if(isImpostor[i]) Impostors.emplace(i + 1);

    ll tot = 0;
    auto query = [&](ll a, ll b, ll c) -> ll {
        tot++;
        if(ddd) {
            set<ll> u;
            u.emplace(a);
            u.emplace(b);
            u.emplace(c);
            chk(sz(u) == 3);

            ll cntI = ll(Impostors.count(a)) + ll(Impostors.count(b)) + ll(Impostors.count(c));
            if(cntI >= 2) return MORE_IMPOSTORS;
            else return MORE_CREWMATES;
        } else {
            cout << "? " << a << " " << b << " " << c << endl;
            ll ans; cin >> ans;
            if(ans == -1) assert(false);
            chk(ans == MORE_IMPOSTORS || ans == MORE_CREWMATES);
            return ans;
        }
    };

    vl mimp;
    vl mcrew;
    for(int i = 1; i <= n; i += 3) {
        ll ans = query(i, i + 1, i + 2);
        if(ans == MORE_IMPOSTORS) mimp.eb(i);
        else mcrew.eb(i);
    }
    assert(!mimp.empty() && !mcrew.empty());

    ll base  = -1;
    ll base2 = -1;

    set<ll> already;
    vl impostors, crewmates;
    {
        ll i = mimp.ft;
        ll j = mcrew.ft;
        dbg(i, j);
        bool go = false;
        {
            set<ll> S;
            for(int delta = 0; delta < 3; delta++) {
                S.emplace(query(i, i + 1, j + delta));
            }
            if(sz(S) == 2) {
                base = i;
                base2 = i + 1;
                go = false;
            } else if((*S.begin()) == MORE_IMPOSTORS) {
                base = i;
                already.emplace(i);
                already.emplace(i + 1);
                impostors.eb(i);
                impostors.eb(i + 1);
                go = true;
            } else {
                base = i;
                base2 = i + 1;
            }
        }
        if(go) {
            set<ll> S;
            for(int delta = 0; delta < 3; delta++) {
                S.emplace(query(j, j + 1, i + delta));
            }
            if(sz(S) == 2) {
                base = j;
                base2 = j + 1;
            } else if((*S.begin()) == MORE_CREWMATES) {
                base2 = j;
                already.emplace(j);
                already.emplace(j + 1);
                crewmates.eb(j);
                crewmates.eb(j + 1);
            } else {
                base = j;
                base2 = j + 1;
            }
        }
    }

    dbg(base, base2);
    dbg(impostors, crewmates);
    dbg("ga");

    for(ll x = 1; x <= n; x++) {
        if(already.count(x)) continue;
        if(x == base || x == base2) continue;
        ll ans = query(base, base2, x);
        already.emplace(x);
        if(ans == MORE_IMPOSTORS) impostors.eb(x);
        else crewmates.eb(x);
    }

    dbg(impostors, crewmates);

    for(ll x = 1; x <= n; x++) {
        if(already.count(x)) continue;
        if(x != base && x != base2) continue;
        ll ans = query(impostors.ft, crewmates.ft, x);
        if(ans == MORE_IMPOSTORS) impostors.eb(x);
        else crewmates.eb(x);
    }

    dbg(tot, 2 * n);
    chk(tot <= 2 * n);

    // sor(impostors);
    // dbg(impostors);
    // dbg(Impostors);

    if(ddd) {
        dbg(sz(Impostors));
        set<ll> oo; for(auto& x: impostors) oo.emplace(x);
        chk(sz(impostors) == sz(Impostors));
        chk(oo == Impostors);
    }

    cout << "! " << sz(impostors) << " ";
    for(auto& x: impostors) cout << x << " ";
    cout << endl;
}

void solve() {
    //? <>
    ll n; cin >> n;
    slv(n, false, vb());
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        ll n = rng_ll(2, 1000);
        n = 3 * n;
        ll k = rng_ll(n/3 + 1, (2*n)/3 - 1);
        vl p(n); for(int i = 0; i < k; i++) p[i] = 1;
        shuf(p);
        vb isImpostor(n);
        for(int i = 0; i < n; i++) if(p[i]) isImpostor[i] = true;

        dbg(n, k);
        dbg(p);
        dbg(isImpostor);
        slv(n, true, isImpostor);
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
