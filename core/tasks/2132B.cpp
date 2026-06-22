#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    ll n; cin >> n;
    vector<ll> re;

    for(ll p10 = 10; p10 < ll(1e18); p10 *= 10LL) {
        if(n % (p10 + 1LL) == 0LL) {
            re.emplace_back(n / (p10 + 1LL));
        }
    }


    sort(re.begin(), re.end());
    if(re.empty()) {
        cout << "0\n";
        return;
    }
    cout << int(re.size()) << "\n";
    for(auto& x: re) cout << x << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
