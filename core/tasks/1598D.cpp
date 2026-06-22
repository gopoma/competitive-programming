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

using vpl = vector<pair<ll, ll>>;
void solve() {
    ll n; cin >> n;
    vpl info(n); for(auto& [a, b]: info) cin >> a >> b;

    auto query = [&](vector<ll>& pref, ll L, ll R) -> ll {
        if(L < 0 || R < 0 || L >= sz(pref) || R >= sz(pref) || L > R) return 0;
        ll sum = pref[R];
        if(0 <= L - 1) sum -= pref[L - 1];
        return sum;
    };

    auto get = [&](bool rev) -> ll {
        vpl arr = info;
        if(rev) {
            for(auto& [a, b]: arr) {
                swap(a, b);
            }
        }

        map<ll, ll> hist;
        for(auto& [a, b]: arr) {
            hist[a]++;
        }

        vl cnt;
        for(auto& [val, freq]: hist) {
            cnt.emplace_back(freq);
        }
        vl pref = cnt;
        for(int i = 1; i < sz(pref); i++) pref[i] += pref[i - 1];


        ll res = 0;
        for(int i = 1; i + 1 < sz(pref); i++) {
            res += query(pref, 0, i - 1) * query(pref, i, i) * query(pref, i + 1, sz(pref) - 1);
        }
        return res;
    };

    ll response = 0;
    ll contrib1 = get(false);
    ll contrib2 = get(true);
    dbg(contrib1, contrib2);
    response += contrib1 + contrib2;

    map<ll, vector<ll>> G;
    for(auto& [a, b]: info) G[a].emplace_back(b);
    vector<pair<ll, vl>> E;
    for(auto& [val, values]: G) {
        sort(all(values));
        E.emplace_back(val, values);
    }
    //*for(auto& [val, values]: E) {
    //*    dbg(val, values);
    //*}

    map<ll, ll> hist_left, hist_right;
    ll cnt_left = 0, cnt_right = 0;

    ll sr = 0;

    for(auto& x: E[0].second) {
        sr -= hist_left[x] * hist_right[x];

        hist_left[x]++;
        cnt_left++;

        sr += hist_left[x] * hist_right[x];
    }
    for(int i = 2; i < sz(E); i++) {
        for(auto& x: E[i].second) {
            sr -= hist_left[x] * hist_right[x];

            hist_right[x]++;
            cnt_right++;

            sr += hist_left[x] * hist_right[x];
        }
    }

    for(int i = 1; i + 1 < sz(E); i++) {
        auto& [_, B] = E[i];
        //* work
        for(auto& b: B) {
            ll adi_left = hist_left[b];
            ll adi_right = hist_right[b];
            cnt_left -= adi_left;
            cnt_right -= adi_right;

            ll contrib = cnt_left * cnt_right - sr;
            if(hist_left[b] > 0 && hist_right[b] > 0) {
                contrib += hist_left[b] * hist_right[b];
            }

            cnt_left += adi_left;
            cnt_right += adi_right;

            response -= contrib;
        }

        //* finish
        //* add E[i] to left
        for(auto& x: B) {
            sr -= hist_left[x] * hist_right[x];

            hist_left[x]++;
            cnt_left++;

            sr += hist_left[x] * hist_right[x];
        }
        //* remove E[i + 1] from right
        for(auto& x: E[i + 1].second) {
            sr -= hist_left[x] * hist_right[x];

            hist_right[x]--;
            cnt_right--;

            sr += hist_left[x] * hist_right[x];
        }
    }

    cout << response << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

int main() {
    cin.tie(0)->sync_with_stdio(0);

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
