#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n; cin >> n;
    vector<int> a(n);
    for(auto& x: a) cin >> x;

    bool has1 = any_of(a.begin(), a.end(), [](const int& x) { return x == 1; });
    if(has1) cout << -1;
    else cout << 1;
    cout << "\n";
}
