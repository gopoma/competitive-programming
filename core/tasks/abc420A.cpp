#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll X, Y; cin >> X >> Y;
    Y--;
    X += Y;
    X %= 12;
    X++;
    cout << X << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
