#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
 
using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f  first
#define s  second



#define tcT template <class T
#define tcTU tcT, class U

tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

// vectors
// oops size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()
#define ts to_string

#define lb lower_bound
#define ub upper_bound



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



//? Template
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
//? /Template

void solve() {
    while(true) {
        int N; cin >> N; if(N == 0) break;
        vpi starts(N); each(x, starts) { cin >> x.f >> x.s; }
        int M; cin >> M;
        vpi ends(M); each(x, ends) { cin >> x.f >> x.s; }

        const int MAXN = 2001;
        vvb vis(MAXN, vb(MAXN));
        vvi dist(MAXN, vi(MAXN));
        deque<pi> q;
        for(auto& [xx, yy]: starts) {
            vis[xx][yy] = true;
            dist[xx][yy] = 0;
            q.eb(xx, yy);
        }
        auto check = [&](int xx, int yy) -> bool {
            return (0 <= xx && xx < MAXN) && (0 <= yy && yy < MAXN);
        };
        while(!q.empty()) {
            auto [cx, cy] = q.ft; q.pop_front();
            for(int k = 0; k < 4; k++) {
                int nx = cx + dx[k];
                int ny = cy + dy[k];
                if(check(nx, ny) && !vis[nx][ny]) {
                    vis[nx][ny] = true;
                    dist[nx][ny] = dist[cx][cy] + 1;
                    q.eb(nx, ny);
                }
            }
        }
        int ans = int(1e9);
        for(auto& [xx, yy]: ends) ans = min(ans, dist[xx][yy]);
        cout << ans << "\n";
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int t = 1; //! cin >> t;
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
