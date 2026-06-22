#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n = 7;
    vector<int> a(n); for(auto& x: a) cin >> x;
    map<int, int> hist; for(auto& x: a) hist[x]++;

    vector<int> b;
    for(auto& [val, cnt]: hist) b.emplace_back(cnt);
    sort(b.rbegin(), b.rend());

    if((b.size() >= 2) && (b[0] >= 3 && b[1] >= 2)) cout << "Yes";
    else cout << "No";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
