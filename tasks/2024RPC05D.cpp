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

vector<string> tokenize(string line, string separator) {
    vector<string> tokens;
    while(true) {
        string token = line.substr(0, line.find(separator));
        tokens.emplace_back(token);

        if(line.find(separator) == string::npos) {
            break;
        }
        line = line.substr(line.find(separator) + 1, int(line.size()) - line.find(separator) + 1);
    }
    return tokens;
};

/**
 * Description: Disjoint Set Union with path compression
 	* and union by size. Add edges and test connectivity.
 	* Use for Kruskal's or Boruvka's minimum spanning tree.
 * Time: O(\alpha(N))
 * Source: CSAcademy, KACTL
 * Verification: *
 */

struct DSU {
	vi e; void init(int N) { e = vi(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};

/**tcT> T kruskal(int N, vector<pair<T,pi>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N); // edges that unite are in MST
	each(a,ed) if (D.unite(a.s.f,a.s.s)) ans += a.f;
	return ans;
}*/

void solve() {
    int N, M; cin >> N >> M;
    cin.ignore();
    str S; getline(cin, S); S.pb(' ');
    vpi updates(M); for(auto& x: updates) cin >> x.f >> x.s;

//?    vs tokens = tokenize(S, " ");
    vs tokens;
    {
        const int m = sz(S);
        str act = "";
        for(int i = 0; i < m; i++) {
            if(S[i] == ' ') {
                if(act != "") {
                    tokens.eb(act);
                }
            } else {
                act.pb(S[i]);
            }
        }
    }

    assert(sz(tokens) == 2 * N - 1);

    dbg("aft");

    //? dbg(N, M);
    //? dbg(S);
    //? dbg(tokens);
    //? dbg(updates);

    DSU dsu; dsu.init(N);

    const int m = sz(tokens);
    for(int i = 0; i < m; i++) {
        if(i % 2 == 0) { //? num
            continue;
        } else { //? token
                if(tokens[i] == "*") {
                    assert(0 <= i - 1);
                    assert(i + 1 < m);

                    ll pL = (i - 1) / 2;
                    ll pR = (i + 1) / 2;

                    assert(0 <= pL && pL < N);
                    assert(0 <= pR && pR < N);

                    dsu.unite(pL, pR);
                }
        }
    }

    map<ll, pl> groups;
    unordered_set<ll> leaders; for(int i = 0; i < N; i++) leaders.emplace(dsu.get(i));
    for(auto& x: leaders) groups[x] = mp(0, 0);

    //? .f -> evens
    //? .s -> odds
    for(int i = 0; i < N; i++) {
        ll val = stoll(tokens[2 * i]);

        ll leader = dsu.get(i);
        pl preg = groups[leader];
        pl nreg = mp(preg.f + (val % 2 == 0), preg.s + (val % 2 == 1));

        groups[leader] = nreg;
    }



    ll global_evens = 0;
    ll global_odds = 0;

    auto get = [&]() -> str {
        if(global_odds % 2 == 0) return "even";
        else return "odd";
    };



    for(auto& [leader, parity]: groups) {
        ll evens = parity.f;
        ll odds = parity.s;

        //? dbg(leader, parity);

        if(odds == 0 || (odds > 0 && evens > 0)) global_evens++;
        else global_odds++;
    }



    //? dbg(global_evens, global_odds);
    cout << get() << "\n";



    vl nums(N);
    for(int i = 0; i < N; i++) nums[i] = stoll(tokens[2*i]);
    for(auto& [idx, val]: updates) {
        idx--;

        //? dbg(nums, idx, val);

        ll leader = dsu.get(idx);
        pl preg = groups[leader];
        bool podd = (preg.s > 0 && preg.f == 0);


        pl nreg = mp(-79, -79);
        if(val % 2 == 0) {
            if(nums[idx] % 2 == 0) nreg = preg;
            else nreg = mp(preg.f + 1, preg.s - 1);
        } else {
            if(nums[idx] % 2 == 1) nreg = preg;
            else nreg = mp(preg.f - 1, preg.s + 1);
        }
        nums[idx] = val;
        assert(nreg != mp(-79LL, -79LL));

        bool nodd = (nreg.s > 0 && nreg.f == 0);


        groups[leader] = nreg;

        if(podd == nodd) {}
        else if(!podd && nodd) {
            global_evens--;
            global_odds++;
        } else if(podd && !nodd) {
            global_odds--;
            global_evens++;
        }
        //? dbg(idx, val, preg, nreg, global_evens, global_odds);

        cout << get() << "\n";
    }
}

int main() {
    //? setIn("D.in");
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    //? cin >> t;

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
