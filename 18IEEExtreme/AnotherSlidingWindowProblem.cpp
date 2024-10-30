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
mt19937 rng(0);



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

//? Generator
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator

//? /Template

ll mCBrute(deque<ll>& arr) {
    const ll N = sz(arr);
    vl p(N); iota(all(p), 0);
    ll ans = BIG;
    do {
        vl current;
        for(int i = 0; i < N; i++) current.eb(arr[p[i]]);

        vl sums;
        while(sz(current) >= 2) {
            sums.eb(current[sz(current) - 1] + current[sz(current) - 2]);
            current.pop_back();
            current.pop_back();
        }
        if(!current.empty()) {
            chk(sz(current) == 1);
            sums.eb(current.ft);
        }
        chk(!sums.empty());
        ckmin(ans, *max_element(all(sums)));
    } while(next_permutation(all(p)));
    return ans;
}

ll mCGreedy(deque<ll>& a) {
    auto check = [&](ll value) {
        multiset<ll> mst;
        for (auto e : a) mst.insert(e);

        if (sz(mst) & 1) {
            auto it = prev(mst.end());
            ll maxi = *it;
            mst.erase(it);

            if (maxi > value) return false;
        }

        while (!mst.empty()) {
            auto it = prev(mst.end());
            ll maxi = *it;
            mst.erase(it);

            if (!mst.empty()) {
                ll maxa = value - maxi;

                auto it2 = mst.upper_bound(maxa);
                
                if (it2 == mst.begin()) {
                    return false;
                } else {
                    it2--;
                    mst.erase(it2);
                }
            }
        }

        return true;
    };

    ll l = 0, r = BIG;
    while (l < r) {
        ll mid = (l + r) / 2;

        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    
    return l;
}

vpi brute(ll N, vl A) {
    vpi ans;
    deque<ll> window;
    for(int L = 0; L < N; L++) {
        vl values;
        for(int R = L; R < N; R++) {
            window.eb(A[R]);
            //? for(ll i = L; i <= R; i++) {
            //?     window.eb(A[i]);
            //? }
            //? mCBrute(window);
            ll xd = mCBrute(window);
            ans.eb(xd, A[R] - A[L]);
            values.eb(xd);
        }
        window.clear();
        chk(is_sorted(all(values)));
        dbg(L, values);
    }
    sor(ans);
    return ans;
}

void solve() {
    ll N, Q; cin >> N >> Q;
    vl A(N); each(x, A) cin >> x;
    vl queries(Q); each(x, queries) cin >> x;
    dbg(N, Q);
    dbg(A);
    dbg(queries);

    vpi valuesAndDifference = brute(N, A);
    const int M = sz(valuesAndDifference);

    vl values(M);
    vl pref(M);
    for(int i = 0; i < M; i++) {
        auto [mCost, diff] = valuesAndDifference[i];
        values[i] = mCost;
        pref[i] = diff;
        if(0 <= i - 1) pref[i] += pref[i - 1];
    }

    auto query = [&](int L, int R) -> ll {
        ll sum = pref[R];
        if(0 <= L - 1) sum -= pref[L - 1];
        return sum;
    };

    each(x, queries) {
        if(M == 0 || x < valuesAndDifference.ft.f) cout << "0\n";
        else {
            int i = upper_bound(all(values), x) - values.begin();
            i--;
            ll ans = query(0, i);
            dbg(ans);
            cout << ans << "\n";
        }
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

//?    while(0) {
//?        RAYA;
//?        ll N = rng_ll(1, 8);
//?        vl arr(N); each(x, arr) x = rng_ll(0, 12);
//?        dbg(N);
//?        dbg(arr);
//?        ll ans = mCBrute(arr);
//?        ll greedy = mCGreedy(arr);
//?        dbg(ans, greedy);
//?        chk(ans == greedy);
//?    }

    while(1) {
        RAYA;
        ll N = rng_ll(1, 6);
        vl A(N); each(x, A) x = rng_ll(1, 15);
        sor(A);
        dbg(N);
        dbg(A);
        brute(N, A);
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
