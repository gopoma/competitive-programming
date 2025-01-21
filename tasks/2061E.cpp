#pragma GCC optimize ("Ofast")
// #undef _GLIBCXX_DEBUG //? for Stress Testing

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



const int MOD = 1e9+7;
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
#define tcT template <class T
#define tcTU tcT, class U
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}
//* /Template

ll brute(ll n, ll m, ll k, vl a, vl b) {
    a.eb(0);
    map<ll, map<ll, map<ll, bool>>> vis;
    map<ll, map<ll, map<ll, ll>>> memo;
    auto dp = [&](const auto& dp, ll i, ll cur_val, ll used_opts) -> ll {
        if(i == n) return 0LL;

        if(vis[i][cur_val][used_opts]) return memo[i][cur_val][used_opts];
        vis[i][cur_val][used_opts] = true;

        ll ans = dp(dp, i + 1, a[i + 1], used_opts) + cur_val;
        if(used_opts > 0) {
            for(auto& x: b) {
                if((cur_val & x) < cur_val) {
                    ckmin(ans, dp(dp, i, cur_val & x, used_opts - 1));
                }
            }
        }
        return memo[i][cur_val][used_opts] = ans;
    };
    return dp(dp, 0, a[0], k);
}

ll slv(ll n, ll m, ll k, vl a, vl b) {
    vl ms;
    vl mask_values((1 << m) + 5);
    for(ll mask = 1; mask < (1 << m); mask++) {
        ll base = (1LL << 40LL) - 1LL;
        for(ll i = 0; i < m; i++) {
            if(mask & (1LL << i)) {
                base &= b[i];
            }
        }
        mask_values[mask] = base;
    }
    for(ll i = 0; i < n; i++) {
        vl dp(m + 1, BIG);
        ll cur = a[i];
        for(ll mask = 1; mask < (1 << m); mask++) {
            ckmin(dp[__builtin_popcount(mask)], cur & mask_values[mask]);
        }
        for(ll j = 1; j <= m; j++) {
            ms.eb(cur - dp[j]);
            cur = dp[j];
        }
    }

    sort(rall(ms));
    ll ans = 0; for(auto& x: a) ans += x;
    for(ll i = 0; i < k; i++) ans -= ms[i];
    return ans;
}

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    vl a(n); for(auto& x: a) cin >> x;
    vl b(m); for(auto& x: b) cin >> x;
    dbg(n, m, k);
    dbg(a);
    dbg(b);
    ll ans = slv(n, m, k, a, b);
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
        ll n = rng_ll(1, 5);
        ll m = rng_ll(1, 3);
        ll k = rng_ll(0, n * m);

        vl a(n), b(m);
        for(auto& x: a) x = rng_ll(0, ll(1e9));
        for(auto& x: b) x = rng_ll(0, ll(1e9));

        dbg(n, m, k);
        // dbg(a);
        // for(auto& x: a) dbg(bitset<20>(x));
        // dbg(b);
        // for(auto& x: b) dbg(bitset<20>(x));

        dbg("Brute");
        ll ans = brute(n, m, k, a, b);
        dbg("/Brute");
        dbg("Greedy");
        ll greedy = slv(n, m, k, a, b);
        dbg("/Greedy");
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    while(0) {
        RAYA;
        ll n = ll(1e5);
        ll m = 10;
        ll k = n * m;
        dbg(n, m, k);

        vl a(n), b(m);
        for(auto& x: a) x = rng_ll(0, ll(1e9));
        for(auto& x: b) x = rng_ll(0, ll(1e9));

        db last = time_elapsed();
        slv(n, m, k, a, b);
        db current = time_elapsed();
        db taken = current - last;
        dbg(taken);
        if(taken > db(2)) {
            chk(false);
        }
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
