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
//* Template
/**
 * Description: A set (not multiset!) with support for finding the $n$'th
   * element, and finding the index of an element. Change \texttt{null\_type} to get a map.
 * Time: O(\log N)
 * Source: KACTL
   * https://codeforces.com/blog/entry/11080
 * Verification: many
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tcT> using Tree = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
#define ook order_of_key
#define fbo find_by_order

/**
int atMost(Tree<pi>& T, int r) {
	return T.ook({r,MOD}); }
int getSum(Tree<pi>& T, int l, int r) {
	return atMost(T,r)-atMost(T,l-1); }
*/

long long count_inv(vl a) {
    const int n = sz(a);
    assert(n == sz(a));

    Tree<pl> st;

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        ans += ll(i - st.ook(mp(a[i], n + 79)));

        st.insert(mp(a[i], i));
    }
    return ans;
}
//* /Template

int find_lis(vector<int> a) {
	int lis = 0;
	vector<int> dp(a.size(), 1);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (a[j] < a[i]) { dp[i] = max(dp[i], dp[j] + 1); }
		}
		lis = max(lis, dp[i]);
	}
	return lis;
}

//* /Template

//? https://www.geeksforgeeks.org/dsa/construction-of-longest-increasing-subsequence-using-dynamic-programming/
vector<int> getLIS(int N, vector<int> arr) {
    vector<pair<int, int>> dp;
    unordered_map<int, int> prv;

    for (int ix = N - 1; ix >= 0; --ix) {
        int ve = -arr[ix];

        auto it = lower_bound(dp.begin(), dp.end(), make_pair(ve, 0),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.first < b.first;
             });

        int tmp = -1;
        int i = distance(dp.begin(), it);

        if (i == dp.size()) {
            if (!dp.empty()) {
                tmp = dp.back().second;
            }
            dp.emplace_back(ve, ix);
        } else {
            if (i > 0) {
                tmp = dp[i-1].second;
            }
            dp[i] = {ve, ix};
        }
        prv[ix] = tmp;
    }

    vector<int> ret;
    int cur = dp.back().second;
    while (cur >= 0) {
        ret.push_back(arr[cur]);
        cur = prv[cur];
    }

    return ret;
}

//* https://www.geeksforgeeks.org/dsa/sum-of-all-subarrays/
ll sS(vector<ll> arr) {
    ll n = arr.size();
    ll res = 0;
    for(int L = 0; L < n; L++) {
        for(int R = L; R < n; R++) {
            for(int k = L; k <= R; k++) {
                res += arr[k];
            }
        }
    }
    return res;
}

ll subarraySum(vector<ll> arr) {
    ll n = arr.size();
    ll res = 0;

    for (ll i = 0; i < n; i++)
        res += (arr[i] * (i + 1) * (n - i));

    return res;
}

ll brute(int n, vi a) {
    ll res = 0;
    for(int L = 0; L < n; L++) {
        for(int R = L; R < n; R++) {
            vi temp;
            for(int k = L; k <= R; k++) {
                temp.emplace_back(a[k]);
            }
            reverse(all(temp));
            res += find_lis(temp);
        }
    }
    return res;
}

ll slv(int n, vi a) {
    reverse(all(a));
    dbg(a);

    map<int, int> where;
    for(int i = 0; i < n; i++) {
        where[a[i]] = i;
    }

    auto lis_arr = getLIS(n, a);
    dbg(lis_arr);

    vl C(n);
    for(auto& x: lis_arr) {
        C[where[x]] = +1;
    }

    vl pref = C;
    for(int i = 1; i < n; i++) {
        pref[i] += pref[i - 1];
    }

    vl prefpref = pref;
    for(int i = 1; i < n; i++) {
        prefpref[i] += prefpref[i - 1];
    }
    dbg(C);
    dbg(pref);

    vl zeros(n, 1);
    for(auto& x: lis_arr) {
        zeros[where[x]] = 0;
    }

    for(int i = 1; i < n; i++) {
        zeros[i] += zeros[i - 1];
    }

    auto query = [&](vl& pref_arr, ll L, ll R) -> ll {
        if(L < 0 || R < 0 || L > R || L >= n || R >= n) return 0LL;
        ll sum = pref_arr[R];
        if(0 <= L - 1) sum -= pref_arr[L - 1];
        return sum;
    };


    ll res = 0;
    for(int i = 0; i < n; i++) {
        ll cnt = i + 1;
        ll contrib1 = (cnt * pref[i]);
        ll contrib2 = query(prefpref, 0, i - 1);
        ll contrib3 = query(zeros, 0, i);
        ll adi = contrib1 - contrib2 + contrib3;
        //* dbg(i, cnt, contrib1, contrib2, contrib3, adi);
        res += adi;
    }
    return res;
}

void solve() {
    int n; cin >> n;
    vi a(n); for(auto& x: a) cin >> x;
    dbg(n, a);
    ll response = slv(n, a);
    cout << response << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

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
