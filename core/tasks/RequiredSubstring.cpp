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
const int alpha = 26;
const char a = 'A';

struct node{
  int next[alpha] = {}, link[alpha] = {};
  int suf = 0;
  int visited = 0, ans = 0;
  int bad = 0; // any term is reachable by suf links
  vector<int> term;
  node() {
    fill(next, next + alpha, -1);
  }
};

vector<node> mem;

int get_next_or_create(int nd, char c) {
  if (mem[nd].next[c - a] == -1) { mem[nd].next[c - a] = mem.size(); mem.emplace_back(); }
  return mem[nd].next[c - a];
}

void build(vector<string> t) {
  mem.reserve(1e2 + 100);mem.clear();
  mem.emplace_back();
  // 0th element is nullptr, 1st is the root
  for (int j = 0; j < t.size(); ++j) {
    int cur = 0;
    for (char c : t[j]) cur = get_next_or_create(cur, c);
    mem[cur].term.push_back(j);
  }
  vector<int> bfs_order;
  queue<int> bfs;
  {
    node &root = mem[0];
    root.suf = 0;
    for (char c = a; c < a + alpha; ++c) {
      root.link[c - a] = (root.next[c - a] == -1 ? 0 : root.next[c - a]);
    }
    bfs.push(0);
  }
  while (!bfs.empty()) {
    int cur_idx = bfs.front();
    bfs.pop();
    node &cur = mem[cur_idx];
    cur.bad = cur.term.size() > 0 || mem[cur.suf].bad;
    bfs_order.push_back(cur_idx);
    for (char c = a; c < a + alpha; ++c) {
      int nxt_idx = cur.next[c - a];
      if (nxt_idx == -1) continue;
      node &nxt = mem[nxt_idx];
      nxt.suf = (cur_idx ? mem[cur.suf].link[c - a] : 0);
      for (char c = a; c < a + alpha; ++c) {
        nxt.link[c - a] = (nxt.next[c - a] == -1 ? mem[nxt.suf].link[c - a] : nxt.next[c - a]);
      }
      bfs.push(nxt_idx);
    }
  }
  // do something
}
//be16ed
//* /Template


bool vis[1000 + 1][100 + 5][2];
int memo[1000 + 1][100 + 5][2];
void solve() {
    // <>
    int n; cin >> n;
    string pattern; cin >> pattern;
    const int m = sz(pattern);

    dbg(n);
    dbg(m);
    dbg(pattern);

    vector<string> t{pattern};
    build(t);

    function<int(int, int, bool)> dp = [&](int i, int j, bool ok) -> int {
        if(i == n) {
            if(ok) return 1;
            else return 0;
        }

        if(vis[i][j][ok]) return memo[i][j][ok];
        vis[i][j][ok] = true;

        int re = 0;

        if(ok) {
            for(int nxt = 0; nxt < 26; nxt++) {
                re += dp(i + 1, mem[j].link[nxt], true);
                re %= MOD;
            }
        } else {
            for(int nxt = 0; nxt < 26; nxt++) {
                re += dp(i + 1, mem[j].link[nxt], mem[mem[j].link[nxt]].bad);
                re %= MOD;
            }
        }

        return memo[i][j][ok] = (re % MOD);
    };

    int re = dp(0, 0, false);
    cout << re << "\n";
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
