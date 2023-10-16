// sometimes pragmas don't work
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> A(N + 1, vector<int>(N + 1, 0));
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> A[i][j];
        }
    }

    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1] + A[i][j];
        }
    }

    auto query = [&](int x1, int y1, int x2, int y2) {
        return dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1];
    };

    int ans = INT_MIN;
    for(int x1 = 1; x1 <= N; x1++) {
        for(int x2 = x1; x2 <= N; x2++) {
            for(int y1 = 1; y1 <= N; y1++) {
                for(int y2 = y1; y2 <= N; y2++) {
                    assert(x1 <= x2 && y1 <= y2);
                    ans = max(ans, query(x1, y1, x2, y2));
                }
            }
        }
    }

    cout << ans << "\n";
}
