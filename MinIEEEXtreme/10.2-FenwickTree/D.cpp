// sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>

using namespace std;



// building blocks
using ll = long long;
using db = long double; // or double, if TL is tight
using str = string; // yay python!
// using u128 = __uint128_t; // for Number Theory related
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>; // minima



// pairs
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;

#define mp make_pair
#define f first
#define s second



#define tcT template<class T
#define tcTU tcT, class U
// ^ lol this makes everything look weird but I'll try it

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



// using u128 = __uint128_t;
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;



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

#define lb lower_bound
#define ub upper_bound
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }

// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { // assert(x >= 0); // make C++11 compatible until USACO updates ...
	return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x))
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down



#define tcTUU tcT, class ...U

inline namespace FileIO {
	void setIn(str s)  { freopen(s.c_str(),"r",stdin); }
	void setOut(str s) { freopen(s.c_str(),"w",stdout); }
	void setIO(str s = "") {
		cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
		// cin.exceptions(cin.failbit);
		// throws exception when do smth illegal
		// ex. try to read letter into int
		if (sz(s)) setIn(s+".in"), setOut(s+".out"); // for old USACO
	}
}



// for debugging!
#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < int(v.size()); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

template <typename T>
ostream& operator <<(ostream &os, const set<T>& v) {
    vector<T> tmp;
    for(auto& e: v) {
        tmp.emplace_back(e);
    }

    return os << tmp;
}

template <typename T>
ostream& operator <<(ostream &os, const pair<T, T>& v) {
    return os << "{" << v.first << ", " << v.second << "}";
}



mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

// Direction vectors
ll dRow[] = { -1LL, 0LL, 1LL,  0LL };
ll dCol[] = {  0LL, 1LL, 0LL, -1LL };

const int MOD = (int)1e9+7; // 998244353;
const int MX = (int)1e6 + 5;
const ll BIG = 1e18; // not too close to LLONG_MAX
const db PI = acos((db)-1);
const char n_l = '\n';



// here goes the template!

/**
 * Description: point update and rectangle sum with offline 2D BIT.
	* For each of the points to be updated, $x\in (0,SZ)$ and $y\neq 0$.
 * Time: O(N\log^2 N)
 * Memory: O(N\log N)
 * Source: Own
 * Verification:
 	* https://dmoj.ca/problem/occ19g4
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=722 (753 ms)
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=601 (679 ms)
 */

template<class T, int SZ> struct OffBIT2D {
	bool mode = 0; // mode = 1 -> initialized
	vpi todo; // locations of updates to process
	int cnt[SZ], st[SZ];
	vi val; vector<T> bit; // store all BITs in single vector
	void init() {
        // assert(!mode);
        mode = 1;

		int lst[SZ]; F0R(i,SZ) lst[i] = cnt[i] = 0;
		sort(all(todo),[](const pi& a, const pi& b) {
			return a.s < b.s; });
		each(t,todo) for (int x = t.f; x < SZ; x += x&-x)
			if (lst[x] != t.s) lst[x] = t.s, cnt[x] ++;
		int sum = 0; F0R(i,SZ) lst[i] = 0, st[i] = (sum += cnt[i]);
		val.rsz(sum); bit.rsz(sum); reverse(all(todo));
		each(t,todo) for (int x = t.f; x < SZ; x += x&-x)
			if (lst[x] != t.s) lst[x] = t.s, val[--st[x]] = t.s;
	}
	int rank(int y, int l, int r) {
		return ub(begin(val)+l,begin(val)+r,y)-begin(val)-l; }
	void UPD(int x, int y, T t) {
		for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y)
			bit[st[x]+y-1] += t; }
	void upd(int x, int y, T t) {
		if (!mode) todo.pb({x,y});
		else for (;x<SZ;x+=x&-x) UPD(x,y,t); }

	// int QUERY(int x, int y) { T res = 0;
    long long QUERY(int x, int y) { T res = 0;
		for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y) res += bit[st[x]+y-1];
		return res; }

	T query(int x, int y) {
        // assert(mode);
		T res = 0; for (;x;x-=x&-x) res += QUERY(x,y);
		return res; }
	T query(int xl, int xr, int yl, int yr) {
		return query(xr,yr)-query(xl-1,yr)
			-query(xr,yl-1)+query(xl-1,yl-1); }
};

