// sometimes pragmas don't work, if so, just comment it!
// #pragma GCC optimize(3,"Ofast","inline")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>

using namespace std;



#ifdef LOCAL
    #include "helpers/debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0
    #define RAYA         0
#endif



// building blocks
using ll = long long;
using ull = unsigned long long;
using db = long double; // or double, if TL is tight
using str = string; // yay python!
// using u128 = __uint128_t; // for Number Theory related
// using i128 = __int128;
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
//! ^ lol this makes everything look weird but I'll try it

tcT> using V = vector<T>; //?
tcT, size_t SZ> using AR = array<T,SZ>;
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
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
tcT> int upb(V<T>& a, const T& b) { return int(ub(all(a),b)-bg(a)); }



// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



const int MOD = (int)1e9+7; // 998244353;
const int MX = (int)2e5+5;
const ll BIG = 1e18; // not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; // for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { // assert(x >= 0); // make C++11 compatible until USACO updates ...
	return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x))
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

tcTU> T fstTrue(T lo, T hi, U f) {
	++hi; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true
		T mid = lo+(hi-lo)/2;
		f(mid) ? hi = mid : lo = mid+1;
	}
	return lo;
}
tcTU> T lstTrue(T lo, T hi, U f) {
	--lo; assert(lo <= hi); // assuming f is decreasing
	while (lo < hi) { // find first index such that f is true
		T mid = lo+(hi-lo+1)/2;
		f(mid) ? lo = mid : hi = mid-1;
	}
	return lo;
}
tcT> void remDup(vector<T>& v) { //! sort and remove duplicates
	sort(all(v)); v.erase(unique(all(v)),end(v)); }
tcTU> void erase(T& t, const U& u) { // don't erase
	auto it = t.find(u); assert(it != end(t));
	t.erase(it); } //! element that doesn't exist from (multi)set



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



//* here goes the template!
//* /here goes the template!

const char n_l = '\n';

const int MAX = 10000 + 5; // TODO: SQRT3

long long n;
vector<int> primes;
bool composite[MAX];
vector<long long> divisors;
vector<pair<long long, int>> factors;

void init(){
	for(int i = 2; i < MAX; i++){
		if(not composite[i]) primes.emplace_back(i);
		for(int p : primes){
			if(i * p >= MAX) break;
			composite[i * p] = true;
			if(i % p == 0) break;
		}
	}
}

void backtracking(int pos, long long val){
	if(pos == factors.size()){
		divisors.emplace_back(val);
		return;
	}
	long long p = 1;
	for(int i = 0; i <= factors[pos].second; i++){
		backtracking(pos + 1, val * p);
		p *= factors[pos].first;
	}
}

bool has_square_root(long long n){
	int r = round(sqrt(n));
	return 1ll * r * r == n;
}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

ull mod_mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull mod_pow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = mod_mul(b, b, mod), e /= 2)
		if (e & 1) ans = mod_mul(ans, b, mod);
	return ans;
}

bool miller_rabin(ull n){
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for(auto a : A) {   // ^ count trailing zeroes
		ull p = mod_pow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = mod_mul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

ull pollard_rho(ull n) {
	auto f = [n](ull x) { return mod_mul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 0, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = mod_mul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}

void factorize(){
	for(int p : primes){
		if(p * p * p > n) break;
		int e = 0;
		while(n % p == 0){
			n /= p;
			e++;
		}
		if(e) factors.emplace_back(make_pair(p, e));
	}
	if(miller_rabin(n)){
		factors.emplace_back(make_pair(n, 1));
	}
	else if(has_square_root(n)){
		factors.emplace_back(make_pair((long long)round(sqrt(n)), 2));
	}
	else{
		long long d = pollard_rho(n);
		factors.emplace_back(make_pair(d, 1));
		factors.emplace_back(make_pair(n / d, 1));
	}
	backtracking(0, 1);
}

void solve() {
    cin >> n;

    factorize();
    remDup(divisors);

    for(auto& x: divisors) cout << x << n_l;
}


clock_t startTime;
double getCurrentTime() { return (double)(clock() - startTime) / CLOCKS_PER_SEC; }
//! https://atcoder.jp/contests/abc180/tasks/abc180_c
//! C - Cream puff
signed main() {
    startTime = clock();

    // read read read
    setIO();
    //? cout << fixed << setprecision(12);

    init(); // TODO: do not forget the init >:v

    long long t = 1LL;
    //? cin >> t;

    while(t--) {
        solve();
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[32m++++++++++++++++++++\n";
        cerr << "time = " << getCurrentTime() << "ms\n";
        cerr << "++++++++++++++++++++\n";
    #endif

    // should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	! do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	! DON'T GET STUCK ON ONE APPROACH
*/
