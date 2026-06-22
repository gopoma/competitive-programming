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
	ll n, x; cin >> n >> x;
	deque<ll> a(n); for(auto& e: a) cin >> e;
	sort(all(a));
	dbg(n, x);
	dbg(a);

	map<ll, ll> xd; 
	for(ll MEX = 0; ; MEX++) {
		while(!a.empty() && a.front() <= MEX) {
			xd[a.front() % x]++;
			a.pop_front();
		}
		if(xd[MEX % x] > 0) {
			xd[MEX % x]--;
			continue;
		} else {
			cout << MEX << "\n";
			return;
		}
	}
	assert(false);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);

    int t = 1;
    cin >> t;

    for(int idx = 0; idx < t; idx++) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
