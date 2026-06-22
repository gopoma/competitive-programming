#include <bits/stdc++.h>
using namespace std;

long long calculateVisibleWallpaperArea(int N, vector<string>& S) {
    const char EMPTY = '.';
    const char WALL  = '#';

    // Normalización
    N += 2;
    vector<string> board;
    vector<vector<bool>> vis(N, vector<bool>(N, false));
    {
        int i = 0;
        while(i < N) {
            int j = 0;

            string current_row;
            while(j < N) {
                // Upper Left
                if(make_pair(i, j) == make_pair(0, 0)) {
                    current_row.push_back(EMPTY);
                    vis[i][j] = true;
                } else if(make_pair(i, j) == make_pair(0, 1)) {
                    current_row.push_back(EMPTY);
                    vis[i][j] = true;
                } else if(make_pair(i, j) == make_pair(1, 0)) {
                    current_row.push_back(EMPTY);
                    vis[i][j] = true;
                }

                // Lower Right
                else if(make_pair(i, j) == make_pair(N - 1, N - 1)) {
                    current_row.push_back(EMPTY);
                    vis[i][j] = true;
                } else if(make_pair(i, j) == make_pair(N - 1, N - 2)) {
                    current_row.push_back(EMPTY);
                    vis[i][j] = true;
                } else if(make_pair(i, j) == make_pair(N - 2, N - 1)) {
                    current_row.push_back(EMPTY);
                    vis[i][j] = true;
                }

                // First Row
                else if(i == 0) {
                    current_row.push_back(WALL);
                    vis[i][j] = true;
                }
                // First Column
                else if(j == 0) {
                    current_row.push_back(WALL);
                    vis[i][j] = true;
                }
                // Last Row
                else if(i == N - 1) {
                    current_row.push_back(WALL);
                    vis[i][j] = true;
                }
                // Last Column
                else if(j == N - 1) {
                    current_row.push_back(WALL);
                    vis[i][j] = true;
                }

                // S
                else current_row.push_back(S[i - 1][j - 1]);

                j++;
            }
            board.emplace_back(current_row);

            i++;
        }
    } //? 12

    vector<int> dx{+1, +0, -1, +0};
    vector<int> dy{+0, +1, +0, -1};

    long long walls = 0;

    // Upper Left Flood Fill
    {
        int sr = 1;
        int sc = 1;
        deque<pair<int, int>> q; q.emplace_back(sr, sc);
        vis[sr][sc] = true;

        while(!q.empty()) {
            auto [r, c] = q.front(); q.pop_front();

            int k = 0;
            while(k < 4) {
                int new_r = r + dx[k];
                int new_c = c + dy[k];

                if((0 <= new_r && new_r < N) && (0 <= new_c && new_c < N)) {
                    walls += (board[new_r][new_c] == WALL);

                    if(!vis[new_r][new_c] && board[new_r][new_c] == EMPTY) {
                        vis[new_r][new_c] = true;
                        q.emplace_back(new_r, new_c);
                    }
                }

                k++;
            }
        }
    } //? 21

    // Lower Right Flood Fill
    {
        int sr = N - 2;
        int sc = N - 2;
        deque<pair<int, int>> q; q.emplace_back(sr, sc);

        if(!vis[sr][sc]) {
            vis[sr][sc] = true;
            while(!q.empty()) {
                auto [r, c] = q.front(); q.pop_front();

                int k = 0;
                while(k < 4) {
                    int new_r = r + dx[k];
                    int new_c = c + dy[k];

                    if((0 <= new_r && new_r < N) && (0 <= new_c && new_c < N)) {
                        walls += (board[new_r][new_c] == WALL);

                        if(!vis[new_r][new_c] && board[new_r][new_c] == EMPTY) {
                            vis[new_r][new_c] = true;
                            q.emplace_back(new_r, new_c);
                        }
                    }

                    k++;
                }
            }
        }
    } //? 31

    // Calculate Answer
    long long answer = 9LL * walls;

    return answer;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<string> S(N);

    int i = 0;
    while(i < N) {
        cin >> S[i];
        i++;
    }

    long long answer = calculateVisibleWallpaperArea(N, S);
    cout << answer << "\n";

    return 0;
}
