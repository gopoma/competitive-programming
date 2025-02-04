//?    ll n, m; cin >> n >> m;
//?    vpl edges(m); for(auto& [u, v]: edges) {
//?        cin >> u >> v;
//?        u--; v--;
//?    }
//?    dbg(n, m);
//?    dbg(edges);
//?    BridgeLocator G; G.init(n);
//?    for(auto& [u, v]: edges) G.ae(u, v);
//?
//?    G.find_bridges();
//?    dbg(G.bridges);

struct BridgeLocator {
    // void IS_BRIDGE(int v,int to); // some function to process the found bridge
    int n; // number of nodes
    vector<vector<int>> adj; // adjacency list of graph
    set<pi> bridges;

    vector<bool> visited;
    vector<int> tin, low;
    int timer;

    void init(int _N) {
        n = _N;
        adj.rsz(n);
    }

    void ae(int x, int y) {
		adj[x].eb(y);
        adj[y].eb(x);
    }

    void dfs(int v, int p = -1) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        bool parent_skipped = false;
        for (int to : adj[v]) {
            if (to == p && !parent_skipped) {
                parent_skipped = true;
                continue;
            }
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v])
                    IS_BRIDGE(v, to);
            }
        }
    }

    void find_bridges() {
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
    }

    void IS_BRIDGE(int v,int to) {
        // dbg("bridge", v, to);
        bridges.emplace(v, to);
        bridges.emplace(to, v);
    }
};
