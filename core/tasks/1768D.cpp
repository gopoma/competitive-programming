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
/**
 * Description: A set (not multiset!) with support for finding the $n$'th
   * element, and finding the index of an element. Change \texttt{null\_type} to get a map.
 * Time: O(\log N)
 * Source: KACTL
   * https://codeforces.com/blog/entry/11080
 * Verification: many
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tcT> using Tree = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
#define ook order_of_key
#define fbo find_by_order

void treeExample() {
	Tree<int> t, t2; t.insert(8);
	auto it = t.insert(10).f; assert(it == t.lb(9));
	assert(t.ook(10) == 1 && t.ook(11) == 2 && *t.fbo(0) == 8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}

/**
int atMost(Tree<pi>& T, int r) {
	return T.ook({r,MOD}); }
int getSum(Tree<pi>& T, int l, int r) {
	return atMost(T,r)-atMost(T,l-1); }
*/

long long count_inv(vl a) {
    const int n = sz(a);
    assert(n == sz(a));

    Tree<pl> st;

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        ans += ll(i - st.ook(mp(a[i], n + 79)));

        st.insert(mp(a[i], i));
    }
    return ans;
}
//? /Template

ll brute(ll n, vl p) {
    map<vl, bool> vis; vis[p] = true;
    map<vl, ll> dist; dist[p] = 0;
    deque<vl> q; q.eb(p);
    map<ll, vvl> response;
    while(!q.empty()) {
        auto cur = q.ft; q.pop_front();
        if(count_inv(cur) == 1) {
            response[dist[cur]].eb(cur);
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                vl newCur = cur;
                swap(newCur[i], newCur[j]);
                if(!vis[newCur]) {
                    vis[newCur] = true;
                    dist[newCur] = dist[cur] + 1;
                    q.eb(newCur);
                }
            }
        }
    }
    ll mn = (*response.begin()).f;
    for(auto& x: response[mn]) dbg(x, count_inv(x));
    return mn;
}

ll slv(ll n, vl p) {
    chk(*min_element(all(p)) == 0);
    chk(*max_element(all(p)) == n - 1);
    dbg(p);

    vb vis(n);

    vl id(n);
    vl ord(n);
    vl cyc;

    ll currentId = 0;
    for(ll u = 0; u < n; u++) {
        if(!vis[u]) {
            ll x = u;
            ll pos = 0;

            while(!vis[x]) {
                id[x] = currentId;
                ord[x] = pos++;
                vis[x] = true;

                x = p[x];
            }
            cyc.eb(pos);
            currentId++;
        }
    }


    ll tot = 0;
    for(auto& it: cyc) tot += (it - 1LL);
    dbg(cyc);

    ll ans = BIG;
    for(ll i = 0; i + 1 < n; i++) {
        RAYA;
        ll u = i;
        ll v = i + 1;
        dbg(u, v, tot);
        ll local_ans = BIG;
        if(id[u] == id[v]) {
            // dbg(id[u], id[v], local_ans);
            ll x = ord[u];
            ll y = ord[v];
            if(x > y) swap(x, y);
            ll mid = y - x - 1;
            ll mid2 = cyc[id[u]] - mid - 2LL;

            local_ans = tot - (cyc[id[u]] - 1LL) + (p[u] != v) + (p[v] != u) + max(0LL, mid - 1LL) + max(0LL, mid2 - 1LL);
        } else {
            if(cyc[id[u]] == cyc[id[v]] && cyc[id[u]] == 1) {
                local_ans = tot - (cyc[id[u]] - 1LL) + 1LL;
            } else {
                local_ans = tot - (cyc[id[u]] - 1LL) - (cyc[id[v]] - 1LL) + 2LL + max(0LL, cyc[id[u]] + cyc[id[v]] - 3LL);
            }
        }
        dbg(id[u], id[v], local_ans);
        ckmin(ans, local_ans);
    }
    return ans;
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl p(n); for(auto& x: p) cin >> x;
    for(auto& x: p) x--;
    dbg(n);
    dbg(p);
    ll ans = slv(n, p);
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

//    const int n = 7;
//    vl p(n); iota(all(p), 0);
//    do {
//        if(count_inv(p) == 1) {
//            dbg(count_inv(p), p);
//        }
//    } while(next_permutation(all(p)));

    //? Stress Testing
    while(0) {
        RAYA;
        ll n = rng_ll(2, 5);
        vl p(n); iota(all(p), 0);
        shuf(p);
        dbg(n);
        dbg(p);
        dbg("Brute");
        ll ans  = brute(n, p);
        dbg("/Brute");
        dbg("Greedy");
        ll greedy = slv(n, p);
        dbg("/Greedy");
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    int t = 1; cin >> t;
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
