//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

#ifdef LOCAL
    #include "helpers/debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif

// building blocks
using ll  = long long;
using db  = long double; // or double, if TL is tight
using str = string;      // yay python!

//? priority_queue for minimum
//? template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

//? using ull  = unsigned long long;
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

#define lb lower_bound
#define ub upper_bound
tcT > int lwb(V<T> &a, const T &b) { return int(lb(all(a), b) - bg(a)); }
tcT > int upb(V<T> &a, const T &b) { return int(ub(all(a), b) - bg(a)); }



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); }  // # of bits set
constexpr int bits(int x) {  // assert(x >= 0); // make C++11 compatible until
	                         // USACO updates ...
	return x == 0 ? 0 : 31 - __builtin_clz(x);
}  // floor(log2(x))
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }

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

tcTU > T fstTrue(T lo, T hi, U f) {
	++hi;
	assert(lo <= hi);  // assuming f is increasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo) / 2;
		f(mid) ? hi = mid : lo = mid + 1;
	}
	return lo;
}
tcTU > T lstTrue(T lo, T hi, U f) {
	--lo;
	assert(lo <= hi);  // assuming f is decreasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo + 1) / 2;
		f(mid) ? lo = mid : hi = mid - 1;
	}
	return lo;
}
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



#define tcTUU tcT, class ...U

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

inline namespace FileIO {
void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void setIO(str s = "") {
	cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
	cout << fixed << setprecision(12);
    cerr << fixed << setprecision(12);
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

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

//? /Custom Helpers



//* Template
//* /Template

#define x first
#define y second

void solve() {
    vector<pd> nodes(4); each(e, nodes) cin >> e.f >> e.s;

    each(e, nodes) dbg(e);

    const db EPS = 1e-12;
    dbg(EPS);

    auto eq = [EPS](db a, db b) {
        return abs(a - b) < EPS;
    };

    auto dist2 = [](pd A, pd B) {
        db dx = A.x - B.x;
        db dy = A.y - B.y;

        return dx * dx + dy * dy;
    };

    auto dist = [dist2](pd A, pd B) {
        return sqrt(dist2(A, B));
    };

    auto get_angle = [dist2](pd A, pd B, pd C) {
        //? need angle ABC
        db a2 = dist2(A, B);
        db b2 = dist2(B, C);
        db c2 = dist2(A, C);

        //? c^2 = a^2 + b^2 - 2*a*b*cos(x)
        //? 2*a*b*cos(x) = a^2 + b^2 - c^2
        //? cos(x) = (a^2 + b^2 - c^2) / (2*a*b)

        db result = acos((a2 + b2 - c2) / (db(2)*db(sqrt(a2))*db(sqrt(b2))));
        return result;
    };

    auto R = [](db S) {
        db result = (S * PI) / db(180);
        return result;
    };

    auto S = [](db R) {
        db result = (db(180) * R) / PI;
        return result;
    };

    //? x-axis is oriented to the right
    //? y-axis is oriented upwards.

    //? The four points are distinct, form a convex quadrilateral shape
    //? (i.e. all interior angles are strictly less than 180◦),
    //? and are given in clockwise order.

    // TODO: are given in clockwise order
    //? A: nodes[0]
    //? B: nodes[1]
    //? C: nodes[2]
    //? D: nodes[3]

    pd A = nodes[0];
    pd B = nodes[1];
    pd C = nodes[2];
    pd D = nodes[3];

    //! Angles

    db angleDAB = get_angle(D, A, B);
    db angleABC = get_angle(A, B, C);
    db angleBCD = get_angle(B, C, D);
    db angleCDA = get_angle(C, D, A);

    vd a(4);
    a[0] = get_angle(D, A, B);
    a[1] = get_angle(A, B, C);
    a[2] = get_angle(B, C, D);
    a[3] = get_angle(C, D, A);

    for(int k = 0; k < 4; k++) {
        dbg(a[k]);
        assert(0 < S(a[k]) && S(a[k]) < db(180));
    }

    RAYA;

    dbg(angleDAB, angleABC, angleBCD, angleCDA);
    dbg(S(angleDAB), S(angleABC), S(angleBCD), S(angleCDA));

    //! Distances

    db dist2AB = dist2(A, B);
    db dist2BC = dist2(B, C);
    db dist2CD = dist2(C, D);
    db dist2DA = dist2(D, A);

    db distAB = dist(A, B);
    db distBC = dist(B, C);
    db distCD = dist(C, D);
    db distDA = dist(D, A);

    RAYA;

    dbg(dist2AB, dist2BC, dist2CD, dist2DA);
    dbg(distAB, distBC, distCD, distDA);

    RAYA;

    set<db> distances;
    distances.emplace(dist2AB);
    distances.emplace(dist2BC);
    distances.emplace(dist2CD);
    distances.emplace(dist2DA);

    set<db> angles;
    angles.emplace(angleDAB);
    angles.emplace(angleABC);
    angles.emplace(angleBCD);
    angles.emplace(angleCDA);

    if(
        eq(angleDAB, PI/db(2.0)) &&
        eq(angleABC, PI/db(2.0)) &&
        eq(angleBCD, PI/db(2.0)) &&
        eq(angleCDA, PI/db(2.0))
    ) {
        assert(sz(angles) == 1);

        if(sz(distances) == 1) cout << "square\n";
        else {
            assert(sz(distances) == 2);
            cout << "rectangle\n";
        }
    } else if(sz(angles) == 2 && sz(distances) == 1) cout << "rhombus\n";
    else {
        //? kite
        bool ok_kite = false;
        for(int i = 0; i < 4; i++) {
            int j = (i + 2) % 4;

            vd other;
            for(int k = 0; k < 4; k++) if(k != i && k != j) {
                other.eb(a[k]);
            }

            dbg(a[i], a[j], other);

            if(eq(a[i], a[j]) && !eq(other[0], other[1])) ok_kite = true;
        }

        if(ok_kite) cout << "kite\n";
        else {
            bool ok_parallelogram = false;
            for(int i = 0; i < 4; i++) {
                db xd1 = a[i % 4];
                db xd2 = a[(i + 1) % 4];
                db xd3 = a[(i + 2) % 4];
                db xd4 = a[(i + 3) % 4];

                if(eq(xd1, xd3) && eq(xd2, xd4)) {
                    assert(!eq(xd1, xd2));
                    ok_parallelogram = true;
                }
            }

            if(ok_parallelogram) cout << "parallelogram\n";
            else {
                bool ok_trapezium = false;

                for(int i = 0; i < 4; i++) {
                    db xd1 = a[i % 4];
                    db xd2 = a[(i + 1) % 4];

                    if(eq(xd1 + xd2, PI)) ok_trapezium = true;
                }

                if(ok_trapezium) cout << "trapezium\n";
                else {
                    cout << "none\n";
                }
            }
        }
    }
}


//? Generator
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator


signed main() {
    setIO();

    ll t = 1;
    //? cin >> t;

    FOR(i, 1, t + 1) {
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
