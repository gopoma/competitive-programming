#pragma GCC optimize ("Ofast")
#undef _GLIBCXX_DEBUG //? for Stress Testing

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
    vector<db> ans;
    while(T--) {
        ll N; cin >> N;
        if(N == 1) ans.emplace_back(db(0));
        else {
            ll take = sqr(N - 2LL);
            ans.emplace_back(db(sqr(N)) - db(take) + db(take) * sqrtl(db(2)));
        }
    }
    const int M = int(ans.size());
    for(int i = 0; i < M; i++) {
        cout << ans[i] << "\n";
        if(i < M - 1) cout << "\n";
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cout << fixed << setprecision(12);
    cerr << fixed << setprecision(12);

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
