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
    auto get = [&](string S) -> vector<ll> {
        reverse(all(S));

        vector<ll> ans;
        for(auto& c: S) {
            if(isdigit(c)) ans.emplace_back(ll(c - '0'));
            else ans.emplace_back(ll(c - 'A' + 10LL));
        }

        return ans;
    };

    auto eval = [&](vector<ll>& digits, ll base) -> ll {
        ll ans = 0;
        ll carry = 1LL;
        for(ll i = 0; i < ll(digits.size()); i++) {
            ans += digits[i] * carry;
            carry *= base;
        }
        return ans;
    };

    string X, Y;
    while(cin >> X) {
        RAYA;
        cin >> Y;
        dbg(X, Y);

        vector<ll> xx = get(X);
        vector<ll> yy = get(Y);

        ll MN_BASE_X = max(*max_element(all(xx)) + 1LL, 2LL);
        ll MN_BASE_Y = max(*max_element(all(yy)) + 1LL, 2LL);
        dbg(xx, MN_BASE_X, yy, MN_BASE_Y);
        bool ok = false;
        for(ll base = MN_BASE_X; base <= 36LL && !ok; base++) {
            for(ll base2 = MN_BASE_Y; base2 <= 36LL && !ok; base2++) {
                ll num = eval(xx, base);
                ll num2 = eval(yy, base2);

                if(num == num2) {
                    cout << X << " (base " << base << ") = " << Y << " (base " << base2 << ")\n";
                    ok = true;
                    break;
                }
            }
        }
        if(!ok) cout << X << " is not equal to " << Y << " in any base 2..36\n";
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
