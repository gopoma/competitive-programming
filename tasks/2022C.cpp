#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



using ll  = long long;
using db  = long double;
using str = string;
using ull  = unsigned long long;

using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;



#define mp make_pair
#define f  first
#define s  second

template<class T> using V = vector<T>;
#define all(x) begin(x), end(x)



const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}



//? Template
#define tcT template <class T
#define tcTU tcT, class U

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)
//? /Template

const ll BIG = ll(1e18);
void solve() {
    ll n; cin >> n; chk(n % 3LL == 0LL);
    vector<str> board(2); for(auto& x: board) cin >> x;
    dbg(n);
    for(auto& x: board) dbg(x);

    const ll INIT = 0;
    const ll UP   = 1;
    const ll DOWN = 2;

    auto get = [&](char c) -> ll {
        return (c == 'A');
    };

    auto get2 = [&](char A, char B, char C) -> ll {
        return ll(get(A) + get(B) + get(C) >= 2LL);
    };
    
    vector<vector<bool>> vis(n + 5, vector<bool>(5));
    vector<vector<ll>> memo(n + 5, vector<ll>(5));
    auto dp = [&](const auto& dp, ll i, ll currentState) -> ll {
        if(i == n) {
            if(currentState == INIT) return 0LL;
            else return -BIG;
        }
        if(vis[i][currentState]) return memo[i][currentState];
        vis[i][currentState] = true;

        ll ans = -BIG;
        if(currentState == INIT) {
            if(i + 1 < n) {
                ckmax(ans, dp(dp, i + 1, UP)   + get2(board[0][i], board[1][i], board[1][i + 1]));
                ckmax(ans, dp(dp, i + 1, DOWN) + get2(board[0][i], board[1][i], board[0][i + 1]));
            }
            if(i + 2 < n) {
                ckmax(ans, dp(dp, i + 3, INIT) + 
                    get2(board[0][i], board[0][i + 1], board[0][i + 2]) + 
                    get2(board[1][i], board[1][i + 1], board[1][i + 2])
                );
            }
        } else if(currentState == UP) {
            if(i + 1 < n) {
                ckmax(ans, dp(dp, i + 2, INIT) + 
                    get2(board[0][i], board[0][i + 1], board[1][i + 1]));
            }
            if(i + 3 < n) {
                ckmax(ans, dp(dp, i + 3, UP) +
                    get2(board[0][i], board[0][i + 1], board[0][i + 2]) +
                    get2(board[1][i + 1], board[1][i + 2], board[1][i + 3])
                );
            }
        } else {
            chk(currentState == DOWN);
            if(i + 1 < n) {
                ckmax(ans, dp(dp, i + 2, INIT) +
                    get2(board[1][i], board[0][i + 1], board[1][i + 1])
                );
            }
            if(i + 3 < n) {
                ckmax(ans, dp(dp, i + 3, DOWN) +
                    get2(board[0][i + 1], board[0][i + 2], board[0][i + 3]) +
                    get2(board[1][i], board[1][i + 1], board[1][i + 2])
                );
            }
        }

        return memo[i][currentState] = ans;
    };
    ll ans = dp(dp, 0, INIT);
    dbg(ans);
    cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int t = 1; cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        solve();
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}