#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

const int INF = int(1e9) + 5;

bool vis[500 + 5][500 + 5][2];
int dist[500 + 5][500 + 5][2];

vector<int> dx{-1, +1,  0,  0};
vector<int> dy{ 0,  0, -1, +1};

// #define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0
#define RAYA   dbg("========================");

void solve() {
    int n, m; cin >> n >> m;
    vector<string> S(n); for(auto& x: S) cin >> x;

    map<char, pair<int, int>> where;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            where[S[i][j]] = {i, j};
        }
    }

    auto check = [&](int i, int j) -> bool {
        return (0 <= i && i < n) && (0 <= j && j < m);
    };

    deque<tuple<int, int, int>> q; q.emplace_back(where['S'].first, where['S'].second, 0);
    vis[where['S'].first][where['S'].second][0] = true;
    dist[where['S'].first][where['S'].second][0] = 0;

    while(!q.empty()) {
        RAYA;
        auto [i, j, active] = q.front(); q.pop_front();
        dbg(i);
        dbg(j);
        dbg(active);

        bool nxt_active = false;
        if(S[i][j] == '?') nxt_active = !active;
        else nxt_active = active;

        for(int k = 0; k < 4; k++) {
            const int ni = i + dx[k];
            const int nj = j + dy[k];

            if(
                check(ni, nj) &&
                S[ni][nj] != '#' &&
                !vis[ni][nj][nxt_active] &&
                (
                    (S[ni][nj] != 'o' && S[ni][nj] != 'x') || (nxt_active && S[ni][nj] == 'x') || (!nxt_active && S[ni][nj] == 'o')
                )
            ) {
                vis[ni][nj][nxt_active] = true;
                dist[ni][nj][nxt_active] = dist[i][j][active] + 1;
                q.emplace_back(ni, nj, nxt_active);
            }
        }
    }

    int gi = where['G'].first;
    int gj = where['G'].second;

    if(!vis[gi][gj][0] && !vis[gi][gj][1]) {
        cout << "-1\n";
        return;
    }

    int re = INF;
    if(vis[gi][gj][0]) re = min(re, dist[gi][gj][0]);
    if(vis[gi][gj][1]) re = min(re, dist[gi][gj][1]);
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
