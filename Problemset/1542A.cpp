#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;

    ll amountOdds = 0, amountEvens = 0;

    for(ll i = 0; i < 2 * n; i++) {
        ll tmp;
        cin >> tmp;

        if(tmp % 2 == 0) {
            amountEvens++;
        } else {
            amountOdds++;
        }
    }

    if(amountOdds == amountEvens) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    cout << "\n";
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
