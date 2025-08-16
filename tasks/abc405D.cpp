#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

// #define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0

void solve() {
    ll n, m; cin >> n >> m;
    vector<string> S(n);
    for(auto& x: S) cin >> x;

    auto check = [&](ll i, ll j) -> bool {
        return (0 <= i && i <  n) && (0 <= j && j < m);
    };

    deque<pair<ll, ll>> q;
    vector<vector<bool>> vis(n, vector<bool>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(S[i][j] == 'E') {
                q.emplace_back(i, j);
                vis[i][j] = true;
            }
        }
    }

    vector<pair<pair<ll, ll>, char>> trans;
    trans.emplace_back(make_pair(-1LL, 0LL), 'v');
    trans.emplace_back(make_pair(0LL, +1LL), '<');
    trans.emplace_back(make_pair(+1LL, 0LL), '^');
    trans.emplace_back(make_pair(0LL, -1LL), '>');

    while(!q.empty()) {
        auto [i, j] = q.front(); q.pop_front();

        for(auto& [dir, c]: trans) {
            auto& [dx, dy] = dir;

            ll ni = i + dx;
            ll nj = j + dy;
            if(check(ni, nj) && S[ni][nj] == '.' && !vis[ni][nj]) {
                vis[ni][nj] = true;
                S[ni][nj] = c;
                q.emplace_back(ni, nj);
            }
        }
    }

    dbg("res");
    for(auto& x: S) cout << x << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
