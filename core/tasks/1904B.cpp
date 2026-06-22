#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

signed main() {
    int t; cin >> t;
    for(int _ = 0; _ < t; _++) {
        int n; cin >> n;
        vector<i64> a(n); for(auto& x: a) cin >> x;
        vector<i64> a_original = a;

        sort(a.begin(), a.end());

        vector<i64> pref(n);
        pref[0] = a[0];
        for(int i = 1; i < n; i++) pref[i] = pref[i - 1] + a[i];

        set<int> marked;
        for(int i = 0; i < n - 1; i++) {
            if(pref[i] < a[i + 1]) {
                marked.emplace(i);
            }
        }

        map<i64, int> res;
        for(int i = 0; i < n; i++) {
            auto left = marked.lower_bound(i);
            if(left == marked.end()) {
                res[a[i]] = n - 1;
            } else {
                res[a[i]] = *left;
            }
        }

        for(auto& x: a_original) cout << res[x] << " ";
        cout << "\n";
    }
}
