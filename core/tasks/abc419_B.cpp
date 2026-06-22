#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    int q; cin >> q;
    multiset<int> ms;
    while(q--) {
        int type; cin >> type;
        if(type == 1) {
            int x; cin >> x;
            ms.emplace(x);
        } else {
            int re = *ms.begin();
            ms.erase(ms.find(re));
            cout << re << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
