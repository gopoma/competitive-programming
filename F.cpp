#ifdef LOCAL
    #ifdef _WIN32
        #define WIN32_LEAN_AND_MEAN
        #define NOMINMAX
        #include <windows.h>
        #include <psapi.h>
    #else
        #include <sys/resource.h>
    #endif
#endif




//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing


#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;




//* Debugger
void print_memory_usage() {
#ifdef LOCAL
    #ifdef _WIN32
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            long double block = 1024;
            long double taken = pmc.PeakWorkingSetSize / (block * block);

            std::cerr << "\n";
            std::cerr << "\033[42m++++++++++++++++++++\033[0m\n";
            std::cerr << "\033[42m[Memory] Peak Working Set: "
            << taken << " MB\033[0m\n";
            std::cerr << "\033[42m++++++++++++++++++++\033[0m";
        }
    #else
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        #ifdef __APPLE__
            double peak_mb = usage.ru_maxrss / (1024.0 * 1024.0); // macOS en Bytes
        #else
            double peak_mb = usage.ru_maxrss / 1024.0;            // Linux en KiB
        #endif
        std::cerr << "[Memory] Peak RSS: " << peak_mb << " MB\n";
    #endif
#endif
}




#ifdef LOCAL
    #include "helpers/debug.h"

    const bool isDebugging = true;
#else
    #define dbg(...)     0
    #define chk(...)     0
    #define RAYA         0

    const bool isDebugging = false;
#endif
//* /Debugger



using ll = long long;
using db = long double; // or double if tight TL
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;
#define mp make_pair
#define f  first
#define s  second



#define tcT template<class T
#define tcTU tcT, class U

tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

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
tcT > int lwb(V<T> &a, const T &b) { return int(lb(all(a), b) - bg(a)); }
tcT > int upb(V<T> &a, const T &b) { return int(ub(all(a), b) - bg(a)); }



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



const int MOD = int(1e9) + 7;
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
const int dx4[4]{1, 0, -1, 0}, dy4[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); }  // # of bits set
constexpr int bits(int x) {  // assert(x >= 0); // make C++11 compatible until
	                         // USACO updates ...
	return x == 0 ? 0 : 31 - __builtin_clz(x);
}  // floor(log2(x))
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }

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

tcTU > T fstTrue(T lo, T hi, U f) {
	++hi;
	assert(lo <= hi);  // assuming f is increasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo) / 2;
		f(mid) ? hi = mid : lo = mid + 1;
	}
	return lo;
}
tcTU > T lstTrue(T lo, T hi, U f) {
	--lo;
	assert(lo <= hi);  // assuming f is decreasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo + 1) / 2;
		f(mid) ? lo = mid : hi = mid - 1;
	}
	return lo;
}
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



void setIn(string s) { freopen(s.c_str(), "r", stdin); }
void setOut(string s) { freopen(s.c_str(), "w", stdout); }

const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
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

const int dx8[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dy8[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

ll custom_abs(ll x) {
    if(x < 0) return -x;
    return +x;
}
//? /Custom Helpers




// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
    return uniform_int_distribution<int>(L,R)(rng);
}

ll rng_ll(ll L, ll R) { assert(L <= R);
    return uniform_int_distribution<ll>(L,R)(rng);
}

// return double in [L,R] inclusive
db rng_db(db L, db R) { assert(L <= R);
    return uniform_real_distribution<db>(L,R)(rng);
}

template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
    assert(N >= 1 && back >= 0); vpi ed;
    FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
    return ed;
}




