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

//? /Custom Helpers



//* Template
struct AngelBeats {
    using i64 = long long;
    static constexpr i64 INF = numeric_limits<i64>::max() / 2.1;

    struct alignas(32) Node {
        i64 sum = 0, g1 = 0, l1 = 0;
        i64 g2 = -INF, gc = 1, l2 = INF, lc = 1, add = 0;
    };

    vector<Node> v;
    i64 n, log;

    AngelBeats() {}
    AngelBeats(int _n) : AngelBeats(vector<i64>(_n)) {}
    AngelBeats(const vector<i64> &vc) {
        n = 1, log = 0;
        while(n < (int)vc.size()) n <<= 1, log++;
        v.resize(2 * n);
        for(i64 i = 0; i < (int)vc.size(); ++i) { v[i + n].sum = v[i + n].g1 = v[i + n].l1 = vc[i]; }
        for(i64 i = n - 1; i; --i) update(i);
    }

    void range_chmin(int l, int r, i64 x) { inner_apply<1>(l, r, x); }
    void range_chmax(int l, int r, i64 x) { inner_apply<2>(l, r, x); }
    void range_add(int l, int r, i64 x) { inner_apply<3>(l, r, x); }
    void range_update(int l, int r, i64 x) { inner_apply<4>(l, r, x); }
    i64 range_min(int l, int r) { return inner_fold<1>(l, r); }
    i64 range_max(int l, int r) { return inner_fold<2>(l, r); }
    i64 range_sum(int l, int r) { return inner_fold<3>(l, r); }

  private:
    void update(int k) {
        Node &p = v[k];
        Node &l = v[k * 2 + 0];
        Node &r = v[k * 2 + 1];

        p.sum = l.sum + r.sum;

        if(l.g1 == r.g1) {
            p.g1 = l.g1;
            p.g2 = max(l.g2, r.g2);
            p.gc = l.gc + r.gc;
        } else {
            bool f = l.g1 > r.g1;
            p.g1 = f ? l.g1 : r.g1;
            p.gc = f ? l.gc : r.gc;
            p.g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
        }

        if(l.l1 == r.l1) {
            p.l1 = l.l1;
            p.l2 = min(l.l2, r.l2);
            p.lc = l.lc + r.lc;
        } else {
            bool f = l.l1 < r.l1;
            p.l1 = f ? l.l1 : r.l1;
            p.lc = f ? l.lc : r.lc;
            p.l2 = min(f ? r.l1 : l.l1, f ? l.l2 : r.l2);
        }
    }

    void push_add(int k, i64 x) {
        Node &p = v[k];
        p.sum += x << (log + __builtin_clz(k) - 31);
        p.g1 += x;
        p.l1 += x;
        if(p.g2 != -INF) p.g2 += x;
        if(p.l2 != INF) p.l2 += x;
        p.add += x;
    }
    void push_min(int k, i64 x) {
        Node &p = v[k];
        p.sum += (x - p.g1) * p.gc;
        if(p.l1 == p.g1) p.l1 = x;
        if(p.l2 == p.g1) p.l2 = x;
        p.g1 = x;
    }
    void push_max(int k, i64 x) {
        Node &p = v[k];
        p.sum += (x - p.l1) * p.lc;
        if(p.g1 == p.l1) p.g1 = x;
        if(p.g2 == p.l1) p.g2 = x;
        p.l1 = x;
    }
    void push(int k) {
        Node &p = v[k];
        if(p.add != 0) {
            push_add(k * 2 + 0, p.add);
            push_add(k * 2 + 1, p.add);
            p.add = 0;
        }
        if(p.g1 < v[k * 2 + 0].g1) push_min(k * 2 + 0, p.g1);
        if(p.l1 > v[k * 2 + 0].l1) push_max(k * 2 + 0, p.l1);

        if(p.g1 < v[k * 2 + 1].g1) push_min(k * 2 + 1, p.g1);
        if(p.l1 > v[k * 2 + 1].l1) push_max(k * 2 + 1, p.l1);
    }

    void subtree_chmin(int k, i64 x) {
        if(v[k].g1 <= x) return;
        if(v[k].g2 < x) {
            push_min(k, x);
            return;
        }
        push(k);
        subtree_chmin(k * 2 + 0, x);
        subtree_chmin(k * 2 + 1, x);
        update(k);
    }

