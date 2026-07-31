//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
#pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

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

ll custom_abs(ll x) {
    if(x < 0) return -x;
    return +x;
}
//? /Custom Helpers



//* Template
/**
 * Description: Disjoint Set Union with path compression
 	* and union by size. Add edges and test connectivity.
 	* Use for Kruskal's or Boruvka's minimum spanning tree.
 * Time: O(\alpha(N))
 * Source: CSAcademy, KACTL
 * Verification: *
 */

struct DSU {
	vi e; void init(int N) { e = vi(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
        //* Small-To-Large Merging
        //* x has bigger set count
		e[x] += e[y]; e[y] = x; return 1;
	}
};

/**tcT> T kruskal(int N, vector<pair<T,pi>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N); // edges that unite are in MST
	each(a,ed) if (D.unite(a.s.f,a.s.s)) ans += a.f;
	return ans;
}*/

/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */

tcT> struct BIT {
	int N; V<T> data;
	void init(int _N) { N = _N; data.rsz(N); }
	void add(int p, T x) { for (++p;p<=N;p+=p&-p) data[p-1] += x; }
	T sum(int l, int r) { return sum(r+1)-sum(l); }
	T sum(int r) { T s = 0; for(;r;r-=r&-r)s+=data[r-1]; return s; }
	int lower_bound(T sum) {
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1<<25; pw; pw >>= 1) {
			int npos = pos+pw;
			if (npos <= N && data[npos-1] < sum)
				pos = npos, sum -= data[pos-1];
		}
		return pos;
	}
};

//* /Template

using Query = tuple<ll, ll, ll>;
void slv(ll n, ll m, ll q, vl positions, vl values, V<Query> que) {



    vb hasHarbour(n + 5);
    set<ll> harbours;
    vl harbourValues(n + 5);
    for(int i = 0; i < m; i++) {
        harbourValues[positions[i]] = values[i];
        hasHarbour[positions[i]] = true;
        harbours.emplace(positions[i]);
    }
    // dbg(hasHarbour);
    // dbg(harbours);
    // dbg(harbourValues);





    DSU dsu; dsu.init(n + 5);
    for(int i = 1; i + 1 <= n; i++) {
        if(!hasHarbour[i] && !hasHarbour[i + 1]) {
            dsu.unite(i, i + 1);
        }
    }

    map<int, vi> G;
    set<ll> starts;
    for(int i = 1; i <= n; i++) {
        if(!hasHarbour[i]) {
            G[dsu.get(i)].eb(i);
        } else {
            const int L = i;
            const int R = i;

            starts.emplace(L);
        }
    }
    starts.emplace(n + 1);






    auto check = [&](int i) -> bool {
        return (1 <= i && i <= n);
    };

    BIT<ll> st; st.init(n + 5);
    auto debug_bit = [&]() -> void {
        if(isDebugging) {
            vl bit;
            for(int i = 0; i <= n; i++) {
                bit.eb(st.sum(i, i));
            }
            dbg(bit);
        }
    };



    for(auto& [_, vec]: G) {
        const int L = vec.ft;
        const int R = vec.bk;

        auto it = harbours.upper_bound(L);
        it--;

        auto prvHarbour = *it;
        assert(check(prvHarbour));
        assert(prvHarbour < L);

        dbg(L, R, prvHarbour);


        ll len = R - L + 1;
        ll conr = (len * (len + 1)) / 2LL;

        st.add(L, harbourValues[prvHarbour] * conr);
        starts.emplace(L);
    }
    // dbg(harbours);
    // dbg(starts);
    // debug_bit();







    dbg("Start Processing");
    dbg("Start Processing");

    auto S = [&](ll l, ll r) -> ll {
        ll re = (r * (r + 1LL)) / 2LL;
        re -= ((l - 1LL) * (l)) / 2LL;
        return re;
    };

    auto inter = [&](ll L1, ll R1, ll L2, ll R2) -> pl {
        if(L1 > L2) {
            swap(L1, L2);
            swap(R1, R2);
        }

        return {max(L1, L2), min(R1, R2)};
    };

    auto work_brute = [&](ll bl, ll br, ll l, ll r) -> ll {
        auto [sl, sr] = inter(bl, br, l, r);
        // dbg("work_brute", bl, br, l, r, sl, sr);
        assert(bl <= br);
        assert(sl <= sr);
        assert(bl <= sl && sr <= br);

        if(hasHarbour[bl]) {
            assert(bl == br);
            return 0;
        }

        ll prvHarbour = bl - 1;
        assert(hasHarbour[prvHarbour]);

        ll right = br - sr + 1;
        ll cnt = sr - sl + 1;

        return harbourValues[prvHarbour] * S(right, right + cnt - 1LL);
    };

    vl response;
    for(auto& [type, a, b]: que) {
        // RAYA;
        if(type == 1) {
            const ll x = a;
            const ll v = b;

            // dbg(type, x, v);
            assert(!harbours.count(x));




            auto it = starts.upper_bound(x);
            it--;

            const ll L = *it; it++;
            const ll R = (*it) - 1;

            // dbg(L, R);
            assert(starts.count(L));
            assert(hasHarbour[L - 1]);
            assert(hasHarbour[R + 1]);
            st.add(L, -st.sum(L, L));




            starts.emplace(x);
            harbours.emplace(x);
            harbourValues[x] = v;
            hasHarbour[x] = true;

            if(x != L) {
                const ll l = L;
                const ll r = x - 1;
                assert(l <= r);
                // dbg("x != L", l, r, harbourValues[l - 1]);

                ll cnt = r - l + 1;
                assert(hasHarbour[l - 1]);
                st.add(l, harbourValues[l - 1] * ((cnt * (cnt + 1LL)) / 2LL));
                starts.emplace(l);
            }
            if(x != R) {
                const ll l = x + 1;
                const ll r = R;
                assert(l <= r);
                // dbg("x != R", l, r, harbourValues[l - 1]);

                ll cnt = r - l + 1;
                assert(hasHarbour[l - 1]);
                st.add(l, harbourValues[l - 1] * ((cnt * (cnt + 1LL)) / 2LL));
                starts.emplace(l);
            }
        } else {
            assert(type == 2);

            const ll l = a;
            const ll r = b;
            // dbg(type, l, r);





            ll lre = 0;



            ll middleL = -67;
            ll leftL   = -67;
            ll leftR   = -67;
            {
                auto it = starts.upper_bound(l);
                it--;

                leftL = *it; it++;
                leftR = (*it) - 1;
                // dbg("left", leftL, leftR);

                middleL = leftR + 1;

                lre += work_brute(leftL, leftR, l, r);
                // dbg("add left");
            }

            ll middleR = -67;
            ll rightL  = -67;
            ll rightR  = -67;
            {
                auto it = starts.upper_bound(r);
                it--;

                rightL = *it; it++;
                rightR = (*it) - 1;
                // dbg("right", rightL, rightR);

                middleR = rightL - 1;

                if(mp(leftL, leftR) != mp(rightL, rightR)) {
                    // dbg("add right");
                    lre += work_brute(rightL, rightR, l, r);
                }
            }
            // dbg(middleL, middleR);




            if(
                (l <= middleL && middleL <= r)
                && (l <= middleR && middleR <= r)
                && (middleL <= middleR)
            ) {
                lre += st.sum(middleL, middleR);
            }

            response.eb(lre);
        }
    }

    for(auto& x: response) cout << x << "\n";
}

