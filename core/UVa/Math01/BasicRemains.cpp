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
    //? Template
    // TODO: here :v
    auto convert = [&](ll num, ll base = 62ULL) {
        if(num == 0) return vector<int>{0};
        vector<int> res;
        while(num > 0) {
            res.emplace_back(num % base);
            num /= base;
        }
        reverse(all(res));
        return res;
    };
    auto eval = [&](vector<int> digits, ll base) -> ll {
        ll ans = 0;
        ll pot = 1;
        for(int i = int(digits.size()) - 1; i >= 0; i--) {
            ans += ll(digits[i]) * pot;
            pot *= base;
        }
        return ans;
    };
    //? /Template
    RAYA;
    ll b;
    string p;
    ll m;
    while(true) {
        cin >> b; if(b == 0) return;
        cin >> p >> m;
        dbg(b, p, m);

        vector<int> digits;
        for(auto& c: to_string(m))
            digits.emplace_back(int(c - '0'));
        ll m_norm = eval(digits, b);
        dbg(m_norm);

        ll ans = 0 % m_norm;
        ll pot = 1 % m_norm;
        reverse(all(p));
        for(int i = 0; i < int(p.size()); i++) {
            ans += ll(p[i] - '0') * pot;
            ans %= m_norm;
            pot *= b;
            pot %= m_norm;
        }
        dbg(ans);
        vector<int> response = convert(ans, b);
        string xd;
        for(auto& x: response) xd.push_back(to_string(x).back());
        cout << xd << "\n";
        RAYA;
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
