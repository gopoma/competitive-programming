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

typedef unsigned long long ull;
typedef long long   ll;
typedef long double ld;

const char nl = '\n';

void solve() {
    ll N;
    cin >> N;

    vector<ll> adj[N+1];
    for(ll i = 1; i <= N; i++) {
        ll A;
        cin >> A;

        adj[i].push_back(A);
    }

    vector<bool> visited(N+1, false);
    ll M = 0;
    vector<ll> B;
    vector<ll> current;

    function<void(ll)> dfs = [&](ll s) {
        if(visited[s]) {
            bool cycle = false;
            for(auto& c: current)
                cycle |= (c == s);

            if(cycle) {
                B.clear();
                for(ll i = (ll)current.size()-1; i >= 0 && current[i] != s; i--) {
                    B.push_back(current[i]);
                }
                B.push_back(s);

                reverse(ALL(B));
                M = (ll)B.size();
            }

            M = (ll)B.size();
            return;
        };
        visited[s] = true;

        // Process Node!
        current.push_back(s);

        for(auto& u: adj[s])
            dfs(u);
    };

    for(ll i = 1; i <= N; i++) {
        if(!visited[i]) {
            dfs(i);
            current.clear();
        }
    }

    cout << M << nl;
    for(auto& b: B) cout << b << " ";
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
