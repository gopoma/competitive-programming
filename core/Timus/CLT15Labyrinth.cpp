#include <bits/stdc++.h>
using namespace std;

long long calculateVisibleWallpaperArea(int N, vector<string>& S) {
    const char EMPTY = '.';
    const char WALL  = '#';

    // Normalización
    vector<string> board;
    vector<vector<bool>> vis(N + 2, vector<bool>(N + 2));

    string top = string(2, EMPTY) + string(N, WALL);
    board.emplace_back(top);

    for(int i = 0; i < N; i++) {
        string current_layer;

        if(i == 0) current_layer.push_back(EMPTY);
        else current_layer.push_back(WALL);

        for(int j = 0; j < N; j++) {
            current_layer.push_back(S[i][j]);
        }

        if(i == N - 1) current_layer.push_back(EMPTY);
        else current_layer.push_back(WALL);

        board.emplace_back(current_layer);

        vis[i + 1][0] = true;
        vis[0][i + 1] = true;
        vis[N + 1][i + 1] = true;
        vis[i + 1][N + 1] = true;
    }

    string down = top; reverse(down.begin(), down.end());
    board.emplace_back(down);

    N += 2;

    vis[0][0]         = true;
    vis[0][N - 1]     = true;
    vis[N - 1][0]     = true;
    vis[N - 1][N - 1] = true;



    long long walls = 0;

    vector<int> dx{+1, +0, -1, -0};
    vector<int> dy{+0, +1, -0, -1};

    vector<pair<int, int>> starts;
    starts.emplace_back(1, 1);
    starts.emplace_back(N - 2, N - 2);

    for(size_t i = 0; i < starts.size(); i++) {
        auto [sr, sc] = starts[i];
        if(!vis[sr][sc]) {
            deque<pair<int, int>> q; q.emplace_back(sr, sc);
            vis[sr][sc] = true;

            while(!q.empty()) {
                auto [r, c] = q.front(); q.pop_front();

                for(int k = 0; k < 4; k++) {
                    int new_r = r + dx[k];
                    int new_c = c + dy[k];

                    if(new_r == clamp(new_r, 0, N - 1) && new_c == clamp(new_c, 0, N - 1)) {
                        if(board[new_r][new_c] == WALL) {
                            walls++;
                        }

                        if(!vis[new_r][new_c] && board[new_r][new_c] == EMPTY) {
                            vis[new_r][new_c] = true;
                            q.emplace_back(new_r, new_c);
                        }
                    }
                }
            }
        }
    }



    long long answer = 9LL * walls;
    return answer;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<string> S(N);

    for(auto& x: S) cin >> x;

    long long answer = calculateVisibleWallpaperArea(N, S);
    cout << answer << "\n";
}
