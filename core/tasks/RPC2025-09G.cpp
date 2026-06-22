#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct Hashing {
  vector<vector<int>> hs;
  vector<int> PWX, PWY;
  int n, m;
  static const int PX = 3731,  PY = 2999, mod = 998244353;
  Hashing() {}
  Hashing(vector<string>& s) {
    n = (int)s.size(), m = (int)s[0].size();
    hs.assign(n + 1, vector<int>(m + 1, 0));
    PWX.assign(n + 1, 1);
    PWY.assign(m + 1, 1);
    for (int i = 0; i < n; i++) PWX[i + 1] = 1LL * PWX[i] * PX % mod;
    for (int i = 0; i < m; i++) PWY[i + 1] = 1LL * PWY[i] * PY % mod;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        hs[i + 1][j + 1] = s[i][j] - 'a' + 1;
      }
    }
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < m; j++) {
        hs[i][j + 1] = (hs[i][j + 1] + 1LL * hs[i][j] * PY % mod) % mod;
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= m; j++) {
        hs[i + 1][j] = (hs[i + 1][j] + 1LL * hs[i][j] * PX % mod) % mod;
      }
    }
  }
  int get_hash(int x1, int y1, int x2, int y2) { // 1-indexed
    assert(1 <= x1 && x1 <= x2 && x2 <= n);
    assert(1 <= y1 && y1 <= y2 && y2 <= m);
    x1--;
    y1--;
    int dx = x2 - x1, dy = y2 - y1;
    return (1LL * (hs[x2][y2] - 1LL * hs[x2][y1] * PWY[dy] % mod + mod) % mod -
        1LL * (hs[x1][y2] - 1LL * hs[x1][y1] * PWY[dy] % mod + mod) % mod * PWX[dx] % mod + mod) % mod;
  }
  int get_hash() {
    return get_hash(1, 1, n, m);
  }
};

// #define dbg(x) cout << #x << ": " << x << endl;
#define dbg(x) 0

void solve() {
    int n, m; cin >> n >> m;
    vector<string> P(n);
    for(auto& x: P) cin >> x;

    int N, M; cin >> N >> M;
    vector<string> S(N);
    for(auto& x: S) cin >> x;



    Hashing P_H(P), S_H(S);
    vector<vector<int>> upd(N + 5, vector<int>(M + 5));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            const int ir = i + n - 1;
            const int jr = j + m - 1;
            if(ir >= N || jr >= M) continue;

            const int x1 = i;
            const int x2 = ir;
            const int y1 = j;
            const int y2 = jr;

            if(P_H.get_hash(1, 1, n, m) == S_H.get_hash(x1 + 1, y1 + 1, x2 + 1, y2 + 1)) {
                upd[x1][y1]++;
                if(x2 + 1 < N) upd[x2 + 1][y1]--;
                if(y2 + 1 < M) upd[x1][y2 + 1]--;
                if(x2 + 1 < N and y2 + 1 < M) upd[x2 + 1][y2 + 1]++;
            }
        }
    }

    for(int i = 1; i < N; i++){
        for(int j = 0; j < M; j++){
            upd[i][j] += upd[i-1][j];
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 1; j < M; j++){
            upd[i][j] += upd[i][j-1];
        }
    }

    vector<string> re(N, string(M, '.'));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(upd[i][j] > 0) {
                re[i][j] = S[i][j];
            }
        }
    }
    for(auto& x: re) cout << x << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
