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
    ll N, M;
    cin >> N >> M;

    string C[N];
    for(auto& c: C) cin >> c;

    string D[M];
    for(auto& d: D) cin >> d;
    ll P[M+1];
    for(auto& p: P) cin >> p;

    unordered_set<string> registry;
    unordered_map<string, ll> prices;
    for(ll i = 0; i < M; i++) {
        registry.insert(D[i]);
        prices[D[i]] = P[i+1];
    }

    ll ans = 0;
    for(auto& c: C) {
        if(!registry.count(c)) ans += P[0];
        else ans += prices[c];
    }
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
