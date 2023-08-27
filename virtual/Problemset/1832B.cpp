#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
    ll n, k;
    cin >> n >> k;

    deque<ll> tmp;
    for(ll i = 0; i < n; i++) {
        ll input;
        cin >> input;

        tmp.push_back(input);
    }

    sort(tmp.begin(), tmp.end());

    for(auto aux: tmp) {
        cout << aux << " ";
    }
    cout << endl;

    for(ll i = 0; i < k; i++) {
        if(tmp[0] + tmp[1] < tmp[tmp.size() - 1]) {
            tmp.pop_front();
            tmp.pop_front();
        } else {
            tmp.pop_back();
        }
    }

    ll sum = 0;
    for(auto aux: tmp) {
        sum += aux;
    }

    cout << sum << "\n";
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
