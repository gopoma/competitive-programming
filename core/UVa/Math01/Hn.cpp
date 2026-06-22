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

long long H(int n){
    long long res = 0;
    for( int i = 1; i <= n; i=i+1 ){
        res = (res + n/i);
    }
    return res;
}

using ll = long long;

ll slv(ll N) {
    if(N == 0) return 0;
    ll ans = 0;
    ll L = 1;
    while(L <= N) {
        ll current_val = N / L;
        ll R = N / current_val;
        ans += (R - L + 1LL) * current_val;
        L = R + 1LL;
    }
    return ans;
}

void solve() {
    ll N; cin >> N;
    ll ans = slv(N);
    dbg(ans);
    cout << ans << "\n";
}

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

//?    for(ll x = 0; x < 1000; x++) slv(ll(1e9));
//?
//?    for(ll x = 0; x <= 10000; x++) {
//?        assert(H(x) == slv(x));
//?    }

    int t = 1;
    cin >> t;

    for(int idx = 0; idx < t; idx++) {
        solve();
    }
}
