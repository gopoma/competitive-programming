#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n;
    cin >> n;

    if(n % 2 == 0) {
        cout << -1 << "\n";
        return;
    }

    ll x = n, m = 40;
    vector<ll> sol;
    for(int i = 1; i <= 40; i++) {
        if(x == 1) {
            m = i - 1;
            break;
        }

        if(((x + 1) / 2) % 2 != 0) {
            x = (x + 1) / 2;
            sol.push_back(1);
        } else {
            x = (x - 1) / 2;
            sol.push_back(2);
        }
    }

    if(x != 1) {
        cout << -1 << "\n";
        return;
    }

    reverse(sol.begin(), sol.end());

    cout << m << "\n";

    if(sol.size() == 1) {
        cout << sol[0] << "\n";
        return;
    }

    for(int i = 0; i < sol.size() - 1; i++) {
        cout << sol[i] << " ";
    }

    cout << sol[sol.size() - 1] << "\n";
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
