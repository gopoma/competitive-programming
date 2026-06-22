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

ll n;
const int MAXN = 110;
ll board[MAXN][MAXN];

bool ok(ll x, ll y) {
    return (0 <= x && x < n &&
        0 <= y && y < n);
}

void solve() {
    cin >> n;

    if(n == 2) {
        cout << "-1\n";
        cout << nl;
    } else {
        bool odd = n%2==1;
        ll cnt = 1;
        for(ll i=0; i<n; i+=2) {
            ll x = i, y = 0;
            while(ok(x, y)) {
                board[x][y] = cnt++;
                x--;
                y++;
            }
        }

        for(ll i=odd?2:1; i<n; i+=2) {
            ll x=n-1, y=i;
            while(ok(x, y)) {
                board[x][y] = cnt++;
                x--;
                y++;
            }
        }

        for(ll i=1; i<n; i+=2) {
            ll x = i, y = 0;
            while(ok(x, y)) {
                board[x][y] = cnt++;
                x--;
                y++;
            }
        }

        for(ll i=odd?1:2; i<n; i+=2) {
            ll x=n-1, y=i;
            while(ok(x, y)) {
                board[x][y] = cnt++;
                x--;
                y++;
            }
        }

        for(ll i=0; i<n; i++) {
            for(ll j=0; j<n; j++) {
                cout << board[i][j] << " ";
            }
            cout << nl;
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
