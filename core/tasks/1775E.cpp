//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;



//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return string(1, c);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A>
string to_string(A v);

string to_string(vector<bool> v) {
    bool first = true;
    string res = "[";
    for (auto x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += x ? "true" : "false";
    }
    res += "]";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}


template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "[";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "]";
    return res;
}



void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}



#ifdef LOCAL
const vector<string> __C_DBG{
    "\033[1;34m",
    "\033[0;32m = \033[35m",
    "\033[0m",
    "]\033[35m:",
    "\033[101m",
    "\033[0m"
};

#define MACRO(code) do {code} while (false)

#define dbg(x)      MACRO(  \
    auto xd = x;    \
    cerr << "Line(" << __LINE__ << "): " << __C_DBG[0] << #x << __C_DBG[1] << to_string(xd) << __C_DBG[2] << endl;  \
)



#define dbg(...)    MACRO(  \
    cerr << "Line(" << __LINE__ << "): " << __C_DBG[0] << "[" << #__VA_ARGS__ << __C_DBG[3];    \
    debug_out(__VA_ARGS__);     \
    cerr << __C_DBG[2];     \
)

#define GA          dbg(0)
// RAYA tiene 32 caracteres "="
#define RAYA        cerr << __C_DBG[4] << "================================" << __C_DBG[5] << endl;

const bool isDebugging = true;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA

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
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
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

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;
//? /Custom Helpers



//* Template
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
    T ID{}; T cmb(T a, T b) { return min(a, b); }
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
// /here goes the template!
//* /Template

ll custom_abs(ll x) {
    if(x < 0) return -x;
    return +x;
}

ll brute(ll n, vl a) {
    auto norm = [&]() -> void {
        vl b;
        for(auto& x: a) if(x != 0) b.eb(x);
        swap(a, b);

        if(a.empty()) return;


        vector<pair<char, ll>> stk;
        for(auto& x: a) {
            if(x < 0) {
                stk.eb('-', custom_abs(x));
            } else {
                assert(x > 0);
                stk.eb('+', custom_abs(x));
            }
        }



        char current_sgn = stk[0].first;
        ll current_sum = stk[0].second;
        vector<pair<char, ll>> nstk;
        for(int i = 1; i < sz(stk); i++) {
            auto& [sgn, x] = stk[i];

            if(sgn == current_sgn) {
                current_sum += x;
            } else {
                nstk.emplace_back(current_sgn, current_sum);
                current_sum = x;
            }
            current_sgn = sgn;
        }
        nstk.emplace_back(current_sgn, current_sum);


        for(int i = 0; i + 1 < sz(nstk); i++) {
            assert(nstk[i].first != nstk[i + 1].first);
        }

        vl na;
        for(auto& [sgn, x]: nstk) {
            if(sgn == '-') na.eb(-x);
            else na.eb(+x);
        }

        swap(a, na);
    };

    ll ans = 0;
    while(true) {
        norm();
        if(a.empty()) break;
        // dbg(a);

        ll mn = BIG;
        for(auto& x: a) ckmin(mn, custom_abs(x));
        ans += mn;

        for(auto& x: a) {
            if(x < 0) {
                x += mn;
            } else {
                x -= mn;
            }
        }
    }
    return ans;
}

