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
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
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

void solve() {
    // <>
    ll n, k; cin >> n >> k;
    vl X(k); for(auto& it: X) { cin >> it; it--; }
    vl C(k); for(auto& it: C) cin >> it;

    if(X.front() == 2 && C.front() != 3) {
        cout << "NO\n";
        return;
    }

    if(X.front() != 2) {
        X.insert(X.begin(), 2);
        C.insert(C.begin(), 3);
        k++;
    }

    dbg(n, k);
    dbg(X);
    dbg(C);

    vl dp(n);
    dp[0] = 1;
    dp[1] = 2;

    for(int i = 0; i < k; i++) {
        dp[X[i]] = C[i];
        if(i + 1 < k) {
            ll cnt = C[i];
            for(int j = X[i]; j < X[i + 1]; j++) {
                dp[j] = min(cnt, C[i + 1]);
                cnt++;
            }
        }
    }

    dbg(dp);
    for(int i = 1; i < n; i++) {
        if(!(dp[i - 1] == dp[i] || dp[i - 1] + 1 == dp[i])) {
            cout << "NO\n";
            return;
        }
    }


    string S(n, '?');
    string base = "ab";
    S[0] = 'a';
    S[1] = 'b';
    int i = 2;

    vector<int> lst(26, -1);
    lst[0] = 0;
    lst[1] = 1;
    for(; i < n;) {
        RAYA;
        dbg(i);
        if(dp[i] != dp[i - 1]) {
            dbg("diff");
            char adi = char(base.back() + 1);
            base.push_back(adi);

            int j = i;
            while(j < n && dp[j - 1] != dp[j]) {
                S[j] = adi;
                lst[S[j] - 'a'] = j;
                j++;
            }
            i = j;
        } else {
            int j = i;
            while(j < n && dp[j - 1] == dp[j]) {
                int mn = INF;
                int id = -1;
                for(int x = 0; x < sz(base); x++) {
                    if(lst[x] < mn) {
                        mn = lst[x];
                        id = x;
                    }
                }

                S[j] = base[id];
                lst[S[j] - 'a'] = j;
                j++;
            }

            i = j;
        }
    }
    cout << "YES\n";
    cout << S << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    cin >> t;
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
