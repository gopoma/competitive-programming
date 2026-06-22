#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const char nl = '\n';

void solve() {
    ll n; cin >> n;

    vector<ll> adj[n];
    for(ll i = 0; i < n - 1; i++) {
        ll u, v; cin >> u >> v;
        adj[u - 1].push_back(v);
    }

    queue<ll> q;
    bool visited[n] = {false};
    visited[0] = true;
    q.push(0);

    set<ll> tmp;
    tmp.insert(0);

    ll result = 0;
    while(!q.empty()) {
        result++;
        ll s = q.front(); q.pop();

        // process node s
        for(auto u: adj[s]) {
            if (visited[u]) continue;
            visited[u] = true;
            q.push(u);
            tmp.insert(u);
        }

        if(tmp.size() == n)
            break;

    }

    cout << (result - 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
