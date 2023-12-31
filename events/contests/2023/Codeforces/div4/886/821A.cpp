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

template <typename T>
void print(vector<T>& v) {
    for(auto& e: v)
        cout << e << " ";
    cout << nl;
}

bool sumsTarget(vector<ll>& X, vector<ll>& Y, ll target) {
    for(ll i = 0; i < SIZE(X); i++) {
        for(ll j = 0; j < SIZE(Y); j++) {
            if(X[i]+Y[j]==target) {
                return true;
            }
        }
    }
    return false;
}

void solve() {
    ll n;
    cin >> n;

    ll grid[n][n];
    for(ll i = 0; i < n; i++)
        for(ll j = 0; j < n; j++)
            cin >> grid[i][j];
    
    bool ok = true;
    for(ll i = 0; i < n; i++)
        for(ll j = 0; j < n; j++) {
            if(grid[i][j] == 1) continue;
            vector<ll> colv;
            vector<ll> rowv;
            // col
            for(ll k = 0; k < n; k++) {
                if(k == i) continue;
                colv.push_back(grid[k][j]);
            }
            // row
            for(ll k = 0; k < n; k++) {
                if(k == j) continue;
                rowv.push_back(grid[i][k]);
            }

            ok &= sumsTarget(colv, rowv, grid[i][j]);
        }

    cout << (ok?"Yes":"No") << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
