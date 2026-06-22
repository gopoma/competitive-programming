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



//? Template
const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



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

tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}
//? /Template

using E = tuple<ll, ll, ll>;
//? left - right - parent
void solve() {
    str S; cin >> S;
    const int N = sz(S);

    V<E> info(2 * N + 1, make_tuple(0, 0, 0));
    
    set<int> notAlready;
    for(int u = 1; u <= 2 * N; u++) notAlready.emplace(u);
    safeErase(notAlready, 1);

    int cur = 1;
    int topNode = 1;
    each(c, S) {
        auto nxt = *notAlready.begin();

        auto [parent, left, right] = info[cur];
        auto [parentNxt, leftNxt, rightNxt] = info[nxt];
        chk(parentNxt == 0 && leftNxt == 0 && rightNxt == 0);

        if(c == 'L') {
            if(left == 0) {
                info[cur] = make_tuple(parent, nxt, right);
                info[nxt] = make_tuple(cur, leftNxt, rightNxt);
                safeErase(notAlready, nxt);
            } else {
                cur = left;
            }
        } else if(c == 'R') {
            if(right == 0) {
                info[cur] = make_tuple(parent, left, nxt);
                info[nxt] = make_tuple(cur, leftNxt, rightNxt);
                safeErase(notAlready, nxt);
            } else {
                cur = right;
            }
        } else {
            assert(c == 'U');
            if(parent == 0) {
                topNode = nxt;
                info[cur] = make_tuple(nxt, left, right);
                info[nxt] = make_tuple(parentNxt, cur, rightNxt);
                safeErase(notAlready, nxt);
            } else {
                cur = parent;
            }
        }
    }

    {
        auto nxt = *notAlready.begin();
        auto [parent, left, right] = info[topNode];
        auto [parentNxt, leftNxt, rightNxt] = info[nxt];

        chk(parent == 0);
        chk(parentNxt == 0 && leftNxt == 0 && rightNxt == 0);

        info[topNode] = make_tuple(nxt, left, right);
        info[nxt] = make_tuple(parentNxt, topNode, rightNxt);

        safeErase(notAlready, nxt);
        topNode = nxt;
    }

    int C = topNode;
    while(!notAlready.empty()) {
        auto nxt = *notAlready.begin();
        safeErase(notAlready, nxt);

        auto [parent, left, right] = info[C];
        auto [parentNxt, leftNxt, rightNxt] = info[nxt];
        
        chk(right == 0);
        chk(parentNxt == 0 && leftNxt == 0 && rightNxt == 0);

        info[C] = make_tuple(parent, left, nxt);
        info[nxt] = make_tuple(C, leftNxt, rightNxt);
        C = nxt;
    }

    const int amountNodes = 2 * N;
    const int A = 1;
    const int B = C;
    cout << amountNodes << " " << A << " " << B << "\n";
    vpi edges;
    for(int i = 1; i <= 2 * N; i++) {
        auto [parent, left, right] = info[i];
        if(left != 0)
            edges.eb(i, left);
        if(right != 0)
            edges.eb(i, right);
        cout << left << " " << right << "\n";
    }
    //? dbg("xd");
    //? for(auto& [u, v]: edges) cout << u << " " << v << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

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
