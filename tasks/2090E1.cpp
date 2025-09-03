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

ll brute(ll n, ll k, vl a, vl b) {
    auto check = [&]() -> bool {
        ll mn = *min_element(all(a));
        ll mx = *max_element(all(a));
        return (mn == 0 && mn == mx);
    };


    ll re = 0;
    while(!check()) {
        // dbg(a);
        // dbg(b);
        // dbg(re);
        re++;

        for(int i = 0; i < n; i++) {
            ll t = min(a[i], b[i]);
            a[i] -= t;
            b[i] -= t;
        }

        deque<ll> c;
        for(auto& x: a) c.emplace_back(x);
        c.emplace_front(c.back());
        c.pop_back();

        vl nxt;
        for(auto& x: c) nxt.emplace_back(x);

        a = nxt;
    }
    // dbg(a);
    // dbg(b);
    return re;
}

ll slv(ll n, ll k, vl a, vl b) {
    set<ll> A, B;
    for(int i = 0; i < n; i++) {
        A.emplace(i);
        B.emplace(i);
    }

    vl dp(n, -BIG);
    vl todo;
    while(!A.empty()) {
       // dbg(A, B);
       // dbg(a, b);

        auto itb = B.lower_bound(*A.begin());
        if(itb == B.end()) {
            itb = B.begin();
        }
        for(; itb != B.end(); itb++) {
            if(A.empty()) break;

            auto it = A.upper_bound(*itb);

            ll x = *itb;

            ll id = -1;
            ll dist = -1;

            if(it == A.begin()) {
                id = *A.rbegin();

                dist = ((n - 1) - id) + 1 + (x);
            } else {
                it--;
                id = *it;

                dist = (x - id);
            }

            assert(id != -1);
            assert(dist >= 0);

            assert(a[id] > 0);
            assert(b[x] > 0);

           // dbg(id, x, dist + 1);

            ll t = min(a[id], b[x]);
            a[id] -= t;
            b[x] -= t;

            if(a[id] == 0) {
                A.erase(id);
                dp[id] = max(dp[id], dist + 1);
            }
            if(b[x] == 0) {
                todo.emplace_back(x);
            }

            break;
        }
        for(auto& x: todo) {
            B.erase(x);
        }
        todo.clear();
    }
   // dbg(a, b);

   // dbg(dp);

    return *max_element(all(dp));
}

void solve() {
    ll n, k; cin >> n >> k;
    vl a(n), b(n);
    for(auto& x: a) cin >> x;
    for(auto& x: b) cin >> x;

    dbg(n, k);
    dbg(a);
    dbg(b);

    ll re = slv(n, k, a, b);
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
        ll n = rng_ll(1, ll(2e5));
        ll k = 0;
        vl a(n), b(n);
        for(auto& x: a) x = rng_ll(1, 10);
        for(auto& x: b) x = rng_ll(1, 10);

        ll sa = accumulate(all(a), 0LL);
        ll sb = accumulate(all(b), 0LL);
        if(sa > sb) {
            ll d = sa - sb;
            b[rng_ll(0, n - 1)] += d;
        }
        sa = accumulate(all(a), 0LL);
        sb = accumulate(all(b), 0LL);
        assert(sa <= sb);

        dbg(n);
        db st = time_elapsed();
        ll ans = slv(n, k, a, b);
        db nd = time_elapsed();
        db taken = nd - st;

        dbg(ans);
        dbg(taken);
        if(taken > db(2)) {
            assert(false);
        }
    }

    while(0) {
        RAYA;
        RAYA;
        ll n = rng_ll(1, 20);
        ll k = 0;
        vl a(n), b(n);
        while(1) {
            for(auto& x: a) x = rng_ll(1, 10);
            for(auto& x: b) x = rng_ll(1, 10);
            ll sa = accumulate(all(a), 0LL);
            ll sb = accumulate(all(b), 0LL);
            if(sa <= sb) break;
        }
        dbg(n);
        dbg(a);
        dbg(b);

        dbg("Brute");
        ll ans = brute(n, k, a, b);
        dbg("/Brute");
        ll gre = slv(n, k, a, b);
        dbg(ans, gre);
        assert(ans == gre);
    }

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
