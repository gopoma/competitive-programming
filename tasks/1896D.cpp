//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//? #undef _GLIBCXX_DEBUG //? for Stress Testing

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
/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */

tcT> struct BIT {
	int N; V<T> data;
	void init(int _N) { N = _N; data.rsz(N); }
	void add(int p, T x) { for (++p;p<=N;p+=p&-p) data[p-1] += x; }
	T sum(int l, int r) { return sum(r+1)-sum(l); }
	T sum(int r) { T s = 0; for(;r;r-=r&-r)s+=data[r-1]; return s; }
	int lower_bound(T sum) {
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1<<25; pw; pw >>= 1) {
			int npos = pos+pw;
			if (npos <= N && data[npos-1] < sum)
				pos = npos, sum -= data[pos-1];
		}
		return pos;
	}
};
//? /Template

set<ll> get(vl A) {
    const int N = sz(A);
    set<ll> S;
    for(int i = 0; i < N; i++) {
        for(int j = i; j < N; j++) {
            ll sum = 0;
            for(int k = i; k <= j; k++) {
                sum += A[k];
            }
            S.emplace(sum);
        }
    }
    return S;
}

using Query = tuple<ll, ll, ll>;

vb brute(ll n, ll q, vl a, V<Query> queries) {
    vb response;
    for(auto& it: queries) {
        auto op = get<0>(it);
        if(op == 1) {
            auto [_, S, __] = it;

            auto temp = get(a);
            response.eb(temp.count(S));
        } else {
            assert(op == 2);
            auto [_, i, v] = it; i--;

            a[i] = v;
        }
    }
    return response;
}

vb slv(ll n, ll q, vl a, V<Query> queries) {
    BIT<ll> st; st.init(n);
    set<ll> owhere;
    ll sum = 0;
    auto del = [&](ll i, ll x) -> void {
        if(a[i] == 1) {
            chk(owhere.count(i));
            safeErase(owhere, i);
        }
        sum -= a[i];
        st.add(i, -st.sum(i, i));
    };

    auto add = [&](ll i, ll x) -> void {
        if(x == 1) {
            chk(!owhere.count(i));
            owhere.emplace(i);
        }
        a[i] = x;
        sum += x;
        st.add(i, x);
    };

    auto upd = [&](ll i, ll x) -> void {
        del(i, x);
        add(i, x);
    };

    auto ddd = [&]() {
        //? vl xd; for(int i = 0; i < n; i++) {
        //?     xd.eb(st.sum(i, i));
        //? }
        //? dbg(xd);
    };

    auto query = [&](ll S) -> bool {
        dbg(sum);
        if(a.ft == 1 || a.bk == 1) {
            return (1 <= S && S <= sum);
        }
        if(owhere.empty()) {
            return (1 <= S && S <= sum && S % 2LL == 0LL);
        }
        dbg("._.xd");
        ll could = max(st.sum(0, *owhere.rbegin()), st.sum(*owhere.begin(), n - 1));
        ll take = fdiv(sum - could, 2LL);
        dbg(could, take, S);
        if(1LL <= S && S <= could) return true;
        return ((S % 2LL == could % 2LL) && (could <= S && S <= could + 2LL * take));
    };

    for(int i = 0; i < n; i++) {
        add(i, a[i]);
    }

    vb response;
    for(auto& it: queries) {
        auto op = get<0>(it);
        if(op == 1) {
            auto [_, S, __] = it;

            bool ok = query(S);
            response.eb(ok);
        } else {
            assert(op == 2);
            auto [_, i, v] = it; i--;

            upd(i, v);
        }
    }
    return response;
}

void solve() {
    //? <>
    ll n, q; cin >> n >> q;
    vl a(n); for(auto& x: a) cin >> x;
    dbg(n, q);
    dbg(a);

    V<Query> queries;
    rep(q) {
        ll op; cin >> op;
        if(op == 1) {
            ll S; cin >> S;
            queries.eb(op, S, -BIG);
        } else {
            ll i, v; cin >> i >> v;
            queries.eb(op, i, v);
        }
    }

    vb response = slv(n, q, a, queries);
    for(int i = 0; i < sz(response); i++) {
        cout << (response[i]?"YES":"NO") << "\n";
    }
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    {
        vl A{2, 1, 2, 1, 2, 2, 2};
        set<ll> S = get(A);
        //? dbg(A);
        //? dbg(S);
    }
    while(0) {
        RAYA;
        ll n = rng_ll(1, 100);
        vl a(n); for(auto& x: a) x = rng_ll(1, 2);
        dbg(n);
        dbg(a);
        a.ft = a.bk = 1;
        if(rng_ll(0, 1)) a.ft = 2;
        if(n == 1) continue;
        set<ll> S = get(a);
        ll sum = accumulate(all(a), 0LL);
        bool ok = true;
        for(ll x = 1; x <= sum; x++) ok &= (S.count(x));
        chk(ok);
    }

    while(0) {
        RAYA;
        ll n = rng_ll(1, 10);
        vl a(n); for(auto& x: a) x = rng_ll(1, 2);

        a.ft = a.bk = 2;

        set<ll> special; for(auto& x: a) special.emplace(x);
        if(sz(special) == 1 && ((*special.begin()) == 2)) continue;

        dbg(n);
        dbg(a);

        vl pref = a;
        for(int i = 1; i < n; i++) pref[i] += pref[i - 1];
        auto query = [&](int L, int R) -> ll {
            ll sum = pref[R];
            if(0 <= L - 1) sum -= pref[L - 1];
            return sum;
        };
        V<set<ll>> where(3);
        for(int i = 0; i < n; i++) {
            where[a[i]].emplace(i);
        }
        ll sum = query(*where[1].begin(), n - 1);
        ll sum2 = query(0, *where[1].rbegin());
        set<ll> good;
        ll mx = max(sum, sum2);
        for(ll x = 1; x <= mx; x++) good.emplace(x);
        ll queda = accumulate(all(a), 0LL) - mx;
        for(ll x = 0; x <= queda / 2LL; x++) good.emplace(mx + 2LL * x);
        chk(good == get(a));
    }

    //? Stress Testing
    while(0) {
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        ll n = rng_ll(1, 100);
        vl a(n); for(auto& x: a) x = rng_ll(1, 2);
        ll q = rng_ll(1, 100);
        V<Query> queries;
        rep(q) {
            if(rng_ll(1, 2) == 1) {
                queries.eb(1, rng_ll(1, 2LL * n), -BIG);
            } else {
                queries.eb(2, rng_ll(1, n), rng_ll(1, 2));
            }
        }
        dbg(n, q);
        dbg(a);
        dbg(queries);
        vb ans = brute(n, q, a, queries);
        vb greedy = slv(n, q, a, queries);
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    int t = 1; cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        RAYA;
        RAYA;
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