void solve() {
    // run A < A3.in
    // xd A < A4.in

    ll n, m, q; cin >> n >> m >> q;
    vl positions(m); for(auto& x: positions) cin >> x;
    vl values(m);    for(auto& x: values) cin >> x;
    V<Query> que(q);
    for(auto& [type, x, y]: que) {
        cin >> type >> x >> y;
    }

    dbg(n, m, q);
    dbg(positions);
    dbg(values);
    for(auto& [type, x, y]: que) {
        dbg(type, x, y);
    }

    slv(n, m, q, positions, values, que);
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
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        ll n = rng_ll(3e4, 3e4);



        set<ll> pos;
        pos.emplace(1);
        pos.emplace(n);
        {
            ll t = rng_ll(1, 1);
            rep(t) {
                pos.emplace(rng_ll(1, n));
            }
        }


        ll m = sz(pos);
        vl positions;
        vl values;

        set<ll> free; for(ll x = 1; x <= n; x++) free.emplace(x);
        for(auto& x: pos) {
            positions.emplace_back(x);
            values.emplace_back(rng_ll(1e7, 1e7));

            free.erase(x);
        }



        ll q = rng_ll(1, 1e3);
        V<Query> que;
        rep(q) {
            ll type = rng_ll(1, 2);
            if(type == 1) {
                if(!free.empty()) {
                    vl free_arr; for(auto& x: free) free_arr.eb(x);

                    ll x = free_arr[rng_ll(0, sz(free_arr) - 1)];
                    ll v = rng_ll(1e7, 1e7);
                    free.erase(x);
                    que.eb(1LL, x, v);
                }
            } else {
                ll l = rng_ll(1, n);
                ll r = rng_ll(l, n);
                que.eb(2LL, l, r);
            }
        }
        q = sz(que);

        dbg(n, m, q);
        // dbg(positions);
        // dbg(values);
        for(auto& [type, x, y]: que) {
            // dbg(type, x, y);
        }

        slv(n, m, q, positions, values, que);
    }

    if(isDebugging) {
        setIn("xd.in");
    }

    int t = 1;
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
