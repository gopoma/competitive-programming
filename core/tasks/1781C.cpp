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



// building blocks
using ll  = long long;
using db  = long double; // or double, if TL is tight
using str = string;      // yay python!

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f first
#define s second



#define tcT template <class T
#define tcTU tcT, class U
//! ^ lol this makes everything look weird but I'll try it

tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

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



// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



const int MOD = 1e9+7;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64



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
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



inline namespace FileIO {
void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void setIO(str s = "") {
	cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
	//? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);
	cin.exceptions(cin.failbit);
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) setIn(s + ".in"), setOut(s + ".out");  // for old USACO
}
}  // namespace FileIO



//? Custom Helpers
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
//? /Custom Helpers


void solve() {
    ll n; cin >> n;
    str S; cin >> S;
    dbg(n, S);

    map<char, vl> where;
    for(int i = 0; i < n; i++) {
        where[S[i]].eb(i);
    }


    map<char, ll> hist;
    for(auto& c: S) hist[c]++;



    using E = pair<ll, char>;
    vector<E> freqs;
    for(auto& [c, amount]: hist) {
        freqs.eb(amount, c);
    }
    sort(all(freqs), [&](E& xx, E& yy) {
        return xx.f > yy.f;
    });
    dbg(freqs);



    vl hists;
    for(auto& [amount, c]: freqs) hists.eb(amount);
    dbg(hists);


    vl divisors;
    {
        for(ll x = 1; x * x <= n; x++) {
            if(n % x == 0) {
                divisors.eb(x);

                if(x != n / x) divisors.eb(n / x);
            }
        }
    }
    sor(divisors);
    dbg(divisors);



    ll mx = ll('z' - 'a' + 1);
    dbg(mx);

    auto calc = [&](ll letters, ll amount) -> ll {
        vl tmp(letters, amount);

        while(sz(hists) < sz(tmp)) hists.eb(0);
        while(sz(tmp) < sz(hists)) tmp.eb(0);

        ll val = 0;

        assert(sz(tmp) == sz(hists));
        const int m = sz(tmp);
        for(int i = 0; i < m; i++) {
            val += abs(tmp[i] - hists[i]);
        }
        assert(val % 2 == 0);

        return val / 2;
    };

    ll ans_val = BIG;
    pl ans_tar = mp(BIG, BIG);
    for(auto& d: divisors) {
        ll amount_letters = d;
        ll amount_per_letter = n / d;

        if(amount_letters > mx) continue;

        dbg(amount_letters, amount_per_letter);

        if(ckmin(ans_val, calc(amount_letters, amount_per_letter))) {
            ans_tar = mp(amount_letters, amount_per_letter);
        }
    }
    assert(ans_val != BIG);
    assert(ans_tar != mp(BIG, BIG));
    dbg(ans_val);
    dbg(ans_tar);

    //? build
    vector<char> cans(n, '$');

    auto [amount_letters, amount_per_letter] = ans_tar;
    dbg(amount_letters);
    dbg(amount_per_letter);

    //? using E = pair<ll, char>;
    map<char, ll> need;
    set<ll> already;
    for(int i = 0; i < min(amount_letters, ll(sz(freqs))); i++) {
        need[freqs[i].s] = amount_per_letter;
        already.emplace(freqs[i].s);
    }
    if(amount_letters > sz(freqs)) {
        rep(amount_letters - sz(freqs)) {
            for(char c = 'a'; c <= 'z'; c++) {
                if(!already.count(c)) {
                    need[c] = amount_per_letter;

                    already.emplace(c);
                    break;
                }
            }
        }
    }
    assert(sz(need) == amount_letters);

    //? take already
    vector<char> sobra;
    for(auto& [c, amount]: need) {
        const ll m = min(amount, ll(sz(where[c])));

        rep(m) {
            cans[where[c].bk] = c;
            where[c].pop_back();
            amount--;
        }

        dbg(c, amount);

        rep(amount) {
            sobra.eb(c);
        }
    }

    //? assign
    dbg(sobra);
    for(int i = 0; i < n; i++) if(cans[i] == '$') {
        cans[i] = sobra.bk;
        sobra.pop_back();
    }

    dbg(cans);




    str ans;
    for(auto& c: cans) ans.pb(c);

    dbg(ans_val);
    cout << ans_val << "\n";
    dbg(ans);
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    cin >> t;

    for(int idx = 0; idx < t; idx++) {
        RAYA;
        RAYA;
        solve();
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
