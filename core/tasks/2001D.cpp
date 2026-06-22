//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

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
mt19937 rng(0);



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

inline namespace IO {
#define SFINAE(x, ...)                                                         \
	template <class, class = void> struct x : std::false_type {};              \
	template <class T> struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

template <auto &is> struct Reader {
	template <class T> void Impl(T &t) {
		if constexpr (DefaultI<T>::value) is >> t;
		else if constexpr (Iterable<T>::value) {
			for (auto &x : t) Impl(x);
		} else if constexpr (IsTuple<T>::value) {
			std::apply([this](auto &...args) { (Impl(args), ...); }, t);
		} else static_assert(IsTuple<T>::value, "No matching type for read");
	}
	template <class... Ts> void read(Ts &...ts) { ((Impl(ts)), ...); }
};

template <class... Ts> void re(Ts &...ts) { Reader<cin>{}.read(ts...); }
#define def(t, args...)                                                        \
	t args;                                                                    \
	re(args);

template <auto &os, bool debug, bool print_nd> struct Writer {
	string comma() const { return debug ? "," : ""; }
	template <class T> constexpr char Space(const T &) const {
		return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n'
		                                                             : ' ';
	}
	template <class T> void Impl(T const &t) const {
		if constexpr (DefaultO<T>::value) os << t;
		else if constexpr (Iterable<T>::value) {
			if (debug) os << '{';
			int i = 0;
			for (auto &&x : t)
				((i++) ? (os << comma() << Space(x), Impl(x)) : Impl(x));
			if (debug) os << '}';
		} else if constexpr (IsTuple<T>::value) {
			if (debug) os << '(';
			std::apply(
			    [this](auto const &...args) {
				    int i = 0;
				    (((i++) ? (os << comma() << " ", Impl(args)) : Impl(args)),
				     ...);
			    },
			    t);
			if (debug) os << ')';
		} else static_assert(IsTuple<T>::value, "No matching type for print");
	}
	template <class T> void ImplWrapper(T const &t) const {
		if (debug) os << "\033[0;31m";
		Impl(t);
		if (debug) os << "\033[0m";
	}
	template <class... Ts> void print(Ts const &...ts) const {
		((Impl(ts)), ...);
	}
	template <class F, class... Ts>
	void print_with_sep(const std::string &sep, F const &f,
	                    Ts const &...ts) const {
		ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
	}
	void print_with_sep(const std::string &) const { os << '\n'; }
};

template <class... Ts> void pr(Ts const &...ts) {
	Writer<cout, false, true>{}.print(ts...);
}
template <class... Ts> void ps(Ts const &...ts) {
	Writer<cout, false, true>{}.print_with_sep(" ", ts...);
}
}  // namespace IO

inline namespace Debug {

#ifdef LOCAL
#include "helpers/debug.h"

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
}  // namespace Debug



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

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;
//? /Custom Helpers



//* Template
/**
 * Description: 1D range increment and sum query.
 * Source: USACO Counting Haybales
 	* https://codeforces.com/blog/entry/82400
 * Verification: USACO Counting Haybales
 */

struct LazySeg {
	struct F { // lazy update
		ll inc = 0;
		F() {}
		F(int x) { inc = x; }
		F& operator*=(const F& a) { inc += a.inc; return *this; }
	}; V<F> lazy;
	struct T { // data you need to store for each interval
		ll sz = 1, mn = BIG, sum = 0;
		T() {}
		T(int x) { mn = sum = x; }
		friend T operator+(const T& a, const T& b) {
			T res; res.sz = a.sz+b.sz;
			res.mn = min(a.mn,b.mn), res.sum = a.sum+b.sum;
			return res;
		}
		T& operator*=(const F& a) {
			mn += a.inc; sum += (ll)sz*a.inc; return *this; }
	}; V<T> seg;
	int SZ = 1;
	void init(const V<T>& _seg) {
		while (SZ < sz(_seg)) SZ *= 2;
		seg.rsz(2*SZ); lazy.rsz(2*SZ);
		F0R(i,SZ) seg[SZ+i] = _seg[i];
		ROF(i,1,SZ) pull(i);
	}
	void push(int ind) { /// modify values for current node
		seg[ind] *= lazy[ind];
		if (ind < SZ) F0R(i,2) lazy[2*ind+i] *= lazy[ind];
		lazy[ind] = F();
	} // recalc values for current node
	void pull(int ind) { seg[ind] = seg[2*ind]+seg[2*ind+1]; }
	void upd(int lo, int hi, F inc, int ind, int L, int R) {
		push(ind); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
			lazy[ind] = inc; push(ind); return; }
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M);
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
	}
	void upd(int lo, int hi, int inc) { upd(lo,hi,{inc},1,0,SZ-1); }
	T query(int lo, int hi, int ind, int L, int R) {
		push(ind); if (lo > R || L > hi) return T();
		if (lo <= L && R <= hi) return seg[ind];
		int M = (L+R)/2;
		return query(lo,hi,2*ind,L,M)+query(lo,hi,2*ind+1,M+1,R);
	}
	T query(int lo, int hi) { return query(lo,hi,1,0,SZ-1); }
};

