#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e6;

void solve() {
    int n, A, B, a0;
    cin >> n >> A >> B >> a0;



    vector<int> cnt(1e6, 0); // frecuencia de cada valor

    int current = ((long long)A * a0 + B) % MOD + 1;
    cnt[current]++;

    for(int i = 1; i < n; i++) {
        current = ((long long)A * current + B) % MOD + 1;
        cnt[current]++;
    }

    for(int x = 0; x <= 1e6; x++)
        if(cnt[x] != 0)
            while(cnt[x] != 0) {
                cout << x << " ";
                cnt[x]--;
            }
    cout << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
