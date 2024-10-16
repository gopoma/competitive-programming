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
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
//? /Template

void solve() {
    vpi directionsKnight{
        mp(+1, +2),
        mp(+2, +1),
        mp(-1, -2),
        mp(-2, -1),
        mp(+1, -2),
        mp(+2, -1),
        mp(-1, +2),
        mp(-2, +1),
    };
    remDup(directionsKnight);
    chk(sz(directionsKnight) == 8);
    vpi directionsKing{
        mp(+1, +1),
        mp(-1, -1),
        mp(+1, -1),
        mp(-1, +1),
    };
    for(int k = 0; k < 4; k++) directionsKing.eb(dx[k], dy[k]);


    int N, M; cin >> N >> M;
    auto check = [&](int x, int y) -> bool {
        return (0 <= x && x < N) && (0 <= y && y < M);
    };

    vs board(N); each(x, board) cin >> x;
    vvb blocked(N, vb(M));

    int sx, sy, tx, ty;
    for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) {
        if(board[i][j] == 'A') {
            sx = i;
            sy = j;
        } else if(board[i][j] == 'B') {
            tx = i;
            ty = j;
        }
    }

    for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) {
        if(board[i][j] == 'Z') {
            for(int k = 0; k < 8; k++) {
                int nx = i + directionsKnight[k].f;
                int ny = j + directionsKnight[k].s;
                if(check(nx, ny) && board[nx][ny] != 'A' && board[nx][ny] != 'B') {
                    blocked[nx][ny] = true;
                }
            }
        }
    }

    vvb vis(N, vb(M)); vis[sx][sy] = true;
    vvi dist(N, vi(M)); dist[sx][sy] = 0;
    deque<pi> q; q.eb(sx, sy);

    dbg(sx, sy, tx, ty);
    while(!q.empty()) {
        auto [cx, cy] = q.ft; q.pop_front();
        for(int k = 0; k < 8; k++) {
            int nx = cx + directionsKing[k].f;
            int ny = cy + directionsKing[k].s;
            if(check(nx, ny) && !blocked[nx][ny] && (board[nx][ny] == '.' || board[nx][ny] == 'B') && !vis[nx][ny]) {
                vis[nx][ny] = true;
                dist[nx][ny] = dist[cx][cy] + 1;
                q.eb(nx, ny);
            }
        }
    }

    if(!vis[tx][ty]) cout << "King Peter, you can't go now!";
    else cout << "Minimal possible length of a trip is " << dist[tx][ty];
    cout << "\n";
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
