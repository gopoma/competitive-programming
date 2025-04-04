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

ll sqr(ll x) { return x * x; }

void solve() {
    ll T; cin >> T;
    ll caso = 0;
    while(T--) {
        caso++;
        ll N; cin >> N;
        vector<ll> ans;
        for(ll factor = 1; factor <= 32000; factor++) {
            //? factor * factor = N - X
            //? X = N - factor * factor
            ll X = N - factor * factor;
            if(X <= 0) break;
            if(X % factor == 0LL) ans.emplace_back(X);
        }
        reverse(all(ans));
        cout << "Case " << caso << ": ";
        const int M = int(ans.size());
        for(int i = 0; i < M; i++) cout << ans[i] << " \n"[i == M - 1];
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
