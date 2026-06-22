#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        vector<vector<long long>> M(n, vector<long long>(n));
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> M[i][j];

        const int MAX = (1 << 30) - 1;
        vector<long long> a(n, MAX);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                a[i] &= M[i][j];
            }
        }

        bool ok = true;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                ok &= ((a[i] | a[j]) == M[i][j]);
            }
        }

        if(!ok) cout << "NO\n";
        else {
            cout << "YES\n";
            for(auto& x: a) cout << x << " ";
            cout << "\n";
        }
    }
}
