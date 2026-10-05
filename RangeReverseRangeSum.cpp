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

ll custom_abs(ll x) {
    if(x < 0) return -x;
    return +x;
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
 * Description: Implicit treap. A vector with O(log n) insert, erase, reverse, rotate, move,
 *   range query and range update. Manual, Node contract and examples: ImplicitTreap.md
 * Time: O(n) build, O(log n) expected rest. Memory: n + q nodes, q = expected inserts
 * Source: own. Verification: stress tested against brute force, see ImplicitTreap.md
 */

struct NoLazy {};                               // marcador: el treap no lleva updates de rango

template <class Node, class LazyUpdate = NoLazy>
struct ImplicitTreap {
  public:
    static constexpr bool HAS_LAZY = !is_same<LazyUpdate, NoLazy>::value;

    explicit ImplicitTreap(long long q) {
        reserve_pool(0, q);
    }

    // gen(i) se llama con i = 0, 1, ..., n - 1 EN ESE ORDEN, y el valor va directo al pool.
    // Asi se puede leer de un stream sin armar ningun vector intermedio.
    template <class F>
    ImplicitTreap(int n, long long q, F gen) {
        assert(n >= 0);
        reserve_pool(n, q);

        for(int i = 0; i < n; i++) {
            new_node(gen(i));                   // el nodo de la posicion i queda en 1 + i
        }

        root = build(0, n - 1);
    }

    ImplicitTreap(const vector<Node>& v, long long q)
        : ImplicitTreap((int)v.size(), q, [&](int i) { return v[i]; }) {}

    static long long max_nodes(long long n, long long q) {
        assert(n >= 0 && q >= 0);
        return n + q;
    }

    int size() const {
        return st[root].sz;
    }

    long long nodes_used() const {
        return (long long)st.size() - 1;
    }

    static size_t node_bytes() {
        return sizeof(InternalNode);
    }

    void insert(int i, Node x) {
        assert(0 <= i && i <= size());          // i == size() agrega al final
        int a, b;
        split(root, i, a, b);
        root = merge(merge(a, new_node(x)), b);
    }

    void erase(int i) {
        assert(0 <= i && i < size());
        int a, b, c, tmp;
        split(root, i, a, tmp);
        split(tmp, 1, b, c);
        root = merge(a, c);
    }

    void set(int p, Node x) {
        assert(0 <= p && p < size());
        int a, b, c, tmp;
        split(root, p, a, tmp);
        split(tmp, 1, b, c);
        st[b].val = x;
        pull(b);
        root = merge(merge(a, b), c);
    }

    Node get(int p) const {
        assert(0 <= p && p < size());
        return prod(p, p);
    }

    Node prod(int l, int r) const {
        assert(0 <= l && l <= r && r < size());
        Node acc;
        bool has = false;
        prod(root, 0, l, r, LazyUpdate(), false, acc, has);
        return acc;
    }

    Node all_prod() const {
        return st[root].agg;
    }

    void apply(int p, LazyUpdate f) {
        static_assert(HAS_LAZY, "este ImplicitTreap se instancio sin LazyUpdate");
        assert(0 <= p && p < size());
        apply(p, p, f);
    }

    void apply(int l, int r, LazyUpdate f) {
        static_assert(HAS_LAZY, "este ImplicitTreap se instancio sin LazyUpdate");
        assert(0 <= l && l <= r && r < size());
        apply(root, 0, l, r, f);
    }

    void reverse(int l, int r) {
        assert(0 <= l && l <= r && r < size());
        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, r - l + 1, b, c);
        all_rev(b);
        root = merge(merge(a, b), c);
    }

    void rotate(int l, int r, int k) {
        assert(0 <= l && l <= r && r < size());
        int len = r - l + 1;
        assert(0 <= k && k < len);

        if(k == 0) {
            return;
        }

        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, len, b, c);
        int b1, b2;
        split(b, k, b1, b2);
        root = merge(merge(a, merge(b2, b1)), c);
    }

    // Corta a[l..r] y lo pega justo antes del que era a[p]. p se cuenta sobre el arreglo
    // ORIGINAL, y tiene que caer afuera del bloque que se mueve.
    void move(int l, int r, int p) {
        assert(0 <= l && l <= r && r < size());
        assert(0 <= p && p <= size() && (p <= l || p > r));
        int a, b, c, tmp;
        split(root, l, a, tmp);
        split(tmp, r - l + 1, b, c);
        int rest = merge(a, c);
        int dest = (p <= l) ? p : p - (r - l + 1);
        int x, y;
        split(rest, dest, x, y);
        root = merge(merge(x, b), y);
    }

  private:
    struct InternalNode {
        int lc = 0;
        int rc = 0;
        unsigned pri = 0;
        int sz = 1;
        Node val{};                             // el elemento propio, cubre 1 posicion
        Node agg{};                             // el agregado del subarbol, cubre sz posiciones
        bool rev = false;
        LazyUpdate lz{};                        // si es NoLazy, entra en el relleno: 0 bytes
    };

    vector<InternalNode> st;
    int root = 0;
    unsigned rng = next_seed();             // ver next_seed(): semilla del reloj, no fija

    void reserve_pool(long long n, long long q) {
        assert(n >= 0 && q >= 0);
        st.reserve(size_t(max_nodes(n, q)) + 1);
        st.push_back(InternalNode());           // el nodo nulo
        st[0].sz = 0;
    }

    //? Para Codeforces, o cualquier lugar donde puedan hackearte: la semilla sale del reloj.
    //? Con una semilla fija las prioridades son identicas en cada corrida, y un atacante que
    //? conoce la secuencia puede elegir las posiciones de insert para hacer el arbol profundo.
    //? Medido: un hill climbing de 3000 evaluaciones duplica la profundidad.
    //? Para depurar con una corrida reproducible, descomenta esto:
    // #define IMPLICIT_TREAP_SEED 2463534242u
    static unsigned next_seed() {
#ifdef IMPLICIT_TREAP_SEED
        static unsigned s = IMPLICIT_TREAP_SEED;
#else
        static unsigned s =
            (unsigned)chrono::high_resolution_clock::now().time_since_epoch().count() | 1u;
#endif
        s ^= s << 13;                           // xorshift32 nunca sale de los no nulos,
        s ^= s >> 17;                           // asi que el | 1u alcanza para no quedar en 0
        s ^= s << 5;
        return s;
    }

    unsigned next_pri() {                       // xorshift: no depende de <random>
        rng ^= rng << 13;
        rng ^= rng >> 17;
        rng ^= rng << 5;
        return rng;
    }

    int new_node(const Node& x) {
        InternalNode t;
        t.pri = next_pri();
        t.val = x;
        t.agg = x;
        st.push_back(t);
        return (int)st.size() - 1;
    }

    // Los nodos de las posiciones 0..n-1 ya estan en el pool, en los indices 1..n y EN ORDEN,
    // asi que solo hay que enlazarlos balanceado. Eso no cumple la propiedad de heap, y medido
    // no importa: tras cualquier carga real la profundidad converge a la de un treap aleatorio,
    // y arrancar balanceado es mas chato que arrancar con el arbol cartesiano de las prioridades.
    int build(int lo, int hi) {
        if(lo > hi) {
            return 0;
        }

        int mid = lo + (hi - lo) / 2;
        int t = 1 + mid;
        st[t].lc = build(lo, mid - 1);
        st[t].rc = build(mid + 1, hi);
        pull(t);
        return t;
    }

    // Saltea los subarboles vacios, asi operator+ nunca recibe Node() y el usuario no necesita
    // identidad ni guardas de rango vacio.
    void pull(int t) {
        st[t].sz = 1 + st[st[t].lc].sz + st[st[t].rc].sz;
        Node a = st[t].val;

        if(st[t].lc) {
            a = st[st[t].lc].agg + a;
        }

        if(st[t].rc) {
            a = a + st[st[t].rc].agg;
        }

        st[t].agg = a;
    }

    // El arbol es la autoridad del largo: 1 para el elemento propio, sz para el agregado.
    void all_apply(int t, const LazyUpdate& f) {
        if(!t) {
            return;
        }

        if constexpr (HAS_LAZY) {
            st[t].val.apply(f, 1);
            st[t].agg.apply(f, st[t].sz);
            st[t].lz *= f;
        }
    }

    // El flag queda pendiente para los HIJOS: los hijos de t ya quedan en el orden correcto.
    void all_rev(int t) {
        if(!t) {
            return;
        }

        st[t].rev = !st[t].rev;
        swap(st[t].lc, st[t].rc);
        st[t].agg.reverse();
    }

    void push(int t) {
        if constexpr (HAS_LAZY) {                // incondicional, como en LazySegmentTree
            all_apply(st[t].lc, st[t].lz);
            all_apply(st[t].rc, st[t].lz);
            st[t].lz = LazyUpdate();
        }

        if(st[t].rev) {
            all_rev(st[t].lc);
            all_rev(st[t].rc);
            st[t].rev = false;
        }
    }

    void split(int t, int k, int& a, int& b) {   // los primeros k van a 'a'
        if(!t) {
            a = b = 0;
            return;
        }

        push(t);

        if(st[st[t].lc].sz + 1 <= k) {
            a = t;
            split(st[t].rc, k - st[st[t].lc].sz - 1, st[a].rc, b);
            pull(a);
        } else {
            b = t;
            split(st[t].lc, k, a, st[b].lc);
            pull(b);
        }
    }

    int merge(int a, int b) {
        if(!a || !b) {
            return a ? a : b;
        }

        if(st[a].pri > st[b].pri) {
            push(a);
            st[a].rc = merge(st[a].rc, b);
            pull(a);
            return a;
        }

        push(b);
        st[b].lc = merge(a, st[b].lc);
        pull(b);
        return b;
    }

    static void join(Node& acc, bool& has, const Node& x) {
        if(has) {
            acc = acc + x;
        } else {
            acc = x;
            has = true;
        }
    }

    // Descenso de lectura pura: lo pendiente viaja en f y en rv, no se escribe nada. Por eso
    // una consulta no reestructura ni ensucia el arbol.
    void prod(int t, int lo, int l, int r, LazyUpdate f, bool rv, Node& acc, bool& has) const {
        if(!t) {
            return;
        }

        int hi = lo + st[t].sz - 1;

        if(hi < l || r < lo) {
            return;                             // disjunto
        }

        if(l <= lo && hi <= r) {
            Node piece = st[t].agg;

            if(rv) {
                piece.reverse();                // el subarbol esta logicamente al reves
            }

            if constexpr (HAS_LAZY) {
                piece.apply(f, st[t].sz);
            }

            join(acc, has, piece);
            return;
        }

        LazyUpdate down = st[t].lz;

        if constexpr (HAS_LAZY) {
            down *= f;                          // el lz del nodo primero, el carry despues
        }

        // rv es el flag ENTRANTE: dice si los hijos de t estan dados vuelta
        int fst = rv ? st[t].rc : st[t].lc;
        int snd = rv ? st[t].lc : st[t].rc;
        bool rv2 = rv != st[t].rev;              // esto baja
        int mp = lo + st[fst].sz;

        prod(fst, lo, l, r, down, rv2, acc, has);

        if(l <= mp && mp <= r) {
            Node own = st[t].val;

            if constexpr (HAS_LAZY) {
                own.apply(f, 1);                 // el propio usa f, no down
            }

            join(acc, has, own);
        }

        prod(snd, mp + 1, l, r, down, rv2, acc, has);
    }

    void apply(int t, int lo, int l, int r, const LazyUpdate& f) {
        if(!t) {
            return;
        }

        int hi = lo + st[t].sz - 1;

        if(hi < l || r < lo) {
            return;
        }

        if(l <= lo && hi <= r) {
            all_apply(t, f);
            return;
        }

        push(t);                                 // aca si hay que empujar: vamos a escribir
        int mp = lo + st[st[t].lc].sz;
        apply(st[t].lc, lo, l, r, f);

        if(l <= mp && mp <= r) {
            st[t].val.apply(f, 1);
        }

        apply(st[t].rc, mp + 1, l, r, f);
        pull(t);
    }
};

struct Node {
    ll sum = 0;

    Node() {}
    Node(ll x) : sum(x) {}

    friend Node operator+(const Node& a, const Node& b) {
        return Node(a.sum + b.sum);
    }

    void reverse() {}
};
//* /Template

void solve() {
    // run A < A3.in
    // xd A < A4.in

    int n, q; cin >> n >> q;
    vi a(n); for(auto& x: a) cin >> x;
    dbg(n, q);
    dbg(a);

    V<Node> start(n);
    for(int i = 0; i < n; i++)
        start[i] = Node(a[i]);
    ImplicitTreap<Node> st(start, q);

    rep(q) {
        int type, l, r; cin >> type >> l >> r; r--;

        if(type == 0) {
            if(l <= r)
                st.reverse(l, r);
        } else {
            ll res = 0;
            if(l <= r)
                res = st.prod(l, r).sum;
            cout << res << "\n";
        }
    }
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
