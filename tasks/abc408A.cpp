#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    ll n, S; cin >> n >> S;
    vector<ll> a(n); for(auto& x: a) cin >> x;

    if(a[0] > S) {
        cout << "No\n";
        return;
    }
    for(int i = 1; i < n; i++) {
        if(a[i] - a[i - 1] > S) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
