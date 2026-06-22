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
/**
 * Description: Polynomial hash for substrings with two bases.
 * Source:
	* KACTL
	* https://codeforces.com/contest/1207/submission/59309672
 * Verification:
	* USACO Dec 17 Plat 1 (LCP :o)
	* CF Check Transcription
 */

using H = AR<int,2>; // bases not too close to ends
H makeH(char c) { return {c,c}; }
uniform_int_distribution<int> BDIST(0.1*MOD,0.9*MOD);
const H base{BDIST(rng),BDIST(rng)};
/// const T ibase = {(int)inv(mi(base[0])),(int)inv(mi(base[1]))};
H operator+(H l, H r) {
	F0R(i,2) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
	return l; }
H operator-(H l, H r) {
	F0R(i,2) if ((l[i] -= r[i]) < 0) l[i] += MOD;
	return l; }
H operator*(H l, H r) {
	F0R(i,2) l[i] = (ll)l[i]*r[i]%MOD;
	return l; }
/// H& operator+=(H& l, H r) { return l = l+r; }
/// H& operator-=(H& l, H r) { return l = l-r; }
/// H& operator*=(H& l, H r) { return l = l*r; }

V<H> pows{{1,1}};
struct HashRange {
	str S; V<H> cum{{}};
	void add(char c) { S += c; cum.pb(base*cum.bk+makeH(c)); }
	void add(str s) { each(c,s) add(c); }
	void extend(int len) { while (sz(pows) <= len)
		pows.pb(base*pows.bk); }
	H hash(int l, int r) { int len = r+1-l; extend(len);
		return cum[r+1]-pows[len]*cum[l]; }
	/**int lcp(HashRange& b) { return first_true([&](int x) {
		return cum[x] != b.cum[x]; },0,min(sz(S),sz(b.S)))-1; }*/
};
/// HashRange HR; HR.add("ababab"); F0R(i,6) FOR(j,i,6) ps(i,j,HR.hash(i,j));
//* /Template

bool isPalindrome(str S) {
    const int n = sz(S);
    int l = 0;
    int r = n - 1;
    while(l < r) {
        if(S[l] != S[r]) return false;
        l++;
        r--;
    }
    return true;
}

bool isGood(str S) {
    const int n = sz(S);
    str T = S;
    sor(T);
    do {
        bool ok = true;
        for(int i = 0; i + 1 < n; i++) {
            str left_S, left_T, right_S, right_T;
            for(int j = 0; j <= i; j++) {
                left_S.pb(S[j]);
                left_T.pb(T[j]);
            }
            for(int j = i + 1; j < n; j++) {
                right_S.pb(S[j]);
                right_T.pb(T[j]);
            }
            sor(left_S);
            sor(left_T);
            sor(right_S);
            sor(right_T);
            if(left_S == left_T && right_S == right_T) {
                ok = false;
                break;
            }
        }
        if(ok) return true;
    } while(next_permutation(all(T)));
    return false;
}

vb brute(str S, ll q, vpl queries) {
    const int n = sz(S);
    vb response;
    for(auto& [l, r]: queries) {
        str temp = S.substr(l, r - l + 1);
        bool ok = isGood(temp);
        dbg(l, r, temp, ok);
        response.eb(ok);
    }
    return response;
}

vb slv(str S, ll q, vpl queries) {
    const int n = sz(S);
    vvl pref(n, vl(26));
    for(int i = 0; i < n; i++) {
        int ord = int(S[i] - 'a');
        // dbg(ord);
        pref[i][ord]++;
        for(int j = 0; j < 26; j++) {
            if(0 <= i - 1) pref[i][j] += pref[i - 1][j];
        }
    }

    HashRange S_H, S_H_rev;
    {
        str SS = S;
        S_H.add(SS);
        reverse(all(SS));
        S_H_rev.add(SS);
    }
    auto isPalindrome = [&](int l, int r) -> bool {
        auto v = S_H.hash(l, r);
        dbg("bef", l, r);
        int gl = l, gr = r;
        l = (n - 1) - gr;
        r = (n - 1) - gl;
        if(l > r) swap(l, r);
        auto v2 = S_H_rev.hash(l, r);
        dbg("af", l ,r);
        return (v == v2);
    };

    vb response;
    vi hist(26);
    for(auto& [l, r]: queries) {
        // dbg(l, r);
        int d = 0;
        for(int i = 0; i < 26; i++) {
            int cnt = pref[r][i];
            if(0 <= l - 1) cnt -= pref[l - 1][i];
            d += bool(cnt);
            hist[i] = cnt;
        }
        if(d == 1) {
            if(r - l == 0) response.eb(true);
            else response.eb(false);
        } else {
            if(d == 2) {
                vl cnt;
                for(int i = 0; i < 26; i++) if(hist[i] > 0) cnt.eb(hist[i]);
                if(cnt[0] > cnt[1]) swap(cnt[0], cnt[1]);
                if(S[l] == S[r] && cnt[1] >= cnt[0]) response.eb(false);
                else response.eb(true);
            } else {
                bool ok_left = (l + ((S[l] == S[r])) + hist[S[r] - 'a'] - 1 < r);
                bool ok_right = (r - ((S[r] == S[l])) - hist[S[l] - 'a'] + 1 > l);
                bool ok = ok_left || ok_right;
                if(ok) response.eb(true);
                else response.eb(false);
            }
        }
    }
    return response;
}

void solve() {
    str S; cin >> S;
    ll q; cin >> q;
    vpl queries(q);
    for(auto& [l, r]: queries) {
        cin >> l >> r; l--; r--;
    }
    vb response = slv(S, q, queries);
    for(auto&& x: response) cout << (x?"Yes":"No") << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    dbg(isDebugging);

    //? Stress Testing
    while(0) {
        RAYA;
        const int n = rng_int(1, 10);
        str S; rep(n) S.pb('a'+rng_int(0, 25));
        dbg(n);
        dbg(S);
        ll q = rng_ll(1, 10);
        dbg(q);
        vpl queries(q);
        for(auto& [l, r]: queries) {
            l = rng_int(0, n - 1);
            r = rng_int(l, n - 1);
        }
        dbg(queries);
        vb ans = brute(S, q, queries);
        vb greedy = slv(S, q, queries);
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
