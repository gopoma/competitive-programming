#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n;
    cin >> n;

    vector<ll> a;

    bool hasOdd = false;
    ll minOdd = LONG_MAX;
    for(ll i = 0; i < n; i++) {
        ll tmp;
        cin >> tmp;

        if(tmp % 2 != 0) {
            hasOdd = true;
            minOdd = min(minOdd, tmp);
        }

        a.push_back(tmp);
    }

    bool isEvenBeautiful = true;
    for(ll i = 0; i < n; i++) {
        if(a[i] % 2 != 0) {
            if(hasOdd) {
                isEvenBeautiful = false;
                break;
            }
        }
    }

    bool isOddBeautiful = true;
    for(ll i = 0; i < n; i++) {
        if(a[i] % 2 == 0) {
            if(minOdd == LONG_MAX || (a[i] - minOdd)     <= 0) {
                isOddBeautiful = false;
                break;
            }
        }
    }

    if(isEvenBeautiful || isOddBeautiful) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
