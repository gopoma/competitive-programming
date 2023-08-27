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

const int bound = 100012;
vector<ll> adj[bound];
bool visited[bound];
bool cats[bound];
const int root = 1;

void dfs(ll s, ll current, ll m, ll* count) {
    if(visited[s]) return;
    visited[s] = true;

    // process node
    if(current + cats[s] > m) return;
    if(!cats[s]) current = 0;

    if(s != root && adj[s].size() == 1) (*count)++;

    for(auto& u: adj[s])
        dfs(u, current + cats[s], m, count);
}

void solve() {
    ll n, m;
    cin >> n >> m;



    for(ll i = 1; i <= n; i++) {
        adj[i].clear();
        visited[i] = false;
        cats[i] = false;
    }



    for(ll i = 1; i <= n; i++) {
        cin >> cats[i];
    }

    for(ll i = 1; i <= n-1; i++) {
        ll x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    ll count = 0;
    dfs(root, 0, m, &count);

    cout << count << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