// /here goes the template!

// here goes the work!

struct Point {
    int x, y;
    ll w;

    Point() {};
    Point(int _x, int _y, ll _w): x(_x), y(_y), w(_w) {}
};

struct Query {
    int x1, x2, y1, y2;

    Query() {};
    Query(int _x1, int _x2, int _y1, int _y2): x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}
};

OffBIT2D<ll, MX> tree;

void solve() {
    int n, q;
    cin >> n >> q;

    set<int> values;

    V<Point> points(n);
    for(auto& e: points) {
        int x, y; ll w;
        cin >> x >> y >> w;

        values.ins(x);
        values.ins(y);

        e = Point(x, y, w);
    }

    V<int> qq;
    V<Point> updates;
    V<Query> queries;
    for(int i = 0; i < q; i++) {
        int type;
        cin >> type;

        qq.emplace_back(type);

        if(type == 0) {
            int x, y; ll w;
            cin >> x >> y >> w;

            values.ins(x);
            values.ins(y);

            updates.emplace_back(Point(x, y, w));
        } else if(type == 1) {
            int l, d, r, u;
            cin >> l >> d >> r >> u;

            r--;
            u--;

            values.ins(l);
            values.ins(d);
            values.ins(r);
            values.ins(u);

            queries.emplace_back(Query(l, r, d, u));
        } else {
            // assert(false);
        }
    }

    // RAYA;
    // DBG("points:");
    // for(auto& e: points) {
    //     DBG3(e.x, e.y, e.w);
    // }
    // RAYA;

    // DBG("updates:");
    // for(auto& e: updates) {
    //     DBG3(e.x, e.y, e.w);
    // }
    // RAYA;

    // DBG("queries:");
    // for(auto& e: queries) {
    //     DBG4(e.x1, e.x2, e.y1, e.y2);
    // }
    // RAYA;



    // Coordinate Compression
    map<int, int> forwards; // get compressend value
    map<int, int> backwards; // get original value

    int count = 1;
    // DBG(values);
    for(auto& e: values) {
        forwards[e] = count;
        backwards[count] = e;
        count++;
    }

    // RAYA;
    // DBG("forwards:");
    // for(auto& it: forwards) {
    //     DBG2(it.first, it.second);
    // }
    // RAYA;

    // RAYA;
    // DBG("backwards:");
    // for(auto& it: backwards) {
    //     DBG2(it.first, it.second);
    // }
    // RAYA;

    for(auto& e: points) {
        e = Point(forwards[e.x], forwards[e.y], e.w);
    }

    for(auto& e: updates) {
        e = Point(forwards[e.x], forwards[e.y], e.w);
    }

    for(auto& e: queries) {
        e = Query(forwards[e.x1], forwards[e.x2], forwards[e.y1], forwards[e.y2]);
    }

    for(auto& e: points) {
        tree.upd(e.x, e.y, e.w);
    }

    for(auto& e: updates) {
        tree.upd(e.x, e.y, e.w);
    }

    tree.init();

    for(auto& e: points) {
        tree.upd(e.x, e.y, e.w);
    }

    // RAYA;
    // DBG("vals");
    // for(auto& e: points) {
    //     DBG4(e.x, e.y, e.w, tree.query(e.x, e.x, e.y, e.y));
    // }
    // RAYA;

    int idxu = 0;
    int idxq = 0;
    for(auto& e: qq) {
        if(e == 0) {
            tree.upd(updates[idxu].x, updates[idxu].y, updates[idxu].w);

            idxu++;
        } else if(e == 1) {
            // DBG4(queries[idxq].x1, queries[idxq].x2, queries[idxq].y1, queries[idxq].y2);
            // assert(1 <= queries[idxq].x1 && queries[idxq].x1 <= queries[idxq].x2);
            // assert(1 <= queries[idxq].y1 && queries[idxq].y1 <= queries[idxq].y2);
            ll ans = tree.query(queries[idxq].x1, queries[idxq].x2, queries[idxq].y1, queries[idxq].y2);
            // assert(ans >= 0LL);

            cout << ans << n_l;

            idxq++;
        } else {
            // assert(false);
        }
    }
}

signed main() {
    // read read read
	setIO();

    long long t = 1LL;
    // cin >> t;

    while(t--) {
        solve();
    }

    // should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
