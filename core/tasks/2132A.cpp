#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string a; cin >> a;

    int m; cin >> m;
    string b, c; cin >> b >> c;

    deque<char> q;
    for(auto& x: a) q.emplace_back(x);

    for(int i = 0; i < m; i++) {
        if(c[i] == 'V') {
            q.push_front(b[i]);
        } else {
            q.push_back(b[i]);
        }
    }

    for(auto& x: q) cout << x;
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
