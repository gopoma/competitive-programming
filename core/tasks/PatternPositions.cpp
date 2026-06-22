//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

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
const vector<string> __C_DBG{"\033[1;34m", "\033[0;32m = \033[35m", "\033[0m", "]\033[35m:", "\033[101m", "\033[0m"};
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << __C_DBG[0] << #x << __C_DBG[1] << to_string(xd) << __C_DBG[2] << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << __C_DBG[0] << "[" << #__VA_ARGS__ << __C_DBG[3]; debug_out(__VA_ARGS__); cout << __C_DBG[2];)

#define GA          dbg(0)
// RAYA tiene 32 caracteres "="
#define RAYA        cout << __C_DBG[4] << "================================" << __C_DBG[5] << endl;

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

using pi = pair<int,int>;
using pl = pair<ll, ll>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vl = V<ll>;
using vb = V<bool>;
using vpi = V<pi>;
using vpl = V<pl>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
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

const int MOD = 1e9+7;
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

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

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}

void setIn(string s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
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

//* Template
/**
 * Description: Sort suffixes. First element of \texttt{sa} is \texttt{sz(S)},
 	* \texttt{isa} is the inverse of \texttt{sa}, and \texttt{lcp} stores
 	* the longest common prefix between every two consecutive elements of \texttt{sa}.
 * Time: O(N\log N)
 * Source: SuprDewd, KACTL, majk, ekzhang (http://ekzlib.herokuapp.com)
 * Verification:
	* https://open.kattis.com/problems/suffixsorting
	* https://judge.yosupo.jp/problem/suffixarray
 */


/**
 * Description: 1D range minimum query. If TL is an issue, use
	* arrays instead of vectors and store values instead of indices.
 * Source: KACTL
 * Verification:
	* https://cses.fi/problemset/stats/1647/
	* http://wcipeg.com/problem/ioi1223
	* https://pastebin.com/ChpniVZL
 * Memory: O(N\log N)
 * Time: O(1)
 */

tcT> struct RMQ { // floor(log_2(x))
	int level(int x) { return 31-__builtin_clz(x); }
	V<T> v; V<vi> jmp;
	int cmb(int a, int b) {
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); }
	void init(const V<T>& _v) {
		v = _v; jmp = {vi(sz(v))};
		iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vi(sz(v)-(1<<j)+1));
			F0R(i,sz(jmp[j])) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
	T query(int l, int r) { return v[index(l,r)]; }
};

struct SuffixArray {
	str S; int N; vi sa, isa, lcp;
	void init(str _S) { N = sz(S = _S)+1; genSa(); genLcp(); }
	void genSa() { // sa has size sz(S)+1, starts with sz(S)
		sa = isa = vi(N); sa[0] = N-1; iota(1+all(sa),0);
		sort(1+all(sa),[&](int a, int b) { return S[a] < S[b]; });
		FOR(i,1,N) { int a = sa[i-1], b = sa[i];
			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i; }
		for (int len = 1; len < N; len *= 2) { // currently sorted
			// by first len chars
			vi s(sa), is(isa), pos(N); iota(all(pos),0);
			each(t,s) {int T=t-len;if (T>=0) sa[pos[isa[T]]++] = T;}
			FOR(i,1,N) { int a = sa[i-1], b = sa[i]; /// verify that nothing goes out of bounds
				isa[b] = is[a]==is[b]&&is[a+len]==is[b+len]?isa[a]:i; }
		}
	}
	void genLcp() { // Kasai's Algo
		lcp = vi(N-1); int h = 0;
		F0R(b,N-1) { int a = sa[isa[b]-1];
			while (a+h < sz(S) && S[a+h] == S[b+h]) ++h;
			lcp[isa[b]-1] = h; if (h) h--; }
		R.init(lcp); /// if we cut off first chars of two strings
		/// with lcp h then remaining portions still have lcp h-1
	}
	RMQ<int> R;
	int getLCP(int a, int b) { // lcp of suffixes starting at a,b
		if (a == b) return sz(S)-a;
		int l = isa[a], r = isa[b]; if (l > r) swap(l,r);
		return R.query(l,r-1);
	}
};

//* /Template

void solve() {
    // <>
    str S; cin >> S;
    int q; cin >> q;
    V<str> que(q); for(auto& x: que) cin >> x;
    const int n = sz(S);

    dbg(n);
    dbg(S);
    dbg(q);
    dbg(que);

    SuffixArray SA; SA.init(S);
    dbg(SA.sa);

    for(int i = 1; i <= n; i++) {
        dbg(SA.sa[i], S.substr(SA.sa[i], (n - 1) - SA.sa[i] + 1));
    }

    RMQ<int> st; st.init(SA.sa);

    auto lbound = [&](str& pattern) {
        auto check = [&](int middle) -> bool {
            return pattern <= S.substr(SA.sa[middle], min(sz(pattern), (n - 1) - SA.sa[middle] + 1));
        };
        int left = 0; // always bad
        int right = n + 1; // always good
        while(left + 1 < right) {
            int middle = (left + right) >> 1;
            if(check(middle)) right = middle;
            else left = middle;
        }
        return right;
    };

    auto ubound = [&](str& pattern) {
        auto check = [&](int middle) -> bool {
            return pattern < S.substr(SA.sa[middle], min(sz(pattern), (n - 1) - SA.sa[middle] + 1));
        };
        int left = 0; // always bad
        int right = n + 1; // always good
        while(left + 1 < right) {
            int middle = (left + right) >> 1;
            if(check(middle)) right = middle;
            else left = middle;
        }
        return right;
    };

    for(auto& x: que) {
        int left = lbound(x);
        int right = ubound(x);
        dbg(x, left, right);

        int re = right - left;
        bool ok = (re > 0);
        if(!ok) {
            cout << "-1\n";
        } else {
            int id = st.query(left, right - 1);
            cout << id + 1 << "\n";
        }
    }

    // <>
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    //* cin >> t;
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
