#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    ll n, m; cin >> n >> m;

    vector<vector<pair<ll, ll>>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        ll a, b, w; cin >> a >> b >> w;

        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }

    vector<bool> vis(n + 1);
    vector<ll> dist(n + 1);
    vector<ll> parent(n + 1);

    multiset<tuple<ll, ll, ll>> ms;
    ms.emplace(0, 1, -1);
    while(!ms.empty()) {
        auto it = *ms.begin();
        auto [dmn, node, par] = it; ms.erase(ms.find(it));

        if(vis[node]) continue;
        vis[node] = true;
        parent[node] = par;
        dist[node] = dmn;

        for(auto& [nxt, d]: adj[node]) {
            ms.emplace(dmn + d, nxt, node);
        }
    }

    if(!vis[n]) {
        cout << "-1\n";
        return;
    }

    vl re;
    ll cur = n;
    while(cur != -1) {
        re.emplace_back(cur);
        cur = parent[cur];
    }
    reverse(re.begin(), re.end());

    for(auto& x: re) cout << x << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
