//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

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
#define f  first
#define s  second



#define tcT template <class T
#define tcTU tcT, class U

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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



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

#define lb lower_bound
#define ub upper_bound



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



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

//? __builtin_popcountll
ll GetBit(ll mask, ll bit) { return (mask >> bit) & 1LL; }
void TurnOn(ll& mask, ll bit) { mask = mask | (1LL << bit); }
void TurnOff(ll& mask, ll bit) { mask = mask & (~(1LL << bit)); }

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0);

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? https://cs.stackexchange.com/questions/88528/is-it-possible-to-make-data-structure-that-will-find-mex-and-support-modificatio
class MEX {
  struct MEXNode {
    MEXNode *children[2];
    bool is_full = false;
    int cnt = 0;

  public:
    MEXNode() {
      children[0] = nullptr;
      children[1] = nullptr;
    }
  };
private:

  inline MEXNode *nonnull(MEXNode *& n) {
    if (!n) n = new MEXNode();
    return n;
  }

  void insert(int val, int level, MEXNode *n) {
    if (level == -1) {
      n->cnt++;
      n->is_full = true;
      return;
    }

    int cur_bit = (val & (1 << level)) >> level;
    insert(val, level - 1, nonnull(n->children[cur_bit]));

    n->is_full = nonnull(n->children[0])->is_full && nonnull(n->children[1])->is_full;
    n->cnt = nonnull(n->children[0])->cnt + nonnull(n->children[1])->cnt;
  }

  // Remove an integer from the set
  void remove(int val, int level, MEXNode *n) {
    if (level == -1) {
      n->cnt--;
      n->is_full = n->cnt > 0;
      return;
    }

    int cur_bit = (val & (1 << level)) >> level;
    remove(val, level - 1, nonnull(n->children[cur_bit]));

    n->is_full = nonnull(n->children[0])->is_full && nonnull(n->children[1])->is_full;
    n->cnt = nonnull(n->children[0])->cnt + nonnull(n->children[1])->cnt;
  }

  // Find the minimum element >=x that isn't present in the set
  int get(int val, int level, MEXNode *n) {
    if (n->is_full) {
      return -1;
    } else if (n->cnt == 0) {
      return val;
    }

    int cur_bit = (val & (1 << level)) >> level;
    int ans = get(val, level - 1, nonnull(n->children[cur_bit]));
    if (cur_bit == 0 && ans == -1) {
      ans = get((val >> level << level) | (1 << level), level - 1, nonnull(n->children[1]));
    }

    return ans;
  }

  MEXNode root_node;
public:

  void insert(int x) {
    insert(x, 31, &root_node);
  }
  void remove(int x) {
    remove(x, 31, &root_node);
  }
  int get(int x) {
    return get(x, 31, &root_node);
  }
};

//? /Template

ll brute(ll n, vl p, vl q) {
    ll ans = 0;
    map<ll, vpl> hist;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            MEX st_p, st_q;
            for(int k = i; k <= j; k++) {
                st_p.insert(p[k]);
                st_q.insert(q[k]);
            }
            if(st_p.get(1) == st_q.get(1)) {
                hist[st_p.get(1)].eb(i, j);
                ans++;
            }
        }
    }
    // for(auto& [mex, it]: hist) {
    //     dbg(mex);
    //     dbg(it);
    //     dbg(sz(it));
    // }
    return ans;
}

ll slv(ll n, vl p, vl q) {
    auto get = [&](vl& arr) -> map<ll, ll> {
        map<ll, ll> where;
        for(int i = 0; i < n; i++) where[arr[i]] = i;
        return where;
    };
    map<ll, ll> where_p = get(p);
    map<ll, ll> where_q = get(q);

    ll ans = 0;
    ll L = where_p[1];
    ll R = where_q[1];
    if(L > R) swap(L, R);
    {
        auto add = [&](ll d) -> void {
            ans += fdiv(d * (d + 1LL), 2LL);
        };
        add(abs((L - 1) - (-1)));
        add(abs((R - L)) - 1LL);
        add(abs((n) - (R + 1LL)));
    }

    auto inter = [](ll l, ll r, ll l2, ll r2) -> bool {
        if(l > l2) {
            swap(l, l2);
            swap(r, r2);
        }
        return (l2 <= r);
    };

    // dbg(ans);
    for(ll mex = 2; mex <= n; mex++) {
        ll L2 = where_p[mex];
        ll R2 = where_q[mex];
        if(L2 > R2) swap(L2, R2);

        ll contrib = 0;
        if(!inter(L, R, L2, R2)) {
            if(R2 < L) {
                ll d1 = abs(L - R2) - 1LL;
                ll d2 = abs(n - R) - 1LL;
                contrib += (d1 + 1LL) * (d2 + 1LL);
            } else {
                chk(R < L2);
                ll d1 = abs(L - (-1)) - 1LL;
                ll d2 = abs(L2 - R) - 1LL;
                contrib += (d1 + 1LL) * (d2 + 1LL);
            }
            // dbg(mex, contrib);
        } else if(L2 < L && R < R2) {
            ll d1 = abs(L - L2) - 1LL;
            ll d2 = abs(R2 - R) - 1LL;
            contrib += (d1 + 1LL) * (d2 + 1LL);
        }
        ans += contrib;
        ll newL = min(L, L2);
        ll newR = max(R, R2);
        L = newL;
        R = newR;
    }
    ans++;
    return ans;
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl p(n), q(n);
    for(auto& x: p) cin >> x;
    for(auto& x: q) cin >> x;
    dbg(n);
    dbg(p);
    dbg(q);
    ll ans = slv(n, p, q);
    dbg(ans);
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        ll n = rng_ll(1, 100);
        vl p(n), q(n);
        iota(all(p), 1);
        iota(all(q), 1);
        shuf(p);
        shuf(q);
        dbg(n);
        dbg(p);
        dbg(q);
        ll ans = brute(n, p, q);
        ll greedy = slv(n, p, q);
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    int t = 1; //! cin >> t;
    for(int i = 0; i < t; i++) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
