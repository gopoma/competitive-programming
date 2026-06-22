#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define F first
#define S second
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';



const int bound = 2e5+13;
vector<ll> adj[bound];
const ll root = 1;
ll dp[bound];
ll deg[bound];
bool visited[bound];

void dfs(ll node) {
    visited[node] = true;

    for(auto& it: adj[node])
        if(!visited[it]) {
            dfs(it);
            dp[node] += dp[it];
        }
}

void solve() {
    ll n;
    cin >> n;


    for(ll i = 1; i <= n; i++) {
        dp[i] = deg[i] = 0;
        visited[i] = false;
        adj[i].clear();
    }



    for(ll i = 1; i <= n-1; i++) {
        ll u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);

        deg[u]++;
        deg[v]++;
    }



    for(ll i = 1; i <= n; i++)
        if(deg[i] == 1 && i != root)
            dp[i]++;

    dfs(root);



    ll q;
    cin >> q;

    for(ll i = 0; i < q; i++) {
        ll x, y;
        cin >> x >> y;

        cout << (dp[x] * dp[y]) << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
