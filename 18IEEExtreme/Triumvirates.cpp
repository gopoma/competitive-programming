#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

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



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



//? Template
const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



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

/**
 * Description: Generate various types of trees.
 * Source: Own + Dhruv Rohatgi
 */

////////////// DISTRIBUTIONS

// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// return double in [L,R] inclusive
db rng_db(db L, db R) { assert(L <= R);
	return uniform_real_distribution<db>(L,R)(rng); }

// http://cplusplus.com/reference/random/geometric_distribution/geometric_distribution/
// flip a coin which is heads with probability p until you flip heads
// mean value of c is 1/p-1
int rng_geo(db p) { assert(0 < p && p <= 1); // p large -> closer to 0
	return geometric_distribution<int>(p)(rng); }

////////////// VECTORS + PERMS

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate random permutation of [0,N-1]
vi randPerm(int N) { vi v(N); iota(all(v),0); shuf(v); return v; }

// random permutation of [0,N-1] with first element 0
vi randPermZero(int N) { vi v(N-1); iota(all(v),1);
	shuf(v); v.ins(bg(v),0); return v; }

// shuffle permutation of [0,N-1]
vi shufPerm(vi v) {
	int N = sz(v); vi key = randPerm(N);
	vi res(N); F0R(i,N) res[key[i]] = key[v[i]];
	return res;
}

// vector with all entries in [L,R]
vi rng_vec(int N, int L, int R) {
	vi res; F0R(_,N) res.pb(rng_int(L,R));
	return res;
}

// vector with all entries in [L,R], unique
vi rng_vec_unique(int N, int L, int R) {
	set<int> so_far; vi res;
	F0R(_,N) {
		int x; do { x = rng_int(L,R); } while (so_far.count(x));
		so_far.ins(x); res.pb(x);
	}
	return res;
}

////////////// GRAPHS

// relabel edges ed according to perm, shuffle
vpi relabelAndShuffle(vpi ed, vi perm) {
	each(t,ed) {
		t.f = perm[t.f], t.s = perm[t.s];
		if (rng()&1) swap(t.f,t.s);
	}
	shuf(ed); return ed;
}

// shuffle graph with vertices [0,N-1]
vpi shufGraph(int N, vpi ed) { // randomly swap endpoints, rearrange labels
	return relabelAndShuffle(ed,randPerm(N)); }
vpi shufGraphZero(int N, vpi ed) {
	return relabelAndShuffle(ed,randPermZero(N)); }

// shuffle tree given N-1 edges
vpi shufTree(vpi ed) { return shufGraph(sz(ed)+1,ed); }
// randomly swap endpoints, rearrange labels
vpi shufRootedTree(vpi ed) {
	return relabelAndShuffle(ed,randPermZero(sz(ed)+1)); }

void pgraphOne(int N, vpi ed) {
	//? ps(N,sz(ed));
	//? each(e,ed) ps(1+e.f,1+e.s);
}

////////////// GENERATING TREES

// for generating tall tree
pi geoEdge(int i, db p) { assert(i > 0);
	return {i,max(0,i-1-rng_geo(p))}; }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
	assert(N >= 1 && back >= 0); vpi ed;
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed; }

// generate path
vpi path(int N) { return treeRand(N,0); }

// generate tall tree (large diameter)
// the higher the p the taller the tree
vpi treeTall(int N, db p) { assert(N >= 1);
	vpi ed; FOR(i,1,N) ed.pb(geoEdge(i,p));
	return ed; }

// generate tall tree, then add rand at end
vpi treeTallShort(int N, db p) {
	assert(N >= 1); int mid = (N+1)/2;
	vpi ed = treeTall(mid,p);
	FOR(i,mid,N) ed.eb(i,rng_int(0,i-1));
	return ed; }

// lots of stuff connected to either heavy1 or heavy2
vpi treeTallHeavy(int N, db p) {
	assert(N >= 1); // + bunch of rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.pb(geoEdge(i,p));
	}
	return ed;
}

// heavy tall tree + random
// lots of verts connected to heavy1 or heavy2
vpi treeTallHeavyShort(int N, db p) {
	assert(N >= 1); // + almost-path + rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i <= heavy2) ed.pb(geoEdge(i,p)); // tall -> heavy1
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.eb(i,rng_int(0,i-1));
	}
	return ed;
}

int rand_prime(int l, int r) {
	while(1) {
		int x = rng_int(l,r);
		bool bad = 0;
		for (int i = 2; i*i <= x; ++i) if (x%i == 0) bad = 1;
		if (!bad) return x;
	}
}

/**
 * Description: Operations with fractions
 * Source: https://martin-thoma.com/fractions-in-cpp/
 * Verification: TopCoder MinimizeAbsoluteDifferenceDiv1
 */

struct frac {
	ll n,d;
	frac(ll _n, ll _d) {
		n = _n, d = _d;
		ll g = gcd(n,d); n /= g, d /= g;
		if (d < 0) n *= -1, d *= -1;
	}
	frac(ll _n) : frac(_n,1) {}
	frac() : frac(0) {}
	friend frac abs(frac F) { return frac(abs(F.n),F.d); }
	friend str ts(const frac& a) { return ts(a.n)+"/"+ts(a.d); }

	friend bool operator<(const frac& l, const frac& r) { return l.n*r.d < r.n*l.d; }
	friend bool operator==(const frac& l, const frac& r) { return l.n == r.n && l.d == r.d; }
	friend bool operator!=(const frac& l, const frac& r) { return !(l == r); }

	frac operator-() const { return frac(-n,d); }
	friend frac operator+(const frac& l, const frac& r) { return frac(l.n*r.d+r.n*l.d,l.d*r.d); }
	friend frac operator-(const frac& l, const frac& r) { return frac(l.n*r.d-r.n*l.d,l.d*r.d); }
	friend frac operator*(const frac& l, const frac& r) { return frac(l.n*r.n,l.d*r.d); }
	friend frac operator*(const frac& l, int r) { return l*frac(r,1); }
	friend frac operator*(int r, const frac& l) { return l*r; }
	friend frac operator/(const frac& l, const frac& r) { return l*frac(r.d,r.n); }
	friend frac operator/(const frac& l, const int& r) { return l/frac(r,1); }
	friend frac operator/(const int& l, const frac& r) { return frac(l,1)/r; }

	friend frac& operator+=(frac& l, const frac& r) { return l = l+r; }
	friend frac& operator-=(frac& l, const frac& r) { return l = l-r; }
	template<class T> friend frac& operator*=(frac& l, const T& r) { return l = l*r; }
	template<class T> friend frac& operator/=(frac& l, const T& r) { return l = l/r; }
};
//? /Template

void solve() {
    ll N; cin >> N;
    vpl points(N); each(x, points) { cin >> x.f >> x.s; }
    V<frac> tans(N);
    ll xr = -ll(1e10);
    ll yr = -ll(1e10);
    for(int i = 0; i < N; i++) {
        auto [xx, yy] = points[i];
        tans[i] = frac(yy - yr, xx - xr);
    }
    vl ords(N); iota(all(ords), 0);
    sort(all(ords), [&](int i, int j) {
        return (tans[i] < tans[j]);
    });
    for(int i = 0; i < N; i += 3) {
        int xx = ords[i];
        int yy = ords[i + 1];
        int zz = ords[i + 2];
        cout << xx << " " << yy << " " << zz << "\n";
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int t = 1; //! cin >> t;
    for(int i = 0; i < t; i++) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
