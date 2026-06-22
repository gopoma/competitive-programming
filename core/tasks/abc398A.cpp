#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;

    string re(n, '-');
    if(n & 1) re[n / 2] = '=';
    else {
        re[n / 2] = '=';
        re[(n / 2) - 1] = '=';
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
