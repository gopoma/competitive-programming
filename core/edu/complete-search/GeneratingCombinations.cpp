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
// using i64 = long long; //? for Number Theory related
// using u64 = uint64_t; //? for Number Theory related
// using i128 = __int128; //? for Number Theory related
// using u128 = __uint128_t; //? for Number Theory related
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

bool isPrime(int num) {
    for(int x = 2; x * x <= num; x++)
        if(num % x == 0)
            return false;
    return (num >= 2);
}

void combinationUtil(vector<int>& arr, vector<int>& data,
                    int start, int end,
                    int index, int r);

// The main function that prints
// all combinations of size r
// in arr[] of size n. This function
// mainly uses combinationUtil()
void work(vector<int>& arr, int n, int r) {
    // A temporary array to store
    // all combination one by one
    vector<int> data(r);

    // Print all combination using
    // temporary array 'data[]'
    combinationUtil(arr, data, 0, n-1, 0, r);
}

/* arr[] ---> Input Array
data[] ---> Temporary array to
store current combination
start & end ---> Starting and
Ending indexes in arr[]
index ---> Current index in data[]
r ---> Size of a combination to be printed */
void combinationUtil(vector<int>& arr, vector<int>& data,
                    int start, int end,
                    int index, int r)
{
    // Current combination is ready
    // to be printed, print it
    if (index == r)
    {
        V<int> tmp;
        for (int j = 0; j < r; j++) {
            tmp.eb(data[j]);
            // cout << data[j] << " ";
        }
        int sum = accumulate(tmp.begin(), tmp.end(), 0);
        dbg(tmp, sum);
        chk(!isPrime(sum));
        return;
    }

    // replace index with all possible
    // elements. The condition "end-i+1 >= r-index"
    // makes sure that including one element
    // at index will make a combination with
    // remaining elements at remaining positions
    for (int i = start; i <= end &&
        end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1,
                        end, index+1, r);
    }
}

const int MAXN = int(1e6);
vector<bool> is_prime(MAXN + 1, true);
set<int> primes;
V<int> pprimes;

void solve() {
    //? Theorem: All prime numbers larger than 3
    //? can be written as 6k+1 or 6k−1 for some natural number k.

    int N;
    cin >> N;
    chk(5 <= N && N <= 55);

    V<int> arr;
    for(int i = 0, j = 0; i < N; j++) {
        str current = to_string(pprimes[j]);
        if(current.back() == '1') {
            arr.eb(pprimes[j]);
            i++;
        }
    }
    // work(arr, sz(arr), 5);
    for(auto& x: arr) cout << x << " ";
    cout << n_l;
}

void precompute() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAXN; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAXN; j += i)
                is_prime[j] = false;
        }
    }

    for(int i = 1; i <= MAXN; i++) {
        if(is_prime[i]) {
            pprimes.eb(i);
        }
    }
}

clock_t startTime;
double getCurrentTime() { return (double)(clock() - startTime) / CLOCKS_PER_SEC; }
// https://atcoder.jp/contests/abc096/tasks/abc096_d
// D - Five, Five Everywhere
signed main() {
    startTime = clock();

    // read read read
    setIO();
    //? cout << fixed << setprecision(12);

    precompute();

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
