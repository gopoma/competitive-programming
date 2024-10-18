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
tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

struct AngelBeats {
    using i64 = long long;
    static constexpr i64 INF = numeric_limits<i64>::max() / 2.1;

    struct alignas(32) Node {
        i64 sum = 0, g1 = 0, l1 = 0;
        i64 g2 = -INF, gc = 1, l2 = INF, lc = 1, add = 0;
    };

    vector<Node> v;
    i64 n, log;

    AngelBeats() {}
    AngelBeats(int _n) : AngelBeats(vector<i64>(_n)) {}
    AngelBeats(const vector<i64> &vc) {
        n = 1, log = 0;
        while(n < (int)vc.size()) n <<= 1, log++;
        v.resize(2 * n);
        for(i64 i = 0; i < (int)vc.size(); ++i) { v[i + n].sum = v[i + n].g1 = v[i + n].l1 = vc[i]; }
        for(i64 i = n - 1; i; --i) update(i);
    }

    void range_chmin(int l, int r, i64 x) { inner_apply<1>(l, r, x); }
    void range_chmax(int l, int r, i64 x) { inner_apply<2>(l, r, x); }
    void range_add(int l, int r, i64 x) { inner_apply<3>(l, r, x); }
    void range_update(int l, int r, i64 x) { inner_apply<4>(l, r, x); }
    i64 range_min(int l, int r) { return inner_fold<1>(l, r); }
    i64 range_max(int l, int r) { return inner_fold<2>(l, r); }
    i64 range_sum(int l, int r) { return inner_fold<3>(l, r); }

  private:
    void update(int k) {
        Node &p = v[k];
        Node &l = v[k * 2 + 0];
        Node &r = v[k * 2 + 1];

        p.sum = l.sum + r.sum;

        if(l.g1 == r.g1) {
            p.g1 = l.g1;
            p.g2 = max(l.g2, r.g2);
            p.gc = l.gc + r.gc;
        } else {
            bool f = l.g1 > r.g1;
            p.g1 = f ? l.g1 : r.g1;
            p.gc = f ? l.gc : r.gc;
            p.g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
        }

        if(l.l1 == r.l1) {
            p.l1 = l.l1;
            p.l2 = min(l.l2, r.l2);
            p.lc = l.lc + r.lc;
        } else {
            bool f = l.l1 < r.l1;
            p.l1 = f ? l.l1 : r.l1;
            p.lc = f ? l.lc : r.lc;
            p.l2 = min(f ? r.l1 : l.l1, f ? l.l2 : r.l2);
        }
    }

    void push_add(int k, i64 x) {
        Node &p = v[k];
        p.sum += x << (log + __builtin_clz(k) - 31);
        p.g1 += x;
        p.l1 += x;
        if(p.g2 != -INF) p.g2 += x;
        if(p.l2 != INF) p.l2 += x;
        p.add += x;
    }
    void push_min(int k, i64 x) {
        Node &p = v[k];
        p.sum += (x - p.g1) * p.gc;
        if(p.l1 == p.g1) p.l1 = x;
        if(p.l2 == p.g1) p.l2 = x;
        p.g1 = x;
    }
    void push_max(int k, i64 x) {
        Node &p = v[k];
        p.sum += (x - p.l1) * p.lc;
        if(p.g1 == p.l1) p.g1 = x;
        if(p.g2 == p.l1) p.g2 = x;
        p.l1 = x;
    }
    void push(int k) {
        Node &p = v[k];
        if(p.add != 0) {
            push_add(k * 2 + 0, p.add);
            push_add(k * 2 + 1, p.add);
            p.add = 0;
        }
        if(p.g1 < v[k * 2 + 0].g1) push_min(k * 2 + 0, p.g1);
        if(p.l1 > v[k * 2 + 0].l1) push_max(k * 2 + 0, p.l1);

        if(p.g1 < v[k * 2 + 1].g1) push_min(k * 2 + 1, p.g1);
        if(p.l1 > v[k * 2 + 1].l1) push_max(k * 2 + 1, p.l1);
    }

    void subtree_chmin(int k, i64 x) {
        if(v[k].g1 <= x) return;
        if(v[k].g2 < x) {
            push_min(k, x);
            return;
        }
        push(k);
        subtree_chmin(k * 2 + 0, x);
        subtree_chmin(k * 2 + 1, x);
        update(k);
    }

