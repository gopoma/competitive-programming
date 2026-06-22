#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = long double;

const ll BIG = ll(1e18) + 5;
const int INF = int(1e9) + 5;

#define dbg(x) cout << #x << ": " << x << endl;
#define RAYA dbg("====================================");
//* #define dbg(x) 0


mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }

const int MAXN = 250;
int a[MAXN + 1];
int pref[MAXN + 1];
int dp[MAXN + 1][MAXN + 1];

void solve(int n, bool isDebugging) {
    if(isDebugging) {
        for(int i = 0; i < n; i++) a[i] = 100;
    } else {
        for(int i = 0; i < n; i++) cin >> a[i];
    }

    for(int i = 0; i < n; i++) {
        pref[i] = a[i];
        if(0 <= i - 1) {
            pref[i] += pref[i - 1];
        }
    }
    auto query = [&](int l, int r) -> int {
        int sum = pref[r];
        if(0 <= l - 1) sum -= pref[l - 1];
        return sum;
    };

    for(int r = 0; r < n; r++) {
        for(int l = r; l >= 0; l--) {
            if(l == r) {
                dp[l][r] = 0;
                continue;
            }

            dp[l][r] = INF;

            int tot = query(l, r);
            for(int mid = l; mid <= r; mid++) {
                int local_res = tot - a[mid];
                if(l <= mid - 1) local_res += dp[l][mid - 1];
                if(mid + 1 <= r) local_res += dp[mid + 1][r];
                dp[l][r] = min(dp[l][r], local_res);
            }
        }
    }

    int res = dp[0][n - 1];
    cout << res << "\n";

//*    auto dp = [&](auto&& dp, int l, int r) -> int {
//*        if(l == r) return 0;
//*        if(vis[l][r]) return memo[l][r];
//*        vis[l][r] = true;
//*
//*        int res = INF;
//*
//*        int tot = query(l, r);
//*        for(int mid = l; mid <= r; mid++) {
//*            int local_res = tot - a[mid];
//*            if(l <= mid - 1) local_res += dp(dp, l, mid - 1);
//*            if(mid + 1 <= r) local_res += dp(dp, mid + 1, r);
//*            res = min(res, local_res);
//*        }
//*
//*        return memo[l][r] = res;
//*    };
//*
//*    int res = dp(dp, 0, n - 1);
//*    cout << res << "\n";
}

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int caso = 1;
    while(true&&0) {
        RAYA;

        db start = time_elapsed();

        int t = 30;
        while(t--) {
            int n = 250;
            solve(n, true);
        }

        db current = time_elapsed();
        db taken = current - start;

        dbg(caso); caso++;
        dbg(taken);

        if(taken > db(1)) {
            assert(false);
        }
    }

    int n;
    while(cin >> n) {
        solve(n, false);
    }
}
