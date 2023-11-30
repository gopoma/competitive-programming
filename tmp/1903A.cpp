#include <bits/stdc++.h>

using namespace std;

signed main() {
    long long t;
    cin >> t;

    while(t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n);
        for(auto& x: a) cin >> x;

        if(k == 1 && !is_sorted(a.begin(), a.end())) cout << "NO\n";
        else cout << "YES\n";
    }
}
