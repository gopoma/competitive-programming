#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    const int n = 3;
    vector<long long> a(n);
    for(auto& e: a) cin >> e;

    long long ans = 0;
    for(int i = 0; i <= min(2, int(*min_element(a.begin(), a.end()))); i++) {
        vector<long long> temp = a;

        long long local_ans = i;
        for(auto& e: temp) e -= i;

        for(auto& e: temp) local_ans += e / 3;
        ans = max(ans, local_ans);
    }
    cout << ans << "\n";
}
