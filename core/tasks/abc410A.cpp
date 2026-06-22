#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n); for(auto& x: a) cin >> x;
    int k; cin >> k;
    int re = 0;
    for(auto& x: a) re += (x>=k);
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
