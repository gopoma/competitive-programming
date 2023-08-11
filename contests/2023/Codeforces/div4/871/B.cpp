#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;

    vector<ll> indices;

    indices.push_back(-1);

    for(ll i = 0; i < n; i++) {
        ll input;
        cin >> input;

        if(input == 1) {
            indices.push_back(i);
        }
    }
    indices.push_back(n);

    ll result = 0;
    for(ll i = 0; i < indices.size() - 1; i++) {
        result = max(result, indices[i + 1] - indices[i] - 1);
    }

    cout << result << endl;
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
