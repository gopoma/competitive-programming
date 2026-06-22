#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for(int _ = 0; _  < t; _++) {
        int n;
        cin >> n;
        assert(2 <= n);

        vector<int> a(n);
        for(auto& e: a) {
            cin >> e;
        }

        int left = 0, right = 1000000000;
        for(int i = 0; i < n - 1; i++) {
            if(a[i] > a[i + 1]) {
                left = max(left, int(ceil((a[i] + a[i + 1]) / 2.0)));
            } else if(a[i] < a[i + 1]) {
                right = min(right, int(floor((a[i] + a[i + 1]) / 2.0)));
            }
        }

        if(left <= right) {
            cout << left << "\n";
        } else {
            cout << "-1\n";
        }
    }
}
