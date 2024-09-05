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

ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

void solve() {
    RAYA;
    ll n, m, c;
    while(true) {
        cin >> n >> m >> c;
        if(!n && !m && !c) return;
        dbg(n, m, c);
        ll color_8_8;
        if((n + m) % 2LL == (8LL + 8LL) % 2LL) color_8_8 = c;
        else color_8_8 = !c;
        dbg(color_8_8);

        ll cols = m - 8LL + 1LL;
        ll rows = n - 8LL + 1LL;
        ll complete_blocks = fdiv(rows, 2LL);
        ll rem = rows % 2LL;
        ll ans = 0;
        if(color_8_8) { //? 1
            ll odd_block_contrib = cdiv(cols, 2LL);
            ll even_block_contrib = fdiv(cols, 2LL);
            ans += complete_blocks * (odd_block_contrib + even_block_contrib);
            if(rem) ans += odd_block_contrib;
        } else { //? 0
            ll odd_block_contrib = fdiv(cols, 2LL);
            ll even_block_contrib = cdiv(cols, 2LL);
            ans += complete_blocks * (odd_block_contrib + even_block_contrib);
            if(rem) ans += odd_block_contrib;
        }
        cout << ans << "\n";

        RAYA;
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
