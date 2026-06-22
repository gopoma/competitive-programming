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
    ll n, k;
    cin >> n >> k;

    ll board[n][n];
    for(ll r = 0; r < n; r++)
        for(ll c = 0; c < n; c++)
            cin >> board[r][c];

    ll diffs = 0;
    for(ll r = 0; r < n/2; r++)
        for(ll c = 0; c < n; c++)
            diffs += (board[r][c] != board[n-r-1][n-c-1]);

    if(n%2!=0) {
        for(ll c = 0; c < n/2; c++)
            diffs += (board[n/2][c] != board[n/2][n-c-1]);
    }

    k-=diffs;
    if(k<0) {
        cout << "NO\n";
        return;
    }

    if((n%2!=0) || k%2==0) cout << "YES\n";
    else cout << "NO\n";
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
