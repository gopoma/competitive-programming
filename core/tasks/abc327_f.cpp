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
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing


#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
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
 * Date: 2026-10-01
 * Source: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/SegmentTree/LazySegmentTree.h
 *   algorithm after atcoder.github.io/ac-library
 * Description: Segment tree with lazy propagation. Node() neutral, a + b associative,
 *   node *= f applies an update to a whole interval, f *= g stacks g after f.
 *   max_right / min_left descend the tree. Manual: LazySegmentTree.md
 * Time: O(n) build, O(log n) per operation, O(1) all_prod
 * Status: Codeforces EDU submission 394467936, AC 125 ms (uses max_right).
 *   Stress-tested, plus 811620 checks on operator[].
 */

template <class Node, class LazyUpdate>
struct LazySegmentTree {
  public:
    LazySegmentTree() : LazySegmentTree(0) {}

    explicit LazySegmentTree(int len) {
        SZ = 1, LOG = 0;

        while (SZ < max(1, len)) {
            SZ *= 2;
            ++LOG;
        }

        n = SZ;                                 // sin vector, n es el tamano con padding
        seg.assign(2 * SZ, Node());             // todo identidad, no hace falta pull:
        lazy.assign(SZ, LazyUpdate());          // Node() + Node() == Node()
    }

    explicit LazySegmentTree(const vector<Node>& init) : n(int(init.size())) {
        SZ = 1, LOG = 0;

        while (SZ < max(1, n)) {
            SZ *= 2;
            ++LOG;
        }

        seg.assign(2 * SZ, Node());
        lazy.assign(SZ, LazyUpdate());

        for (int i = 0; i < n; i++) {
            seg[SZ + i] = init[i];
        }

        for (int i = SZ - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void set(int pos, Node val) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        seg[pos] = val;

        for (int i = 1; i <= LOG; i++) {
            pull(pos >> i);
        }
    }

    Node get(int pos) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        return seg[pos];
    }

    // Azucar de lectura, para que se lea como un vector: seg[i] es exactamente get(i).
    // Devuelve por VALOR, pero NO es const, y es el unico de la familia asi: leer obliga a
    // bajar el lazy del camino con push. O sea que no se puede leer de un const&.
    Node operator[](int pos) {
        return get(pos);
    }

    Node prod(int l, int r) {
        assert(0 <= l && l <= r && r < n);

        l += SZ, r += SZ;                       // hojas inclusivas: seg[l] .. seg[r]

        for (int i = LOG; i >= 1; i--) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {                 // l no arranca su bloque de 2^i
                push(l >> i);
            }

            if ((r & m) != m) {                 // r no termina su bloque de 2^i
                push(r >> i);
            }
        }

        Node sml, smr;

        while (l <= r) {
            if (l & 1) {                        // l es hijo derecho: su padre se sale
                sml = sml + seg[l++];
            }

            if (!(r & 1)) {                     // r es hijo izquierdo: su padre se sale
                smr = seg[r--] + smr;
            }

            l >>= 1, r >>= 1;
        }

