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

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> g(n+1);
    unordered_map<ll, ll> degree;
    for(ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;

        degree[u]++;
        degree[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(auto& it: degree) {
        bool childrenSameDegree = true;
        ll val = degree[g[it.F][0]];
        for(auto& c: g[it.F]) {
            if(degree[c] != val) {
                childrenSameDegree = false;
                break;
            }
        }

        bool allLeafs = true;
        for(auto& c: g[it.F]) {
            for(auto& l: g[c]) {
                if(l != it.F && degree[l] != 1) {
                    allLeafs = false;
                    break;
                }
            }
        }

        if(childrenSameDegree && allLeafs) {
            cout << g[it.F].size() << " " << (g[g[it.F][0]].size() - 1) << nl;
            return;
        }
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
