#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;

    vector<ll> p;
    for(ll i = 0; i < n; i++) {
        ll tmp;
        cin >> tmp;

        p.push_back(tmp);
    }

    ll result = -1;
    for(ll i = 0; i < n; i++) {
        ll current = abs(p[i] - i - 1);
        if(current != 0) {
            result = current;
            break;
        }
    }

    for(ll i = 0; i < n; i++) {
        ll current = abs(p[i] - i - 1);
        if(current != 0) {
            result = __gcd(result, current);
        }
    }

    cout << result << "\n";
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
