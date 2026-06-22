#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a;
    vector<ll> b;

    for(ll i = 0; i < n; i++) {
        ll tmp;
        cin >> tmp;
        a.push_back(tmp);
    }

    for(ll i = 0; i < n; i++) {
        ll tmp;
        cin >> tmp;
        b.push_back(tmp);
    }


    vector<ll> A;
    vector<ll> B;
    for(auto aa: a)
        A.push_back(aa);

    for(auto bb: b)
        B.push_back(bb);

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    unordered_map<ll, vector<ll>> tmp;

    for(ll i = 0; i < n; i++) {
        tmp[A[i]].push_back(B[i]);
    }

    for(ll i = 0; i < n - 1; i++) {
        const ll partial = tmp[a[i]].back();
        tmp[a[i]].pop_back();

        cout << partial << " ";
    }

    cout << tmp[a[n - 1]].back() << "\n";
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
