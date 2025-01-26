#pragma GCC optimize ("Ofast")

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
//* /Template
str ans;
void brute(int n, int l, int k, str S) {
    sor(S);
    str response = "{";
    do {
        vs tokens;
        for(int i = 0; i < n; i++) {
            str cur;
            for(int j = 0; j < l; j++) {
                cur.pb(S[i * l + j]);
            }
            tokens.eb(cur);
        }
        if(is_sorted(all(tokens))) {
            ckmin(response, tokens[k]);
        }
    } while(next_permutation(all(S)));
    ans = response;
}

str greedy;
void slv(int n, int l, int k, str S) {
    sor(S);
    deque<char> d; for(auto& c: S) d.eb(c);
    dbg(d);
    vs response(n, str(l, '?'));
    dbg(response);
    int left = 0;
    int right = n - 1;
    for(int i = 0; i < l; i++) {
        // RAYA;
        // dbg(i, left, right, k, d);
        for(int j = left; j <= k; j++) {
            response[j][i] = d.ft; d.pop_front();
        }
        for(int j = right; j >= k + 1; j--) {
            response[j][i] = d.bk; d.pop_back();
        }
        // dbg(response);
        int new_left = k;
        while(new_left >= left && response[k][i] == response[new_left][i]) { new_left--; }
        new_left++;

        int new_right = k;
        while(new_right <= right && response[k][i] == response[new_right][i]) { new_right++; }
        new_right--;

        // dbg(k, new_left, new_right);

        for(int j = new_left - 1; j >= left; j--) {
            for(int x = i + 1; x < l; x++) {
                response[j][x] = d.bk; d.pop_back();
            }
        }
        for(int j = right; j > new_right; j--) {
            for(int x = i + 1; x < l; x++) {
                response[j][x] = d.bk; d.pop_back();
            }
        }

        left = new_left;
        right = new_right;
        // dbg(left, right);
    }
    assert(is_sorted(all(response)));
    for(auto& vec: response) for(auto& x: vec) chk(x != '?');
    for(auto& x: response) cout << x << "\n";
    greedy = response[k];
}

void solve() {
    int n, l, k; cin >> n >> l >> k; k--;
    str S; cin >> S;
    dbg(n, l, k);
    dbg(S);
    slv(n, l, k, S);
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    dbg(isDebugging);

    //? Stress Testing
    while(0) {
        RAYA;
        int n = rng_int(1, 3);
        int l = rng_int(1, 3);
        int k = rng_int(0, n - 1);
        str S; rep(n * l) S.pb(char('a' + rng_int(0, 25)));
        dbg(n, l, k);
        dbg(S);
        dbg("Brute");
        brute(n, l, k, S);
        dbg("/Brute");
        dbg("Greedy");
        slv(n, l, k, S);
        dbg("/Greedy");
        dbg(ans, greedy);
        chk(ans == greedy);
    }

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
