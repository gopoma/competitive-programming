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

#define sz(x) int(x.size())

void solve() {
    auto get = [&](ll N) -> vector<int> {
        vector<int> ans;
        for(auto& c: to_string(N))
            ans.emplace_back(int(c - '0'));
        reverse(all(ans));
        return ans;
    };
    auto all_ones = [&](vector<int>& digits) -> bool {
        bool ok = true;
        for(auto& d: digits)
            ok &= (d == 1);
        return ok;
    };
    auto eval = [&](vector<int> digits, ll base) -> ll {
        ll ans = 0;
        ll pot = 1;
        for(int i = 0; i < sz(digits); i++) {
            ans += pot * ll(digits[i]);
            pot *= base;
        }
        return ans;
    };
    ll T; cin >> T;
    while(T--) {
        ll A, B, C;
        char pad;
        cin >> A >> pad >> B >> pad >> C;
        dbg(A, B, C);

        vector<int> a = get(A);
        vector<int> b = get(B);
        vector<int> c = get(C);
        if(all_ones(a) && all_ones(b) && all_ones(c) && (sz(a) + sz(b) == sz(c))) {
            cout << "1\n";
        } else {
            ll MN_BASE = max(max({*max_element(all(a)), *max_element(all(b)), *max_element(all(c))}) + 1, 2);
            bool ok = false;
            for(ll base = MN_BASE; base <= 64; base++) {
                if(eval(a, base) + eval(b, base) == eval(c, base)) {
                    cout << base << "\n";
                    ok = true;
                    break;
                }
            }
            if(!ok) cout << "0\n";
        }
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
