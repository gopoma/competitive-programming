#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for(int _ = 0; _ < t; _++) {
        int n; cin >> n;
        string S; cin >> S;

        bool all_zeros = true;
        for(auto& x: S) all_zeros &= (x == '0');
        if(
            all_zeros
            || S.find("10") != string::npos
            || S.find("01") != string::npos
        ) cout << "YES";
        else cout << "NO";
        cout << "\n";
    }
}
