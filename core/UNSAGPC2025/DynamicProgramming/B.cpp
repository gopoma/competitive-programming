#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

const ll BIG = ll(1e18);

ll caso = 0;
void solve() {
    caso++;
    ll n; cin >> n;
    vl a(n); for(int i = 1; i < n; i++) cin >> a[i];
    vl pref = a;

    for(int i = 1; i < n; i++) {
        pref[i] += pref[i - 1];
    }

    pl mn = make_pair(pref[0], 0);
    tuple<ll, ll, ll> res = make_tuple(0, 0, BIG);
    for(ll i = 1; i < n; i++) {
        auto [mn_pref_left, l] = mn;
        ll current_sum = pref[i] - mn_pref_left;

        assert(l <= i);
        res = max(res, make_tuple(current_sum, i - l + 1, -l));

        mn = min(mn, make_pair(pref[i], i));
    }

    auto [mx_sum, mx_length, l] = res;
    l = -l;

    if(mx_sum == 0) {
        cout << "Route " << caso << " has no nice parts\n";
        return;
    }

    cout << "The nicest part of route " << caso << " is between stops ";
    ll r = l + mx_length - 1;
    cout << (l + 1) << " and " << (r + 1) << "\n";
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
