#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    ll X, Y; cin >> X >> Y;
    vl dp(10 + 1);
    dp[1] = X;
    dp[2] = Y;
    for(int i = 3; i <= 10; i++) {
        ll cur = dp[i - 1] + dp[i - 2];
        string temp = to_string(cur);
        reverse(temp.begin(), temp.end());
        cur = stoll(temp);
        dp[i] = cur;
    }
    cout << dp[10] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);

    solve();

    return 0;
}

