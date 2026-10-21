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
//? #pragma GCC optimize ("Ofast")
//? //! #pragma GCC optimize ("trapv")
//?
//? #include <bits/stdc++.h> //? if you don't want IntelliSense
//? using namespace std;
//?
//? #undef _GLIBCXX_DEBUG //? for Stress Testing
//? #pragma GCC target ("avx,avx2")


//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#include <bits/stdc++.h> //? if you don't want IntelliSense
#undef _GLIBCXX_DEBUG //? for Stress Testing
using namespace std;




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
const int INF = int(1e9) + 5;
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
 * Author: gopoma
 * Date: 2026-10-03
 * Source: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/SegmentTree/SparseSegmentTree.h
 *   algorithm after usaco.guide/plat/sparse-segtree
 * Description: Segment tree over a universe up to 1e18; nodes are created only when a set touches
 *   them. Pool: max_nodes(n, q) = (ceil(log2 n) + 1) * q + 1.
 *   Manual: SparseSegmentTree.md
 * Time: O(log n) set, get and prod, O(1) all_prod. No build: it starts empty.
 * Status: Stress-tested against a map at n = 1e18. No judge submission yet.
 */

template <class T>
struct SparseSegmentTree {
  public:
    SparseSegmentTree(long long len, long long max_ops) : n(len) {
        assert(n >= 1 && max_ops >= 0);

        st.reserve(size_t(max_nodes(n, max_ops)));
        st.push_back(InternalNode());           // el nodo nulo: todo el subarbol en T()
    }

    static long long max_nodes(long long len, long long max_ops) {
        assert(len >= 1 && max_ops >= 0);
        return (long long)(ceil_log2(len) + 1) * max_ops + 1;
    }

    void set(long long pos, T val) {
        assert(0 <= pos && pos < n);
        root = set(root, 0, n - 1, pos, val);
    }

    T get(long long pos) const {
        assert(0 <= pos && pos < n);
        return get(root, 0, n - 1, pos);
    }

    T prod(long long l, long long r) const {
        assert(0 <= l && l <= r && r < n);
        return prod(root, 0, n - 1, l, r);
    }

