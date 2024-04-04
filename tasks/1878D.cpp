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

//? Template
typedef long long LL;
typedef struct item * pitem;
struct item {
    int prior, value, cnt;
    LL sum;
    bool rev;

    item(int value):prior(rng()), value(value) {
        cnt = 0;
        rev = 0;
        sum = value;
        l = r = nullptr;
    }

    pitem l, r;
};

namespace Treap {
    int cnt (pitem it) {
        return it != nullptr? it->cnt : 0;
    }
    LL sum(pitem it) {
        return it != nullptr? it->sum : 0;
    }
    void upd_cnt (pitem it) {
        if (it!=nullptr) {
            it->cnt = cnt(it->l) + cnt(it->r) + 1;
            it->sum = sum(it->l) + sum(it->r) + it->value;
        }
    }
    void push (pitem it) {
        if (it != nullptr && it->rev == true) {
            it->rev = false;
            swap (it->l, it->r);
            if (it->l)  it->l->rev ^= true;
            if (it->r)  it->r->rev ^= true;
        }
    }
    void merge (pitem & t, pitem l, pitem r) {
        push (l);
        push (r);
        if (l==nullptr || r==nullptr)
            t = (l!=nullptr) ? l : r;
        else if (l->prior > r->prior)
            merge (l->r, l->r, r),  t = l;
        else
            merge (r->l, l, r->l),  t = r;
        upd_cnt (t);
    }
    void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
        if (t==nullptr) {
            l = r = nullptr;
            return;
        }
        push(t);
        int cur_key = add + cnt(t->l);

        if (key <= cur_key)
            split (t->l, l, t->l, key, add),  r = t;
        else
            split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
        upd_cnt (t);
    }
    void reverse (pitem &t, int l, int r) {
        pitem t1, t2, t3;
        split (t, t1, t2, l);
        split (t2, t2, t3, r-l+1);
        assert(t2 != NULL);
        t2->rev ^= true;
        merge (t, t1, t2);
        merge (t, t, t3);
    }
    LL query (pitem &t, int l, int r) {
        pitem t1, t2, t3;
        split (t, t1, t2, l);
        split (t2, t2, t3, r-l+1);
        LL ans = t2->sum;
        merge (t, t1, t2);
        merge (t, t, t3);
        return ans;
    }
    void insert (pitem & t, int key, int value) {
        pitem x = new item(value);
        pitem L, R;
        split(t, L, R, key);
        merge(L, L, x);
        merge(t, L, R);
        upd_cnt(t);
    }
    int erase (pitem & t, int key) {
        assert(cnt(t) > key);
        pitem L, MID, R;
        split(t, L, MID, key);
        split(MID, MID, R, 1);
        merge(t, L, R);
        upd_cnt(t);
        int rt = MID->value;
        delete MID;
        return rt;
    }
    void output (pitem t, string &v) {
        if (t==nullptr)  return;
        push (t);
        output (t->l, v);
        v.push_back(t->value);
        output (t->r, v);
    }
    void output2 (pitem t) {
        if (t==nullptr)  return;
        push (t);
//        cout << "(";
        output2 (t->l);
        cout << (t->value) << " ";
        output2 (t->r);
//        cout << ")";
    }
}

void solve() {
    int n, k; cin >> n >> k;
    str S; cin >> S;

    vi l(k); each(x, l) cin >> x;
    vi r(k); each(x, r) cin >> x;

    int q; cin >> q;
    vi queries(q); each(x, queries) cin >> x;

    dbg(n, k);
    dbg(S);
    dbg(l);
    dbg(r);
    RAYA;
    dbg(q);
    dbg(queries);
    RAYA;

    chk(is_sorted(all(l)));
    chk(is_sorted(all(r)));


    pitem tr = nullptr;
    for(int i = 0; i < n; i++) {
        Treap::insert(tr, i, S[i]);
    }

    const int m = sz(l);
    each(x, queries) {
        RAYA;
        int idx = int(lower_bound(all(l), x) - l.begin());
        dbg(x, idx);

        if(idx == m) idx--;
        if(x < l[idx]) idx--;
        chk(0 <= idx && idx < m);

        chk(l[idx] <= x && x <= r[idx]);

        int L = min(x, r[idx] + l[idx] - x); L--;
        int R = max(x, r[idx] + l[idx] - x); R--;
        assert(L <= R);
        dbg(L, R);

        Treap::reverse(tr, L, R);
    }

    str ans;
    Treap::output(tr, ans);
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