/**
 * Description: 1D point update and range query where \texttt{cmb} is
 	* any associative operation. \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 * API: SegTree<node> tree; tree.init(int(n));
 */

tcT> struct SegTree { // cmb(ID,b) = b
	// const T ID{}; T cmb(T a, T b) { return a+b; }
    T ID{}; T cmb(T a, T b) { return a+b; }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// zero-indexed, inclusive
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}
	/// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
	/// 	if (r < lo || val > seg[ind]) return -1;
	/// 	if (l == r) return l;
	/// 	int m = (l+r)/2;
	/// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
	/// 	return first_at_least(lo,val,2*ind+1,m+1,r);
	/// }
};

class SegmentTree {
private:
    std::vector<int> seg;
    std::vector<int> lazy;
    std::vector<int> arr;
    int n;

    void build(int node, int st, int en) {
        if (st == en) {
            seg[node] = arr[st];
            return;
        }

        int mid = (st + en) / 2;

        // Llamada recursiva para el hijo izquierdo
        build(2 * node, st, mid);

        // Llamada recursiva para el hijo derecho
        build(2 * node + 1, mid + 1, en);

        // Actualización del nodo padre con los valores de los hijos
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }

    void update(int node, int st, int en, int l, int r, int val) {
        if (lazy[node] != 0) { // Si el nodo es "lazy", lo actualiza
            seg[node] += (en - st + 1) * lazy[node];

            if (st != en) { // Si los hijos existen, los marca como "lazy"
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0; // Ya no es "lazy"
        }

        if (en < l || st > r) { // Caso 1: fuera del rango
            return;
        }

        if (st >= l && en <= r) { // Caso 2: completamente dentro del rango
            seg[node] += (en - st + 1) * val;
            if (st != en) {
                lazy[2 * node] += val; // Marca a los hijos como "lazy"
                lazy[2 * node + 1] += val;
            }
            return;
        }

        // Caso 3: parcialmente dentro del rango
        int mid = (st + en) / 2;

        // Llamada recursiva para actualizar el hijo izquierdo
        update(2 * node, st, mid, l, r, val);
        // Llamada recursiva para actualizar el hijo derecho
        update(2 * node + 1, mid + 1, en, l, r, val);

        // Actualización del nodo padre con los valores de los hijos
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }

    int query(int node, int st, int en, int l, int r) {
        if (lazy[node] != 0) { // Si el nodo es "lazy", lo actualiza
            seg[node] += (en - st + 1) * lazy[node];
            if (st != en) { // Verifica si los hijos existen
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0; // Ya no es "lazy"
        }

        if (en < l || st > r) { // Caso 1: fuera del rango
            return 0;
        }

        if (l <= st && en <= r) { // Caso 2: completamente dentro del rango
            return seg[node];
        }

        int mid = (st + en) / 2;

        // Consulta del hijo izquierdo
        int q1 = query(2 * node, st, mid, l, r);

        // Consulta del hijo derecho
        int q2 = query(2 * node + 1, mid + 1, en, l, r);

        return q1 + q2;
    }

public:
    SegmentTree(int size, std::vector<int>& elements) {
        n = size;
        arr = elements;
        seg.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1);
    }
	// Constructor sin arreglo, inicializa todo a cero
    SegmentTree(int size) {
        n = size;
        arr.assign(n, 0); // Inicializa el arreglo con ceros
        seg.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1);
    }
    void update(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
// /here goes the template!

struct node_mx {
	long long val;
    int idx;

	node_mx(): idx(-79), val(-BIG) {}

	node_mx(int _idx, long long _val) : idx(_idx), val(_val) {}

	node_mx operator + (const node_mx &rhs) const {
        if(val > rhs.val) return node_mx(idx, val);
        else if(val == rhs.val) return node_mx(min(idx, rhs.idx), val);
        else return node_mx(rhs.idx, rhs.val);
	}
};

struct node_mn {
	long long val;
    int idx;

	node_mn(): idx(-79), val(BIG) {}

	node_mn(int _idx, long long _val) : idx(_idx), val(_val) {}

	node_mn operator + (const node_mn &rhs) const {
        if(val < rhs.val) return node_mn(idx, val);
        else if(val == rhs.val) return node_mn(min(idx, rhs.idx), val);
        else return node_mn(rhs.idx, rhs.val);
	}
};

//* /Template

vl brute(ll n, vl a) {
    vvl where(n + 5);
    for(int i = 0; i < n; i++) where[a[i]].eb(i);

    LazySeg st;
    ll current_tar_size = -79;
    {
        ll tot_size = 1;
        while(tot_size < n) tot_size *= 2LL;
        V<LazySeg::T> initial_data(tot_size);

        set<ll> uu;
        for(int i = n - 1; i >= 0; i--) {
            uu.emplace(a[i]);
            initial_data[i] = LazySeg::T(sz(uu));
        }
        st.init(initial_data);
        current_tar_size = sz(uu);
    }
    chk(current_tar_size != -79);


    bool inMaxPhase = true;
    vl ans;
    ll L = 0;
    vb already(n + 5);
    while(L < n && current_tar_size > 0) {
        pl todo;
        if(inMaxPhase) {
            //? maximum value
            //? minimum index
            pl tar = mp(-BIG, BIG);
            for(; L < n; L++) {
                ll val = st.query(L, L).sum;
                if(val != current_tar_size) break;
                if(already[a[L]]) continue;
                ckmax(tar, mp(a[L], -L));
            }
            todo = tar;
            todo.s *= -1LL;
        } else {
            //? minimum value
            //? minimum index
            pl tar = mp(BIG, BIG);
            for(; L < n; L++) {
                ll val = st.query(L, L).sum;
                if(val != current_tar_size) break;
                if(already[a[L]]) continue;
                ckmin(tar, mp(a[L], L));
            }
            todo = tar;
        }
        auto [val, idx] = todo;
        st.upd(where[val].ft, where[val].bk, -1);
        ans.eb(val);
        current_tar_size--;
        inMaxPhase = !inMaxPhase;
        L = idx + 1;
        already[a[idx]] = true;
    }
    return ans;
}

vl slv2(ll n, vl a) {
    SegTree<node_mx> st_mx; st_mx.init(n);
    SegTree<node_mn> st_mn; st_mn.init(n);

    vvl where(n + 5);
    for(int i = 0; i < n; i++) {
        where[a[i]].eb(i);
        st_mx.upd(i, node_mx(i, a[i]));
        st_mn.upd(i, node_mn(i, a[i]));
    }

    ll tar_size = -79;
    vi tree(4 * n + 5, 0);
    const ll MAXN = n;
    SegmentTree st(MAXN);
    {
        set<ll> uu;
        for(int i = n - 1; i >= 0; i--) {
            uu.emplace(a[i]);
            st.update(i, i, sz(uu));
        }
        tar_size = sz(uu);
    }
    assert(tar_size != -79);
    //? dbg(MAXN);
    //? dbg(tar_size);

    auto ddd = [&]() {
        vl xd;
        for(int i = 0; i < MAXN; i++) {
            xd.eb(st.query(i, i));
        }
        dbg(xd);
    }; //? ddd();

    vl ans;
    ll L = 0;
    bool inMaxPhase = true;
    while(L < n && tar_size > 0) {
        //? RAYA;
        //? dbg(tar_size);
        //? ddd();
        ll fixedLeft, fixedRight;
        {
            ll left = L - 1; //? always bad
            ll right = MAXN; //? always good
            while(left + 1 < right) {
                ll middle = (left + right) / 2LL;
                if(st.query(middle, middle) < tar_size) right = middle;
                else left = middle;
            }
            fixedRight = right - 1;
        }
        {
            ll left = L - 1; //? always bad
            ll right = MAXN; //? always good
            while(left + 1 < right) {
                ll middle = (left + right) / 2LL;
                if(st.query(middle, middle) < tar_size + 1) right = middle;
                else left = middle;
            }
            fixedLeft = right;
        }
        //? dbg(fixedLeft, fixedRight);
        pl tar;
        if(inMaxPhase) {
            auto node = st_mx.query(fixedLeft, fixedRight);
            tar = mp(node.idx, node.val);
        } else {
            auto node = st_mn.query(fixedLeft, fixedRight);
            tar = mp(node.idx, node.val);
        }
        auto [idx, val] = tar;
        //? dbg(idx, val);


        //? dbg(where[val].ft, where[val].bk);
        st.update(where[val].ft, where[val].bk, -1);
        L = idx + 1;
        tar_size--;
        each(x, where[val]) {
            st_mx.upd(x, node_mx());
            st_mn.upd(x, node_mn());
        }
        inMaxPhase = !inMaxPhase;
        ans.eb(val);
    }
    return ans;
}

vl slv(ll n, vl a) {
    SegTree<node_mx> st_mx; st_mx.init(n);
    SegTree<node_mn> st_mn; st_mn.init(n);

    vvl where(n + 5);
    for(int i = 0; i < n; i++) {
        where[a[i]].eb(i);
        st_mx.upd(i, node_mx(i, a[i]));
        st_mn.upd(i, node_mn(i, a[i]));
    }

    ll tar_size = -79;
    vi tree(4 * n + 5, 0);
    const ll MAXN = n;
    SegmentTree st(MAXN);
    {
        set<ll> uu;
        for(int i = n - 1; i >= 0; i--) {
            uu.emplace(a[i]);
            st.update(i, i, sz(uu));
        }
        tar_size = sz(uu);
    }
    assert(tar_size != -79);
    //? dbg(MAXN);
    //? dbg(tar_size);

    auto ddd = [&]() {
        vl xd;
        for(int i = 0; i < MAXN; i++) {
            xd.eb(st.query(i, i));
        }
        dbg(xd);
    }; //? ddd();

    vl ans;
    ll L = 0;
    bool inMaxPhase = true;
    while(L < n && tar_size > 0) {
        //? RAYA;
        //? dbg(tar_size);
        //? ddd();
        ll fixedLeft, fixedRight;
        {
            ll left = L - 1; //? always bad
            ll right = MAXN; //? always good
            while(left + 1 < right) {
                ll middle = (left + right) / 2LL;
                if(st.query(middle, middle) < tar_size) right = middle;
                else left = middle;
            }
            fixedRight = right - 1;
        }
        {
            ll left = L - 1; //? always bad
            ll right = MAXN; //? always good
            while(left + 1 < right) {
                ll middle = (left + right) / 2LL;
                if(st.query(middle, middle) < tar_size + 1) right = middle;
                else left = middle;
            }
            fixedLeft = right;
        }
        //? dbg(fixedLeft, fixedRight);
        pl tar;
        if(inMaxPhase) {
            auto node = st_mx.query(fixedLeft, fixedRight);
            tar = mp(node.idx, node.val);
        } else {
            auto node = st_mn.query(fixedLeft, fixedRight);
            tar = mp(node.idx, node.val);
        }
        auto [idx, val] = tar;
        //? dbg(idx, val);


        //? dbg(where[val].ft, where[val].bk);
        st.update(where[val].ft, where[val].bk, -1);
        L = idx + 1;
        tar_size--;
        each(x, where[val]) {
            st_mx.upd(x, node_mx());
            st_mn.upd(x, node_mn());
        }
        inMaxPhase = !inMaxPhase;
        ans.eb(val);
    }
    return ans;
}

void solve() {
    def(ll, n);
    vl a(n); re(a);
    //? dbg(n);
    //? dbg(a);

    vl ans = slv(n, a);
    //? dbg(ans);
    ps(sz(ans));
    ps(ans);
}

//? Generator
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator


signed main() {
    setIO();
    //? setIn("2001D.in");
    //? ios_base::sync_with_stdio(false);
    //? cin.tie(nullptr);

    while(0) {
        RAYA;
        ll n = rng_ll(1, 10);
        vl a(n); each(x, a) x = rng_ll(1, n);
        dbg(n);
        dbg(a);
        dbg("Brute");
        vl ans = brute(n, a);
        dbg("Greedy");
        vl greedy = slv(n, a);
        dbg(ans);
        dbg(greedy);
        chk(ans == greedy);
    }

    ll t = 1; re(t);

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
