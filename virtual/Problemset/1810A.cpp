#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n;
    cin >> n;

    bool ok = false;

    for(int i = 1; i <= n; i++) {
        ll current;
        cin >> current;

        if(current <= i) {
            ok = true;
        }
    }

    if(ok) {
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
