//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;

//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return string(1, c);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A>
string to_string(A v);

string to_string(vector<bool> v) {
    bool first = true;
    string res = "[";
    for (auto x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += x ? "true" : "false";
    }
    res += "]";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}


template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "[";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "]";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(xd) << "\033[0m" << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m";)

#define GA          dbg(0)
#define RAYA        cout << "\033[101m" << "================================" << "\033[0m" << endl;

const bool isDebugging = true;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA

const bool isDebugging = false;
#endif
//* /Debugger

using ll = long long;
using db = long double; // or double if tight TL
using str = string;

using pi = pair<int,int>;
using pl = pair<ll, ll>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vl = V<ll>;
using vb = V<bool>;
using vpi = V<pi>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7;
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}


//* Template
/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */

tcT> struct BIT {
	int N; V<T> data;
	void init(int _N) { N = _N; data.rsz(N); }
	void add(int p, T x) { for (++p;p<=N;p+=p&-p) data[p-1] += x; }
	T sum(int l, int r) { return sum(r+1)-sum(l); }
	T sum(int r) { T s = 0; for(;r;r-=r&-r)s+=data[r-1]; return s; }
	int lower_bound(T sum) {
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1<<25; pw; pw >>= 1) {
			int npos = pos+pw;
			if (npos <= N && data[npos-1] < sum)
				pos = npos, sum -= data[pos-1];
		}
		return pos;
	}
};

//* /Template

ll brute(ll n, ll k, vl a, vl b) {
    ll re = 0;
    for(int mask = 0; mask < (1 << n); mask++) {
        ll lre = 0;
        vl id;
        vl bs;
        for(ll bit = 0; bit < n; bit++) {
            if(mask & (1LL << bit)) {
                id.emplace_back(bit);
                lre -= a[bit];
                bs.emplace_back(b[bit]);
            } else {

            }
        }
        sort(all(bs));

        const int N = sz(bs);
        for(int i = 0; i < min(int(k), N); i++) {
            bs.pop_back();
        }
        lre += accumulate(all(bs), 0LL);
        re = max(re, lre);
    }
    for(int mask = 0; mask < (1 << n); mask++) {
        ll lre = 0;
        vl id;
        vl bs;
        for(ll bit = 0; bit < n; bit++) {
            if(mask & (1LL << bit)) {
                id.emplace_back(bit);
                lre -= a[bit];
                bs.emplace_back(b[bit]);
            } else {

            }
        }
        sort(all(bs));
        const int N = sz(bs);
        for(int i = 0; i < min(int(k), N); i++) {
            bs.pop_back();
        }
        lre += accumulate(all(bs), 0LL);
        if(lre == re) {
            vl A, B;
            for(auto& i: id) {
                A.emplace_back(a[i]);
                B.emplace_back(b[i]);
            }
            // dbg("chosen");
            // dbg(A);
            // dbg(B);
            // dbg("/chosen");
        }
    }
    return re;
}

ll brute2(ll n, ll k, vl a, vl b) {
    // <>
    V<pl> oo;
    for(int i = 0; i < n; i++) {
        if(a[i] > b[i]) {

        } else {
            oo.emplace_back(a[i], b[i]);
        }
    }
    a.clear();
    b.clear();
    for(auto& [x, y]: oo) {
        a.emplace_back(x);
        b.emplace_back(y);
    }
    n = sz(oo);

    ll re = 0;
    for(int i = 0; i < n; i++) {
        ll lre = 0;
        vl bs;
        for(int j = 0; j <= i; j++) {
            lre -= a[j];
            bs.emplace_back(b[j]);
        }
        sor(bs);
        const int N = sz(bs);
        for(int j = 0; j < min(int(k), N); j++) {
            bs.pop_back();
        }
        lre += accumulate(all(bs), 0LL);
        re = max(re, lre);
    }
    return re;
}


ll slv(ll n, ll k, vl a, vl b) {
    V<pl> temp;
    for(int i = 0; i < n; i++) {
        if(a[i] > b[i]) {

        } else {
            temp.emplace_back(a[i], b[i]);
        }
    }
    sort(all(temp));
    a.clear();
    b.clear();
    for(auto& [x, y]: temp) {
        a.emplace_back(x);
        b.emplace_back(y);
    }
    n = sz(temp);
    // dbg(n, k);
    // dbg(a);
    // dbg(b);


    // <>
    V<pl> order;
    for(ll i = 0; i < n; i++) {
        order.emplace_back(b[i], i);
    }
    sort(all(order));
    reverse(all(order));
    // dbg(order);
    map<int, int> forwards;
    for(int i = 0; i < n; i++) {
        forwards[order[i].second] = i + 1;
    }
    // dbg(forwards);

    BIT<ll> st_cnt, st_sum;
    const int MAXN = n + 5;
    st_cnt.init(MAXN + 5);
    st_sum.init(MAXN + 5);

        // <>
        auto ddd = [&]() -> void {
            if(isDebugging) {
                vl temp_cnt, temp_sum;
                for(int i = 0; i < MAXN; i++) {
                    temp_cnt.emplace_back(st_cnt.sum(i, i));
                    temp_sum.emplace_back(st_sum.sum(i, i));
                }
                // dbg(temp_cnt);
                // dbg(temp_sum);
            }
        };
    ll re = 0;
    ll sum_a = 0, sum_b = 0;
    for(int i = 0; i < n; i++) {
        // dbg("ga");
        // dbg(i, forwards[i], a[i], b[i]);
        sum_a += a[i];
        sum_b += b[i];

        st_cnt.add(forwards[i], +1);
        st_sum.add(forwards[i], b[i]);
        ddd();

        ll S = 0;
        if(st_cnt.sum(0, MAXN) <= k) {
            // dbg("not enough");
            S = st_sum.sum(0, MAXN);
        } else {
            // dbg("enough");
            int left = -1; // always bad
            int right = MAXN; // always good
            while(left + 1 < right) {
                int middle = (left + right) >> 1;
                if(st_cnt.sum(0, middle) >= k) right = middle;
                else left = middle;
            }
            S = st_sum.sum(0, right);
        }
        // dbg(sum_a, sum_b, S);
        re = max(re, -sum_a + sum_b - S);
    }
    return re;
}

void solve() {
    ll n, k; cin >> n >> k;
    vl a(n), b(n);
    for(auto& x: a) cin >> x;
    for(auto& x: b) cin >> x;
    dbg(n, k);
    dbg(a);
    dbg(b);
    ll re = slv(n, k, a, b);
    dbg(re);
    cout << re << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(0) {
        RAYA;
        RAYA;
        RAYA;

        ll n = rng_ll(1, 16);
        ll k = rng_ll(0, n);
        V<pl> temp(n);
        for(auto& [x, y]: temp) {
            x = rng_ll(1, ll(1e2));
            ll adi = rng_ll(0, 100);
            y = x + adi;
            //x = rng_ll(1, 100);
            //y = rng_ll(1, 100);
        }
        sort(all(temp));

        vl a, b;
        for(auto& [x, y]: temp) {
            if(x < y || true) {
                a.emplace_back(x);
                b.emplace_back(y);
            }
        }
        n = sz(a);
        k = rng_ll(0, n);
        dbg(n, k);
        // dbg(a);
        // dbg(b);
        dbg("Brute");
        ll ans = brute(n, k, a, b);
        dbg("/Brute");
        ll gre = slv(n, k, a, b);
        dbg(ans, gre);
        assert(ans == gre);
    }

    int t = 1;
    cin >> t;
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
    #endif
}
