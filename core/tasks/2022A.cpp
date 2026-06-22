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

void solve() {
    ll n, r; cin >> n >> r;
    vector<ll> a(n); for(auto& x: a) cin >> x;
    ll ans = 0;
    ll queda = 0;
    for(auto& x: a) {
        ll take = x / 2LL;
        ans += 2LL * take;
        x -= 2LL * take;
        r -= take;
        queda += x;
    }
    dbg(r, queda);

    if(queda <= r) {
        ans += queda;
    } else {
        ll ex = queda - r;
        ans += r - ex;
        dbg(ex);
    }
    cout << ans << "\n";
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