    void subtree_chmax(int k, i64 x) {
        if(x <= v[k].l1) return;
        if(x < v[k].l2) {
            push_max(k, x);
            return;
        }
        push(k);
        subtree_chmax(k * 2 + 0, x);
        subtree_chmax(k * 2 + 1, x);
        update(k);
    }

    template <int cmd> inline void _apply(int k, i64 x) {
        if constexpr(cmd == 1) subtree_chmin(k, x);
        if constexpr(cmd == 2) subtree_chmax(k, x);
        if constexpr(cmd == 3) push_add(k, x);
        if constexpr(cmd == 4) subtree_chmin(k, x), subtree_chmax(k, x);
    }

    template <int cmd> void inner_apply(int l, int r, i64 x) {
        if(l == r) return;
        l += n, r += n;
        for(int i = log; i >= 1; i--) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while(l < r) {
                if(l & 1) _apply<cmd>(l++, x);
                if(r & 1) _apply<cmd>(--r, x);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for(int i = 1; i <= log; i++) {
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <int cmd> inline i64 e() {
        if constexpr(cmd == 1) return INF;
        if constexpr(cmd == 2) return -INF;
        return 0;
    }

    template <int cmd> inline void op(i64 &a, const Node &b) {
        if constexpr(cmd == 1) a = min(a, b.l1);
        if constexpr(cmd == 2) a = max(a, b.g1);
        if constexpr(cmd == 3) a += b.sum;
    }

    template <int cmd> i64 inner_fold(int l, int r) {
        if(l == r) return e<cmd>();
        l += n, r += n;
        for(int i = log; i >= 1; i--) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        i64 lx = e<cmd>(), rx = e<cmd>();
        while(l < r) {
            if(l & 1) op<cmd>(lx, v[l++]);
            if(r & 1) op<cmd>(rx, v[--r]);
            l >>= 1;
            r >>= 1;
        }
        if constexpr(cmd == 1) lx = min(lx, rx);
        if constexpr(cmd == 2) lx = max(lx, rx);
        if constexpr(cmd == 3) lx += rx;
        return lx;
    }
};

/**
 * @brief Range Chmin Chmax Add Update Range Min Max Sum Segment Tree Beats!
 * @docs docs/segment-tree/segment-tree-beats.md
 */

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

//* /Template

void solve() {
    int n, m; cin >> n >> m;
    vpi sgmts(m); each(x, sgmts) cin >> x.f >> x.s;

    dbg(n, m);
    dbg(sgmts);



    vl arr(n + 1);
    for(int i = 1; i <= n; i++) arr[i] = i + 1;
    AngelBeats stb(arr);



    LazySeg lzst;
    {
        int mx = n + 5;
        int m = 1;
        while(m < mx) m *= 2;

        vector<LazySeg::T> tmp(m, LazySeg::T(0));
        lzst.init(tmp);
    }

    each(x, sgmts) {
        //? dbg(x.f, x.s, x.s + 1);

        stb.range_chmax(x.f, x.s + 1, x.s + 1); //? [l, r - 1]
        lzst.upd(x.f, x.s, 1); //? [l, r]
    }

    //! debug
    //?for(int i = 1; i <= n; i++) if(n <= 20) {
    //?    dbg(i, stb.range_sum(i, i + 1));
    //?    dbg(i, lzst.query(i, i).sum);
    //?}

    vl dp(n + 2, -BIG);
    for(ll idx = n + 1; idx >= 1; idx--) {
        if(idx == n + 1) dp[idx] = 0;
        else {
            ckmax(dp[idx], dp[stb.range_sum(idx, idx + 1)] + lzst.query(idx, idx).sum);
            ckmax(dp[idx], dp[idx + 1]);
        }
    }

//?    function<ll(int)> solve = [&](int idx) -> long long {
//?        if(idx == n + 1) return 0;
//?
//?        ll ans = -BIG;
//?
//?        //? take
//?        ckmax(ans, solve(stb.range_sum(idx, idx + 1)) + lzst.query(idx, idx).sum);
//?
//?        //? no take
//?        ckmax(ans, solve(idx + 1));
//?
//?        return ans;
//?    };

//?    ll ans = solve(1);

    ll ans = dp[1];
    cout << ans << "\n";
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
    cin >> t;

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
