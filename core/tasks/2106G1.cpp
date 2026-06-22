#pragma GCC optimize ("Ofast")
//* #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //* for Stress Testing



#include <bits/stdc++.h>
using namespace std;



// building blocks
using ll = long long;
using db = long double; // or double if tight TL
using str = string;

//* priority_queue for minimum
//* template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

//* using ull  = unsigned long long;
//* using i64  = long long;
//* using u64  = uint64_t;
//* using i128 = __int128;
//* using u128 = __uint128_t;
//* using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f first
#define s second



#define tcT template<class T
#define tcTU tcT, class U
#define tcTUU tcT, class ...U

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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



// vectors
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
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



// Debugger
//* __int128_t printer
std::ostream& operator<<( std::ostream& dest, __int128_t value ) {
    std::ostream::sentry s(dest);
    if (s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char* d = std::end(buffer);

        do {
            -- d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);

        if(value < 0) {
            -- d;
            *d = '-';
        }

        int len = int(std::end(buffer) - d);
        if(dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

const string PAIR_LEFT = "(";
const string PAIR_RIGHT = ")";
const string IT_LEFT = "[";
const string IT_RIGHT = "]";
const string PAIR_SEP = ", ";
const string IT_SEP = ", ";



// benq - print any container + pair
template <typename T, typename = void>
struct is_iterable: false_type {};

template <typename T>
struct is_iterable<T,
    void_t<decltype(begin(declval<T>())),
    decltype(end(declval<T>()))>
>: true_type {};



template <typename T>
typename enable_if<
    is_iterable<T>::value &&
    !is_same<T, string>::value, ostream&
>::type operator<<(ostream &cout, T const &v);



template <typename A, typename B>
ostream &operator<<(ostream &cout, pair<A, B> const &p) {
    return cout << PAIR_LEFT << p.f << PAIR_SEP << p.s << PAIR_RIGHT;
}



template <typename T>
typename enable_if<
    is_iterable<T>::value &&
    !is_same<T, string>::value, ostream&
>::type operator<<(ostream &cout, T const &v) {
    cout << IT_LEFT;
    for (auto it = v.begin(); it != v.end();) {
        cout << *it;
        if(++it != v.end()) {
            cout << IT_SEP;
        }
    }
    return cout << IT_RIGHT;
}



template <typename A, typename B>
istream &operator>>(istream &cin, pair<A, B> &p) {
    cin >> p.first;
    return cin >> p.second;
}



template <typename T>
void debug(string s, T x) {
    cerr << "\033[1;34m" << s << "\033[0;32m = \033[35m" << x << "\033[0m\n";
}

template <typename T, typename... Args>
void debug(string s, T x, Args... args) {
    for (int i = 0, b = 0; i < (int)s.size(); i++)
        if (s[i] == '(' || s[i] == '{') {
            b++;
        } else if (s[i] == ')' || s[i] == '}') {
            b--;
        } else if (s[i] == ',' && b == 0) {
            cerr << "\033[1;34m" << s.substr(0, i) << "\033[0;32m = \033[35m" << x << "\033[31m | ";
            debug(s.substr(s.find_first_not_of(' ', i + 1)), args...);
            break;
        }
}



#ifdef LOCAL
    const bool isDebugging = true;

    #define MACRO(code) do {code} while (false)
    #define dbg(...) MACRO(cerr << "Line(" << __LINE__ << "): "; debug(#__VA_ARGS__, __VA_ARGS__);)
    #define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);
    #define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
    const bool isDebugging = false;

    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
    return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time).count();
}
// /Debugger



//* Helpers
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

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}
//* /Helpers

//* Custom Helpers
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
//* /Custom Helpers



const int MOD = 1e9 + 7;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const int INF = int(1e9) + 5;
const db PI = acos((db)-1);

const int dx[4]{1, 0, -1, 0};  //? for every grid problem!!
const int dy[4]{0, 1, 0, -1};  //? for every grid problem!!
//* const int dx[8]{1, 0, -1,  0, 1,  1, -1, -1};  //? for every grid problem!!
//* const int dy[8]{0, 1,  0, -1, 1, -1,  1, -1};  //? for every grid problem!!

mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



//* Template
//* /Template

