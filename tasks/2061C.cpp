#include <bits/stdc++.h>
using namespace std;



using ll = long long;
using db = long double; // or double if tight TL
using str = string;



using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f first
#define s second



#define tcT template<class T
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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



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



#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



// Debugger
const string PAIR_LEFT = "(";
const string PAIR_RIGHT = ")";
const string IT_LEFT = "[";
const string IT_RIGHT = "]";
const string PAIR_SEP = ", ";
const string IT_SEP = ", ";

// benq - print any container + pair
template<typename T, typename = void> struct is_iterable : false_type {};
template<typename T> struct is_iterable<T, void_t<decltype(begin(declval<T>())),decltype(end(declval<T>()))>> : true_type {};
template<typename T> typename enable_if<is_iterable<T>::value&&!is_same<T, string>::value,ostream&>::type operator<<(ostream &cout, T const &v);
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << PAIR_LEFT << p.f << PAIR_SEP << p.s << PAIR_RIGHT; }
template<typename T> typename enable_if<is_iterable<T>::value&&!is_same<T, string>::value,ostream&>::type operator<<(ostream &cout, T const &v) {
    cout << IT_LEFT;
    for (auto it = v.begin(); it != v.end();) {
        cout << *it;
        if (++it != v.end()) cout << IT_SEP;
    }
    return cout << IT_RIGHT;
}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) {
    cin >> p.first;
    return cin >> p.second;
}

template<typename T> void debug(string s, T x) {cerr << "\033[1;34m" << s << "\033[0;32m = \033[35m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
        if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;34m" << s.substr(0, i) << "\033[0;32m = \033[35m" << x << "\033[31m | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}
template<typename T> void debug_nameless(T x) {cerr << "\033[35m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug_nameless(T x, Args... args) {cerr << "\033[35m" << x << "\033[31m | "; debug_nameless(args...);}



#ifdef LOCAL
    const bool isDebugging = true;

    #define MACRO(code) do {code} while (false)
    #define dbg(...) MACRO(cerr << "Line(" << __LINE__ << "): "; debug(#__VA_ARGS__, __VA_ARGS__);)
    #define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);
    #define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
    const bool isDebugging = false;

    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }
// /Debugger



const int MOD = 998244353;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)



//* Template

/**
 * Description: modular arithmetic operations
 * Source:
 * KACTL
 * https://codeforces.com/blog/entry/63903
 * https://codeforces.com/contest/1261/submission/65632855 (tourist)
 * https://codeforces.com/contest/1264/submission/66344993 (ksun)
 * also see https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp
 * (ecnerwal) Verification: https://open.kattis.com/problems/modulararithmetic
 */

template <int MOD, int RT> struct mint {
	static const int mod = MOD;
	static constexpr mint rt() { return RT; }  // primitive root for FFT
	int v;
	explicit operator int() const {
		return v;
	}  // explicit -> don't silently convert to int
	mint() : v(0) {}
	mint(ll _v) {
		v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD;
	}
	bool operator==(const mint &o) const { return v == o.v; }
	friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
	friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
	friend istream &operator>>(istream &is, mint &a) {
		ll x;
		is >> x;
		a = mint(x);
		return is;
	}
	friend ostream &operator<<(ostream &os, mint a) {
		os << int(a);
		return os;
	}

	mint &operator+=(const mint &o) {
		if ((v += o.v) >= MOD) v -= MOD;
		return *this;
	}
	mint &operator-=(const mint &o) {
		if ((v -= o.v) < 0) v += MOD;
		return *this;
	}
	mint &operator*=(const mint &o) {
		v = int((ll)v * o.v % MOD);
		return *this;
	}
	mint &operator/=(const mint &o) { return (*this) *= inv(o); }
	friend mint pow(mint a, ll p) {
		mint ans = 1;
		assert(p >= 0);
		for (; p; p /= 2, a *= a)
			if (p & 1) ans *= a;
		return ans;
	}
	friend mint inv(const mint &a) {
		assert(a.v != 0);
		return pow(a, MOD - 2);
	}

	mint operator-() const { return mint(-v); }
	mint &operator++() { return *this += 1; }
	mint &operator--() { return *this -= 1; }
	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
};

using mi = mint<MOD, 5>;  // 5 is primitive root for both common mods
using vmi = V<mi>;
using pmi = pair<mi, mi>;
using vpmi = V<pmi>;

//* /Template

const int MAXN = int(2e5) + 5;
bool vis[MAXN][2];
mi  memo[MAXN][2];
void solve() {
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    dbg(n);
    dbg(a);

    for(int i = 0; i <= n + 1; i++) {
        for(int j = 0; j < 2; j++) {
            vis[i][j] = false;
        }
    }
    auto dp = [&](const auto& dp, int i, bool lastWasLiar) -> mi {
        if(i == n) return mi(1);
        if(vis[i][lastWasLiar]) return memo[i][lastWasLiar];
        vis[i][lastWasLiar] = true;

        mi ans = 0;
        if(lastWasLiar) {
            ans += dp(dp, i + 1, false);
        } else {
            if(i == 0) {
                // Try Liar
                if(i + 1 == n) ans += dp(dp, i + 1, true);
                else {
                    if(a[i + 1] == 1) ans += dp(dp, i + 1, true);
                }

                // Try Honest
                if(a[i] == 0) {
                    ans += dp(dp, i + 1, false);
                }
            } else {
                // Try Liar
                if(i + 1 == n) ans += dp(dp, i + 1, true);
                else {
                    if(a[i - 1] + 1 == a[i + 1]) ans += dp(dp, i + 1, true);
                }

                // Try Honest
                if(a[i - 1] == a[i]) ans += dp(dp, i + 1, false);
            }
        }
        dbg(i, lastWasLiar, ans);
        return memo[i][lastWasLiar] = ans;
    };
    mi ans = dp(dp, 0, false);
    dbg(ans);
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    dbg(isDebugging);

    //? Stress Testing
    while(0) {
        RAYA;
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
