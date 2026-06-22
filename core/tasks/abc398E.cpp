
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

#define dbg(x) cout << #x << ": " << x << endl;

void solve() {
    ll n; cin >> n;
    vector<vector<ll>> adj(n);
    vector<vector<bool>> already(n, vector<bool>(n));

    for(int i = 0; i < n - 1; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);

        already[u][v] = already[v][u] = true;
    }

    vector<vector<ll>> dist(n, vector<ll>(n));
    deque<ll> q;
    vector<bool> vis(n);
    vector<ll> d(n);
    for(int src = 0; src < n; src++) {
        for(int u = 0; u < n; u++) {
            vis[u] = false;
        }

        q.emplace_back(src);
        vis[src] = true;
        d[src] = 0;
        dist[src][src] = 0;
        while(!q.empty()) {
            auto cur = q.front(); q.pop_front();
            for(auto& nxt: adj[cur]) {
                if(!vis[nxt]) {
                    vis[nxt] = true;
                    d[nxt] = d[cur] + 1;
                    dist[src][nxt] = dist[nxt][src] = d[nxt];
                    q.emplace_back(nxt);
                }
            }
        }
    }

    set<pair<ll, ll>> E;
    for(int u = 0; u < n; u++) {
        for(int v = u + 1; v < n; v++) {
            if(!already[u][v] && (dist[u][v] & 1)) {
                E.emplace(u + 1, v + 1);
            }
        }
    }

    int N = E.size();
    if(N % 2 == 0) {
        // should choose Second
        cout << "Second" << endl;

        while(true) {
            ll i, j; cin >> i >> j;
            if(i == -1 && j == -1) {
                return;
            }
            E.erase(E.find({i, j}));

            auto [x, y] = *E.begin();
            cout << x << " " << y << endl;
            E.erase(E.find({x, y}));
        }
    } else {
        // should choose First
        cout << "First" << endl;
        while(true) {
            auto [x, y] = *E.begin();
            cout << x << " " << y << endl;
            E.erase(E.find({x, y}));

            ll i, j; cin >> i >> j;
            if(i == -1 && j == -1) {
                return;
            }
            E.erase(E.find({i, j}));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
