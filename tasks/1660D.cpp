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
    int n; cin >> n;
    vl a(n); each(x, a) cin >> x;

    dbg(n);
    dbg(a);

    vector<pair<vl, pair<ll, ll>>> windows;
    {
        vl act;
        int L = 0;
        int R = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] == 0) {
                if(act.empty()) continue;

                windows.eb(mp(act, mp(L, R)));

                act.clear();
            } else {
                if(act.empty()) {
                    L = i;
                    R = i;
                } else R++;

                act.eb(a[i]);
            }
        }

        if(!act.empty()) {
            windows.eb(mp(act, mp(L, R)));
        }
    }

    dbg(windows);

    //? amount of twos
    //? # to delete from front
    //? # to delete form back

    using E = tuple<ll, ll, ll>;
    E ans = make_tuple(0, -1, -1);

    for(auto& tmp: windows) {
        vl window = tmp.f;
        ll L = tmp.s.f;
        ll R = tmp.s.s;

        dbg(window, L, R);

        ll negs = 0;
        for(auto& x: window) {
            assert(x != 0);
            negs += (x < 0);
        }

        if(negs % 2 == 0) {
            //? take all
            ll twos = 0;
            for(auto& x: window) twos += (ll(abs(x)) == 2LL);

            ckmax(ans, make_tuple(twos, L, R));
        } else {
            //? careful

            auto get = [&](vl& arr) {
                ll twos = 0;
                ll act_negs = 0;
                each(x, arr) {
                    if(x < 0) {
                        act_negs++;
                    }
                    assert(act_negs <= negs);
                    if(act_negs == negs) break;

                    twos += (ll(abs(x)) == 2LL);
                }
                return twos;
            };

            ll from_front = get(window);
            reverse(all(window));
            ll from_back = get(window);

            if(from_front >= from_back) {
                //? select from front
                ll R_act = L;
                ll act_negs = 0;
                for(; R_act <= R; R_act++) {
                    if(a[R_act] < 0) act_negs++;
                    if(act_negs == negs) {
                        R_act--;
                        break;
                    }
                }

                ckmax(ans, make_tuple(from_front, L, R_act));
            } else {
                //? select from back
                ll L_act = R;
                ll act_negs = 0;
                for(; L_act >= L; L_act--) {
                    if(a[L_act] < 0) act_negs++;
                    if(act_negs == negs) {
                        L_act++;
                        break;
                    }
                }

                ckmax(ans, make_tuple(from_back, L_act, R));
            }
        }
    }

    {
        dbg(ans);
        ll L = get<1>(ans);
        ll R = get<2>(ans);

        ll needF = L - 0;
        ll needB = (n - 1) - R;
        if(L == -1) {
            assert(R == -1);

            needF = n;
            needB = 0;
        }
        dbg(needF, needB);
        cout << needF << " " << needB << "\n";
    }
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