//* Template
namespace OY {
    namespace OFFLINERARSC2D {
        using size_type = uint32_t;
        template <typename SizeType, typename WeightType>
        struct Rect {
            SizeType m_x[2], m_y[2];
            WeightType m_w;
            WeightType weight() const { return m_w; }
        };
        template <typename SizeType>
        struct Rect<SizeType, bool> {
            SizeType m_x[2], m_y[2];
            static constexpr bool weight() { return true; }
        };
        template <typename SizeType>
        struct Query {
            SizeType m_x[2], m_y[2], m_y2[2];
        };
        template <typename SizeType, typename WeightType, typename SumType = WeightType>
        struct Table {
            static constexpr bool is_bool = std::is_same<WeightType, bool>::value;
            using rect = Rect<SizeType, WeightType>;
            using query = Query<SizeType>;
            std::vector<rect> m_rects;
            std::vector<query> m_queries;
            std::vector<SizeType> m_sorted_ys;
            Table(size_type rect_cnt = 0, size_type query_cnt = 0) { m_rects.reserve(rect_cnt), m_queries.reserve(query_cnt); }
            void add_rect(SizeType x_min, SizeType x_max, SizeType y_min, SizeType y_max, WeightType w = 1) {
                if constexpr (is_bool)
                    m_rects.push_back({x_min, x_max + 1, y_min, y_max});
                else
                    m_rects.push_back({x_min, x_max + 1, y_min, y_max, w});
            }
            void add_query(SizeType x_min, SizeType x_max, SizeType y_min, SizeType y_max) { m_queries.push_back({x_min, x_max + 1, y_min, y_max + 1}); }
            std::vector<SumType> solve() {
                struct pair {
                    SizeType m_val;
                    size_type m_index;
                    bool operator<(const pair &rhs) const { return m_val < rhs.m_val; }
                };
                struct node {
                    SumType m_val[4];
                    node &operator+=(const node &rhs) {
                        m_val[0] += rhs.m_val[0], m_val[1] += rhs.m_val[1], m_val[2] += rhs.m_val[2], m_val[3] += rhs.m_val[3];
                        return *this;
                    }
                };
                std::vector<pair> ps(m_rects.size() * 2);
                for (size_type i = 0; i != m_rects.size(); i++) ps[i * 2] = {m_rects[i].m_y[0], i * 2}, ps[i * 2 + 1] = {m_rects[i].m_y[1] + 1, i * 2 + 1};
                std::sort(ps.begin(), ps.end());
                m_sorted_ys.reserve(ps.size());
                for (size_type i = 0; i != ps.size(); i++) {
                    if (!i || ps[i].m_val != ps[i - 1].m_val) m_sorted_ys.push_back(ps[i].m_val);
                    m_rects[ps[i].m_index >> 1].m_y[ps[i].m_index & 1] = m_sorted_ys.size() - 1;
                }
                std::vector<pair> qs(m_queries.size() * 2);
                for (size_type i = 0; i != m_rects.size(); i++) ps[i * 2] = {m_rects[i].m_x[0], i * 2}, ps[i * 2 + 1] = {m_rects[i].m_x[1], i * 2 + 1};
                for (size_type i = 0; i != m_queries.size(); i++) {
                    m_queries[i].m_y2[0] = std::lower_bound(m_sorted_ys.begin(), m_sorted_ys.end(), m_queries[i].m_y[0]) - m_sorted_ys.begin();
                    m_queries[i].m_y2[1] = std::lower_bound(m_sorted_ys.begin(), m_sorted_ys.end(), m_queries[i].m_y[1]) - m_sorted_ys.begin();
                    qs[i * 2] = {m_queries[i].m_x[0], i * 2}, qs[i * 2 + 1] = {m_queries[i].m_x[1], i * 2 + 1};
                }
                std::sort(ps.begin(), ps.end());
                std::sort(qs.begin(), qs.end());
                pair *p = ps.data(), *pend = ps.data() + ps.size();
                std::vector<node> sum(m_sorted_ys.size() + 1);
                std::vector<SumType> res(m_queries.size());
                auto add = [&](size_type i, const node &inc) {
                    for (; i < sum.size(); i += (i + 1) & (-i - 1)) sum[i] += inc;
                };
                auto presum = [&](size_type i) {
                    node res{};
                    for (; ~i; i -= (i + 1) & (-i - 1)) res += sum[i];
                    return res;
                };
                for (auto &q : qs) {
                    for (; p != pend && p->m_val < q.m_val; p++) {
                        auto &rect = m_rects[p->m_index >> 1];
                        size_type d = p->m_index & 1;
                        SumType l0 = m_sorted_ys[rect.m_y[0]], r0 = m_sorted_ys[rect.m_y[1]];
                        if (d) {
                            SumType w = -(SumType)rect.weight(), w2 = -w * rect.m_x[1];
                            add(rect.m_y[0], {-l0 * w2, w2, -l0 * w, w});
                            add(rect.m_y[1], {r0 * w2, -w2, r0 * w, -w});
                        } else {
                            SumType w = rect.weight(), w2 = -w * rect.m_x[0];
                            add(rect.m_y[0], {-l0 * w2, w2, -l0 * w, w});
                            add(rect.m_y[1], {r0 * w2, -w2, r0 * w, -w});
                        }
                    }
                    auto &qr = m_queries[q.m_index >> 1];
                    auto s1 = presum(qr.m_y2[0] - 1), s2 = presum(qr.m_y2[1] - 1);
                    SumType a = s2.m_val[0] + (SumType)s2.m_val[1] * qr.m_y[1] - (s1.m_val[0] + (SumType)s1.m_val[1] * qr.m_y[0]);
                    SumType b = s2.m_val[2] + (SumType)s2.m_val[3] * qr.m_y[1] - (s1.m_val[2] + (SumType)s1.m_val[3] * qr.m_y[0]);
                    if (q.m_index & 1)
                        res[q.m_index >> 1] += a + m_queries[q.m_index >> 1].m_x[1] * b;
                    else
                        res[q.m_index >> 1] -= a + m_queries[q.m_index >> 1].m_x[0] * b;
                }
                return res;
            }
        };
    }
}
//* /Template

void solve() {
    // run A < A3.in
    // xd A < A4.in

    int n, m, q; cin >> n >> m >> q;
    vi L(n), R(n);
    for(int i = 0; i < n; i++) {
        cin >> L[i] >> R[i];
    }


    OY::OFFLINERARSC2D::Table<uint32_t, ll, ll> S(n, q);

    for(int i = 0; i < n; i++) {
        int l1 = i + 1;
        int r1 = L[i];

        int l2 = i + 1;
        int r2 = R[i];

        S.add_rect(l1, l2, r1, r2, 1);
    }

    rep(q) {
        int l1, l2, r1, r2; cin >> l1 >> l2 >> r1 >> r2;
        dbg(l1, l2, r1, r2);

        S.add_query(l1, l2, r1, r2);
    }

    auto res = S.solve();
    for(auto& x: res) cout << x << "\n";
}

// Static Rectangle Add Rectangle Sum
// https://judge.yosupo.jp/submission/210893

// F - Count Cells in a Window
// https://atcoder.jp/contests/abc477/tasks/abc4
int main() {
    cin.tie(0)->sync_with_stdio(0);

    if(isDebugging) {
        dbg("debug");
        // setIn("xd.in");
    }

    int t = 1;
    // cin >> t;
    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        solve();
    }


    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";

        print_memory_usage();
    #endif
}
