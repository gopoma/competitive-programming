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
    ll n;
    while(true) {
        cin >> n;
        if(n == 0) return;
        vector<db> a(n); for(auto& x: a) cin >> x;
        db tar = accumulate(all(a), db(0.0)) / db(n);
        tar = round(tar * db(100)) / db(100);
        db ans = 0, ans2 = 0;
        for(auto& x: a) {
            dbg(x, tar);
            if(x < tar) {
                ans += tar - x;
                dbg("give", tar - x);
            } else {
                ans2 += x - tar;
                dbg("need", x - tar);
            }
        }
        dbg(ans, ans2);
        db response = min(fabsl(ans), fabsl(ans2));
        cout << "$" << response << "\n";
        RAYA;
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cout << fixed << setprecision(2);
    cerr << fixed << setprecision(2);

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