    T all_prod() const {
        return st[root].val;
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template<class F>
    long long max_right(long long l, long long r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_izq(root, 0, n - 1, l, r, acc, pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template<class F>
    long long min_left(long long l, long long r, F pred) const {
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_der(root, 0, n - 1, l, r, acc, pred) + 1;
    }

    // Tope de dump(): n puede valer 1e18 y volcarlo entero no entra en memoria.
    static const long long DUMP_MAX = 10000000;

    // Vuelca el universo entero para depurar: dump()[i] es lo que da get(i). Las posiciones
    // sin materializar vuelven como T(), que es el RANGO VACIO y no "un cero".
    // No consume nodos del pool.
    vector<T> dump() const {
        assert(n <= DUMP_MAX);

        vector<T> out;
        out.reserve(size_t(n));
        dump(root, 0, n - 1, out);
        return out;
    }

    long long size() const {
        return n;
    }

    long long nodes_used() const {
        return (long long)st.size() - 1;
    }

  private:
    struct InternalNode {
        int lc = 0;
        int rc = 0;
        T val{};
    };

    long long n;
    int root = 0;
    vector<InternalNode> st;

    static int ceil_log2(long long x) {
        int c = 0;

        while((1LL << c) < x) {
            ++c;
        }

        return c;
    }

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, lx - 1).
    // st[0] es el nodo nulo y su val ya es T(), asi que un subarbol sin materializar no
    // necesita caso aparte: aporta la identidad y no mueve acc.
    template<class F>
    long long corte_izq(int cur, long long lx, long long rx, long long l, long long r, T& acc, F f) const {
        if(rx < l || r < lx) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if(l <= lx && rx <= r) {                // el nodo entra completo en [l, r]
            T t = acc + st[cur].val;            // acc a la izquierda, el nodo a la derecha
            if(f(t)) {
                acc = t;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if(lx == rx) {
                return lx;                      // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        long long mx = lx + (rx - lx) / 2;
        long long res = corte_izq(st[cur].lc, lx, mx, l, r, acc, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur].rc, mx + 1, rx, l, r, acc, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(rx + 1, r).
    template<class F>
    long long corte_der(int cur, long long lx, long long rx, long long l, long long r, T& acc, F f) const {
        if(rx < l || r < lx) {
            return l - 1;
        }

        if(l <= lx && rx <= r) {
            T t = st[cur].val + acc;            // el nodo a la IZQUIERDA de acc
            if(f(t)) {
                acc = t;
                return l - 1;
            }

            if(lx == rx) {
                return lx;
            }
        }

        long long mx = lx + (rx - lx) / 2;
        long long res = corte_der(st[cur].rc, mx + 1, rx, l, r, acc, f);   // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur].lc, lx, mx, l, r, acc, f);
    }

    // st[0] es el nodo nulo: sus hijos son 0 y su val ya es T().
    void dump(int cur, long long lx, long long rx, vector<T>& out) const {
        if(lx == rx) {
            out.push_back(st[cur].val);
            return;
        }

        long long mx = lx + (rx - lx) / 2;
        dump(st[cur].lc, lx, mx, out);
        dump(st[cur].rc, mx + 1, rx, out);
    }

    int new_node() {
        st.push_back(InternalNode());
        return int(st.size()) - 1;
    }

    // Devuelve el indice del nodo que cubre [lx, rx]. Si era el nodo nulo lo materializa,
    // y si ya existia lo modifica en el lugar: por eso un camino repetido no cuesta nodos.
    int set(int cur, long long lx, long long rx, long long p, const T& x) {
        if(cur == 0) {
            cur = new_node();
        }

        if(lx == rx) {
            st[cur].val = x;
            return cur;
        }

        long long mx = lx + (rx - lx) / 2;      // asi no desborda con n cerca de 2^63

        if(p <= mx) {
            st[cur].lc = set(st[cur].lc, lx, mx, p, x);
        } else {
            st[cur].rc = set(st[cur].rc, mx + 1, rx, p, x);
        }

        st[cur].val = st[st[cur].lc].val + st[st[cur].rc].val;
        return cur;
    }

    T get(int cur, long long lx, long long rx, long long p) const {
        while(lx != rx) {
            if(cur == 0) {                      // subarbol sin materializar
                return T();
            }

            long long mx = lx + (rx - lx) / 2;

            if(p <= mx) {
                cur = st[cur].lc;
                rx = mx;
            } else {
                cur = st[cur].rc;
                lx = mx + 1;
            }
        }

        return st[cur].val;                     // si cur es 0, st[0].val ya es T()
    }

    T prod(int cur, long long lx, long long rx, long long ql, long long qr) const {
        if(cur == 0 || rx < ql || qr < lx) {
            return T();
        }

        if(ql <= lx && rx <= qr) {
            return st[cur].val;
        }

        long long mx = lx + (rx - lx) / 2;
        return prod(st[cur].lc, lx, mx, ql, qr) + prod(st[cur].rc, mx + 1, rx, ql, qr);
    }
};
struct SparseNode {
    int size = 0, mx = 0;

    SparseNode() {}
    SparseNode(int x) {
        size = 1;
        mx = x;
    }

    friend SparseNode operator+(const SparseNode& a, const SparseNode& b) {
        SparseNode res;
        res.size = a.size + b.size;
        res.mx = max(a.mx, b.mx);
        return res;
    }
};


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
struct Node {
    // size == 0 es el rango vacio, la identidad de +. pref, suf y best son sumas de
    // subarreglos, y el vacio cuenta, asi que ninguna de las tres baja de cero.
    int size = 0, mx = -INF;

    Node() {}
    Node(int x) {
        size = 1;
        mx = x;
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
        res.mx = max(a.mx, b.mx);
        return res;
    }
};

//* /Template



/**
 * Description: DP with Binary Search
 * Source: own
 * Verification: https://cses.fi/problemset/task/1145/
 */

int lis(vi v) {
	vi min_last{INT_MIN}; // min last term of increasing sequence with i terms
	for (int x: v) {
		int lo = lb(all(min_last),x)-begin(min_last);
		if (lo == sz(min_last)) min_last.pb(0);
		min_last[lo] = x;
	}
	return sz(min_last)-1;
}


int brute(int n, vi a) {
    int res = lis(a);
    int mn = *min_element(all(a));
    int mx = *max_element(all(a));

    for(int i = 0; i < n; i++) {
        for(int x = mn - 2; x <= mx + 2; x++) {
            vi na = a;
            na[i] = x;

            ckmax(res, lis(na));
        }
    }
    return res;
}

int slv(int n, vi a) {
    int response = lis(a);

    SparseSegmentTree<SparseNode> st(int(1e9) + 10, 5 * n);
    vi selected_to_extend_LIS(n);
    vi dpleft(n);
    for(int i = 0; i < n; i++) {
        int gmx = st.all_prod().mx;

        int left = 0;
        int right = int(1e9) + 5;
        int corte = st.max_right(left, right, [&](SparseNode& node) {
            return node.mx < gmx;
        });


        selected_to_extend_LIS[i] = corte + 2;
        if(corte == -1) {
            selected_to_extend_LIS[i] = 0;
        }
        int len = st.prod(0, a[i] - 1).mx;
        dpleft[i] = len + 1;
        st.set(a[i], dpleft[i]);
    }
    dbg(selected_to_extend_LIS);
    dbg(dpleft);




    vi b = a;
    {
        vi uni;
        for(int i = 0; i < n; i++) {
            uni.eb(selected_to_extend_LIS[i]);
            uni.eb(a[i]);
        }
        sor(uni);
        for(int i = 0; i < n; i++) {
            b[i] = lower_bound(all(uni), b[i]) - uni.begin() + 1;
            selected_to_extend_LIS[i] = lower_bound(all(uni), selected_to_extend_LIS[i]) - uni.begin() + 1;
        }
    }

    const int MAXN = sz(b) + sz(selected_to_extend_LIS) + 5;
    vector<Node> start(MAXN + 5, Node(0));
    SegmentTree<Node> dpright(start);
    for(int i = n - 1; i >= 0; i--) {
        int clen = 1;
        if(i) {
            clen += dpleft[i - 1];
        }

        int lenright = dpright.prod(selected_to_extend_LIS[i] + 1, MAXN).mx;
        clen += lenright;

        ckmax(response, clen);

        // dbg(i, clen);


        int len = dpright.prod(b[i] + 1, MAXN).mx;
        dpright.set(b[i], len + 1);
    }


    return response;
}

void solve() {
    // run A < A3.in
    // xd A < A4.in

    int n; cin >> n;
    vi a(n); for(auto& x: a) cin >> x;

    dbg(n);
    dbg(a);

    cout << slv(n, a) << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(isDebugging&&1) {
        RAYA;
        RAYA;
        RAYA;

        int n = rng_int(1, 8);
        vi a(n); for(auto& x: a) x = rng_int(1, 8);
        dbg(n);
        dbg(a);

        int ans = brute(n, a);
        int gre = slv(n, a);
        dbg(gre, ans);
        chk(gre == ans);
    }

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
