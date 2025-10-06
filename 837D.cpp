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
//* /Template



int     dp[200 + 1][60 + 1][60 + 1];
int nxt_dp[200 + 1][60 + 1][60 + 1];
int brute(int n, int k, vl a) {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= 60; j++) {
            for(int k = 0; k <= 60; k++) {
                dp[i][j][k] = nxt_dp[i][j][k] = 0;
            }
        }
    }

    vi p2(n), p5(n);
    for(int i = 0; i < n; i++) {
        while(a[i] % 2 == 0) {
            p2[i]++;
            a[i] /= 2LL;
        }
        while(a[i] % 5 == 0) {
            p5[i]++;
            a[i] /= 5LL;
        }
    }

    for(int i = 0; i < n; i++) {
        dbg(i, p2[i], p5[i]);
    }

    for(int i = n; i >= 0; i--) {
        for(int cnt = 0; cnt <= k + 1; cnt++) {
            for(int twos = 0; twos < 60; twos++) {
                for(int fives = 0; fives < 60; fives++) {
                    if(cnt == k) {
                        dp[cnt][twos][fives] = min(twos, fives);
                    } else if(i == n) {
                        if(cnt == k) {
                            dp[cnt][twos][fives] = min(twos, fives);
                        } else {
                            dp[cnt][twos][fives] = 0;
                        }
                    } else {
                        dp[cnt][twos][fives] = 0;
                        // skip
                        dp[cnt][twos][fives] = max(dp[cnt][twos][fives], nxt_dp[cnt][twos][fives]);
                        // take
                        dp[cnt][twos][fives] = max(dp[cnt][twos][fives], nxt_dp[cnt + 1][twos + p2[i]][fives + p5[i]]);
                    }
                }
            }
        }
        for(int cnt = 0; cnt <= k + 1; cnt++) {
            for(int twos = 0; twos < 60; twos++) {
                for(int fives = 0; fives < 60; fives++) {
                    nxt_dp[cnt][twos][fives] = dp[cnt][twos][fives];
                }
            }
        }
    }

    int re = dp[0][0][0];
    return re;
}

int slv(int n, int k, vl a) {
    vi p2(n), p5(n);
    for(int i = 0; i < n; i++) {
        while(a[i] % 2 == 0) {
            p2[i]++;
            a[i] /= 2LL;
        }
        while(a[i] % 5 == 0) {
            p5[i]++;
            a[i] /= 5LL;
        }
    }

    for(int i = 0; i < n; i++) {
        dbg(i, p2[i], p5[i]);
    }

    const int choose = n - k;
    dbg(choose);
    pair<int, int> g = {INF, INF};
    {
        // dp[i][subset_cnt]: min amount of cnt_2
        pair<int, int> dp[200 + 1][200 + 1];
        for(int i = n; i >= 0; i--) {
            for(int subset_cnt = 0; subset_cnt <= n; subset_cnt++) {
                if(i == n) {
                    if(subset_cnt == choose) {
                        dp[i][subset_cnt] = {0, 0};
                    } else {
                        dp[i][subset_cnt] = {INF, INF};
                    }
                } else {
                    dp[i][subset_cnt] = {INF, INF};
                    // skip
                    dp[i][subset_cnt] = min(dp[i][subset_cnt], dp[i + 1][subset_cnt]);
                    // take
                    dp[i][subset_cnt] = min(dp[i][subset_cnt], {dp[i + 1][subset_cnt + 1].first + p2[i], dp[i + 1][subset_cnt + 1].second + p5[i]});
                }
            }
        }
        g = dp[0][0];
    }

    pair<int, int> g2;
    {
        // dp[i][subset_cnt]: min amount of cnt_5
        pair<int, int> dp[200 + 1][200 + 1];
        for(int i = n; i >= 0; i--) {
            for(int subset_cnt = 0; subset_cnt <= n; subset_cnt++) {
                if(i == n) {
                    if(subset_cnt == choose) {
                        dp[i][subset_cnt] = {0, 0};
                    } else {
                        dp[i][subset_cnt] = {INF, INF};
                    }
                } else {
                    dp[i][subset_cnt] = {INF, INF};
                    // skip
                    dp[i][subset_cnt] = min(dp[i][subset_cnt], dp[i + 1][subset_cnt]);
                    // take
                    dp[i][subset_cnt] = min(dp[i][subset_cnt], {dp[i + 1][subset_cnt + 1].first + p5[i], dp[i + 1][subset_cnt + 1].second + p2[i]});
                }
            }
        }
        g2 = dp[0][0];
        swap(g2.first, g2.second);
    }

    int re = 0;
    {
        int cnt_2 = 0;
        int cnt_5  = 0;
        for(int i = 0; i < n; i++) {
            cnt_2 += p2[i];
            cnt_5 += p5[i];
        }
        dbg(cnt_2, cnt_5);
        dbg(g, g2);
        re = 0;
        re = max(re, min(cnt_2 - g.first, cnt_5 - g.second));
        re = max(re, min(cnt_2 - g2.first, cnt_5 - g2.second));
    }

    return re;
}

void solve() {
    int n, k; cin >> n >> k;
    vl a(n); for(auto& x: a) cin >> x;

    dbg(n, k);
    dbg(a);

    int re = slv(n, k, a);
    dbg(re);
    cout << re << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(1) {
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        int n = rng_ll(1, 5);
        int k = rng_ll(1, n);
        vl a(n); for(auto& x: a) x = rng_ll(1, 100);
        dbg(n, k);
        dbg(a);

        ll ans = brute(n, k, a);
        dbg("Greedy");
        ll gre = slv(n, k, a);
        dbg("/Greedy");
        dbg(ans, gre);
        assert(ans == gre);
    }

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
