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
    auto F = [&](ll x) -> ll {
        return 2LL * x * x + x;
    };
    auto give = [&](ll nth, string val) -> void {
        cout << "TERM " << nth << " IS " << val << "\n";
    };
    ll N;
    while(cin >> N) {
        dbg(N);
        if(N == 1) give(N, "1/1");
        else if(N == 2) give(N, "1/2");
        else if(N == 3) give(N, "2/1");
        else {
            ll left = 0; //? always good
            ll right = ll(1e9); //? always bad
            while(left + 1 < right) {
                ll middle = (left + right) >> 1LL;
                if(F(middle) <= N) left = middle;
                else right = middle;
            }
            ll L = left;
            dbg(L, F(L), F(L) + 1);
            ll mid = 2LL * L + 1LL;
            ll mid2 = mid + 1LL;
            dbg(mid, mid2);
            if(N == F(L)) give(N, to_string(mid - 1LL) + "/1");
            else if(N == F(L) + 1) give(N, to_string(mid) + "/1");
            else {
                if(N<=F(L)+1LL+mid-1LL) {
                    ll d = N - (F(L) + 1LL);
                    give(N, to_string(mid - d)+"/"+to_string(d + 1LL));
                } else {
                    ll d = F(L + 1LL) - N;
                    give(N, to_string(mid + 1LL - d)+"/"+to_string(d + 1LL));
                }
            }
        }
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
