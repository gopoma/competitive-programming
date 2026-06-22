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

ll n, m;
ll okRow(ll x) { return 1 <= x && x <= n; }
ll okCol(ll y) { return 1 <= y && y <= m; }
ll countPossibles(ll x, ll y) {
    ll res = 0;
    // (x-1,y) (x,y-1) (x+1,y) (x,y+1)
    res += okRow(x-1);
    res += okCol(y-1);
    res += okRow(x+1);
    res += okCol(y+1);
    return res;
}

void solve() {
    cin >> n >> m;

    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    cout << min(countPossibles(x1, y1), countPossibles(x2, y2)) << nl;
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
