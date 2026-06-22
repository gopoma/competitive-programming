//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
#pragma GCC optimize ("trapv")

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

ll F(ll x) {
    return (x * (x + 1LL)) / 2LL;
}

ll F(ll x, ll y) {
    return F(y) - F(x - 1);
}

vl tot_nums, tot_digits, start, sum;
ll MX;
void precompute() {
    tot_nums.emplace_back(0);
    tot_digits.emplace_back(0);
    start.emplace_back(0);
    sum.emplace_back(0);

    ll p10 = 1LL;
    for(ll d = 1; ; d++) {
        ll tn = 9LL * p10;
        ll td = d * 9LL * p10;

        tot_nums.emplace_back(tn);
        tot_digits.emplace_back(td);
        start.emplace_back(p10);
        sum.emplace_back(0);

        if(td > ll(1e16)) break;

        p10 *= 10LL;
    }


    MX = sz(tot_nums);

    sum[1] = F(1, 9);
    ll S = sum[1];
    for(ll d = 2; d < MX; d++) {
        sum[d] = 9LL * S + start[d] * F(1, 9);
        S += sum[d];
    }


    for(int d = 1; d < MX; d++) {
        dbg(d, tot_nums[d], tot_digits[d], start[d], sum[d]);
    }
}


ll work(ll R) {
    if(R == 0) return 0;
    if(R == 1) return 1;

    ll re = 0;

    R++;
    ll p10 = 10;
    for(ll d = 1; d < MX; d++) {
        ll blocks = R / p10;
        dbg(d, blocks);

        vector<ll> contrib(10);
        for(ll i = 0; i < 10; i++) {
            contrib[i] += i * blocks * (p10 / 10LL);
        }

        ll rem = R % p10;
        ll aux = p10 / 10LL;
        dbg(rem, aux);
        for(ll i = 0; i < 10; i++) {
            if(rem < aux) {
                contrib[i] += i * rem;
                break;
            } else {
                contrib[i] += i * aux;
                rem -= aux;
            }
        }


        for(ll i = 0; i < 10; i++) {
            re += contrib[i];
        }

        p10 *= 10LL;
    }
    dbg(re);
    return re;
}

ll work(ll L, ll R) {
    return work(R) - work(L - 1);
}

void solve() {
    ll k; cin >> k;


    ll re = 0;

    ll d = 1;
    for(; d < MX; d++) {
        if(k - tot_digits[d] >= 0) {
            k -= tot_digits[d];
            re += sum[d];
        } else {
            break;
        }
    }
    dbg(d);


    ll left = 0; // always good
    ll right = ll(1e17); // always bad
    while(left + 1 < right) {
        ll middle = (left + right) >> 1LL;
        if(k - d * middle >= 0) left = middle;
        else right = middle;
    }
    k -= d * left;
    ll current_number = start[d] + left;
    dbg(k, current_number);

    // should add sum of digits of numbers [start[d], ..., start[d] + left - 1]
    if(left != 0) {
        dbg(start[d], start[d] + left - 1);
        ll contrib = work(start[d], start[d] + left - 1);
        dbg(contrib);
        re += contrib;
    }

    // should add first k digits of current_number
    for(int i = 0; i < k; i++) {
        re += ll(to_string(current_number)[i] - '0');
    }

    dbg(re);
    cout << re << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int t; cin >> t;
    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        solve();
    }

    return 0;
}
