#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    vector<ll> list = {-18, 1, 10, 4, 7, -1};
    const ll target = 0;

    set<ll> tmp;
    for(auto ee: list) {
        const ll cc = target - ee;

        if(tmp.count(cc) != 0) {
            cout << cc << " " << ee << "\n";
            return;
        } else {
            tmp.insert(ee);
        }
    }

    cout << "Not Found\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
