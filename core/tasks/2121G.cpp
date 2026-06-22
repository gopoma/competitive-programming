//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
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
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
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

void solve() {
    ll n; cin >> n;
    vector<char> S(n + 1, '$');
    for(int i = 1; i <= n; i++) cin >> S[i];
    dbg(n);
    dbg(S);



    vl a(n + 1);
    for(int i = 1; i <= n; i++) {
        if(S[i] == '1') a[i] = 1;
        else a[i] = -1;
    }
    vl pref = a;
    for(int i = 1; i <= n; i++) {
        pref[i] += pref[i - 1];
    }

    dbg(a);
    dbg(pref);

    V<pl> b;
    for(int i = 1; i <= n; i++) {
        b.emplace_back(pref[i - 1], i);
    }
    sort(all(b));
    dbg(b);



    vl id(n + 1);
    {
        ll cnt = 0;
        for(auto& [_, i]: b) {
            id[i] = cnt++;
        }
    }



    vl suff_0(n + 2);
    vl suff_1(n + 2);
    for(int i = n; i >= 1; i--) {
        if(S[i] == '0') {
            suff_0[i]++;
        } else {
            suff_1[i]++;
        }
        suff_0[i] += suff_0[i + 1];
        suff_1[i] += suff_1[i + 1];
    }
    dbg(suff_0);
    dbg(suff_1);


    BIT<ll> st_0; st_0.init(n + 5);
    BIT<ll> st_1; st_1.init(n + 5);
    BIT<ll> st_cnt; st_cnt.init(n + 5);

    ll res = 0;
    for(ll i = 1; i <= n; i++) {
        RAYA;
        dbg(i, a[i], pref[i]);
        {
            int id_bit = id[i];
            dbg(id_bit);

            st_0.add(id_bit, suff_0[i]);
            st_1.add(id_bit, suff_1[i]);
            st_cnt.add(id_bit, +1);
        }

        //* pref[i] - pref[j] >= 0 - +cnt[1]
        //* pref[i] >= pref[j]
        //* pref[j] <= pref[i]
        auto it = upper_bound(all(b), make_pair(pref[i], ll(1e9) + 5));

        int ones_R = -1;
        if(it == b.begin()) {

        } else {
            it--;
            dbg(*it);
            ones_R = id[(*it).second];
        }
        dbg(ones_R);

        if(ones_R != -1) {
            ll sum_ones = st_1.sum(0, ones_R);
            ll cnt_ones = st_cnt.sum(0, ones_R);
            ll contrib_ones = sum_ones - cnt_ones * suff_1[i + 1];
            dbg(sum_ones, cnt_ones, contrib_ones);
            res += contrib_ones;
        }

        ll sum_zeros = st_0.sum(ones_R + 1, n + 4);
        ll cnt_zeros = st_cnt.sum(ones_R + 1, n + 4);
        ll contrib_zeros = sum_zeros - cnt_zeros * suff_0[i + 1];
        dbg(sum_zeros, cnt_zeros, contrib_zeros);
        res += contrib_zeros;
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1; cin >> t;
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
