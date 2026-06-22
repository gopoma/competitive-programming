#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n, m; cin >> n >> m;
    multiset<ll> ms;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        ms.emplace(x);
    }
    for(int i = 0; i < m; i++) {
        ll x; cin >> x;
        if(ms.find(x) != ms.end()) {
            ms.erase(ms.find(x));
        }
    }
    for(auto& x: ms) cout << x << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
