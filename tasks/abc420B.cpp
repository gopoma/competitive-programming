#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, m; cin >> n >> m;
    vector<string> S(n); for(auto& x: S) cin >> x;

    vector<ll> dp(n);
    for(int i = 0; i < m; i++) {
        vector<ll> cnt(2);
        for(int j = 0; j < n; j++) {
            if(S[j][i] == '0') cnt[0]++;
            else cnt[1]++;
        }

        if(cnt[0] == 0 || cnt[1] == 0) {
            for(int j = 0; j < n; j++) {
                dp[j]++;
            }
        } else if(cnt[0] < cnt[1]) {
            for(int j = 0; j < n; j++) {
                if(S[j][i] == '0')
                    dp[j]++;
            }
        } else {
            for(int j = 0; j < n; j++) {
                if(S[j][i] == '1')
                    dp[j]++;
            }
        }
    }

    ll mx = *max_element(dp.begin(), dp.end());
    vector<ll> re;
    for(int i = 0; i < n; i++) if(dp[i] == mx) re.emplace_back(i);
    for(auto& x: re) cout << (x+1) << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
