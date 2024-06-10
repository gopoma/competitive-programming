//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debugICPC.h"

#define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define chk(...)
#define RAYA
#endif

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}



// building blocks
using ll  = long long;
using db  = long double; // or double, if TL is tight
using str = string;      // yay python!

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
#define f first
#define s second



#define tcT template <class T
#define tcTU tcT, class U
//! ^ lol this makes everything look weird but I'll try it

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



// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



const int MOD = 1e9+7;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



inline namespace FileIO {
void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void setIO(str s = "") {
	cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
	//? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);
	cin.exceptions(cin.failbit);
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) setIn(s + ".in"), setOut(s + ".out");  // for old USACO
}
}  // namespace FileIO



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
//? /Custom Helpers

//? long long collinear(Point p, Point p1, Point p2) {
ll collinear(
    int x1, int y1,
    int x2, int y2,
    int x3, int y3
) {
	return (1LL * (y1 - y2) * (x3 - x2)) -
	       (1LL * (x1 - x2) * (y3 - y2));
}

bool isCollinear(
    int x1, int y1,
    int x2, int y2,
    int x3, int y3
) {
    return (collinear(x1, y1, x2, y2, x3, y3) == 0);
}

const int INF = int(1e9);
pi brute(int N, vpi& points) {
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            int on = 0;
            int off = 0;
            for(int k = 0; k < N; k++) {
                if(k == i || k == j) continue;


                ll act = collinear(
                    points[i].f, points[i].s,
                    points[j].f, points[j].s,
                    points[k].f, points[k].s
                );

                chk(act != 0);

                on += (act < 0);
                off += (act > 0);
            }

            if(on == off) {
                return mp(i, j);
            }
        }
    }

    return mp(INF, INF);
}

pi brute2(int N, vpi& points) {
    int idx1 = 0;

    for(int idx2 = 1; idx2 < N; idx2++) {
        int on = 0;
        int off = 0;
        for(int i = 0; i < N; i++) {
            if(i == idx1 || i == idx2) continue;

            ll act = collinear(
                points[idx1].f, points[idx1].s,
                points[idx2].f, points[idx2].s,
                points[i].f, points[i].s
            );

            chk(act != 0);

            on += (act < 0);
            off += (act > 0);
        }

        if(on == off) {
            return mp(idx1, idx2);
        }
    }
    chk(false);
}

pi slv(int N, vpi& points) {
    return brute2(N, points);
}

bool check_ans(int N, vpi points, pi ans) {
    int on = 0;
    int off = 0;

    for(int i = 0; i < N; i++) {
        if(i == ans.f || i == ans.s) continue;

        ll act = (collinear(
            points[ans.f].f, points[ans.f].s,
            points[ans.s].f, points[ans.s].s,
            points[i].f, points[i].s
        ));

        on += (act < 0);
        off += (act > 0);
    }

    return (on == off);
}


void solve() {
    int N; cin >> N;
    vpi points(N); each(x, points) cin >> x.f >> x.s;

    dbg(N);
    each(x, points) dbg(x);

    pi ans = slv(N, points);
    ans.f++; ans.s++;

    cout << ans.f << " " << ans.s << "\n";
}

// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(0) {
        RAYA;

        int N;
        while(true) {
            N = rng_int(4, 30);
            if(N % 2 == 0) break;
        }
        dbg("gen:", N);
        vpi points;
        auto check = [&]() -> bool {
            bool ok = true;
            const int n = sz(points);
            for(int i = 0; i < n; i++) {
                for(int j = i + 1; j < n; j++) {
                    for(int k = j + 1; k < n; k++) {
                        ok &= !isCollinear(
                            points[i].f, points[i].s,
                            points[j].f, points[j].s,
                            points[k].f, points[k].s
                        );
                    }
                }
            }
            return ok;
        };

        int MAX_ITERATIONS = int(1e3);
        int counter = 0;
        while(sz(points) < N) {
            counter++;
            if(counter == MAX_ITERATIONS) {
                points.clear();
            }
            int xx = rng_int(int(-1e1), int(1e1));
            int yy = rng_int(int(-1e1), int(1e1));

            pi act = mp(xx, yy);

            points.eb(act);
            if(check()) continue;

            points.pop_back();
        }

        dbg(N, sz(points));
        chk(N == sz(points));
        each(x, points) dbg(x);

        pi ans = slv(N, points);
        chk(ans != mp(INF, INF));
        dbg(ans);
        dbg(points[ans.f]);
        dbg(points[ans.s]);

        chk(check_ans(N, points, ans));
    }

    int t = 1;
    //? cin >> t;

    for(int idx = 0; idx < t; idx++) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
