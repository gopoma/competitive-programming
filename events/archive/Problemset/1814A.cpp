#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
    ll n, k;
    cin >> n >> k;

    // 2 * x + y * k = n
    // d = gcd(2, k)
    // if d | n -> YES
    // else -> NO

    ll d = __gcd(2LL, k);

    if(n % d == 0) {
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
