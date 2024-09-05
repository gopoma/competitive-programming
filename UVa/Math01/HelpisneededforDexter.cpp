#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "helpers/debug.h"

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define RAYA
#endif

template<class T> using V = vector<T>;
#define all(x) begin(x), end(x)

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

using ll = long long;
using db = long double;

void solve() {
//?    {
//?        const ll MAXN = 1000;
//?        vector<ll> dp(MAXN + 5, ll(1e18));
//?        dp[0] = 0;
//?        dp[1] = 1;
//?        dp[2] = 2;
//?        dp[3] = 2;
//?        map<ll, ll> hist;
//?        for(ll x = 4; x <= MAXN; x++) {
//?            for(ll y = 1; y <= x; y++) {
//?                dp[x] = min(dp[x], 1LL + max(dp[y - 1LL], dp[x - y]));
//?            }
//?        }
//?        for(ll x = 0; x <= MAXN; x++) {
//?            //? dbg(x, dp[x]);
//?            hist[dp[x]]++;
//?        }
//?        for(auto& x: hist) dbg(x);
//?    }
//?    dbg("xd");
    ll N;
    while(cin >> N) {
        ll ans = 0;
        for(ll bit = 40; bit >= 0; bit--) {
            if(N & (1LL << bit)) {
                ans = bit + 1LL;
                break;
            }
        }
        dbg(N, ans);
        cout << ans << "\n";
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);

    int t = 1;
    //? cin >> t;

    for(int idx = 0; idx < t; idx++) {
        solve();
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
