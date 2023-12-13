#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

void solve() {
    int n, k; cin >> n >> k;
    vector<i64> a(n); for(auto& x: a) cin >> x;

    if(k >= 3) cout << "0\n";
    else if(k == 2) {
        vector<i64> diffs;
        set<i64> fvals; for(auto& x: a) fvals.emplace(x);

        i64 ans = *min_element(a.begin(), a.end());
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                i64 diff = abs(a[i] - a[j]);
                if(diff == 0 || fvals.count(diff)) {
                    cout << "0\n";
                    return;
                }
                diffs.emplace_back(diff);
            }
        }

        for(auto& d: diffs) {
            ans = min(ans, d);
            auto left = fvals.lower_bound(d);
            auto right = fvals.upper_bound(d);

            if(left != fvals.begin() && (*left) != d) {
                left--;
                ans = min(ans, abs(d - (*left)));
            }
            if(right != fvals.end()) {
                ans = min(ans, abs(d - (*right)));
            }
        }

        cout << ans << "\n";
    } else {
        assert(k == 1);
        i64 ans = *min_element(a.begin(), a.end());
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                ans = min(ans, abs(a[i] - a[j]));
            }
        }
        cout << ans << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    for(int _ = 0; _ < t; _++) {
        solve();
    }
}