    void subtree_chmax(int k, i64 x) {
        if(x <= v[k].l1) return;
        if(x < v[k].l2) {
            push_max(k, x);
            return;
        }
        push(k);
        subtree_chmax(k * 2 + 0, x);
        subtree_chmax(k * 2 + 1, x);
        update(k);
    }

    template <int cmd> inline void _apply(int k, i64 x) {
        if constexpr(cmd == 1) subtree_chmin(k, x);
        if constexpr(cmd == 2) subtree_chmax(k, x);
        if constexpr(cmd == 3) push_add(k, x);
        if constexpr(cmd == 4) subtree_chmin(k, x), subtree_chmax(k, x);
    }

    template <int cmd> void inner_apply(int l, int r, i64 x) {
        if(l == r) return;
        l += n, r += n;
        for(int i = log; i >= 1; i--) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while(l < r) {
                if(l & 1) _apply<cmd>(l++, x);
                if(r & 1) _apply<cmd>(--r, x);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for(int i = 1; i <= log; i++) {
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <int cmd> inline i64 e() {
        if constexpr(cmd == 1) return INF;
        if constexpr(cmd == 2) return -INF;
        return 0;
    }

    template <int cmd> inline void op(i64 &a, const Node &b) {
        if constexpr(cmd == 1) a = min(a, b.l1);
        if constexpr(cmd == 2) a = max(a, b.g1);
        if constexpr(cmd == 3) a += b.sum;
    }

    template <int cmd> i64 inner_fold(int l, int r) {
        if(l == r) return e<cmd>();
        l += n, r += n;
        for(int i = log; i >= 1; i--) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        i64 lx = e<cmd>(), rx = e<cmd>();
        while(l < r) {
            if(l & 1) op<cmd>(lx, v[l++]);
            if(r & 1) op<cmd>(rx, v[--r]);
            l >>= 1;
            r >>= 1;
        }
        if constexpr(cmd == 1) lx = min(lx, rx);
        if constexpr(cmd == 2) lx = max(lx, rx);
        if constexpr(cmd == 3) lx += rx;
        return lx;
    }
};

/**
 * @brief Range Chmin Chmax Add Update Range Min Max Sum Segment Tree Beats!
 * @docs docs/segment-tree/segment-tree-beats.md
 */
//? /Template

const ll BIG = ll(1e18);
ll brute(ll n, vl a) {
    //? <>
    chk(n >= 3);
    ll ans = -BIG;
    for(int L = 0; L < n; L++) {
        for(int R = L; R < n; R++) {
            if((R - L + 1) >= 3) {
                vl current;
                for(int k = L; k <= R; k++) current.eb(a[k]);
                ll cVal = current.bk;
                sort(rall(current));
                bool good = !(current[0] > cVal && current[1] > cVal && current[2] > cVal);
                if(!good) continue;

                ll local_ans = current[0] + current[1] + current[2] - (R - L); 
                ckmax(ans, local_ans);
            }
        }
    }
//?    for(int L = 0; L < n; L++) for(int R = L; R < n; R++) {
//?        if((R - L + 1) >= 3) {
//?            vl current;
//?            for(int k = L; k <= R; k++) current.eb(a[k]);
//?            vl backup = current;
//?            sort(rall(current));
//?            ll local_ans = current[0] + current[1] + current[2] - (R - L); 
//?            if(local_ans == ans) dbg(backup);
//?        }
//?    }
    return ans;
}

ll slv(ll n, vl a) {
    vl aGuarda = a;
    a[0] -= 1;
    for(int i = 1; i < n; i++) {
        a[i] -= (i - 1);
    }
    AngelBeats seg(a);
    ll ans = -BIG;
    for(int middle = 1; middle + 1 < n; middle++) {
        ckmax(ans, seg.range_max(0, middle) + seg.range_max(middle + 1, n) + aGuarda[middle]);
        seg.range_add(0, middle + 1, -1);
        seg.range_add(middle + 1, n, +1);
    }
    return ans;
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl a(n); each(x, a) cin >> x;
    dbg(n);
    dbg(a);
    ll ans = slv(n, a);
    dbg(ans);
    cout << ans << "\n";
}


//? Generator
mt19937 rng(0);
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

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
