#pragma GCC optimize ("Ofast")
#undef _GLIBCXX_DEBUG //? for Stress Testing

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
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}
//* /Template

ll cost(ll n, vl& a, vl& b) {
    vl c(n); for(int i = 0; i < n; i++) c[i] = a[i] ^ b[i];
    ll ans = c.ft; for(auto& it: c) ans &= it;
    // dbg(n, a, b, ans);
    return ans;
}

ll brute(ll n, vl a, vl b) {
    sor(a);
    sor(b);
    ll mx = -BIG;
    map<ll, vvl> hist;
    do {
        ll cur = cost(n, a, b);
        ckmax(mx, cur);
        hist[cur].eb(b);
    } while(next_permutation(all(b)));
    // dbg(mx);
    // for(auto& x: hist[mx]) dbg(x);
    // dbg(a);
    return mx;
}

ll slv(ll n, vl a, vl b) {
    if(n == 1) return a.ft ^ b.ft;

    vpl groups{mp(0, n - 1)};
    ll ans = 0;
    for(ll bit = 34LL; bit >= 0; bit--) {
        bool gok = true;
        vpl new_groups;
        for(auto& [l, r]: groups) {
            sort(a.begin() + l, a.begin() + r + 1, [&](ll x, ll y) {
                ll bit_x = x & (1LL << bit);
                ll bit_y = y & (1LL << bit);
                return bit_x < bit_y;
            });
            sort(b.begin() + l, b.begin() + r + 1, [&](ll x, ll y) {
                ll bit_x = x & (1LL << bit);
                ll bit_y = y & (1LL << bit);
                return bit_x < bit_y;
            });
            reverse(b.begin() + l, b.begin() + r + 1);

            ll partition_point = -1;
            for(int i = l; i <= r; i++) {
                if((a[i] & (1LL << bit)) == (b[i] & (1LL << bit))) {
                    gok = false;
                    break;
                }
                if(l <= i - 1 && (a[i - 1] & (1LL << bit)) != (a[i] & (1LL << bit))) {
                    partition_point = i - 1;
                }
            }
            if(!gok) break;
            if(partition_point == -1) {
                new_groups.eb(l, r);
            } else {
                new_groups.eb(l, partition_point);
                new_groups.eb(partition_point + 1, r);
            }
        }
        if(gok) {
            ans |= (1LL << bit);
            swap(groups, new_groups);
        }
    }

    return ans;
}

void solve() {
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    vl b(n); for(auto& x: b) cin >> x;
    dbg(n);
    dbg(a);
    dbg(b);
    ll ans = slv(n, a, b);
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
        vl a(n); for(auto& x: a) x = rng_ll(0, 5);
        vl b(n); for(auto& x: b) x = rng_ll(0, 5);
        sor(a);
        dbg(n);
        dbg(a);
        dbg(b);
        dbg("Brute");
        ll ans = brute(n, a, b);
        dbg("/Brute");
        dbg("Greedy");
        ll greedy = slv(n, a, b);
        dbg("/Greedy");
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    while(0) {
        RAYA;
        ll n = ll(1e5);
        vl a(n); for(auto& x: a) x = rng_ll(0LL, (1LL << 30LL) - 1LL);
        vl b(n); for(auto& x: b) x = rng_ll(0LL, (1LL << 30LL) - 1LL);
        dbg(n);
        db last = time_elapsed();
        ll greedy = slv(n, a, b);
        dbg(greedy);
        db current = time_elapsed();
        db taken = current - last;
        dbg(taken);
        if(taken > db(3)) chk(false);
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
