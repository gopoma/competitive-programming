#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for(auto& x: a) cin >> x;

    map<int, int> hist; for(auto& x: a) hist[x]++;

    int mx = -1;
    for(auto& [val, cnt]: hist) {
        if(cnt == 1) {
            mx = max(mx, val);
        }
    }
    if(mx == -1) {
        cout << "-1\n";
        return;
    }

    for(int i = 0; i < n; i++) {
        if(a[i] == mx) {
            cout << (i + 1) << "\n";
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
