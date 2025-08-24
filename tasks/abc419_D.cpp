#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

const ll BIG = ll(1e18) + 5;
void solve() {
    int n, m; cin >> n >> m;
    string S, T; cin >> S >> T;

    vector<int> diff(n + 1);
    for(int _ = 0; _ < m; _++) {
        int L, R; cin >> L >> R;
        L--; R--;
        diff[L]++;
        diff[R + 1]--;
    }

    for(int i = 1; i < n; i++) {
        diff[i] += diff[i - 1];
    }

    string re;
    for(int i = 0; i < n; i++) {
        if(diff[i] & 1) {
            re.push_back(T[i]);
        } else {
            re.push_back(S[i]);
        }
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
