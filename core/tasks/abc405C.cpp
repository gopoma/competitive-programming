#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

#define dbg(x) cout << #x << ": " << x << endl;
// #define dbg(x) 0

void solve() {
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    ll re = 0;
    ll sum = a.back();
    for(int i = n - 2; i >= 0; i--) {
        re += a[i] * sum;
        sum += a[i];
    }
    cout << re << "\n";
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
