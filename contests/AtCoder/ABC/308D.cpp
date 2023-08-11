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

// Direction vectors
ll dRow[] = { -1, 0, 1,  0 };
ll dCol[] = {  0, 1, 0, -1 };

bool inBounds(ll x, ll y, ll boundx, ll boundy) {
    return x >= 0 && y >= 0 && x < boundx && y < boundy;
}

bool candidate(char current, char parent) {
    return (parent == 's' && current == 'n') ||
    (parent == 'n' && current == 'u') ||
    (parent == 'u' && current == 'k') ||
    (parent == 'k' && current == 'e') ||
    (parent == 'e' && current == 's');
}

void solve() {
    ll H, W;
    cin >> H >> W;

    char grid[H][W];
    bool vis[H][W];

    for(ll i = 0; i < H; i++)
        for(ll j = 0; j < W; j++)
            vis[i][j] = false;

    for(ll i = 0; i < H; i++)
        for(ll j = 0; j < W; j++)
            cin >> grid[i][j];

    if(grid[0][0] != 's') {
        cout << "No\n";
        return;
    }

    queue<pair<ll, ll>> q;

    q.push({0, 0});
    vis[0][0] = true;

    bool ok = false;

    while(!q.empty()) {
        pair<ll, ll> cell = q.front();
        ll x = cell.first;
        ll y = cell.second;

        q.pop();

        if(x == H-1 && y == W-1) {
            ok = true;
            break;
        }

        for(ll i = 0; i < 4; i++) {
            ll adjx = x + dRow[i];
            ll adjy = y + dCol[i];

            if(inBounds(adjx, adjy, H, W) && !vis[adjx][adjy] && candidate(grid[adjx][adjy], grid[x][y])) {
                q.push({ adjx, adjy });
                vis[adjx][adjy] = true;
            }
        }
    }

    cout << (ok?"Yes":"No") << "\n";
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
