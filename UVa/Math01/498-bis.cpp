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
    ll x;
    RAYA;
    while(cin >> x) {
        cin.ignore();

        string S;
        getline(cin, S);

        dbg(x);
        dbg(S);

        vector<string> tokens;
        {
            string current;
            for(auto& c: S) {
                if(c == ' ') {
                    tokens.emplace_back(current);
                    current.clear();
                } else {
                    current.push_back(c);
                }
            }
            tokens.emplace_back(current);
            for(auto& x: tokens) while(!x.empty() && x.back() == ' ') x.pop_back();
            vector<string> new_tokens;
            for(auto& x: tokens) if(!x.empty()) new_tokens.emplace_back(x);
            swap(tokens, new_tokens);
        }
        dbg(tokens);
        vector<ll> a;
        for(auto& e: tokens) a.emplace_back(stoll(e));
        dbg(a);

        if(!a.empty())
            a.pop_back();
        reverse(all(a));
        for(ll i = 0; i < int(a.size()); i++) {
            a[i] *= (i + 1LL);
        }
        ll ans = 0;
        ll pot = 1;
        for(int i = 0; i < int(a.size()); i++) {
            ans += pot * a[i];
            pot *= x;
        }
        dbg(ans);
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
