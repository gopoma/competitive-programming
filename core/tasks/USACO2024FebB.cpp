#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

void solve() {
    int N; cin >> N;
    long long M; cin >> M;
    string S; cin >> S;
    vector<long long> a(N); for(auto& x: a) cin >> x;

    bool all_eq = true;
    char bg = S.front();
    for(auto& c: S) all_eq &= (c == bg);

    long long sum = accumulate(a.begin(), a.end(), 0LL);

    if(all_eq) cout << sum << "\n";
    else {
        vector<bool> loop(N, false);
        for(int i = 0; i < N - 1; i++) {
            if(S[i] == 'R' && S[i + 1] == 'L') {
                loop[i] = true;
                loop[i + 1] = true;
            }
        }
        if(S[0] == 'L' && S[N - 1] == 'R') {
            loop[0] = true;
            loop[N - 1] = true;
        }

        auto prev = [&](int xx) {
            xx--;
            if(xx < 0) xx += N;
            return xx;
        };

        int start = 0;
        while(S[prev(start)] == S.front()) {
            start = prev(start);
        }

        vector<long long> go;
        vector<bool> vis(N, false);
        long long current_sum = 0;
        char xd = S[start];
        for(int i = start; i < 2 * N; i++) {
            int idx = i % N;
            if(vis[idx]) break;
            else {
                vis[idx] = true;

                if(loop[idx]) {
                    go.emplace_back(current_sum);
                    current_sum = 0;
                } else {
                    if(S[idx] == xd) {
                        current_sum += a[idx];
                    } else {
                        go.emplace_back(current_sum);
                        current_sum = a[idx];

                        xd = S[idx];
                    }
                }
            }
        }
        go.emplace_back(current_sum);

        for(auto& xx: go) {
            sum -= min(xx, M);
        }
        cout << sum << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
