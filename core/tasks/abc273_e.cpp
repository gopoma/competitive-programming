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


//* sometimes pragmas don't work, if so, just comment it!
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
 * Source: https://github.com/gopoma/competitive-programming/blob/main/lib/data-structures/1D%20Range%20Queries/SegmentTree/PersistentSegmentTree.h
 *   algorithm after usaco.guide/adv/persistent
 * Description: Persistent segment tree. Every set returns the root of a NEW version and a root
 *   is just an int. Pool: max_nodes(n, q) = 2n + (ceil(log2 n) + 1) * q + 1.
 *   Manual: PersistentSegmentTree.md
 * Time: O(n) build, O(log n) set, get and prod, O(1) all_prod and copy
 * Status: Stress-tested against brute force over all versions. No judge submission yet.
 */

template <class T>
struct PersistentSegmentTree {
  public:
    PersistentSegmentTree(int len, long long max_ops) : n(len) {
        assert(n >= 1 && max_ops >= 0);

        st.reserve(size_t(max_nodes(n, max_ops)));
        st.push_back(InternalNode());           // el nodo nulo: subarbol entero en T()
    }

    static long long max_nodes(int len, long long max_ops) {
        assert(len >= 1 && max_ops >= 0);
        return 2LL * len + (long long)(ceil_log2(len) + 1) * max_ops + 1;
    }

    int build() {
        return 0;
    }

    int build(const vector<T>& init) {
        assert(int(init.size()) == n);
        return build(0, n - 1, init);
    }

    int set(int root, int pos, T val) {
        assert(valid(root));
        assert(0 <= pos && pos < n);

        return set(root, 0, n - 1, pos, val);
    }

    T get(int root, int pos) const {
        assert(valid(root));
        assert(0 <= pos && pos < n);

        return get(root, 0, n - 1, pos);
    }

