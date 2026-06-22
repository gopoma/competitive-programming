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

/**
 * Description: insert string of lowercase letters
 */

struct vertex {
    char alphabet;
    bool exist;
    //? vector<vertex *> child;
    map<int, vertex *> child;

    vertex(char a) : alphabet(a), exist(false) {
        //? child.assign(26, NULL);
    }
};

class Trie {        // this is TRIE
private:            // NOT Suffix Trie
    vertex *root;

public:
    Trie() { root = new vertex('!'); }

    void insert(string word) { // insert a word into trie
        vertex *cur = root;
        for (int i = 0; i < (int)word.size(); ++i) { // O(n)
            int alphaNum = word[i] - 'a';
            if (cur->child[alphaNum] == NULL) // add new branch if NULL
                cur->child[alphaNum] = new vertex(word[i]);
            cur = cur->child[alphaNum];
        }
        cur->exist = true;
    }

    vi query(string word) { // insert a word into trie
        vi ans;
        vertex *cur = root;
        for (int i = 0; i < (int)word.size(); ++i) { // O(n)
            int alphaNum = word[i] - 'a';
            cur = cur->child[alphaNum];
            if(cur == NULL) break;
            if(cur->exist) ans.eb(i + 1);
        }
        return ans;
    }
};
//* /Template

void solve() {
    // <>
    int n; cin >> n;
    str S; cin >> S;

    int m; cin >> m;
    V<str> words(m);
    for(auto& x: words) cin >> x;

    dbg(n);
    dbg(S);
    dbg(m);
    dbg(words);



    V<str> cWords(m);
    Trie st;

    for(int i = 0; i < m; i++) {
        str temp = words[i];
        reverse(all(temp));
        for(auto& c: temp) c = tolower(c);

        cWords[i] = temp;
        st.insert(temp);
    }
    dbg(cWords);



    map<H, int> forwards;
    for(int i = 0; i < m; i++) {
        HashRange hTemp; hTemp.add(cWords[i]);
        H xTemp = hTemp.hash(0, sz(cWords[i]) - 1);

        forwards[xTemp] = i;
    }

    HashRange hS; hS.add(S);
    V<bool> dp(n + 1);
    V<int> nxt(n + 1);
    for(int i = n; i >= 0; i--) {
        if(i == n) {
            dp[i] = true;
            nxt[i] = -1;
        } else {
            dp[i] = false;

            const int L = i;
            const int R = n - 1;
            str current = S.substr(L, R - L + 1);
            vi transitions = st.query(current);
            dbg(S, i, current, transitions);
            each(d, transitions) {
                if(dp[i + d]) {
                    nxt[i] = i + d - 1;
                    dp[i] = true;
                }
            }
        }
    }

    dbg(dp);
    dbg(nxt);
    assert(dp[0]);

    V<pi> intervals;

    int current = 0;
    while(true) {
        int nxt_current = nxt[current];

        if(current == n) break;

        intervals.emplace_back(current, nxt_current);
        current = nxt_current + 1;
    }

    V<str> response;
    for(auto& [l, r]: intervals) {
        dbg(l, r, S.substr(l, r - l + 1));
        str fragment = words[forwards[hS.hash(l, r)]];
        response.emplace_back(fragment);
    }

    for(auto& x: response) cout << x << " ";
    cout << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    // <>
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
