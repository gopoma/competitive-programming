#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

#define dbg(x) cout << #x << ": " << x << endl;
// #define dbg(x) 0

void solve() {
    ll R, X; cin >> R >> X;

    if(X == 1) {
        if(1600 <= R && R <= 2999) cout << "Yes";
        else cout << "No";
    } else {
        if(1200 <= R && R <= 2399) cout << "Yes";
        else cout << "No";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
