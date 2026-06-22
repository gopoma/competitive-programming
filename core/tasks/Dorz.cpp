//? template: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/contest/TemplateLong.cpp
// sometimes pragmas don't work, if so, just comment it!
// #pragma GCC optimize ("Ofast")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
    #include "helpers/debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define DBG(x)        0
    #define DBGY(x)       0
    #define DBG2(x,y)     0
    #define DBG3(x,y,z)   0
    #define DBG4(x,y,z,w) 0
    #define RAYA          0
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
const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

namespace Solution1 {

str solve(str s) {
    int n = sz(s);

    auto isVowel = [](char c) {
        return c == 'a' || c == 'e';
    };

    std::vector<std::string> t;
    for (int i = n - 1; i >= 0; ) {
        if (isVowel(s[i])) {
            t.push_back(s.substr(i - 1, 2));
            i -= 2;
        } else {
            t.push_back(s.substr(i - 2, 3));
            i -= 3;
        }
    }
    std::reverse(t.begin(), t.end());

    str ans = "";
    for (int i = 0; i < t.size(); i++) {
        for(auto& x: t[i]) ans.pb(x);
        ans.pb(".\n"[i == t.size() - 1]);
    }

    return ans;
}

}  // namespace Solution1

namespace Solution2 {

str solve(str s) {
    int n = sz(s);

    vector<string> a;
    string temp = "";
    for(int i = n - 1; i >= 0; i--){
        temp += s[i];
        if(s[i] == 'a' || s[i] == 'e'){
            temp += s[i - 1];
            i--;
            a.emplace_back(temp);
            temp = "";
        }
    }
    reverse(a.begin(), a.end());
    for(auto &x : a) reverse(x.begin(), x.end());

    str ans = "";
    for(auto& x: a[0]) ans.pb(x);
    for(int i = 1; i < a.size(); i++) {
        ans.pb('.');
        for(auto& x: a[i]) ans.pb(x);
    }
    ans.pb('\n');

    return ans;
}

}

namespace Solution3 {

str solve(str s) {
    set<char> ss;
	ss.insert('a');
	ss.insert('e');
	ss.insert('i');
	ss.insert('o');
	ss.insert('u');

    int n = sz(s);
	s += "ss";

    str ans = "";

    #define forn(i,n) for(int i = 0; i < (int)n; i++)
	forn(i, n) {
		if(i + 3 < n + 1 && ss.find(s[i + 3]) == ss.end()) {
			//debug(s[i + 3]);
            ans.pb(s[i]);
            ans.pb(s[i + 1]);
            ans.pb(s[i + 2]);
			i += 2;
		} else {
            ans.pb(s[i]);
            ans.pb(s[i + 1]);
			i++;
		}

        if (i != n - 1) ans.pb('.');
	}

    ans.pb('\n');
    return ans;
}

}

namespace Solution4 {

str solve(str S) {
    auto vowel = [](char c) {
        return (c == 'a' || c == 'e');
    };

    const int n = sz(S);
    str ans = "";
    for(int i = 0; i < n; i++) {
        if((i != n - 1) && !vowel(S[i]) && vowel(S[i + 1])) {
            if(i != 0) ans.pb('.');
        }
        ans.pb(S[i]);
    }
    ans.pb('\n');

    return ans;
}

}

//* here goes the template!
int rng_int(int L, int R) {
    assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);
}

ll rng_ll(ll L, ll R) {
    assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);
}
//* /here goes the template!


clock_t startTime;
double getCurrentTime() { return (double)(clock() - startTime) / CLOCKS_PER_SEC; }
signed main() {
    startTime = clock();

    // read read read
    setIO();
    //? cout << fixed << setprecision(12);

    while(true) {
        const int n = rng_int(4, 400);
        str S = "";
        for(int i = 0; i < n; i++) {
            if(n < i + 2) break;

            const int opt = rng_int(1, 2);
            if(opt == 1) {
                S.pb('b');;
                S.pb('a');
            } else {
                S.pb('c');
                S.pb('e');
                S.pb('d');
            }
        }

        dbg(S);

        str out1 = Solution1::solve(S); // jiangly
        // str out2 = Solution2::solve(S); // CS
        // str out3 = Solution3::solve(S); // Mazapan
        str out4 = Solution4::solve(S); // io

        dbg(S, out1, out4);
        if(out1 != out4) {
            dbg("go", S, out1, out4, ":v");
            break;
        }

    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << getCurrentTime() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
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
