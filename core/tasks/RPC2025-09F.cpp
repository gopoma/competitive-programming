#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

// #define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0

const int INF = int(1e9) + 5;
void solve() {
    int n, l, k; cin >> n >> l >> k;

    int dist[k][n];
    string id[n];

    int a[n][l];
    for(int i = 0; i < n; i++) {
        cin >> id[i];
        for(int j = 0; j < l; j++) {
            cin >> a[i][j];
        }
    }

    int p1 = -1;
    { // most distant from the first protein in the list
        int mx = -INF;
        for(int i = 0; i < n; i++) {
            int d = 0;
            for(int j = 0; j < l; j++) {
                // from x to y: d += abs(a[x][i] - a[y][i]);
                d += abs(a[i][j] - a[0][j]);
            }

            if(d > mx) {
                p1 = i;
                mx = d;
            }
        }
    }
    assert(p1 != -1);
    dbg(p1);
    cout << id[p1] << "\n";



    int cur_id = 0;
    {
        for(int i = 0; i < n; i++) {
            int d = 0;
            for(int j = 0; j < l; j++) {
                // from x to y: d += abs(a[x][i] - a[y][i]);
                d += abs(a[i][j] - a[p1][j]);
            }
            dist[cur_id][i] = d;
        }
        cur_id++;
    }



    for(int i = 1; i < k; i++) {
        int p_cur = -1;
        int gmx = -INF;

        for(int j = 0; j < n; j++) {
            int mx = INF;

            for(int p = 0; p < cur_id; p++) {
                int d = dist[p][j];

                mx = min(mx, d);
            }

            if(gmx < mx) {
                p_cur = j;
                gmx = mx;
            }
        }
        assert(p_cur != -1);

        cout << id[p_cur] << "\n";



        for(int x = 0; x < n; x++) {
            int d = 0;
            for(int y = 0; y < l; y++) {
                d += abs(a[x][y] - a[p_cur][y]);
            }
            dist[cur_id][x] = d;
        }
        cur_id++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
