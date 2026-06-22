#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q; cin >> n >> q;

    vector<int> cnt(n + 1);
    set<pair<int, int>> S;
    for(int i = 1; i <= n; i++) {
        S.emplace(cnt[i], i);
    }

    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        if(x == 0) {
            auto it = *S.begin();
            auto [_, id] = it; S.erase(it);

            cout << id << " ";

            S.erase(make_pair(cnt[id], id));

            cnt[id]++;

            S.emplace(cnt[id], id);
        } else {
            int id = x;
            cout << id << " ";

            S.erase(make_pair(cnt[id], id));

            cnt[id]++;

            S.emplace(cnt[id], id);
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
