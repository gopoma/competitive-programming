#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n; cin >> n;
    vector<ll> a(n); for(auto& x: a) cin >> x;
    map<ll, ll> hist;
    ll re = 0;
    for(int i = 0; i < n; i++) {
        re += hist[i - a[i]];
        hist[a[i] + i]++;
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
