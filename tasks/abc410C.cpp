#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cout << #x << ": " << x << endl;

void solve() {
    int n, q; cin >> n >> q;

    vector<int> a(n);
    for(int i = 0; i < n; i++) a[i] = i + 1;

    int f = 0;
    for(int i = 0; i < q; i++) {
        int type; cin >> type;

        if(type == 1) {
            int p, x; cin >> p >> x; p--;

            a[(f + p) % n] = x;
        } else if(type == 2) {
            int p; cin >> p; p--;

            cout << a[(f + p) % n] << "\n";
        } else {
            int k; cin >> k;

            f += k;
            f %= n;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
