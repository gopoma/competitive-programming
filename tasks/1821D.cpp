//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

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
 * Description: 1D point update and range query where \texttt{cmb} is
 	* any associative operation. \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 * API: SegTree<node> tree; tree.init(int(n));
 */

tcT> struct SegTree { // cmb(ID,b) = b
	// const T ID{}; T cmb(T a, T b) { return a+b; }
    T ID{}; T cmb(T a, T b) { return a+b; }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// zero-indexed, inclusive
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}
	/// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
	/// 	if (r < lo || val > seg[ind]) return -1;
	/// 	if (l == r) return l;
	/// 	int m = (l+r)/2;
	/// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
	/// 	return first_at_least(lo,val,2*ind+1,m+1,r);
	/// }
};
// /here goes the template!

struct node {
    static long long Mod;

	long long val;

	node(): val(1LL) {}

	node(long long _val) : val(_val) {}

	node operator + (const node &rhs) const {
		return node((val * rhs.val) % Mod);
	}
};

//* /Template

ll brute(ll n, ll k, vl L, vl R) {
    const int MX = R.back();
    vector<bool> on(MX + 15);
    for(int i = 0; i < n; i++) {
        for(int j = L[i]; j <= R[i]; j++) {
            on[j] = true;
        }
    }

    auto dp = [&](auto&& dp, int i, bool taking, bool taken, int cnt) -> ll {
        if(cnt == k && taking == false) return 0;
        if(i == MX + 5) return BIG;

        ll re = BIG;
        if(taking) {
            if(taken) {
                // go nxt
                if(on[i + 1]) {
                    re = min(re, dp(dp, i + 1, true, true, cnt + 1) + 1);
                }
                assert(on[i]);

                // stop
                re = min(re, dp(dp, i, false, true, cnt) + 1);
            } else {
                assert(false);
            }
        } else {
            if(taken) {
                // skip
                re = min(re, dp(dp, i + 1, false, false, cnt) + 1);
            } else {
                // take
                if(on[i]) {
                    re = min(re, dp(dp, i, true, true, cnt + 1) + 1);
                }
                // skip
                re = min(re, dp(dp, i + 1, false, false, cnt) + 1);
            }

        }
        return re;
    };

    ll re = dp(dp, 0, false, false, 0);
    if(re == BIG) return -1;
    return re;
}

ll slv(ll n, ll k, vl L, vl R) {
    {
        ll tot = 0;
        for(int i = 0; i < n; i++) {
            tot += (R[i] - L[i] + 1);
        }
        if(tot < k) {
            return -1;
        }
    }



    vl len(n);
    for(int i = 0; i < n; i++) {
        len[i] = R[i] - L[i] + 1;
    }
    vector<pair<ll, ll>> temp;
    for(int i = 0; i < n; i++) {
        temp.emplace_back(len[i], i);
    }
    sort(all(temp));
    reverse(all(temp));
    dbg(temp);



    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        auto [_, id] = temp[i];
        p[id] = i;
    }
    dbg(p);



    SegTree<ll> st_sum, st_cnt;
    st_sum.init(n);
    st_cnt.init(n);



    ll response = BIG;
    ll ones = 0;
    ll pSum = 0;
    for(int i = 0; i < n; i++) {
        RAYA;
        auto updNxt = [&]() -> void {
            if(len[i] == 1) {
                ones++;
            } else {
                st_sum.upd(p[i], len[i]);
                st_cnt.upd(p[i], 1);
            }
        };

        pSum += len[i];
        dbg(i, pSum);
        if(pSum < k) {
            dbg("skip");
            updNxt();
            continue;
        }
        dbg("go");

        ll re = L[i] + 2;
        ll K = k - 1;

        if(K == 0) {
            response = min(response, re);

            updNxt();
            continue;
        }




        ll left = -1; // always bad
        ll right = n - 1; // always good
        while(left + 1 < right) {
            ll middle = (left + right) >> 1LL;
            if(st_sum.query(0, middle) >= K) { right = middle; }
            else { left = middle; }
        }
        ll taken = st_cnt.query(0, right);
        dbg(right);
        dbg(K, taken);

        re += 2LL * taken;
        K -= st_sum.query(0, right);

        K = max(K, 0LL);

        if(K > 0) {
            ll take = min(K, len[i] - 1);
            K -= take;
            re += take;
        }

        if(K > 0) {
            ll take = min(ones, K);
            K -= take;
            re += 2LL * take;
        }
        dbg(K);
        dbg(re);
        assert(K == 0);
        response = min(response, re);

        updNxt();
    }
    return response;
}

void solve() {
    ll n, k; cin >> n >> k;
    vl L(n), R(n);
    for(auto& x: L) cin >> x;
    for(auto& x: R) cin >> x;
    dbg(n, k);
    dbg(L);
    dbg(R);

    ll re = slv(n, k, L, R);
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
        RAYA;
        ll n = rng_ll(1, 5);
        ll k = rng_ll(1, 10);

        vl L, R;

        ll curR = 0;
        for(int i = 0; i < n; i++) {
            ll nxtL = curR + rng_ll(2, 3);
            ll gap = rng_ll(1, 3);
            ll nxtR = nxtL + gap - 1;
            curR = nxtR;

            L.emplace_back(nxtL);
            R.emplace_back(nxtR);
        }

        dbg(n, k);
        dbg(L);
        dbg(R);

        ll ans = brute(n, k, L, R);
        ll gre = slv(n, k, L, R);
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
