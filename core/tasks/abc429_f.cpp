#ifdef LOCAL
    #ifdef _WIN32
        #define WIN32_LEAN_AND_MEAN
        #define NOMINMAX
        #include <windows.h>
        #include <psapi.h>
    #else
        #include <sys/resource.h>
    #endif
#endif




// fast setup for C++17/20/23
#pragma GCC optimize ("Ofast")
//! #pragma GCC optimize ("trapv")

#include <bits/stdc++.h> //? if you don't want IntelliSense
using namespace std;

#undef _GLIBCXX_DEBUG //? for Stress Testing
#pragma GCC target ("avx,avx2")


// //* sometimes pragmas don't work, if so, just comment it!
// //? #pragma GCC optimize ("Ofast")
// //? #pragma GCC target ("avx,avx2")
// //! #pragma GCC optimize ("trapv")
//
// //! #undef _GLIBCXX_DEBUG //? for Stress Testing
//
//
// #include <algorithm>
// #include <array>
// #include <bitset>
// #include <cassert>
// #include <chrono>
// #include <climits>
// #include <cmath>
// #include <complex>
// #include <cstring>
// #include <functional>
// #include <iomanip>
// #include <iostream>
// #include <map>
// #include <numeric>
// #include <queue>
// #include <random>
// #include <set>
// #include <vector>
// using namespace std;




//* Debugger
void print_memory_usage() {
#ifdef LOCAL
    #ifdef _WIN32
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            long double block = 1024;
            long double taken = pmc.PeakWorkingSetSize / (block * block);

            std::cerr << "\n";
            std::cerr << "\033[42m++++++++++++++++++++\033[0m\n";
            std::cerr << "\033[42m[Memory] Peak Working Set: "
            << taken << " MB\033[0m\n";
            std::cerr << "\033[42m++++++++++++++++++++\033[0m";
        }
    #else
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        #ifdef __APPLE__
            double peak_mb = usage.ru_maxrss / (1024.0 * 1024.0); // macOS en Bytes
        #else
            double peak_mb = usage.ru_maxrss / 1024.0;            // Linux en KiB
        #endif
        std::cerr << "[Memory] Peak RSS: " << peak_mb << " MB\n";
    #endif
#endif
}




#ifdef LOCAL
    #include "helpers/debug.h"

    const bool isDebugging = true;
#else
    #define dbg(...)     0
    #define chk(...)     0
    #define RAYA         0

    const bool isDebugging = false;
#endif
//* /Debugger



using ll = long long;
using db = long double; // or double if tight TL
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;
#define mp make_pair
#define f  first
#define s  second



#define tcT template<class T
#define tcTU tcT, class U

tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

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



