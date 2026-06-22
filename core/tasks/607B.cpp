#include <bits/stdc++.h>
using namespace std;

const int INF = int(1e9) + 5;

int a[500 + 5];
bool vis[500 + 5][500 + 5];
int memo[500 + 5][500 + 5];

int dp(int l, int r) {
    if(l > r) {
        return 1;
    }

    if(vis[l][r]) return memo[l][r];
    vis[l][r] = true;

    int re = INF;
    if(a[l] == a[r]) {
        re = min(re, dp(l + 1, r - 1));
    }
    for(int mid = l; mid < r; mid++) {
        re = min(re, dp(l, mid) + dp(mid + 1, r));
    }

    return memo[l][r] = re;
}

void solve() {
    int n; cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    int re = dp(1, n);
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
