#pragma region Macros
// #pragma GCC target("avx2")
#pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define rep2(i, a, b) for(ll i = a; i <= b; ++i)
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define rep3(i, a, b) for(ll i = a; i >= b; --i)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define vll vector<ll>
#define vpi vector<pii>
#define vpll vector<pll>
#define overload2(_1, _2, name, ...) name
#define vec(type, name, ...) vector<type> name(__VA_ARGS__)
#define VEC(type, name, size)                                                                                                                                  \
    vector<type> name(size);                                                                                                                                   \
    IN(name)
#define vv(type, name, h, ...) vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define VV(type, name, h, w)                                                                                                                                   \
    vector<vector<type>> name(h, vector<type>(w));                                                                                                             \
    IN(name)
#define vvv(type, name, h, w, ...) vector<vector<vector<type>>> name(h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...)                                                                                                                         \
    vector<vector<vector<vector<type>>>> name(a, vector<vector<vector<type>>>(b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))
#define mt make_tuple

#define fi first
#define se second
#define all(c) begin(c), end(c)
#define SUM(v) accumulate(all(v), 0LL)
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define lb(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define ub(c, x) distance((c).begin(), upper_bound(all(c), (x)))
using namespace std;
constexpr pii dx4[4] = {pii{1, 0}, pii{0, 1}, pii{-1, 0}, pii{0, -1}};
constexpr pii dx8[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
const string YESNO[2] = {"NO", "YES"};
const string YesNo[2] = {"No", "Yes"};
const string yesno[2] = {"no", "yes"};
void YES(bool t = 1) { cout << YESNO[t] << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << YesNo[t] << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << yesno[t] << endl; }
void no(bool t = 1) { yes(!t); }
template <class T> using vc = vector<T>;
template <class T> using vvc = vector<vc<T>>;
template <class T> using vvvc = vector<vvc<T>>;
template <class T> using vvvvc = vector<vvvc<T>>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
#define si(c) (int)(c).size()
#define INT(...)                                                                                                                                               \
    int __VA_ARGS__;                                                                                                                                           \
    IN(__VA_ARGS__)
#define LL(...)                                                                                                                                                \
    ll __VA_ARGS__;                                                                                                                                            \
    IN(__VA_ARGS__)
#define STR(...)                                                                                                                                               \
    string __VA_ARGS__;                                                                                                                                        \
    IN(__VA_ARGS__)
#define CHR(...)                                                                                                                                               \
    char __VA_ARGS__;                                                                                                                                          \
    IN(__VA_ARGS__)
#define DBL(...)                                                                                                                                               \
    double __VA_ARGS__;                                                                                                                                        \
    IN(__VA_ARGS__)
int scan() { return getchar(); }
void scan(int &a) { cin >> a; }
void scan(long long &a) { cin >> a; }
void scan(char &a) { cin >> a; }
void scan(double &a) { cin >> a; }
void scan(string &a) { cin >> a; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &);
template <class T> void scan(vector<T> &a) {
    for(auto &i : a) scan(i);
}
template <class T> void scan(T &a) { cin >> a; }
void IN() {}
template <class Head, class... Tail> void IN(Head &head, Tail &...tail) {
    scan(head);
    IN(tail...);
}
template <class T, class S> inline bool chmax(T &a, const S &b) { return (a < b ? a = b, 1 : 0); }
template <class T, class S> inline bool chmin(T &a, const S &b) { return (a > b ? a = b, 1 : 0); }
vi iota(int n) {
    vi a(n);
    iota(all(a), 0);
    return a;
}
template <typename T> vi iota(vector<T> &a, bool greater = false) {
    vi res(a.size());
    iota(all(res), 0);
    sort(all(res), [&](int i, int j) {
        if(greater) return a[i] > a[j];
        return a[i] < a[j];
    });
    return res;
}
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end())

template <class T> T ceil(T x, T y) {
    assert(y >= 1);
    return (x > 0 ? (x + y - 1) / y : x / y);
}

template <class T> T floor(T x, T y) {
    assert(y >= 1);
    return (x > 0 ? x / y : (x + y - 1) / y);
}
template <class T> T POW(T x, int n) {
    T res = 1;
    for(; n; n >>= 1, x *= x)
        if(n & 1) res *= x;
    return res;
}
template <class T> T POW(T x, ll n, const ll &mod) {
    T res = 1;
    for(; n; n >>= 1, x = x * x % mod)
        if(n & 1) res = res * x % mod;
    return res;
}
vector<pll> factor(ll x) {
    vector<pll> ans;
    for(ll i = 2; i * i <= x; i++)
        if(x % i == 0) {
            ans.push_back({i, 1});
            while((x /= i) % i == 0) ans.back().second++;
        }
    if(x != 1) ans.push_back({x, 1});
    return ans;
}
template <class T> vector<T> divisor(T x) {
    vector<T> ans;
    for(T i = 1; i * i <= x; i++)
        if(x % i == 0) {
            ans.pb(i);
            if(i * i != x) ans.pb(x / i);
        }
    return ans;
}
template <typename T> void zip(vector<T> &x) {
    vector<T> y = x;
    sort(all(y));
    for(int i = 0; i < x.size(); ++i) { x[i] = lb(y, x[i]); }
}
template <class S> void fold_in(vector<S> &v) {}
template <typename Head, typename... Tail, class S> void fold_in(vector<S> &v, Head &&a, Tail &&...tail) {
    for(auto e : a) v.emplace_back(e);
    fold_in(v, tail...);
}
template <class S> void renumber(vector<S> &v) {}
template <typename Head, typename... Tail, class S> void renumber(vector<S> &v, Head &&a, Tail &&...tail) {
    for(auto &&e : a) e = lb(v, e);
    renumber(v, tail...);
}
template <class S, class... Args> vector<S> zip(vector<S> &head, Args &&...args) {
    vector<S> v;
    fold_in(v, head, args...);
    sort(all(v)), v.erase(unique(all(v)), v.end());
    renumber(v, head, args...);
    return v;
}
// bit 演算系
ll pow2(int i) { return 1LL << i; }
int topbit(signed t) { return t == 0 ? -1 : 31 - __builtin_clz(t); }
int topbit(ll t) { return t == 0 ? -1 : 63 - __builtin_clzll(t); }
int lowbit(signed a) { return a == 0 ? 32 : __builtin_ctz(a); }
int lowbit(ll a) { return a == 0 ? 64 : __builtin_ctzll(a); }
// int allbit(int n) { return (1 << n) - 1; }
ll allbit(ll n) { return (1LL << n) - 1; }
int popcount(signed t) { return __builtin_popcount(t); }
int popcount(ll t) { return __builtin_popcountll(t); }
bool ispow2(int i) { return i && (i & -i) == i; }

int in() {
    int x;
    cin >> x;
    return x;
}
ll lin() {
    unsigned long long x;
    cin >> x;
    return x;
}

template <class T> pair<T, T> operator-(const pair<T, T> &x, const pair<T, T> &y) { return pair<T, T>(x.fi - y.fi, x.se - y.se); }
template <class T> pair<T, T> operator+(const pair<T, T> &x, const pair<T, T> &y) { return pair<T, T>(x.fi + y.fi, x.se + y.se); }
template <class T> pair<T, T> operator&(const pair<T, T> &l, const pair<T, T> &r) { return pair<T, T>(max(l.fi, r.fi), min(l.se, r.se)); }

// template <class T> pair<T, T> &operator+=(pair<T, T> x, const pair<T, T> &y) {
//     x = x + y;
//     return &x;
// }
// template <class T> pair<T, T> &operator-=(pair<T, T> x, const pair<T, T> &y) {
//     x = x - y;
//     return &x;
// }

template <class T> ll operator*(const pair<T, T> &x, const pair<T, T> &y) { return (ll)x.fi * y.fi + (ll)x.se * y.se; }

template <typename T> struct edge {
    int from, to;
    T cost;
    int id;
    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
    edge(int from, int to, T cost, int id) : from(from), to(to), cost(cost), id(id) {}
    constexpr bool operator<(const edge<T> &rhs) const noexcept { return cost < rhs.cost; }
    edge &operator=(const int &x) {
        to = x;
        return *this;
    }
    operator int() const { return to; }
};
template <typename T> using Edges = vector<edge<T>>;

using Tree = vector<vector<int>>;
using Graph = vector<vector<int>>;
template <class T> using Wgraph = vector<vector<edge<T>>>;
Graph getG(int n, int m = -1, bool directed = false, int margin = 1) {
    Tree res(n);
    if(m == -1) m = n - 1;
    while(m--) {
        int a, b;
        cin >> a >> b;
        a -= margin, b -= margin;
        res[a].emplace_back(b);
        if(!directed) res[b].emplace_back(a);
    }
    return move(res);
}
template <class T> Wgraph<T> getWg(int n, int m = -1, bool directed = false, int margin = 1) {
    Wgraph<T> res(n);
    if(m == -1) m = n - 1;
    while(m--) {
        int a, b;
        T c;
        cin >> a >> b >> c;
        a -= margin, b -= margin;
        res[a].emplace_back(b, c);
        if(!directed) res[b].emplace_back(a, c);
    }
    return move(res);
}
void add(Graph &G, int x, int y) { G[x].eb(y), G[y].eb(x); }
template <class S> void add(Wgraph<S> &G, int x, int y, S c) { G[x].eb(y, c), G[y].eb(x, c); }

#define i128 __int128_t
#define ull unsigned long long int
#define TEST                                                                                                                                                   \
    INT(testcases);                                                                                                                                            \
    while(testcases--)
template <class T> ostream &operator<<(ostream &os, const vector<T> &v) {
    for(auto it = begin(v); it != end(v); ++it) {
        if(it == begin(v))
            os << *it;
        else
            os << " " << *it;
    }
    return os;
}
template <class T, class S> ostream &operator<<(ostream &os, const pair<T, S> &p) {
    os << p.first << " " << p.second;
    return os;
}
template <class S, class T> string to_string(pair<S, T> p) { return "(" + to_string(p.first) + "," + to_string(p.second) + ")"; }
template <class A> string to_string(A v) {
    if(v.empty()) return "{}";
    string ret = "{";
    for(auto &x : v) ret += to_string(x) + ",";
    ret.back() = '}';
    return ret;
}
string to_string(string s) { return "\"" + s + "\""; }
string to_string(char c) { return string(1, c); }

#ifdef _LOCAL
void dump() { cerr << endl; }
template <class Head, class... Tail> void dump(Head head, Tail... tail) {
    cerr << to_string(head) << " ";
    dump(tail...);
}
#define endl '\n'
#undef endl
#define debug(x)                                                                                                                                               \
    cout << #x << ": ";                                                                                                                                        \
    dump(x)
#else
void dump() {}
template <class Head, class... Tail> void dump(Head head, Tail... tail) {}
#define debug(x)
#endif

template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
struct Setup_io {
    Setup_io() {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
        cout << fixed << setprecision(15);
    }
} setup_io;
#define drop(s) cout << #s << endl, exit(0)

template <int N> struct ndFORarray {
    std::array<int, N> v;
    ndFORarray(std::array<int, N> v_) : v(v_) {}
    struct ndFORitr {
        const std::array<int, N> &v;
        std::array<int, N> tmp;
        bool is_end;
        ndFORitr(const std::array<int, N> &v_) : v(v_), tmp(), is_end(false) {}
        bool operator!=(const ndFORitr &) const { return !is_end; }
        void operator++() {
            int pos = N - 1;
            while(pos != -1) {
                tmp[pos] += 1;
                if(tmp[pos] == v[pos]) {
                    tmp[pos] = 0;
                    pos -= 1;
                } else {
                    break;
                }
            }
            if(pos == -1) { is_end = true; }
        }
        const std::array<int, N> &operator*() const { return tmp; }
    };
    ndFORitr begin() const { return ndFORitr(v); }
    ndFORitr end() const { return ndFORitr(v); }
};

struct ndFORvector {
    std::vector<int> v;
    ndFORvector(std::vector<int> v_) : v(v_) {}
    struct ndFORitr {
        const std::vector<int> &v;
        std::vector<int> tmp;
        bool is_end;
        ndFORitr(const std::vector<int> &v_) : v(v_), tmp(v.size(), 0), is_end(false) {}
        bool operator!=(const ndFORitr &) const { return !is_end; }
        void operator++() {
            int pos = v.size() - 1;
            while(pos != -1) {
                tmp[pos] += 1;
                if(tmp[pos] == v[pos]) {
                    tmp[pos] = 0;
                    pos -= 1;
                } else {
                    break;
                }
            }
            if(pos == -1) { is_end = true; }
        }
        const std::vector<int> &operator*() const { return tmp; }
    };
    ndFORitr begin() const { return ndFORitr(v); }
    ndFORitr end() const { return ndFORitr(v); }
};

auto ndFOR(std::vector<int> v) { return ndFORvector(v); }
template <class... Ts> auto ndFOR(Ts... v) { return ndFORarray<std::tuple_size<std::tuple<Ts...>>::value>({v...}); }
template <class F> struct REC {
    F f;
    REC(F &&f_) : f(std::forward<F>(f_)) {}
    template <class... Args> auto operator()(Args &&...args) const { return f(*this, std::forward<Args>(args)...); }
};

#pragma endregion

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

// TODO [l, r[
/**
 * @brief Range Chmin Chmax Add Update Range Min Max Sum Segment Tree Beats!
 * @docs docs/segment-tree/segment-tree-beats.md
 */

// https://judge.yosupo.jp/submission/204887
int main() {
    INT(n, Q);
    VEC(ll, a, n);
    AngelBeats seg(a); // TODO [l, r[
    while(Q--) {
        INT(t, l, r);
        switch(t) {
        case 0: {
            LL(x);
            seg.range_chmin(l, r, x); // TODO [l, r[
            break;
        }
        case 1: {
            LL(x);
            seg.range_chmax(l, r, x);
            break;
        }
        case 2: {
            LL(x);
            seg.range_add(l, r, x);
            break;
        }
        case 3: cout << seg.range_sum(l, r) << endl; break;
        default: break;
        }
    }
}
