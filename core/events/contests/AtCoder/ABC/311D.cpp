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

    char grid[N][M];
    for(ll i = 0; i < N; i++)
        for(ll j = 0; j < M; j++)
            cin >> grid[i][j];

    unordered_set<pair<ll, ll>> ans;

    bool visited[N][M];
    for(ll i = 0; i < N; i++)
        for(ll j = 0; j < M; j++)
            visited[i][j] = false;
    queue<pair<ll, ll>> q;
    queue<pair<<pair<ll, ll>, char>> dd;
    q.push({1, 1});
    vis[1][1] = true;

    bool left = false, up = false, right = true, down = true;
    while(!q.empty()) {
        pair<ll, ll> cell = q.front();
        ll x = cell.first;
        ll y = cell.second;
        q.pop();

        pair<pair<ll, ll>, char> dir = dd.front();
        if(dir.first.first == x && dir.first.second == y) {
            left = left || dir.second;
            up = up || dir.second;
            right = right || dir.second;
            down = down || dir.second;
        }

        // Direction vectors
        ll dRow[] = { -1, 0, 1,  0 };
        ll dCol[] = {  0, 1, 0, -1 };

        // [1] - LEFT
        if(left) {
            ll adjx = x + dRow[0];
            ll adjy = y + dCol[0];

            if(!(adjx < 0 || adjy < 0 || adjx >= N || adjy >= M || vis[adjx][adjy] || mtx[adjx][adjy] == '#')) {
                q.push({ adjx, adjy });
                dd.push_back({ { adjx, adjy }, 'L' });
                vis[adjx][adjy] = true;
            }

            left = false;
        }
        // [2] - UP
        if(up) {
            ll adjx = x + dRow[1];
            ll adjy = y + dCol[1];

            if(!(adjx < 0 || adjy < 0 || adjx >= N || adjy >= M || vis[adjx][adjy] || mtx[adjx][adjy] == '#')) {
                q.push({ adjx, adjy });
                dd.push_back({ { adjx, adjy }, 'U' });
                vis[adjx][adjy] = true;
            }

            up = false;
        }
        // [3] - RIGHT
        if(right) {
            ll adjx = x + dRow[2];
            ll adjy = y + dCol[2];

            if(!(adjx < 0 || adjy < 0 || adjx >= N || adjy >= M || vis[adjx][adjy] || mtx[adjx][adjy] == '#')) {
                q.push({ adjx, adjy });
                dd.push_back({ { adjx, adjy }, 'R' });
                vis[adjx][adjy] = true;
            }

            right = false;
        }
        // [4] - DOWN
        if(down) {
            ll adjx = x + dRow[3];
            ll adjy = y + dCol[3];

            if(!(adjx < 0 || adjy < 0 || adjx >= N || adjy >= M || vis[adjx][adjy] || mtx[adjx][adjy] == '#')) {
                q.push({ adjx, adjy });
                dd.push_back({ { adjx, adjy }, 'D' });
                vis[adjx][adjy] = true;
            }

            down = false;
        }
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
