#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define F first
#define S second
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

const int N = 100;
int mat[N][N];

void solve() {
    int k, n;
    cin >> k >> n;
    k++;
    k = min(k, 100);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            mat[i][j] = 0;
        }
    }

    vector<pair<int, int>> fish(n);
    for(auto& it: fish) cin >> it.F >> it.S;

    for(auto& it: fish) {
        mat[it.F-1][it.S-1] = 1;
    }

    int stripSum[N][N];
    for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
        stripSum[i][j] = 0;

    for (int j = 0; j < N; j++) {
        int sum = 0;
        for (int i = 0; i < k; i++)
            sum += mat[i][j];
        stripSum[0][j] = sum;

        // Calculate sum of remaining rectangles
        for (int i = 1; i < N - k + 1; i++) {
            sum += (mat[i + k - 1][j] - mat[i - 1][j]);
            stripSum[i][j] = sum;
        }
    }

    // max_sum stores maximum sum and its position in matrix
    int max_sum = INT_MIN, *pos = NULL;

    // 2: CALCULATE SUM of Sub-Squares using stripSum[][]
    for (int i = 0; i < N - k + 1; i++) {
        // Calculate and print sum of first subsquare in
        // this row
        int sum = 0;
        for (int j = 0; j < k; j++)
            sum += stripSum[i][j];

        // Update max_sum and position of result
        if (sum > max_sum) {
            max_sum = sum;
            pos = &(mat[i][0]);
        }

        // Calculate sum of remaining squares in current row
        // by removing the leftmost strip of previous
        // sub-square and adding a new strip
        for (int j = 1; j < N - k + 1; j++) {
            sum += (stripSum[i][j + k - 1]
                    - stripSum[i][j - 1]);

            // Update max_sum and position of result
            if (sum > max_sum) {
                max_sum = sum;
                pos = &(mat[i][j]);
            }
        }
    }

    cout << max_sum << nl;

    /*
    for(auto& it: fish) {
        int sum = 0;

        for(int i = it.F; i <= min(100, it.F + s); i++) {
            for(int j = it.S; j <= min(100, it.S + s); j++) {
                sum += mtx[i][j];
            }
        }

        ans = max(ans, sum);

        sum = 0;

        for(int i = it.F; i <= min(100, it.F + s); i++) {
            for(int j = it.S; j >= max(1, it.S - s); j--) {
                sum += mtx[i][j];
            }
        }

        ans = max(ans, sum);
    }

    cout << ans << nl;
    */
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
