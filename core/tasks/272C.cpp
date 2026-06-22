#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<long long> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    assert(is_sorted(a.begin(), a.end()));

    int m;
    cin >> m;

    long long ans = 0LL;
    for(int _ = 0; _ < m; _++) {
        long long w, h;
        cin >> w >> h;

        ans = max(ans, a[w]);

        cout << ans << "\n";

        ans += h;
    }
}
