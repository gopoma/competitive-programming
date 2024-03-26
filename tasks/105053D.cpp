//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debugICPC.h"

#define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define chk(...)
#define RAYA
#endif

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}



using ll = long long;
using db = long double; // or double if tight TL
using str = string;

using pi = pair<int,int>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vb = V<bool>;
using vpi = V<pi>;

// vectors
// oops size(x), rbegin(x), rend(x) need C++17
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

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

//? Template
//? /Template

vector<ll> get_divisors(ll num) {
    vector<ll> divisors;
    for(ll x = 1LL; x * x <= num; x++) {
        if(num % x == 0) {
            divisors.eb(x);

            if(x != num / x) divisors.eb(num / x);
        }
    }
    sor(divisors);

    return divisors;
}

map<ll, ll> get_factors(ll N) {
    map<ll, ll> factors;
    for(ll x = 2LL; x * x <= N; x++) {
        while(N % x == 0) {
            factors[x]++;

            N /= x;
        }
    }
    if(N > 1) factors[N]++;
    return factors;
}

bool isPerfectSquare(long double x) {
    if (x >= 0) {
        long long sr = sqrt(x);

        return (sr * sr == x);
    }
    return false;
}


void brute() {
    for(ll num = 1; num <= 100; num++) {
        vector<ll> divisors = get_divisors(num);

        map<ll, ll> xd= get_factors(num);
        dbg(num, divisors, xd);
    }
}

void solve() {
    //? brute();
    ll N; cin >> N;

    if(isPerfectSquare(N)) {
        cout << "N\n";
        return;
    }

    map<ll, ll> factors = get_factors(N);
    if(sz(factors) == 1) {
        cout << "Y\n";
    } else {
        if(sz(factors) == 2) {
            bool ok = true;
            for(auto& [val, cnt]: factors) {
                ok &= (cnt == 1);
            }
            if(ok) cout << "Y\n";
            else cout << "N\n";
        } else cout << "N\n";
    }

    if(false) {
        vector<ll> divisors = get_divisors(N);

        dbg(N);
        each(d, divisors) {
            auto xd = get_factors(d);
            vector<ll> tmp; each(x, xd) rep(x.s) tmp.eb(x.f);
            dbg(d, tmp);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    //? cin >> t;

    for(int idx = 0; idx < t; idx++) {
        solve();
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
