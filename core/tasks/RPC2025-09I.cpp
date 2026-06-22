#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

// #define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0

void solve() {
    const int n = 6;
    vector<vector<int>> a(3, vector<int>(6));

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++) {
            cin >> a[i][j];
        }
    }

    auto check = [&](vector<int>& b, vector<int>& c) -> bool {
        int cnt = 0;
        int tot = 0;
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 6; j++) {
                if(b[i] == c[j]) continue;
                tot++;
                if(b[i] > c[j]) {
                    cnt++;
                }
            }
        }
        if(tot == 0) return false;
        return 2 * cnt >= tot;
    };


    for(int i = 0; i < 3; i++) {
        vector<vector<int>> other;
        for(int j = 0; j < 3; j++) {
            if(j != i) other.emplace_back(a[j]);
        }
        if(check(a[i], other[0]) && check(a[i], other[1])) {
            cout << (i + 1) << "\n";
            return;
        }
    }
    cout << "No dice\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
