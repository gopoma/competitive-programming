#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

using Edge = tuple<int, int, int>;
void solve() {
    ll n, m; cin >> n >> m;

    vector<Edge> edges(m);
    for(auto& [u, v, w]: edges) {
        cin >> u >> v >> w;
        u--; v--;
    }

    vector<vector<int>> adj(n);
    vector<Edge> E;
    vector<bool> vis(n);
    deque<int> q;
    auto check = [&](int bit) -> bool {
        E.clear();

        for(int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = false;
        }

        for(auto& [u, v, w]: edges) {
            if(!bool(w & (1 << bit))) {
                E.emplace_back(u, v, w);

                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
            }
        }

        vis[0] = true;
        q.emplace_back(0);

        while(!q.empty()) {
            auto src = q.front(); q.pop_front();

            for(auto& nxt: adj[src]) {
                if(!vis[nxt]) {
                    vis[nxt] = true;
                    q.emplace_back(nxt);
                }
            }
        }

        if(vis[n - 1]) {
            swap(edges, E);

            return true;
        } else {
            return false;
        }
    };

    int re = 0;
    for(int bit = 29; bit >= 0; bit--) {
        if(!check(bit)) {
            re |= (1 << bit);
        }
    }
    cout << re << "\n";
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
