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
    ll num, denom;
    while(cin >> num >> denom) {
        assert(!(num == 0 && denom == 0));
        dbg(num, denom);
        RAYA;

        ll g = __gcd(num, denom);
        num /= g;
        denom /= g;

        vector<long long> ans;
        while(true) {
            ll I = num / denom;
            ans.emplace_back(I);
            dbg(num, denom, I);
            num %= denom;
            if(num == 1) break;
            swap(num, denom);
        }
        ans.emplace_back(denom);

        cout << "[";
        const int M = int(ans.size());
        for(int i = 0; i < M; i++) {
            cout << ans[i];
            if(i == 0) cout << ";";
            else if(i < M - 1) cout << ",";
        }
        cout << "]\n";
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
