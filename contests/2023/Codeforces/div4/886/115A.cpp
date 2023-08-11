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
    int n; cin >> n;
    vector<int> adj[n+1];
    vector<int> roots;

    for(int i = 1; i <= n; i++) {
        int p; cin >> p;
        if(p == -1) {
            roots.push_back(i);
        } else {
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
    }

    bool visited[n+1]{false};
    function<int(int)> height = [&](int s) {
        if(visited[s]) return 0;
        visited[s] = true;
 
        int res = 1;
        for(auto& u: adj[s])
            res = max(res, height(u)+1);

        return res;
    };

    int ans = 1;
    for(int& r: roots)
        ans = max(ans, height(r));

    cout << ans << nl;
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
