//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
#pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

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
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()

/**
 * Description: Tests primality up to $SZ$. Runs faster if only
 	* odd indices are stored.
     * Time: O(SZ\log\log SZ) or O(SZ)
     * Source: KACTL
     * Verification: https://open.kattis.com/problems/primesieve
     */

using vi = vector<int>;
template<int SZ> struct Sieve {
    bitset<SZ> is_prime; vi primes;
    //* Sieve() {
    //* 	is_prime.set(); is_prime[0] = is_prime[1] = 0;
    //* 	for (int i = 4; i < SZ; i += 2) is_prime[i] = 0;
    //* 	for (int i = 3; i*i < SZ; i += 2) if (is_prime[i])
    //* 		for (int j = i*i; j < SZ; j += i*2) is_prime[j] = 0;
    //* 	F0R(i,SZ) if (is_prime[i]) primes.pb(i);
    //* }
    int sp[SZ]{}; // smallest prime that divides
    Sieve() { // above is faster
        FOR(i,2,SZ) {
            if (sp[i] == 0) sp[i] = i, primes.pb(i);
            for (int p: primes) {
                if (p > sp[i] || i*p >= SZ) break;
                sp[i*p] = p;
            }
        }
    }
};

Sieve<int(2e6) + 5> st;
vl C;
using i128 = __int128;
using Info = tuple<ll, ll, ll>;
void precompute() {
    V<Info> G;
    for(ll x = 2; x <= ll(1e6); x++) {
        vl factors;
        ll cur = x;
        while(cur != 1 && sz(factors) <= 2) {
            factors.emplace_back(st.sp[cur]);
            cur /= st.sp[cur];
        }
        if(sz(factors) != 2 || (factors.ft == factors.bk)) continue;
        G.emplace_back(x * x, factors.ft * factors.ft, factors.bk * factors.bk);
    }

    for(int i = 0; i < sz(G); i++) {
        auto [xx, pp, qq] = G[i];
        C.emplace_back(xx);
        if(i128(xx) * i128(pp) <= i128(1e12))
            G.emplace_back(xx * pp, pp, qq);
        if(i128(xx) * i128(qq) <= i128(1e12))
            G.emplace_back(xx * qq, pp, qq);
    }
    sort(C.begin(), C.end());
}

void solve() {
    ll A; cin >> A;
    auto it = upper_bound(C.begin(), C.end(), A);
    it--;
    cout << *it << "\n";
}

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precompute();

    ll q; cin >> q;
    while(q--) {
        solve();
        RAYA;
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
