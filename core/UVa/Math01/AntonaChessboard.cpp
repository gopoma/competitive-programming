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

using ll = long long;

ll sqr(ll x) { return x * x; }

void solve() {
    ll N;
    while(true) {
        RAYA;
        cin >> N;
        dbg(N);
        if(N == 0) return;

        if(N == 1) cout << "1 1\n";
        else if(N == 2) cout << "1 2\n";
        else if(N == 3) cout << "2 2\n";
        else if(N == 4) cout << "2 1\n";
        else {
            ll L = -79;
            {
                ll left = 0; //? always good
                ll right = ll(1e9); //? always bad
                while(left + 1 < right) {
                    ll middle = (left + right) >> 1LL;
                    if(middle * middle <= N) left = middle;
                    else right = middle;
                }
                L = left;
            }
            assert(L != -79);
            ll R = L + 1;
            dbg(L, R, L * L, R * R);
            if(sqr(L) == N) {
                if(sqr(N) % 2LL == 0LL) cout << L << " " << 1 << "\n";
                else cout << 1 << " " << L << "\n";
            } else {
                assert(sqr(L) < N && N < sqr(R));
                if(sqr(L) % 2LL == 0LL) {
                    ll extend = R;
                    if(N <= sqr(L) + extend) {
                        const ll row = L + 1;
                        const ll col = N - sqr(L);
                        cout << row << " " << col << "\n";
                    } else {
                        const ll row = sqr(R) - N + 1LL;
                        const ll col = R;
                        cout << row << " " << col << "\n";
                    }
                } else {
                    ll extend = R;
                    if(N <= sqr(L) + extend) {
                        const ll row = N - sqr(L);
                        const ll col = R;
                        cout << row << " " << col << "\n";
                    } else {
                        const ll row = R;
                        const ll col = sqr(R) - N + 1LL;
                        cout << row << " " << col << "\n";
                    }
                }
            }
        }
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int t = 1;
    //? cin >> t;

    for(int idx = 0; idx < t; idx++) {
        solve();
    }
}