    T prod(int root, int l, int r) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        return prod(root, 0, n - 1, l, r);
    }

    T all_prod(int root) const {
        assert(valid(root));
        return st[root].val;
    }


    // PREFIJOS, ancla en l: la mayor p de [l, r] tal que f(prod(rt, l, p)) es verdadera,
    // o l - 1 si ninguna lo es. f tiene que ser T T T F F F al crecer p.
    template<class F>
    int max_right(int root, int l, int r, F pred) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_izq(root, 0, n - 1, l, r, acc, pred) - 1;
    }

    // SUFIJOS, ancla en r: la menor p de [l, r] tal que f(prod(rt, p, r)) es verdadera,
    // o r + 1 si ninguna lo es. f tiene que ser T T T F F F al DECRECER p.
    template<class F>
    int min_left(int root, int l, int r, F pred) const {
        assert(valid(root));
        assert(0 <= l && l <= r && r < n);

        T acc = T();
        return corte_der(root, 0, n - 1, l, r, acc, pred) + 1;
    }

    // Vuelca el arreglo logico de UNA version: dump(rt)[i] es lo que da get(rt, i).
    // Sirve para mirar cualquier version, incluso vieja, y no consume nodos del pool.
    // Los mismos dos descensos, pero sobre la DIFERENCIA de dos versiones: el arreglo
    // virtual que se recorre es root_after MENOS root_before. f(antes, despues) recibe los dos
    // acumulados y la resta corre por tu cuenta, asi que el monoide no necesita inverso.
    //
    // Sirve para el k-esimo menor de un rango de posiciones: con el arbol sobre el dominio
    // de valores y ver[i] = conteos de a[0..i-1], el rango [l, r) ES la diferencia entre
    // ver[l] y ver[r]. Y el centinela te dice si el k-esimo no existe.
    //
    // PRECONDICION: root_before tiene que ser una sub-version de root_after, o sea que sus
    // agregados no lo superen en ningun nodo. Se cumple solo si los dos salen de la misma
    // cadena de prefijos. Con versiones de ramas distintas la diferencia puede dar negativa
    // y la monotonia de f se rompe en silencio: no hay forma de asertarlo.
    template<class F>
    int max_right(int root_before, int root_after, int l, int r, F pred) const {
        assert(valid(root_before) && valid(root_after));
        assert(0 <= l && l <= r && r < n);

        T acc_before = T(), acc_after = T();
        return corte_izq(root_before, root_after, 0, n - 1, l, r, acc_before, acc_after, pred) - 1;
    }

    template<class F>
    int min_left(int root_before, int root_after, int l, int r, F pred) const {
        assert(valid(root_before) && valid(root_after));
        assert(0 <= l && l <= r && r < n);

        T acc_before = T(), acc_after = T();
        return corte_der(root_before, root_after, 0, n - 1, l, r, acc_before, acc_after, pred) + 1;
    }

    vector<T> dump(int root) const {
        assert(valid(root));

        vector<T> out;
        out.reserve(size_t(n));
        dump(root, 0, n - 1, out);
        return out;
    }

    int copy(int root) {
        assert(valid(root));
        return clone(root);
    }

    int size() const {
        return n;
    }

    long long nodes_used() const {
        return (long long)st.size() - 1;
    }

  private:
    struct InternalNode {
        int l = 0;
        int r = 0;
        T val{};
    };

    int n;
    vector<InternalNode> st;

    static int ceil_log2(int x) {
        int c = 0;

        while((1 << c) < x) {
            ++c;
        }

        return c;
    }

    bool valid(int rt) const {
        return 0 <= rt && rt < int(st.size());
    }

    // El nodo se arma entero antes de entrar al pool, asi que nunca se lee st[...] con una
    // referencia viva mientras se inserta.
    int new_node(int l, int r, const T& val) {
        InternalNode nd;
        nd.l = l;
        nd.r = r;
        nd.val = val;
        st.push_back(nd);
        return int(st.size()) - 1;
    }

    int clone(int k) {
        return new_node(st[k].l, st[k].r, st[k].val);
    }

    // Los mismos dos, caminando las dos versiones en lockstep. La descomposicion de [l, r]
    // depende del par (lx, rx) de la recursion y no del nodo, asi que bajar por los dos
    // hijos a la vez los mantiene cubriendo el mismo intervalo.
    template<class F>
    int corte_izq(int cur_before, int cur_after, int lx, int rx, int l, int r,
                  T& acc_before, T& acc_after, F f) const {
        if(rx < l || r < lx) {
            return r + 1;                       // disjunto: no tocar los acumulados
        }

        if(l <= lx && rx <= r) {                // el nodo entra completo en [l, r]
            T t_before = acc_before + st[cur_before].val;
            T t_after = acc_after + st[cur_after].val;

            if(f(t_before, t_after)) {
                acc_before = t_before;
                acc_after = t_after;
                return r + 1;                   // aguanta entero: saltarlo sin bajar
            }

            if(lx == rx) {
                return lx;                      // una sola posicion, y rompe: es esta
            }
        }                                       // rompe adentro: hay que bajar

        int mx = (lx + rx) / 2;
        int res = corte_izq(st[cur_before].l, st[cur_after].l, lx, mx, l, r,
                            acc_before, acc_after, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur_before].r, st[cur_after].r, mx + 1, rx, l, r,
                         acc_before, acc_after, f);
    }

    template<class F>
    int corte_der(int cur_before, int cur_after, int lx, int rx, int l, int r,
                  T& acc_before, T& acc_after, F f) const {
        if(rx < l || r < lx) {
            return l - 1;
        }

        if(l <= lx && rx <= r) {
            T t_before = st[cur_before].val + acc_before;   // el nodo a la IZQUIERDA
            T t_after = st[cur_after].val + acc_after;

            if(f(t_before, t_after)) {
                acc_before = t_before;
                acc_after = t_after;
                return l - 1;
            }

            if(lx == rx) {
                return lx;
            }
        }

        int mx = (lx + rx) / 2;
        int res = corte_der(st[cur_before].r, st[cur_after].r, mx + 1, rx, l, r,
                            acc_before, acc_after, f);     // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur_before].l, st[cur_after].l, lx, mx, l, r,
                         acc_before, acc_after, f);
    }

    // Menor p de [l, r] con f(prod(l, p)) FALSA, o r + 1. acc entra valiendo prod(l, lx - 1).
    // st[0] es el nodo nulo y su val ya es T(), asi que un subarbol sin materializar no
    // necesita caso aparte: aporta la identidad y no mueve acc.
    template<class F>
    int corte_izq(int cur, int lx, int rx, int l, int r, T& acc, F f) const {
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

        int mx = (lx + rx) / 2;
        int res = corte_izq(st[cur].l, lx, mx, l, r, acc, f);

        if(res <= r) {
            return res;                         // ya esta, no seguir
        }

        return corte_izq(st[cur].r, mx + 1, rx, l, r, acc, f);
    }

    // Mayor p de [l, r] con f(prod(p, r)) FALSA, o l - 1. acc entra valiendo prod(rx + 1, r).
    template<class F>
    int corte_der(int cur, int lx, int rx, int l, int r, T& acc, F f) const {
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

        int mx = (lx + rx) / 2;
        int res = corte_der(st[cur].r, mx + 1, rx, l, r, acc, f);   // el DERECHO primero

        if(res >= l) {
            return res;
        }

        return corte_der(st[cur].l, lx, mx, l, r, acc, f);
    }

    // st[0] es el nodo nulo: sus hijos son 0 y su val ya es T(), asi que un subarbol sin
    // materializar no necesita caso aparte.
    void dump(int cur, int lx, int rx, vector<T>& out) const {
        if(lx == rx) {
            out.push_back(st[cur].val);
            return;
        }

        int mx = (lx + rx) / 2;
        dump(st[cur].l, lx, mx, out);
        dump(st[cur].r, mx + 1, rx, out);
    }

    int build(int lx, int rx, const vector<T>& a) {
        if(lx == rx) {
            return new_node(0, 0, a[lx]);
        }

        int mx = (lx + rx) / 2;
        int lc = build(lx, mx, a);
        int rc = build(mx + 1, rx, a);
        return new_node(lc, rc, st[lc].val + st[rc].val);
    }

    int set(int cur, int lx, int rx, int p, const T& x) {
        if(lx == rx) {
            return new_node(0, 0, x);
        }

        int mx = (lx + rx) / 2;
        int lc = st[cur].l;
        int rc = st[cur].r;

        if(p <= mx) {
            lc = set(lc, lx, mx, p, x);
        } else {
            rc = set(rc, mx + 1, rx, p, x);
        }

        return new_node(lc, rc, st[lc].val + st[rc].val);
    }

    T get(int cur, int lx, int rx, int p) const {
        while(lx != rx) {
            if(cur == 0) {                      // subarbol sin materializar
                return T();
            }

            int mx = (lx + rx) / 2;

            if(p <= mx) {
                cur = st[cur].l;
                rx = mx;
            } else {
                cur = st[cur].r;
                lx = mx + 1;
            }
        }

        return st[cur].val;                     // si cur es 0, st[0].val ya es T()
    }

    T prod(int cur, int lx, int rx, int ql, int qr) const {
        if(cur == 0 || rx < ql || qr < lx) {
            return T();
        }

        if(ql <= lx && rx <= qr) {
            return st[cur].val;
        }

        int mx = (lx + rx) / 2;
        return prod(st[cur].l, lx, mx, ql, qr) + prod(st[cur].r, mx + 1, rx, ql, qr);
    }
};
struct Node {
    // size == 0 es el rango vacio, la identidad de +. pref, suf y best son sumas de
    // subarreglos, y el vacio cuenta, asi que ninguna de las tres baja de cero.
    int size = 0, mx = 0;

