
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
#pragma GCC optimize ("trapv")

#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



using ll  = long long;
using db  = long double;
using str = string;
using ull  = unsigned long long;

using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;



#define mp make_pair
#define f  first
#define s  second

template<class T> using V = vector<T>;
#define all(x) begin(x), end(x)



const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}



//? Template
//? /Template

ll brute(ll n, ll x, V<ll> a) {
    for(ll taken = 0;;taken++) {
        V<ll> xd = a;
        for(int _ = 0; _ < taken; _++) {
            sort(xd.rbegin(), xd.rend());
            for(int i = 0; i < min(x, ll(xd.size())); i++) {
                if(xd[i] > 0) xd[i]--;
            } 
        }
        bool ok = true;
        for(auto& e: xd) ok &= (e == 0LL);
        if(ok) return taken;
    }
}

using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;

ll slv(ll n, ll x, V<ll> a) {
    i128 sum = accumulate(all(a), 0LL);
    i128 mx = *max_element(all(a));
    i128 left = 0;
    i128 right = i128(1e18);
    while(left + i128(1) < right) {
        i128 middle = (left + right) / i128(2);
        if(mx <= middle && middle * x >= sum) right = middle;
        else left = middle;
    }
    return ll(right);
}

void solve() {
    ll n, x; cin >> n >> x;
    V<ll> a(n); for(auto& e: a) cin >> e;
    dbg(n, x);
    dbg(a);
    ll ans = slv(n, x, a);
    dbg(ans);
    cout << ans << "\n";
}


//? Generator
mt19937 rng(0);
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    while(1) {
        RAYA;
        ll n = rng_ll(ll(5e5), ll(5e5));
        ll x = rng_ll(1, 10);
        V<ll> a(n); for(auto& e: a) e = rng_ll(ll(1e9), ll(1e9));
        dbg(n, x);
        //? dbg(a);
        dbg("Brute");
        //? ll ans = brute(n, x, a);
        dbg("/Brute");
        dbg("Greedy");
        ll greedy = slv(n, x, a);
        dbg("/Greedy");
        //? dbg(ans, greedy);
        //? chk(ans == greedy);
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