const int MOD = int(1e9) + 7;
const int INF = int(5e8) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
const int dx4[4]{1, 0, -1, 0}, dy4[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



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



void setIn(string s) { freopen(s.c_str(), "r", stdin); }
void setOut(string s) { freopen(s.c_str(), "w", stdout); }

const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
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

const int dx8[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dy8[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

template <typename T>
T custom_abs(T x) {
    if(x < T(0)) return -x;
    return +x;
}

template <typename T>
T custom_sqrt(T x) {
    T r = sqrtl(x);
    while((r + T(1)) * (r + T(1)) < x) r++;
    while(r * r > x) r--;
    return r;
}
//? /Custom Helpers




// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
    return uniform_int_distribution<int>(L,R)(rng);
}

ll rng_ll(ll L, ll R) { assert(L <= R);
    return uniform_int_distribution<ll>(L,R)(rng);
}

// return double in [L,R] inclusive
db rng_db(db L, db R) { assert(L <= R);
    return uniform_real_distribution<db>(L,R)(rng);
}

template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
    assert(N >= 1 && back >= 0); vpi ed;
    FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
    return ed;
}




//* Template
/**
 * Description: All-Pairs Shortest Path
 * Source: KACTL
 * Verification:
    * https://open.kattis.com/problems/allpairspath
    * https://cses.fi/problemset/task/1672/
 */

void floydWarshall(vvi& m) {
    int n = sz(m);
    F0R(k,n) F0R(i,n) F0R(j,n)
        if (m[i][k] != INF && m[k][j] != INF) {
            auto newDist = m[i][k] + m[k][j];
            ckmin(m[i][j], newDist);
        }
}

/**
 * Author: gopoma
 * Date: 2026-10-03
 * Source: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/SegmentTree/SegmentTree.h
 *   algorithm after codeforces.com/blog/entry/18051 (Al.Cash) and KACTL
 * Description: Segment tree with point assignment and range query. T() is the neutral value,
 *   a + b folds two neighbouring intervals (a left of b) and must be associative.
 *   max_right / min_left descend the tree to find a boundary. Manual: SegmentTree.md
 * Time: O(n) build, O(log n) set, prod, max_right and min_left, O(1) get and all_prod
 * Status: Stress-tested against brute force, exhaustive for n = 1..40. No judge submission yet.
 */

template <class T>
struct SegmentTree {
  public:
    SegmentTree() : SegmentTree(0) {}

    explicit SegmentTree(int len) {
        SZ = 1;

        while(SZ < max(1, len)) {
            SZ *= 2;
        }

        n = SZ;                                 // sin vector, n es el tamano con padding
        seg.assign(2 * SZ, T());                // todo identidad, no hace falta pull:
    }                                           // T() + T() == T()

    explicit SegmentTree(const vector<T>& init) : n(int(init.size())) {
        SZ = 1;

        while(SZ < max(1, n)) {
            SZ *= 2;
        }

        seg.assign(2 * SZ, T());

        for(int i = 0; i < n; i++) {
            seg[SZ + i] = init[i];
        }

        for(int p = SZ - 1; p > 0; p--) {
            pull(p);
        }
    }

    void set(int pos, T val) {
        assert(0 <= pos && pos < n);

        pos += SZ;
        seg[pos] = val;

        for(pos /= 2; pos > 0; pos /= 2) {
            pull(pos);
        }
    }

    T get(int pos) const {
        assert(0 <= pos && pos < n);
        return seg[pos + SZ];
    }

    T all_prod() const {
        return seg[1];
    }

    // Vuelca el arreglo logico para depurar: dump()[i] es exactamente lo que da get(i).
    // Son n elementos, no SZ: el relleno [n, SZ) no es parte del arreglo.
    vector<T> dump() const {
        return vector<T>(seg.begin() + SZ, seg.begin() + SZ + n);
    }

    T prod(int l, int r) const { // zero-indexed, inclusive
        assert(0 <= l && l <= r && r < n);

        T ra = T();
        T rb = T();

        l += SZ;
        r += SZ + 1;

        while(l < r) {
            if(l & 1) {
                ra = ra + seg[l];
                l++;
            }

            if(r & 1) {
                r--;
                rb = seg[r] + rb;
            }

            l /= 2;
            r /= 2;
        }

        return ra + rb;
    }

    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    //
    // Recorre la descomposicion de [l, r] de izquierda a derecha absorbiendo nodos enteros
    // mientras f aguante, y cuando uno rompe baja por el para ubicar la posicion exacta.
    // El nodo actual cubre [pos, pos + len - 1]; ACL no necesita llevar eso porque su
    // version no tiene r, pero con rango acotado hay que AGRANDAR mientras el padre entre
    // y ENCOGER cuando el hermano se pase de r.
    template<class F>
    int max_right(int l, int r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        int k = l + SZ;
        int pos = l;
        int len = 1;
        T sm = T();                             // vale prod(l, pos - 1)

        while(pos <= r) {
            while(k % 2 == 0 && pos + 2 * len - 1 <= r) {
                k >>= 1;                        // agrandar: el padre todavia entra
                len *= 2;
            }

            while(pos + len - 1 > r) {
                k = 2 * k;                      // encoger: este nodo se pasa de r
                len /= 2;
            }

            T t = sm + seg[k];                  // sm a la izquierda, el nodo a la derecha

            if(!pred(t)) {                      // rompe: la respuesta esta adentro
                while(k < SZ) {
                    k = 2 * k;
                    len /= 2;
                    T t2 = sm + seg[k];

                    if(pred(t2)) {              // el izquierdo aguanta: absorber e ir al derecho
                        sm = t2;
                        pos += len;
                        k++;
                    }
                }

                return pos - 1;                 // pos rompe, la ultima buena es pos - 1
            }

            sm = t;                             // aguanta entero: absorber y seguir
            pos += len;
            k++;
        }

        return r;                               // aguanto todo [l, r]
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    // Espejo del de arriba: el nodo cubre [pos - len + 1, pos], se encoge por el lado
    // derecho, y el agregado se arma con el nodo a la IZQUIERDA de lo acumulado.
    template<class F>
    int min_left(int l, int r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        int k = r + SZ;
        int pos = r;
        int len = 1;
        T sm = T();                             // vale prod(pos + 1, r)

        while(pos >= l) {
            while(k % 2 == 1 && k > 1 && pos - 2 * len + 1 >= l) {
                k >>= 1;
                len *= 2;
            }

            while(pos - len + 1 < l) {
                k = 2 * k + 1;                  // encoger por el lado DERECHO
                len /= 2;
            }

            T t = seg[k] + sm;                  // el nodo a la IZQUIERDA de sm

            if(!pred(t)) {
                while(k < SZ) {
                    k = 2 * k + 1;              // el DERECHO primero
                    len /= 2;
                    T t2 = seg[k] + sm;

                    if(pred(t2)) {
                        sm = t2;
                        pos -= len;
                        k--;
                    }
                }

                return pos + 1;
            }

            sm = t;
            pos -= len;
            k--;
        }

        return l;
    }

  private:
    int n = 1;
    int SZ = 1;
    vector<T> seg;

    void pull(int p) {
        seg[p] = seg[2 * p] + seg[2 * p + 1];
    }
};

// /here goes the template!
//* /Template

vvi dpSingle[1 << 3];
vvi dpDouble[1 << 3][1 << 3];
struct Node {
    int size = 0;
    vvi dist;
    int maskleft, maskright;
    int l, r;

    Node() {}
    Node(int mask, int _l, int _r) {
        size = 1;

        maskleft = mask;
        maskright = mask;

        dist = dpSingle[mask];
        dbg(mask, dist);

        l = _l;
        r = _r;
    }

    friend Node operator+(const Node& a, const Node& b) {
        if(a.size == 0) {
            return b;
        }

        if(b.size == 0) {
            return a;
        }

        Node res;
        res.size = a.size + b.size;
        res.maskleft = a.maskleft;
        res.maskright = b.maskright;
        res.dist = vvi(3, vi(3, INF));
        res.l = a.l;
        res.r = b.r;

        dbg("Info");
        vvi between = dpDouble[a.maskright][b.maskleft];
        dbg(a.maskright, b.maskleft);
        for(auto& vec: between) {
            dbg(vec);
        }
        for(int u = 0; u < 3; u++) {
            for(int v = 0; v < 3; v++) {
                for(int l = 0; l < 3; l++) {
                    for(int r = 0; r < 3; r++) {
                        ckmin(res.dist[l][r], a.dist[l][u] + between[2 * u][2 * v + 1] + b.dist[v][r]);
                    }
                }
            }
        }

        dbg(a.l, a.r, b.l, b.r);
        dbg(a.maskleft, a.maskright);
        dbg(b.maskleft, b.maskright);
        dbg(a.dist);
        dbg(b.dist);
        dbg(res.l, res.r, res.dist);
        dbg("/Info");
        return res;
    }
};

void precompute() {
    // single
    {
        // bit on: .
        // bit off: #
        for(int mask = 0; mask < (1 << 3); mask++) {
            str state;
            for(int i = 0; i < 3; i++) {
                if(mask & (1 << i)) {
                    state.pb('.');
                } else {
                    state.pb('#');
                }
            }

            vvi dist(3, vi(3, INF));
            if(state[0] == '.') ckmin(dist[0][0], 0);
            if(state[1] == '.') ckmin(dist[1][1], 0);
            if(state[2] == '.') ckmin(dist[2][2], 0);
            if(state[0] == '.' && state[1] == '.') {
                ckmin(dist[0][1], 1);
                ckmin(dist[1][0], 1);
            }
            if(state[1] == '.' && state[2] == '.') {
                ckmin(dist[1][2], 1);
                ckmin(dist[2][1], 1);
            }

            floydWarshall(dist);
            dpSingle[mask] = dist;
        }
    }

    // double
    {
        const int n = 3;
        const int m = 2;
        auto id = [&](int i, int j) -> int {
            return i * m + j;
        };
        for(int maskA = 0; maskA < (1 << 3); maskA++) {
            for(int maskB = 0; maskB < (1 << 3); maskB++) {
                vs state(3, str(2, '#'));
                for(int i = 0; i < 3; i++) {
                    if(maskA & (1 << i)) {
                        state[i][0] = '.';
                    }

                    if(maskB & (1 << i)) {
                        state[i][1] = '.';
                    }
                }

                vvi dist(6, vi(6, INF));
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < m; j++) {
                        if(state[i][j] == '.') {
                            ckmin(dist[id(i, j)][id(i, j)], 0);
                        }
                    }
                }


                auto add_edge = [&](int x1, int y1, int x2, int y2) -> void {
                    if(state[x1][y1] == '.' && state[x2][y2] == '.') {
                        int id1 = id(x1, y1);
                        int id2 = id(x2, y2);

                        ckmin(dist[id1][id2], 1);
                        ckmin(dist[id2][id1], 1);
                    }
                };
                add_edge(0, 0, 0, 1);
                add_edge(1, 0, 1, 1);
                add_edge(2, 0, 2, 1);

                add_edge(0, 0, 1, 0);
                add_edge(0, 1, 1, 1);
                add_edge(1, 0, 2, 0);
                add_edge(1, 1, 2, 1);

                floydWarshall(dist);

                dpDouble[maskA][maskB] = dist;
            }
        }
    }
}
void solve() {
    // run A < A3.in
    // xd A < A4.in

    int n; cin >> n;
    vs S(3); for(auto& x: S) cin >> x;
    int q; cin >> q;
    vpi queries(q);
    for(auto& [i, j]: queries) {
        cin >> i >> j;
        i--; j--;
    }
    dbg(n);
    for(auto& x: S) {
        dbg(x);
    }
    dbg(q);
    for(auto& [i, j]: queries) {
        dbg(i, j);
    }




    auto calc_mask = [&](int col) -> int {
        int mask = 0;
        for(int row = 0; row < 3; row++) {
            if(S[row][col] == '.') {
                mask |= (1 << row);
            }
        }
        return mask;
    };
    vector<Node> start(n);
    for(int col = 0; col < n; col++) {
        int mask = calc_mask(col);
        start[col] = Node(mask, col, col);
        dbg(col, mask);
    }
    SegmentTree<Node> st(start);


    if(isDebugging) {
        vvi dist = st.all_prod().dist;
        dbg("all_prod", dist);
    }
    for(auto& [i, j]: queries) {
        RAYA;
        RAYA;
        RAYA;
        dbg("Processing", i, j);

        S[i][j] = (S[i][j] == '.')? '#' : '.';
        st.set(j, Node(calc_mask(j), j, j));

        int res = st.all_prod().dist[0][2];
        dbg(res);
        if(res >= 40 * n) res = -1;
        cout << res << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precompute();

    if(isDebugging) {
        dbg("debug");
        // setIn("xd.in");
    }

    int t = 1;
    // cin >> t;
    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        solve();
    }


    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";

        print_memory_usage();
    #endif
}
