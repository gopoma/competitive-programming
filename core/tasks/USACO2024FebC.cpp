#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

//? void solve() {
//?     int N, Q;
//?     cin >> N >> Q;
//?
//?     vector<int> c(N); for(auto& x: c) cin >> x;
//?     vector<int> t(N); for(auto& x: t) cin >> x;
//?
//?     for(int _ = 0; _ < Q; _++) {
//?         int V, S; cin >> V >> S;
//?
//?         int mx = 0;
//?         for(int i = 0; i < N; i++)
//?             mx += ((t[i] + S) < c[i]);
//?
//?         if(V <= mx) cout << "YES";
//?         else cout << "NO";
//?
//?         cout << "\n";
//?     }
//? }

void solve() {
    int N, Q;
    cin >> N >> Q;

    vector<int> c(N); for(auto& x: c) cin >> x;
    vector<int> t(N); for(auto& x: t) cin >> x;

    map<int, int> mx;
    int bad = -1;
    for(int inc = 1;; inc++) {
        int cnt = 0;

        for(int i = 0; i < N; i++) {
            cnt += (t[i] + inc < c[i]);
        }

        if(cnt == 0) {
            bad = inc;
            break;
        } else {
            mx[inc] = cnt;
        }
    }
    assert(bad != -1);

    for(int _ = 0; _ < Q; _++) {
        int V, S; cin >> V >> S;

        if(S >= bad) cout << "NO";
        else {
            assert(1 <= S && S < bad);
            if(V <= mx[S]) cout << "YES";
            else cout << "NO";
        }
        cout << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
