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
    auto get2 = [&](char c) -> ll {
        if(isdigit(c)) return ll(c - '0');
        else return ll(c - 'A' + 10LL);
    };

    auto get3 = [&](ll d) -> char {
        if(0 <= d && d <= 9) return to_string(d).back();
        else return char('A' + d - 10LL);
    };

    auto get = [&](string str_N, ll base) -> ll {
        ll ans = 0;

        ll pot = 1;
        for(int i = 0; i < int(str_N.size()); i++) {
            ans += pot * get2(str_N[i]);
            pot *= base;
        }
        return ans;
    };

    //? Template
    // TODO: here :v
    auto convert = [&](ll num, ll base = 62ULL) {
        if(num == 0) return V<int>{0};
        V<int> res;

        while(num > 0) {
            res.emplace_back(num % base);
            num /= base;
        }

        reverse(all(res));
        return res;
    };
    //? /Template

    string str_N;
    ll base_from, base_to;
    while(cin >> str_N) {
        //? RAYA;
        cin >> base_from >> base_to;
        //? dbg(str_N, base_from, base_to);
        reverse(all(str_N));

        ll N = get(str_N, base_from);
        //? dbg(N);

        vector<int> xd = convert(N, base_to);
        //? dbg(xd);

        string ans;
        for(auto& d: xd) ans.push_back(get3(d));
        //? dbg(ans);

        if(int(ans.size()) > 7) ans = "ERROR";
        reverse(all(ans));
        while(int(ans.size()) < 7) ans.push_back(' ');
        reverse(all(ans));
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
