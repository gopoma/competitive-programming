//? #pragma GCC optimize ("trapv")

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

ll memo[10][2][2][10];
ll slv(ll m, ll n) {
    auto pref = [&](ll R) -> ll {
        if(R < 0) return 0LL;
        if(R == 0) return 1LL;
        const string R_str = to_string(R);
        vector<int> digits;
        for(auto& c: R_str)
            digits.emplace_back(int(c - '0'));
        memset(memo, -1, sizeof(memo));
        function<ll(int, bool, bool, int)> dp = [&](int idx, bool last_defined, bool reached_lower, int lleva) -> ll {
            if(idx == int(digits.size())) return lleva;
            if(memo[idx][last_defined][reached_lower][lleva] != -1) return memo[idx][last_defined][reached_lower][lleva];

            ll ans = 0;
            if(!last_defined) {
                ans += dp(idx + 1, false, false, 0);

                if(idx == 0) {
                    for(int d = 1; d <= digits[idx]; d++) {
                        ans += dp(idx + 1, true, (d < digits[idx]), 0);
                    }
                } else {
                    for(int d = 1; d <= 9; d++) {
                        ans += dp(idx + 1, true, true, 0);
                    }
                }
            } else {
                if(reached_lower) {
                    for(int d = 0; d <= 9; d++) {
                        ans += dp(idx + 1, true, true, lleva + (d == 0));
                    }
                } else {
                    for(int d = 0; d <= digits[idx]; d++) {
                        ans += dp(idx + 1, true, (d < digits[idx]), lleva + (d == 0));
                    }
                }
            }
            return memo[idx][last_defined][reached_lower][lleva] = ans;
        };
        return dp(0, false, false, 0) + 1LL;
    };
    ll right = pref(n);
    ll left = pref(m - 1);
    //?dbg(n, right);
    //?dbg(m - 1, left);
    ll ans = right - left;
    return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ll m, n;
    while(true) {
        RAYA;
        cin >> m >> n;
        if(m < 0) break;
        assert(m <= n);
        dbg(m, n);

        ll ans = slv(m, n);
        dbg(ans);
        cout << ans << "\n";
    }

//?    for(int i = 0; i < 100000; i++) {
//?        slv(0, ll(1e9));
//?    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
