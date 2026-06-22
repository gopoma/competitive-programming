#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long T; cin >> T;
    while(T--) {
        long long n, m; cin >> n >> m;
        long long A = ((m - 1LL) * m) >> 1LL;
        long long L = m - n;
        long long B = ((L - 1LL) * L) >> 1LL;
        long long ans = A - B;
        cout << ans << "\n";
    }

    return 0;
}
