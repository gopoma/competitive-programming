#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool isPrime(ll n) {
    if (n < 2) return false;
    for (ll x = 2; x * x <= n; x++) {
        if(n % x == 0) return false;
    }
    return true;
}

void solve() {
    ll n;
    cin >> n;

    if(n == 1) {
        cout << "NO\n";
        return;
    }

    ll tmp = sqrt(n);

    if(tmp * tmp == n && isPrime(tmp)) {
        cout << "YES";
    } else {
        cout << "NO";
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
