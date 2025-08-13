#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cout << #x << ": " << x << endl;

void solve() {
    int n, m; cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    for(auto& [a, b, w]: edges) {
        cin >> a >> b >> w;
    }

    vector<vector<pair<int, int>>> adj(n + 1);
    for(auto& [a, b, w]: edges) {
        adj[a].emplace_back(b, w);
    }

    vector<vector<bool>> vis(n + 1, vector<bool>((1 << 10) + 5));
    vis[1][0] = true;

    deque<pair<int, int>> q; q.emplace_back(1, 0);

    while(!q.empty()) {
        auto& [src, tot] = q.front(); q.pop_front();

        for(auto& [nxt, w]: adj[src]) {
            if(!vis[nxt][tot ^ w]) {
                q.emplace_back(nxt, tot ^ w);
                vis[nxt][tot ^ w] = true;
            }
        }
    }

    for(int tot = 0; tot < (1 << 10) + 5; tot++) {
        if(vis[n][tot]) {
            cout << tot << "\n";
            return;
        }
    }
    cout << -1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
