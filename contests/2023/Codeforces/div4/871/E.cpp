#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

using ll = long long;

void solve() {
    ll n, m;
    cin >> n >> m;

    ll mtx[n][m];
    bool vis[n][m];

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < m; j++) {
            mtx[i][j] = 0;
        }
    }

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < m; j++) {
            vis[i][j] = false;
        }
    }

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < m; j++) {
            cin >> mtx[i][j];
        }
    }

    // Direction vectors
    ll dRow[] = { -1, 0, 1,  0 };
    ll dCol[] = {  0, 1, 0, -1 };

    ll maxArea = 0;

    for(ll r = 0; r < n; r++) {
        for(ll s = 0; s < m; s++) {
            if(!vis[r][s] && mtx[r][s] != 0) {            
                queue<pair<ll, ll>> q;

                q.push({r, s});
                vis[r][s] = true;

                ll area = 0;

                while(!q.empty()) {
                    pair<ll, ll> cell = q.front();
                    ll x = cell.first;
                    ll y = cell.second;

                    area += mtx[x][y];

                    q.pop();

                    for(ll i = 0; i < 4; i++) {
                        ll adjx = x + dRow[i];
                        ll adjy = y + dCol[i];

                        if(!(adjx < 0 || adjy < 0 || adjx >= n || adjy >= m || vis[adjx][adjy] || mtx[adjx][adjy] == 0)) {
                            q.push({ adjx, adjy });
                            vis[adjx][adjy] = true;
                        }
                    }
                }           

                maxArea = max(maxArea, area);
            }
        }
    }

    cout << maxArea << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
