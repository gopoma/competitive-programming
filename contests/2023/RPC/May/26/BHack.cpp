#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);

    for(ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll result = 0;
    while(!is_sorted(a.begin(), a.end())) {
        result++;
        for(ll i = 0; i <= n - k; i++) {
            sort(a.begin() + i, a.begin() + i + k);
        }
    }

    cout << result << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
