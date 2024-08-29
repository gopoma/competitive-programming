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

void solve(ll caso) {
    ll n; cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> a[i][j];
    map<ll, ll> hist;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) hist[a[i][j]]++;
    bool ok = true;
    for(auto& [val, cnt]: hist) ok &= (cnt <= n);
    cout << "Case " << caso << ": " << (ok?"yes":"no") << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);

    int t = 1;
    cin >> t;

    ll caso = 0;
    for(int idx = 0; idx < t; idx++) {
        caso++;
        solve(caso);
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
