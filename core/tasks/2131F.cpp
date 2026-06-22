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
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(xd) << "\033[0m" << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m";)

#define GA          dbg(0)
#define RAYA        cout << "\033[101m" << "================================" << "\033[0m" << endl;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
#endif
//* /Debugger

using ll = long long;
using db = long double; // or double if tight TL
using str = string;

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

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

//* Template
//* /Template

const ll BIG = ll(1e18) + 5;

ll brute(ll n, string a, string b) {
    vector<vector<ll>> mn_dist(n, vector<ll>(n, BIG));
    for(int maska = 0; maska < (1 << n); maska++) {
        for(int maskb = 0; maskb < (1 << n); maskb++) {
            string A = a, B = b;
            int cur = 0;
            for(int bit = 0; bit < n; bit++) {
                if(maska & (1 << bit)) {
                    A[bit] = (A[bit] == '1') ? '0' : '1';
                    cur++;
                }
                if(maskb & (1 << bit)) {
                    B[bit] = (B[bit] == '1') ? '0' : '1';
                    cur++;
                }
            }

            vector<vector<int>> mat(n, vector<int>(n));
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    mat[i][j] = int(A[i] - '0') ^ int(B[j] - '0');
                }
            }
            if(mat[0][0] == 0) {
                vector<pair<int, int>> dir;
                dir.emplace_back(+1, 0);
                dir.emplace_back(0, +1);

                auto check = [&](int i, int j) -> bool {
                    return (0 <= i && i < n) && (0 <= j && j < n);
                };

                vector<vector<bool>> vis(n, vector<bool>(n));
                vis[0][0] = true;

                deque<pair<int, int>> q; q.emplace_back(0, 0);


                while(!q.empty()) {
                    auto [i, j] = q.front(); q.pop_front();

                    mn_dist[i][j] = min(mn_dist[i][j], ll(cur));

                    for(auto& [dx, dy]: dir) {
                        int ni = i + dx;
                        int nj = j + dy;
                        if(check(ni, nj) && !vis[ni][nj] && mat[ni][nj] == 0) {
                            vis[ni][nj] = true;
                            q.emplace_back(ni,  nj);
                        }
                    }
                }
            }
        }
    }
    ll re = 0;
    for(auto& vec: mn_dist) {
        re += accumulate(all(vec), 0LL);
        dbg(vec);
    }
    return re;
}

ll slv(ll n, string a, string b) {
    auto get = [&](string S, string T) -> vl {
        vector<vector<ll>> cnt(2, vector<ll>(n));
        for(int i = 0; i < n; i++) {
            if(S[i] == '0') {
                cnt[0][i]++;
            } else {
                cnt[1][i]++;
            }
        }

        for(int i = 0; i < 2; i++) {
            for(int j = 1; j < n; j++) {
                cnt[i][j] += cnt[i][j - 1];
            }
        }
        vector<ll> dp(n, BIG);
        for(int i = 0; i < n; i++) {
            if(T.front() == '0') {
                dp[i] = min(dp[i], min(cnt[1][i], 1LL + cnt[0][i]));
            } else {
                dp[i] = min(dp[i], min(cnt[0][i], 1LL + cnt[1][i]));
            }
        }
        return dp;
    };

    vector<ll> dpa = get(a, b);
    vector<ll> dpb = get(b, a);
    assert(dpa.front() == dpb.front());
    dbg(dpa, dpb);

    ll re = accumulate(all(dpa), 0LL) + accumulate(all(dpb), 0LL) - dpa.front();
    // dbg(re);

    vector<ll> pref = dpa;
    for(int i = 1; i < n; i++) {
        pref[i] += pref[i - 1];
    }

    for(int i = 1; i < n; i++) {
        ll size = (n - 1);
        ll contrib = (pref[n - 1] - dpa.front()) + size * dpb[i];
        // dbg(pref[i], dpa.front(), size, dpb[i]);
        // dbg(contrib);
        dbg(contrib);
        re += contrib;
    }
    return re;
}

void solve() {
    ll n; cin >> n;
    string a, b; cin >> a >> b;

    ll re = brute(n, a, b);
    dbg(re);
    cout << re << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(1) {
        RAYA;
        RAYA;
        RAYA;
        ll n = rng_ll(6, 6);
        string a, b;
        for(int i = 0; i < n; i++) {
            a.push_back(to_string(rng_ll(0, 1)).front());
            b.push_back(to_string(rng_ll(0, 1)).front());
        }
        dbg(n, a, b);
        dbg("/Brute");
        ll ans = brute(n, a, b);
        dbg("/Brute");
        dbg("/Greedy");
        ll gre = slv(n, a, b);
        dbg("/Greedy");
        dbg(ans, gre);
        assert(ans == gre);
    }

    int t = 1; cin >> t;
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
