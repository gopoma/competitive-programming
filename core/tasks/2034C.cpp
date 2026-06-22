//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

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



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



//? Custom Helpers
template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

//? __builtin_popcountll
ll GetBit(ll mask, ll bit) { return (mask >> bit) & 1LL; }
void TurnOn(ll& mask, ll bit) { mask = mask | (1LL << bit); }
void TurnOff(ll& mask, ll bit) { mask = mask & (~(1LL << bit)); }

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? /Template



void solve() {
    //? <>
    int n, m; cin >> n >> m;
    vs S(n); for(auto& x: S) cin >> x;
    for(auto& x: S) dbg(x);

    map<char, pi> directions;
    directions['L'] = mp(0, -1);
    directions['R'] = mp(0, +1);
    directions['U'] = mp(-1, 0);
    directions['D'] = mp(+1, 0);

    map<char, char> opposite;
    opposite['L'] = 'R';
    opposite['U'] = 'D';
    opposite['R'] = 'L';
    opposite['D'] = 'U';

    auto check = [&](int i, int j) -> bool {
        return (0<=i&&i<n)&&(0<=j&&j<m);
    };

    vvb bad(n, vb(m));
    {

        vvb good(n, vb(m));
        vvb vis(n, vb(m));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(good[i][j]) continue;
                if(bad[i][j]) continue;
                if(S[i][j] == '?') {
                    dbg(i, j, '?');
                    for(auto& [c, it]: directions) {
                        auto [delta_x, delta_y] = it;
                        int nx = i + delta_x;
                        int ny = j + delta_y;
                        if(!check(nx, ny)) continue;
                        if(S[nx][ny] == '?' || (S[nx][ny] == opposite[c])) {
                            bad[i][j] = true;
                            vis[i][j] = true;
                            break;
                        }
                    }
                } else {
                    vpl stk;
                    int cx = i;
                    int cy = j;
                    while(true) {
                        stk.eb(cx, cy);

                        if(bad[cx][cy]) {
                            dbg(i, j, "bad", stk);
                            for(auto& [xx, yy]: stk) {
                                bad[xx][yy] = true;
                                vis[xx][yy] = true;
                            }
                            break;
                        } else if(good[cx][cy]) {
                            dbg(i, j, "good", stk);
                            for(auto& [xx, yy]: stk) {
                                good[xx][yy] = true;
                                vis[xx][yy] = true;
                            }
                            break;
                        } else {
                            if(vis[cx][cy]) {
                                dbg(i, j, "bad", stk);
                                for(auto& [xx, yy]: stk) {
                                    bad[xx][yy] = true;
                                    vis[xx][yy] = true;
                                } 
                                break;  
                            } else {
                                vis[cx][cy] = true;

                                int nx = cx + directions[S[cx][cy]].f;
                                int ny = cy + directions[S[cx][cy]].s;
                                dbg(i,j,cx,cy,nx,ny);
                                if(!check(nx, ny)) {
                                    dbg(i, j, "good", stk);
                                    for(auto& [xx, yy]: stk) {
                                        good[xx][yy] = true;
                                        vis[xx][yy] = true;
                                    }
                                    break;
                                } else if(S[nx][ny] == '?') { 
                                    dbg(i, j, "bad", stk); 
                                    for(auto& [xx, yy]: stk) {
                                        bad[xx][yy] = true;
                                        vis[xx][yy] = true;
                                    }
                                    break;
                                } else {
                                    stk.eb(nx, ny);
                                    cx = nx;
                                    cy = ny;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    dbg("before expanding");
    each(x, bad) dbg(x);
    {
        vvb vis(n, vb(m));
        deque<pi> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(vis[i][j]) continue;
                if(!bad[i][j]) continue;
                q.eb(i, j);
                vis[i][j] = true;
                while(!q.empty()) {
                    auto [cx, cy] = q.ft; q.pop_front();
                    for(auto& [c, it]: directions) {
                        auto [delta_x, delta_y] = it;
                        int nx = cx + delta_x;
                        int ny = cy + delta_y;
                        if(!check(nx, ny)) continue;
                        if(!vis[nx][ny] && (S[nx][ny] == '?' || (S[nx][ny] == opposite[c]))) {
                            bad[nx][ny] = true;
                            vis[nx][ny] = true;
                            q.eb(nx, ny);
                        }
                    }
                }
            }
        }
        dbg("after expanding");
        each(x, bad) dbg(x);

        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ans += bad[i][j];
            }
        }
        cout << ans << "\n";
    }
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
    }

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
