//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

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

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
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

//? __builtin_popcountll
ll GetBit(ll mask, ll bit) { return (mask >> bit) & 1LL; }
void TurnOn(ll& mask, ll bit) { mask = mask | (1LL << bit); }
void TurnOff(ll& mask, ll bit) { mask = mask & (~(1LL << bit)); }

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0);

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
const int MAX = int(1e3) + 5; // TODO: SQRT3

int n;
vector<int> primes;
bool composite[MAX];
vector<int> divisors;
vector<pair<int, int>> factors;

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

void backtracking(int pos, int val){
	if(pos == factors.size()){
		divisors.emplace_back(val);
		return;
	}
	int p = 1;
	for(int i = 0; i <= factors[pos].second; i++){
		backtracking(pos + 1, val * p);
		p *= factors[pos].first;
	}
}

bool has_square_root(int n){
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
		factors.emplace_back(make_pair((int)round(sqrt(n)), 2));
	}
	else{
		int d = pollard_rho(n);
		factors.emplace_back(make_pair(d, 1));
		factors.emplace_back(make_pair(n / d, 1));
	}
	backtracking(0, 1);
}
//* /here goes the template!

const char n_l = '\n';

// TODO: modularize >:v
vector<int> factorize(int x) {
    divisors.clear();
    factors.clear();

    n = x;

    factorize();
    remDup(divisors);

    return divisors;
}
//? /Template

/**
 * Description: Hash map with similar API as unordered\_map.
 	* Initial capacity must be a power of 2 if provided.
 * Source: KACTL
 * Memory: \tilde 1.5x unordered map
 * Time: \tilde 3x faster than unordered map
 * API: hash_map<ll, ll> go({},{},{},{}, {1 << 20});
 */

// #include<bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//? For CodeForces, or other places where hacking might be a problem:

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { // To use most bits rather than just the lowest ones:
	const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
	ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
//?__gnu_pbds::gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});

template <typename K, typename V, typename Hash = chash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = chash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

ll brute(int N, vl a) {
    hash_map<int, int> hist; for(auto& x: a) hist[x]++;
    remDup(a);
    ll ans = 0;
    for(auto& x: a) {
        {
            ll count = hist[x];
            ans += count * (count - 1LL) * (count - 2LL);
        }
        {
            for(ll b = 2; ; b++) {
                ll nxt = x * b;
                ll nxtnxt = nxt * b;
                if(nxtnxt > a.bk) break;
                if((hist.find(nxt) != hist.end()) && (hist.find(nxtnxt) != hist.end())) {
                    ans += ll(hist[x]) * ll(hist[nxt]) * ll(hist[nxtnxt]);
                }
            }
        }
    }
    return ans;
}

hash_map<int, vi> already;
int MAX_COUNT = 5000;
int current_count = 0;
ll slv(int N, vl& a) {
   hash_map<int, int> hist;
    for(auto& x: a) hist[x]++;
    remDup(a);
    ll ans = 0;
    for(auto& x: a) {
        {
            ll count = hist[x];
            ans += count * (count - 1LL) * (count - 2LL);
        }
        vi divs;
        if(already.find(x) != already.end()) {
            divs = already[x];
        } else {
            if(current_count < MAX_COUNT) {
                divs = factorize(x);
                already[x] = divs;
                current_count++;
            } else {
                divs = factorize(x);
            }
        }
        for(auto& d: divs) { if(d == 1) continue;
            ll prev = x / d;
            ll nxt = x * d;
            if(nxt > a.bk) break; 
            if(hist.find(prev) != hist.end() && hist.find(nxt) != hist.end()) {
                ans += ll(hist[prev]) * ll(hist[x]) * ll(hist[nxt]);
            }
        }        
    }
    return ans;
}

void solve() {
    //? <>
    int N; cin >> N;
    vl a(N); for(auto& x: a) cin >> x;
    ll ans = slv(N, a);
    dbg(ans);
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    init(); // TODO: do not forget the init >:v

    //? Stress Testing
    while(0) {
        RAYA;
        int N = rng_int(1, 100);
        vl a(N); for(auto& x: a) x = rng_ll(1, 1000000000);
        dbg(N);
        dbg(a);
        ll ans = brute(N, a);
        ll greedy = slv(N, a);
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    int t = 1; cin >> t;
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
