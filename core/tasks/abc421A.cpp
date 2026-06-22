#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    int n; cin >> n;
    vector<string> S(n);
    for(auto& x: S) cin >> x;
    int X; cin >> X;
    string Y; cin >> Y;
    X--;
    cout << ((S[X] == Y)?"Yes":"No") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);

    solve();

    return 0;
}

