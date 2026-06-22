#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

const ll BIG = ll(1e18) + 5;
void solve() {
    ll n; cin >> n;
    vector<pair<ll, ll>> a(n);
    for(auto& [x, y]: a) cin >> x >> y;

    vector<pair<ll, ll>> b;

    auto inter = [&](ll L1, ll R1, ll L2, ll R2) -> pair<bool, pair<ll, ll>> {
        assert(L1 <= R1);
        assert(L2 <= R2);
        if(L1 > L2) {
            swap(L1, L2);
            swap(R1, R2);
        }

        if(R1 < L2) return {false, {BIG, BIG}};

        ll L = max(L1, L2);
        ll R = min(R1, R2);

        return {true, {L, R}};
    };

    auto check = [&](ll middle) -> bool {
        ll cur_xl = 1;
        ll cur_xr = ll(1e9);

        ll cur_yl = 1;
        ll cur_yr = ll(1e9);

        for(auto& [x, y]: a) {
            ll xl = max(1LL, x - middle);
            ll xr = min(x + middle, ll(1e9));

            ll yl = max(1LL, y - middle);
            ll yr = min(y + middle, ll(1e9));

            auto [ok, it] = inter(xl, xr, cur_xl, cur_xr);
            auto [ok2, it2] = inter(yl, yr, cur_yl, cur_yr);

            if(!(ok && ok2)) return false;

            cur_xl = it.first;
            cur_xr = it.second;
            cur_yl = it2.first;
            cur_yr = it2.second;
        }

        return true;
    };

    ll left = -1; // always bad
    ll right = ll(1e9) + 5; // always good
    while(left + 1 < right) {
        ll middle = (left + right) >> 1LL;
        if(check(middle)) right = middle;
        else left = middle;
    }
    cout << right << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
