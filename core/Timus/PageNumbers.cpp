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
    ll N; cin >> N; // <>
    for(int tar_digit = 0; tar_digit < 10; tar_digit++) {
        function<ll()> solve = [&]() -> ll {
            const string N_str = to_string(N);
            vector<int> digits;
            for(auto& c: N_str) digits.emplace_back(c - '0');
            const int MAXN = int(digits.size());
            ll memo[15][5][5][15];
            memset(memo, -1, sizeof(memo));
            function<ll(int, bool, bool, int)> dp = [&](int idx, bool lastWasDefined, bool reachedLower, int counter) -> ll {
                if(idx == MAXN) return counter;
                if(memo[idx][lastWasDefined][reachedLower][counter] != -1) return memo[idx][lastWasDefined][reachedLower][counter];
                ll ans = 0;
                if(!lastWasDefined) {
                    ans += dp(idx + 1, lastWasDefined, reachedLower, counter);
                    if(idx == 0) {
                        for(int d = 1; d <= digits[idx]; d++) {
                            ans += dp(idx + 1, true, d < digits[idx], counter + (d == tar_digit));
                        }
                    } else {
                        for(int d = 1; d <= 9; d++) {
                            ans += dp(idx + 1, true, true, counter + (d == tar_digit));
                        }
                    }
                } else {
                    if(reachedLower) {
                        for(int d = 0; d <= 9; d++) {
                            ans += dp(idx + 1, true, true, counter + (d == tar_digit));
                        }
                    } else {
                        for(int d = 0; d <= digits[idx]; d++) {
                            ans += dp(idx + 1, true, d < digits[idx], counter + (d == tar_digit));
                        }
                    }
                }
                return memo[idx][lastWasDefined][reachedLower][counter] = ans;
            };
            ll ans = dp(0, false, false, 0);
            return ans;
        };
        ll ans = solve();
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
