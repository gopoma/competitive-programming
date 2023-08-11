#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n, l; cin >> n >> l;
    ll arr[n];

    for(ll& a: arr)
        cin >> a;

    sort(arr, arr + n);

    ll maxDistance = 0;
    for(ll i = 1; i < n; i++)
        maxDistance = max(maxDistance, arr[i] - arr[i - 1]);

    ld result = max((ld) (maxDistance / 2.0), (ld) max(arr[0] - 0, l - arr[n - 1]));

    cout << fixed << setprecision(9) << result << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;

    while(t--)
        solve();

    return 0;
}