        return sml + smr;
    }

    Node all_prod() const {
        return seg[1];
    }

    // Vuelca el arreglo logico para depurar: dump()[i] es exactamente lo que da get(i).
    // NO es const: baja todos los lazy pendientes, igual que get hace sobre un solo camino.
    // El orden k = 1 .. SZ-1 es correcto por construccion, porque el padre de k es k / 2 < k.
    vector<Node> dump() {
        for (int k = 1; k < SZ; k++) {
            push(k);
        }

        return vector<Node>(seg.begin() + SZ, seg.begin() + SZ + n);
    }

    void apply(int pos, LazyUpdate upd) {
        assert(0 <= pos && pos < n);

        pos += SZ;

        for (int i = LOG; i >= 1; i--) {
            push(pos >> i);
        }

        seg[pos] *= upd;

        for (int i = 1; i <= LOG; i++) {
            pull(pos >> i);
        }
    }

    void apply(int l, int r, LazyUpdate upd) {
        assert(0 <= l && l <= r && r < n);

        l += SZ, r += SZ;                       // hojas inclusivas: seg[l] .. seg[r]

        for (int i = LOG; i >= 1; i--) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {
                push(l >> i);
            }

            if ((r & m) != m) {
                push(r >> i);
            }
        }

        int l2 = l, r2 = r;

        while (l <= r) {
            if (l & 1) {
                all_apply(l++, upd);
            }

            if (!(r & 1)) {
                all_apply(r--, upd);
            }

            l >>= 1, r >>= 1;
        }

        l = l2, r = r2;

        for (int i = 1; i <= LOG; i++) {
            int m = (1 << i) - 1;

            if ((l & m) != 0) {
                pull(l >> i);
            }

            if ((r & m) != m) {
                pull(r >> i);
            }
        }
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template <class F>
    int max_right(int l, int r, F pred) {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_izq(l, r, 1, 0, SZ - 1, acc, pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template <class F>
    int min_left(int l, int r, F pred) {
        assert(0 <= l && l <= r && r < n);

        Node acc = Node();
        return corte_der(l, r, 1, 0, SZ - 1, acc, pred) + 1;
    }


  private:
    int n, SZ, LOG;
    vector<Node> seg;
    vector<LazyUpdate> lazy;

    void pull(int k) {
        seg[k] = seg[2 * k] + seg[2 * k + 1];
    }

    // Keeps seg[k] equal to the true aggregate of the subtree at k: f lands on the value
    // right away, and only an internal node has to remember it for its children.
    void all_apply(int k, const LazyUpdate& f) {
        seg[k] *= f;

        if (k < SZ) {
            lazy[k] *= f;
        }
    }

    void push(int k) {
        all_apply(2 * k, lazy[k]);
        all_apply(2 * k + 1, lazy[k]);
        lazy[k] = LazyUpdate();
    }

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, L - 1).
    // El agregado se lee sin push: all_apply mantiene seg[ind] siempre al dia.
    template <class F>
    int corte_izq(int l, int r, int ind, int L, int R, Node& acc, F f) {
        if (R < l || r < L) {
            return r + 1;                       // disjunto: no tocar acc
        }

        if (l <= L && R <= r) {                 // el nodo entra completo en [l, r]
            Node t = acc + seg[ind];            // acc a la izquierda, el nodo a la derecha

            if (f(t)) {
                acc = t;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if (L == R) {
                return L;                       // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        push(ind);                              // una hoja nunca llega aca

        int M = (L + R) / 2;
        int res = corte_izq(l, r, 2 * ind, L, M, acc, f);

        if (res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(l, r, 2 * ind + 1, M + 1, R, acc, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(R + 1, r).
    template <class F>
    int corte_der(int l, int r, int ind, int L, int R, Node& acc, F f) {
        if (R < l || r < L) {
            return l - 1;
        }

        if (l <= L && R <= r) {
            Node t = seg[ind] + acc;            // el nodo a la IZQUIERDA de acc

            if (f(t)) {
                acc = t;
                return l - 1;
            }

            if (L == R) {
                return L;
            }
        }

        push(ind);

        int M = (L + R) / 2;
        int res = corte_der(l, r, 2 * ind + 1, M + 1, R, acc, f);   // el DERECHO primero

        if (res >= l) {
            return res;
        }

        return corte_der(l, r, 2 * ind, L, M, acc, f);
    }
};



struct LazyUpdate { // lazy update
    // "si has, asignar v a todo el intervalo; despues sumar a a todo el intervalo"
    bool has = false;
    int v = 0, a = 0;

    LazyUpdate() {}

    static LazyUpdate assign(int x) {
        LazyUpdate f;
        f.has = true;
        f.v = x;
        return f;
    }

    static LazyUpdate add(int x) {
        LazyUpdate f;
        f.a = x;
        return f;
    }

    // f actua DESPUES: un assign posterior gana y borra el add que quedaba debajo, mientras
    // que un add posterior solo se acumula. Por eso assign y add no conmutan.
    LazyUpdate& operator*=(const LazyUpdate& f) {
        if(f.has) {
            has = true;
            v = f.v;
            a = f.a;
        } else {
            a += f.a;
        }

        return *this;
    }
};

struct Node { // data you need to store for each interval
    int size = 0, mx = 0, mn = 0;  // size == 0 es el rango vacio

    Node() {}
    Node(int x) {
        size = 1;
        mx = mn = x;
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
        res.mn = min(a.mn, b.mn);
        return res;
    }

    // size es lo que permite que el update escale a todo el intervalo de una sola vez.
    Node& operator*=(const LazyUpdate& f) {
        if(size == 0) {                         // la identidad se queda identidad
            return *this;
        }

        if(f.has) {
            mx = mn = f.v + f.a;
        } else {
            mx += f.a;
            mn += f.a;
        }

        return *this;
    }
};

//* /Template

void solve() {
    // run A < A3.in
    // xd A < A4.in

    int n, d, w; cin >> n >> d >> w;
    // d is for time
    // w is for location

    vpi points(n);
    for(auto& [T, X]: points) {
        cin >> T >> X;
    }
    sor(points);
    dbg(n, d, w);
    dbg(points);

    int MAXN = int(2e5) + 100;
    if(isDebugging) {
        MAXN = 10;
    }
    vvi blocks(MAXN);
    for(auto& [T, X]: points) {
        blocks[X].eb(T);
    }


    V<Node> start(MAXN, Node(0));
    LazySegmentTree<Node, LazyUpdate> st(start);
    int res = 0;
    for(int loc = 0; loc < MAXN; loc++) {
        if(loc - w >= 0) {
            // remove unnecesary rows
            for(auto& t: blocks[loc - w]) {
                int l = max(0, t - d + 1);
                int r = t;
                st.apply(l, r, LazyUpdate::add(-1));
            }
        }

        {
            // add current row
            for(auto& t: blocks[loc]) {
                int l = max(0, t - d + 1);
                int r = t;
                st.apply(l, r, LazyUpdate::add(1));
            }
        }

        int lre = st.all_prod().mx;
        ckmax(res, lre);
    }

    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

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
