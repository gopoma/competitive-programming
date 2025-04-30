#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

#define dbg(x) cout << "Line(" << __LINE__ << "): " << #x << ": " << x << endl;
#define GA     debug(0)
#define RAYA   cout << "================================" << endl;

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    vector<vector<int>> G;
    for(int _ = 0; _ < m; _++) {
        int k; cin >> k;
        vector<int> C(k);
        for(auto& x: C) {
            cin >> x;
            x--;
        }
        G.emplace_back(C);
    }

    vector<int> B(n);
    for(auto& x: B) {
        cin >> x;
        x--;
    }

    vector<int> where(n);
    for(int i = 0; i < n; i++) {
        where[B[i]] = i;
    }

    vector<int> mx(m, 0);
    for(int i = 0; i < m; i++) {
        for(auto& x: G[i]) {
            mx[i] = max(mx[i], where[x]);
        }
    }

    vector<int> a(n + 5);
    for(int i = 0; i < m; i++) {
        a[mx[i]]++;
        a[sz(a) - 1]--;
    }
    for(int i = 1; i < sz(a); i++) {
        a[i] += a[i - 1];
    }
    for(int i = 0; i < n; i++) {
        cout << a[i] << "\n";
    }
}
