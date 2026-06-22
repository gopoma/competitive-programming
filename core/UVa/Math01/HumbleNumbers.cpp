#pragma GCC optimize ("trapv")

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
    const int size = 6000;
    std::string suffixes[size];

    for(int i = 1; i <= size; ++i) {
        if (i % 100 >= 11 && i % 100 <= 13) {
            suffixes[i - 1] = "th";
        } else {
            switch (i % 10) {
                case 1: suffixes[i - 1] = "st"; break;
                case 2: suffixes[i - 1] = "nd"; break;
                case 3: suffixes[i - 1] = "rd"; break;
                default: suffixes[i - 1] = "th";
            }
        }
    }

    vector<long long> ans;
    ll current_w = 1;
    for(ll w = 0; w < 32LL; w++) {
        if(current_w > 2000000000) break;
        ll current_x = 1;
        for(ll x = 0; x < 32LL; x++) {
            if(current_w * current_x > 2000000000) break;
            ll current_y = 1;
            for(ll y = 0; y < 32LL; y++) {
                if(current_w * current_x * current_y > 2000000000) break;
                ll current_z = 1;
                for(ll z = 0; z < 32LL; z++) {
                    if(current_w * current_x * current_y * current_z > 2000000000) break;

                    ans.emplace_back(current_w * current_x * current_y * current_z);
                    current_z *= 7LL;
                }
                current_y *= 5LL;
            }
            current_x *= 3LL;
        }
        current_w *= 2LL;
    }
    sort(ans.begin(), ans.end());

    ll n;
    while(true) {
        cin >> n;
        if(n == 0) return;
        cout << "The ";
        cout << n;
        string n_str = to_string(n);
        cout << suffixes[n - 1];
        cout << " humble number is ";
        n--;
        cout << ans[n] << ".\n";
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
