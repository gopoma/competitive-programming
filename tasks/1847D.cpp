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
#define dbg(...) 0

void slv(ll n, ll m, ll q, vector<char> S, V<pl> intervals, vl que) {

    set<ll> aux;
    for(ll x = 1; x <= n; x++) aux.emplace(x);

    vl order;
    vector<bool> vis(n + 1);
    for(auto& [L, R]: intervals) {
        while(true) {
            auto it = aux.lower_bound(L);
            if(it == aux.end()) break;

            ll x = *it;
            if(x > R) break;

            order.emplace_back(x);
            assert(aux.find(x) != aux.end());
            aux.erase(aux.find(x));
            vis[x] = true;
        }
    }
    dbg(order);


    // free
    vl cntFree(5);
    for(ll x = 1; x <= n; x++) {
        if(!vis[x]) {
            cntFree[S[x] - '0']++;
        }
    }
    dbg(cntFree[0], cntFree[1]);


    map<ll, ll> forwards;
    for(ll i = 0; i < sz(order); i++) {
        forwards[order[i]] = i + 1;
    }

    BIT<ll> st; st.init(sz(order) + 5);
    for(auto& x: order) {
        st.add(forwards[x], (S[x] == '1'));
    }
    auto ddd = [&]() -> void {
        if(isDebugging) {
            vl tempSt;
            for(ll i = 1; i <= sz(order); i++) {
                tempSt.emplace_back(st.sum(i, i));
            }
            dbg(tempSt);
        }
    };
    ddd();



    for(auto& x: que) {
        RAYA;
        dbg(x);
        dbg(S);
        if(vis[x]) {
            st.add(forwards[x], -(S[x] == '1'));
            S[x] = (S[x] == '0')? '1' : '0';
            st.add(forwards[x], +(S[x] == '1'));
        } else {
            cntFree[S[x] - '0']--;
            S[x] = (S[x] == '0')? '1' : '0';
            cntFree[S[x] - '0']++;
        }
        ddd();

        ll zeros = cntFree[0];
        ll ones = cntFree[1];
        dbg(zeros, ones);

        ll bads = sz(order) - st.sum(1, sz(order));
        ll take = min(bads, ones);
        ones -= take;
        ll contrib1 = take;
        dbg(bads, take, zeros, ones);

        ll onesInCritical  = st.sum(1, sz(order)) + take;
        ll onesAlreadyGood = st.sum(1, onesInCritical) + take;
        ll badZeros = onesInCritical - onesAlreadyGood;
        dbg(onesInCritical, onesAlreadyGood, badZeros);

        ll contrib2 = 0;
        if(badZeros > 0) {
            assert(ones == 0);
            contrib2 += badZeros;
        } else {
            contrib2 += min(badZeros, ones);
        }

        ll re = contrib1 + contrib2;
        dbg(re, contrib1, contrib2);
        cout << re << "\n";
    }
}

void solve() {
    ll n, m, q; cin >> n >> m >> q;
    vector<char> S(n + 1, '?');
    for(int i = 1; i <= n; i++) {
        cin >> S[i];
    }

    V<pl> intervals(m);
    for(auto& [L, R]: intervals) {
        cin >> L >> R;
    }
    vl que(q);
    for(auto& x: que) {
        cin >> x;
    }

    dbg(n, m, q);
    dbg(S);
    dbg(intervals);
    dbg(que);


    slv(n, m, q, S, intervals, que);
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
        RAYA;
        RAYA;
        ll n = rng_ll(1, 1000);
        ll m = rng_ll(1, 1000);
        ll q = rng_ll(1, 1000);
        vector<char> S; S.emplace_back('?');
        for(int i = 0; i < n; i++) S.emplace_back(char('0' + rng_ll(0, 1)));
        V<pl> intervals(m);
        for(auto& [L, R]: intervals) {
            L = rng_ll(1, n);
            R = rng_ll(L, n);
        }
        vl que(q);
        for(auto& x: que) x = rng_ll(1, n);
        dbg(n, m, q);
        dbg(S);
        dbg(intervals);
        dbg(que);
        slv(n, m, q, S, intervals, que);
    }

    int t = 1;
    //* cin >> t;
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
