#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n;
    cin >> n;

    ll p[n];
    for(ll i = 0; i < n; i++) {
        cin >> p[i];
    }

    ll result[n];
    ll counter = 0;
    for(ll i = 1; i < n; i++) {
        result[counter++] = p[i];
    }
    result[counter] = p[0];

    for(ll l = 0; l < n; l++) {
        for(ll r = l; r < n; r++) {
            ll partial[n];
            ll counter = 0;

            for(ll i = r + 1; i < n; i++) {
                partial[counter++] = p[i];
            }
            for(ll i = r; i >= l; i--) {
                partial[counter++] = p[i];
            }
            for(ll i = 0; i < l; i++) {
                partial[counter++] = p[i];
            }

            bool found = false;

            for(ll i = 0; i < n; i++) {
                if(result[i] > partial[i])
                    break;

                if(result[i] < partial[i]) {
                    found = true;
                    break;
                }
            }

            if(found) {
                for(ll i = 0; i < n; i++) {
                    result[i] = partial[i];
                }
            }
        }
    }

    for(ll i = 0; i < n - 1; i++) {
        cout << result[i] << " ";
    }
    cout << result[n - 1] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