void slv(ll n, vl a) {
    {
        vl na;
        for(auto& x: a) {
            if(x != 0) {
                na.eb(x);
            }
        }
        swap(a, na);
    }


    ll re = 0;
    dbg(a);
    if(!a.empty()) {
        vector<pair<char, ll>> stk;
        {
            for(auto& x: a) {
                if(x < 0) {
                    stk.eb('-', custom_abs(x));
                } else {
                    assert(x > 0);
                    stk.eb('+', custom_abs(x));
                }
            }



            char current_sgn = stk[0].first;
            ll current_sum = stk[0].second;
            vector<pair<char, ll>> nstk;
            for(int i = 1; i < sz(stk); i++) {
                auto& [sgn, x] = stk[i];

                if(sgn == current_sgn) {
                    current_sum += x;
                } else {
                    nstk.emplace_back(current_sgn, current_sum);
                    current_sum = x;
                }
                current_sgn = sgn;
            }
            nstk.emplace_back(current_sgn, current_sum);


            for(int i = 0; i + 1 < sz(nstk); i++) {
                assert(nstk[i].first != nstk[i + 1].first);
            }
            swap(stk, nstk);
        }
        dbg(stk);
        const int m = sz(stk);
        dbg(m);




        SegTree<pl> st; st.init(m);
        st.ID = {BIG, BIG};
        list<ll> L;
        set<int> alive;
        vector<list<ll>::iterator> iters(n);

        vector<char> sgns(m);
        vl sum(m);

        for(int i = 0; i < m; i++) {
            L.eb(i);
            alive.emplace(i);
            auto lst = L.end(); --lst;
            iters[i] = lst;


            auto [sgn, x] = stk[i];
            sgns[i] = sgn;
            sum[i]  = x;

            st.upd(i, {x, i});
        }
        dbg(L);
        dbg(sgns);
        dbg(sum);
        auto ddd = [&]() -> void {
            if(isDebugging) {
                vl segment_tree;
                for(int i = 0; i < m; i++) {
                    segment_tree.eb(st.query(i, i).first);
                }
                dbg(segment_tree);
            }
        };
        ddd();

        dbg("Processing");
        while(true) {
            RAYA;
            auto [gmn, _] = st.query(0, m - 1);
            if(gmn == BIG) break;

            re = gmn;

            dbg(gmn);
            dbg(alive);
            dbg(sgns);
            dbg(sum);
            ddd();

            vl todo;
            while(true) {
                auto [mn, i] = st.query(0, m - 1);
                if(mn != gmn) break;
                st.upd(i, {BIG, BIG});
                todo.eb(i);
            }
            dbg(todo);


            vl ntodo;
            for(auto& i: todo) {
                alive.erase(i);
                auto it = iters[i];

                if(it != L.begin()) {
                    auto prv = prev(it);
                    ntodo.eb(*prv);
                }
                L.erase(iters[i]);
            }
            swap(todo, ntodo);
            dbg("Should Normalize", todo);


            for(auto& i: todo) {
                if(!alive.count(i)) continue;

                auto it = iters[i];
                it++;
                ll ntot = sum[i];

                char current_sgn = sgns[i];
                while(it != L.end() && (sgns[*it] == current_sgn)) {
                    ntot += sum[*it] - gmn;
                    st.upd(*it, {BIG, BIG});
                    alive.erase(*it);

                    ll guarda_id_to_remove = *it;
                    it++;
                    L.erase(iters[guarda_id_to_remove]);
                }

                sum[i] = ntot;
                st.upd(i, {ntot, i});
            }
        }
        ddd();

//        for(int i = 0; i < m; i++) {
//            dbg(i, *iters[i], iters[i] == L.begin(), iters[i] == L.end());
//            auto nxt = next(iters[i]);
//            if(nxt != L.end()) {
//                dbg(i, *nxt);
//            }
//            if(iters[i] != L.begin()) {
//                auto prv = prev(iters[i]);
//                dbg(i, *prv);
//            }
//        }
    }

    cout << re << "\n";


    if(isDebugging) {
        dbg("Brute");
        ll ans = brute(n, a);
        dbg("/Brute");

        dbg(re, ans);
        assert(re == ans);
    }
}

void solve() {
    // run A < A3.in
    // xd A < A4.in

    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    dbg(n);
    dbg(a);

    slv(n, a);
}



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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(isDebugging && 1) {
        ll n = rng_ll(1, 100);
        vl a(n); for(auto& x: a) x = rng_ll(-1e9, 1e9);
        dbg(n);
        slv(n, a);
    }

    if(isDebugging) {
        setIn("xd.in");
    }


    int t = 1;
    cin >> t;
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
    #endif
}
