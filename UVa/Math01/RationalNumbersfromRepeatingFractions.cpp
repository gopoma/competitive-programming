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
    ll caso = 0;
    while(true) {
        caso++;
        RAYA;
        ll j; cin >> j;
        if(j == -1) return;
        string S; cin >> S;
        dbg(j, S);

        assert(int(S.size()) >= 3);
        assert(S[0] == '0');
        assert(S[1] == '.');

        ll num = -79, denom = -79;
        int amount_decimals = int(S.size()) - 2;
        if(j == 0) {
            num = stoll(S.substr(2, amount_decimals));
            denom = stoll("1" + string(amount_decimals, '0'));
        } else {
            assert(amount_decimals >= 1);
            ll free = amount_decimals - j;
            ll periodic = j;
            dbg(free, periodic);

            ll tot = stoll(S.substr(2, amount_decimals));
            ll resta = free? stoll(S.substr(2, free)) : 0;
            dbg(tot, resta);

            num = tot - resta;
            denom = stoll(string(j, '9') + string(free, '0'));
            assert(num >= 0);
            assert(denom >= 0);

            dbg(num, denom);
        }
        ll g = __gcd(num, denom);
        num /= g;
        denom /= g;
        cout << "Case " << caso << ": " << num << "/" << denom << "\n";
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
