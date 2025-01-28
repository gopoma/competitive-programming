#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

vl v;
ll n, b, x;

ll f(ll k) {
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll a = v[i] / k, c = v[i] % k;
        if (c == 0) {
            res += a * a * k * (k - 1) / 2 * b;
        } else {
            res +=
                (a * a * k * (k - 1) / 2 + a * c * (k - c) + (2 * a + 1) * c * (c - 1) / 2) *
                b;
        }
    }
    return res - (k - 1) * x;
}

ll ternarySearch(ll low, ll high) { // O(log n)
    while (high - low > 2) {
        ll m1 = low + (high - low) / 3;
        ll m2 = high - (high - low) / 3;
        if (f(m1) < f(m2)) low = m1;
        else high = m2;
    }
    ll maxi = f(low);
    for (ll i = low + 1; i <= high; i++) {
        maxi = max(maxi, f(i));
    }
    return maxi;
}

//? https://codeforces.com/contest/1928/submission/245840952
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> b >> x;
        v.resize(n);
        for (auto &i : v) cin >> i;

        ll ans = ternarySearch(1, *max_element(v.begin(), v.end()) + 10);
        cout << ans << '\n';

        v.clear();
    }

    return 0;
}