void slv(ll n, ll ROOT, vl values) {
    ll tot = 0;

    auto query1 = [&](vl& a) -> ll {
        tot++;
        if(isDebugging) {
            ll rpta = 0;
            for(auto& x: a) {
                chk(1 <= x && x <= n);
                if(x == ROOT) rpta += values[ROOT - 1];
                else if(x == 1) rpta += values[ROOT - 1] + values[0];
                else rpta += values[ROOT - 1] + values[0] + values[x - 1];
            }
            return rpta;
        } else {
            //* dbg(response[0], vroot);
            const ll k = sz(a);
            cout << "? 1 " << k << " ";

            for(auto& x: a) cout << x << " ";
            cout << endl;

            ll rpta; cin >> rpta;
            return rpta;
        }

    };

    auto query2 = [&](ll x) -> void {
        if(isDebugging) {
            values[x - 1] = -values[x - 1];
        }
        tot++;
        cout << "? 2 " << x << endl;
    };

    auto answer = [&](vl response) -> void {
        chk(tot <= n + 200);

        dbg(values);
        dbg(response);
        chk(response == values);
        for(auto& x: response) assert(x == -1 || x == +1);

        cout << "! ";
        for(auto& x: response) cout << x << " ";
        cout << endl;
    };

    vl ONE{1};
    ll res = query1(ONE);
    {
        if(res == -1 || res == 1) {
            //* const ll root = 1;
            //* go go go
            ll val_node_1 = res;

            vl response(n);
            response[0] = val_node_1;

            for(ll x = 2; x <= n; x++) {
                vl tmp{x};
                ll val_current_node = query1(tmp);
                response[x - 1] = val_current_node - response[0];
            }

            answer(response);
            return;
        }
    }

    ll vroot_plus_v1 = res;
    query2(1);
    ll vroot_plus_minus_v1 = query1(ONE);

    ll vroot = fdiv(vroot_plus_v1 + vroot_plus_minus_v1, 2LL);
    ll v1_original = vroot_plus_v1 - vroot;
    ll v1 = -v1_original;
    dbg(vroot, v1);

    vl response(n);
    response[0] = v1;

    ll left = 2;
    ll right = n;
    {
        vl bucket_sizes{20, 2, 1};
        for(auto& it: bucket_sizes) {
            const ll BUCKET_SIZE = it;
            dbg(BUCKET_SIZE, left, right);

            for(ll start = left; start <= right; start += BUCKET_SIZE) {
                const ll L = start;
                const ll R = min(L + BUCKET_SIZE - 1LL, right);
                dbg("xd", BUCKET_SIZE, L, R);

                vl bucket;
                for(ll cur = L; cur <= R; cur++) {
                    bucket.eb(cur);
                }

                ll S = query1(bucket);
                query2(1);
                ll S2 = query1(bucket);

                const ll k = sz(bucket);
                bool ok = (S - S2) != (2LL * k * response[0]);
                dbg(BUCKET_SIZE, L, R, ok);
                if(ok) {
                    left = L;
                    right = R;
                    response[0] = -response[0];
                    break;
                }
                response[0] = -response[0];
            }
        }
    }
    dbg(left, right);
    chk(1 <= left && left <= right && right <= n);
    chk(left == right);
    const ll root = left;
    chk(root != 1);

    response[root - 1] = vroot;
    for(ll x = 2; x <= n; x++) {
        if(x != root) {
            dbg(response[0]);
            vl C{x};
            ll d = query1(C);
            response[x - 1] = d - vroot - response[0];
        }
    }

    answer(response);
}

void solve() {
    ll n; cin >> n;
    vpl edges(n - 1);
    for(auto& [u, v]: edges) {
        cin >> u >> v;
    }

    vl a{};
    slv(n, -1, a);
}



// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
	assert(N >= 1 && back >= 0); vpi ed;
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed; }

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
    //* cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
	//? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);
	//* cin.exceptions(cin.failbit);
	// throws exception when do smth illegal
	// ex. try to read letter into int
    dbg(isDebugging);



    //? Stress Testing
    while(0) {
        RAYA;
        dbg("Brute");
        dbg("/Brute");
        dbg("Greedy");
        dbg("/Greedy");

        ll n = rng_ll(2, 5);
        ll ROOT = rng_ll(1, n);
        vl values(n);
        for(auto& x: values) {
            while(x == 0) {
                x = rng_ll(-1, 1);
            }
        }
        dbg(n);
        dbg(ROOT);
        dbg(values);
        slv(n, ROOT, values);
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
