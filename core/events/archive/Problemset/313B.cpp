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
    /*
        1 2 3 4 5 6
        . . . . . .
        4
        3 4 -> 1
        2 3 -> 1
        1 6 -> 5
        2 6 -> 4
    */

   /*
          0 1 2 3 4 5
          # . . # # #
        0 0 1 0 1 1
        0 0 1 1 2 3
        5
        1 3 -> 1 -> 1 - 0
        5 6 -> 1 -> 3 - 2
        1 5 -> 2 -> 2 - 0
        3 6 -> 2 -> 3 - 1
        3 4 -> 0 -> 1 - 1
    */

    string s;
    cin >> s;
    ll n = SIZE(s);

    ll eq[n-1]{0};
    // 0 1 2 3 4
    for(ll i = 0; i < n-1; i++)
        eq[i] = s[i] == s[i+1];

    ll dp[n]{0};
    // 0 1 2 3 4 5
    for(ll i = 1; i < n; i++)
        dp[i] = dp[i-1] + eq[i-1];

    ll m;
    cin >> m;

    for(ll i = 0; i < m; i++) {
        ll l, r;
        cin >> l >> r;
        assert(1 <= l && l < r && r <= n);
        cout << (dp[r-1]-dp[l-1]) << nl;
    }
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
