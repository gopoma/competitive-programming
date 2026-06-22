#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

signed main() {
    int t; cin >> t;
    for(int _ = 0; _ < t; _++) {
        i64 a, b; cin >> a >> b;
        pair<i64, i64> K; cin >> K.first >> K.second;
        pair<i64, i64> Q; cin >> Q.first >> Q.second;

        const int n = 8;
        vector<i64> dx = {a, b, -a, -b, -a,  b,  a, -b};
        vector<i64> dy = {b, a, -b, -a,  b, -a, -b,  a};

        set<pair<i64, i64>> aux;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                pair<i64, i64> new_K = make_pair(K.first + dx[i], K.second + dy[i]);
                pair<i64, i64> new_Q = make_pair(Q.first + dx[j], Q.second + dy[j]);

                bool ok1 = new_K != K && new_K != Q;
                bool ok2 = new_Q != K && new_Q != Q;
                bool ok3 = new_K == new_Q;
                if(ok1 && ok2 && ok3) {
                    assert(new_K == new_Q);
                    aux.emplace(new_K);
                }
            }
        }

        cout << aux.size() << "\n";
    }
}