    Node() {}
    Node(int x) {
        size = 1;
        mx = x;
    }

    friend Node operator+(const Node& a, const Node& b) {
        Node res;
        res.size = a.size + b.size;
        res.mx = max(a.mx, b.mx);
        return res;
    }
};

//* /Template

void solve() {
    // run A < A3.in
    // xd A < A4.in


    int q; cin >> q;

    const int MAXN = int(5e5) + 5;
    const int max_ops = int(2e6) + 5;
    PersistentSegmentTree<Node> st(MAXN, max_ops);

    V<Node> start(MAXN, Node(0));
    vi roots;
    roots.reserve(5 * q);
    roots.eb(st.build(start));
    map<int, int> notebook;

    rep(q) {
        str type; cin >> type;

        int len = st.get(roots.bk, 0).mx;
        chk(len >= 0);
        int ans;
        if(type == "ADD") {
            int x; cin >> x;
            dbg(type, x);

            len++;
            roots.eb(st.set(roots.bk, len, x));
            roots.eb(st.set(roots.bk, 0, len));

            ans = x;
        } else if(type == "DELETE") {
            dbg(type);

            len = st.get(roots.bk, 0).mx;
            if(len == 0) {
            } else {
                len--;
            }

            roots.eb(st.set(roots.bk, 0, len));

            if(len == 0) {
                ans = -1;
            } else {
                ans = st.get(roots.bk, len).mx;
            }
        } else if(type == "SAVE") {
            int y; cin >> y;
            dbg(type, y);

            notebook[y] = roots.bk;

            int clen = st.get(roots.bk, 0).mx;
            if(clen == 0) {
                ans = -1;
            } else {
                ans = st.get(roots.bk, clen).mx;
            }
        } else if(type == "LOAD") {
            int z; cin >> z;
            dbg(type, z);

            roots.eb(notebook[z]);
            int clen = st.get(roots.bk, 0).mx;
            if(clen == 0) {
                ans = -1;
            } else {
                ans = st.get(roots.bk, clen).mx;
            }
        }

        cout << ans << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    if(isDebugging) {
        dbg("debug");
        setIn("xd.in");
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
